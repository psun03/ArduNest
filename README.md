# AruNest
Code for AruNest .ino and server side PHP scripts
AruNest is an Arduino enabled Nest thermostat controller. The arduino device wirelessly connects to a remote server to retrieve the current/target temperature and displays it on the LCD screen. The temperature can be modified by the Arduino by physical buttons.

Ino File
AruNest.ino - This file is the logic behind the AruNest. This handles the buttons events, displays information on the LCD, and sends requests to the remote server.

PHP Files:
These files act has a middle man, taking commands from the Arduino and relaying it to the Nest server. These files are dependant on the PHP Nest library (https://github.com/gboudreau/nest-api).
1) getTemp.php - This file retrieves the target and current temperature to the AruNest
2) setCurTemp.php - This files sends the desired current temperature to the Nest server.
