/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
/*
 * CBQ was removed from newer Linux UAPI headers, including recent Android
 * NDKs, but BusyBox tc still decodes CBQ netlink attributes. Keep the ABI
 * definitions from Android common 6.1 when the sysroot no longer has them.
 */
#ifndef BUSYBOX_ANDROID_PKT_SCHED_COMPAT_H
#define BUSYBOX_ANDROID_PKT_SCHED_COMPAT_H

#ifndef TCA_CBQ_MAX
#define TC_CBQ_MAXPRIO 8
#define TC_CBQ_MAXLEVEL 8
#define TC_CBQ_DEF_EWMA 5

struct tc_cbq_lssopt {
	unsigned char change;
	unsigned char flags;
#define TCF_CBQ_LSS_BOUNDED 1
#define TCF_CBQ_LSS_ISOLATED 2
	unsigned char ewma_log;
	unsigned char level;
#define TCF_CBQ_LSS_FLAGS   1
#define TCF_CBQ_LSS_EWMA    2
#define TCF_CBQ_LSS_MAXIDLE 4
#define TCF_CBQ_LSS_MINIDLE 8
#define TCF_CBQ_LSS_OFFTIME 0x10
#define TCF_CBQ_LSS_AVPKT   0x20
	__u32 maxidle;
	__u32 minidle;
	__u32 offtime;
	__u32 avpkt;
};

struct tc_cbq_wrropt {
	unsigned char flags;
	unsigned char priority;
	unsigned char cpriority;
	unsigned char __reserved;
	__u32 allot;
	__u32 weight;
};

struct tc_cbq_ovl {
	unsigned char strategy;
#define TC_CBQ_OVL_CLASSIC  0
#define TC_CBQ_OVL_DELAY    1
#define TC_CBQ_OVL_LOWPRIO  2
#define TC_CBQ_OVL_DROP     3
#define TC_CBQ_OVL_RCLASSIC 4
	unsigned char priority2;
	__u16 pad;
	__u32 penalty;
};

struct tc_cbq_police {
	unsigned char police;
	unsigned char __res1;
	unsigned short __res2;
};

struct tc_cbq_fopt {
	__u32 split;
	__u32 defmap;
	__u32 defchange;
};

struct tc_cbq_xstats {
	__u32 borrows;
	__u32 overactions;
	__s32 avgidle;
	__s32 undertime;
};

enum {
	TCA_CBQ_UNSPEC,
	TCA_CBQ_LSSOPT,
	TCA_CBQ_WRROPT,
	TCA_CBQ_FOPT,
	TCA_CBQ_OVL_STRATEGY,
	TCA_CBQ_RATE,
	TCA_CBQ_RTAB,
	TCA_CBQ_POLICE,
	__TCA_CBQ_MAX,
};

#define TCA_CBQ_MAX (__TCA_CBQ_MAX - 1)
#endif

#endif
