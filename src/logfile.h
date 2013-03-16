#ifndef LOGERR_H
#define LOGERR_H

#include <stdio.h>
#include <stdlib.h>

char filelog[100];
void logfile_init(char *fl);
void logerror(char *file, int line, char *format, ...);

#endif
