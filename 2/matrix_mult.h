#include <cstdio>

class MatrixMult {
private:
    double** matrix_A = nullptr;
    double** matrix_B = nullptr;
    double** matrix_C = nullptr;
    int n_A = 0;
    int k_A = 0;
    int n_B = 0;
    int k_B = 0;
    int num_threads = 0;
    const char* filename_C;

public:
    MatrixMult(const char* filename_A, const char* filename_B, int num_threads_, const char* filename_C_ = "C.txt");
    void multiply();
    ~MatrixMult();
    void show();

private:
    void delete_matrix(double*** matrix, int n);
    bool read_matrix_A(const char* filename);
    bool read_matrix_B(const char* filename);
};