
/// ASSEMBLY myfunc main

char myfunc(int a)
{
  return 'A';   /** myfunc
                    65,ireturn
                **/
}

int main()
{
  return myfunc(66);  /** main
                          66,invokestatic Method expr_fcall5 myfunc,ireturn
                      **/
}
