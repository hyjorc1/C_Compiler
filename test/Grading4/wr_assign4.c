
/// JEXPR test1 test2

int gi;
char gc;
float gf;

void test1()
{
  gi = 7;     /** test1 
      wr_assign4.gi` = 7 
      CODE 
      putstatic Field wr_assign4 gi I
  **/
  gc = '#';   /** test1 
      wr_assign4.gc` = 35 
      CODE 
      putstatic Field wr_assign4 gc C
  **/
  gf = 3.5;   /** test1 
      wr_assign4.gf` = [+]?3[.]50*f 
      CODE 
      putstatic Field wr_assign4 gf F
  **/
}

int test2()
{
  return gi=9;  /** test2 
      ireturn 9  
      ireturn wr_assign4.gi` 
      CODE 
      bipush 9,putstatic Field wr_assign4 gi I,getstatic Field wr_assign4 gi I,ireturn 
      bipush 9,dup,putstatic Field wr_assign4 gi I,ireturn
  **/
}
