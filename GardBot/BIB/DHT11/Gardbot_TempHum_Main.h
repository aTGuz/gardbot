


//extern String TEMPHUM_ReadAirHumidity();
//extern String TEMPHUM_ReadAirTemperature();


// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor



#define DHTPIN DHT11_PINO     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor






long TEMPHUM_ReadAirHumidity() 
{

    delay(200);


    // Initialize DHT sensor.
    // Note that older versions of this library took an optional third parameter to
    // tweak the timings for faster processors.  This parameter is no longer needed
    // as the current DHT reading algorithm adjusts itself to work on faster procs.
    DHT dht(DHTPIN, DHTTYPE);


    // initiate Temp and Hum sensor
    dht.begin();


    long sensorValue1 = -1;
    long FinalSensorValue = -1;

    int CountRead = 0;

    int TotalReadTimesForAvg = 10;

    long SumReadValue = 0;

    

    while ((CountRead <= 100) && (FinalSensorValue <= 0))
    {
        CountRead++;


        int x = 1;

        while (x <= TotalReadTimesForAvg)
        {
            sensorValue1 = -1;

            // Reading temperature or humidity takes about 250 milliseconds!
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h = dht.readHumidity();

            // Check if any reads failed and exit early (to try again).
            if (isnan(h)) 
            {
                LogTerm(F("Read Air humidity failed"));
            }
            else
            {
                SumReadValue += (float) h;
                x++;
            }


        }


        FinalSensorValue = SumReadValue / TotalReadTimesForAvg;

        //LogTerm(String(F("CountRead = ")) + String(CountRead) + String(F(" | sensorValue1 = ")) + String(sensorValue1));

    }

    return FinalSensorValue;
    
}





long TEMPHUM_ReadAirTemperature() 
{
    
    delay(200);


    // Initialize DHT sensor.
    // Note that older versions of this library took an optional third parameter to
    // tweak the timings for faster processors.  This parameter is no longer needed
    // as the current DHT reading algorithm adjusts itself to work on faster procs.
    DHT dht(DHTPIN, DHTTYPE);


    // initiate Temp and Hum sensor
    dht.begin();


    long sensorValue1 = -1;
    long FinalSensorValue = -1;

    int CountRead = 0;

    int TotalReadTimesForAvg = 10;

    long SumReadValue = 0;

    

    while ((CountRead <= 100) && (FinalSensorValue <= 0))
    {
        CountRead++;


        int x = 1;

        while (x <= TotalReadTimesForAvg)
        {
            sensorValue1 = -1;

            // Reading temperature or humidity takes about 250 milliseconds!
            // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
            float h = dht.readTemperature();

            // Check if any reads failed and exit early (to try again).
            if (isnan(h)) 
            {
                LogTerm(F("Read temperature failed"));
            }
            else
            {
                SumReadValue += (float) h;
                x++;
            }


        }


        FinalSensorValue = SumReadValue / TotalReadTimesForAvg;

        //LogTerm(String(F("CountRead = ")) + String(CountRead) + String(F(" | sensorValue1 = ")) + String(sensorValue1));

    }

    return FinalSensorValue;
    
    
}








