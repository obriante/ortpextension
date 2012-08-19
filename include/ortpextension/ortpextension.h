/*
 * ortpextension.h
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

/** \mainpage ortpextension API documentation
 *
 * \section Init Initializing ortpextension
 *
 * see ortpextension.h documentation.
 *
 * \section RtpSession RtpSession Replacement
 *
 * see the rtpsession_extension.h documentation.
 *
 * \section RtpExtension Rtp Extension Object:
 *
 * see the rtp_extension.h documentation.
 *
 * \section ortpextension Examples Tests:
 *
 * - rtprecv.c Show how to receive a single RTP stream with a generic Extension.
 * - rtpsend.c Show how to send a single RTP stream with a generic Extension.
 *
 *
 * <H2>README</H2>
 *
 * @verbinclude README
 *
 */

/**
 * @page ortpextension_readme README
 * @verbinclude README
 */

/**
 * @page ortpextension_install INSTALL
 * @verbinclude INSTALL
 */

/**
 * @page ortpextension_license COPYING
 * @verbinclude COPYING
 */

/**
 * @page ortpextension_changelog ChangeLog
 * @verbinclude ChangeLog
 */

/**
 * \file ortpextension.h
 * \brief The Main Header to Import
 *
 * This Header File Contain All library Imports to work with RTP Extension.
 **/

#ifndef ORTPEXTENSION_H_
#define ORTPEXTENSION_H_

#include <ortpextension/rtp_extension.h>
#include <ortpextension/rtpsession_extension.h>

#endif /* ORTPEXTENSION_H_ */
