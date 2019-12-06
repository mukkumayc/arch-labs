//
// Created by sergo on 12/5/19.
//

#include <chrono>
#include <random>

#include "matrix.hpp"

using namespace std;

template<typename T>
Matrix<T>::Matrix(size_t n, size_t m): height(n), width(m) {
    size_t pointersSpaceSize = sizeof(T *) * n;
    size_t elementsRowSize = sizeof(T) * m;
    data = reinterpret_cast<T **>(new char[pointersSpaceSize + elementsRowSize * n]);
    for (size_t i = 0; i < n; ++i) {
        data[i] = reinterpret_cast<T *>(reinterpret_cast<char *>(data) +
                                        pointersSpaceSize + i * m * sizeof(T));
    }
}

template<typename T>
Matrix<T>::Matrix(size_t n): Matrix(n, n) {}

template<typename T>
T *Matrix<T>::operator[](size_t n) {
    return data[n];
}

template<typename T>
[[nodiscard]] size_t Matrix<T>::getWidth() const {
    return width;
}

template<typename T>
[[nodiscard]] size_t Matrix<T>::getHeight() const {
    return height;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, Matrix<T> &matrix) {
    for (int i = 0; i < matrix.getHeight(); ++i) {
        for (int j = 0; j < matrix.getWidth(); ++j) {
            out << matrix[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}

void randomizeMatrix(Matrix<int> &matrix) {
    int low = 0;
    int high = 1e6;
    auto now = chrono::system_clock::now();
    default_random_engine generator(now.time_since_epoch().count());
    uniform_int_distribution<int> distribution(low, high);
    int i, j;
#pragma omp parallel for default(shared), private(i, j)
    for (i = 0; i < matrix.getHeight(); ++i) {
#pragma omp parallel for default(shared), private(j)
        for (j = 0; j < matrix.getWidth(); ++j) {
            matrix[i][j] = distribution(generator);
        }
    }
}

template class Matrix<int>;

template std::ostream& operator<<<int>(std::ostream&, Matrix<int>&);