


// print the values of the array with the plants controled by the system
void CORE_PrintPlants()
{


    LogTerm(F("====  PLANTS  ===================="));



    for (int x = 0 ; x <= ctMAX_PLANTS ; x++)
    {

        if (gaPlants[x] != F(""))
        {


            // IDPlant;Name;Type;DatePlant;Active;Obs
            String tmp_IDPlant = getValue(gaPlants[x], ';', 1);
            String tmp_Name = getValue(gaPlants[x], ';', 2);
            String tmp_Type = getValue(gaPlants[x], ';', 3);
            String tmp_DatePlant = getValue(gaPlants[x], ';', 4);
            String tmp_Active = getValue(gaPlants[x], ';', 5);
            String tmp_Obs = getValue(gaPlants[x], ';', 6);

            //LogTerm(gaPlants[x]);

            if (tmp_IDPlant != F(""))
            {
                LogTerm(String(F("Plant [")) + String(x) + String(F("] -- IDPlant: ")) + tmp_IDPlant);
                LogTerm(String(F("Plant [")) + String(x) + String(F("] -- Name: ")) + tmp_Name);
                LogTerm(String(F("Plant [")) + String(x) + String(F("] -- Type: ")) + tmp_Type);
                LogTerm(String(F("Plant [")) + String(x) + String(F("] -- DatePlant: ")) + tmp_DatePlant);
                LogTerm(String(F("Plant [")) + String(x) + String(F("] -- Obs: ")) + tmp_Obs);


                if (tmp_Active == F("1"))
                {
                    LogTerm(String(F("Plant [")) + String(x) + String(F("] -- Active: YES")));
                }
                else
                {
                    LogTerm(String(F("Plant [")) + String(x) + String(F("] -- Active: NO"))); 
                }      
                
                LogTerm(F("------------------------------"));          
            }


            
            

        }


    }    
}




// define the array with the plans controle by the system, from a file in the sd card
void CORE_ExecDefinePlantsFromSD()
{

    String retPlants = "";



    retPlants = DB_DefinePlantsFromSD(gaPlants);  


    if (retPlants.substring(0, 1) != "1") 
    {

        BUZZER_TocaSom(F("ERRO"));


        LogTerm(F("MAIN: Fail to load file with plants"));
        LogTerm(String(F("MAIN: Error: ")) + retPlants.substring(3));
        LogTerm(F("MAIN: Critical failure. The system will reset in 10 seconds..."));
        LogTerm(F(""));

        delay(10000);
        ResetArduino();       
    }

    

    CORE_PrintPlants();



}
