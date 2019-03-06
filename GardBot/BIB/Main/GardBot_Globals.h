

// RTC

// IMPORTANT OBSERVATION: Im using brazilian date format (DD/MM/YYYY) because... im brazilian.
// Any date in the system is currently being presented in the above format.
// TODO: Make the date be any format we want, link american or brazilian
#define RTC_CLK		7
#define RTC_DATA	6
#define RTC_RST		5



// SD
#define SD_MAX_TENTATIVA_READ 	2
#define SD_DELAY_TENTATIVA_READ 1000
#define SD_PINO 				53


// define the debug mode
#define ctDEBUG_MODE true

// Buzzer
#define BUZZER_PINO 32

// DHT11 - Temp and Hum sensor
#define DHT11_PINO 22


// photoresistor sensor
#define LIGHT_SENSOR_PINO A0

// Soil Moisture and Temp Sensor
#define SOIL_SENSOR A1


// State tracking var
String gOperation_Mode;

// vars that check if screen is rendered for a particular operation mode
// also can be used to check if its the first time a operational mode is reached
bool gRendered_INITIALIZE;
bool gRendered_OPERATION;
bool gRendered_LOGDATA;



// log at every 1S, 10S, 30S, 1M, 1H, 1D , etc. S = seconds, M = minutes, H = hours, D = Days
String gLOG_LogAtEvery;

String gLOG_LastLogDateTime;



// max number of plants controled by the system
#define ctMAX_PLANTS 4 // total number, as read by humans. If it says 4 then there are exactly plants (doesnt start in zero)
String gaPlants[ctMAX_PLANTS];




void InitiateVars()
{
	gOperation_Mode = F("INITIALIZE");


	gRendered_INITIALIZE = false;
	gRendered_OPERATION = false;
	gRendered_LOGDATA = false;

	// Loggins vars
	gLOG_LogAtEvery = F("3S");
	gLOG_LastLogDateTime = F("-1");


	// main array with the plants controled
	for (int x = 0 ; x <= ctMAX_PLANTS ; x++)
	{
		gaPlants[x] = F("");
	}	 

}