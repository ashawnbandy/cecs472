/* Convert a sentence to upper or lower case */
/* ANSI C prototypes (may be omitted in
 *  older versions of C */
void upper_it(char *sentence);
void lower_it(char *sentence);
main() {
  char buffer[100]; /* holds the sentence */
  char whichway[5]; /* to upper or to lower */
  /* control-C to exit */
  for (;;) {
    printf("enter the string ");
    gets(buffer);
    printf("u) to upper, l) to lower? ");
    gets(whichway);
    switch (whichway[0]) {
      case 'u':
        upper_it(buffer);
        break;
      case 'l':
        lower_it(buffer);
        break;
      default:
        printf("unrecognized option\n");
    }
    printf("%s\n", buffer);
  }
}
