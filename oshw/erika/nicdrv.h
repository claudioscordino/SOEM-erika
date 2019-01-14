/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

/** \file
 * \brief
 * Headerfile for nicdrv.c
 */

#ifndef _nicdrvh_
#define _nicdrvh_

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
   	/** socket connection used */
   	int         *sock;
   	/** tx buffer */
   	ec_bufT     (*txbuf)[EC_MAXBUF];
   	/** tx buffer lengths */
   	int         (*txbuflength)[EC_MAXBUF];
   	/** temporary receive buffer */
   	ec_bufT     *tempbuf;
   	/** rx buffers */
   	ec_bufT     (*rxbuf)[EC_MAXBUF];
   	/** rx buffer status fields */
   	int         (*rxbufstat)[EC_MAXBUF];
   	/** received MAC source address (middle word) */
   	int         (*rxsa)[EC_MAXBUF];
} ec_stackT;

/** pointer structure to buffers for redundant port */
typedef struct
{
   	ec_stackT   stack;
   	int         sockhandle;
   	/** rx buffers */
   	ec_bufT rxbuf[EC_MAXBUF];
   	/** rx buffer status */
   	int rxbufstat[EC_MAXBUF];
   	/** rx MAC source address */
   	int rxsa[EC_MAXBUF];
   	/** temporary rx buffer */
   	ec_bufT tempinbuf;
} ecx_redportt;

/** pointer structure to buffers, vars and mutexes for port instantiation */
typedef struct
{
   	ec_stackT   stack;
   	int         sockhandle;
   	/** rx buffers */
   	ec_bufT rxbuf[EC_MAXBUF];
   	/** rx buffer status */
   	int rxbufstat[EC_MAXBUF];
   	/** rx MAC source address */
   	int rxsa[EC_MAXBUF];
   	/** temporary rx buffer */
   	ec_bufT tempinbuf;
   	/** temporary rx buffer status */
   	int tempinbufs;
   	/** transmit buffers */
   	ec_bufT txbuf[EC_MAXBUF];
   	/** transmit buffer lenghts */
   	int txbuflength[EC_MAXBUF];
   	/** temporary tx buffer */
   	ec_bufT txbuf2;
   	/** temporary tx buffer length */
   	int txbuflength2;
   	/** last used frame index */
   	int lastidx;
   	/** current redundancy state */
   	int redstate;
   	/** pointer to redundancy port and buffers */
   	ecx_redportt *redport;

	/** Device id in the device pool */
	int dev_id;

	// TODO: add mutex support
} ecx_portt;

extern const uint16 priMAC[3];
extern const uint16 secMAC[3];

extern ecx_portt     ecx_port;
extern ecx_redportt  ecx_redport;

void ec_setupheader(void *p);
int ecx_setupnic(ecx_portt *port, const char *ifname, int secondary);
int ecx_closenic(ecx_portt *port);
void ecx_setbufstat(ecx_portt *port, int idx, int bufstat);
int ecx_getindex(ecx_portt *port);
int ecx_outframe(ecx_portt *port, int idx, int sock);
int ecx_outframe_red(ecx_portt *port, int idx);
int ecx_waitinframe(ecx_portt *port, int idx, int timeout);
int ecx_srconfirm(ecx_portt *port, int idx,int timeout);

int ecx_inframe(ecx_portt *port, int idx, int stacknumber);

#ifdef __cplusplus
}
#endif

#endif
