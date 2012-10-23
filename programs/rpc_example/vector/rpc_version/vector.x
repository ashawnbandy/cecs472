/***   vector.x - RPC specification file                   ***/

/*   From this file, rpcgen will generate the following:  */

/*   the client stub   vector_svc.c
     the server stub   vector_clnt.c
     the xdr routines  vector_xdr.c
     the header file   vector.h  */
/*---------------------------------------------------------------*/   
/*  '%' tells the compiler not to try to interpret the line, 
    just to pass it on to the header file                        */
%#include <sys/time.h>

/* The structures used by the actual rpc calls.
   We pass two vectors and get one back. 
   For illustration purposes we pass these using arrays */

struct pass {
  int data[4];
  };

struct answer {
  int data[2];
  };

/*  The program definition  */
program VECTORPROG { 
  version VECTORVER {
    answer ADD(pass) = 1;  /* procedure 1 */
  } = 1;                   /* version number */
} = 0x20000064;            /* program number */ 
