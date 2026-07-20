# Android libselinux subset

These files come from Magisk v30.7 commit
`e8a58776f1d7bdf852072ad0baa6eceb9a1e4aac`, under
`native/src/external/selinux/libselinux`.

Only the public headers, internal headers, and source files needed by the
BusyBox SELinux applets are kept here. This lets the CMake/NDK build match
Magisk's static `libselinux` linkage without downloading another repository at
configure time. See `LICENSE` for the upstream public-domain notice.
