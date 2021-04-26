
/// JEXPR test3 test4

void test1(char A[])
{
  char c;
  c = A[0];
}

char test2(int n, char B[])
{
  return B[n];
}

void test3()
{
  test1("Hello"); /** test3
      calling A_string::test1[(][']Hello\x00['][.]toCharArray[(][)][)]
      calling A_string::test1[(][']Hello['][.]toCharArray[(][)][)]
      CODE
      ldc [']Hello.?x00['],invokevirtual Method java/lang/String toCharArray [(][)][\[]C,invokestatic Method A_string test1 [(][\[]C[)]V 
      ldc [']Hello['],invokevirtual Method java/lang/String toCharArray [(][)][\[]C,invokestatic Method A_string test1 [(][\[]C[)]V 
  **/
}

void test4()
{
  char x;
  x = test2(5, "world!"); /** test4
      calling A_string::test2[(]5. [']world[!]\x00['][.]toCharArray[(][)][)]
      calling A_string::test2[(]5. [']world[!]['][.]toCharArray[(][)][)]
      CODE
      ldc [']world!.?x00['],invokevirtual Method java/lang/String toCharArray [(][)][\[]C,invokestatic Method A_string test2 [(]I[\[]C[)]C
      ldc [']world!['],invokevirtual Method java/lang/String toCharArray [(][)][\[]C,invokestatic Method A_string test2 [(]I[\[]C[)]C
  **/
}

