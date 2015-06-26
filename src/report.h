#ifndef REPORT_H
#define REPORT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct files_count{
	float files;
	int hora;
	struct files_count *next;
} lfiles_count;
typedef struct ts_reports{
	char d[40];
	char f[40];
	char s[40];
	char e[40];
	char h[40];
	double per;
	struct ts_reports *next;
} lts_reports;

#endif
