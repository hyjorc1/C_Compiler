// File: ifdefs1.c

#define A
#define B
#define C

#ifdef A
    #ifdef B
        #ifdef C
            7 
        #else
            6
        #endif
    #else
        #ifdef C
            5
        #else
            4
        #endif
    #endif
#else
    #ifdef B
        #ifdef C
            3
        #else
            2
        #endif
    #else
        #ifdef C
            1
        #else
            0
        #endif
    #endif
#endif
