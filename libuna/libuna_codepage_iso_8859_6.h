/*
 * ISO 8859-6 codepage (Arabic) functions
 *
 * Copyright (c) 2008-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBUNA_CODEPAGE_ISO_8859_6_H )
#define _LIBUNA_CODEPAGE_ISO_8859_6_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint16_t libuna_codepage_iso_8859_6_byte_stream_to_unicode_base_0xa0[ 96 ];

extern const uint8_t libuna_codepage_iso_8859_6_unicode_to_byte_stream_base_0x0618[ 64 ];

#define libuna_codepage_iso_8859_6_byte_stream_to_unicode( byte_stream_character ) \
	( byte_stream_character < 0xa0 ) ? byte_stream_character : libuna_codepage_iso_8859_6_byte_stream_to_unicode_base_0xa0[ byte_stream_character - 0xa0 ]

#define libuna_codepage_iso_8859_6_unicode_to_byte_stream( unicode_character ) \
	( unicode_character < 0x00a1 ) ? (uint8_t) unicode_character : \
	( unicode_character == 0x00a4 ) ? 0xa4 : \
	( unicode_character == 0x00ad ) ? 0xad : \
	( unicode_character == 0x060c ) ? 0xac : \
	( ( unicode_character >= 0x0618 ) && ( unicode_character < 0x658 ) ) ? libuna_codepage_iso_8859_6_unicode_to_byte_stream_base_0x0618[ unicode_character - 0x0618 ] : \
	0x1a

#if defined( __cplusplus )
}
#endif

#endif

