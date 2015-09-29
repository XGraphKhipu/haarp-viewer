#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <syslog.h>
#include "logfile.h"


int logfile_init(char *fl) {
	if(!strlen(fl))
		return 0;
	strcpy(filelog,fl);
	return 1;
}

int logerror(char *file, int line, char *format, ...) {
	char msg_error[1000],tim[70];
	
	FILE *fileloge = fopen(filelog,"a");
	if(!fileloge) {
		syslog(LOG_WARNING, "[haarpviewer] file log %s not open!", filelog);
		return 0;
	}
	va_list arg;
	va_start(arg, format);
	vsnprintf(msg_error,1000,format,arg);
	va_end(arg);

	time_t t = time(NULL);
	struct tm *st = localtime(&t);
	strftime(tim,70,"[%b %d %H:%M:%S]",st);
	
	fprintf(fileloge,"%s In file: %s(%i) %s\n",tim,file,line,msg_error);
	
	fclose(fileloge);
	return 1;
}
