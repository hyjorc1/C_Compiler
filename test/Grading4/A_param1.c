
/// JEXPR test1 test2 test3

void test1(char A[])
{
  char c;
  c = A[0]; /** test1
      local1` = local0[\[]0[\]]
      CODE
      aload_0,iconst_0,caload
  **/
}

void test2(int n, char B[])
{
  test1(B);  /** test2
      calling A_param1::test1[(]local1[)]
      CODE
      aload_1,invokestatic Method A_param1 test1 [(][\[]C[)]V
  **/
}

void test3()
{
  char C[4];
  test2(4, C);  /** test3
      calling A_param1::test2[(]4. local0`?[)]
      CODE
      aload_0,invokestatic Method A_param1 test2 [(]I[\[]C[)]V
  **/
}
