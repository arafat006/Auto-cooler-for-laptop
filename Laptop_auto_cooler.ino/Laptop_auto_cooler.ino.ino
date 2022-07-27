#include <OneWire.h>
#include <DallasTemperature.h>

const int SensorDigitalPort = 2; // Arduino pin connected to DS18B20 sensor's DQ pin
const int RelayDigitalPort = 3; 

OneWire oneWire(SensorDigitalPort);         // setup a oneWire instance
DallasTemperature tempSensor(&oneWire); // pass oneWire to DallasTemperature library

float tempCelsius;    // temperature in Celsius
float tempFahrenheit; // temperature in Fahrenheit

void setup()
{
  Serial.begin(9600); // initialize serial
  tempSensor.begin();    // initialize the sensor
  pinMode(RelayDigitalPort, OUTPUT);
  digitalWrite(RelayDigitalPort, HIGH);
}

void loop()
{
  tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius

  if(validTemparature(tempCelsius))
  {
    if(tempCelsius > 37.0)
    {
      Serial.println("Okay");
      digitalWrite(RelayDigitalPort, LOW);
    }
    else if(tempCelsius < 35.0)
    {
      digitalWrite(RelayDigitalPort, HIGH);
    }
  
    Serial.print("Temperature: ");
    Serial.print(tempCelsius);
    Serial.print((char)176);
    Serial.println();
  }
   
  delay(5000);
}


bool validTemparature(int tempValue)
{
  if(-10 < tempValue && tempValue < 110 )
  {
    return true;
  }
  return false;
}


