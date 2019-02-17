
#include "RTC_Krodal.h" 





void RTC_SetCurrentDateTime(int dayofmonth, int month, int year, int hours, int minutes, int seconds, int dayofweek)
{


	/*
	// Fill these variables with the date and time
	// Example for april 15, 2013, 10:08, monday is 2nd day of Week.
	// Set your own time and date in these variables.
	seconds    = 0;
	minutes    = 8;
	hours      = 10;
	dayofweek  = 2;  // Day of week, any day can be first, counts 1...7
	dayofmonth = 15; // Day of month, 1...31
	month      = 4;  // month 1...12
	year       = 2013;
	*/

	// Set a time and date
	// This also clears the CH (Clock Halt) bit, 
	// to start the clock.

	// Fill the structure with zeros to make 
	// any unused bits zero

	ds1302_struct rtc;


	memset ((char *) &rtc, 0, sizeof(rtc));

	rtc.Seconds    = bin2bcd_l( seconds);
	rtc.Seconds10  = bin2bcd_h( seconds);
	rtc.CH         = 0;      // 1 for Clock Halt, 0 to run;
	rtc.Minutes    = bin2bcd_l( minutes);
	rtc.Minutes10  = bin2bcd_h( minutes);
	// To use the 12 hour format,
	// use it like these four lines:
	//    rtc.h12.Hour   = bin2bcd_l( hours);
	//    rtc.h12.Hour10 = bin2bcd_h( hours);
	//    rtc.h12.AM_PM  = 0;     // AM = 0
	//    rtc.h12.hour_12_24 = 1; // 1 for 24 hour format
	rtc.h24.Hour   = bin2bcd_l( hours);
	rtc.h24.Hour10 = bin2bcd_h( hours);
	rtc.h24.hour_12_24 = 0; // 0 for 24 hour format
	rtc.Date       = bin2bcd_l( dayofmonth);
	rtc.Date10     = bin2bcd_h( dayofmonth);
	rtc.Month      = bin2bcd_l( month);
	rtc.Month10    = bin2bcd_h( month);
	rtc.Day        = dayofweek;
	rtc.Year       = bin2bcd_l( year - 2000);
	rtc.Year10     = bin2bcd_h( year - 2000);
	rtc.WP = 0;  

	// Write all clock data at once (burst mode).
	DS1302_clock_burst_write( (uint8_t *) &rtc);

}


void RTC_ShowCurrentDateTimeToSerial()
{
	ds1302_struct rtc;
	char buffer[45];     

	char DayOfWeek[10];

	// Read all clock data at once (burst mode).
	DS1302_clock_burst_read( (uint8_t *) &rtc);

	switch (rtc.Day)
	{
		case 1:
			String(F("Monday")).toCharArray(DayOfWeek, 15);
			break;
		case 2:
			String(F("Tuesday")).toCharArray(DayOfWeek, 15);
			break;
		case 3:
			String(F("Wednsday")).toCharArray(DayOfWeek, 15);
			break;
		case 4:
			String(F("Thursday")).toCharArray(DayOfWeek, 15);
			break;
		case 5:
			String(F("Friday")).toCharArray(DayOfWeek, 15);
			break;
		case 6:
			String(F("Saturday")).toCharArray(DayOfWeek, 15);
			break;
		case 7:
			String(F("Sunday")).toCharArray(DayOfWeek, 15);
			break;
	}


	sprintf(buffer, "%02d/%02d/%02d %02d:%02d:%02d - %s - (DD/MM/YYYY)",
		bcd2bin( rtc.Date10, rtc.Date), \
		bcd2bin( rtc.Month10, rtc.Month), \		
		2000 + bcd2bin( rtc.Year10, rtc.Year), \
		bcd2bin( rtc.h24.Hour10, rtc.h24.Hour), \
		bcd2bin( rtc.Minutes10, rtc.Minutes), \
		bcd2bin( rtc.Seconds10, rtc.Seconds), \
		DayOfWeek);
	Serial.println( buffer);


	//delay( 5000);
}


String RTC_Now()
{
	ds1302_struct rtc;
	char buffer[45];     

	char DayOfWeek[15];



	// Read all clock data at once (burst mode).
	DS1302_clock_burst_read( (uint8_t *) &rtc);

	switch (rtc.Day)
	{
		case 1:
			String(F("Monday")).toCharArray(DayOfWeek, 15);
			break;
		case 2:
			String(F("Tuesday")).toCharArray(DayOfWeek, 15);
			break;
		case 3:
			String(F("Wednsday")).toCharArray(DayOfWeek, 15);
			break;
		case 4:
			String(F("Thursday")).toCharArray(DayOfWeek, 15);
			break;
		case 5:
			String(F("Friday")).toCharArray(DayOfWeek, 15);
			break;
		case 6:
			String(F("Saturday")).toCharArray(DayOfWeek, 15);
			break;
		case 7:
			String(F("Sunday")).toCharArray(DayOfWeek, 15);
			break;
	}


	sprintf(buffer, "%02d/%02d/%02d %02d:%02d:%02d",
		bcd2bin( rtc.Date10, rtc.Date), \
		bcd2bin( rtc.Month10, rtc.Month), \		
		2000 + bcd2bin( rtc.Year10, rtc.Year), \
		bcd2bin( rtc.h24.Hour10, rtc.h24.Hour), \
		bcd2bin( rtc.Minutes10, rtc.Minutes), \
		bcd2bin( rtc.Seconds10, rtc.Seconds));

	return String(buffer);



	//delay( 5000);
}

