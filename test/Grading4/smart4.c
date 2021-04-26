
/// JEXPR test

int test(int a)
{
  a++;
  return a++; /** test
    local0` = local0 [+] 1,local0`` = local0` [+] 1,ireturn local0`
    CODE
    iinc 0 1,iload_0,iinc 0 1,ireturn
  **/
}

