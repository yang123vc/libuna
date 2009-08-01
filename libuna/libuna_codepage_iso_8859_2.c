/*
 * ISO 8859-2 codepage (Central European) function
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include "libuna_codepage_iso_8859_2.h"

/* Extended ASCII to Unicode character lookup table for ISO 8859-2 codepage
 * Unknown are filled with the Unicode replacement character 0xfffd
 */
const uint16_t libuna_codepage_iso_8859_2_byte_stream_to_unicode_base_0xa0[ 96 ] = {
	0x00a0, 0x0104, 0x02d8, 0x0141, 0x00a4, 0x013d, 0x015a, 0x00a7,
	0x00a8, 0x0160, 0x015e, 0x0164, 0x0179, 0x00ad, 0x017d, 0x017b,
	0x00b0, 0x0105, 0x02db, 0x0142, 0x00b4, 0x013e, 0x015b, 0x02c7,
	0x00b8, 0x0161, 0x015f, 0x0165, 0x017a, 0x02dd, 0x017e, 0x017c,
	0x0154, 0x00c1, 0x00c2, 0x0102, 0x00c4, 0x0139, 0x0106, 0x00c7,
	0x010c, 0x00c9, 0x0118, 0x00cb, 0x011a, 0x00cd, 0x00ce, 0x010e,
	0x0110, 0x0143, 0x0147, 0x00d3, 0x00d4, 0x0150, 0x00d6, 0x00d7,
	0x0158, 0x016e, 0x00da, 0x0170, 0x00dc, 0x00dd, 0x0162, 0x00df,
	0x0155, 0x00e1, 0x00e2, 0x0103, 0x00e4, 0x013a, 0x0107, 0x00e7,
	0x010d, 0x00e9, 0x0119, 0x00eb, 0x011b, 0x00ed, 0x00ee, 0x010f,
	0x0111, 0x0144, 0x0148, 0x00f3, 0x00f4, 0x0151, 0x00f6, 0x00f7,
	0x0159, 0x016f, 0x00fa, 0x0171, 0x00fc, 0x00fd, 0x0163, 0x02d9
};

/* Unicode to ASCII character lookup table for ISO 8859-2 codepage
 * Unknown are filled with the ASCII replacement character 0x1a
 */
const uint8_t libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x00a0[ 128 ] = {
	0xa0, 0x1a, 0x1a, 0x1a, 0xa4, 0x1a, 0x1a, 0xa7,
	0xa8, 0x1a, 0x1a, 0x1a, 0x1a, 0xad, 0x1a, 0x1a,
	0xb0, 0x1a, 0x1a, 0x1a, 0xb4, 0x1a, 0x1a, 0x1a,
	0xb8, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0xc1, 0xc2, 0x1a, 0xc4, 0x1a, 0x1a, 0xc7,
	0x1a, 0xc9, 0x1a, 0xcb, 0x1a, 0xcd, 0xce, 0x1a,
	0x1a, 0x1a, 0x1a, 0xd3, 0xd4, 0x1a, 0xd6, 0xd7,
	0x1a, 0x1a, 0xda, 0x1a, 0xdc, 0xdd, 0x1a, 0xdf,
	0x1a, 0xe1, 0xe2, 0x1a, 0xe4, 0x1a, 0x1a, 0xe7,
	0x1a, 0xe9, 0x1a, 0xeb, 0x1a, 0xed, 0xee, 0x1a,
	0x1a, 0x1a, 0x1a, 0xf3, 0xf4, 0x1a, 0xf6, 0xf7,
	0x1a, 0x1a, 0xfa, 0x1a, 0xfc, 0xfd, 0x1a, 0x1a,
	0x1a, 0x1a, 0xc3, 0xe3, 0xa1, 0xb1, 0xc6, 0xe6,
	0x1a, 0x1a, 0x1a, 0x1a, 0xc8, 0xe8, 0xcf, 0xef,
	0xd0, 0xf0, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xca, 0xea, 0xcc, 0xec, 0x1a, 0x1a, 0x1a, 0x1a
};

const uint8_t libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x0138[ 72 ] = {
	0x1a, 0xc5, 0xe5, 0x1a, 0x1a, 0xa5, 0xb5, 0x1a,
	0x1a, 0xa3, 0xb3, 0xd1, 0xf1, 0x1a, 0x1a, 0xd2,
	0xf2, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0xd5, 0xf5, 0x1a, 0x1a, 0xc0, 0xe0, 0x1a, 0x1a,
	0xd8, 0xf8, 0xa6, 0xb6, 0x1a, 0x1a, 0xaa, 0xba,
	0xa9, 0xb9, 0xde, 0xfe, 0xab, 0xbb, 0x1a, 0x1a,
	0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0xd9, 0xf9,
	0xdb, 0xfb, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a, 0x1a,
	0x1a, 0xac, 0xbc, 0xaf, 0xbf, 0xae, 0xbe, 0x1a
};

const uint8_t libuna_codepage_iso_8859_2_unicode_to_byte_stream_base_0x02d8[ 8 ] = {
	0xa2, 0xff, 0x1a, 0xb2, 0x1a, 0xbd, 0x1a, 0x1a
};

