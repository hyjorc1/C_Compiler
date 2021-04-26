
/// JEXPR test1 test2 test3

int test1(int A[])
{
  return A[0]; /** test1
      ireturn local0[\[]0[\]]
      CODE
      aload_0,iconst_0,iaload
  **/
}

void test2(int n, int B[])
{
  test1(B);  /** test2
      calling A_param2::test1[(]local1[)]
      CODE
      aload_1,invokestatic Method A_param2 test1 [(][\[]I[)]I
  **/
}

void test3()
{
  int C[4];
  test2(4, C);  /** test3
      calling A_param2::test2[(]4. local0`?[)]
      CODE
      aload_0,invokestatic Method A_param2 test2 [(]I[\[]I[)]V
  **/
}
