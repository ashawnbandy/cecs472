/* ************************************************************* */
/* Print information about the remote host that we are connected to. 
 */
print_remote(local_socket)
int local_socket;
{
  struct sockaddr_in name_info;
  struct hostent *host_info;
  int name_length = sizeof(name_info);
  /* Get information about the peer (remote machine) connected to this
   * socket. The type cast from sockaddr_in to sockaddr is because 
   * getpeername handles all kinds of sockaddrs. */
  getpeername(local_socket, (struct sockaddr *) &name_info, &name_length);
  /* Get and print the host name. Note the cast on the name. Internet
   * addressing is actually the address of an unsigned long, but because
   * the gethostbyaddr is general purpose it expects a (char *) */
  host_info = gethostbyaddr( (char *) &name_info.sin_addr.s_addr,
        sizeof(name_info.sin_addr.s_addr),AF_INET);
  if (host_info == NULL)
    printf("print_remote: unable to get local host name\n");
  else 
    printf("Remote host, name: %s, ",host_info->h_name);
  /* Print the internet address in dot notation */
  printf("address: %s, ",inet_ntoa(name_info.sin_addr));
  /* Print the port the remote is using. The port is in network standard
   * order and must be converted to host order in order to print it. */
  printf("port: %d\n", ntohs(name_info.sin_port));
}
