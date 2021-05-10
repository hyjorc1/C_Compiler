
/// ASSEMBLY main

int main()
{
  int L;

  L=108;

  putchar(72);
  putchar(101);

  putchar(putchar(L));  /** main
      iload_0,invokestatic Method libc putchar,invokestatic Method libc putchar
  **/

  putchar(111);
  putchar(10);
  return 0;
}
