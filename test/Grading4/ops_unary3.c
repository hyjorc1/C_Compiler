
//
// Type conversions
//

/// JEXPR toint
/// JEXPR tofloat

void dummy1(int a);
void dummy2(float a);

void toint()
{
  dummy1( (int) 'A' );    /** toint 
    65 
    CODE 
    bipush 65
  **/
  dummy1( (int) 44  );    /** toint 
    44 
    CODE 
    bipush 44
  **/
  dummy1( (int) 4.8 );    /** toint 
    f2i[(][+]?4[.]80*f[)] 
    CODE 
    ldc [+]?4[.]80*f,f2i
  **/
}

void tofloat()
{
  dummy2( (float) 44  );  /** tofloat 
    i2f[(]44[)]   
    CODE   
    bipush 44,i2f
  **/
}
