void ShimGlow(byte pin, byte level)
{
  levelGlow = level;
  analogWrite(pin, level);
}
