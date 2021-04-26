
/// JEXPR thing

void thing()
{
  int a = 2,  /** thing 
                  local[012]` = 2 
                  CODE 
                  iconst_2,istore_[012]
              **/
      b = 3,  /** thing 
                  local[012]` = 3 
                  CODE 
                  iconst_3,istore_[012]
              **/
      c = 123456789; /** thing 
                  local[012]` = 123456789 
                  CODE 
                  ldc 123456789,istore_[012]
              **/
}
