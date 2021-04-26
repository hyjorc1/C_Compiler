
/// JEXPR test1 test2 test3

void print(float x);

void test1(float A[])
{
  print(A[0]); /** test1
      local0[\[]0[\]]
      CODE
      aload_0,iconst_0,faload
  **/
}

void test2(int n, float B[])
{
  test1(B);  /** test2
      calling A_param3::test1[(]local1[)]
      CODE
      aload_1,invokestatic Method A_param3 test1 [(][\[]F[)]V
  **/
}

float X[10];

void test3()
{
  test2(4, X);  /** test3
      calling A_param3::test2[(]4. A_param3[.]X[)]
      CODE
      getstatic Field A_param3 X [\[]F,invokestatic Method A_param3 test2 [(]I[\[]F[)]V
  **/
}
