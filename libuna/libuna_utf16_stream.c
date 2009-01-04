/*
 * UTF-16 stream functions
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

#include <common.h>
#include <types.h>

#include "libuna_definitions.h"
#include "libuna_error.h"
#include "libuna_inline.h"
#include "libuna_types.h"
#include "libuna_unicode_character.h"
#include "libuna_utf16_stream.h"

/* Copies an UTF-16 stream byte order mark (BOM)
 * Returns 1 if successful or -1 on error
 */
LIBUNA_INLINE int libuna_utf16_stream_copy_byte_order_mark(
                   uint8_t *utf16_stream,
                   size_t utf16_stream_size,
                   size_t *utf16_stream_index,
                   uint8_t byte_order,
                   libuna_error_t **error )
{
	static char *function = "libuna_utf16_stream_copy_byte_order_mark";

	if( utf16_stream == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_index == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream index.\n",
		 function );

		return( -1 );
	}
	if( ( *utf16_stream_index + 1 ) >= utf16_stream_size )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_TOO_SMALL,
		 "%s: UTF-16 stream too small.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.\n",
		 function );

		return( -1 );
	}
	if( byte_order == LIBUNA_ENDIAN_BIG )
	{
		utf16_stream[ *utf16_stream_index     ] = 0xfe;
		utf16_stream[ *utf16_stream_index + 1 ] = 0xff;
	}
	else if( byte_order == LIBUNA_ENDIAN_LITTLE )
	{
		utf16_stream[ *utf16_stream_index     ] = 0xff;
		utf16_stream[ *utf16_stream_index + 1 ] = 0xfe;
	}
	*utf16_stream_index += 2;

	return( 1 );
}

/* Determines the size of a UTF-16 stream from a UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf8(
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     size_t *utf16_stream_size,
     libuna_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_size_from_utf8";
	size_t utf8_string_iterator                  = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf8_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream size.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	*utf16_stream_size = 1;

	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_INPUT,
			 "%s: unable to copy Unicode character from UTF-8.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_stream_size,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
			 "%s: unable to determine size of Unicode character in UTF-16.\n",
			 function );

			return( -1 );
		}
	}
	/* Convert the amount of characters into bytes
	 */
	*utf16_stream_size *= 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-8 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf8(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     uint8_t byte_order,
     libuna_utf8_character_t *utf8_string,
     size_t utf8_string_size,
     libuna_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_copy_from_utf8";
	size_t utf8_string_iterator                  = 0;
	size_t utf16_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_stream == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.\n",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-8 string.\n",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_iterator,
	     byte_order,
	     error ) != 1 )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_CONVERSION,
		 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
		 "%s: unable to copy UTF-16 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf8_string_iterator < utf8_string_size )
	{
		/* Convert the UTF-8 string bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf8(
		     &unicode_character,
		     utf8_string,
		     utf8_string_size,
		     &utf8_string_iterator,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_INPUT,
			 "%s: unable to copy Unicode character from UTF-8 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 stream bytes
		 */
		if( libuna_unicode_character_copy_to_utf16_stream(
		     unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_iterator,
		     byte_order,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
			 "%s: unable to copy Unicode character to UTF-16 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Determines the size of a UTF-16 stream from a UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf16(
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     size_t *utf16_stream_size,
     libuna_error_t **error )
{
	static char *function = "libuna_utf16_stream_size_from_utf16";

	if( utf16_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream size.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 * Assumes the UTF-16 string is santized
	 */
	*utf16_stream_size = 1 + utf16_string_size;

	/* Convert the amount of characters into bytes
	 */
	*utf16_stream_size *= 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-16 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf16(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     uint8_t byte_order,
     libuna_utf16_character_t *utf16_string,
     size_t utf16_string_size,
     libuna_error_t **error )
{
	static char *function                    = "libuna_utf16_stream_copy_from_utf16";
	size_t utf16_string_iterator             = 0;
	size_t utf16_stream_iterator             = 0;
	libuna_utf16_character_t utf16_character = 0;

	if( utf16_stream == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.\n",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 string.\n",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_iterator,
	     byte_order,
	     error ) != 1 )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_CONVERSION,
		 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
		 "%s: unable to copy UTF-16 byte order mark.\n",
		 function );

		return( -1 );
	}
	/* Assumes the UTF-16 string is santized
	 */
	while( utf16_string_iterator < utf16_string_size )
	{
		utf16_character = utf16_string[ utf16_string_iterator++ ];

		if( byte_order == LIBUNA_ENDIAN_BIG )
		{
			utf16_stream[ utf16_stream_iterator + 1 ]   = (uint8_t) ( utf16_character & 0xff );
			utf16_character                           >>= 8;
			utf16_stream[ utf16_stream_iterator     ]   = (uint8_t) ( utf16_character & 0xff );
		}
		else if( byte_order == LIBUNA_ENDIAN_LITTLE )
		{
			utf16_stream[ utf16_stream_iterator     ]   = (uint8_t) ( utf16_character & 0xff );
			utf16_character                           >>= 8;
			utf16_stream[ utf16_stream_iterator + 1 ]   = (uint8_t) ( utf16_character & 0xff );
		}
		utf16_stream_iterator += 2;
	}
	return( 1 );
}

/* Determines the size of a UTF-16 stream from a UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_size_from_utf32(
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     size_t *utf16_stream_size,
     libuna_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_size_from_utf32";
	size_t utf32_string_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf32_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream size.\n",
		 function );

		return( -1 );
	}
	/* Add the byte order mark
	 */
	*utf16_stream_size += 1;

	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 character bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_INPUT,
			 "%s: unable to copy Unicode character from UTF-32.\n",
			 function );

			return( -1 );
		}
		/* Determine how many UTF-16 character bytes are required
		 */
		if( libuna_unicode_character_size_to_utf16(
		     unicode_character,
		     utf16_stream_size,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
			 "%s: unable to determine size of Unicode character in UTF-16.\n",
			 function );

			return( -1 );
		}
	}
	/* Convert the amount of characters into bytes
	 */
	*utf16_stream_size *= 2;

	return( 1 );
}

/* Copies an UTF-16 stream from an UTF-32 string
 * Returns 1 if successful or -1 on error
 */
int libuna_utf16_stream_copy_from_utf32(
     uint8_t *utf16_stream,
     size_t utf16_stream_size,
     uint8_t byte_order,
     libuna_utf32_character_t *utf32_string,
     size_t utf32_string_size,
     libuna_error_t **error )
{
	static char *function                        = "libuna_utf16_stream_copy_from_utf32";
	size_t utf32_string_iterator                 = 0;
	size_t utf16_stream_iterator                 = 0;
	libuna_unicode_character_t unicode_character = 0;

	if( utf16_stream == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-16 stream.\n",
		 function );

		return( -1 );
	}
	if( utf16_stream_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 stream size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBUNA_ENDIAN_BIG )
	 && ( byte_order != LIBUNA_ENDIAN_LITTLE ) )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.\n",
		 function );

		return( -1 );
	}
	if( utf32_string == NULL )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_INVALID,
		 "%s: invalid UTF-32 string.\n",
		 function );

		return( -1 );
	}
	if( utf32_string_size > (size_t) SSIZE_MAX )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_ARGUMENTS,
		 LIBUNA_ARGUMENT_ERROR_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-32 string size value exceeds maximum.\n",
		 function );

		return( -1 );
	}
	if( libuna_utf16_stream_copy_byte_order_mark(
	     utf16_stream,
	     utf16_stream_size,
	     &utf16_stream_iterator,
	     byte_order,
	     error ) != 1 )
	{
		libuna_error_set(
		 error,
		 LIBUNA_ERROR_DOMAIN_CONVERSION,
		 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
		 "%s: unable to copy UTF-16 byte order mark.\n",
		 function );

		return( -1 );
	}
	while( utf32_string_iterator < utf32_string_size )
	{
		/* Convert the UTF-32 string bytes into a Unicode character
		 */
		if( libuna_unicode_character_copy_from_utf32(
		     &unicode_character,
		     utf32_string,
		     utf32_string_size,
		     &utf32_string_iterator,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_INPUT,
			 "%s: unable to copy Unicode character from UTF-32 string.\n",
			 function );

			return( -1 );
		}
		/* Convert the Unicode character into UTF-16 stream bytes
		 */
		if( libuna_unicode_character_copy_to_utf16_stream(
		     unicode_character,
		     utf16_stream,
		     utf16_stream_size,
		     &utf16_stream_iterator,
		     byte_order,
                    error ) != 1 )
		{
			libuna_error_set(
			 error,
			 LIBUNA_ERROR_DOMAIN_CONVERSION,
			 LIBUNA_CONVERSION_ERROR_INVALID_OUTPUT,
			 "%s: unable to copy Unicode character to UTF-16 stream.\n",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

