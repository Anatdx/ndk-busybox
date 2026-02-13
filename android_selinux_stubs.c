/*
 * Stub implementations of SELinux applet mains for Android NDK builds.
 * NDK has no libselinux; these satisfy the applet table so the linker succeeds.
 * Each stub just returns EXIT_SUCCESS (callers should not reach these when
 * SELinux applets are disabled in the build).
 */
#include "libbb.h"

int chcon_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}

int getenforce_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}

int runcon_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}

int selinuxenabled_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}

int sestatus_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}

int setenforce_main(int argc UNUSED_PARAM, char **argv UNUSED_PARAM)
{
	return EXIT_SUCCESS;
}
