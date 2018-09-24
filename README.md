# ArduNest - The Arduino Remote Thermostat for Nest
Code for ArduNest .ino and server side PHP scripts
ArduNest is an Arduino enabled Nest thermostat controller. The arduino device wirelessly connects to a remote server to retrieve the current/target temperature and displays it on the LCD screen. The temperature can be modified by the Arduino by physical buttons.

# Goals
Here are some goals for the project.

- Accessiblilty - The portable thermostat must be able to change the temperature from the device somewhere upstairs
- Efficiency - The portable thermostat must be low powered or at least have some power saving properties when the user does not want to set the new target temperature

# Parts Used:
- WeMos D1 R2 - Arduino based board with an ESP-8266 Wifi chip embedded.
- LCD Arduino Shield with Keypad

# How it works
1. On bootup, the WeMos will call a PHP script to get the current temperature and current target temperature and display on the lcd.
2. The user can set the desired temperature by using the up and down buttons. If the user presses the up button, the target temperature will increment by one. If the user presses the down button, the target temperature will decrease by one.
3. The user can also use the right button to cancel and the lcd will display the original target temperature.
4. If the user presses the left button, the WeMos will send a new target temperature to the server.
5. The PHP script will send the command to NEST cloud to change the target temperature.
6. The NEST cloud receives the data from the script and sends it to NEST thermostat.
7. NEST thermostat receives the new target temperature and starts the A/C.

# Files
Arduino INO File: <br/>
AruNest.ino - This file is the logic behind the AruNest. This handles the buttons events, displays information on the LCD, and sends requests to the remote server.

Libriries Used:
- LCDKeypad - https://github.com/dzindra/LCDKeypad/releases/tag/v1.1.0

Server-Sise PHP Files:<br/>
These files act has a middle man, taking commands from the Arduino and relaying it to the Nest server. These files are dependant on the PHP Nest library (https://github.com/gboudreau/nest-api).
1. getTemp.php - This file retrieves the target and current temperature to the AruNest
2. setCurTemp.php - This files sends the desired current temperature to the Nest server.


Check it out in action <br/>
[![VIDEO](https://img.youtube.com/vi/LGTQfrPi12s/0.jpg)](https://youtu.be/LGTQfrPi12s)

