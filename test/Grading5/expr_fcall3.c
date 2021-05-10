
/// ASSEMBLY recurse

int recurse(int a, int b)
{
  return recurse(b, a); /** recurse
    iload_1,iload_0,invokestatic Method expr_fcall3 recurse [(]II[)]I,ireturn
  **/
}
