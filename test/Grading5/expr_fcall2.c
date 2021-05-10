
/// ASSEMBLY myfunc main

int myfunc(int a)
{
  return 17;    /** myfunc
                    17,ireturn
                **/
}

int main()
{
  return myfunc(66);  /** main
                          66,invokestatic Method expr_fcall2 myfunc [(]I[)]I,ireturn
                      **/
}
