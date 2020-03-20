void DosPump(byte pin, int time1, float freq, float scale, bool pinStat)
{
  if ((freq - freqPumpCur) > 0)
  {
    if (!inckPump) //разовая проверка шага для инкримента
    {
      stapPump = time1 / ((freq - freqPumpCur) * scale);
      inckPump = true;
      
    }
    
    if (millis() - timerPump >= stapPump)
    {
      timerPump = millis();
      freqPumpCur = freqPumpCur + 1/scale;
    }
    
  }    
  else
  {
    inckPump = false;
  }
  if ((freq - freqPumpCur) < 0)
  {
    if(!deckPump)
    {
      stapPump = time1 / ((freqPumpCur - freq) * scale);
      deckPump = true;
    }
    if (millis() - timerPump >= stapPump)
    {
      timerPump = millis();
      freqPumpCur = freqPumpCur - (1 / scale);
    }

  }
  else
  {
    deckPump = false;
  }


  pinLevelPump = 1000 / freqPumpCur; //Допилить пересчет скорости помпы в временнУю величину
  if (pinStat)
  {
    if (millis() - timerPump >= pinLevelPump) {
      timerPump = millis();   // "сбросить" таймер
      if (flagPump == false) {
        flagPump = true;
      }
      else {
        flagPump = false;
      }
      if (flagPump == true) {
        digitalWrite(pin, HIGH);
      }
      else {
        digitalWrite(pin, LOW);
      }
      // дейтвия, которые хотим выполнить один раз за период
    }
  }
  else
  {
    digitalWrite(pin, LOW);
  }
  
}
