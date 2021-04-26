
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3

void test1()
{
  char A[10];
  char c;

  c = A[3];   /** test1 
    local[01]`?[\[]3[\]]  
    CODE  
    aload_0,iconst_3,caload
  **/
}

int A[11];

void test2(int b)
{
  b = A[2];   /** test2 
    A_read1.A[\[]2[\]]   
    CODE  
    getstatic Field A_read1 A [\[]I,iconst_2,iaload
  **/
}

void test3(int i)
{
  float F[12];  
  F[i];       /** test3 
    local1`?[\[]local0[\]]  
    CODE  
    aload_1,iload_0,faload
  **/
}
