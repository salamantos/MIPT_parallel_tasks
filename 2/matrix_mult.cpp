#include <fstream>
#include "matrix_mult.h"
#include <iostream>

void MatrixMult::multiply() {
#pragma omp parallel for collapse(2) num_threads(num_threads)
    for (int i = 0; i < n_A; i++) {
        for (int j = 0; j < k_B; j++) {
            matrix_C[i][j] = 0;
            for (int k = 0; k < k_A; k++) {
                matrix_C[i][j] += matrix_A[i][k] * matrix_B[k][j];
            }
        }
    }
}

MatrixMult::MatrixMult(const char* filename_A, const char* filename_B, int num_threads_, const char* filename_C_) :
        num_threads(num_threads_), filename_C(filename_C_) {
    if (!read_matrix_A(filename_A)) {
        std::cerr << "Error occured";
        return;
    }
    if (!read_matrix_B(filename_B)) {
        std::cerr << "Error occured";
        return;
    }
    matrix_C = new(std::nothrow) double* [n_A];
    if (!matrix_C) {
        std::cerr << "Error occured";
        return;
    }
    for (int i = 0; i < n_A; i++) {
        matrix_C[i] = new(std::nothrow) double[k_B];
        if (!matrix_C[i]) {
            std::cerr << "Error occured";
            return;
        }
    }
}

void MatrixMult::delete_matrix(double*** matrix, int n) {
    for (int i = 0; i < n; i++) {
        delete[] (*matrix)[i];
    }
    delete[] (*matrix);
}

bool MatrixMult::read_matrix_A(const char* filename) {
    std::ifstream file;
    file.open(filename);
    file >> n_A >> k_A;
    matrix_A = new(std::nothrow) double* [n_A];
    if (!matrix_A) {
        return false;
    }
    for (int i = 0; i < n_A; i++) {
        matrix_A[i] = new(std::nothrow) double[k_A];
        if (!matrix_A[i]) {
            return false;
        }
        for (int j = 0; j < k_A; j++) {
            file >> matrix_A[i][j];
        }
    }
    file.close();
    return true;
}

bool MatrixMult::read_matrix_B(const char* filename) {
    std::ifstream file;
    file.open(filename);
    file >> n_B >> k_B;
    matrix_B = new(std::nothrow) double* [n_B];
    if (!matrix_B) {
        return false;
    }
    for (int i = 0; i < n_B; i++) {
        matrix_B[i] = new(std::nothrow) double[k_B];
        if (!matrix_B[i]) {
            return false;
        }
        for (int j = 0; j < k_B; j++) {
            file >> matrix_B[i][j];
        }
    }
    file.close();
    return true;
}

void MatrixMult::show() {
    std::ofstream file;
    file.open(filename_C);
    file << n_A << " " << k_B << "\n";
    for (int i = 0; i < n_A; i++) {
        for (int j = 0; j < k_B; j++) {
            file << matrix_C[i][j] << " ";
        }
        file << std::endl;
    }
    file.close();
}

MatrixMult::~MatrixMult() {
    delete_matrix(&matrix_A, n_A);
    delete_matrix(&matrix_B, n_B);
    delete_matrix(&matrix_C, n_A);
}
