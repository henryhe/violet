/**
*author hepan
*用于接受标准输入的日志，然后得到提交的数据，解析为各行都是有效数据的格式，格式如下
*基站（wifi）号  x坐标  y坐标 pt  时间
*/
#include "locate.h"  //同目录下，包含了所有需要的头文件和声明


//仅仅过滤掉不是提交数据的日志
BOOL isNeededRawLine(char* line){
  char* indicator = line;
  while( *indicator != '\0'){
    if(*indicator == '_' && *(indicator+1)=='x' && *(indicator+2)== '='){
      return TRUE; 
    }
    indicator++;
  }
  return FALSE;
}


void parseLine(char * line){



}

void main(int argc,char * argv[]){
   time_t rawtime_start;
   struct tm* timeinfo;
   time(&rawtime_start);
   timeinfo = localtime(&rawtime_start);
   printf("read log start:%s",asctime(timeinfo));
   long int line_num = 0;
   char *line = (char *) malloc(READ_BUFFER_SIZE);
   while(fgets(line,READ_BUFFER_SIZE,stdin)!=NULL){
        line_num++;
        if(isNeededRawLine(line) == TRUE)
	        parseLine(line);
   }   
   time_t rawtime_end;
   time(&rawtime_end);
   timeinfo = localtime(&rawtime_end);
   printf("read log   end:%s",asctime(timeinfo));
   printf("read lines : %ld\n",line_num);

}
