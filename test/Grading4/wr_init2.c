
/// JEXPR thing

void thing()
{
  int a = 12345;  /** thing 
    local[012]` = 12345 
    CODE 
    sipush 12345,istore_[012]
  **/
  char b = 'B';   /** thing 
    local[012]` = 66 
    CODE 
    bipush 66,istore_[012]
  **/
  float e = 2.7182818;  /** thing 
    local[012]` = [+]?2.718282f 
    CODE 
    ldc [+]?2.718282f,fstore_[012]
  **/
}
