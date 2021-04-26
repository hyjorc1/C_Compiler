
/// JEXPR thing

void thing()
{
  int a;
  char b;
  float e;

  e = 2.7182818;  /** thing 
    local[012]` = [+]?2.718282f 
    CODE 
    ldc [+]?2.718282f,fstore_[012] 
    ldc [+]?2.718282f,dup,fstore_[012] 
  **/
  b = 'B';   /** thing 
    local[012]` = 66 
    CODE 
    bipush 66,istore_[012] 
    bipush 66,dup,istore_[012]
  **/
  a = 12345;  /** thing 
    local[012]` = 12345 
    CODE 
    sipush 12345,istore_[012] 
    sipush 12345,dup,istore_[012]
  **/
}
