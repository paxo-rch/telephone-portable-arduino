long f_read_int(String adress)
{
	long value = 0;
	File file_open = SD.open(adress);

	while(file_open.available())
	{
		char letter = file_open.read();
		if(letter != 'e')value = value * 10 + (letter - 48);
		Serial.println(letter);
	}
  	file_open.close();
	return value;
}

void f_write_int(String adress, long value)
{
	SD.remove(adress);
	File file_open=SD.open(adress, FILE_WRITE);
	file_open.print(value);
  	file_open.close();
}