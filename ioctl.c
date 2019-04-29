// textfile form: https://sample-videos.com/download-sample-text-file.php
#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
    bool end_of_file = false;
    long last_page_position;
    do
    {
      char input = getchar();
      if(input == 'b')
      {
        fseek(fd, last_page_position, SEEK_SET);
      }
      for(int o = 0; o < ws.ws_row - 2; o++)
      {
        for(int i = 0; i < ws.ws_col; i++)
        {
          last_page_position = ftell(fd);
          int output = fgetc(fd);
          if(output != -1)    // If end of file is reached
          {
            printf("%c", output);
          }
          else
          {
              end_of_file = true;
          }
        }
      }
      if(!end_of_file)
      { printf("To go forward press enter.\n"); }
    } while(!end_of_file);
  }
  else
  { printf("ERROR, File not found\n"); }
  fclose(fd);
  return 0;
}
