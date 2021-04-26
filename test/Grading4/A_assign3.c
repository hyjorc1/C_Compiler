
/// JEXPR test1 test2

int A[15];

int test1()
{
  return A[1] = 8;  /** test1 
    A_assign3.A[\[]1[\]]` = 8,ireturn 8   
    CODE  
    getstatic Field A_assign3 A [\[]I,iconst_1,bipush 8,dup_x2,iastore,ireturn
  **/
}

int test2(int i)
{
  int B[12];
  return B[i++] = 11; /** test2 
    local0` = local0 [+] 1,local1`?[\[]local0[\]]` = 11,ireturn 11  
    CODE  
    aload_1,iload_0,iinc 0 1,bipush 11,dup_x2,iastore,ireturn 
    aload_1,iload_0,dup,iconst_1,iadd,istore_0,bipush 11,dup_x2,iastore,ireturn 
    aload_1,iload_0,iload_0,iconst_1,iadd,istore_0,bipush 11,dup_x2,iastore,ireturn
  **/
}
