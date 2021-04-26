
/// JEXPR test1

char test1()
{
  return '!' + '('; /** test1 
    3 [+] 40 
    CODE 
    bipush 33,bipush 40,iadd,i2c
  **/
}

/// JEXPR test2

char test2(char x)
{
  return '\n' + x; /** test2 
    10 [+] local0 
    CODE 
    bipush 10,iload_0,iadd,i2c
  **/
}

/// JEXPR test3

char test3(char x, char y)
{
  return x + y; /** test3 
    local0 [+] local1 
    CODE 
    iload_0,iload_1,iadd,i2c
  **/
}

/// JEXPR test4

char test4()
{
  return 'T' - '#'; /** test4 
    84 [-] 35 
    CODE 
    bipush 84,bipush 35,isub,i2c
  **/
}

/// JEXPR test5

char test5(char x)
{
  return x - ' '; /** test5 
    local0 [-] 32 
    CODE 
    iload_0,bipush 32,isub,i2c
  **/
}

/// JEXPR test6

char test6(char x, char y)
{
  return x - y; /** test6 
    local0 [-] local1 
    CODE 
    iload_0,iload_1,isub,i2c
  **/
}

/// JEXPR test7

char test7()
{
  return '2' * '3'; /** test7 
    50 [*] 51 
    CODE 
    bipush 50,bipush 51,imul,i2c
  **/
}

/// JEXPR test8

char test8(char x)
{
  return x * '0'; /** test8 
    local0 [*] 48 
    CODE 
    iload_0,bipush 48,imul,i2c
  **/
}

/// JEXPR test9

char test9(char x, char y)
{
  return y * x; /** test9 
    local1 [*] local0 
    CODE 
    iload_1,iload_0,imul,i2c
  **/
}

