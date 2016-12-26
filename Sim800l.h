/*
*  This library was written by  Cristian Steib.
 *      steibkhriz@gmail.com
 *
 * Revised by:
 * 		Vittorio Esposito	-	https://github.com/VittorioEsposito
 *
 *
 *  Designed to work with the GSM Sim800l.
 *
 *  ENG
 *     	This library uses SoftwareSerial, you can define RX and TX pins
 *     	in the header "Sim800l.h", by default pins are RX=10 and TX=11.
 *     	Be sure that GND is connected to arduino too.
 *     	You can also change the RESET_PIN as you prefer.
 *
 *	ESP
 *     	Esta libreria usa SoftwareSerial, se pueden cambiar los pines de RX y TX
 *     	en el archivo header, "Sim800l.h", por defecto los pines vienen configurado en
 *     	RX=10 TX=11.
 *     	Tambien se puede cambiar el RESET_PIN por otro que prefiera
 *
 *	ITA
 *		Questa libreria utilizza la SoftwareSerial, si possono cambiare i pin di RX e TX
 *      dall' intestazione "Sim800l.h", di default essi sono impostati come RX=10 RX=11
 *		Assicurarsi di aver collegato il dispositivo al pin GND di Arduino.
 *		E' anche possibile cambiare il RESET_PIN.
 *
 *
 *    PINOUT:
 *        _____________________________
 *       |  ARDUINO UNO >>>   SIM800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  10       >>>   TX
 *        TX  11       >>>   RX
 *       RESET 2       >>>   RST
 *
 *   POWER SOURCE 4.2V >>> VCC
 *
 *
 *	SOFTWARE SERIAL NOTES:
 *
 *		PINOUT
 *		The library has the following known limitations:
 *		1. If using multiple software serial ports, only one can receive data at a time.
 *		2. Not all pins on the Mega and Mega 2560 support change interrupts, so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), A13 (67), A14 (68), A15 (69).
 *		3. Not all pins on the Leonardo and Micro support change interrupts, so only the following can be used for RX: 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 *		4. On Arduino or Genuino 101 the current maximum RX speed is 57600bps
 *		5. On Arduino or Genuino 101 RX doesn't work on Pin 13
 *
 *		BAUD RATE
 *		Supported baud rates are 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 31250, 38400, 57600, and 115200.
 *
 *
 *	Created on:  April 20, 2016
 *  	Author:  Cristian Steib
 *		Reviser: Vittorio Esposito
 *
 *
*/

#ifndef Sim800l_h
#define Sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"


#define RX_PIN 		10
#define TX_PIN 		11
#define RESET_PIN 	2		// pin to the reset pin sim800l

#define LED_FLAG	true 	// true: use led.	 false: don't user led.
#define LED_PIN 	13 		// pin to indicate states.

#define BUFFER_RESERVE_MEMORY	255
#define DEFAULT_BAUD_RATE		9600
#define TIME_OUT_READ_SERIAL	60000


class Sim800l
{
private:

    uint32_t _baud;
    int _timeout;
    String _buffer;
    bool _sleepMode;
    uint8_t _functionalityMode;

    String _readSerial();


public:

    void begin();				//Default baud 9600
    void begin(uint32_t baud);
    void reset();

    bool setSleepMode(bool state);
    bool getSleepMode();
    bool setFunctionalityMode(uint8_t fun);
    uint8_t getFunctionalityMode();

    bool setPIN(String pin);
    String getProductInfo();

    String getOperatorsList();
    String getOperator();

    // Methods for callinG
    bool answerCall();
    void callNumber(char* number);
    bool hangoffCall();
    uint8_t getCallStatus();
    //Methods for sms
    bool sendSms(char* number,char* text);
    String readSms(uint8_t index); 			//return all the content of sms
    String getNumberSms(uint8_t index); 	//return the number of the sms..
    bool delAllSms();     					// return :  OK or ERROR ..


    void signalQuality();
    void setPhoneFunctionality();
    void activateBearerProfile();
    void deactivateBearerProfile();
    //get time with the variables by reference
    void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);
    String dateNet(); //return date,time, of the network
    bool updateRtc(int utc);  //Update the RTC Clock with de Time AND Date of red-.

};

#endif
