#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "logfile.h"


void getvarconf(const char *var, char **re)
{
	FILE *ft = fopen("/etc/haarp/haarp.conf","r");
	if(!ft)
	{
		logerror(__FILE__,__LINE__,"Error, config file /etc/haarp/haarp.conf not found!");
		exit(1);
	}
	char line[200];
	char *l;

	strcpy(*re,"\0");

	while( fgets(line,200,ft) )
	{
		l = strstr(line,var);
		if(l)
		{
			sscanf(l + strlen(var),"%s",*re);
			return;
		}
	}
}

int getActive(const char *domain1)
{
	char domain[100];
	strcpy(domain, domain1);
	
	char *dregex = getDomainRegexlst(domain);
	
	if(dregex)
		strcpy(domain, dregex);

	FILE *ft = fopen("/etc/haarp/haarp.lst","r");
	if(!ft)
		exit(1);

	char line[1000];
	char *l,*t;

	while ( fgets(line,1000,ft) )
	{
		t  = strstr(line,"#");
		if(t)
			*t = '\0';
		l = strstr(line,domain);
		if(l)
			return 1;
	}
	return 0;
}
char * getDomainRegexlst(char *domain) {
	char * domain2regex[ROW_DOMAIN][COL_DOMAIN] = {
        	{"mediafire", "205\\.196\\.|199\\.91"},
      		{"fbcdn", "fbcdn"},
	        {"aol", "avideos"},
	        {"pornhub", "pornhub"},
	        {"porntube_vid", "video.{0,5}\\.porntube"},
	        {"porntube_img", "thumbnails.{0,5}\\.porntube"},
	        {"socialpg_dragoncity", "socialpointgames\\.com"},
	        {"socialpg", "socialpointgames\\.com"},
	        {"mercadolibre_img", "mlstatic\\.com"},
        	{"GAMESF_wooga", "wooga\\.com"},
	        {"GAMESF_popcap", "popcap\\.com"},
       		{"GAMESF_llnwd", "llnwd\\.net"},
	        {"GAMESF_cloudfront", "cloudfront\\.net"},
	        {"GAMESF_amazonaws", "amazonaws\\.com"},
	        {"GAMESF_akamaihd", "akamaihd\\.net"},
	        {"FrivIntro", "\\.friv\\.com"} };

	char *d = (char *)malloc(sizeof(char) * 100);
	memset(d, '\0', 100);
	int i;
	for ( i = 0; i < ROW_DOMAIN; i++ ) {
		if( strstr(domain, domain2regex[i][0]) ) {
			strcpy(d, domain2regex[i][1]);
			return d;
		}
	}
	return NULL;
}

/*
 * Aceptar sólo: [0aZ-9zZ], " ", "-", "_".
 * 
 * */
int es_name(char *name)
{
	int len = strlen(name);
	int i;
	for(i=0;i<len;i++)
	{
		int n = name[i];
		//if(n<45 || (n>45 && n<48) || (n>57 && n<65) || (n>90 && n<95) || (n>95 && n<97) || (n>122))
		if(!isalnum(n) && n != 32 && n != 45 && n != 95 && n != 46) 
			return 0;
	}
	return 1;
}
char * strtolower(const char *c) {
	int size = strlen(c);
	char *re = (char *)malloc(sizeof(char)*(size + 1));
	strcpy(re, "\0");
	int i;
	for ( i = 0; i < size; i++ ) {
		re[i] = tolower(c[i]);
	}
	re[size] = '\0';
	return re;
}

char * time_t2date(time_t t, int format_with_sec) {
	time_t min  = 60;
	time_t hour = 3600;
	time_t day  = 24*hour;
	
	char *re = (char *)malloc(sizeof(char)*150);
	char tmp[15];
	memset(re, '\0', 150);

	char coma[5];
	memset(coma, '\0', 5);

	if(t/day) {
		sprintf(re, "%li Da%s", t/day, (t/day == 1)?"y":"ys");
		t = t%day;
	} else 
		sprintf(re, "0 Days");

	strcpy(coma, ", ");
	
	if(t/hour) {
		sprintf(tmp, "%s%li Hou%s", coma, t/hour, (t/hour == 1)?"r":"rs");
		strcat(re, tmp);
		t = t%hour;
		strcpy(coma, ", ");
	} else 
		strcat(re, ", 0 Hours");
	
	if(t) {
		sprintf(tmp, "%s%.1lf Mi%s", coma, t/(min+0.0), (t/min == 1)?"n":"ns");
		strcat(re, tmp);
	} else {
		strcat(re, ", 0 Mins");
	}
	return re;
}
ldominios * getDomainCache(MYSQL *conn) {
	ldominios *p = NULL;
	if( mysql_query(conn, "select domain from haarp where deleted=0 and static=0 group by domain order by domain DESC")) {
		logerror(__FILE__, __LINE__, "Error in mysql query!: '%s'", mysql_error(conn));
		return NULL;
	}
	MYSQL_RES *res = mysql_store_result(conn);
	MYSQL_ROW r;
	while ( (r = mysql_fetch_row(res)) != NULL ) {
		ldominios *nodo = (ldominios *)malloc(sizeof(ldominios));
		strcpy(nodo->d, r[0]);
		nodo->next = NULL;
		if(!p)
			p = nodo;
		else {
			nodo->next = p;
			p = nodo;
		}	
	}
	return p;
}
