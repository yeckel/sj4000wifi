# sj4000wifi
QT based app for working with SJ4000 WiFi outdoor camera

Based on the work from:

http://www.rcgroups.com/forums/showpost.php?s=bdc0be9f330339f4a44c0f91c4b2d9a7&p=29634969&postcount=3156


Compiling was tested at Ubuntu 14.04 with downloaded QT 5.4.0 from http://www.qt.io/download/
QT distributed with Ubuntu should make too.

How to compile:

git clone https://github.com/yeckel/sj4000wifi.git
/opt/Qt/5.4/gcc_64/bin/qmake
make

Calling camera:
curl "http://192.168.1.254/?custom=1&cmd={CommandHere}&par={OptionHere}"

Data obtained using MITM attack and wireshark:
ettercap -Tq -i wlan0 -M arp:remote //{LOCAL IP}/ //192.168.1.254/

All camera commands:
CMD	Function				Parameter		Output
1001
1002
1003	Free space for fotos left					<Value>10055</Value>
1005
1006
1007
1008
1009
1011
1012
2001	Recording(in mode video) 		1-start/0-stop
2002
2003
2004
2005
2006
2007
2008
2009	Free remaining secons for video					<Value>15752</Value>
2010
2013
2014
2015
2016
2019
3001
3002	get list of all commands					XML file		
3003
3004
3005
3006
3007
3008
3010
3011
3012	FW Version							<String>G20141204V01</String>
3013
3014	Dump settings							XML File
3015	Media files list						XML File
3016	Camera mode							0-video, 1-foto, 3-time videos, 4-time fotos
3017	Free bytes left on card						<Value>32093601792</Value>
3018
3019	Battery status							Values between (min)0..5(max), 5 when on charger
3021
3022
3023
3024
3025
3026
3027
3028
3029	Some non working link						http://115.29.201.46:8020/download/filedesc.xml
3030	FW Filename(not downloadable)					http://192.168.1.254/FW96655A.bin
4001
4002
4003
4004

