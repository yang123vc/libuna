/*
 * Configuration file for Windows native compilation
 *
 * Copyright (c) 2006-2008, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _CONFIG_WINDOWS_H )
#define _CONFIG_WINDOWS_H

#include "config.h"

/* Windows does not have other platform specific headers
 */
#undef HAVE_CYGWIN_FS_H
#undef HAVE_LINUX_FS_H
#undef HAVE_SYS_DISKLABEL_H
#undef HAVE_SYS_DISK_H

/* Windows does not have <inttypes.h> or <stdint.h>
 */
#undef HAVE_INTTYPES_H
#undef HAVE_STDINT_H

/* Windows does not have %jd and %zd printf conversion specifiers
 */
#undef HAVE_PRINTF_JD
#undef HAVE_PRINTF_ZD

/* Windows does not have <unistd.h> but uses <io.h> and <share.h> instead
 */
#undef HAVE_UNISTD_H
#define HAVE_IO_H	1
#define HAVE_SHARE_H	1

/* Windows does not have <sys/ioctl.h> and <sys/utsname.h>
 */
#undef HAVE_SYS_IOCTL_H
#undef HAVE_SYS_UTSNAME_H

/* Use Windows crypto API instead of libcrypto or equivalent
 */
#undef HAVE_OPENSSL_MD5_H
#undef HAVE_OPENSSL_OPENSSLV_H
#undef HAVE_LIBCRYPTO
#define HAVE_WINCPRYPT_H	1

/* Use Windows GUID (UUID) calculation algorithms instead of libuuid
 */
#undef HAVE_UUID_UUID_H
#undef HAVE_LIBUUID
#undef HAVE_UUID_GENERATE_RANDOM
#undef HAVE_UUID_GENERATE_TIME

/* Windows does not have getopt or <glob.h>
 */
#undef HAVE_GETOPT
#undef HAVE_GLOB_H

/* Windows does not have <signal.h>
 */
#undef HAVE_SIGNAL_H

/* If wide character support was enabled
 * make use of the wide character support functions
 */
#if defined( HAVE_WIDE_CHARACTER_TYPE )
#define HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS	1
#endif

/* Make sure the function definitions are available
 * these should be normally defined in config.h
 * use the following defintions to control the function
 * definitions per source file in common
 */
#undef HAVE_DATE_TIME
#undef HAVE_DIRECTORY_IO	1
#define HAVE_ERROR_STRING	1
#define HAVE_FILE_IO		1
#define HAVE_FILE_STREAM_IO	1
#define HAVE_NARROW_STRING	1

#if defined( HAVE_WIDE_CHARACTER_TYPE )
#define HAVE_WIDE_STRING	1
#else
#undef HAVE_WIDE_STRING
#endif

/* Functions in common/date_time.h
 */
#if defined( HAVE_DATE_TIME )
#if !defined( HAVE_CTIME_R )
#define HAVE_CTIME_R		1
#endif

#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define HAVE_WCTIME_R		1
#endif

#if !defined( HAVE_GMTIME_R )
#define HAVE_GMTIME_R		1
#endif

#if !defined( HAVE_LOCALTIME_R )
#define HAVE_LOCALTIME_R	1
#endif

#if !defined( HAVE_MKTIME )
#define HAVE_MKTIME		1
#endif

#else
#undef HAVE_CTIME_R
#undef HAVE_WCTIME_R
#undef HAVE_GMTIME_R
#undef HAVE_LOCALTIME_R
#undef HAVE_MKTIME
#endif

/* Functions in common/directory_io.h
 */
#if defined( HAVE_DIRECTORY_IO )
#if !defined( HAVE_MKDIR )
#define HAVE_MKDIR		1
#endif

#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define HAVE_WMKDIR		1 
#endif

#else
#undef HAVE_MKDIR
#undef HAVE_WMKDIR
#endif

/* Functions in common/error_string.h
 */
#if defined( HAVE_ERROR_STRING )
#if !defined( HAVE_STRERROR_R )
#define HAVE_STRERROR_R		1
#endif

#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define HAVE_WCSERROR_R		1
#endif

#else
#undef HAVE_STRERROR_R
#undef HAVE_WCSERROR_R
#endif

/* Functions in common/file_io.h
 */
#if defined( HAVE_FILE_IO )
#if !defined( HAVE_OPEN )
#define HAVE_OPEN		1
#endif

#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define HAVE_WOPEN		1
#endif

#if !defined( HAVE_CLOSE )
#define HAVE_CLOSE		1
#endif

#if !defined( HAVE_LSEEK )
#define HAVE_LSEEK		1
#endif

#if !defined( HAVE_READ )
#define HAVE_READ		1
#endif

#if !defined( HAVE_WRITE )
#define HAVE_WRITE		1
#endif

#else
#undef HAVE_OPEN
#undef HAVE_WOPEN
#undef HAVE_CLOSE
#undef HAVE_LSEEK
#undef HAVE_READ
#undef HAVE_WRITE
#endif

/* Functions in common/file_stream_io.h
 */
#if defined( HAVE_FILE_STREAM_IO )
#if !defined( HAVE_FOPEN )
#define HAVE_FOPEN		1
#endif

#if defined( HAVE_WIDE_CHARACTER_SUPPORT_FUNCTIONS )
#define HAVE_WFOPEN		1
#endif

#if !defined( HAVE_FCLOSE )
#define HAVE_FCLOSE		1
#endif

#if !defined( HAVE_FREAD )
#define HAVE_FREAD		1
#endif

#if !defined( HAVE_FWRITE )
#define HAVE_FWRITE		1
#endif

#else
#undef HAVE_FOPEN
#undef HAVE_WFOPEN
#undef HAVE_FCLOSE
#undef HAVE_FREAD
#undef HAVE_FWRITE
#endif

/* Functions in common/narrow_string.h
 */
#if defined( HAVE_NARROW_STRING )
#if !defined( HAVE_STRLEN )
#define HAVE_STRLEN		1
#endif

#if !defined( HAVE_STRNCMP )
#define HAVE_STRNCMP		1
#endif

#if !defined( HAVE_STRNCPY )
#define HAVE_STRNCPY		1
#endif

#if !defined( HAVE_STRCHR )
#define HAVE_STRCHR		1
#endif

#if !defined( HAVE_STRRCHR )
#define HAVE_STRRCHR		1
#endif

#if !defined( HAVE_SNPRINTF )
#define HAVE_SNPRINTF		1
#endif

#if !defined( HAVE_FGETS )
#define HAVE_FGETS		1
#endif

#define HAVE_ATOI64		1

#else
#undef HAVE_STRLEN
#undef HAVE_STRNCMP
#undef HAVE_STRNCPY
#undef HAVE_STRCHR
#undef HAVE_STRRCHR
#undef HAVE_SNPRINTF
#undef HAVE_FGETS
#undef HAVE_ATOI64
#endif

/* Functions in common/wide_string.h
 */
#if defined( HAVE_WIDE_STRING )
#if !defined( HAVE_WCSLEN )
#define HAVE_WCSLEN		1
#endif

#if !defined( HAVE_WCSNCMP )
#define HAVE_WCSNCMP		1
#endif

#if !defined( HAVE_WCSNCPY )
#define HAVE_WCSNCPY		1
#endif

#if !defined( HAVE_WCSCHR )
#define HAVE_WCSCHR		1
#endif

#if !defined( HAVE_WCSRCHR )
#define HAVE_WCSRCHR		1
#endif

#if !defined( HAVE_SWPRINTF )
#define HAVE_SWPRINTF		1
#endif

#if !defined( HAVE_FGETWS )
#define HAVE_FGETWS		1
#endif

#define HAVE_WTOI64		1

#else
#undef HAVE_WCSLEN
#undef HAVE_WCSNCMP
#undef HAVE_WCSNCPY
#undef HAVE_WCSCHR
#undef HAVE_WCSRCHR
#undef HAVE_SWPRINTF
#undef HAVE_FGETWS
#undef HAVE_WTOI64
#endif

/* Some functions are different within the Windows API
 */
#define HAVE_WINDOWS_API	1

#endif
