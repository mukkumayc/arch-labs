//
// Created by sergo on 12/5/19.
//

#ifndef ARCH_LABS_MATRIX_HPP
#define ARCH_LABS_MATRIX_HPP

#include <ostream>

template<typename T>
class Matrix {
    T **data;
    size_t width;
    size_t height;

public:
    explicit Matrix(size_t, size_t);

    explicit Matrix(size_t);

    T *operator[](size_t);

    [[nodiscard]] size_t getWidth() const;

    [[nodiscard]] size_t getHeight() const;
};

template<typename T>
extern std::ostream &operator<<(std::ostream &out, Matrix<T> &matrix);

extern void randomizeMatrix(Matrix<int>& matrix);

#endif // ARCH_LABS_MATRIX_HPP