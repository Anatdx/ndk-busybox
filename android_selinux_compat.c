/*
 * Small Android-only pieces omitted from the minimal static libselinux build.
 *
 * Android has no /etc/selinux/config or desktop-style file-context database.
 * BusyBox only calls matchpathcon() as an mkswap fallback after fgetfilecon()
 * reports an unlabeled regular file. Match upstream libselinux's behavior when
 * that database is absent instead of pulling in its PCRE label backend.
 */
#include <errno.h>
#include <sys/stat.h>

int require_seusers;

int matchpathcon(const char *path, mode_t mode, char **context)
{
	(void)path;
	(void)mode;
	(void)context;
	errno = ENOENT;
	return -1;
}
