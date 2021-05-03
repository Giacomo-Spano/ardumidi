#include <MIDI.h>

#include <driver/adc.h>


#define LED 13

MIDI_CREATE_DEFAULT_INSTANCE();

int sensorReading = 0;
const int knockSensor = 33;//A0; // the piezo is connected to analog pin 0
const int threshold = 500;  // threshold value to decide when the detected sound is a knock or not

void setup()
{
    Serial.begin(115200);

    //Serial.println("prova");

    
    

  MIDI.begin(1/*MIDI_CHANNEL_OFF*/);
}

int readSensorValue(){
  adc1_config_width(ADC_WIDTH_BIT_10);   //Range 0-1023 
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_6);  //ADC_ATTEN_DB_11 = 0-3,6V
  return adc1_get_raw( ADC1_CHANNEL_0 ); //Read analog
}


void loop()
{
  // read the sensor and store it in the variable sensorReading:
  //sensorReading = analogRead(knockSensor);
  sensorReading = readSensorValue();
  //sensorReading = adc1_get_raw(ADC1_CHANNEL_0);
  Serial.print("\nsensorReading = ");
  Serial.print(sensorReading, DEC);

  int voltage_value = (sensorReading * 3.3 ) / (4095);
  Serial.print(" Voltage = ");
  Serial.print(voltage_value);
  Serial.print(" volts ");



  // if the sensor reading is greater than the threshold:
  if (sensorReading >= threshold) {
    // send the string "Knock!" back to the computer, followed by newline
    //Serial.println("Knock!");
    //Serial.println(sensorReading, DEC);
    MIDI.sendNoteOn(42, 127, 1);
    delay(1000);		       
    MIDI.sendNoteOff(42, 0, 1);
  }
  delay(100);  // delay to avoid overloading the serial port buffer

  
  /*MIDI.sendNoteOn(42, 127, 1);
  delay(1000);		       
  MIDI.sendNoteOff(42, 0, 1);

  delay(1000);		    
  MIDI.sendNoteOn(97, 97, 1);
  delay(1000);		       
  MIDI.sendNoteOff(97, 0, 1);
  delay(1000);*/
}

