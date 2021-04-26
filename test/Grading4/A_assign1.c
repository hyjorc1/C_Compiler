
/// JEXPR test1 test2 test3 test4

void test1()
{
  char A[12];

  A[0]   = '0'; /** test1  
                    local0`?[\[]0[\]]` = 48   
                    CODE    
                    aload_0,iconst_0,bipush 48,castore 
                    aload_0,iconst_0,bipush 48,dup_x2,castore
                **/
}

void test2(int i)
{
  int A[12];
  A[i]   = 49;  /** test2  
                    local1`?[\[]local0[\]]` = 49   
                    CODE  
                    aload_1,iload_0,bipush 49,iastore 
                    aload_1,iload_0,bipush 49,dup_x2,iastore
                **/
}

void test3(int i)
{
  float A[12];
  A[i-1] = 3.0; /** test3  
                    local1`?[\[]local0 - 1[\]]` = [+]?3.0*f  
                    CODE 
                    aload_1,iload_0,iconst_1,isub,ldc [+]?3.0*f,fastore 
                    aload_1,iload_0,iconst_1,isub,ldc [+]?3.0*f,dup_x2,fastore
                **/
}

void test4(int i)
{
  char A[12];
  A[++i] = '3'; /** test4  
                    local0` = local0 [+] 1,local1`?[\[]local0`[\]]` = 51 
                    local0` = local0 [+] 1,local1`?[\[]local0 [+] 1[\]]` = 51   
                    CODE  
                    aload_1,iload_0,iconst_1,iadd,istore_0,iload_0,bipush 51,dup_x2,castore 
                    aload_1,iload_0,iconst_1,iadd,dup,istore_0,bipush 51,dup_x2,castore 
                    aload_1,iinc 0 1,iload_0,bipush 51,castore 
                    aload_1,iinc 0 1,iload_0,bipush 51,dup_x2,castore
                **/
}
