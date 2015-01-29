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
1001	Take foto (n foto mode, time foto)	-
1002	Foto image size				par=0-12M,1-10M,..6-VGA,7-1.3M,8-14M	
1003	Free space for fotos left					<Value>10055</Value>
1005	?? Quality
1006	?? Sharpness
1007	White balance				par=0 -auto,1-Daylight,2-Cloudy,3-Thungsten,4-Fluorescent
1008	?? Color
1009	?? ISO setting
1011	?? Anti Shake
1012	Time laps between fotos			par=0-3s,1-5s,2-10s,3-20s
2001	Recording(in mode video,time video)	1-start/0-stop
2002	Video resolution			par=0-FHD,1-720p60f,2-720p30f,3-WVGA,4-VGA
2003	Cyclic record				par=0-off,1-3min,2-5Min,3-10Min,4..?
2004	WDR (HDR)				par=0 off,1 on
2005	Exposure				par=3- +1.0,4- +2/3,12- -2,7 -1/3
2006	?? Motion detection (not in App, not working)			
2007	Audio recording				par=0 off,1 on
2008	Date stamp				par=0 off,1 on
2009	Free remaining seconds for video				<Value>15752</Value>
2010	?? Live View Size
2013	
2014	
2015	
2016	
2019
3001	Set mode 				par=1 (0-foto,1-video,3-time video, 4-time foto)
3002	get list of all commands					XML file		
3003	Set wifi name				str=YeckelCam
3004	Set wifi password			str=123456
3005	Set Date				str=2015-01-29		<status>0</status>
3006    Set Time				str=11:13:31		<status>0</status>
3007	Turn camera off				par=0-newer,1-3min,2-5-min,3-10min,4-now
3008	?? DV Language
3010	Format SD card				par=1
3011	Reset to default
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
3025	Powerline frequency			par=0- 50Hz, 1- 60Hz
3026	Rotate					par=0- Normal,1 -upside down
3027
3028
3029	Some non working link						http://115.29.201.46:8020/download/filedesc.xml
3030	FW Filename(not downloadable)					http://192.168.1.254/FW96655A.bin
4001
4002
4003
4004

When there is parameter missing or, then the SJ4000wifi camera freeze itself and needs to be restarted. The commands are thus "setters" and "getters".
