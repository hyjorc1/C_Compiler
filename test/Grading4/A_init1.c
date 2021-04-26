
/// JEXPR test1 
/// JEXPR test2
/// JEXPR test3

void test1()
{
  char A[10]; /** test1 
                  local0` = new char[\[]10[\]]
                  CODE  
                  bipush 10,newarray char,astore_0
              **/
}

void test2()
{
  int A[15];  /** test2 
                  local0` = new int[\[]15[\]]
                  CODE  
                  bipush 15,newarray int,astore_0
              **/
}

void test3()
{
  float B[22];  /** test3 
                    local0` = new float[\[]22[\]]   
                    CODE 
                    bipush 22,newarray float,astore_0
                **/
}
