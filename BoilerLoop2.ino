//========Main===========
#include "GyverButton.h"
GButton butStart(3);//Пин для кнопки Start
bool start;
#define potent_pin 1 
//========Main==============
//=========BoilerLoop=======
int tempCoolate;
int ust_tempCooleteHighLevel = 86;
int ust_tempCooleteLowLevel = 75;
bool hysteresisTempOff;
//=========BoilerLoop=======
//=========shim==============
int ledPin = 8;
int ledBrightness = 0;
int ledSte = 5;
//=========shim==============


//=========shimGlow==============
byte pinGlow = 7;
byte levelGlow;
byte modeGlow;
byte ust1_levelGlow = 255;
byte ust2_levelGlow = 180;
//=========shimGlow=============

//=========ShimFan==============
byte pinFan = 8;
bool fanOff; //выключение вентилятора
byte pinLevelFan = 0; //Глобальная переменная текущего сигнала пина вентелятора
int stap1Fan;   //Глобальная переменная шага инкриментации/декриментации
int time1Fan = 2000; //Уставка времени первого градиента
byte level1Fan = 153; //Уставка конечного уровня первого градиента
int time2Fan = 31000; //Уставка времени второго градиента
byte level2Fan = 51; //Уставка конечного уровня второго градиента
int time3Fan = 18000; //Уставка времени третьего градиента
byte level3Fan = 102; //Уставка конечного уровня третьего градиента
int time4Fan = 17000; //Уставка времени четвертого градиента
byte level4Fan = 191; //Уставка конечного уровня четвертого градиента
int time5Fan = 20000; //Уставка времени пятого градиента
byte level5Fan = 255; //Уставка конечного уровня пятого градиента
int time6Fan = 20000; //Уставка времени шестого градиента
byte level6Fan = 255; //Уставка конечного уровня шестого градиента
unsigned long timerFan;
bool incK; //Глобальная переменная вычисления шага инкримента
bool decK; //Глобальная переменная вычисления шага декремента
//=========ShimFan==============

//========StartFun===========
unsigned long timerStartFun;
unsigned long curTimeStartFun; //Текущее время функции StartFun дискретизация 1 с
//========StartFun===========

//=========DosPump===========
byte pinPump = 9;
int pinLevelPump = 0;//Глобальная переменная текущего временнОго интервала моргания пина помпы
int stapPump; //Глобальная переменная шага инкриментации/декриментации
float freqPumpCur; 
float freqPump = 5; //задаваемая частота помпы в герцах
int u_time1Pump = 5000; //уставка первого отрезка времени за которое нужно изменять частоту
float u_scalePump = 10.; //масштаб
unsigned long timerPump;
bool flagPump;
bool pumpPinState;
bool inckPump;
bool deckPump;
bool pumpOn = true;
bool pumpOff = false;
//=========DosPump===========

void setup() {
  Serial.begin(9600);
  butStart.setDebounce(150);
  butStart.setTimeout(500);
  //=========DosPump===========
 // timerPump = millis();
  pinMode(9, OUTPUT);// установка пина как ВЫХОД
  //=========DosPump===========
  //Serial.begin(butStart);

}

void loop() {

  Serial.println("$");
  Serial.println(pinLevelFan);
  Serial.println(" ");
  Serial.println(start * 100);
  Serial.println(" ");
  Serial.println(curTimeStartFun);
  Serial.println(";");
  
  butStart.tick();
  //shim(ledPin);

  tempCoolate = analogRead(potent_pin) / 8;

  if (butStart.isPress())
  {
    start = true;
  }
  if (butStart.isDouble())
  {
    start = false;
  }

  if (start)
  {
    TempInterlocks();
    if (hysteresisTempOff) //Превышение верхнего порога температуры
    {//#Прописать функцию гашения котла
     
      DosPump(pinPump, u_time1Pump, freqPump, u_scalePump, pumpOn);
      ShimFan(pinFan, time1Fan, 0, true);
      ShimGlow(pinGlow, 0);
    }
    else                  //Переход нижней границы порога температуры
    {
      //#запустить таймер
      //#if(время таймера не истекло(125с)){
      StartFun(); //#Запустить функцию запуска}
     
      //#if(время таймера больше 125с){
      //#запустить функцию}
     
      //DosPump(pinPump, u_time1Pump, freqPump, u_scalePump, pumpOff);
      //ShimFan(pinFan, time1Fan, level1Fan);
      ShimGlow(pinGlow, ust1_levelGlow);
    }
  }
  if (!start)
  { //#Прописать функцию гашения котла
   
    DosPump(pinPump, u_time1Pump, 0, u_scalePump, pumpOff);
    ShimFan(pinFan, 1, 0, true);
    ShimGlow(pinGlow, 0);
    curTimeStartFun = 0; //сброс текущего времени функции StartFun
  }  
}
