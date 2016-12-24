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

#include "Arduino.h"
#include "Sim800l.h"
#include <SoftwareSerial.h>

SoftwareSerial SIM(RX_PIN,TX_PIN);
//String _buffer;

void Sim800l::begin(){
	
	pinMode(RX_PIN, INPUT);
	pinMode(TX_PIN, OUTPUT);
	pinMode(RESET_PIN, OUTPUT);
	
	_baud = DEFAULT_BAUD_RATE;			// Default baud rate 9600
	SIM.begin(_baud);
	
	#if (LED_FLAG) 
		pinMode(LED_PIN, OUTPUT);
	#endif
	
	_buffer.reserve(BUFFER_RESERVE_MEMORY); // Reserve memory to prevent intern fragmention
}

void Sim800l::begin(uint32_t baud) {
		
	pinMode(RX_PIN, INPUT);
	pinMode(TX_PIN, OUTPUT);
	pinMode(RESET_PIN, OUTPUT);
	
	_baud = baud;
	SIM.begin(_baud);
	
	#if (LED_FLAG) 
		pinMode(LED_PIN, OUTPUT);
	#endif
	
	_buffer.reserve(BUFFER_RESERVE_MEMORY); // Reserve memory to prevent intern fragmention
}


//
//PRIVATE METHODS
//
String Sim800l::_readSerial(){
	
	uint64_t timeOld = millis();
	
	while (!SIM.available() && !(millis() > timeOld + TIME_OUT_READ_SERIAL)) {
		delay(13);
	}
	
	String replyString;
	
	while(SIM.available()) {
		if (SIM.available()>0) {
			replyString += (char) SIM.read();
		}
	}
	
	return replyString;
	
/*
	// Timeout:  12k * 13 = 156 seconds
	_timeout=0;
	while  (!SIM.available() && _timeout < 12000  ) 
	{
		delay(13);
		_timeout++;
	}
  
	// .readString() = 1 second to execute
	if (SIM.available()) {
		return SIM.readString();
	}
*/

}


//
//PUBLIC METHODS
//

void Sim800l::reset(){
  #if (LED_FLAG)
    digitalWrite(LED_PIN,1);
  #endif 
  digitalWrite(RESET_PIN,1);
  delay(1000);
  digitalWrite(RESET_PIN,0);
  delay(1000);
  // wait for the module response

  SIM.print(F("AT\r\n"));
  while (_readSerial().indexOf("OK")==-1 ){
    SIM.print(F("AT\r\n"));
  }
  
  //wait for sms ready
  while (_readSerial().indexOf("SMS")==-1 ){
  }
  #if (LED_FLAG)
    digitalWrite(LED_PIN,0);
  #endif 
}

void Sim800l::setPhoneFunctionality(){
  /*AT+CFUN=<fun>[,<rst>] 
  Parameters
  <fun> 0 Minimum functionality
  1 Full functionality (Default)
  4 Disable phone both transmit and receive RF circuits.
  <rst> 1 Reset the MT before setting it to <fun> power level.
  */
  SIM.print (F("AT+CFUN=1\r\n"));
}


void Sim800l::signalQuality(){
/*Response
+CSQ: <rssi>,<ber>Parameters
<rssi>
0 -115 dBm or less
1 -111 dBm
2...30 -110... -54 dBm
31 -52 dBm or greater
99 not known or not detectable
<ber> (in percent):
0...7 As RXQUAL values in the table in GSM 05.08 [20]
subclause 7.2.4
99 Not known or not detectable 
*/
  SIM.print (F("AT+CSQ\r\n"));
  Serial.println(_readSerial());
}


void Sim800l::activateBearerProfile(){
  SIM.print (F(" AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\" \r\n" ));_buffer=_readSerial();  // set bearer parameter 
  SIM.print (F(" AT+SAPBR=3,1,\"APN\",\"internet\" \r\n" ));_buffer=_readSerial();  // set apn  
  SIM.print (F(" AT+SAPBR=1,1 \r\n"));delay(1200);_buffer=_readSerial();			// activate bearer context
  SIM.print (F(" AT+SAPBR=2,1\r\n "));delay(3000);_buffer=_readSerial(); 			// get context ip address
}


void Sim800l::deactivateBearerProfile(){
  SIM.print (F("AT+SAPBR=0,1\r\n "));
  delay(1500);
}



bool Sim800l::answerCall(){
   SIM.print (F("ATA\r\n"));
   _buffer=_readSerial();
   //Response in case of data call, if successfully connected 
   if ( (_buffer.indexOf("OK") )!=-1 ) return true;  
   else return false;
}


void  Sim800l::callNumber(char* number){
  SIM.print (F("ATD"));
  SIM.print (number);
  SIM.print (F("\r\n"));
}



uint8_t Sim800l::getCallStatus(){
/*
  values of return:
 
 0 Ready (MT allows commands from TA/TE)
 2 Unknown (MT is not guaranteed to respond to tructions)
 3 Ringing (MT is ready for commands from TA/TE, but the ringer is active)
 4 Call in progress

*/
  SIM.print (F("AT+CPAS\r\n"));
  _buffer=_readSerial();  
  return _buffer.substring(_buffer.indexOf("+CPAS: ")+7,_buffer.indexOf("+CPAS: ")+9).toInt();

}



bool Sim800l::hangoffCall(){
  SIM.print (F("ATH\r\n"));
  _buffer=_readSerial();
  if ( (_buffer.indexOf("OK") ) != -1) return true;
  else return false;
}






bool Sim800l::sendSms(char* number,char* text){

    SIM.print (F("AT+CMGF=1\r")); 	//set sms to text mode  
    _buffer=_readSerial();
    SIM.print (F("AT+CMGS=\""));  	// command to send sms
    SIM.print (number);           
    SIM.print(F("\"\r"));       
    _buffer=_readSerial(); 
    SIM.print (text);
    SIM.print ("\r"); 
	//change delay 100 to readserial	
    _buffer=_readSerial();
    SIM.print((char)26);
    _buffer=_readSerial();
    //expect CMGS:xxx   , where xxx is a number,for the sending sms.
    if (((_buffer.indexOf("CMGS") ) != -1 ) ){
      return true;
    }
    else {
      return false;
    }
}


String Sim800l::getNumberSms(uint8_t index){
  _buffer=readSms(index);
  Serial.println(_buffer.length());
  if (_buffer.length() > 10) //avoid empty sms
  {
    uint8_t _idx1=_buffer.indexOf("+CMGR:");
    _idx1=_buffer.indexOf("\",\"",_idx1+1);
    return _buffer.substring(_idx1+3,_buffer.indexOf("\",\"",_idx1+4));
  }else{
    return "";
  }
}



String Sim800l::readSms(uint8_t index){
  SIM.print (F("AT+CMGF=1\r")); 
  if (( _readSerial().indexOf("ER")) ==-1) {
    SIM.print (F("AT+CMGR="));
    SIM.print (index);
    SIM.print("\r");
    _buffer=_readSerial();
    if (_buffer.indexOf("CMGR:")!=-1){
      return _buffer;
    }
    else return "";    
    }
  else
    return "";
}


bool Sim800l::delAllSms(){ 
  SIM.print(F("at+cmgda=\"del all\"\n\r"));
  _buffer=_readSerial();
  if (_buffer.indexOf("OK")!=-1) {return true;}else {return false;}
  
}


void Sim800l::RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second){
  SIM.print(F("at+cclk?\r\n"));
  // if respond with ERROR try one more time. 
  _buffer=_readSerial();
  if ((_buffer.indexOf("ERR"))!=-1){
    delay(50);
    SIM.print(F("at+cclk?\r\n"));
  } 
  if ((_buffer.indexOf("ERR"))==-1){
    _buffer=_buffer.substring(_buffer.indexOf("\"")+1,_buffer.lastIndexOf("\"")-1);  
    *year=_buffer.substring(0,2).toInt();
    *month= _buffer.substring(3,5).toInt();
    *day=_buffer.substring(6,8).toInt();
    *hour=_buffer.substring(9,11).toInt();
    *minute=_buffer.substring(12,14).toInt();
    *second=_buffer.substring(15,17).toInt();
 }
}

//Get the time  of the base of GSM
String Sim800l::dateNet() {
  SIM.print(F("AT+CIPGSMLOC=2,1\r\n "));
  _buffer=_readSerial();

  if (_buffer.indexOf("OK")!=-1 ){
    return _buffer.substring(_buffer.indexOf(":")+2,(_buffer.indexOf("OK")-4));
  } else
  return "0";      
}

// Update the RTC of the module with the date of GSM. 
bool Sim800l::updateRtc(int utc){
  
  activateBearerProfile();
  _buffer=dateNet();
  deactivateBearerProfile();
  
  _buffer=_buffer.substring(_buffer.indexOf(",")+1,_buffer.length());
  String dt=_buffer.substring(0,_buffer.indexOf(","));
  String tm=_buffer.substring(_buffer.indexOf(",")+1,_buffer.length()) ;

  int hour = tm.substring(0,2).toInt();
  int day = dt.substring(8,10).toInt();

  hour=hour+utc;

  String tmp_hour;
  String tmp_day;
  //TODO : fix if the day is 0, this occur when day is 1 then decrement to 1, 
  //       will need to check the last month what is the last day .  
  if (hour<0){
    hour+=24;
    day-=1;
  }
  if (hour<10){

      tmp_hour="0"+String(hour);
  }else{
    tmp_hour=String(hour);
  }
  if (day<10){
    tmp_day="0"+String(day);    
  }else{
    tmp_day=String(day);
  }
    //for debugging
  //Serial.println("at+cclk=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n");
  SIM.print("at+cclk=\""+dt.substring(2,4)+"/"+dt.substring(5,7)+"/"+tmp_day+","+tmp_hour+":"+tm.substring(3,5)+":"+tm.substring(6,8)+"-03\"\r\n");
  if ( (_readSerial().indexOf("ER"))!=-1) {return false;}else return true;

   
  }
