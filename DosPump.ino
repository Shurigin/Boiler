void DosPump(byte pin, byte stepPump, bool pinStat)
{
  if (pinStat)
  {
    digitalWrite(pin, LOW);
  }
  else
  {
    if (millis() - timerPump > stepPump)
    {
      timerPump = millis();
      if (flagPump == false)
      {
        flagPump = true;
      }
      else
      {
        flagPump = false;
      }
    }
    if (flagPump == true)
    {
      digitalWrite(pin, HIGH);
    }
    else
    {
      digitalWrite(pin, LOW);
    }
  }

}
