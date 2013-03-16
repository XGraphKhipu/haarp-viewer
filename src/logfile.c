#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include "logfile.h"


void logfile_init(char *fl) {
	strcpy(filelog,fl);
}

void logerror(char *file, int line, char *format, ...) {
	char msg_error[200],tim[70];
	
	FILE *fileloge = fopen(filelog,"a");
	if(!fileloge) {
		printf("Error, file log no open! %s(%d)",file,line);
		return;
	}
	va_list arg;
	va_start(arg, format);
	vsnprintf(msg_error,200,format,arg);
	va_end(arg);

	time_t t = time(NULL);
	struct tm *st = localtime(&t);
	strftime(tim,70,"[%b %d %H:%M:%S]",st);
	
	fprintf(fileloge,"%s In file: %s(%i) %s\n",tim,file,line,msg_error);
	
	fclose(fileloge);
}
