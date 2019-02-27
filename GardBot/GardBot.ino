/*

GarBot

*/




#include "BIB/Main/Gardbot_GeneralIncludes.h" 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  INTERNAS ARDUINO
//  ================
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



// INTERNA ARDUINO: SETUP
void setup()
{  

    Serial.begin(115200);       

    LogTerm (F("Garbot 1.0"));
    LogTerm (F("=========="));
    LogTerm (F(""));


    //RTC_SetCurrentDateTime(16, 2, 2019, 23, 42, 0, 6); // sabado 6


    // initiate sd card
    digitalWrite(SD_PINO, HIGH);

    // Inicia o BUZZER
    pinMode(BUZZER_PINO, OUTPUT);



    delay(1000);


}


// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{



    LogTerm(String(F("SoilSensor_GetSoilHumidity = ")) + String(SoilSensor_GetSoilHumidity()));

    //LogTerm(String(F("LightSensor_GetAmbientLightValue = ")) + String(LightSensor_GetAmbientLightValue()));

    //LogTerm(F("------------------"));


    //delay(500);

    //LogTerm(String(F("Humidity: ")) + TEMPHUM_ReadAirHumidity());

    //LogTerm(String(F("Temperature: ")) + TEMPHUM_ReadAirTemperature());


    /*
    //RTC_ShowCurrentDateTimeToSerial();

    //delay(1000);

    LogTerm(RTC_Now());

    delay(1000);
    
    //SD_TestaCartao();


    String ret = F("");


    ret = SD_ApagaArquivo(String(F("teste.txt")));

    LogTerm(ret);

    delay(1000);

    BUZZER_TocaSom(F("SUCESSO"));

    delay(1000);

    LogTerm(String(F("Humidity: ")) + TEMPHUM_ReadAirHumidity());

    LogTerm(String(F("Temperature: ")) + TEMPHUM_ReadAirTemperature());

    if (gOperation_Mode == F("STANDBY"))
    {

    }
    */




    
}














