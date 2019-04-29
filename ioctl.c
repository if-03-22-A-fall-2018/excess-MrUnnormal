// textfile form: https://sample-videos.com/download-sample-text-file.php
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  struct winsize ws;
	if (ioctl(0,TIOCGWINSZ,&ws)!=0)
  {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
  FILE* fd = fopen("text.txt", "r");
  if(fd != 0)
  {
    int end_of_file = 10;
    do
    {
      for(int o = 0; o < ws.ws_row - 2; o++)
      {
        for(int i = 0; i < ws.ws_col; i++)
        {
          int output = fgetc(fd);
          if(output != -1)
          {
            printf("%c", output);
          }
          else
          {
              end_of_file = -10;
          }
        }
        if(end_of_file == 10)
        { printf("\n"); }
      }
      getchar();
    } while(end_of_file == 10);


    /*char* output;
    if(fgets(output, 2, fd) == 0)
    {

    }
    else
    {
      printf("%s", output);
    }*/
  }
  else
  {
      printf("ERROR\n");
  }
  return 0;
}
