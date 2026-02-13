/*
 * Android NDK build: include autoconf then override SELinux (NDK has no libselinux).
 * Use -include include/autoconf_android.h instead of -include include/autoconf.h
 * so we only need one -include flag.
 */
#include "autoconf.h"
#include "override_selinux_android.h"
