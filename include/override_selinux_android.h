/*
 * Override autoconf.h SELinux options when building for Android with NDK.
 * NDK does not provide selinux/selinux.h; this header is -included after
 * autoconf.h so these undefs take effect and libbb.h skips the selinux include.
 * Declare stub applet mains so applet_tables.h (which still references them) links.
 *
 * Disable ENABLE_BUSYBOX so the first busybox_main block (help/--list) is not
 * compiled; we keep only the dispatcher and avoid redefinition with the macro.
 */
#undef CONFIG_BUSYBOX
#define CONFIG_BUSYBOX 0
#undef ENABLE_BUSYBOX
#define ENABLE_BUSYBOX 0
#undef IF_BUSYBOX
#define IF_BUSYBOX(...)
#undef IF_NOT_BUSYBOX
#define IF_NOT_BUSYBOX(...) __VA_ARGS__

int chcon_main(int argc, char **argv);
int getenforce_main(int argc, char **argv);
int runcon_main(int argc, char **argv);
int selinuxenabled_main(int argc, char **argv);
int sestatus_main(int argc, char **argv);
int setenforce_main(int argc, char **argv);

#undef CONFIG_SELINUX
#define CONFIG_SELINUX 0
#undef ENABLE_SELINUX
#define ENABLE_SELINUX 0
#undef IF_SELINUX
#define IF_SELINUX(...)
#undef IF_NOT_SELINUX
#define IF_NOT_SELINUX(...) __VA_ARGS__

#undef CONFIG_FEATURE_TAR_SELINUX
#define CONFIG_FEATURE_TAR_SELINUX 0
#undef ENABLE_FEATURE_TAR_SELINUX
#define ENABLE_FEATURE_TAR_SELINUX 0
#undef IF_FEATURE_TAR_SELINUX
#define IF_FEATURE_TAR_SELINUX(...)
#undef IF_NOT_FEATURE_TAR_SELINUX
#define IF_NOT_FEATURE_TAR_SELINUX(...) __VA_ARGS__

#undef CONFIG_SELINUXENABLED
#define CONFIG_SELINUXENABLED 0
#undef ENABLE_SELINUXENABLED
#define ENABLE_SELINUXENABLED 0
#undef IF_SELINUXENABLED
#define IF_SELINUXENABLED(...)
#undef IF_NOT_SELINUXENABLED
#define IF_NOT_SELINUXENABLED(...) __VA_ARGS__

#undef CONFIG_SESTATUS
#define CONFIG_SESTATUS 0
#undef ENABLE_SESTATUS
#define ENABLE_SESTATUS 0
#undef IF_SESTATUS
#define IF_SESTATUS(...)
#undef IF_NOT_SESTATUS
#define IF_NOT_SESTATUS(...) __VA_ARGS__

#undef CONFIG_SETENFORCE
#define CONFIG_SETENFORCE 0
#undef ENABLE_SETENFORCE
#define ENABLE_SETENFORCE 0
#undef IF_SETENFORCE
#define IF_SETENFORCE(...)
#undef IF_NOT_SETENFORCE
#define IF_NOT_SETENFORCE(...) __VA_ARGS__

#undef CONFIG_CHCON
#define CONFIG_CHCON 0
#undef ENABLE_CHCON
#define ENABLE_CHCON 0
#undef IF_CHCON
#define IF_CHCON(...)
#undef IF_NOT_CHCON
#define IF_NOT_CHCON(...) __VA_ARGS__

#undef CONFIG_GETENFORCE
#define CONFIG_GETENFORCE 0
#undef ENABLE_GETENFORCE
#define ENABLE_GETENFORCE 0
#undef IF_GETENFORCE
#define IF_GETENFORCE(...)
#undef IF_NOT_GETENFORCE
#define IF_NOT_GETENFORCE(...) __VA_ARGS__

#undef CONFIG_RUNCON
#define CONFIG_RUNCON 0
#undef ENABLE_RUNCON
#define ENABLE_RUNCON 0
#undef IF_RUNCON
#define IF_RUNCON(...)
#undef IF_NOT_RUNCON
#define IF_NOT_RUNCON(...) __VA_ARGS__
