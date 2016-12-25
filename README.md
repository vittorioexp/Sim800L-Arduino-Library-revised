## Library SIM800l Module for Arduino UNO
The Purpose of This library is to use the module in the most easy way and transparent.  
Website: [Sim800l library](https://github.com/VittorioEsposito/Sim800l-revised)


Go to arduino IDE Sketch >> Import Library >> add library... Select the folder Sim800l

OR 

Place the Sim800l library folder your arduinosketchfolder/libraries/ folder. 
You may need to create the libraries subfolder if its your first library. Restart the IDE.


## connections & pinouts
Arduino Uno  |   Sim800l   |    Notes  
-------------|-------------|------------
+5v| (3.8v)~(4.4v)!| Power supply input
10 RX_PIN | TX |  
11 TX_PIN | RX |
2   RESET_PIN | RST| Reset Pin
GND | GND | 


## Methods and functions

Name|Return|Notes
:-------|:-------:|:-----------------------------------------------:|
begin()|None|Initialize the library
begin(number)|None|Initialize the library
reset()|None|Reset the module,and wait to Sms Ready.
setSleepMode(bool)|true or false|enable or disable sleep mode
getSleepMode()|true or false|return sleep mode
setFunctionalityMode(number)|true or false|set functionality mode
getFunctionalityMode()|true or false|return functionality mode
sendSms(number,text)|true or false|parameters must be Strings.
readSms(index)|String|index is the position of the sms in the prefered memory storage
getNumberSms(index)|String|returns the number of the sms.
delAllSms()|true or false|Delete all sms
answerCall()|true or false|
callNumber(number)|None|
hangoffCall()|true or false|
getCallStatus()|uint8_t|Return the call status, 0=ready,2=Unknown(),3=Ringing,4=Call in progress
setPhoneFunctionality()|None|Set at to full functionality 
activateBearerProfile()|None|
deactivateBearerProfile()|None|
RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second)|None| Parameters must be reference ex: &day
dateNet()|String|Return date time GSM
updateRtc(utc)|true or false|Return if the rtc was update with date time GSM. 
____________________________________________________________________________________

You can regulate the voltage to the desired with this, is not the best,
but for start it's easy.

![alt text](https://github.com/cristiansteib/Sim800l/blob/master/images/power_supply.png "LM317")



For the **reset pin** they need NPN transistor, this is an example circuit that you can use.

![alt text](https://github.com/cristiansteib/Sim800l/blob/master/images/RESET.png "reset_circuit")
