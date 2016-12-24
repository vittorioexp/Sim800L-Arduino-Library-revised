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

#include <Sim800l.h>
#include <SoftwareSerial.h> //is necesary for the library!! 
Sim800l Sim800l;  //to declare the library



String textSms,numberSms;
uint8_t index1;
uint8_t LED2=13; // use what you need 
bool error;



void setup(){
 
pinMode(LED2,OUTPUT); 
digitalWrite(LED2,HIGH);

    Serial.begin(9600); // only for debug the results . 
    Sim800l.begin(); // initializate the library. 
    Sim800l.reset();
    //don't forget to catch the return of the function delAllSms! 
    error=Sim800l.delAllSms(); //clean memory of sms;
    
}

void loop(){
    textSms=Sim800l.readSms(1); //read the first sms
    
    if (textSms.indexOf("OK")!=-1) //first we need to know if the messege is correct. NOT an ERROR
        {           
        if (textSms.length() > 7)  // optional you can avoid SMS empty
            {
                
                numberSms=Sim800l.getNumberSms(1);  // Here you have the number
                //for debugin
                Serial.println(numberSms); 
                textSms.toUpperCase();  // set all char to mayus ;)

                if (textSms.indexOf("TURNON")!=-1){
                    Serial.println("LED TURN ON");
                    digitalWrite(LED2,1);
                }
                else if (textSms.indexOf("TURNOFF")!=-1){
                    Serial.println("LED TURN OFF");
                    digitalWrite(LED2,0);

                }
                else{
                    Serial.println("Not Compatible ...sorry.. :D");
                }


            Sim800l.delAllSms(); //do only if the message is not empty,in other case is not necesary
             //delete all sms..so when receive a new sms always will be in first position
            } 



        }
    }
 