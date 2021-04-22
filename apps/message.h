String ad_message() { return "/arduino/apps/message/message.bmp"; }

byte number_new_message()
{
    File directory = SD.open("/arduino/apps/message/new");
    int indent = 0;
    byte i = 0;
    File entry = directory.openNextFile();
    while (entry)
    {
        i++;
        entry.close();
        entry = directory.openNextFile();
    }
    directory.rewindDirectory();
    return i;
}

String get_number_phone_new_message(byte number)
{
    String adress = "/arduino/apps/message/new/";
    adress += number;
    adress += ".txt";
    File file_new_message = SD.open(adress, FILE_READ);

    String string_number = "";

    while (string_number.length() < 13)
    {
        string_number = string_number + char(file_new_message.read());
    }
    file_new_message.close();
    return string_number;
}

char *get_phone_number(char *input, int line)
{
    if (line <= 0)
    {
        // numéro de ligne invalide
        return NULL;
    }

    char *ptr = input;

    for (int i = 0; i < line; i++)
    {
        ptr = strstr(ptr, "+CMGL:");
        ptr += 6;

        if (!ptr)
        {
            // erreur
            return NULL;
        }
    }

    ptr = strchr(ptr, ',') + 1;
    ptr = strchr(ptr, ',') + 2;

    char *target = strchr(ptr, '"');

    if (!target)
    {
        // erreur
        return NULL;
    }

    char *number = malloc(sizeof(char) * ((target - ptr) + 1));

    if (!number)
    {
        // erreur
        return NULL;
    }

    memcpy(number, ptr, target - ptr);
    number[target - ptr] = '\0';

    return number;
}

char *get_message(char *input, int line)
{
    if (line <= 0)
    {
        // numéro de ligne invalide
        return NULL;
    }

    char *ptr = input;

    for (int i = 0; i < line; i++)
    {
        ptr = strstr(ptr, "+CMGL:");
        ptr += 6;

        if (!ptr)
        {
            // erreur
            return NULL;
        }
    }

    ptr = strchr(ptr, '\n');
    ptr++;

    if (!ptr)
    {
        // erreur
        return NULL;
    }

    char *target = strchr(ptr, '\n');

    if (!target)
    {
        // erreur
        return NULL;
    }

    char *message = malloc(sizeof(char) * ((target - ptr) + 1));

    if (!message)
    {
        // erreur
        return NULL;
    }

    memcpy(message, ptr, target - ptr);
    message[target - ptr] = '\0';

    return message;
}

void new_message(String sms, String num)
{
    byte number = number_new_message() + 1;

    String adress = "/arduino/apps/message/new/";
    adress += number;
    adress += ".txt";

    File file_open = SD.open(adress, FILE_WRITE);

    file_open.println(num);
    file_open.close();
}

void puts_messages(char *input, int lines)
{
    for (int i = 1; i < lines + 1; i++)
    {
        char *message = get_message(input, i);
        char *phone_number = get_phone_number(input, i);

        String string_message = message;
        String string_phone_number = phone_number;

        free(message);
        free(phone_number);

        new_message(string_message, string_phone_number);
    }
}

void download_messages()
{
    Serial1.println("AT+CMGF=1");
    delay(100);

    while (Serial1.available())
        Serial1.read();

    Serial1.println("AT+CMGL=\"REC UNREAD\"");
    String msg_sim;
    short i = 0;
    while (1)
    {
        if (Serial1.available())
        {
            msg_sim += Serial1.read();

            i++;
            if (msg_sim[i - 1] == 'K')
            {
                break;
            }
        }
    }
    Serial.print(msg_sim);
    Serial1.println("AT+CMGD=4");
    Serial.println("\nfin serie");

    char *msg_sim_char = msg_sim;
    if (i > 30)
        puts_messages(msg_sim_char, 1);
    else
        Serial.println("pas de nouveaux messages");
}

void draw_message_interface()
{
    fill_screen(0, 0, 0);

    byte number_message;

    number_message = number_new_message();
    Serial.print("nombre de messages: ");
    Serial.println(number_message);
    for (byte i = 1; i < number_message + 1; i++)
    {
        tft.setColor(230, 200, 0);
        tft.fillRoundRect(30, 50 + i * 50, 290, 80 + i * 50);
        tft.setCursor(60, 70 + i * 50);
        tft.setColor(0, 0, 0);
        tft.print(get_number_phone_new_message(i));
    }
}

void message()
{
    while (1)
    {
        allready_active = 1;
        download_messages();
        draw_message_interface();
        allready_active = 0;
        screen();
        while (!touch())
        {
        }
    }
}
