#ifndef LOGERR_H
#define LOGERR_H

#include <stdio.h>
#include <stdlib.h>

char filelog[100];
int logfile_init(char *fl);
int logerror(char *file, int line, char *format, ...);

#endif
