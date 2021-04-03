/* 
  These prototypes are not necessary for us in part 4,
  but allow us to also run this through gcc with no warnings,
  and to run this through our compiler for part 3.
*/
int getchar();
int putchar(int x);

int main()
{
  /*
    Read two digits and sum them.
    No spaces between the digits on input.
    No error checking, if the two characters
    are not digits, we get interesting results.

    Also, we do a lot more casting than normal C,
    in case student compilers don't automatically
    coerce types from int to char or char to int
    (this was extra credit in part 3).
  */
  char d1, d2, sum;
  d1 = (char) getchar() - '0';
  d2 = (char) getchar() - '0';
  sum = d1 + d2;
  putchar((int)(d1 + '0')); 
  putchar((int)'+');        
  putchar((int)(d2 + '0'));
  putchar((int)'=');
  /* 
    Print the two digit sum, one digit at a time. 
    Leading digit might be zero, but there's no
    way to suppress that without using if.
  */
  putchar((int)(sum / 10 + '0'));   
  putchar((int)(sum % 10 + '0'));
  putchar((int)'\n');  
  return sum;   /* Produced Java bytecode will show this return value */
}
