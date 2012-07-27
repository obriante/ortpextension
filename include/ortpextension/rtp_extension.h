/*
 * rtp_extension.h
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

/**
 * \file rtp_extension.h
 * \brief Implement RTP Extension
 *
 * This Header File Implement RTP Extension Structure
**/

#ifndef RTP_EXTENSION_H_
#define RTP_EXTENSION_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>


#ifdef __cplusplus
extern "C"{
#endif

/**
 * \brief Structure that modelize The Complete RTP Extension
 **/
typedef struct Rtp_Header_Extension {
	uint16_t type; /**< Extension Type */
	uint32_t *extension ; /**< Extension Words Array */
	uint16_t length; /**< Number Length Of Extension Words */
}RtpExtension_t; /** Rtp_Header_Extension */

void *init_rtp_extension();
void *init_rtp_extension_with_length(uint16_t);
void uninit_rtp_extension(RtpExtension_t*);

void set_extension(RtpExtension_t *, uint16_t, uint32_t*, uint16_t);
void* rtp_extension_to_uint32_t(RtpExtension_t*);

void print_rtp_extension(RtpExtension_t*);

#ifdef __cplusplus
}
#endif


#endif /*  RTP_EXTENSION_H_ */
