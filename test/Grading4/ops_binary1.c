
/// JEXPR test1 test2 test3 test4 test5 test6 test7 test8 test9 testA testB

int test1()
{
  return 3 + 4; /** test1 
                    3 [+] 4 
                    CODE 
                    iconst_3,iconst_4,iadd
                **/
}


int test2(int x)
{
  return 15 + x; /** test2 
                      15 [+] local0 
                      CODE 
                      bipush 15,iload_0,iadd
                  **/
}


int test3(int x, int y)
{
  return x + y; /** test3 
                  local0 [+] local1 
                  CODE 
                  iload_0,iload_1,iadd
                **/
}


int test4()
{
  return 33 - 44; /** test4 
      33 [-] 44 
      CODE 
      bipush 33,bipush 44,isub
  **/
}


int test5(int x)
{
  return 15 - x; /** test5 
      15 [-] local0 
      CODE 
      bipush 15,iload_0,isub
  **/
}


int test6(int x, int y)
{
  return x - y; /** test6 
    local0 [-] local1 
    CODE 
    iload_0,iload_1,isub
  **/
}


int test7()
{
  return 33 * 44; /** test7 
    33 [*] 44 
    CODE 
    bipush 33,bipush 44,imul
  **/
}


int test8(int x)
{
  return x * 15; /** test8 
    local0 [*] 15 
    CODE 
    iload_0,bipush 15,imul
  **/
}


int test9(int x, int y)
{
  return y * x; /** test9 
    local1 [*] local0 
    CODE 
    iload_1,iload_0,imul
  **/
}


int testA(int x)
{
  return x % 2; /** testA 
    local0 [%] 2 
    CODE 
    iload_0,iconst_2,irem
  **/
}


int testB(int x, int y, int z)
{
  return x / z; /** testB 
      local0 [/] local2 
      CODE 
      iload_0,iload_2,idiv
  **/
}

