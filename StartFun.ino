void StartFun()
{
  if (millis() - timerStartFun >= 1000)
  {
    timerStartFun = millis();   // "сбросить" таймер
    curTimeStartFun++;
  }
  
  if (curTimeStartFun < 6)
  {
  ShimFan(pinFan, time1Fan, level1Fan, false);//первый градиент 2 с плюс плато до 5 с
  }
  else if (curTimeStartFun == 6)
  {
    ShimFan(pinFan, 1, 0, true);
  }
  else if (curTimeStartFun > 6 && curTimeStartFun < 45)
  {
     ShimFan(pinFan, time2Fan, level2Fan, false);//всторой градиент 31 с плюс плато
  }
  else if (curTimeStartFun > 45 && curTimeStartFun < 50)
  {
    //запускаем помпу на частоте 2 ГЦ
  }
  else if (curTimeStartFun > 50 && curTimeStartFun < 68)
  {
    ShimFan(pinFan, time3Fan, level3Fan, false);
  }
  else if (curTimeStartFun > 68 && curTimeStartFun < 85)
  {
    ShimFan(pinFan, time4Fan, level4Fan, false);
  }
  else if (curTimeStartFun > 85 && curTimeStartFun < 105)
  {
    ShimFan(pinFan, time5Fan, level5Fan, false);
  }
  else if (curTimeStartFun > 105 && curTimeStartFun < 130)
  {
    ShimFan(pinFan, time6Fan, level6Fan, false);
  }
  //if(прошло 2 секунды)
}
