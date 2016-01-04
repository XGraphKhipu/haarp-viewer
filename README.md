Haarp-Viewer
===================

A viewer made ​​in Ext Js for [HaarpCache] (https://github.com/keikurono/haarpcache).

## ▓ Demo ▓
![GIF Demo] (https://perufw.files.wordpress.com/2015/09/haarpviewer1.gif)

## Installation

Need to install ExtJs and LibCGI

For ExtJs:

	su
	apt-get install unzip
	mkdir /var/www/html/ 2>/dev/null
	cd /var/www/html/
	wget http://extjs.cachefly.net/ext-3.4.0.zip 
	unzip  ext-3.4.0.zip
	ln -s ext-3.4.0 ext
	ln -s html/ext-3.4.0 ../ext
	
For LibCGI:

	cd /usr/src
	apt-get install autoconf git
	git clone git://github.com/keikurono/libcgi.git
	cd libcgi
	./autogen.sh
	./configure --prefix=/usr
	make
	make install	

Install HaarpViewer:

	cd /usr/src/
	git clone git://github.com/keikurono/haarp-viewer.git
	cd haarp-viewer
	cd src/
	make
	
	cd ..
	rm -f /usr/lib/cgi-bin/report.cgi /usr/lib/cgi-bin/haarp.cgi 2>/dev/null
	rm -f /var/www/cgi-bin/report.cgi /var/www/cgi-bin/haarp.cgi 2>/dev/null
	cp src/*.cgi /usr/lib/cgi-bin/ 2>/dev/null
	cp src/*.cgi /var/www/cgi-bin/ 2>/dev/null
	cp hc.html /var/www/html/
	cp hc.html /var/www/ 
	cp -r images /var/www/html/
	cp -r images /var/www/
	touch /var/log/haarp/webaccess.log
	chown www-data:www-data /var/log/haarp/webaccess.log
	echo "ACCESSWEBLOG /var/log/haarp/webaccess.log" >> /etc/haarp/haarp.conf
	
	a2enmod cgi 2>/dev/null
	service apache2 restart 2>/dev/null

Access:
	
	http://<ip_server>/cgi-bin/haarp.cgi

## Changelog

__Version 1.1_2__

2016/01/04
* Fix problem with some icons in the report.
* Adding functionality of filter by domain search in the report panel.
* Support for HaarpCache 2.1.2.

__Version 1.1_1__

2015/10/01

* Update logfile format and fix incorrect status in some plugins in the report
* Update directories for default for a good instalation of the haarp-viewer
* Adding new icons for a lot of plugins

__Version 1.1__

2015/09/14

* Add view for the files in cache.
* Add more images for each plugin additional in HaarpCache 1.4.x.
* Fix problem with the report of used of the HaarpCache.
* Change of values integer to floats for report of field Hits in the main report.

__Version 1.0__

2012/04/07

* First version of the Haarp-View.



<br/>
<div align="center">
<p><h6>If you find this code useful, or wish to fund further development,
you can use PayPal to donate to the HaarpCache project:</h6>
<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&amp;hosted_button_id=QYCCSYYGW52QU"><img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif"></a>
</div>

    
  </body>
</html>
