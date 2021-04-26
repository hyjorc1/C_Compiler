
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3

void test1()
{
  char A[10];
  char c;

  c = A[3+4];   /** test1 
    local[01]`?[\[]3 [+] 4[\]]  
    CODE  
    aload_0,iconst_3,iconst_4,iadd,caload
  **/
}

void test2(int b)
{
  int A[11];
  A[ A[1] ];   /** test2 
    local1`?[\[]local1`?[\[]1[\]][\]]  
    CODE  
    aload_1,aload_1,iconst_1,iaload,iaload
  **/
}

void test3(int i)
{
  float A[12];  
  A[i*i+1];       /** test3 
              local1`?[\[]local0 [*] local0 [+] 1[\]] 
              CODE  
              aload_1,iload_0,iload_0,imul,iconst_1,iadd,faload
          **/
}
