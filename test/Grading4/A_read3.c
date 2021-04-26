
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3

int test1(int i)
{
  int A[17];
  return A[i];  /** test1 
    ireturn local1`?[\[]local0[\]]  
    CODE  
    aload_1,iload_0,iaload,ireturn
  **/
}

void test2()
{
  int A[11];
  test1(A[2]);  /** test2 
    A_read3::test1[(]local0`?[\[]2[\]][)] 
    CODE  
    aload_0,iconst_2,iaload,invokestatic Method A_read3 test1 [(]I[)]I
  **/
}

void test3(int i)
{
  float A[12];  
  A[test1(i)];    /** test3 
    local1`?[\[]A_read3::test1[(]local0[)][\]]  
    CODE  
    aload_1,iload_0,invokestatic Method A_read3 test1 [(]I[)]I,faload
  **/
}
