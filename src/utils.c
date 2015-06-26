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
	
	if( strstr(domain,"mediafire") )
		strcpy(domain, "205\\.196\\.|199\\.91");
	if( strstr(domain, "fbcdn") )
		strcpy(domain, "fbcdn");
	if( strstr(domain, "aol") )
		strcpy(domain, "avideos");
	if( strstr(domain, "pornhub") )
		strcpy(domain, "pornhub");
	if( strstr(domain, "porntube_vid") )
		strcpy(domain, "video.{0,5}\\.porntube");
	if( strstr(domain, "porntube_img") )
		strcpy(domain, "thumbnails.{0,5}\\.porntube");
	FILE *ft = fopen("/etc/haarp/haarp.lst","r");
	if(!ft)
		exit(1);

	char line[1000];
	char *l,*t;

	while( fgets(line,1000,ft) )
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
