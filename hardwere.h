bool but_home()
{
	return (digitalRead(33) == LOW);
}

DS3231  rtc(SDA, SCL);