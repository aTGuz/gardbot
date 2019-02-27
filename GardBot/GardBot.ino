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



    LogTerm(String(F("SoilSensor_GetSoilHumidity =        ")) + String(SoilSensor_GetSoilHumidity()));

    LogTerm(String(F("LightSensor_GetAmbientLightValue =  ")) + String(LightSensor_GetAmbientLightValue()));

    LogTerm(String(F("TEMPHUM_ReadAirHumidity:            ")) + TEMPHUM_ReadAirHumidity());

    LogTerm(String(F("TEMPHUM_ReadAirTemperature:         ")) + TEMPHUM_ReadAirTemperature());

    LogTerm(String(F("RTC_Now:                            ")) + RTC_Now());



    String ret = F("");

    ret = SD_ApagaArquivo(String(F("teste.txt")));

    LogTerm(String(F("SD_ApagaArquivo: ")) + ret);

    BUZZER_TocaSom(F("SUCESSO"));

    LogTerm(F("------------------------------------------------------"));


    //delay(500);

    

    
    
}














