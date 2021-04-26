
/// JEXPR test

int why;

int test()
{
  why++;
  return why++; /** test
    smart5.why` = smart5.why [+] 1,smart5.why`` = smart5.why` [+] 1,ireturn smart5.why`
    CODE
    getstatic Field smart5 why I,iconst_1,iadd,putstatic Field smart5 why I,getstatic Field smart5 why I,dup,iconst_1,iadd,putstatic Field smart5 why I
    getstatic Field smart5 why I,iconst_1,iadd,putstatic Field smart5 why I,getstatic Field smart5 why I,getstatic Field smart5 why I,iconst_1,iadd,putstatic Field smart5 why I
  **/
}
