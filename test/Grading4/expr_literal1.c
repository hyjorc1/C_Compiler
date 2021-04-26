
/// JEXPR consts

void dummy1(char a)
{
  return;
}

void dummy2(int a)
{
  return;
}

void dummy3(float a)
{
  return;
}

void consts()
{
  dummy1('A');          /** consts 
    65 
    CODE 
    bipush 65 
  **/
  dummy2(4);            /** consts 
    4 
    CODE 
    iconst_4 
    bipush 4
  **/
  dummy3(3.1415926);    /** consts 
    [+]?3.141593f 
    CODE 
    ldc [+]?3.141593f 
  **/
}
