
/// JEXPR test1 test2 test3 test4

float test1(float a, float b)
{
  return a -= b; /** test1 
    freturn local0` 
    freturn local0 [-] local1 
    CODE 
    fload_0,fload_1,fsub,fstore_0,fload_0,freturn 
    fload_0,fload_1,fsub,dup,fstore_0,freturn
  **/
}

int test2(int c, int d)
{
  return c += d; /** test2 
    ireturn local0` 
    ireturn local0 [+] local1 
    CODE 
    iload_0,iload_1,iadd,istore_0,iload_0,ireturn 
    iload_0,iload_1,iadd,dup,istore_0,ireturn
  **/
}

float test3(float a, float b)
{
  return a *= b; /** test3 
    freturn local0` 
    freturn local0 [*] local1 
    CODE 
    fload_0,fload_1,fmul,fstore_0,fload_0,freturn 
    fload_0,fload_1,fmul,dup,fstore_0,freturn
  **/
}

int test4(int c, int d)
{
  return c /= d; /** test4 
    ireturn local0` 
    ireturn local0 [/] local1 
    CODE 
    iload_0,iload_1,idiv,istore_0,iload_0,ireturn 
    iload_0,iload_1,idiv,dup,istore_0,ireturn
  **/
}
