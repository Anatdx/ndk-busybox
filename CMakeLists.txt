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

# Android NDK has no selinux headers; exclude selinux applets and libbb/selinux_common.c,
# and add stub mains so the applet table links.
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  set(BUSYBOX_SOURCES_FILTERED)
  foreach(SRC ${BUSYBOX_SOURCES})
    if(SRC MATCHES "selinux/.*\\.c$" OR SRC MATCHES "libbb/selinux_common\\.c$")
      # skip
    else()
      list(APPEND BUSYBOX_SOURCES_FILTERED ${SRC})
    endif()
  endforeach()
  list(APPEND BUSYBOX_SOURCES_FILTERED ${CMAKE_CURRENT_SOURCE_DIR}/android_selinux_stubs.c)
  set(BUSYBOX_SOURCES ${BUSYBOX_SOURCES_FILTERED})
endif()

add_library(busybox STATIC ${BUSYBOX_SOURCES})

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
)
# Pre-include autoconf (Android uses autoconf_android.h which also disables SELinux for NDK)
if(CMAKE_SYSTEM_NAME STREQUAL "Android")
  target_compile_options(busybox PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/include/autoconf_android.h)
else()
  target_compile_options(busybox PRIVATE -include ${CMAKE_CURRENT_SOURCE_DIR}/include/autoconf.h)
endif()

# When embedded (e.g. into ksud), entry is busybox_main() not main()
if(BUSYBOX_EMBEDDED)
  target_compile_definitions(busybox PRIVATE BUSYBOX_EMBEDDED=1)
endif()
