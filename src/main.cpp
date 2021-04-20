/**
 * @file main.cpp
 * @author Wesley José Santos
 * @brief 
 * @version 0.1
 * @date 2021-02-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <Arduino.h>
#include <TimerOne.h>
#include <MCUFRIEND_kbv.h>
#include <Adafruit_GFX.h>       //Biblioteca grafica
#include <TouchScreen.h>        //Biblioteca Touch

#define YP A3 // Y+ is on Analog1
#define XM A2 // X- is on Analog2
#define YM 9 // Y- is on Digital7
#define XP 8 // X+ is on Digital6
#define TS_MINX 118
#define TS_MINY 92
#define TS_MAXX 906
#define TS_MAXY 951
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_RESET A4
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
MCUFRIEND_kbv tft;
#define MINPRESSURE 10
#define MAXPRESSURE 1000

int menu = 1;
int simular = 0;
int pagina = 0;
float potenciometro = 0;
float tensao_pot = 0;
int barra = 0;
int barra2 = 0;
float rpm = 0;
float rps = 0;
float tempo = 0;                            
int contador = 0;
float rpmAnterior = 0;

//Variaveis do menu
int leve = 0;
int dleve = 0;
int dpesa = 0;
int selecionar = 0;

// Marcas diesel pesado
int fordpesado = 0;
int edc7cummins = 0;
int motorftp = 0;
int iveco = 0;
int edc7uc31 = 0;
int mb = 0;
int scania = 0;
int vwpesado = 0;
int volvo = 0;


int contador2 = 1;

///////////////////////////////////////////////////////////////////////////////

void interrupcao()
{
  contador = contador + 1;                      

if (menu == 12) //Sinal EDC7 CUMMINS
 {
    if(contador >= 0 && contador <= 116)                   
    {
      digitalWrite(31,!digitalRead(31));         
       if(contador2 == 1 && contador == 1){digitalWrite(33,LOW);} // Dente 1 Fase
       if(contador2 == 1 && contador == 8){digitalWrite(33,HIGH);} // Dente 1 Fase
       if(contador2 == 1 && contador == 16){digitalWrite(33,LOW);} // Dente 2 Fase
       if(contador2 == 1 && contador == 20){digitalWrite(33,HIGH);} // Dente 2 Fase 
       if(contador2 == 1 && contador == 26){digitalWrite(33,LOW);} // Dente 3 Fase
       if(contador2 == 1 && contador == 48){digitalWrite(33,HIGH);} // Dente 3 Fase 
       if(contador2 == 1 && contador == 56){digitalWrite(33,LOW);} // Dente 4 Fase
       if(contador2 == 1 && contador == 88){digitalWrite(33,HIGH);} // Dente 4 Fase  
       if(contador2 == 2 && contador == 4){digitalWrite(33,LOW);} // Dente 6 Fase
       if(contador2 == 2 && contador == 8){digitalWrite(33,HIGH);} // Dente 6 Fase               
       if(contador2 == 2 && contador == 16){digitalWrite(33,LOW);} // Dente 7 Fase
       if(contador2 == 2 && contador == 48){digitalWrite(33,HIGH);} // Dente 7 Fase
       if(contador2 == 2 && contador == 88){digitalWrite(33,LOW);} // Dente 8 Fase
       if(contador2 == 2 && contador == 96){digitalWrite(33,HIGH);} // Dente 8 Fase
    }
    if(contador >= 116)                           
    {
      digitalWrite(31,LOW);                                               
      if(contador >= 119)
      {
        contador = 0;
        contador2 = contador2 + 1;
        if(contador2 > 2){contador2 = 1;}                           
      } 
    }    
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  if (menu == 13) //Sinal Ford Pesado Motor FTP
    {
    if(contador >= 0 && contador <= 121)
    {
       if(contador >= 1 && contador <= 36){digitalWrite(31,!digitalRead(31));} // Quantidade de dente antes da falha (Valor deve ser dividido por 2)
       if(contador2 == 1 && contador == 3){digitalWrite(33,HIGH);} // Dente 1 Fase
       if(contador2 == 1 && contador == 4){digitalWrite(33,LOW);} // Dente 1 Fase
       if(contador2 == 1 && contador == 33){digitalWrite(33,HIGH);} // Dente 2 Fase
       if(contador2 == 1 && contador == 34){digitalWrite(33,LOW);} // Dente 2 Fase
       if(contador2 == 2 && contador == 33){digitalWrite(33,HIGH);} // Dente 5 Fase
       if(contador2 == 2 && contador == 34){digitalWrite(33,LOW);} // Dente 5 Fase
       if(contador > 36 && contador <=40){digitalWrite(31,LOW);} // Quantidade de falha depois da 1 contagem da rotação
       if(contador > 40 && contador <= 76){digitalWrite(31,!digitalRead(31));} // Quantidade de dente antes da 2 falha (Valor deve ser dividido por 2)
       if(contador2 == 1 && contador == 73){digitalWrite(33,HIGH);} // Dente 3 Fase
       if(contador2 == 1 && contador == 74){digitalWrite(33,LOW);} // Dente 3 Fase
       if(contador2 == 2 && contador == 73){digitalWrite(33,HIGH);} // Dente 6 Fase
       if(contador2 == 2 && contador == 74){digitalWrite(33,LOW);} // Dente 6 Fase
       if(contador > 76 && contador <=80){digitalWrite(31,LOW);} // Quantidade de falha depois da 2 contagem da rotação 
       if(contador > 80 && contador <= 116){digitalWrite(31,!digitalRead(31));}  // Quantidade de dente antes da 3 falha (Valor deve ser dividido por 2)
       if(contador2 == 1 && contador == 113){digitalWrite(33,HIGH);} // Dente 4 Fase
       if(contador2 == 1 && contador == 114){digitalWrite(33,LOW);} // Dente 4 Fase
       if(contador2 == 2 && contador == 113){digitalWrite(33,HIGH);} // Dente 7 Fase
       if(contador2 == 2 && contador == 114){digitalWrite(33,LOW);} // Dente 7 Fase
       if(contador > 116 && contador <=120){digitalWrite(31,LOW);} // Quantidade de falha depois da 3 contagem da rotação
    }

    if(contador >= 120)
    {   
      contador = 0;
      contador2 = contador2 + 1;
      if(contador2 > 2){contador2 = 1;}
    }  
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


////////////////////////////////////////////////////////////////////////////////Inicio Setup
void setup()
{
  pinMode(A7, INPUT); 
  pinMode(31,OUTPUT);
  pinMode(33,OUTPUT);
  pinMode(35,OUTPUT);
  
////////////////////////////////////////////////////////////////////////////////Inicio Da Abertura

  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);
  tft.fillScreen(WHITE);
  tft.setRotation(1);
  delay(100);

  Timer1.initialize(200000);                               
  Timer1.attachInterrupt(interrupcao); 

  tft.fillRoundRect(0, 106, 600, 106, 3,  BLACK);
  delay(500);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(85, 150);
  tft.println("Simulador de Sinais");

  delay(2000); 
  tft.fillScreen(BLACK);
}
////////////////////////////////////////////////////////////////////////////////Fim Da Abertura

void loop()
{
  
////////////////////////////////////////////////////////////////////////////////Inicio Menu 1 
  while(menu == 1)
  { 
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);
   
    tft.drawRoundRect(15, 75, 300, 50, 5, WHITE);
    tft.drawRoundRect(15, 135, 300, 50, 5, WHITE);
    tft.drawRoundRect(15, 195, 300, 50, 5, WHITE);
    tft.drawRoundRect(140, 255, 200, 50, 5, WHITE);
  

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(25, 20);
  tft.println("Simulador de Sinais v1.0");

    if(leve == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("Gasolina e Flex");  
    }  
    if(leve == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("Gasolina e Flex");  
    }

    if(dleve == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("Diesel Leve");  
    }  
    if(dleve == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("Diesel Leve");  
    }

    if(dpesa == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 207);
       tft.print("Diesel Pesado");  
    }  
    if(dpesa == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 207);
       tft.print("Diesel Pesado");  
    }
    
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(150, 270);
    tft.print("Selecionar");  
   
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {

       if(p.x > 75 && p.x < 110 && p.y > 15 && p.y < 330)
       {
          delay(100);
          leve = !leve; 
          dleve = 0;
          dpesa = 0;
       }
       if(p.x > 135 && p.x < 170 && p.y > 15 && p.y < 330)
       {
          delay(100);
          dleve = !dleve; 
          dpesa = 0;
          leve = 0;
       }
       if(p.x > 195 && p.x < 230 && p.y > 15 && p.y < 330)
       {
          delay(100);
          dpesa = !dpesa; 
          leve = 0;
          dleve = 0;
       }
       if(p.x > 255 && p.x < 305 && p.y > 140 && p.y < 340)
       {
          delay(100);
          selecionar = !selecionar;
          if(leve == 1){menu = 22;tft.fillScreen(BLACK);}
          if(dleve == 1){menu = 22;tft.fillScreen(BLACK);}
          if(dpesa == 1){menu = 4;tft.fillScreen(BLACK);}
       }
     }
  }
////////////////////////////////////////////////////////////////////////////////Fim Menu 1  
////////////////////////////////////////////////////////////////////////////////Inicio Menu 4 (Marca Diesel Pesado) 
  while(menu == 4)
  {
 
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);
   

    tft.drawRoundRect(15, 75, 220, 50, 5, WHITE);
    tft.drawRoundRect(15, 135, 220, 50, 5, WHITE);
    tft.drawRoundRect(15, 195, 220, 50, 5, WHITE);
    
    tft.drawRoundRect(245, 75, 220, 50, 5, WHITE);
    tft.drawRoundRect(245, 135, 220, 50, 5, WHITE);
    tft.drawRoundRect(245, 195, 220, 50, 5, WHITE);

    tft.drawRoundRect(140, 255, 200, 50, 5, WHITE); //Selecionar
  
//    tft.drawRoundRect(415, 255, 50, 50, 5, WHITE); //Avançar
    tft.drawRoundRect(15, 255, 50, 50, 5, WHITE); //voltar
  

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(25, 20);
  tft.println("Marcas Diesel Pesado");

    if(fordpesado == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("FORD");  
    }  
    if(fordpesado == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("FORD");  
    }

    if(iveco == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("IVECO");  
    }  
    if(iveco == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("IVECO");  
    }

    if(mb == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 207);
       tft.print("MERCEDES");  
    }  
    if(mb == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 207);
       tft.print("MERCEDES");  
    }

    if(scania == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(255, 87);
       tft.print("SCANIA");  
    }  
    if(scania == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(255, 87);
       tft.print("SCANIA");  
    }
    
    if(vwpesado == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(255, 147);
       tft.print("VOLKSWAGEN");  
    }  
    if(vwpesado == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(255, 147);
       tft.print("VOLKSWAGEN");  
    }
    
    if(volvo == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(255, 207);
       tft.print("VOLVO");  
    }  
    if(volvo == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(255, 207);
       tft.print("VOLVO");  
    } 

    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(25, 270);
    tft.print("<-");
    
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(150, 270);
    tft.print("Selecionar");  
      
//    tft.setTextColor(WHITE);
//    tft.setTextSize(3);
//    tft.setCursor(425, 270);
//    tft.print("->"); 
    
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {

       
       if(p.x > 75 && p.x < 110 && p.y > 15 && p.y < 220)
       {
          delay(100);
          fordpesado = !fordpesado;
          iveco = 0;
          mb = 0;
          scania = 0;
          vwpesado = 0;
          volvo = 0;
       }
       if(p.x > 135 && p.x < 170 && p.y > 15 && p.y < 220)
       {
          delay(100);
          fordpesado = 0;
          iveco = !iveco;
          mb = 0;
          scania = 0;
          vwpesado = 0;
          volvo = 0;
       }
       if(p.x > 195 && p.x < 230 && p.y > 15 && p.y < 220)
       {
          delay(100);
          fordpesado = 0;
          iveco = 0;
          mb = !mb;
          scania = 0;
          vwpesado = 0;
          volvo = 0;
       }
       if(p.x > 75 && p.x < 110 && p.y > 245 && p.y < 465)
       {
          delay(100);
          fordpesado = 0;
          iveco = 0;
          mb = 0;
          scania = !scania;
          vwpesado = 0;
          volvo = 0;
       }
       if(p.x > 135 && p.x < 170 && p.y > 245 && p.y < 465)
       {
          delay(100);
          fordpesado = 0;
          iveco = 0;
          mb = 0;
          scania = 0;
          vwpesado = !vwpesado;
          volvo = 0;
       }
       if(p.x > 195 && p.x < 230 && p.y > 245 && p.y < 465)
       {
          delay(100);
          fordpesado = 0;
          iveco = 0;
          mb = 0;
          scania = 0;
          vwpesado = 0;
          volvo = !volvo;
       }

       if(p.x > 255 && p.x < 305 && p.y > 140 && p.y < 340)       {
          delay(100);
          selecionar = !selecionar;
          if(fordpesado == 1){menu = 22;tft.fillScreen(BLACK);}
          if(iveco == 1){menu = 22;tft.fillScreen(BLACK);}          
          if(mb == 1){menu = 22;tft.fillScreen(BLACK);}
          if(scania == 1){menu = 22;tft.fillScreen(BLACK);} 
          if(vwpesado == 1){menu = 22;tft.fillScreen(BLACK);} 
          if(volvo == 1){menu = 22;tft.fillScreen(BLACK);}                     
       }
        if(p.x > 255 && p.x < 305 && p.y > 15 && p.y < 65) //Voltar
        {
           delay(100);
           pagina = !pagina;
          tft.fillScreen(BLACK);
           menu = 1;
        }
       
//        if(p.x > 255 && p.x < 305 && p.y > 415 && p.y < 465) //Proxima pagina
//        {
//           delay(100);
//           tft.fillScreen(BLACK);
//           menu = 41;
//        }
    }
  }
////////////////////////////////////////////////////////////////////////////////Fim Menu 4 (Marca Diesel Pesado)

  while(menu == 22)
  {
 
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);
   

    tft.drawRoundRect(15, 75, 230, 50, 5, WHITE);
    tft.drawRoundRect(15, 135, 230, 50, 5, WHITE);
//    tft.drawRoundRect(15, 195, 170, 50, 5, WHITE);
    

    tft.drawRoundRect(15, 255, 50, 50, 5, WHITE); //Voltar
    tft.drawRoundRect(140, 255, 200, 50, 5, WHITE); //Selecionar
//    tft.drawRoundRect(415, 255, 50, 50, 5, WHITE); //Pagina 2

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);

  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.setCursor(25, 20);
  tft.println("FORD PESADO");

    if(edc7cummins == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("EDC7 CUMMINS");  
    }  
    if(edc7cummins == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 87);
       tft.print("EDC7 CUMMINS");  
    }

    if(motorftp == 0)
    {
       tft.setTextColor(RED);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("MOTOR FTP");  
    }  
    if(motorftp == 1)
    {
       tft.setTextColor(WHITE);
       tft.setTextSize(3);
       tft.setCursor(25, 147);
       tft.print("MOTOR FTP");  
    }

//    if(flag36_1 == 0)
//    {
//       tft.setTextColor(RED);
//       tft.setTextSize(3);
//       tft.setCursor(25, 207);
//       tft.print("36-1 Hall");  
//    }  
//    if(flag36_1 == 1)
//    {
//       tft.setTextColor(WHITE);
//       tft.setTextSize(3);
//       tft.setCursor(25, 207);
//       tft.print("36-1 Hall");  
//    }

    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(25, 270);
    tft.print("<-");
    
//Pagina 2
//    tft.setTextColor(RED);
//    tft.setTextSize(3);
//    tft.setCursor(425, 270);
//    tft.print("->");  

    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(150, 270);
    tft.print("Selecionar");  
   
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {

      
       if(p.x > 75 && p.x < 110 && p.y > 15 && p.y < 230)
       {
          delay(100);
          edc7cummins = !edc7cummins; 
          motorftp = 0;
//          flag36_1 = 0;
       }
       if(p.x > 135 && p.x < 170 && p.y > 15 && p.y < 230)
       {
          delay(100);
          motorftp = !motorftp; 
//          flag36_1 = 0;
          edc7cummins = 0;
       }
//       if(p.x > 195 && p.x < 230 && p.y > 15 && p.y < 170)
//       {
//          delay(100);
//          flag36_1 = !flag36_1; 
//          flag44_4 = 0;
//          flag36_2 = 0;
//       }

//Pagina 2     
//       if(p.x > 255 && p.x < 305 && p.y > 415 && p.y < 465)
//       {
//          delay(100);
//          pagina = !pagina;
//          tft.fillScreen(CYAN);
//          menu = 2;
//       }

       if(p.x > 255 && p.x < 305 && p.y > 140 && p.y < 340)
       {
          delay(100);
          simular = !simular;
          if(edc7cummins == 1 && simular == 1){menu = 12;tft.fillScreen(BLACK);}
          if(motorftp == 1 && simular == 1){menu = 13;tft.fillScreen(BLACK);}
//          if(flag36_1 == 1 && simular == 1){menu = 14;tft.fillScreen(BLACK);}
       }
       if(p.x > 255 && p.x < 305 && p.y > 15 && p.y < 65) //Voltar
        {
           delay(100);
           pagina = !pagina;
          tft.fillScreen(BLACK);
           menu = 4;
        }       
     } 
  }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  while(menu == 12) // FORD PESADO ECD7 CUMMINS
  {
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);
    
    tft.drawRoundRect(415, 255, 50, 50, 5, WHITE);
    
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(425, 270);
    tft.print("<-");

    tft.fillRoundRect(40, 106, barra, 106, 5,  RED);
    tft.fillRoundRect(barra2, 106, (400-barra), 106, 5,  BLACK);
    tft.drawRoundRect(40, 10, 400, 50, 5, WHITE);
    
    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.setCursor(50, 20);
    tft.print("ECD7 CUMMINS");   

    float potenciometro = analogRead(A7);
    delay(10);
    tensao_pot = ((5.0 / 1023.0) * (potenciometro) * 400.0);

    barra = map(tensao_pot,0,2000,0,400); // O ultimo valor corresponde ao limite de RPM. Valor 1000.0 = 5000 RPM
    barra2 = 40 + barra;
    
    rpmAnterior = rpm;
    rpm = 10.0 + tensao_pot; // O valor corresponde a quantidade minima de RPM. Valor 10.0 = 10 RPM                                      
    rps = rpm / 60.0;
    tempo = (1 / (72.0 * rps)) * 1000000.0;                          
    Timer1.setPeriod(tempo);

    tft.setTextColor(BLACK);
    tft.setTextSize(4);
    tft.setCursor(50, 265);
    tft.print("RPM: ");
    tft.print(round(rpmAnterior));

    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.setCursor(50, 265);
    tft.print("RPM: ");
    tft.print(round(rpm));
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
       if(p.x > 255 && p.x < 305 && p.y > 415 && p.y < 465)
       {
          delay(100);
          tft.fillScreen(BLACK);
          menu = 1;
       }
    }
  } 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
  while(menu == 13) //FORD PESADO MOTOR FTP
  {
    TSPoint p = ts.getPoint();
    pinMode(XM, OUTPUT);
    digitalWrite(XM, LOW);
    pinMode(YP, OUTPUT);
    digitalWrite(YP, HIGH);
    pinMode(YM, OUTPUT);
    digitalWrite(YM, LOW);
    pinMode(XP, OUTPUT);
    digitalWrite(XP, HIGH);

    p.x = map(p.x, TS_MAXX, TS_MINX, 0, 320);
    p.y = map(p.y, TS_MAXY, TS_MINY, 0, 480);
    
    tft.drawRoundRect(415, 255, 50, 50, 5, WHITE);
    
    tft.setTextColor(WHITE);
    tft.setTextSize(3);
    tft.setCursor(425, 270);
    tft.print("<-");

    tft.fillRoundRect(40, 106, barra, 106, 5,  RED);
    tft.fillRoundRect(barra2, 106, (400-barra), 106, 5,  BLACK);
    tft.drawRoundRect(40, 10, 400, 50, 5, WHITE);
    
    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.setCursor(50, 20);
    tft.print("   MOTOR FPT");   

    float potenciometro = analogRead(A7);
    delay(10);
    tensao_pot = ((5.0 / 1023.0) * (potenciometro) * 400.0); // O ultimo valor corresponde ao limite de RPM. Valor 1000.0 = 5000 RPM
    barra = map(tensao_pot,0,2000,0,400);
    barra2 = 40 + barra;
    
    rpmAnterior = rpm;
    rpm = 10.0 + tensao_pot;  // O valor corresponde a quantidade minima de RPM. Valor 10.0 = 10 RPM                                  
    rps = rpm / 60.0;
    tempo = (1 / (72.0 * rps)) * 1000000.0;                          
    Timer1.setPeriod(tempo);

    tft.setTextColor(BLACK);
    tft.setTextSize(4);
    tft.setCursor(50, 265);
    tft.print("RPM: ");
    tft.print(round(rpmAnterior));

    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.setCursor(50, 265);
    tft.print("RPM: ");
    tft.print(round(rpm));
  
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE)
    {
       if(p.x > 255 && p.x < 305 && p.y > 415 && p.y < 465)
       {
          delay(100);
          tft.fillScreen(BLACK);
          menu = 1;
       }
    }
  } 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                                                               
}