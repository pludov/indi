/*

  Copyright (c) 2002 Finger Lakes Instrumentation (FLI), L.L.C.
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

        Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

        Redistributions in binary form must reproduce the above
        copyright notice, this list of conditions and the following
        disclaimer in the documentation and/or other materials
        provided with the distribution.

        Neither the name of Finger Lakes Instrumentation (FLI), LLC
        nor the names of its contributors may be used to endorse or
        promote products derived from this software without specific
        prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
  REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.

  ======================================================================

  Finger Lakes Instrumentation, L.L.C. (FLI)
  web: http://www.fli-cam.com
  email: support@fli-cam.com

*/

#ifndef _LIBFLI_USB_H_
#define _LIBFLI_USB_H_

#if defined(__linux__)

#define unix_bulkwrite		linux_bulkwrite
#define unix_bulkread		linux_bulkread
#define unix_usb_connect	linux_usb_connect
#define unix_usb_disconnect	linux_usb_disconnect
#define unix_bulktransfer	linux_bulktransfer

#elif defined(__FreeBSD__) || defined(__NetBSD__)

#define unix_bulkwrite		bsd_bulkwrite
#define unix_bulkread		bsd_bulkread
#define unix_usb_connect	bsd_usb_connect
#define unix_usb_disconnect	bsd_usb_disconnect
#define unix_bulktransfer	bsd_bulktransfer

#else
#error "Unknown system"
#endif

long unix_bulkwrite(flidev_t dev, void *buf, long *wlen);
long unix_bulkread(flidev_t dev, void *buf, long *rlen);
long unix_usbio(flidev_t dev, void *buf, long *wlen, long *rlen);
long unix_usb_connect(flidev_t dev, fli_unixio_t *io, char *name);
long unix_usb_disconnect(flidev_t dev);
long unix_bulktransfer(flidev_t dev, int ep, void *buf, long *len);

#define usb_bulktransfer unix_bulktransfer /* XXX */

#endif /* _LIBFLI_USB_H_ */
