#include <stdio.h>
#include <rpc/rpc.h>
#include "db.h"
#define NAME_LEN   80
#define SSN_LEN    11
#define GRADE_LEN  1
#define RECORD_LEN 100
#define MAX_RECORDS 10

static void dbprog_2();

main()
{
	SVCXPRT *transp;

	(void)pmap_unset(DBPROG, DBVER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create udp service.\n");
		exit(1);
	}
	if (!svc_register(transp, DBPROG, DBVER, dbprog_2, IPPROTO_UDP)) {
		(void)fprintf(stderr, "unable to register (DBPROG, DBVER, udp).\n");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		(void)fprintf(stderr, "cannot create tcp service.\n");
		exit(1);
	}
	if (!svc_register(transp, DBPROG, DBVER, dbprog_2, IPPROTO_TCP)) {
		(void)fprintf(stderr, "unable to register (DBPROG, DBVER, tcp).\n");
		exit(1);
	}
	svc_run();
	(void)fprintf(stderr, "svc_run returned\n");
	exit(1);
}

static void
dbprog_2(rqstp, transp)
	struct svc_req *rqstp;
	SVCXPRT *transp;
{
	union {
		char *get_by_name_2_arg;
		char *get_by_ssn_2_arg;
		dbrecord change_grade_by_name_2_arg;
		dbrecord change_grade_by_ssn_2_arg;
	} argument;
	char *result;
	bool_t (*xdr_argument)(), (*xdr_result)();
	char *(*local)();

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void)svc_sendreply(transp, xdr_void, (char *)NULL);
		return;

	case GET_BY_NAME:
		xdr_argument = xdr_wrapstring;
		xdr_result = xdr_dbrecord;
		local = (char *(*)()) get_by_name_2;
		break;

	case GET_BY_SSN:
		xdr_argument = xdr_wrapstring;
		xdr_result = xdr_dbrecord;
		local = (char *(*)()) get_by_ssn_2;
		break;

	case CHANGE_GRADE_BY_NAME:
		xdr_argument = xdr_dbrecord;
		xdr_result = xdr_dbrecord;
		local = (char *(*)()) change_grade_by_name_2;
		break;

	case CHANGE_GRADE_BY_SSN:
		xdr_argument = xdr_dbrecord;
		xdr_result = xdr_dbrecord;
		local = (char *(*)()) change_grade_by_ssn_2;
		break;

	default:
		svcerr_noproc(transp);
		return;
	}
	bzero((char *)&argument, sizeof(argument));
	if (!svc_getargs(transp, xdr_argument, &argument)) {
		svcerr_decode(transp);
		return;
	}
	result = (*local)(&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, xdr_result, result)) {
		svcerr_systemerr(transp);
	}
	if (!svc_freeargs(transp, xdr_argument, &argument)) {
		(void)fprintf(stderr, "unable to free arguments\n");
		exit(1);
	}
}

