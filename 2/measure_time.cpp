#include <fstream>
#include <time.h>
#include <iostream>
#include "matrix_mult.h"

#include <string>
#include <fstream>
#include <ctime>
#include "math.h"
#include <cstdlib>

#define MAX_THREADS 10

void generate_matrix(const char* filename, int count_n, int count_k) {
    std::ofstream file;
    file.open(filename);
    file << count_n << " " << count_k << '\n';
    for (size_t i = 0; i < count_n; i++) {
        for (size_t j = 0; j < count_k; j++) {
            double num = (double) rand() / RAND_MAX + rand();
            file << num;
        }
        file << '\n';
    }
    file.close();
}

int main(int argc, char** argv) {
    generate_matrix("A.txt", 1000, 1000);
    generate_matrix("B.txt", 1000, 1000);

    std::ofstream outfile;
    outfile.open(argv[1]);
    outfile << "#threads = [";
    for (size_t i = 1; i < MAX_THREADS; i++) {
        outfile << i;
        if (i + 1 != MAX_THREADS) {
            outfile << ", ";
        }
    }
    outfile << "]\n";

    outfile << "time = [";
    for (size_t i = 1; i < MAX_THREADS; i++) {
        MatrixMult matrix_mult("A.txt", "B.txt", i, "C.txt");
        struct timespec start, finish;
        double elapsed;
        clock_gettime(CLOCK_MONOTONIC, &start);
        matrix_mult.multiply();
        clock_gettime(CLOCK_MONOTONIC, &finish);
        elapsed = (finish.tv_sec - start.tv_sec);
        elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
        outfile << elapsed;
        if (i + 1 != MAX_THREADS) {
            outfile << ", ";
        }
        matrix_mult.show();
    }
    outfile << "]\n";
}