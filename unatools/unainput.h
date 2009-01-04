/*
 * Common input functions for the unatools
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

#if !defined( _UNAINPUT_H )
#define _UNAINPUT_H

#include <common.h>
#include <types.h>

#include "system_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

int unainput_determine_byte_stream_codepage(
     const system_character_t *argument,
     int *byte_stream_codepage );

int unainput_determine_format(
     const system_character_t *argument,
     int *format );

int unainput_determine_newline_conversion(
     const system_character_t *argument,
     int *newline_conversion );

#if defined( __cplusplus )
}
#endif

#endif
