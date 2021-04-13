#include "global.h"

int debug = 0; /* set 1 to trigger debug mode */
int mode = -1;
char *output_file = NULL;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        printusage();
        return 0;
    }

    int fileIdx = 2;

    /* set output file */
    if (argc >= 4 && !strcmp(argv[2], "-o")) {
        output_file = argv[3];
        freopen(output_file, "w", stdout);
        fileIdx = 4;
    }

    if (!strcmp(argv[1], "-0")) {
        printversion();
    } else {
        if (fileIdx >= argc) {
            fprintf(stderr, "Modes 1 to 5 need input files\n");
        } else if (!strcmp(argv[1], "-1")) {
            mode = 1;
            mode1(argc, argv, fileIdx);
        } else if (!strcmp(argv[1], "-2")) {
            mode = 2;
            mode2(argc, argv, fileIdx);
        } else if (!strcmp(argv[1], "-3")) {
            mode = 3;
            mode3(argc, argv, fileIdx);
        } else if (!strcmp(argv[1], "-4")) {
            mode = 4;
            mode4(argc, argv, fileIdx);
        } else if (strlen(argv[1]) >= 2 && argv[1][1] >= '1' && argv[1][1] <= '5') {
            fprintf(stderr, "The other modes are not implemented.\n");
        } else {
            printusage();
        }
    }    
    return 0;
}

void print(const char *format, ...) {
    if (debug) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

void printusage() {
    fprintf(stderr, "Usage:\n\t./mycc -mode [options] infile\n\n");
    fprintf(stderr, "Valid modes:\n");
    fprintf(stderr, "\t-0: Version information\n");
    fprintf(stderr, "\t-1: Mode 1\n");
    fprintf(stderr, "\t-2: Mode 2\n");
    fprintf(stderr, "\t-3: Mode 3\n");
    fprintf(stderr, "\t-4: Mode 4\n");
    fprintf(stderr, "\t-5: (not implemented yet)\n");
    fprintf(stderr, "\nValid options:\n");
    fprintf(stderr, "\t-o outfile: write to outfile instead of standard output\n");
}

void printversion() {
    fprintf(stdout, "My bare-bones C compiler (for COM 540)\n");
    fprintf(stdout, "\tWritten by Yijia Huang (hyj@iastate.edu)\n");
    fprintf(stdout, "\tVersion 0.4\n");
    fprintf(stdout, "\t12 Apr, 2021\n");
}

char *concat(char *s1, char *s2) {
    char * s3 = (char *)malloc(1 + strlen(s1) + strlen(s2));
    strcpy(s3, s1);
    strcat(s3, s2);
    return s3;
}

// Below function extracts characters present in src
// between m and n (excluding n)
char* substr(const char *src, int m, int n) {
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}

int file_exists(const char *file_name) {
    struct stat buffer;
    return stat(file_name, &buffer) == 0;
}

FILE *get_file(const char* file_name) {
    return file_exists(file_name) ? fopen(file_name, "a") : fopen(file_name, "w");
}
