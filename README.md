haarp-ext-js-viewer
===================

A viewer made ​​in Ext Js for HaarpCache


Instalation
===================

Need to install ExtJs and LibCGI

For ExtJs:

	cd /var/www/
	wget http://extjs.cachefly.net/ext-3.4.0.zip 
	unzip  ext-3.4.0.zip
	ln -s ext-3.4.0 ext

For LibCGI:

	cd /usr/src
	git clone https://github.com/keikurono/libcgi.git
	cd libcgi
	./autogen.sh
	./configure --prefix=/usr
	make
	make install	

Install HaarpViewer:

	cd src/
	make
	make install

	cd ..
	cp src/*.cgi /usr/lib/cgi-bin/
	cp hc.html /var/www/
	cp -r images /var/www/
	touch /var/log/haarp/webaccess.log
	chown www-data:www-data /var/log/haarp/webaccess.log

Access:
	
	http://<ip_server>/cgi-bin/haarp.cgi

