
/// JEXPR <clinit>


char T='t'; /** <clinit>
    clinit_both.T` = 116
  CODE
    bipush 116,putstatic Field clinit_both T C
**/
char C[1000]; /** <clinit>
    clinit_both.C` = new char[\[]1000[\]]
    CODE
    sipush 1000,newarray char,putstatic Field clinit_both C [\[]C
**/


void thing1();


int count = 37; /** <clinit>
    clinit_both.count` = 37
  CODE
    bipush 37,putstatic Field clinit_both count I
**/
int A[44];  /** <clinit>
    clinit_both.A` = new int[\[]44[\]]
    CODE
    bipush 44,newarray int,putstatic Field clinit_both A [\[]I
**/


void thing2();


float pi = 3.14;  /** <clinit>
    clinit_both.pi` = [+]?3.140*f
  CODE
    ldc [+]?3.140*f,putstatic Field clinit_both pi F
**/
float x[3]; /** <clinit>
    clinit_both.x` = new float[\[]3[\]]
    CODE
    iconst_3,newarray float,putstatic Field clinit_both x [\[]F
**/

