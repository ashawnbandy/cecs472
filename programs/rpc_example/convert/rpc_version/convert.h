/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CONVERT_H_RPCGEN
#define _CONVERT_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#include <sys/time.h>

#define CONVERTPROG 0x20000064
#define CONVERTVER 1

#if defined(__STDC__) || defined(__cplusplus)
#define UPPER_IT 1
extern  char ** upper_it_1(char **, CLIENT *);
extern  char ** upper_it_1_svc(char **, struct svc_req *);
#define LOWER_IT 2
extern  char ** lower_it_1(char **, CLIENT *);
extern  char ** lower_it_1_svc(char **, struct svc_req *);
extern int convertprog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define UPPER_IT 1
extern  char ** upper_it_1();
extern  char ** upper_it_1_svc();
#define LOWER_IT 2
extern  char ** lower_it_1();
extern  char ** lower_it_1_svc();
extern int convertprog_1_freeresult ();
#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CONVERT_H_RPCGEN */
