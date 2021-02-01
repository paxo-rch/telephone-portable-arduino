#define actu_heure 60000
String directionfichier = "/";
byte c;

#include <fonc_importantes.h>
#include <fonc_basique.h>
#include <arriere_plan.h>
#include <json.h>


void setup()
{
  pinMode(53, OUTPUT);
  Init();
  crs(100, 100);
  couleur(0x0000);
  taille(3);
  //ecran(0x1111);
  Serial.println("AT");
}

void loop() {
  menu(1);
  actu();
}

void Init(void)
{
  if (!SD.begin(4)) {
    tft.setTextSize(3);
    tft.setTextColor(ILI9341_RED);
    tft.print("ERREUR: Carte SD");
    while (true);
  }
  tft.begin();
  tft.setRotation(3);
  ecran(0x000);
  bmpDraw("/arduino/paxo/paxo.bmp", 110, 100);
    crs(113, 200);
  tft.print("demarage (10s)");
  light(true);
  delay(10000);
  Serial1.begin(9600);
  rtc.begin();
  Serial.begin(115200);
}

void appel(long numero)
{
  Serial1.print("ATD+33");
  Serial1.print(numero);
  Serial1.println(";");
}

void menu(byte type)
{
  while(true)
  {
  int pos[8] = {10, 85, 160, 235};
  byte posy[2] = {40, 140};
  byte curseurx = 0;
  byte curseury = 0;
  couleur(0x0000);
  ecran(0xFFFF);
  touches("exit", "<", ">", "select");
    switch (type)
    {
      case 1:
         bmpDraw("/arduino/appdata/snake/snake.bmp", pos[0], 40);
         bmpDraw("/arduino/appdata/fichier/fichier.bmp", pos[1], 40);
         bmpDraw("/arduino/appdata/message/message.bmp", pos[2], 40);
         bmpDraw("/arduino/appdata/phone/phone.bmp", pos[3], 40);
         bmpDraw("/arduino/appdata/pong/pong.bmp", pos[0], 140);
         bmpDraw("/arduino/appdata/reglage/reglage.bmp", pos[1], 140);
         bmpDraw("/arduino/appdata/chrono/chrono.bmp", pos[2], 140);
      break;
    }

    while (true)
    {
      clavier();
      actu();
      if(touche)
      {
        if(touche == 8 && curseury == 1){type++; break;}
        if(touche == 2 && curseury == 0 && type != 1){type--; break;}
        tft.drawRect(pos[curseurx]- 2, posy[curseury] - 2, 54, 54, 0xFFFF);
        if(touche == 2 && curseury != 0){curseury--;}
        if(touche == 8 && curseury != 1){curseury++;}
        if(touche == 4 && curseurx != 0){curseurx--;}
        if(touche == 6 && curseurx != 3){curseurx++;}
        tft.drawRect(pos[curseurx]- 2, posy[curseury] - 2, 54, 54, 0x000);
        if(touche == 20)
        {
          break;
        }
      }
    }

    //ouverture de l'application
    if(touche == 20)
    switch(type)
    {
      case 1:
      switch(curseury)
      {
        case 0:
          switch(curseurx)
          {
            case 0: snake(); break;
            case 1: fichier(); break;
            case 2: message(); break;
            case 3: telephone(); break;
          }
        break;
        case 1:
          switch(curseurx)
          {
            case 0: pong(); break;
            case 1: reglage(); break;
            case 2: chrono(); break;
            case 3: telephone(); break;
          }
        break;
      }
      break;

      case 2:

      break;
    }
  }
}


void message()
{
  ecran(0xFFFF);
  crs(100, 0);
  taille(3);
  couleur(0x0000);
  tft.print("non programmée");
}

void telephone()
{
  ecran(0xFFFF);
  byte curseur = 20;
  touches("menu", "contacts", "clear", "appeler");
  long numero = 0;
  tft.fillRect(10, 120, 300, 30, 0xFA2E);
  while(true)
  {
    actu();
    clavier();
    if(touche != - 48)
    {
      if(touche != 20 && touche != 19 && touche != 18 && touche != 17)
      {
        numero = numero*10 + touche;
        crs(curseur, 125);
        taille(2);
        tft.print(touche);
        curseur += 12;
      }
      if(touche == 20) appel(numero);
      if(touche == 17) return;
      if(touche == 19)
      {
        numero = 0;
      }
    }
  }
}

void snake()
{
  touches("", "", "", "");
  game = true;
  ecran(0xFFFF);
  byte snake[100][2] = {0};
  byte tete = 0;
  byte deriere = 0;
  bool point = true;
  byte pointxy[2] = {0, 0};
  int vitesse;
  byte piege1[2] = {0, 0};
  byte i;
  byte piege2[2] = {0, 0};
  byte piege3[2] = {0, 0};
  bool gameover = false;
  long conteur = millis();
  snake[0][1] = 8;
  snake[0][0] = 8;
  byte direc = 2;
  int score = 5;
  pointxy[0] = random(1, 32);
  pointxy[1] = random(4, 19);
  tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 9, 9, 0xD366);
  while(touche != 17)
  while(gameover == false)
  {
    if(score < 20){
      vitesse = score;
    }
    if(millis()-300ul > conteur - vitesse * 10)
    {
      i = score;
      Serial.println("1");
      while(i != 1)
      {
          i--;
          snake[i][1] = snake[i - 1][1];
          snake[i][0] = snake[i - 1][0];
      }
      actu();
      clavier();
      if(touche){
          tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, 0xD366);
          if(touche == 2){direc = 3;}
          if(touche == 6){direc = 2;}
          if(touche == 8){direc = 1;}
          if(touche == 4){direc = 4;}
      }
      if(direc == 2)snake[0][1] = snake[0][1] + 1;  
      if(direc == 4)snake[0][1] = snake[0][1] - 1;     
      if(direc == 1)snake[0][0] = snake[0][0] + 1;  
      if(direc == 3)snake[0][0] = snake[0][0] - 1;     
      ram();
      tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, 0x33E2);
      tft.fillRect(snake[score - 1][1] * 10, snake[score - 1][0] * 10, 10, 10, ILI9341_WHITE);
      conteur = millis();
    }
    clavier();
    if(touche){
          if(touche == 2){direc = 3;}
          if(touche == 6){direc = 2;}
          if(touche == 8){direc = 1;}
          if(touche == 4){direc = 4;}
    }
    tete = 1;
    while(tete != score)
    {
      if( (snake[0][1] == snake[tete][1] && snake[0][0] == snake[tete][0] ) || snake[0][0] > 21 || snake[0][0] == 2 || snake[0][1] > 31)
      {
        tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, ILI9341_RED); 
        touches("menu", "", "", "rejouer");
        crs(100, 100);
        taille(4);
        couleur(0x000);
        tft.print(score);
        while(touche != 17 && touche != 20)
        { 
          clavier(); 
        }
        if(touche == 17)return;
        if(touche == 20)
        {
          ecran(0xFFFF);
          score = 5;
          pointxy[0] = random(1, 32);
          pointxy[1] = random(4, 22);
          tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, 0xD366);
          snake[100][2] = {0};
          snake[0][1] = 8;
          snake[0][0] = 8;
          touches("", "", "", "");
        }
      }
      tete++;
    }
    if(snake[0][0] == pointxy[1] && snake[0][1] == pointxy[0]){
      pointxy[0] = random(1, 29);
      pointxy[1] = random(1, 19);
      tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, 0xD366);
      score++;
    }
  }
}

void fichier()
{
  bool Exit = false;
  String directionfichier = "";
  touches("menu", "", "exit", "select");
  while(true)
  {
    ecran(0xFFFF);
    File lieu = SD.open(directionfichier);
    listDirectoryFiles(lieu, 0);
    lieu.close();
    
    byte e[2][8] = {{10,85,160,235,10,85,160,235},{40,40,40,40,140,140,140,140}};
    for(byte b = 0; b < c; b++){
      if(type(b) == 0){
        bmpDraw("/arduino/appdata/fichier/fichier.bmp", e[0][b], e[1][b]);      
        if(strchr(fichiers[b].c_str(), '.') == true) bmpDraw("/arduino/appdata/fichier/finconnu.bmp", e[0][b], e[1][b]);
      }
      if(type(b) == 1){
        bmpDraw("/arduino/appdata/fichier/image.bmp", e[0][b], e[1][b]);
      }
      if(type(b) == 2){
        bmpDraw("/arduino/appdata/fichier/texte.bmp", e[0][b], e[1][b]);
      }
      couleur(0x0000);
      tft.setCursor(e[0][b], e[1][b]+54);
      taille(1);
      tft.print(fichiers[b]);
    }

    byte lecteur = 0;

      while(1)
      {
        clavier();
        actu();
        if(touche)
        {
          tft.drawRect(e[0][lecteur]- 2, e[1][lecteur] - 2, 54, 54, 0xFFFF);
       
          if(touche == 6){
            lecteur++;
          }

          if(touche == 4){
            lecteur--;
          }
          if(touche == 20){
            break;
          }
          if(touche == 17){
            return;
          }
          if(touche == 19){
            break;
          }
          tft.drawRect(e[0][lecteur]- 2, e[1][lecteur] - 2, 54, 54, 0x0000);
        }
      }
      directionfichier = directionfichier+"/"+fichiers[lecteur];
      if(touche == 20){
        ouverture(directionfichier);
      }
      if(touche == 19){
          directionfichier = "";
      }
    }
}

void pong()
{
  float direction_pong[2] = {2, 2};
  float  raquette = 100;
  long conteur = 0;
  byte score = 0;
  conteur = millis();
  float pong[2] = {10,10};
    while(true)
    {
      direction_pong[1] = -4;
      pong[1] = 40;
      direction_pong[0] = 4;
      pong[0] = 40;
      ecran(0x000);
      while(true)
    {
      if(direction_pong[0] == 0)direction_pong[0] = random(-1,1);
    touche = customKeypad.getKey() - 48;
    if(touche){
      tft.fillRect(raquette - 25, 200, 50, 10, ILI9341_BLACK); 
      switch(touche){
        case 6:
          raquette= raquette + 20;
        break;
        case 4:
          raquette=raquette-20;
        break;
      }
      tft.fillRect(raquette - 25, 200, 50, 10, ILI9341_WHITE); 
    }
    if(millis()-20ul > conteur)
    {
      if(pong[0] > 315 || pong[0] < 5)direction_pong[0] = direction_pong[0] * (-1);
      if(pong[1] < 40)direction_pong[1] = direction_pong[1] * (-1);

      
      if(pong[1] > 195 && pong[0] < raquette + 30 && pong[0] > raquette - 30)
      {
        direction_pong[1] = direction_pong[1] * (-1);
        direction_pong[0] = direction_pong[0] + (pong[0]-raquette)/10;
        tft.setTextSize(2);
        tft.setCursor(290, 40);
        tft.setTextColor(ILI9341_BLACK);
        tft.print(score);
        
        score = score + 1;
        tft.setCursor(290, 40);
        tft.setTextColor(ILI9341_WHITE);
        tft.print(score);
      }
      conteur = millis();
      if(pong[1] > 210)
      {break;}

      
    tft.fillCircle(pong[0], pong[1], 2, ILI9341_BLACK); 
    pong[0] = pong[0] + direction_pong[0];
    pong[1] = pong[1] + direction_pong[1];
    tft.fillCircle(pong[0], pong[1], 2, ILI9341_WHITE); 
}
    }
    while(true){
    touche = customKeypad.getKey();
    if(touche){
      break;
    }
    
  }
  score = 0;
  if(touche-48 == 17){break;}
    }
}

void reglage()
{
  while(true)
  {
    couleur(0x0000);
    ecran(0xFFFF);
    taille(2);
    crs(20, 40);
    tft.println("actualisation de l'heure");
    crs(20, 70);
    tft.println("actualisation de la ram");
    crs(20, 100);
    tft.println("code");
    byte curseur = 0;
    tft.drawRect(18, 38, 290, 20, 0x0000);
    while(true)
    {
      clavier();
      if(touche != -48)
      {
        tft.drawRect(18, 38 + curseur*30, 290, 20, 0xFFFF);
        if(touche == 8) curseur++;
        if(touche == 2 && curseur != 0) curseur--;
        tft.drawRect(18, 38 + curseur*30, 290, 20, 0x0000);
      }
    }
  }
}

void chrono()
{
  touches("menu", "effacer", "stop", "lancer");
  float chronometre;
  float debut;
  while(true)
  {
    ecran(0xFFFF);
    crs(60, 100);
    couleur(0x0000);
    taille(2);
    tft.print("0:0:0");
    clavier();
    while(touche == -48)
    {
      clavier();
    }
    if(touche == 20)
    {
      debut = millis();
      clavier();
      int h,m,s,rs = 0;
      taille(2);
      while(touche == -48)
      {
        clavier();
        delay(50);
        m=s/60;
        rs=s%60;
        h=m/60;
        m=m%60;
        crs(60, 100);
        couleur(0xFFFF);
        tft.print(h);
        tft.print(":");
        tft.print(m);
        tft.print(":");
        tft.print(rs);
        s = (millis() - debut) / 1000;
        m=s/60;
        rs=s%60;
        h=m/60;
        m=m%60;
        crs(60, 100);
        couleur(0x0000);
        tft.print(h);
        tft.print(":");
        tft.print(m);
        tft.print(":");
        tft.print(rs);
      }
      if(touche == 17) return;
      if(touche == 18) s = 0;
      if(touche == 19)
      {
        clavier();
        while(touche == -48)
        {
          clavier();
        }
      }
    }
    
  }
}
