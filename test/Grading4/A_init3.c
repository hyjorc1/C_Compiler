
/// JEXPR test1
/// JEXPR test2
/// JEXPR test3

void test1(int x)
{
  int y;
  char A[10]; /** test1 
                  local[12]` = new char.10. 
                  CODE 
                  bipush 10,newarray char,astore_[12]
              **/
}

void test2(int x)
{
  int y;
  int A[15];  /** test2 
                  local[123]` = new int.15. 
                  CODE 
                  bipush 15,newarray int,astore_[123]
              **/
  int z;
}

void test3(int A, int B, int C)
{
  char  D[21];  /** test3 
                    local[345]` = new char.21.  
                    CODE 
                    bipush 21,newarray char,astore_3 
                    bipush 21,newarray char,astore [45]
                **/

  int   E[22];  /** test3 
                    local[345]` = new int.22. 
                    CODE 
                    bipush 22,newarray int,astore_3 
                    bipush 22,newarray int,astore [45]
                **/

  float F[23];  /** test3 
                    local[345]` = new float.23. 
                    CODE 
                    bipush 23,newarray float,astore_3 
                    bipush 23,newarray float,astore [45]
                **/
}
