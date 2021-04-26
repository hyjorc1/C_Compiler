
/// JEXPR test1 test2

int n;

void test1()
{
  n += 7; /** test1 
    wr_update3.n` = wr_update3.n [+] 7 
    CODE 
    getstatic Field wr_update3 n I,bipush 7,iadd,dup,putstatic Field wr_update3 n I 
    getstatic Field wr_update3 n I,bipush 7,iadd,putstatic Field wr_update3 n I
  **/
}

int test2()
{
  return n -= 5; /** test2 
    ireturn wr_update3.n ([-] 5)? 
    CODE 
    getstatic Field wr_update3 n I,iconst_5,isub,dup,putstatic Field wr_update3 n I,ireturn 
    getstatic Field wr_update3 n I,iconst_5,isub,putstatic Field wr_update3 n I,getstatic Field wr_update3 n I,ireturn
  **/
}
