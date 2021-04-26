
/// JEXPR test1

int test1(int a, int b)
{
  a = b = 7;
  b = 8;    
  return 0; /** test1
      local1` = 7,local0` = 7,local1`` = 8,ireturn 0
    CODE
      bipush 7,dup,istore_1,istore_0,bipush 8,istore_1,iconst_0,ireturn
      bipush 7,istore_1,iload_1,istore_0,bipush 8,istore_1,iconst_0,ireturn
  **/
}
