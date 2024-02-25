#include <iostream>
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc >= 5) {
        const char *filepath;

        if (strcmp(argv[1], "pane") == 0) {
            filepath = argv[4];
        }
    }

    else {
        std::cout << "Argumentos insuficientes\n";
        return 1;
    }

    return 0;
}