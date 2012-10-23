/***   convert.x - RPC specification file                   ***/

/*   From this file, rpcgen will generate the following:  */

/*   the client stub   convert_svc.c
     the server stub   convert_clnt.c
     the xdr routines  convert_xdr.c
     the header file   convert.h  */
/*---------------------------------------------------------------*/   
/*  '%' tells the compiler not to try to interpret the line, 
    just to pass it on to the header file                        */
%#include <sys/time.h>

/*  The program definition  */
program CONVERTPROG { 
  version CONVERTVER {
    string UPPER_IT(string) = 1;  /* procedure 1 */
    string LOWER_IT(string) = 2;  /* procedure 2 */
  } = 1;                          /* version number */
} = 0x20000064;                   /* program number */ 

/* Note:
  Sun considers program numbers 0x200100000-0x3FFFFFFFF 
  as user-defined, but NeXT uses 0x200100000-0x200199999 */
