#include <sys/stat.h>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif


/*
 * Cross-platform version of stat() function.
 * TODO: test it for Windows ;)
 */
