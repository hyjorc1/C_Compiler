
/// JEXPR test1
/// JEXPR test2

int A[15];

void test1()
{
  A[0] *= 7;   /** test1 
      A_update2.A[\[]0[\]]` = A_update2.A[\[]0[\]] [*] 7   
      CODE  
      getstatic Field A_update2 A [\[]I,dup,iconst_0,dup_x1,iaload,bipush 7,imul,iastore 
      getstatic Field A_update2 A [\[]I,dup,iconst_0,dup_x1,iaload,bipush 7,imul,dup_x2,iastore 
  **/
}

void test2(int i)
{
  A[i++] -= 9; /** test2 
      local0` = local0 [+] 1,A_update2.A[\[]local0[\]]` = A_update2.A[\[]local0[\]] - 9   
      CODE  
      getstatic Field A_update2 A [\[]I,dup,iload_0,iinc 0 1,dup_x1,iaload,bipush 9,isub,dup_x2,iastore 
  **/
}

