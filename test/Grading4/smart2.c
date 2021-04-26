
/// JEXPR test2

float test2(float x) 
{
  float y;

  x = y += 6.2;
  y += 6.3;  
  return 0.0; /** test2
      local1` = local1 [+] [+]?6[.]20*f,local0` = local1 [+] [+]?6[.]20*f,local1`` = local1` [+] [+]?6[.]30*f,freturn 0
    CODE
      fload_1,ldc [+]?6[.]20*f,fadd,dup,fstore_1,fstore_0,fload_1,ldc [+]?6[.]30*f,fadd,fstore_1,fconst_0,freturn
      fload_1,ldc [+]?6[.]20*f,fadd,fstore_1,fload_1,fstore_0,fload_1,ldc [+]?6[.]30*f,fadd,fstore_1,fconst_0,freturn
  **/
}
