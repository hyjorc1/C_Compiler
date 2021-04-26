
/// JEXPR const1
/// JEXPR const2
/// JEXPR const3

char const1()
{
  return 'B';   /** const1 
      ireturn 66 
      CODE 
      bipush 66
  **/
}


int const2()
{
  return 1234;  /** const2 
      ireturn 1234 
      CODE 
      sipush 1234
  **/
}


float const3()
{
  return 5.5;   /** const3 
      freturn [+]?5.50*f 
      CODE 
      ldc [+]?5.50*f
  **/
}

