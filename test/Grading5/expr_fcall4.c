
/// ASSEMBLY other main

void other()
{
  putchar(77);
  return;       /** other
                    return
                **/
}

int main()
{
  other();    /** main
                  invokestatic Method expr_fcall4 other [(][)]V
              **/

  return 5;
}
