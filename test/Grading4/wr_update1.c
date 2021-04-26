
/// JEXPR test1 test2 test3 test4

void test1(int a, int b)
{
  a -= b; /** test1 
    local0` = local0 [-] local1 
    CODE 
    iload_0,iload_1,isub,istore_0 
    iload_0,iload_1,isub,dup,istore_0
  **/
}

void test2(float c, float d)
{
  c += d; /** test2 
    local0` = local0 [+] local1 
    CODE 
    fload_0,fload_1,fadd,fstore_0 
    fload_0,fload_1,fadd,dup,fstore_0
  **/
}

void test3(int a, int b)
{
  a *= b; /** test3 
    local0` = local0 [*] local1 
    CODE 
    iload_0,iload_1,imul,istore_0 
    iload_0,iload_1,imul,dup,istore_0
  **/
}

void test4(float c, float d)
{
  c /= d; /** test4 
    local0` = local0 [/] local1 
    CODE 
    fload_0,fload_1,fdiv,fstore_0 
    fload_0,fload_1,fdiv,dup,fstore_0
  **/
}
