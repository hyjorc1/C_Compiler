#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tokens.h"
#include "global.h"

int debug = 1;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printusage();
        return 0;
    }

    int fileIdx = 2;

    /* set output file */
    if (argc >= 4 && !strcmp(argv[2], "-o")) {
        freopen(argv[3], "w", stdout);
        fileIdx = 4;
    }

    if (!strcmp(argv[1], "-0")) {
        printversion();
    } else {
        if (fileIdx >= argc) {
            fprintf(stderr, "Modes 1 to 5 need input files\n");
        } else if (!strcmp(argv[1], "-1")) {
            mode1(argc, argv, fileIdx);
        } else if (!strcmp(argv[1], "-2")) {
            mode2(argc, argv, fileIdx);
        } else if (strlen(argv[1]) >= 2 && argv[1][1] >= '1' && argv[1][1] <= '5') {
            fprintf(stderr, "The other modes are not implemented.\n");
        } else {
            printusage();
        }
    }    
    return 0;
}

