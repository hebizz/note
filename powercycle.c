#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<stdint.h>
#include<sys/file.h>

#define SIZE 30


int main(int argc,char *argv[]){
  printf("argc is %d\n",argc);
  system("stty -F /dev/ttyS4 raw");
  system("stty -F /dev/ttyS4 -echo echoe -echok");
  if (argc == 3){
    unsigned char Buf[SIZE];
    unsigned char Rbuf[SIZE];
    uint8_t _timeoff;
    uint32_t _timeon;
    int middle,length,res,count;
    strcpy(Buf,"jxhead21powerconfig");
    middle = atoi(argv[1]);
    _timeoff = (uint8_t)middle; 
    printf("timeoff is %u\n",_timeoff);
    Buf[19] = _timeoff;
    Buf[20] = _timeoff;

    middle = atoi(argv[2]);
    _timeon = (uint32_t)middle;
    printf("timeon is %x\n",_timeon);

    Buf[21] = (_timeon & 0x000000FF);
    Buf[22] = (_timeon & 0x0000FF00) >> 8;
    Buf[23] = (_timeon & 0x00FF0000) >> 16;
    Buf[24] = (_timeon & 0xFF000000) >> 24;

    Buf[25] = Buf[21];
    Buf[26] = Buf[22];
    Buf[27] = Buf[23];
    Buf[28] = Buf[24];

    Buf[29] = 0x00;
    
    printf("Buf: %02x%02x%02x%02x\n",Buf[21], Buf[22], Buf[23], Buf[24]);
    printf("Buf: %02x%02x%02x%02x\n",Buf[25], Buf[26], Buf[27], Buf[28]);
   
    FILE *fp = fopen("/dev/ttyS4","wb");
    
    if (!fp){
      printf("fail open dev\n");
    }

    flock(fp->_fileno,LOCK_EX);  
    fwrite(Buf, 30, 1, fp);
    flock(fp->_fileno,LOCK_UN);
    fread(Rbuf,30, 1, fp );
    count = 0
    while (count <= 5) {
      if (strcmp(Rbuf,Buf) == 0) {
        print("ok");
        break;
      } else {
        fwrite(Buf, 30, 1, fp);
        count += 1
      }
    }
  }

  if (argc == 2){
    unsigned char Buf[SIZE];
    uint8_t _powermode;
    int middle,length;
    strcpy(Buf,"jxhead11powermode");
    middle = atoi(argv[1]);
    _powermode = (uint8_t)middle;
    printf("powermode is %u\n",_powermode);
    Buf[17] = _powermode;
    Buf[18] = _powermode;
   
    FILE *fp = fopen("/dev/ttyS4","wb");
   
    if (!fp){
      printf("fail open dev\n");
    }

    flock(fp->_fileno,LOCK_EX);
    fwrite(Buf, 30, 1, fp);
    flock(fp->_fileno,LOCK_UN);
  }  
  return 0;
}  
