
/// JEXPR test1 test2 test3 test4 test5 test6

int G;

void test1()
{
  int a;
  ++a;    /** test1 
      local0` = local0 [+] 1 
      CODE 
      iinc 0 1 
      iload_0,iconst_1,iadd,istore_0 
      iload_0,iconst_1,iadd,dup,istore_0 
  **/
}

void test2()
{
  float b;
  ++b;    /** test2 
      local0` = local0 [+] 1  
      CODE 
      fload_0,fconst_1,fadd,fstore_0 
      fload_0,fconst_1,fadd,dup,fstore_0
  **/
}

int test3(int c)
{
  return ++c; /** test3 
      local0` = local0 [+] 1,ireturn local0` 
      local0` = local0 [+] 1,ireturn local0 [+] 1  
      CODE  
      iinc 0 1,iload_0,ireturn 
      iload_0,iconst_1,iadd,istore_0,iload_0,ireturn 
      iload_0,iconst_1,iadd,dup,istore_0,ireturn
  **/
}

float test4(float d)
{
  return ++d; /** test4 
      local0` = local0 [+] 1,freturn local0` 
      local0` = local0 [+] 1,freturn local0 [+] 1  
      CODE  
      fload_0,fconst_1,fadd,fstore_0,fload_0,freturn 
      fload_0,fconst_1,fadd,dup,fstore_0,freturn
  **/
}

void test5()
{
  ++G;  /** test5 
      wr_incdec1.G` = wr_incdec1.G [+] 1  
      CODE  
      getstatic Field wr_incdec1 G I,iconst_1,iadd,dup,putstatic Field wr_incdec1 G I  
      getstatic Field wr_incdec1 G I,iconst_1,iadd,putstatic Field wr_incdec1 G I
  **/
}

int test6()
{
  return ++G; /** test6 
      wr_incdec1.G` = wr_incdec1.G [+] 1,ireturn wr_incdec1.G` 
      wr_incdec1.G` = wr_incdec1.G [+] 1,ireturn wr_incdec1.G [+] 1  
      CODE  
      getstatic Field wr_incdec1 G I,iconst_1,iadd,dup,putstatic Field wr_incdec1 G I,ireturn  
      getstatic Field wr_incdec1 G I,iconst_1,iadd,putstatic Field wr_incdec1 G I,getstatic Field wr_incdec1 G I,ireturn
  **/
}
