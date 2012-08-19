/*
 * extension_utils.c
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

#include "extension_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <netinet/in.h>

void *
bytes_inverter_to_packet (uint32_t * value, int length)
{

  int i = 0;
  int iterator = length;

  uint32_t *inputvalue = (uint32_t *) value;
  uint32_t *retvalue = (uint32_t *) malloc (length * sizeof (uint32_t));

  for (i = 0; i <= iterator; i++) {
    retvalue[i] = ntohl (inputvalue[i]);

  }

  return retvalue;
}

void *
bytes_inverter_from_packet (uint32_t * value, int length)
{
  int i = 0;
  int iterator = length;

  uint32_t *inputvalue = (uint32_t *) value;
  uint32_t *retvalue = (uint32_t *) malloc (length * sizeof (uint32_t));

  for (i = 0; i <= iterator; i++) {
    retvalue[i] = htonl (inputvalue[i]);

  }

  return retvalue;
}
