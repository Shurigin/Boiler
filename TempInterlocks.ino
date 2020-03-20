void TempInterlocks()
{
  if (tempCoolate >= ust_tempCooleteHighLevel)
    {
      hysteresisTempOff = true;
    }
    if (tempCoolate < ust_tempCooleteLowLevel)
    {
      hysteresisTempOff = false;
    }
}
