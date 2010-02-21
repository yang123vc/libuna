/*
 * Split string values functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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

#if !defined( _LIBSYSTEM_SPLIT_VALUES_H )
#define _LIBSYSTEM_SPLIT_VALUES_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libsystem_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libsystem_split_values libsystem_split_values_t;

struct libsystem_split_values
{
	/* The amount of split values
	 */
	int amount_of_values;

	/* The string
	 */
	libsystem_character_t *string;

	/* The values
	 */
	libsystem_character_t **values;

	/* The sizes of the values
	 */
	size_t *sizes;
};

int libsystem_split_values_initialize(
     libsystem_split_values_t **split_values,
     const libsystem_character_t *string,
     size_t string_size,
     int amount_of_values,
     liberror_error_t **error );

int libsystem_split_values_free(
     libsystem_split_values_t **split_values,
     liberror_error_t **error );

int libsystem_split_values_parse_string(
     libsystem_split_values_t **split_values,
     const libsystem_character_t *string,
     size_t string_size,
     libsystem_character_t delimiter,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif
