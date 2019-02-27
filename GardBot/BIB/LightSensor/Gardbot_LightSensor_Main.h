



long LightSensor_GetAmbientLightValue() 
{

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

            sensorValue1 = analogRead(LIGHT_SENSOR_PINO);

            if (sensorValue1 >= 1)
            {
                SumReadValue += sensorValue1;
                x++;
            }
        }



        FinalSensorValue = SumReadValue / TotalReadTimesForAvg;

        //LogTerm(String(F("CountRead = ")) + String(CountRead) + String(F(" | sensorValue1 = ")) + String(sensorValue1));

    }

    return FinalSensorValue;
   
}





