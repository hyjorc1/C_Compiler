
//
// More negation tests
//

void dummy1(char a);
void dummy2(int b);
void dummy3(float c);

/// JEXPR test
void test()
{
  dummy1( -('A') );   /** test 
      i2c[(][-] *65[)] 
      CODE 
      bipush 65,ineg,i2c
  **/
  dummy2( -(3)   );   /** test 
      [-] *3 
      CODE 
      iconst_3,ineg
  **/
  dummy3( -(4.5) );   /** test 
      [-] *[+]?4[.]50*f 
      CODE 
      ldc [+]?4[.]50*f,fneg
  **/
}
