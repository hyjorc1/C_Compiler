
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3
/// JEXPR test4

void test1()
{
  char A[12];

  A[0]  += '0'; /** test1  
      local0`?[\[]0[\]]` = i2c[(]local0`?[\[]0[\]] [+] 48[)]   
      CODE    
      aload_0,dup,iconst_0,dup_x1,caload,bipush 48,iadd,i2c,castore 
      aload_0,dup,iconst_0,dup_x1,caload,bipush 48,iadd,i2c,dup_x2,castore
  **/
}

void test2(int i)
{
  int A[12];
  A[i]  *= 49; /** test2  
      local1`?[\[]local0[\]]` = local1`?[\[]local0[\]] [*] 49   
      CODE  
      aload_1,dup,iload_0,dup_x1,iaload,bipush 49,imul,iastore 
      aload_1,dup,iload_0,dup_x1,iaload,bipush 49,imul,dup_x2,iastore
  **/
}

void test3(int i)
{
  float A[12];
  A[i-1] /= 3.0; /** test3  
      local1`?[\[]local0 - 1[\]]` = local1`?[\[]local0 - 1[\]] [/] [+]?3.0*f  
      CODE 
      aload_1,dup,iload_0,iconst_1,isub,dup_x1,faload,ldc [+]?3.0*f,fdiv,fastore 
      aload_1,dup,iload_0,iconst_1,isub,dup_x1,faload,ldc [+]?3.0*f,fdiv,dup_x2,fastore
  **/
}

void test4(int i)
{
  char A[12];
  A[++i] -= '3'; /** test4  
      local0` = local0 [+] 1,local1`?[\[]local0`[\]]` = i2c[(]local1`?[\[]local0`[\]] - 51[)] 
      local0` = local0 [+] 1,local1`?[\[]local0 [+] 1[\]]` = i2c[(]local1`?[\[]local0 [+] 1[\]] - 51[)]
      CODE  
      aload_1,dup,iinc 0 1,iload_0,dup_x1,caload,bipush 51,isub,i2c,castore 
      aload_1,dup,iinc 0 1,iload_0,dup_x1,caload,bipush 51,isub,i2c,dup_x2,castore
  **/
}
