#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned char msg [] = {
    0xAA, 0xAA, 0xBB, 0xBB,     // magic number
    0x0,                    // power off time A
    0x0,                    // power off time B
    0x0, 0x0, 0x0, 0x0,     // power on cycle A
    0x0, 0x0, 0x0, 0x0,     // power on cycle B
    0x0                     // checksum
};

void overwriteChecksum();

int main(int argc, char *argv[]) {

//  if (argc <= 2) {
//    return  -1;
//  }

//  printf("%s, %s\n", argv[1], argv[2]);
//  int t_poweroff = atoi(argv[1]);
//  int t_poweron  = atoi(argv[2]);

//  uint8_t poweroff = (uint8_t)t_poweroff;
//  uint32_t poweron = (uint32_t)t_poweron;

//  msg[4] = msg[5] = poweroff;

  msg[9] = msg[13] = (poweron & (0xFF000000u)) >> 24;
  msg[8] = msg[12] = (poweron & (0x00FF0000u)) >> 16;
  msg[7] = msg[11] = (poweron & (0x0000FF00u)) >> 8;
  msg[6] = msg[10] = (poweron & (0x000000FFu));

  overwriteChecksum();

  FILE *fptr = fopen("serial_wrt", "wb");  // create and/or overwrite
  if (!fptr) {
    printf("Error in creating file. Aborting.\n");
    return -2;
  }
  fwrite(&msg, sizeof(msg), 1, fptr);
  fclose(fptr);

  system("cat serial_wrt > /dev/ttysWK3");
}

void overwriteChecksum() {
  uint8_t check = 0;
  for (int i = 0; i < 14; i++) {
    check += msg[i];
  }
  msg[14] = check;
}
