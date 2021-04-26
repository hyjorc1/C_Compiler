
/// JEXPR <clinit>

char T='t'; /** <clinit>
    clinit_var.T` = 116
  CODE
    bipush 116,putstatic Field clinit_var T C
**/

void thing1();

int count = 37; /** <clinit>
    clinit_var.count` = 37
  CODE
    bipush 37,putstatic Field clinit_var count I
**/

void thing2();

float pi = 3.14;  /** <clinit>
    clinit_var.pi` = [+]?3.140*f
  CODE
    ldc [+]?3.140*f,putstatic Field clinit_var pi F
**/

