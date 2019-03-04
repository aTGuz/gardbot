



bool LOG_IsLogTime()
{

	//gLOG_LogAtEvery

	bool ret = false;


	String Now = RTC_Now();

	int Part_Now = -1;
	int Part_LastLog = -1;

	//gLOG_LogAtEvery = F("1S");

	if (gLOG_LastLogDateTime == F("-1"))
	{
		gLOG_LastLogDateTime = Now;
		ret = true;
	}
	else
	{

		/*
		if (gLOG_LogAtEvery == F("1S"))
		{
			Part_Now = Right(Now, 2).toInt();
			Part_LastLog = Right(gLOG_LastLogDateTime, 2).toInt();

			if (Part_Now != Part_LastLog)
			{
				ret = true;
			}
			else
			{
				ret = false;
			}

		}	
		*/

		if (gLOG_LogAtEvery == F("1M"))
		{
			Part_Now = Left(Right(Now, 5), 2).toInt();
			Part_LastLog = Left(Right(gLOG_LastLogDateTime, 5), 2).toInt();

			if (Part_Now != Part_LastLog)
			{
				ret = true;
			}
			else
			{
				ret = false;
			}

		}	

		if ( (gLOG_LogAtEvery == F("1S")) || (gLOG_LogAtEvery == F("3S")) || (gLOG_LogAtEvery == F("5S")) || (gLOG_LogAtEvery == F("10S")) || (gLOG_LogAtEvery == F("30S")) )
		{

			int Mult = 1;

			if (gLOG_LogAtEvery == F("1S"))
			{
				Mult = 1;
			}

			if (gLOG_LogAtEvery == F("3S"))
			{
				Mult = 3;
			}

			if (gLOG_LogAtEvery == F("5S"))
			{
				Mult = 5;
			}

			if (gLOG_LogAtEvery == F("10S"))
			{
				Mult = 10;
			}

			if (gLOG_LogAtEvery == F("30S"))
			{
				Mult = 30;
			}

			Part_Now = Right(Now, 2).toInt();
			Part_LastLog = Right(gLOG_LastLogDateTime, 2).toInt();

			if (Part_Now != Part_LastLog)
			{
				if (Part_Now % Mult == 0)
				{
					ret = true;
				}
				else
				{
					ret = false;
				}
			}
			else
			{
				ret = false;
			}



		}	


		gLOG_LastLogDateTime = Now;
	}



	//gLOG_LastLogDateTime

	return ret;
}