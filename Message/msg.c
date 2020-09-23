#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// returns 0 to represent false and 1 to represent true
int foo(char* line) {
   int state = 1; // 4 is the final state
   for (int i = 0; i < strlen(line); i++) {
        //printf("%c\n", line[i]);
        //printf("%d\n", state);
      if (state == 1 && line[i] == 'E') 
        state = 2;
      else if (state == 2 && (line[i] == '0' || line[i] == '1' || line[i] == '2')) 
        state = 3;
      else if (state == 3 && (line[i] == '0' || line[i] == '1' || line[i] == '2')) 
        state = 3;
      else if (state == 3 && (line[i] == 'F')) 
        state = 4;
      else
        return 0;
   }
   if (state == 4) return 1;
   return 0;
}

int eep(char* line) {
   int state = 1; // 4 is the final state
   for (int i = 0; i < strlen(line); i++) {
      if (state == 1 && line[i] == 'P') 
        state = 2;
      else if (state == 2 && line[i] == 'B') 
        state = 3;
      else if (state == 3 && line[i] == 'C') 
        state = 2;
      else
        return 0;
   }
   if (state == 2) return 1;
   return 0;
}

int op(char* line) {
   int state = 1; // 4 is the final state
   for (int i = 0; i < strlen(line); i++) {
      if (state == 1 && line[i] == 'Q') 
        state = 2;
      else if (state == 2 && line[i] == '6') 
        state = 2;
      else if (state == 2 && line[i] == '7') 
        state = 3;
      else if (state == 3 && line[i] == '6') 
        state = 3;
      else if (state == 3 && line[i] == '7') 
        state = 2;
      else
        return 0;
   }
   if (state == 3) return 1;
   return 0;
}

int ork(char* line) {
   int state = 1; // 4 is the final state
   for (int i = 0; i < strlen(line); i++) {
     //printf("%c\n", line[i]);
     //printf("%d\n", state);
      if (state == 1 && line[i] == 'M') 
        state = 2;
         //Two digits
      else if (state == 2 && (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')) 
        state = 3;
      else if (state == 3 && (line[i] == '0' || line[i] == '1' || line[i] == '2' || line[i] == '3' || line[i] == '4' || line[i] == '5' || line[i] == '6' || line[i] == '7' || line[i] == '8' || line[i] == '9')) 
        state = 4;
        //Two digits
      else if (state == 4 && line[i] == 'P') 
        state = 5;
      else if (state == 5 && line[i] == 'B') 
        state = 6;
      else if (state == 6 && line[i] == 'C') 
        state = 5;
      else if (state == 4 && line[i] == 'E') 
        state = 7;
      else if (state == 7 && (line[i] == '0' || line[i] == '1' || line[i] == '2')) 
        state = 8;
      else if (state == 8 && (line[i] == '0' || line[i] == '1' || line[i] == '2')) 
        state = 8;
      else if (state == 8 && line[i] == 'F') 
        state = 9;
      else
        return 0;
      
   }
   if ((state == 5)||(state == 9)) return 1;
   return 0;
}

int checker(char* line){
  int isAccepted = 0;
  if (foo(line)) isAccepted = 1;
  else if (eep(line)) isAccepted = 1;
  else if (op(line)) isAccepted = 1;
  else if (ork(line)) isAccepted = 1;
  return isAccepted;
}

int main(int argc, char* argv[])
{
  
  FILE *input;

  input = stdin;

  if (argc > 1) {
    input = fopen(argv[1],"r");
    if (NULL == input) {
      printf("Unable to open '%s'\n", argv[1]);
      exit(EXIT_FAILURE);
    }
  }

  char line[256];

  while (fgets(line, 256, input)) {
      //printf("%s", line);
      line[strlen(line) - 1] = '\0';
      if (checker(line)) {
        printf("%s OK\n", line);
        fflush(stdout);
        //printf("%s OK\n", line);
      }
      else {
        printf("%s FAIL\n", line);
      }
  }
  if (argc == 1) {
    fclose(input);
  }
  return 0;
}
