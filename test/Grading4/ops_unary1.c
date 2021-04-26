
//
// Negation tests
//

/// JEXPR cnegate

char cnegate(char x)
{
  return -x;  /** cnegate 
    [-] *local0 
    CODE 
    ineg,i2c
  **/
}

/// JEXPR inegate

int inegate(int x)
{
  return -x;  /** inegate 
    [-] *local0 
    CODE 
    ineg
  **/
}

/// JEXPR fnegate

float fnegate(float x)
{
  return -x;  /** fnegate 
    [-] *local0 
    CODE 
    fneg
  **/
}
