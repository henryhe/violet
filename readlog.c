#include <stdio.h>
#include <time.h>
#include <malloc.h>
void main(int argc,char * argv[]){
   time_t rawtime_start;
   struct tm* timeinfo;
   time(&rawtime_start);
   timeinfo = localtime(&rawtime_start);
   printf("read log start:%s",asctime(timeinfo));
   long int line_num = 0;
   char *line = (char *) malloc(1000);
   while(fgets(line,1024,stdin)!=NULL){
        line_num++;
	printf("%s",line);
   }   
   time_t rawtime_end;
   time(&rawtime_end);
   timeinfo = localtime(&rawtime_end);
   printf("read log end:%s",asctime(timeinfo));

   printf("test for git pull");
}
