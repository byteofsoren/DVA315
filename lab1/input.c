#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

void *input(const char *prompt){
  int bufferSize = 10;
  char *buffer;
  int running = 1;
  int counter = 1;
  buffer = NULL;
  printf("%s", prompt );
  buffer = (char *) calloc(bufferSize, sizeof(char));
  fgets(buffer, bufferSize, stdin);
  bufferSize = strlen(buffer);
  while (running) {
    if (buffer[bufferSize - 1] == '\n') {
      buffer[bufferSize - 1] = '\0';
      return buffer;
    }else if (buffer[bufferSize - 1] == '\0'){
      return buffer;/**/
    }else{
      char junk[4];
      fgets(junk, 4, stdin);
      buffer = (char *) realloc(buffer, counter * bufferSize * sizeof(char));
      strcat(buffer, junk);
      bufferSize = strlen(buffer);
      counter++;

    }
  }
  return buffer;
}
