#ifndef DARWIN_FTS_H_INCLUDED
#define DARWIN_FTS_H_INCLUDED
/* Temporarily force FTS_COMPAT until we've cleared up the fallout */
#ifndef WANT_FTS_NEW
# ifndef WANT_FTS_COMPAT
#  define WANT_FTS_COMPAT 1
# endif
#endif
#include <Availability.h>
#ifdef VARIANT_INODE32
# undef WANT_FTS_NEW
# define WANT_FTS_COMPAT 1
#elif defined(WANT_FTS_NEW)
# undef WANT_FTS_COMPAT
#elif !defined(WANT_FTS_COMPAT)
# if defined(__MAC_OS_X_VERSION_MIN_REQUIRED) && __MAC_OS_X_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# elif defined(__IPHONE_OS_VERSION_MIN_REQUIRED) && __IPHONE_OS_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# elif defined(__WATCH_OS_VERSION_MIN_REQUIRED) && __WATCH_OS_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# elif defined(__TV_OS_VERSION_MIN_REQUIRED) && __TV_OS_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# elif defined(__BRIDGE_OS_VERSION_MIN_REQUIRED) && __BRIDGE_OS_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# elif defined(__VISION_OS_VERSION_MIN_REQUIRED) && __VISION_OS_VERSION_MIN_REQUIRED < 280000
#  define WANT_FTS_COMPAT 1
# endif
#endif
#ifdef WANT_FTS_COMPAT
# include <fts_compat.h>
#else
# include <fts_new.h>
#endif
#endif /* DARWIN_FTS_H_INCLUDED */
