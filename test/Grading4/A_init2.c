
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3

void test1(int x)
{
  char A[10]; /** test1 
                  local1` = new char[\[]10[\]]  
                  CODE  
                  bipush 10,newarray char,astore_1
              **/
}

void test2(int x, int y)
{
  int A[15];  /** test2 
                  local2` = new int[\[]15[\]] 
                  CODE  
                  bipush 15,newarray int,astore_2
              **/
}

void test3(int x, int y, int z)
{
  float B[22];  /** test3 
                    local3` = new float[\[]22[\]]   
                    CODE 
                    bipush 22,newarray float,astore_3
                **/
}
