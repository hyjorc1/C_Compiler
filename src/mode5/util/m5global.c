#include "m5global.h"

void m5preprocess() {
    m4preprocess();

}

void m5process(char *argv[], int i) {
    m4process(argv, i);

}

void m5postprocess() {
    m4postprocess();
    
}