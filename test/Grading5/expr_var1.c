
/// ASSEMBLY main

int putchar(int c);

int main()
{
  int a;
  a = 49;   /** main
                49,?dup,istore_0
            **/

  putchar(a);   /** main
                    iload_0,putchar
                **/
  putchar(10);
  return 0;
}
