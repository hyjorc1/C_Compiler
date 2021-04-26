
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3
/// JEXPR test4
/// JEXPR test5
/// JEXPR test6
/// JEXPR test7
/// JEXPR test8
/// JEXPR test9
/// JEXPR testB

float test1()
{
  return 3.0 + 4.1; /** test1 
    [+]?3[.]0*f [+] [+]?4[.]10*f 
    CODE 
    ldc [+]?3[.]0*f,ldc [+]?4[.]10*f,fadd
  **/
}


float test2(float x)
{
  return 1.5 + x; /** test2 
    [+]?1[.]50*f [+] local0 
    CODE 
    ldc [+]?1[.]50*f,fload_0,fadd
  **/
}


float test3(float x, float y)
{
  return x + y; /** test3 
    local0 [+] local1 
    CODE 
    fload_0,fload_1,fadd
  **/
}


float test4()
{
  return 3.3 - 1.0; /** test4 
    [+]?3[.]30*f [-] [+]?1([.]0*f)? 
    CODE 
    ldc [+]?3[.]30*f,fconst_1,fsub
  **/
}


float test5(float x)
{
  return 1.5 - x; /** test5 
    [+]?1[.]50*f [-] local0 
    CODE 
    ldc [+]?1[.]50*f,fload_0,fsub
  **/
}


float test6(float x, float y)
{
  return x - y; /** test6 
    local0 [-] local1 
    CODE 
    fload_0,fload_1,fsub
  **/
}


float test7()
{
  return 3.3 * 4.4; /** test7 
    [+]?3[.]30*f [*] [+]?4[.]40*f 
    CODE 
    ldc [+]?3[.]30*f,ldc [+]?4[.]40*f,fmul
  **/
}


float test8(float x)
{
  return x * 2.0; /** test8 
    local0 [*] [+]?2([.]0*f)? 
    CODE 
    fload_0,fconst_2,fmul
  **/
}


float test9(float x, float y)
{
  return y * x; /** test9 
    local1 [*] local0 
    CODE 
    fload_1,fload_0,fmul
  **/
}


float testB(float x, float y, float z)
{
  return x / z; /** testB 
    local0 [/] local2 
    CODE 
    fload_0,fload_2,fdiv
  **/
}

