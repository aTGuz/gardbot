

// RTC
#define RTC_CLK		7
#define RTC_DATA	6
#define RTC_RST		5



// SD
#define SD_MAX_TENTATIVA_READ 	2
#define SD_DELAY_TENTATIVA_READ 1000
#define SD_PINO 				53


// define the debug mode
#define ctDEBUG_MODE false

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



void InitiateVars()
{

	gOperation_Mode = F("");


	gOperation_Mode = F("STANDBY");
}