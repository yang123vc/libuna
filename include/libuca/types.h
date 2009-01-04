/*
 * Type definitions for libuca
 *
 * Copyright (c) 2008, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBUCA_TYPES_H )
#define _LIBUCA_TYPES_H

#include <libuca/features.h>

#if 1 || defined( HAVE_SYS_TYPES_H )
#include <sys/types.h>

#else
#error Missing system type definitions (sys/types.h)
#endif

#if defined( HAVE_WINDOWS_API ) && !defined( HAVE_INTTYPES_H ) && !defined( HAVE_STDINT_H )

/* Define LIBUCA_DEFINITION_INTEGER_TYPES to avoid conflict if types are already defined
 */
#if !defined( LIBUCA_DEFINITION_INTEGER_TYPES )

#define LIBUCA_DEFINITION_INTEGER_TYPES

#ifdef __cplusplus
extern "C" {
#endif

/* Windows does not have <inttypes.h> or <stdint.h> and therefore does not support the
 * (u)int#_t type definitions it has __int# defintions instead
 */
typedef __int8			int8_t;
typedef unsigned __int8		uint8_t;
typedef __int16			int16_t;
typedef unsigned __int16	uint16_t;
typedef __int32			int32_t;
typedef unsigned __int32	uint32_t;

#ifdef __cplusplus
}
#endif

#endif

#elif 1 || defined( HAVE_INTTYPES_H )
#include <inttypes.h>

#elif 1 || defined( HAVE_STDINT_H )
#include <stdint.h>

#else
#error Missing integer type definitions (inttypes.h, stdint.h)
#endif

#if defined( LIBPFF_WIDE_CHARACTER_TYPE )

#if 0 || defined( HAVE_WCHAR_H )

/* __USE_UNIX98 is required to add swprintf definition
 *  */
#if !defined( __USE_UNIX98 )
#define __USE_UNIX98
#define LIBPFF_DEFINITION_UNIX98
#endif

/* __USE_ISOC99 is required to add wcstoll and wcstuoll definition
 *  */
#if !defined( __USE_ISOC99 )
#define __USE_ISOC99
#define LIBPFF_DEFINITION_ISOC99
#endif

#include <wchar.h>

#if defined( LIBPFF_DEFINITION_UNIX98 )
#undef __USE_UNIX98
#undef LIBPFF_DEFINITION_UNIX98
#endif

#if defined( LIBPFF_DEFINITION_ISOC99 )
#undef __USE_ISOC99
#undef LIBPFF_DEFINITION_ISOC99
#endif

#else
#error Missing wide character type definition (wchar.h)
#endif

#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Unicode character definitions
 *  */
typedef uint32_t libuca_unicode_character_t;

/* UTF-8 character definitions
 *  */
typedef uint8_t libuca_utf8_character_t;

/* UTF-16 character definitions
 *  */
typedef uint16_t libuca_utf16_character_t;

/* UTF-32 character definitions
 *  */
typedef uint32_t libuca_utf32_character_t;

#ifdef __cplusplus
}
#endif

#endif

