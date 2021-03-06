int f_read_int(String adress)
{
	int value = 0;
	File file_open = SD.open(adress);

	while(file_open.available())
	{
		value = value * 10 + (file_open.read() - 48);
	}
  	file_open.close();
	return value;
}

void f_write_int(String adress, int value)
{
	SD.remove(adress);
	File file_open=SD.open(adress, FILE_WRITE);
	file_open.print(value);
  	file_open.close();
}