/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "repair.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif
#include "repair_structures.h"

static void
repairprog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		struct queue_car_param queue_car_1_arg;
		struct repair_car_param repair_car_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case QUEUE_CAR:
		_xdr_argument = (xdrproc_t) xdr_queue_car_param;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) queue_car_1_svc;
		break;

	case REPAIR_CAR:
		_xdr_argument = (xdrproc_t) xdr_repair_car_param;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) repair_car_1_svc;
		break;

	case CARS_IN_GARAGE:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_cars_in_garage_return;
		local = (char *(*)(char *, struct svc_req *)) cars_in_garage_1_svc;
		break;

	case WORKTIME_LEFT:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) worktime_left_1_svc;
		break;

	case CLEAR_GARAGE:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_void;
		local = (char *(*)(char *, struct svc_req *)) clear_garage_1_svc;
		break;

	case GARAGE_EMPTY:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_int;
		local = (char *(*)(char *, struct svc_req *)) garage_empty_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (REPAIRPROG, REPAIR);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, REPAIRPROG, REPAIR, repairprog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (REPAIRPROG, REPAIR, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, REPAIRPROG, REPAIR, repairprog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (REPAIRPROG, REPAIR, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
