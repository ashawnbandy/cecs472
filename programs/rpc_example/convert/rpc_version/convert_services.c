#include <ctype.h>  /* toupper, tolower*/
/* Convert a sentence to upper or lower case */
void upper_it(char *sentence){
  char *letter = sentence;
  while (*letter) {
    *letter = toupper(*letter);
    letter++;
  }
}
void lower_it(char *sentence){
  char *letter = sentence;
  while (*letter) {
    *letter = tolower(*letter);
    letter++;
  }
}
