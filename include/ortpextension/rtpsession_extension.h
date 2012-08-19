/*
 * rtpsession_extension.h
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
 * \file rtpsession_extension.h
 * \brief Replace oRTP Function
 *
 * Replace The oRTP Function to Send and Receive RTP Packet With Header Extension
 **/

#ifndef RTP_SESSION_EXTENSION_H_
#define RTP_SESSION_EXTENSION_H_

#include <ortpextension/rtp_extension.h>
#include <ortp/ortp.h>
#include <stdbool.h>



#ifdef __cplusplus
extern "C" {
#endif

/**
 * To set Extension Flag into the RTP Header
 * @param mp a mblk_t Object
 * @param value The Flag Value
 **/
#define rtp_set_extbit(mp,value)		((rtp_header_t*)((mp)->b_rptr))->extbit=(value)

extern	void rtp_header_init_from_session_with_extension(rtp_header_t *, RtpSession *);
extern	int rtp_session_send_with_ts_with_extension(RtpSession *, const uint8_t *, int, uint32_t, RtpExtension_t *);
extern	mblk_t * rtp_session_create_packet_with_extension(RtpSession *, int, const uint8_t *, int, RtpExtension_t*);
extern	mblk_t * rtp_session_create_packet_with_data_with_extension(RtpSession *, uint8_t *, int, void (*freefn)(void*), RtpExtension_t *);

extern	int rtp_get_payload_with_extension(mblk_t *, unsigned char **, RtpExtension_t *);
extern	int rtp_session_recv_with_ts_with_extension(RtpSession *, uint8_t *, int, uint32_t, int *, RtpExtension_t *);

extern	void set_jitter_buffer(RtpSession *, int, bool, int);

#ifdef __cplusplus
}
#endif

#endif /* RTP_SESSION_EXTENSION_H_ */
