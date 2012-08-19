/*
 * rtp_extension.c
 *
 * The ortpextension library implement RTP extension (Realtime Transport Protocol - RFC 3550)
 * Copyright (C) 2011  Orazio Briante orazio.briante@hotmail.it
 * Laboratory A.R.T.S. - University Mediterranea of Reggio Calabria - Faculty of Engineering
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <ortpextension/rtp_extension.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
  {
#endif

/**
 * Initialize RTP Extension Object Without Words
 * @return Pointer to a initialized RTP Extension
 */
void *
init_rtp_extension()
{

  return (void *) init_rtp_extension_with_length(0);
}

/**
 * Initialize RTP Extension Object With a Number Of Words
 * @param length The Number Of Words to initialize
 * @return Pointer to a initialized RTP Extension
 * */
void *
init_rtp_extension_with_length(uint16_t length)
{

  RtpExtension_t *rtp_extension = malloc(sizeof(RtpExtension_t));
  rtp_extension->type = 0;

  rtp_extension->length = length;

  if (length == 0)
    {
      rtp_extension->extension = 0;
    }
  else
    {
      int size = length * sizeof(uint32_t) * 8;
      rtp_extension->extension = (uint32_t *) malloc(size);
    }

  return rtp_extension;
}

/**
 * To uninitialize an RTP Extension object
 * @param rtp_extension TRP EXTENSION that must be deallocated
 * */
void
uninit_rtp_extension(RtpExtension_t * rtp_extension)
{

  free(rtp_extension->extension);
  rtp_extension->extension = NULL;
  free(rtp_extension);
  rtp_extension = NULL;

}

/**
 * To Set All Params Of a Initialized Rtp Extension Object
 * @param rtp_extension The Initialized Extension
 * @param type The Extension Type
 * @param words The uint32_t Array With The Extension Words
 * @param length - The Number of Words
 */
void
set_extension(RtpExtension_t * rtp_extension, uint16_t type, uint32_t * words,
    uint16_t length)
{

  rtp_extension->type = type;
  rtp_extension->length = 0;
  if (rtp_extension->extension != NULL )
    {
      free(rtp_extension->extension);
      rtp_extension->extension = 0;
    }

  if (length > 0)
    {

      if (words != NULL )
        {

          rtp_extension->length = length;
          rtp_extension->extension = (uint32_t *) malloc(
              length * sizeof(uint32_t));

          int i = 0;
          for (i = 0; i < length; i++)
            {
              rtp_extension->extension[i] = words[i];
            }
        }
    }
}

/**
 * To Convert Rtp Extension Object into a uint32_t Array
 * @param extension The RTP Extension
 * @return Pointer to uint32_t Array
 **/
void *
rtp_extension_to_uint32_t(RtpExtension_t * extension)
{

  uint32_t *extension_buf = (uint32_t *) malloc(
      sizeof(uint32_t) * (extension->length + 1));

  extension_buf[0] = extension->type;
  extension_buf[0] <<= 16;
  extension_buf[0] += extension->length;

  int i = 0;
  if (extension->extension != NULL )
    {

      for (i = extension->length - 1; i >= 0; i--)
        {

          memcpy(&extension_buf[i + 1], &extension->extension[i],
              sizeof(uint32_t));

        }
    }

  return extension_buf;
}

/**
 * Debug Function for RtpExtension_t object
 * @param rtp_extension RTP Extension That Must Be Showed
 */
void
print_rtp_extension(RtpExtension_t * rtp_extension)
{

  fprintf(stderr, "(RtpExtension_t)->type:\t0x%X\n", rtp_extension->type);
  fprintf(stderr, "(RtpExtension_t)->length:\t0x%X\n", rtp_extension->length);

  if (rtp_extension->extension == NULL )
    {
      fprintf(stderr, "(RtpExtension_t)->extension:\tNOT ASSIGNED\n");
    }
  else
    {
      int i = 0, n_word = rtp_extension->length;

      for (i = 0; i < n_word; i++)
        {
          fprintf(stderr, "(RtpExtension_t)->extension[%i]:\t0x%X\n", i,
              rtp_extension->extension[i]);

        }

    }
}

#ifdef __cplusplus
}
#endif
