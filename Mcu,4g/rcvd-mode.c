#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
  char buffer[3];
  FILE *fptr = fopen("/dev/ttysWK3", "r");  // create and/or overwrite
  if (!fptr) {
    printf("Error in creating file. Aborting.\n");
    return -2;
  }
  int confirm[3] = {-1, -1, -1};
  while(!feof(fptr)) {
    for (int i = 0; i < 3; i++) {
      fgets(buffer, 3, fptr);
      //printf("%s", buffer);
      int tmp = atoi(buffer);
      confirm[i] = tmp; 
    }
    if(confirm[0]==confirm[1] && confirm[1]==confirm[2]) {
      FILE *optr = fopen("/components/mode", "w");
      if (!optr) {
        printf("Error in creating file. Aborting.\n");
        return -2;
      }
      fprintf(optr, "%d", confirm[0]); 
      fclose(optr);
    }
  }
  fclose(fptr);
}
