


long SoilSensor_GetSoilHumidity() 
{

	long sensorValue1 = -1;
	long FinalSensorValue = -1;

    int CountRead = 0;

    int TotalReadTimesForAvg = 100;

    long SumReadValue = 0;

    

    while ((CountRead <= 100) && (FinalSensorValue <= 0))
    {
        CountRead++;


        int x = 1;

        while (x <= TotalReadTimesForAvg)
        {
            sensorValue1 = -1;

            sensorValue1 = analogRead(SOIL_SENSOR);

            if (sensorValue1 >= 1)
            {
                SumReadValue += sensorValue1;
                x++;
            }
        }


        FinalSensorValue = SumReadValue / TotalReadTimesForAvg + 1;

        //LogTerm(String(F("CountRead = ")) + String(CountRead) + String(F(" | sensorValue1 = ")) + String(sensorValue1));

    }

    return FinalSensorValue;
    
}


