
/// JEXPR test

void test(int a)
{
  int b;
  ++a;
  b = ++a;
  return; /** test
    local0` = local0 [+] 1,local0`` = local0` [+] 1,local1` = local0``
    local0` = local0 [+] 1,local0`` = local0` [+] 1,local1` = local0` [+] 1
    CODE
    iinc 0 1,iinc 0 1,iload_0,istore_1,return
  **/
}

