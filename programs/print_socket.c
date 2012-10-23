/* ************************************************************* */
/* Print information about our socket. The port is usually what we are
 *  interested in. The local host should always be the machine we are
 *  running on, but we print it to be sure. 
 */
print_socket(local_socket)
int local_socket;
{
  struct sockaddr_in name_info;
  struct hostent *host_info;
  int name_length = sizeof(name_info);
  /* Get information about the our machine.
   * The type cast from sockaddr_in to sockaddr is because 
   * getsockname handles all kinds of sockaddrs. */
  getsockname(local_socket, (struct sockaddr *) &name_info, &name_length);
  /* Get and print the host name. Note the cast on the name. Internet
   * addressing is actually the address of an unsigned long, but because
   * the gethostbyaddr is general purpose it expects a (char *) */
  host_info = gethostbyaddr((char *) &name_info.sin_addr.s_addr,
        sizeof(name_info.sin_addr.s_addr),AF_INET);
  if (host_info == NULL)
    printf("print_socket: unable to get local host name\n");
  else
    printf("Local host, name: %s, ",host_info->h_name);
  /* Print the (our) internet address in dot notation */
  printf("address: %s, ",inet_ntoa(name_info.sin_addr));
  /* Print the port the local machine is using */
  /* Print the port the remote is using. The port is in network standard
   * order and must be converted to host order in order to print it. */
  printf("port: %d\n",ntohs(name_info.sin_port));
}
