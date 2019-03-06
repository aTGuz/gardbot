


// gardbot main includes
#include "GardBot_Globals.h" 
#include "GardBot_Support.h" 



// RTC
#include "../RTC/RTC_Krodal.h" 
#include "../RTC/RTC_Main.h" 



// SPI:
#include <SPI.h>

// SD
// LEITOR SD Adafruit - Engine
//#include <SdFat.h>
#include "../SD/SDFat/src/SdFat.h" 

// LEITOR SD MAIN
#include "../SD/Gardbot_SD_Main.h" 

// database - MAIN
#include "../Database/Gardbot_Database_Main.h" 

// buzzer
#include "../Buzzer/Gardbot_Buzzer_Main.h" 

// Core functions -- todo: do we really need an include with core funcs ? 
// Doing this because its how i did in other project of mine, and i just copied the code
#include "Gardbot_CoreFunctions.h" 




// temp and hum sensor dht11
#include "DHT.h"
#include "../DHT11/Gardbot_TempHum_Main.h" 

// soil sensor
#include "../SoilSensor/Gardbot_SoilSensor_Main.h" 


// light sensor
#include "../LightSensor/Gardbot_LightSensor_Main.h" 


// Logging functions
#include "../LOG/Gardbot_LOG_Main.h" 


