#include <rpc/rpc.h>
#include <sys/time.h>
#include "db.h"
#define NAME_LEN   80
#define SSN_LEN    11
#define GRADE_LEN  1
#define RECORD_LEN 100
#define MAX_RECORDS 10

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

dbrecord *
get_by_name_2(argp, clnt)
	char **argp;
	CLIENT *clnt;
{
	static dbrecord res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, GET_BY_NAME, xdr_wrapstring, argp, xdr_dbrecord, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


dbrecord *
get_by_ssn_2(argp, clnt)
	char **argp;
	CLIENT *clnt;
{
	static dbrecord res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, GET_BY_SSN, xdr_wrapstring, argp, xdr_dbrecord, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


dbrecord *
change_grade_by_name_2(argp, clnt)
	dbrecord *argp;
	CLIENT *clnt;
{
	static dbrecord res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, CHANGE_GRADE_BY_NAME, xdr_dbrecord, argp, xdr_dbrecord, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}


dbrecord *
change_grade_by_ssn_2(argp, clnt)
	dbrecord *argp;
	CLIENT *clnt;
{
	static dbrecord res;

	bzero((char *)&res, sizeof(res));
	if (clnt_call(clnt, CHANGE_GRADE_BY_SSN, xdr_dbrecord, argp, xdr_dbrecord, &res, TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&res);
}

