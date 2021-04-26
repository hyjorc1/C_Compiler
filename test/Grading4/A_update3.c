
/// JEXPR test1
/// JEXPR test2

int A[15];

int test1()
{
  return A[1] += 8;  /** test1 
    A_update3.A[\[]1[\]]` = A_update3.A[\[]1[\]] [+] 8,ireturn A_update3.A[\[]1[\]] [+] 8   
    CODE  
    getstatic Field A_update3 A [\[]I,dup,iconst_1,dup_x1,iaload,bipush 8,iadd,dup_x2,iastore,ireturn
  **/
}

int test2(int i)
{
  int B[12];
  return B[i++] -= 11; /** test2 
      local0` = local0 [+] 1,local1`?[\[]local0[\]]` = local1`?[\[]local0[\]] - 11,ireturn local1`?[\[]local0[\]] - 11  
      CODE  
      aload_1,dup,iload_0,iinc 0 1,dup_x1,iaload,bipush 11,isub,dup_x2,iastore,ireturn 
  **/
}
