
/// JEXPR consts

void consts()
{
  char C;
  int I;
  float F;

  C = 'C';          /** consts 
    67 
    CODE 
    bipush 67 
  **/
  I = 345;          /** consts 
    345 
    CODE 
    sipush 345
  **/
  F = 3.14;         /** consts 
    [+]?3.140*f 
    CODE 
    ldc [+]?3.140*f 
  **/
}
