#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mysql/mysql.h>
#include <ctype.h>

#define ROW_DOMAIN 16
#define COL_DOMAIN 2


void getvarconf(const char *var, char **re);
int getActive(const char *domain1);
int es_name(char *name);
char * strtolower(const char *c);
char * time_t2date(time_t t, int format_with_sec);

typedef struct dominios{
	char d[100];
	struct dominios *next;
} ldominios;
ldominios * getDomainCache(MYSQL *conn);

char * getDomainRegexlst(char *domain);

#endif
