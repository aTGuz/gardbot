








// define the global var with the plants. The var being passed as argument will be the one defined. 
// we pass the global var of the plants: gaPlants
// return in the format: CodReturn|description
// CodReturn: 1 for ok. -1 and -2 are errors
String DB_DefinePlantsFromSD(String aRetPlants[])
{

	String ret = F("1");

	String retFunc = F("");

	String FullPathFile_Plants = F("");

	String IDsPlantDesired = F("");

	FullPathFile_Plants = F("Gardbot/Plants/Plants.csv");

	// zera a var de engatados
	for (int x = 0 ; x <= ctMAX_PLANTS ; x++)
	{
		aRetPlants[x] = F("");
	}	





	retFunc = SD_GetAllRegsFromFile(FullPathFile_Plants, aRetPlants, ctMAX_PLANTS);


	if ((retFunc.substring(0, 2) == F("-1")) || (retFunc.substring(0, 2) == F("-2")))
	{
		// erro de sd card
		ret = retFunc;
		return ret;
	}

	if (retFunc.substring(0, 1) == F("1"))
	{

		




		for (int x = 0 ; x <= ctMAX_PLANTS ; x++)
		{
			if (aRetPlants[x] != F(""))
			{
				//LogTerm(String(F("aRetPlants[")) + String(x) + String(F("] = ")) + aRetPlants[x]);
			}
		}		
		

		ret = retFunc;
		return ret;

	}

	return ret;
}






