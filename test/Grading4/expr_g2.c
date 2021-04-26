
int gx;
float gy;
char gz;

/// JEXPR func1 func2 func3

int func1()
{
  return gx; /** func1 
    expr_g2[.]gx 
    CODE 
    getstatic * Field * expr_g2 * gx * I
  **/
}


float func2()
{
  return gy; /** func2 
    expr_g2[.]gy 
    CODE 
    getstatic * Field * expr_g2 * gy * F
  **/
}


char func3()
{
  return gz; /** func3 
    expr_g2[.]gz 
    CODE 
    getstatic * Field * expr_g2 * gz * C
  **/
}
