Haarp-Viewer
===================

A viewer made ​​in Ext Js for [HaarpCache] (https://github.com/keikurono/haarpcache).

## ▓ Demo ▓
![GIF Demo] (https://perufw.files.wordpress.com/2015/09/haarpviewer1.gif)

## Installation

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

## Changelog

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
