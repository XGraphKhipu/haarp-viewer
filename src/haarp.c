/*
 * haarp.c
 * 
 * Copyright 2013 Manolo Canales <kei.haarpcache@gmail.com>
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
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <libcgi/cgi.h>
#include <libcgi/session.h>

int main(){
	cgi_init();
	cgi_session_start();
	cgi_init_headers();
	
	//if(cgi_session_var_exists("user"))
	//{
		cgi_include("hc.html");
	/*}
	else
	{
		//puts("<script>alert('Access denied');document.location='index.cgi';</script>");
		puts("<script>document.location='index.cgi';</script>");
		//puts("Login fallido, cgi_session_var_exist('user')=0 </br>");
		//puts(cgi_session_var("admin"));	
	}	*/
	cgi_end();
	
	return 1;
}



