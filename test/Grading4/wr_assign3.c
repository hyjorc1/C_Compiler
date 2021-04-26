
/// JEXPR test1 test2 test3

int test1(int a)
{
  return a=2; /** test1 
    ireturn 2 
    ireturn local0` 
    CODE 
    iconst_2,istore_0,iload_0,ireturn 
    iconst_2,dup,istore_0,ireturn
  **/
}

char test2(char c)
{
  return c='X'; /** test2 
    ireturn 88 
    ireturn local0` 
    CODE 
    bipush 88,istore_0,iload_0,ireturn 
    bipush 88,dup,istore_0,ireturn
  **/
}

float test3(float f)
{
  return f=3.5; /** test3 
    freturn [+]?3.50*f 
    freturn local0` 
    CODE 
    ldc [+]?3.50*f,fstore_0,fload_0,freturn 
    ldc [+]?3.50*f,dup,fstore_0,freturn
  **/
}
