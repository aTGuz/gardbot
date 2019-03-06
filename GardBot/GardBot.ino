/*

GarBot

*/




#include "BIB/Main/Gardbot_GeneralIncludes.h" 




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  EXECUTION PROCS
//  ===============
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void EXEC_INITIALIZE()
{
    if (gRendered_INITIALIZE == false)
    {
        LogTerm(F("== [Actual Mode: INITIALIZE] =="));

        gRendered_INITIALIZE = true;
    }  

    gOperation_Mode = F("LOGDATA");
}

void EXEC_OPERATION()
{
    if (gRendered_OPERATION == false)
    {
        LogTerm(F("== [Actual Mode: OPERATION] =="));

        gRendered_OPERATION = true;
    }     
}

void EXEC_LOGDATA()
{
    if (gRendered_LOGDATA == false)
    {
        LogTerm(F("== [Actual Mode: LOGDATA] =="));

        gRendered_LOGDATA = true;
    }     


    if (LOG_IsLogTime())
    {
        //LogTerm(RTC_Now() + String(F(" - Do Log !"))); 

        RunAllSensorsTest();

    }


}


void RunAllSensorsTest()
{

    LogTerm(F("--------------------------------------------------------------"));

    //LogTerm(F("aqui"));

    LogTerm(String(F("RTC_Now:                            ")) + RTC_Now());

    LogTerm(String(F("SoilSensor_GetSoilHumidity =        ")) + String(SoilSensor_GetSoilHumidity()));

    LogTerm(String(F("LightSensor_GetAmbientLightValue =  ")) + String(LightSensor_GetAmbientLightValue()));

    LogTerm(String(F("TEMPHUM_ReadAirHumidity:            ")) + TEMPHUM_ReadAirHumidity());

    LogTerm(String(F("TEMPHUM_ReadAirTemperature:         ")) + TEMPHUM_ReadAirTemperature());


    String ret = F("");

    ret = SD_ApagaArquivo(String(F("oplkjuhf.txt")));

    if (Left(ret, 36) == F("0|Nao foi possivel apagar o arquivo:"))
    {
        LogTerm(String(F("SD Test:                            SUCESSO!")));
    }
    else
    {
        LogTerm(String(F("SD Test:                            ERRO: ")) + ret);
    }







}

void TestInterrupts()
{
    
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  MAIN ARDUINO
//  ============
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void setup()
{  

    Serial.begin(115200);     

    InitiateVars();  

    LogTerm (F("Garbot 1.0"));
    LogTerm (F("=========="));
    LogTerm (F(""));


    //RTC_SetCurrentDateTime(16, 2, 2019, 23, 42, 0, 6); // sabado 6


    // initiate sd card
    digitalWrite(SD_PINO, HIGH);

    // Inicia o BUZZER
    pinMode(BUZZER_PINO, OUTPUT);


    CORE_ExecDefinePlantsFromSD();

    delay(1000);


}





// INTERNA ARDUINO: LOOP ETERNO
void loop() 
{


    //delay(50);


    if (gOperation_Mode == F("INITIALIZE"))
    {
        EXEC_INITIALIZE();
    }

    if (gOperation_Mode == F("OPERATION"))
    {
        EXEC_OPERATION();
    }

    if (gOperation_Mode == F("LOGDATA"))
    {
        EXEC_LOGDATA();
    }


    TestInterrupts();



    /*

    LogTerm(F("--------------------------------------------------------------"));

    
    LogTerm(String(F("RTC_Now:                            ")) + RTC_Now());

    LogTerm(String(F("SoilSensor_GetSoilHumidity =        ")) + String(SoilSensor_GetSoilHumidity()));

    LogTerm(String(F("LightSensor_GetAmbientLightValue =  ")) + String(LightSensor_GetAmbientLightValue()));

    LogTerm(String(F("TEMPHUM_ReadAirHumidity:            ")) + TEMPHUM_ReadAirHumidity());

    LogTerm(String(F("TEMPHUM_ReadAirTemperature:         ")) + TEMPHUM_ReadAirTemperature());


    String ret = F("");

    ret = SD_ApagaArquivo(String(F("teste.txt")));

    LogTerm(String(F("SD_ApagaArquivo: ")) + ret);

    BUZZER_TocaSom(F("SUCESSO"));

    */

    
    
}





//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////









