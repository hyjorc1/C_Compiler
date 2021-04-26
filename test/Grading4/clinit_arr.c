
/// JEXPR <clinit>

int A[44];  /** <clinit>
    clinit_arr.A` = new int[\[]44[\]]
    CODE
    bipush 44,newarray int,putstatic Field clinit_arr A [\[]I
**/


char C[1000]; /** <clinit>
    clinit_arr.C` = new char[\[]1000[\]]
    CODE
    sipush 1000,newarray char,putstatic Field clinit_arr C [\[]C
**/


float x[3]; /** <clinit>
    clinit_arr.x` = new float[\[]3[\]]
    CODE
    iconst_3,newarray float,putstatic Field clinit_arr x [\[]F
**/
