Sim800L Arduino Library revised
=====

The SIM800L Arduino Library is a simple and easy-to-use library for the SIM800L module, allowing for quick and efficient communication with the module using the Arduino platform.


Features
---

* Simplifies the initialization and configuration of the SIM800L module
* Provides a set of easy-to-use functions for sending and receiving SMS messages
* Supports making and receiving phone calls
* Includes example sketches to demonstrate the library's capabilities


Installation
---

You can install the Sim800L Arduino Library in the Arduino IDE by going to Sketch > Include Library > Manage Libraries, searching for "Sim800L" and clicking on the "install" button.
Alternatively, you can download the library files from the GitHub repository and install it by going to Sketch > Include Library > Add .ZIP Library and selecting the downloaded files.


Usage
---

To use the library, simply include the library in your sketch and create an instance of the SIM800L class. The library provides a set of functions for sending and receiving SMS messages, making and receiving phone calls, and more.

For example, to send an SMS message, you can use the following code:
```
#include <Sim800L.h>

Sim800L Sim800L(10, 11);   // RX_PIN and TX_PIN

void setup(){
	Sim800L.begin(4800); 			
	Sim800L.sendSms("+1234567890","Hello world!");
}

void loop(){
	//do nothing
}
```



Collaboration
---

This is an open-source project and I'm currently looking for more collaborators to help grow and improve it. If you're interested, feel free to submit your pull request to the GitHub repository.


Connecting the SIM800L to the Arduino
---

Before you can use the Sim800L Arduino Library, you need to physically connect the SIM800L module to your Arduino board.

1. Connect the SIM800L's GND pin to the GND pin on the Arduino board
2. Connect the SIM800L's VCC pin to the 3.3V pin on the Arduino board
3. Connect the SIM800L's RX pin to the TX pin on the Arduino board (default is pin 11)
4. Connect the SIM800L's TX pin to the RX pin on the Arduino board (default is pin 10)
5. Connect the SIM800L's RST pin to the RESET pin on the Arduino board (default is pin 2)

It is important to note that the SIM800L module requires a stable power supply of at least 2A, it is strongly recommended to use an external power supply to power the SIM800L module.
The SIM800L's VCC pin should be connected to the 3.3V pin on the Arduino board. Connecting it to the 5V pin may damage the module as it operates on 3.3V voltage level. It is important to ensure the voltage level is compatible with the module's specifications to avoid any damage.


Function List
---

Here is a list of functions that can be called on an instance of the SIM800L class:

Name|Return|Notes
:-------|:-------:|:-----------------------------------------------:|
begin()|None|Initialize the module with a defalt baud rate
begin(number)|None|Initialize the module with a custom baud rate
reset()|None|Reset the module, and wait to Sms Ready.
setSleepMode(bool)|bool|enable or disable sleep mode. If it returns true, there is an error.
getSleepMode()|bool|return sleep mode status. If it returns true, there is an error.
setFunctionalityMode(number)|bool|set functionality mode. If it returns true, there is an error.
getFunctionalityMode()|bool|return functionality mode status. If it returns true, there is an error.
setPIN(String)|bool|enable user to set a pin code. If it returns true, there is an error.
getProductInfo()|String|return product identification information
getOperatorsList()|String|return the list of operators
getOperator()|String|return the currently selected operator
calculateLocation()|bool|calculate gsm position. If it returns true, there is an error.
getLocationCode()|String|return the location code
getLongitude()|String|return longitude
getLatitude()|String|return latitude
sendSms(number,text)|bool|both parameters must be Strings. If it returns true, there is an error.
readSms(index)|String|index is the position of the sms in the prefered memory storage
getNumberSms(index)|String|returns the number of the sms.
delAllSms()|bool|Delete all sms. If it returns true, there is an error.
signalQuality()|String|return info about signal quality
answerCall()|bool| If it returns true, there is an error.
callNumber(number)|None|
hangoffCall()|bool| If it returns true, there is an error.
getCallStatus()|uint8_t|Return the call status, 0=ready,2=Unknown(),3=Ringing,4=Call in progress
setPhoneFunctionality()|None|Set at to full functionality 
activateBearerProfile()|None|
deactivateBearerProfile()|None|
RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second)|None| Parameters must be reference ex: &day
dateNet()|String|Return date time GSM
updateRtc(utc)|bool|Return if the rtc was update with date time GSM. 
____________________________________________________________________________________



License
---

The Sim800L Arduino Library revised by Vittorio Esposito is open-source software and is licensed under the GPL-3.0 license.


Credits
---

Original version of the library by:   [Cristian Steib] (https://github.com/cristiansteib)
