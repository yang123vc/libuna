/*
 * ISO 8859-3 codepage (Latin 3) function
 *
 * Copyright (c) 2008-2012, Joachim Metz <joachim.metz@gmail.com>
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

#include "libuna_codepage_iso_8859_3.h"

/* Extended ASCII to Unicode character lookup table for ISO 8859-3 codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_iso_8859_3_byte_stream_to_unicode_base_0xa0[ 96 ] = {
	0x00a0, 0x0126, 0x02d8, 0x00a3, 0x00a4, 0xfffd, 0x0124, 0x00a7,
	0x00a8, 0x0130, 0x015e, 0x011e, 0x0134, 0x00ad, 0xfffd, 0x017b,
	0x00b0, 0x0127, 0x00b2, 0x00b3, 0x00b4, 0x00b5, 0x0125, 0x00b7,
	0x00b8, 0x0131, 0x015f, 0x011f, 0x0135, 0x00bd, 0xfffd, 0x017c,
	0x00c0, 0x00c1, 0x00c2, 0xfffd, 0x00c4, 0x010a, 0x0108, 0x00c7,
	0x00c8, 0x00c9, 0x00ca, 0x00cb, 0x00cc, 0x00cd, 0x00ce, 0x00cf,
	0xfffd, 0x00d1, 0x00d2, 0x00d3, 0x00d4, 0x0120, 0x00d6, 0x00d7,
	0x011c, 0x00d9, 0x00da, 0x00db, 0x00dc, 0x016c, 0x015c, 0x00df,
	0x00e0, 0x00e1, 0x00e2, 0xfffd, 0x00e4, 0x010b, 0x0109, 0x00e7,
	0x00e8, 0x00e9, 0x00ea, 0x00eb, 0x00ec, 0x00ed, 0x00ee, 0x00ef,
	0xfffd, 0x00f1, 0x00f2, 0x00f3, 0x00f4, 0x0121, 0x00f6, 0x00f7,
	0x011d, 0x00f9, 0x00fa, 0x00fb, 0x00fc, 0x016d, 0x015d, 0x02d9
};

/* Unicode to ASCII character lookup table for ISO 8859-3 codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x00a0[ 96 ] = {
	0xa0, 0x1a, 0x1a, 0xa3, 0xa4, 0x1a, 0x1a, 0xa7,
	0xa8, 0x1a, 0x1a, 0x1a, 0x1a, 0xad, 0x1a, 0x1a,
	0xb0, 0x1a, 0xb2, 0xb3, 0xb4, 0xb5, 0x1a, 0xb7,
	0xb8, 0x1a, 0x1a, 0x1a, 0x1a, 0xbd, 0x1a, 0x1a,
	0xc0, 0xc1, 0xc2, 0x1a, 0xc4, 0x1a, 0x1a, 0xc7,
	0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
	0x1a, 0xd1, 0xd2, 0xd3, 0xd4, 0x1a, 0xd6, 0xd7,
	0x1a, 0xd9, 0xda, 0xdb, 0xdc, 0x1a, 0x1a, 0xdf,
	0xe0, 0xe1, 0xe2, 0x1a, 0xe4, 0x1a, 0x1a, 0xe7,
	0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
	0x1a, 0xf1, 0xf2, 0xf3, 0xf4, 0x1a, 0xf6, 0xf7,
	0x1a, 0xf9, 0xfa, 0xfb, 0xfc, 0x1a, 0x1a, 0x1a
};

const uint8_t libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0108[ 8 ] = {
	0xc6, 0xe6, 0xc5, 0xe5, 0x1a, 0x1a, 0x1a, 0x1a
};

const uint8_t libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0118[ 16 ] = {
	0x1a, 0x1a, 0x1a, 0x1a, 0xd8, 0xf8, 0xab, 0xbb,
	0xd5, 0xf5, 0x1a, 0x1a, 0xa6, 0xb6, 0xa1, 0xb1
};

const uint8_t libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0130[ 8 ] = {
	0xa9, 0xb9, 0x1a, 0x1a, 0xac, 0xbc, 0x1a, 0x1a
};

const uint8_t libuna_codepage_iso_8859_3_unicode_to_byte_stream_base_0x0158[ 8 ] = {
	0x1a, 0x1a, 0x1a, 0x1a, 0xde, 0xfe, 0xaa, 0xba
};

