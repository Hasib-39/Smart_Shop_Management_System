#pragma once


#include <stdio.h>
#include <stdlib.h>

void intelligent_close(FILE* fp) {

  if (fp != NULL) {
    fclose(fp);
  }
}


void filePrinter(FILE* fp) {
  char c;
  
  // move the file pointer to the beginning of the file
  // rewind(fp);
  
  // read each character from the file and print it to the terminal
  while ((c = fgetc(fp)) != EOF) {
    putchar(c);
  }
  
  // print a newline character at the end of the file
  putchar('\n');
}

int fileChecker(FILE* fp) {
    if (fp == NULL) {
        fprintf(stderr, "Error: could not open file.\n");
        return 1;
    }
    return 0;
}