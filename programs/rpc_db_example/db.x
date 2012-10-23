/***   db.x - RPC specification file 						8/25/92	***/

/*   From this file, rpcgen will generate the following:  */

/*	 the client stub	db_svc.c
     the server stub	db_clnt.c
     the xdr routines	db_xdr.c
     the header file	db.h	*/
/*--------------------------------------------------------------------*/	 

/*  '%' tells the compiler not to try to interpret the line, 
    just to pass it on to the header file                             */

%#define NAME_LEN   80
%#define SSN_LEN    11
%#define GRADE_LEN  1
%#define RECORD_LEN 100
%#define MAX_RECORDS 10


/* The student database, students.db contains dbrecords. 
   In our program, each of the server procedures will return a dbrecord  */
   
struct dbrecord {
  string Name<NAME_LEN>;	
  string SSN<SSN_LEN>;
  string Grade<GRADE_LEN>;
};

/*  The program definition  */
program DBPROG { 
	version DBVER {
		dbrecord GET_BY_NAME(string) = 1;            /* procedure 1 */
		dbrecord GET_BY_SSN(string) = 2;             /* procedure 2 */
		dbrecord CHANGE_GRADE_BY_NAME(dbrecord) = 3; /* procedure 3 */
		dbrecord CHANGE_GRADE_BY_SSN(dbrecord) = 4;  /* procedure 4 */
	} = 2;                                         /* version number */
} = 0x20000001;                                  /* program number */ 

/* Note:
  Sun considers program numbers 0x200100000-0x3FFFFFFFF as user-defined,
  but NeXT uses 0x200100000-0x200199999 */
