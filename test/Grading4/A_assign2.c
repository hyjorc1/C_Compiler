
/// JEXPR test1 test2

int A[15];

void test1()
{
  A[0] = 7;   /** test1
                  A_assign2.A[\[]0[\]]` = 7   
                  CODE  
                  getstatic Field A_assign2 A [\[]I,iconst_0,bipush 7,iastore 
                  getstatic Field A_assign2 A [\[]I,iconst_0,bipush 7,dup_x2,iastore
              **/
}

void test2(int i)
{
  A[i++] = 9; /** test2 
      local0` = local0 [+] 1,A_assign2.A[\[]local0[\]]` = 9   
      CODE  
      getstatic Field A_assign2 A [\[]I,iload_0,iinc 0 1,bipush 9,iastore 
      getstatic Field A_assign2 A [\[]I,iload_0,iinc 0 1,bipush 9,dup_x2,iastore 
      getstatic Field A_assign2 A [\[]I,iload_0,iload_0,iconst_1,iadd,istore_0,bipush 9,iastore 
      getstatic Field A_assign2 A [\[]I,iload_0,iload_0,iconst_1,iadd,istore_0,bipush 9,dup_x2,iastore  
      getstatic Field A_assign2 A [\[]I,iload_0,dup,iconst_1,iadd,istore_0,bipush 9,iastore 
      getstatic Field A_assign2 A [\[]I,iload_0,dup,iconst_1,iadd,istore_0,bipush 9,dup_x2,iastore
  **/
}

