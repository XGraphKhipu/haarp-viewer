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
	#install autoconf
	#for derivatives debian:
	apt-get install autoconf
	git clone https://github.com/keikurono/libcgi.git
	cd libcgi
	./autogen.sh
	./configure --prefix=/usr
	make
	make install	

Install HaarpViewer:

	cd /usr/src/
	git clone https://github.com/keikurono/haarp-ext-js-viewer.git
	cd haarp-ext-js-viewer
	cd src/
	make
	make install

	cd ..
	cp src/*.cgi /usr/lib/cgi-bin/
	cp hc.html /var/www/
	cp -r images /var/www/
	touch /var/log/haarp/webaccess.log
	chown www-data:www-data /var/log/haarp/webaccess.log
	echo "ACCESSWEBLOG /var/log/haarp/webaccess.log" >> /etc/haarp/haarp.conf

Access:
	
	http://<ip_server>/cgi-bin/haarp.cgi


![Hviewer](http://img831.imageshack.us/img831/4756/haarpviewer2.png)

If you find this code useful, or wish to fund further development,
you can use PayPal to donate to the Haarp-Ext-Js-Viewer project:

<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&amp;hosted_button_id=QYCCSYYGW52QU"><br>
<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif"></a>
