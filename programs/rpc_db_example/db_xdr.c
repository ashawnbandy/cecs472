#include <rpc/rpc.h>
#include "db.h"
#define NAME_LEN   80
#define SSN_LEN    11
#define GRADE_LEN  1
#define RECORD_LEN 100
#define MAX_RECORDS 10


bool_t
xdr_dbrecord(xdrs, objp)
	XDR *xdrs;
	dbrecord *objp;
{
	if (!xdr_string(xdrs, &objp->Name, NAME_LEN)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->SSN, SSN_LEN)) {
		return (FALSE);
	}
	if (!xdr_string(xdrs, &objp->Grade, GRADE_LEN)) {
		return (FALSE);
	}
	return (TRUE);
}


