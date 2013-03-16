/*
 * (c) Copyright 2013 Manolo Canales <kei.haarpcache@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libcgi/cgi.h>
#include <libcgi/session.h>
#include <mysql/mysql.h>
#include <sys/statvfs.h>
#include "logfile.h"
#include "utils.h"
#include "report.h"

#define charmalloc(a) (char *)malloc(sizeof(char)*a);

int main(){
	cgi_init();
	cgi_session_start();
	cgi_process_form();
	
	int start = atoi(cgi_param("start"));
	
	char *h = charmalloc(100);
	char *u = charmalloc(100);
	char *p = charmalloc(100);
	char *d = charmalloc(100);
	char *fl = charmalloc(100);

	getvarconf("MYSQL_HOST",&h);
	getvarconf("MYSQL_USER",&u);
	getvarconf("MYSQL_PASS",&p);
	getvarconf("MYSQL_DB",&d);
	
	getvarconf("ACCESSWEBLOG", &fl);
	
	logfile_init(fl);
	
	logerror(__FILE__,__LINE__,"Init ");
	if(start == 1)
	{
		puts("Content-Type: text/plain");
		puts("");
		MYSQL *connect;		
		connect = mysql_init(NULL);		
		if(!mysql_real_connect(connect, h, u, p, d, MYSQL_PORT, NULL, 0))
		{
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}
		long double totaleconomy = 0;
		long double totalhits = 0;
		long double totalcount = 0;
		long double totalsize = 0;
		char pet[350];
		char coma = ' ';
		strcpy(pet,"select domain,COUNT(*) as files,sum(filesize) as size,sum(filesize*requested) as eco, sum(requested) as hits from haarp where deleted=0 and static=0 group by domain order by 1 DESC");	
		if(mysql_query(connect, pet))
		{
			logerror(__FILE__,__LINE__,"%s",mysql_error(connect));
			exit(1);
		}
		double percent;
		MYSQL_RES *res = mysql_store_result(connect);		
		MYSQL_ROW v;
		puts("{ data: [");
		while ( (v = mysql_fetch_row(res)) != NULL ) {
			if(atoi(v[2])) {
				percent=(atof(v[3])*100)/atof(v[2]);
			}
			else
				continue;
			printf("%c{domain : '%s', files: '%s', size : '%s', eco : '%s', hits : '%s', porc :'%0.2lf', active: '%d'}\n",coma,v[0],v[1],v[2],v[3],v[4],percent,getActive(v[0]));
			
			coma = ',';
			totaleconomy += atof(v[3]);
			totalhits += atof(v[4]);
			totalcount += atof(v[1]);
			totalsize += atof(v[2]);
		}
		mysql_close(connect);
		printf("%c{domain: 'Totales', files : '%.2Lf', size : '%.2Lf', eco: '%.2Lf', hits : '%.2Lf', porc : '%.2Lf', active: '1' }\n", coma, totalcount, totalsize, totaleconomy, totalhits, (totaleconomy/totalsize)*100.0);	
		puts("]");
		puts("}");
		return 1;
	}
	if(start == 2) //history HC, max and min date.
	{
		puts("Content-Type: text/plain");
		puts("");		
		int len = strlen(cgi_param("domain"));
		char  * domain = (char *)malloc(sizeof(char)*len+2);
		strcpy(domain,cgi_param("domain"));

		MYSQL *connect;
		connect = mysql_init(NULL);
		if(!mysql_real_connect(connect, h, u, p, d, MYSQL_PORT, NULL, 0))
		{
			printf("{success: false, errors: \"Error, mysql connect\"}");
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}
		char pet[200];
		sprintf(pet,"select date(min(downloaded)), date(max(downloaded)) from haarp where domain=trim('%s')",domain);
		if(mysql_query(connect,pet))
		{
			printf("{success: false, errors: 'Error, mysql connect'}");
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}
		MYSQL_RES * res = mysql_store_result(connect);		
		MYSQL_ROW r = mysql_fetch_row(res);
		printf("{success: true, min: '%s', max : '%s'}",r[0],r[1]);
		mysql_close(connect);
		free(domain);
	}
	if(start == 3) //history HC.
	{
		MYSQL *connect;
		connect = mysql_init(NULL);
		FILE *f = fopen("/tmp/t1","w");		
		puts("Content-Type: text/plain");
		puts("");
		if(!mysql_real_connect(connect, h, u, p, d, MYSQL_PORT, NULL, 0))
		{
			printf("{success :false, errors: 'Error, mysql connect'}");
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}
		int len = strlen(cgi_param("data"));
		char * domain = (char*)malloc(sizeof(char)*(len+2));
		strcpy(domain,cgi_param("data"));
							
		len = strlen(cgi_param("fecha"));
		char * date = (char*)malloc(sizeof(char)*(len+2));
		strcpy(date,cgi_param("fecha"));
		//~ trim(date);		
		
		char pet[200];
		
		sprintf(pet,"select count(*), hour(downloaded) as hora from haarp where domain='%s' and date(downloaded)='%s' group by hora",domain,date);
		if(mysql_query(connect,pet))
		{
			printf("{success: false, errors: 'Error, mysql query'}");
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}		
		MYSQL_RES *res = mysql_store_result(connect);
		MYSQL_ROW r;		
		lfiles_count *primer = NULL;
		lfiles_count *ultimo = NULL;
		while( (r = mysql_fetch_row(res)) != NULL )
		{
			lfiles_count *nodo = (lfiles_count *)malloc(sizeof(lfiles_count)*1);
			nodo->files = atoi(r[0]);
			nodo->hora = atoi(r[1]);
			fprintf(f,"(files) %d\n",nodo->hora);
			nodo->next = NULL;
			if(!primer)
			{
				primer = nodo;
				ultimo = nodo;
			}
			else
			{
				ultimo->next = nodo;
				ultimo = nodo;
			}
		}
		sprintf(pet,"select count(*),hour(last_request) as hora from haarp where domain='%s' and date(last_request)='%s' and requested>0 group by hora;",domain,date);
		if(mysql_query(connect,pet))
		{
			printf("{success: false, errors: 'Error, mysql query'}");
			logerror(__FILE__,__LINE__,"Error Mysql: %s",mysql_error(connect));
			exit(1);
		}
		res = mysql_store_result(connect);
		lfiles_count *primer1 = NULL;
		lfiles_count *ultimo1 = NULL;
		while( (r = mysql_fetch_row(res)) != NULL )
		{
			lfiles_count *nodo = (lfiles_count *)malloc(sizeof(lfiles_count)*1);
			nodo->files = atoi(r[0]);
			nodo->hora = atoi(r[1]);
			fprintf(f,"(hits) %d\n", nodo->hora);
			nodo->next = NULL;
			if(!primer1)
			{
				primer1 = nodo;
				ultimo1 = nodo;
			}
			else
			{
				ultimo1->next = nodo;
				ultimo1 = nodo;
			}
		}
		lfiles_count *nodo = primer;
		puts("{ data: [");
		char p = ' ';	
		int cont = 0;
		while(nodo)
		{
			lfiles_count *nodo1 = primer1;
			int entro = 0;	
			while(nodo1)
			{
				if(nodo->hora > nodo1->hora)
				{
					if(nodo1->hora > cont)
					{
						int i;
						for(i=cont;i<nodo1->hora;i++)
						{
							printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);
							p = ',';
						}
						cont = ++i;
					}
					else
						cont++;
					printf("%c{domain: '%s', cache: 0, hits: %d, date: '%d:00'}\n",p,domain,nodo1->files,nodo1->hora);
					p = ',';
					primer1 = nodo1->next;
					free(nodo1);
					nodo1 = primer1;	
					continue;				
				}
				else if( nodo->hora == nodo1->hora )
				{
					if(nodo->hora > cont)
					{
						int i;
						for(i=cont;i<nodo->hora;i++)
						{
							printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);
							p = ',';
						}
						cont = ++i;
					}
					else 
						cont++;				
					printf("%c{domain: '%s', cache: %d, hits: %d, date: '%d:00'}\n",p,domain,nodo->files,nodo1->files,nodo->hora);
					p = ',';
					primer1 = nodo1->next;
					free(nodo1);					
					entro = 1;
					break;
				}
				else 
				{
					if(nodo->hora > cont)
					{
						int i;
						for(i=cont;i<nodo->hora;i++)
						{
							printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);
							p = ',';
						}
						cont = ++i;
					}
					else
						cont++;
			
					printf("%c{domain: '%s', cache: %d, hits: 0, date: '%d:00'}\n",p,domain,nodo->files,nodo->hora);
					p = ',';
					entro = 1;
					break;
				}
			}
			if(!entro)
			{
				if(nodo->hora > cont)
				{
					int i;
					for(i=cont;i<nodo->hora;i++)
					{
						printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);
						p = ',';
					}
					cont = ++i;
				}
				else
					cont++;
				printf("%c{domain: '%s', cache: %d, hits: 0, date: '%d:00'}\n",p,domain,nodo->files,nodo->hora);
				p = ',';
			}
			nodo = nodo->next;
		}
		nodo = primer1;
		while(nodo)
		{

			if(nodo->hora > cont)
			{
				int i;
				for(i=cont;i<nodo->hora;i++)
				{
					printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);
					p = ',';
				}
				cont = ++i;
			}
			else			
				cont++;
			printf("%c{domain: '%s', cache: 0, hits: %d, date: '%d:00'}\n",p,domain,nodo->files,nodo->hora);
			p = ',';
			nodo = nodo->next;
		}
		if(cont < 23)
		{
			int i;
			for(i=cont;i<=23;i++)
			{
				printf("%c{domain: '%s', cache: 0, hits: 0, date: '%d:00'}\n",p,domain,i);			
				p = ',';
			}
		}
		mysql_close(connect);
		puts("]}");
	}
	return 1;
}
