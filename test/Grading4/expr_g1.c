
int gx;
float gy;
char gz;

/// JEXPR func1

void func1()
{
  gx; /** func1 
    expr_g1[.]gx 
    CODE 
    getstatic * Field * expr_g1 * gx * I
  **/
}

/// JEXPR func2

void func2()
{
  gy; /** func2 
    expr_g1[.]gy 
    CODE 
    getstatic * Field * expr_g1 * gy * F
  **/
}

/// JEXPR func3

void func3()
{
  gz; /** func3 
    expr_g1[.]gz 
    CODE 
    getstatic * Field * expr_g1 * gz * C
  **/
}
