/* This program implements the user interface for the browser client. It also
 * has pieces of the browser server. The change directory and list directory
 * code should be carefully examined.
 * The trick is this client implements the commands directly, while you must
 * build a client that passes (most of) the commands to the server and gets
 * the answer back; and you must build the server.
 *
 * The list command prints the contents of the current directory to the screen 
 * It prints one directory entry per iteration of the loop. Each entry is
 * printed on a separate line. The trick here is that the ctime call puts
 * a newline (\n) at the end of the string it returns. If you want the
 * information about a directory entry to go to into a string you may
 * use sprintf. See get_port.c for a hint about how to do this. 
 * Your program should print the directory in that same format as this
 * program does (i.e., name date). 
 * Remember to read the homework assignment carefully !
 */
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
main () {
  DIR *dirp;
  struct dirent *dp;
  struct stat buf;
  char command[80];

  while (1) {
    printf(">");
    gets(command);
    switch (command[0]) {
      case 'l': 
        dirp = opendir(".");
        for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
          stat(dp->d_name, &buf);
          printf("%s\t%s",dp->d_name, ctime(&(buf.st_mtime)));
        } 
        closedir(dirp);
        break;
      case 'c':
        chdir(&command[2]);
        break;
      case 'p':
        /* you must implement this command from the manual entry */
        printf("read the manual entry for getcwd\n");
        break;
      case 'q':
        exit();
      default:
        printf("bad command\n");
        
    }
  }
}
