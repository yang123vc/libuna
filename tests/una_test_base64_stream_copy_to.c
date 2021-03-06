/*
 * Unicode and ASCII (byte stream) conversion library base64 stream copy to testing program
 *
 * Copyright (C) 2008-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "una_test_libuna.h"

/* Tests copying a base64 stream to a byte stream
 * Returns 1 if successful, 0 if not or -1 on error
 */
int una_test_base64_stream_copy_to_byte_stream(
     const uint8_t *base64_stream,
     size_t base64_stream_size,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint32_t base64_variant,
     uint8_t flags,
     const uint8_t *expected_byte_stream,
     size_t expected_byte_stream_size,
     int expected_result )
{
	libuna_error_t *error          = NULL;
	size_t result_byte_stream_size = 0;
	int result                     = 0;

        fprintf(
         stdout,
         "Testing copying base64 stream to byte stream with variant: 0x%08" PRIx32 "\t",
	 base64_variant );

	result = libuna_base64_stream_size_to_byte_stream(
	          base64_stream,
	          base64_stream_size,
	          &result_byte_stream_size,
	          base64_variant,
	          flags,
	          &error );

	if( result == 1 )
	{
		if( result_byte_stream_size != expected_byte_stream_size )
		{
			result = 0;
		}
	}
	if( result != 0 )
	{
		if( result == -1 )
		{
			libuna_error_free(
			 &error );
		}
		result = libuna_base64_stream_copy_to_byte_stream(
			  base64_stream,
			  base64_stream_size,
			  byte_stream,
			  byte_stream_size,
			  base64_variant,
			  flags,
			  &error );
	}
	if( result == 1 )
	{
		if( memory_compare(
		     byte_stream,
		     expected_byte_stream,
		     sizeof( uint8_t ) * expected_byte_stream_size ) != 0 )
		{
			result = 0;
		}
	}
	if( result == expected_result )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	if( result == -1 )
	{
		if( expected_result != -1 )
		{
			libuna_error_backtrace_fprint(
			 error,
			 stderr );
		}
		libuna_error_free(
		 &error );
	}
	if( result == expected_result )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return( result );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	uint8_t byte_stream[ 256 ];

	uint8_t expected_byte_stream[ 16 ] = {
		'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 0xc3, 0xa1, ' ', 't', 'e', 's', 't', '.' };

	uint8_t rfc1421_base64_stream[ 25 ] = {
		'V', 'G', 'h', 'p', 'c', 'y', 'B', 'p', 'c', 'y', 'D', 'D', 'o', 'S', 'B', '0', 'Z', 'X', 'N', '0',
	        'L', 'g', '=', '=', '\n' };

	uint8_t rfc1421_utf16be_base64_stream[ 50 ] = {
		0, 'V', 0, 'G', 0, 'h', 0, 'p', 0, 'c', 0, 'y', 0, 'B', 0, 'p', 0, 'c', 0, 'y', 0, 'D', 0, 'D',
	        0, 'o', 0, 'S', 0, 'B', 0, '0', 0, 'Z', 0, 'X', 0, 'N', 0, '0', 0, 'L', 0, 'g', 0, '=', 0, '=',
	        0, '\n' };

	uint8_t rfc1421_utf32le_base64_stream[ 100 ] = {
		'V', 0, 0, 0, 'G', 0, 0, 0, 'h', 0, 0, 0, 'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'B', 0, 0, 0,
	        'p', 0, 0, 0, 'c', 0, 0, 0, 'y', 0, 0, 0, 'D', 0, 0, 0, 'D', 0, 0, 0, 'o', 0, 0, 0, 'S', 0, 0, 0,
	        'B', 0, 0, 0, '0', 0, 0, 0, 'Z', 0, 0, 0, 'X', 0, 0, 0, 'N', 0, 0, 0, '0', 0, 0, 0, 'L', 0, 0, 0,
	        'g', 0, 0, 0, '=', 0, 0, 0, '=', 0, 0, 0, '\n', 0, 0, 0 };

	uint8_t rfc1642_base64_stream[ 22 ] = {
		'V', 'G', 'h', 'p', 'c', 'y', 'B', 'p', 'c', 'y', 'D', 'D', 'o', 'S', 'B', '0', 'Z', 'X', 'N', '0',
	        'L', 'g' };

	uint8_t *expected_long_byte_stream = \
		(uint8_t *) "The test of success is not what you do when you are on top. Success is how high you bounce when you hit bottom.\n";

	uint8_t *rfc2045_base64_stream1 = \
		(uint8_t *) "VGhlIHRlc3Qgb2Ygc3VjY2VzcyBpcyBub3Qgd2hhdCB5b3UgZG8gd2hlbiB5b3UgYXJlIG9uIHRv\n"
		            "cC4gU3VjY2VzcyBpcyBob3cgaGlnaCB5b3UgYm91bmNlIHdoZW4geW91IGhpdCBib3R0b20uCg==\n";

	uint8_t *rfc2045_base64_stream2 = \
		(uint8_t *) "\tVGhlIHRlc3Qgb2Ygc3VjY2VzcyBpcyBub3Qgd2hhdCB5b3UgZG8gd2hlbiB5b3UgYXJlIG9uIHRv  \n"
		            "  cC4gU3VjY2VzcyBpcyBob3cgaGlnaCB5b3UgYm91bmNlIHdoZW4geW91IGhpdCBib3R0b20uCg==\t\n";

	uint8_t expected_byte_stream1[ 6 ] = { 0xe6, 0xb5, 0x8b, 0xe8, 0xaf, 0x95 };

	uint8_t *rfc1642_base64_stream1 = (uint8_t *) "5rWL6K+V";

	uint8_t *url_base64_stream1 = (uint8_t *) "5rWL6K-V";

	uint8_t expected_byte_stream2[ 9 ] = { 0xe8, 0xa9, 0xa6, 0xe3, 0x81, 0xbf, 0xe3, 0x82, 0x8b };

	uint8_t *rfc1642_base64_stream2 = (uint8_t *) "6Kmm44G/44KL";

	uint8_t *url_base64_stream2 = (uint8_t *) "6Kmm44G_44KL";

	libuna_error_t *error = NULL;

	if( argc != 1 )
	{
		fprintf(
		 stderr,
		 "This program does not take arguments.\n" );

		return( EXIT_FAILURE );
	}
	/* Case 1: base64 stream is NULL, base64 stream size is 25, variant RFC1421
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     NULL,
	     25,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421,
	     0,
	     expected_byte_stream,
	     64,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 2: base64 stream is a buffer, base64 stream size is 25, variant RFC1421
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_base64_stream,
	     25,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 3: base64 stream is a buffer, base64 stream size is 25, variant RFC1421
	 *         byte stream is a buffer, byte stream size is 8
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_base64_stream,
	     25,
	     byte_stream,
	     8,
	     LIBUNA_BASE64_VARIANT_RFC1421,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 4: base64 stream is a buffer, base64 stream size is 32, variant RFC1421
	 *         byte stream is NULL, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_base64_stream,
	     25,
	     NULL,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 5: base64 stream is a buffer, base64 stream size is 50, variant RFC1421 in UTF-16 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_utf16be_base64_stream,
	     50,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421 | LIBUNA_BASE64_VARIANT_ENCODING_UTF16_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 6: base64 stream is a buffer, base64 stream size is 50, variant RFC1421 in UTF-16 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_utf16be_base64_stream,
	     50,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421 | LIBUNA_BASE64_VARIANT_ENCODING_UTF16_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 7: base64 stream is a buffer, base64 stream size is 100, variant RFC1421 in UTF-32 big-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_utf32le_base64_stream,
	     100,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421 | LIBUNA_BASE64_VARIANT_ENCODING_UTF32_BIG_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 8: base64 stream is a buffer, base64 stream size is 100, variant RFC1421 in UTF-32 little-endian
	 *         byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1421_utf32le_base64_stream,
	     100,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421 | LIBUNA_BASE64_VARIANT_ENCODING_UTF32_LITTLE_ENDIAN,
	     0,
	     expected_byte_stream,
	     16,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 10: base64 stream is a buffer, base64 stream size is 154, variant RFC2045
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc2045_base64_stream1,
	     154,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC2045,
	     0,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 11: base64 stream is a buffer, base64 stream size is 154, variant RFC1421
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc2045_base64_stream1,
	     154,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1421,
	     0,
	     expected_long_byte_stream,
	     112,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 12: base64 stream is a buffer, base64 stream size is 160, variant RFC2045
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc2045_base64_stream2,
	     160,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC2045,
	     LIBUNA_BASE64_FLAG_STRIP_WHITESPACE,
	     expected_long_byte_stream,
	     112,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 13: base64 stream is a buffer, base64 stream size is 160, variant RFC2045
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: -1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc2045_base64_stream2,
	     160,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC2045,
	     0,
	     expected_long_byte_stream,
	     112,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 14: base64 stream is a buffer, base64 stream size is 8, variant RFC1642
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1642_base64_stream1,
	     8,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1642,
	     0,
	     expected_byte_stream1,
	     6,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 15: base64 stream is a buffer, base64 stream size is 8, variant URL
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     url_base64_stream1,
	     8,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_URL,
	     0,
	     expected_byte_stream1,
	     6,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 16: base64 stream is a buffer, base64 stream size is 12, variant RFC1642
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     rfc1642_base64_stream2,
	     12,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_RFC1642,
	     0,
	     expected_byte_stream2,
	     9,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	/* Case 17: base64 stream is a buffer, base64 stream size is 12, variant URL
	 *          byte stream is a buffer, byte stream size is 256
	 * Expected result: 1
	 */
	if( una_test_base64_stream_copy_to_byte_stream(
	     url_base64_stream2,
	     12,
	     byte_stream,
	     256,
	     LIBUNA_BASE64_VARIANT_URL,
	     0,
	     expected_byte_stream2,
	     9,
	     1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to copy base64 stream to byte stream.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libuna_error_backtrace_fprint(
		 error,
		 stderr );
		libuna_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

