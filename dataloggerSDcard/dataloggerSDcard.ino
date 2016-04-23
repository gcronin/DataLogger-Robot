/*
AttoPilot Current and Voltage Sensing Demo
N.Poole, Sparkfun Electronics, 2011

"I don't care what you do with it, and neither does the script." (apathyware)

Physical Connections:
-------------------------
Arduino  | Peripherals
-------- | --------------
Pin 3  --- SerLCD "RX"
Pin A0 --- AttoPilot "V"
Pin A1 --- AttoPilot "I"
GND ------ AttoPilot "GND"
GND ------ SerLCD "GND"
5V ------- SerLCD "VCC"

This demo will read the Voltage and Current from the "AttoPilot Voltage and Current Sense Board,"
convert the raw ADC data to Volts and Amps and display them as floating point numbers on the
Serial Enabled LCD. (If you would like to do without the Serial LCD, I have included commented code
for reading the results through the Serial Terminal.)

*/
#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;
const int errorSDCardLED = 6;
const int powerLED = 5;
const int writeToFileLED = 4;
const int errorDataFileLED = 7;

int VRaw; //This will store our raw ADC data
int IRaw;
float VFinal; //This will store the converted data
float IFinal;

void setup() {

digitalWrite(errorDataFileLED, LOW);
digitalWrite(powerLED, HIGH);  // power LED
digitalWrite(writeToFileLED, LOW);
digitalWrite(errorSDCardLED, LOW);

Serial.begin(9600);
Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    digitalWrite(errorSDCardLED, HIGH);  //red light comes on if no card.
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

}


void loop() { 

  String dataString = "";
  
  //Measurement
  VRaw = analogRead(A0);
  IRaw = analogRead(A1);
  

  
  //Conversion
  VFinal = VRaw/49.44; //45 Amp board
  //VFinal = VRaw/12.99; //90 Amp board
  //VFinal = VRaw/12.99; //180 Amp board  
  
  IFinal = IRaw/14.9; //45 Amp board
  //IFinal = IRaw/7.4; //90 Amp board
  //IFinal = IRaw/3.7; //180 Amp board

  dataString = String(millis());
  dataString += ", ";
  dataString += String(VFinal);
  dataString += ", ";
  dataString += String(IFinal);

  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
    toggle(writeToFileLED);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    digitalWrite(errorDataFileLED, HIGH);
    
  }
  delay(200);
  
  
}

void toggle(int pin)
{
  digitalWrite(pin, !digitalRead(pin));
}
