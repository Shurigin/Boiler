void ShimFan (byte pin, int time1, byte level1, bool off)
{
  if (off)
  {
    pinLevelFan = 0;
    analogWrite(pin, pinLevelFan);
  }
  else
  {
    //if (pinLevelFan >= 0 && pinLevelFan <= (level1Fan - 1))
    if ((level1 - pinLevelFan) > 0)
    {
      if (!incK) //Вычисление шага в начальный момент времени для инкримента
      {
        stap1Fan = time1 / (level1 - pinLevelFan);
        incK = true;
      }

      if (millis() - timerFan >= stap1Fan)
      {
        timerFan = millis();   // "сбросить" таймер
        pinLevelFan++;
      }
    }
    else
    {
      incK = false;
    }
    if ((level1 - pinLevelFan) < 0)
    {
      if (!decK) //Вычисление шага в начальный момент времени для декремента
      {
        stap1Fan = time1 / (pinLevelFan - level1);
        decK = true;
      }
      if (millis() - timerFan >= stap1Fan)
      {
        timerFan = millis();   // "сбросить" таймер
        pinLevelFan--;
      }
    }
    else
    {
      decK = false;
    }
    analogWrite(pin, pinLevelFan);
  }
}
