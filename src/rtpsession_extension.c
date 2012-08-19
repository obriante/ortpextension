/*
 * rtpsession_extension.c
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

#include <ortpextension/rtpsession_extension.h>
#include "extension_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <ortp/ortp.h>


#ifdef __cplusplus
extern "C"
{
#endif

/**
 *	Send a rtp datagram to the destination set by rtp_session_set_remote_addr() containing
 *	the data from buffer with timestamp userts. This is a high level function that uses
 *	rtp_session_create_packet() and rtp_session_sendm_with_ts() to send the data.
 *
 *@param session Rtp Session.
 *@param buffer a buffer containing the data to be sent in a rtp packet.
 *@param len the length of the data buffer, in bytes.
 *@param userts	the timestamp of the data to be sent. Refer to the rfc to know what it is.
 *@param extension RTP Extension Object
 *
 *@return the number of bytes sent over the network.
 **/
  int
    rtp_session_send_with_ts_with_extension (RtpSession * session,
					     const uint8_t * buffer,
					     int len, uint32_t userts,
					     RtpExtension_t * extension)
  {
    mblk_t *m;
    int err;

#ifdef USE_SENDMSG
      m =
      rtp_session_create_packet_with_data_with_extension (session,
							  (uint8_t *) buffer,
							  len, NULL,
							  extension);
#else
      m =
      rtp_session_create_packet_with_extension (session,
						RTP_FIXED_HEADER_SIZE,
						(uint8_t *) buffer, len,
						extension);
#endif
      err = rtp_session_sendm_with_ts (session, m, userts);

      return err;
  }

  void
    rtp_header_init_from_session_with_extension (rtp_header_t * rtp,
						 RtpSession * session)
  {
    rtp->version = 2;
    rtp->padbit = 0;
    rtp->extbit = 1;
    rtp->markbit = 0;
    rtp->cc = 0;
    rtp->paytype = session->snd.pt;
    rtp->ssrc = session->snd.ssrc;
    rtp->timestamp = 0;		/* set later, when packet is sended */
    /* set a seq number */
    rtp->seq_number = session->rtp.snd_seq;
  }

/**
 *	Allocates a new rtp packet. In the header, ssrc and payload_type according to the session's
 *	context. Timestamp is not set, it will be set when the packet is going to be
 *	sent with rtp_session_sendm_with_ts(). Sequence number is initalized to previous sequence number sent + 1
 *	If payload_size is zero, thus an empty packet (just a RTP header) is returned.
 *
 *@param session a rtp session.
 *@param header_size the rtp header size. For standart size (without extensions), it is RTP_FIXED_HEADER_SIZE
 *@param payload data to be copied into the rtp packet.
 *@param payload_size size of data carried by the rtp packet.
 *@param extension Rtp Extension Object
 *
 *@return a rtp packet in a mblk_t (message block) structure.
 **/
  mblk_t *rtp_session_create_packet_with_extension (RtpSession * session,
						    int header_size,
						    const uint8_t * payload,
						    int payload_size,
						    RtpExtension_t *
						    extension)
  {

    mblk_t *mp;
    uint32_t *rtp_extension =
      (uint32_t *) rtp_extension_to_uint32_t (extension);
    uint8_t *rtp_ext = (uint8_t *) bytes_inverter_to_packet (rtp_extension,
							     extension->length
							     + 1);

    int extension_size = (extension->length + 1) * sizeof (uint32_t);
    int msglen = header_size + extension_size + payload_size;
    rtp_header_t *rtp;

    mp = allocb (msglen, BPRI_MED);
    rtp = (rtp_header_t *) mp->b_rptr;
    rtp_header_init_from_session_with_extension (rtp, session);
    /*copy the payload, if any */
    mp->b_wptr += header_size;

    memcpy (mp->b_wptr, rtp_ext, extension_size);
    mp->b_wptr += extension_size;

    if (payload_size) {
      memcpy (mp->b_wptr, payload, payload_size);
      mp->b_wptr += payload_size;
    }
    return mp;
  }

/**
 *	Creates a new rtp packet using the given payload buffer (no copy). The header will be allocated separetely.
 *  In the header, ssrc and payload_type according to the session's
 *	context. Timestamp and seq number are not set, there will be set when the packet is going to be
 *	sent with rtp_session_sendm_with_ts().
 *	oRTP will send this packet using libc's sendmsg() (if this function is availlable!) so that there will be no
 *	packet concatenation involving copies to be done in user-space.
 *  @param freefn can be NULL, in that case payload will be kept untouched.
 *
 * @param session a rtp session.
 * @param payload the data to be sent with this packet
 * @param payload_size size of data
 * @param freefn a function that will be called when the payload buffer is no more needed.
 * @param extension Rtp Extension Object
 *
 * @return a rtp packet in a mblk_t (message block) structure.
 */
  mblk_t *rtp_session_create_packet_with_data_with_extension (RtpSession *
							      session,
							      uint8_t *
							      payload,
							      int
							      payload_size,
							      void (*freefn)
							       
							      (void *),
							      RtpExtension_t *
							      extension)
  {
    mblk_t *mp, *mpayload;

    uint8_t *rtp_ext = (uint8_t *) rtp_extension_to_uint32_t (extension);
    //uint8_t *rtp_ext=(uint8_t *)bits_inverter(rtp_extension,extension->length);

    int extension_size = (extension->length + 1) * sizeof (uint32_t);
    int header_size = RTP_FIXED_HEADER_SIZE + extension_size;	/* revisit when support for csrc is done */
    rtp_header_t *rtp;

    mp = allocb (header_size, BPRI_MED);
    rtp = (rtp_header_t *) mp->b_rptr;
    rtp_header_init_from_session_with_extension (rtp, session);
    mp->b_wptr += header_size;

    memcpy (mp->b_wptr, rtp_ext, extension_size);
    mp->b_wptr += extension_size;

    /* create a mblk_t around the user supplied payload buffer */
    mpayload = esballoc (payload, payload_size, BPRI_MED, freefn);
    mpayload->b_wptr += payload_size;
    /* link it with the header */
    mp->b_cont = mpayload;
    return mp;
  }

/**
 * Get a pointer to the beginning of the payload data of the RTP packet.
 * @param packet a RTP packet represented as a mblk_t
 * @param start a pointer to the beginning of the payload data, pointing inside the packet.
 * @param rtp_extension Rtp Extension object
 *
 * @return the length of the payload data.
 */
  int
    rtp_get_payload_with_extension (mblk_t * packet, unsigned char **start,
				    RtpExtension_t * rtp_extension)
  {

    unsigned char *tmp;
    int header_len = RTP_FIXED_HEADER_SIZE + (rtp_get_cc (packet) * 4);
    tmp = packet->b_rptr + header_len;
    if (tmp > packet->b_wptr) {
      if (packet->b_cont != NULL) {
	tmp = packet->b_cont->b_rptr
	  + (header_len - (packet->b_wptr - packet->b_rptr));
	if (tmp <= packet->b_cont->b_wptr) {
	  *start = tmp;
	  return packet->b_cont->b_wptr - tmp;
	}
      }
      ortp_warning ("Invalid RTP packet");
      return -1;
    }
    if (rtp_get_extbit (packet)) {

      int extsize = rtp_get_extheader (packet, NULL, NULL);

      if (extsize >= 0) {
	uint8_t *words;
	rtp_get_extheader (packet, &rtp_extension->type, &words);
	rtp_extension->length = extsize / (sizeof (uint32_t));
	words = (uint8_t *) bytes_inverter_from_packet ((uint32_t *) words,
							rtp_extension->length);
	rtp_extension->extension = (uint32_t *) words;

	tmp += 4 + extsize;
      }
    }
    *start = tmp;

    return packet->b_wptr - tmp;
  }

/**
 *	This function internally calls rtp_session_recvm_with_ts() to get a rtp packet. The content
 *	of this packet is then copied into the user supplied buffer in an intelligent manner:
 *	the function takes care of the size of the supplied buffer and the timestamp given in
 *	argument. Using this function it is possible to read continous audio data (e.g. pcma,pcmu...)
 *	with for example a standart buffer of size of 160 with timestamp incrementing by 160 while the incoming
 *	stream has a different packet size.
 *
 * Returns: if a packet was availlable with the corresponding timestamp supplied in argument
 *	then the number of bytes written in the user supplied buffer is returned. If no packets
 *	are availlable, either because the sender has not started to send the stream, or either
 *	because silence packet are not transmitted, or either because the packet was lost during
 *	network transport, then the function returns zero.
 * @param *session a rtp session.
 * @param *buffer a user supplied buffer to write the data.
 * @param len the length in bytes of the user supplied buffer.
 * @param ts the timestamp wanted.
 * @param *have_more the address of an integer to indicate if more data is availlable for the given timestamp.
 * @param *rtp_extension Rtp Extension Object
 *
 **/
  int
    rtp_session_recv_with_ts_with_extension (RtpSession * session,
					     uint8_t * buffer, int len,
					     uint32_t ts, int *have_more,
					     RtpExtension_t * rtp_extension)
  {
    mblk_t *mp = NULL;
    int plen, blen = 0;
    *have_more = 0;

    while (1) {
      if (session->pending) {
	mp = session->pending;
	session->pending = NULL;
      }
      else {
	mp = rtp_session_recvm_with_ts (session, ts);
	if (mp != NULL)
	  rtp_get_payload_with_extension (mp, &mp->b_rptr, rtp_extension);
      }
      if (mp) {
	plen = mp->b_wptr - mp->b_rptr;
	if (plen <= len) {
	  memcpy (buffer, mp->b_rptr, plen);
	  buffer += plen;
	  blen += plen;
	  len -= plen;
	  freemsg (mp);
	  mp = NULL;
	}
	else {
	  memcpy (buffer, mp->b_rptr, len);
	  mp->b_rptr += len;
	  buffer += len;
	  blen += len;
	  len = 0;
	  session->pending = mp;
	  *have_more = 1;
	  break;
	}
      }
      else
	break;
    }

    return blen;
  }

/**
 * Set the Jitter Buffer length
 *
 * @param *session  a rtp session
 * @param nomsize the nominal jitter size in millisec
 * @param adaptative for adaptative jitter
 * @param max_pkts the max numbers of packets to be stored into the buffer
 */
  void
    set_jitter_buffer (RtpSession * session, int nomsize, bool adaptative,
		       int max_pkts)
  {

    PayloadType *payload = NULL;
    if (session->rcv.pt != -1) {
      payload = rtp_profile_get_payload (session->rcv.profile,
					 session->rcv.pt);
    }				/*else not set yet */
    jitter_control_init (&session->rtp.jittctl, nomsize, payload);

    JBParameters jbp;
    jbp.min_size = session->rtp.jittctl.jitt_comp_ts;
    jbp.nom_size = session->rtp.jittctl.jitt_comp_ts;
    jbp.max_size = -1;
    jbp.max_packets = max_pkts;	/* maximum number of packet allowed to be queued */
    jbp.adaptive = adaptative;
    rtp_session_set_jitter_buffer_params (session, &jbp);

  }

#ifdef __cplusplus
}
#endif
