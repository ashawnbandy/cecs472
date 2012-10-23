/* file: ssl_serv.c */
/* gcc ssl_serv.c -lssl */
/* DEBUG version, do not use this */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <openssl/ssl.h>
#include "passiveTCP.c"

#define pass "password"

int passwd_cb(char *buf, int num,
 int rwflag,void *userdata)
{
  if (num < strlen(pass)+1)
    return 0;
  strcpy(buf, pass);
  return strlen(pass);
};

int main(){
  int master, client, len; char message[80];
  int wn, rn, rslt;
  struct sockaddr_in my_addr, his_addr;
  SSL_METHOD* meth;
  SSL_CTX *ctx;
  SSL *ssl;
  master = passiveTCP("7654",5);
  len=sizeof(his_addr);
  /* get the connection to the client */
  client = accept(master, 
    (struct sockaddr *) &his_addr, &len);

  // Do the SSL stuff
  SSL_library_init();
  meth = SSLv23_method();
  ctx = SSL_CTX_new(meth);

  printf("c %x\n",ctx);
  SSL_CTX_use_certificate_chain_file(ctx,"server.pem"); // required
  SSL_CTX_set_default_passwd_cb(ctx,passwd_cb); // Avoids screen prompt
  printf("a %x\n",ctx);
  SSL_CTX_use_PrivateKey_file(ctx,"server.pem",SSL_FILETYPE_PEM);//required
  printf("b %x\n",ctx);

  ssl = SSL_new(ctx);
  SSL_set_fd(ssl,client);
  rslt = SSL_accept(ssl);
  printf("acc %d\n",rslt);

  rn = SSL_read(ssl,message,80);
  printf("%d read: %s\n",rn,message);
  strcpy(message,"Server replies");
  wn = SSL_write(ssl, message, 80); /* send reply */
  printf("%d\n",wn);
  SSL_free(ssl);
  close(client); close(master); return 1;
}
