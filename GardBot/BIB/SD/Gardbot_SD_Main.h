




String SD_TestaCartao()
{

	uint32_t cardSize;

	SdFat SD;

	String ret = F("1|");



	uint32_t t = millis();

	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!SD.cardBegin(SD_PINO, SPI_SIXTEENTH_SPEED))
	{
		LogTerm(F("SD: Failed initializating SD card"));

		ret = F("0|Failed initializating SD card");
		return ret;	
	}

	t = millis() - t;	

	ret += String(t) + String(F("ms|"));

	cardSize = SD.card()->cardSize();

	if (cardSize == 0) 
	{
		LogTerm(F("SD: Failed getting the size of the SD card"));

		ret = F("0|Failed getting the size of the SD card");
		return ret;	
	}


	

	//cout << F("\ninit time: ") << t << " ms" << endl;
	//cout << F("\nCard type: ");

	switch (SD.card()->type())
	{
		case SD_CARD_TYPE_SD1:
			ret += String(F("SD1"));
			break;

		case SD_CARD_TYPE_SD2:
			ret += String(F("SD2"));
			break;

		case SD_CARD_TYPE_SDHC:
			if (cardSize < 70000000) 
			{
				ret += String(F("SDHC"));
			} 
			else
			{
				ret += String(F("SDXC"));
			}
			break;

		default:
			ret += String(F("Desconhecido"));
			break;
	}


	return ret;	
}





// retorna formato: CodRetorno|descricao
// Param byref: LetorSD - SD_CHIP_SELECT	SD_CHIP_SELECTretora o objeto passado, leitor SD
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_InicializaCartaoSD(SdFat &LeitorSD)
{

	String ret = F("1|SD Initilized");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;


	// not over 50 MHz. Try a lower speed if SPI errors occur.
	if (!LeitorSD.begin(SD_PINO, SPI_SIXTEENTH_SPEED))
	{
		LogTerm(F("SD: Failed initializating SD card"));

		while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
		{	
			LogTerm(F("SD: Trying again..."));

			// desliga sd
			pinMode(SD_PINO, OUTPUT);
			digitalWrite(SD_PINO, HIGH);	
			delay(SD_DELAY_TENTATIVA_READ);

			// religa sd
			pinMode(SD_PINO, INPUT);
			digitalWrite(SD_PINO, LOW);	
			delay(SD_DELAY_TENTATIVA_READ);



			if (LeitorSD.begin(SD_PINO, SPI_SIXTEENTH_SPEED))
			{
				SucessoTentativa = true;
			}

			ContaTentativa++;

		}


		ret = F("-1|Failed initializating SD card");

		return ret;	
	}

	return ret;
}




// retorna formato: CodRetorno|descricao
// RetryOrCheckExists = RETRY ou CHECK . Se for RETRY, significa que esta sendo tentado abrir um arquivo conhecido e caso
//	ocorra algum erro, o sistema deve tentar de novo. Se for CHECK, o sistema nao sabe se existe o arquivo e deseja justamente
//  verificar se ele existe. Para tanto, tenta abri-lo e se ocorrer o erro, informa o caller que o arquivo nao existe
// 1 para a funcao rodou certo 
// -1 erros outros
// -2 para arquivo nao existe
String SD_AbreArqTexto(String FullPathFile, SdFat &LeitorSD, File &objArquivo, String RetryOrCheck)
{

	String ret = F("1|File opened");

	int ContaTentativa = 0;
	bool SucessoTentativa = false;




	objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

	if (!objArquivo) 
	{

		if (RetryOrCheck == "RETRY")
		{
			LogTerm(String(F("SD: Failed in opening the file: ")) + FullPathFile);


			while ((ContaTentativa <= SD_MAX_TENTATIVA_READ) && (SucessoTentativa == false))
			{
				LogTerm(F("SD: Trying again..."));

				// desliga sd
				pinMode(SD_PINO, OUTPUT);
				digitalWrite(SD_PINO, HIGH);	
				delay(SD_DELAY_TENTATIVA_READ);

				// religa sd
				pinMode(SD_PINO, INPUT);
				digitalWrite(SD_PINO, LOW);	
				delay(SD_DELAY_TENTATIVA_READ);

				objArquivo = LeitorSD.open(FullPathFile, FILE_READ);

				if (objArquivo) 
				{
					SucessoTentativa = true;

					return ret;	
				}


				ContaTentativa++;

			}


			ret = String(F("-1|Failed in opening the file: ")) + FullPathFile;

			return ret;	
		}



		if (RetryOrCheck == "CHECK")
		{
			LogTerm(String(F("SD: File not found: ")) + FullPathFile);

			ret = String(F("-2|File not found: ")) + FullPathFile;

			return ret;	
		}



	}

	return ret;
}

// retorna formato: CodRetorno|descricao
// Param byref: aRetRegs - contera todos os registros do arquivo, se existirem
// 1 para a funcao rodou certo 
// -1 erros outros
String SD_GetAllRegsFromFile(String FullPathFile, String aRetRegs[], int MaxSizeRetArray)
{


	String ret = F("1|");

	String buff =F("");

	int ContaEnter = 0;

	int CharAtual;


	//int ContaTentativa = 0;
	//bool SucessoTentativa = false;

	SdFat SD;
	String retSD = F("");




	retSD = SD_InicializaCartaoSD(SD);



	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	File file;
	String retFile = F("");




	retFile = SD_AbreArqTexto(FullPathFile, SD, file, F("RETRY"));

	


	if (retFile.substring(0, 1) != F("1"))
	{
		return retFile;
	}
	else
	{




		if (ctDEBUG_MODE == true)
		{
			LogTerm(String(F("SD: File opened with success: ")) + FullPathFile);
		}
		


		int ContaReg = 0; 

		while (file.available()) 
		{
			//LogTerm(file.read());

			CharAtual = file.read();
			

			if (CharAtual == 13)
			{
				ContaEnter++;
			}
			
			if (ContaEnter >= 1)
			{

				switch (CharAtual) 
				{
					case 10:

						//tft.fillRoundRect(Botao_PosAtual_X, Botao_PosAtual_Y, Size_Botao_W, Size_Botao_H, 10, RA8875_GREEN);
						break;

					case 13:

						ContaReg++;
						break;

					default:

						if (ContaReg <= MaxSizeRetArray)
						{
							aRetRegs[ContaReg - 1] += CharFromAsc2(CharAtual);
						}
						
						break;
				}


				
			}

			//Serial.write(CharAtual);
			//Serial.println(CharAtual);

			//LogTerm(CharAtual);
			
		}




	

	}

	file.close();



	return ret;


}





String SD_GetFirstRegFromFile(String FullPathFile, String RetryOrCheck)
{



	String ret = F("1|");

	String buff = F("");

	int ContaEnter = 0;

	int CharAtual;






	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	File file;
	String retFile = F("");

	retFile = SD_AbreArqTexto(FullPathFile, SD, file, RetryOrCheck);

	if (retFile.substring(0, 1) != F("1"))
	{
		return retFile;
	}
	else
	{

		if (ctDEBUG_MODE == true)
		{
			LogTerm(String(F("SD: File opened with success: ")) + FullPathFile);
		}
		

		while (file.available()) 
		{
			//LogTerm(file.read());

			CharAtual = file.read();

			if (CharAtual == 13)
			{
				ContaEnter++;
			}
			
			if (ContaEnter >= 1)
			{
				if ((CharAtual != 10) && (CharAtual != 13))
				{
					ret += CharFromAsc2(CharAtual);

					//LogTerm(CharAtual);
					//Serial.write(CharAtual);
				}
				
			}

			//Serial.write(CharAtual);
			//Serial.println(CharAtual);

			//LogTerm(CharAtual);
			
		}		

	}

	file.close();

	return ret;
}


String SD_ApagaArquivo(String FullPathFile)
{

	String ret = F("");

	File Arquivo_Temp;


	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}


	Arquivo_Temp = SD.open(FullPathFile, O_WRITE);

	if (Arquivo_Temp.remove())
	{
		ret = String(F("1|File deleted with success: ")) + FullPathFile;
	}
	else
	{
		ret = String(F("0|It wasnt possible to delete the file: ")) + FullPathFile;
	}

	return ret;
}




String SD_CreateNewUserFile(String IDUser, String Nome, String Nivel, String CPF, String Saldo, String DataCad)
{

	String ret = F("1|");

	String FullPathFile_TEMP = String(F("CB/BD/Usuarios/USU_")) + IDUser + String(F(".csv"));

	File ArquivoUser_Temp;


	SdFat SD;
	String retSD = F("");



	SD_ApagaArquivo(FullPathFile_TEMP);
	



	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}



	ArquivoUser_Temp = SD.open(FullPathFile_TEMP, FILE_WRITE);

	if (ArquivoUser_Temp)
	{

		String Linha = F("");

		Linha = F("IDUser;CPF;DataCad;Nome;Nivel;SaldoAtual");
		ArquivoUser_Temp.println(Linha);

		Linha = String(IDUser) + String(F(";")) + CPF + String(F(";")) + DataCad + String(F(";")) + Nome + String(F(";")) + String(Nivel) + String(F(";")) + String(Saldo);
		ArquivoUser_Temp.print(Linha);

	    ArquivoUser_Temp.close();

	    LogTerm(String(F("Novo arquivo de usuario criado: ")) + FullPathFile_TEMP);

	    delay(500);

	}
	else
	{
		LogTerm(String(F("It wasnt possible to create the file: ")) + FullPathFile_TEMP);

		ret = String(F("-2|It wasnt possible to create the file: ")) + FullPathFile_TEMP;
	}



	return ret;

}





String SD_CreateNewLoginFile(String IDUser, String CPF, String IDCartao)
{

	String ret = F("1|");

	String FullPathFile_TEMP = String(F("CB/BD/Logins/RFID/")) + IDCartao + String(F(".csv"));

	File ArquivoUser_Temp;

	String DataCad = RTC_Now();


	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}




	ArquivoUser_Temp = SD.open(FullPathFile_TEMP, FILE_WRITE);

	if (ArquivoUser_Temp)
	{

		String Linha = F("");

		Linha = F("IDUser;CPF;ID_RFID");
		ArquivoUser_Temp.println(Linha);

		Linha = String(IDUser) + String(F(";")) + CPF + String(F(";")) + String(IDCartao);
		ArquivoUser_Temp.print(Linha);

	    ArquivoUser_Temp.close();

	    LogTerm(String(F("Novo arquivo de login criado: ")) + FullPathFile_TEMP);

	    delay(500);

	}
	else
	{
		LogTerm(String(F("Nao foi possivel criar o arquivo:: ")) + FullPathFile_TEMP);

		ret = String(F("-2|Nao foi possivel criar o arquivo ")) + FullPathFile_TEMP;
	}



	return ret;

}








String SD_RenameArquivo(String FullPathFile_Original, String FullPathFile_Destino)
{

	String ret = F("");

	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}


	char __FullPathFile_Original[FullPathFile_Original.length() + 1];
	FullPathFile_Original.toCharArray(__FullPathFile_Original, sizeof(__FullPathFile_Original));

	char __FullPathFile_Destino[FullPathFile_Destino.length() + 1];
	FullPathFile_Destino.toCharArray(__FullPathFile_Destino, sizeof(__FullPathFile_Destino));


	SdFile Arquivo_Temp(__FullPathFile_Original, O_WRITE);

	if (!Arquivo_Temp.isOpen()) 
	{
		ret = String(F("0|It wasnt possible to rename the file: ")) + FullPathFile_Original;
	}
	else
	{
		if (Arquivo_Temp.rename(SD.vwd(), __FullPathFile_Destino)) 
		{
			ret = String(F("1|File renamed with success: ")) + FullPathFile_Original + String(F(" to ")) + FullPathFile_Destino;
		}
		else
		{
			ret = String(F("0|It wasnt possible to rename the file:: ")) + FullPathFile_Original + String(F(" to ")) + FullPathFile_Destino;
		}
	}

	return ret;
}






String SD_CopiaArquivo(String FullPathFile_Original, String FullPathFile_Destino)
{

	String ret = F("");

	SdFat SD;
	String retSD = F("");

	retSD = SD_InicializaCartaoSD(SD);

	if (retSD.substring(0, 1) != F("1"))
	{
		return retSD;
	}


	char __FullPathFile_Original[FullPathFile_Original.length() + 1];
	FullPathFile_Original.toCharArray(__FullPathFile_Original, sizeof(__FullPathFile_Original));

	char __FullPathFile_Destino[FullPathFile_Destino.length() + 1];
	FullPathFile_Destino.toCharArray(__FullPathFile_Destino, sizeof(__FullPathFile_Destino));


	SdFile Arquivo_Origem(__FullPathFile_Original, O_READ);
	SdFile Arquivo_Destino(__FullPathFile_Destino, O_WRITE);

	if (!Arquivo_Origem.isOpen()) 
	{
		ret = String(F("0|It wasnt possible to locate the file: ")) + FullPathFile_Original;
	}
	else
	{

		while (Arquivo_Origem.available()) 
		{
			Arquivo_Destino.write(Arquivo_Origem.read());			
		}	

		Arquivo_Origem.close();
		Arquivo_Destino.close();

		ret = String(F("1|File copied with success: ")) + FullPathFile_Original + String(F(" to ")) + FullPathFile_Destino;


	}

	return ret;
}

// comando do gabriel: i0,yio,,,nkjy kopd.skgb.ophlbo-dpt/buo0jk.0ov.lby0hy.bjo.bjoun.jou0-n.jpu-rn/u-prb=/

