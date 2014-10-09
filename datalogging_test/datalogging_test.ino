/*Sketch to test the Adafruit datalogging shield
  Adapted from http://www.ladyada.net/make/logshield/lighttemp.html
  */

#define aref_voltage 3.3         // we tie 3.3V to ARef and measure it with a multimeter!

int photocellPin = 0;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the analog resistor divider

//Differently than in the Adafruit circuit example, the temp sensor here is a thermistor
int tempPin = 1;        // V_out from the thermistor voltage divider is connected to a1
int tempReading;        // the analog reading from the sensor

// This function will map measured voltage from the lookup table
// source: http://playground.arduino.cc/Main/MultiMap
// note: the _in array should have increasing values
float FmultiMap(float val, float * _in, float * _out, uint8_t size)
{
  // take care the value is within range
  // val = constrain(val, _in[0], _in[size-1]);
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];

  // search right interval
  uint8_t pos = 1;  // _in[0] allready tested
  while(val > _in[pos]) pos++;

  // this will handle all exact "points" in the _in array
  if (val == _in[pos]) return _out[pos];

  // interpolate in the right segment for the rest
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}

// Voltage-temperature table calculated in thermistor-values.xlsx
// using B-parameter approximation
// TODO: make a python / shell script to generate larger, more precise lookup table
float voltage_values[]={0,0.01,0.01,0.01,0.02,0.02,0.04,0.05,0.07,0.09,0.13,0.17,0.22,0.28,0.36,0.45,0.55,0.67,0.8,0.94,1.09,1.25,1.41,1.57,1.73,1.88,2.03,2.16,2.28,2.4,2.5,2.59,2.67,2.74,2.81,2.86,2.91};
float temp_values[]={-55,-50,-45,-40,-35,-30,-25,-20,-15,-10,-5,0,5,10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85,90,95,100,105,110,115,120,125};
    
void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   

  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);
}


void loop(void) {
  photocellReading = analogRead(photocellPin);  
  
  Serial.print("Light reading = ");
  Serial.print(photocellReading);     // the raw analog reading
  
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    Serial.println(" - Dark");
  } else if (photocellReading < 200) {
    Serial.println(" - Dim");
  } else if (photocellReading < 500) {
    Serial.println(" - Light");
  } else if (photocellReading < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  
  tempReading = analogRead(tempPin);  
  
  Serial.print("Temp reading = ");
  Serial.print(tempReading);     // the raw analog reading
  
  // converting that reading to voltage, which is based off the reference voltage
  float voltage = tempReading * aref_voltage / 1024; 
 
  // print out the voltage
  Serial.print(" - ");
  Serial.print(voltage); Serial.println(" volts");
 
  // now print out the temperature
  
  float temperatureC;
  temperatureC = FmultiMap((float)voltage, voltage_values, temp_values, 37);
  
  Serial.print(temperatureC); Serial.println(" degrees C");
 

 
  delay(1000);
}

