haarp-ext-js-viewer
===================

A viewer made ​​in Ext Js for HaarpCache


Installation
===================

Need to install ExtJs and LibCGI

For ExtJs:

	#installing unzip
	apt-get install unzip
	cd /var/www/html
	wget http://extjs.cachefly.net/ext-3.4.0.zip 
	unzip  ext-3.4.0.zip
	ln -s ext-3.4.0 ext

For LibCGI:

	cd /usr/src
	#install autoconf
	#for derivatives debian:
	apt-get install autoconf
	git clone git://github.com/keikurono/libcgi.git
	cd libcgi
	./autogen.sh
	./configure --prefix=/usr
	make
	make install	

Install HaarpViewer:

	cd /usr/src/
	git clone git://github.com/keikurono/haarp-ext-js-viewer.git
	cd haarp-ext-js-viewer
	cd src/
	make

	cd ..
	cp src/*.cgi /usr/lib/cgi-bin/
	cp hc.html /usr/lib/cgi-bin/
	cp -r images /var/www/html/
	touch /var/log/haarp/webaccess.log
	chown www-data:www-data /var/log/haarp/webaccess.log
	echo "ACCESSWEBLOG /var/log/haarp/webaccess.log" >> /etc/haarp/haarp.conf

Access:
	
	http://<ip_server>/cgi-bin/haarp.cgi


<img src="http://perufw.files.wordpress.com/2014/02/hviewer.jpg" alt="Drawing" align="center" width="600"/>

If you find this code useful, or wish to fund further development,
you can use PayPal to donate to the Haarp-Ext-Js-Viewer project:

<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&amp;hosted_button_id=QYCCSYYGW52QU"><br>
<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif"></a>
