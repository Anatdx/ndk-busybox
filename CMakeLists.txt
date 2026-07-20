# ndk-busybox: build as static library for embedding (e.g. into ksud).
# Run: python3 scripts/gen_sources_cmake.py  to regenerate busybox_sources.cmake from Android.mk.
cmake_minimum_required(VERSION 3.14)
project(ndk-busybox LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)

# BB_VER must match Android.mk
set(BB_VER "1.36.1-Magisk")
set(BB_BT "AUTOCONF_TIMESTAMP")

include(${CMAKE_CURRENT_SOURCE_DIR}/busybox_sources.cmake)

# Filter out arch-specific .S files that don't match current target
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64|arm64|ARM64")
  set(BB_ARCH_FILTER "x86-64|x86-32")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7|armv7a|ARM")
  set(BB_ARCH_FILTER "x86-64|x86-32")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
  set(BB_ARCH_FILTER "x86-32")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i686|x86")
  set(BB_ARCH_FILTER "x86-64")
else()
  set(BB_ARCH_FILTER "none")
endif()

if(BB_ARCH_FILTER AND NOT BB_ARCH_FILTER STREQUAL "none")
  set(BUSYBOX_SOURCES_FILTERED)
  foreach(SRC ${BUSYBOX_SOURCES})
    if(SRC MATCHES "\\.S$" AND SRC MATCHES "${BB_ARCH_FILTER}")
      # skip this arch-specific asm
    else()
      list(APPEND BUSYBOX_SOURCES_FILTERED ${SRC})
    endif()
  endforeach()
  set(BUSYBOX_SOURCES ${BUSYBOX_SOURCES_FILTERED})
endif()

# Upstream Magisk links BusyBox against a static libselinux. The NDK sysroot
# intentionally does not expose that private platform library, so build the
# matching sources instead of silently replacing the applets with no-op stubs.
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  set(SELINUX_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/android/libselinux)
  set(SELINUX_SRC ${SELINUX_ROOT}/src)
  add_library(busybox_selinux STATIC
    ${SELINUX_SRC}/booleans.c
    ${SELINUX_SRC}/callbacks.c
    ${SELINUX_SRC}/check_context.c
    ${SELINUX_SRC}/compute_create.c
    ${SELINUX_SRC}/context.c
    ${SELINUX_SRC}/enabled.c
    ${SELINUX_SRC}/fgetfilecon.c
    ${SELINUX_SRC}/freecon.c
    ${SELINUX_SRC}/fsetfilecon.c
    ${SELINUX_SRC}/getenforce.c
    ${SELINUX_SRC}/getfilecon.c
    ${SELINUX_SRC}/init.c
    ${SELINUX_SRC}/lgetfilecon.c
    ${SELINUX_SRC}/lsetfilecon.c
    ${SELINUX_SRC}/mapping.c
    ${SELINUX_SRC}/policyvers.c
    ${SELINUX_SRC}/procattr.c
    ${SELINUX_SRC}/selinux_config.c
    ${SELINUX_SRC}/selinux_internal.c
    ${SELINUX_SRC}/sestatus.c
    ${SELINUX_SRC}/setenforce.c
    ${SELINUX_SRC}/setfilecon.c
    ${SELINUX_SRC}/setrans_client.c
    ${CMAKE_CURRENT_SOURCE_DIR}/android_selinux_compat.c
  )
  target_include_directories(busybox_selinux PUBLIC ${SELINUX_ROOT}/include)
  target_include_directories(busybox_selinux PRIVATE ${SELINUX_SRC})
  target_compile_definitions(busybox_selinux PRIVATE
    ANDROID
    DISABLE_SETRANS
    HAVE_REALLOCARRAY
    HAVE_STRLCPY
    fgets_unlocked=fgets
  )
  target_compile_options(busybox_selinux PRIVATE -w)
endif()

add_library(busybox STATIC ${BUSYBOX_SOURCES})

if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  target_link_libraries(busybox PUBLIC busybox_selinux)
endif()

target_include_directories(busybox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_definitions(busybox PUBLIC
  BB_VER="${BB_VER}"
  BB_BT=${BB_BT}
  __USE_BSD
  __USE_GNU
)
target_compile_options(busybox PRIVATE
  -w
  -Wno-implicit-function-declaration
  -Wno-int-conversion
)
target_compile_options(busybox PRIVATE $<$<COMPILE_LANGUAGE:ASM>:-D__ASSEMBLER__>)
target_compile_options(busybox PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/include/autoconf.h)

# When embedded (e.g. into ksud), entry is busybox_main() not main()
if(BUSYBOX_EMBEDDED)
  target_compile_definitions(busybox PRIVATE BUSYBOX_EMBEDDED=1)
endif()
