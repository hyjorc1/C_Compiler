
/// JEXPR thing1 thing2 thing3

void thing1()
{
  int a;

  a = 1;  /** thing1 
    local0` = 1 
    CODE 
    iconst_1,istore_0 
    iconst_1,dup,istore_0
  **/
}

void thing2(int a)
{
  float b;

  b = 0.0;  /** thing2 
    local1` = 0([.]0*f)? 
    CODE 
    fconst_0,fstore_1 
    fconst_0,dup,fstore_1
  **/
}

void thing3(int a, float b)
{
  char c;

  c = 'C';   /** thing3 
      local2` = 67 
      CODE 
      bipush 67,istore_2 
      bipush 67,dup,istore_2
  **/
}
