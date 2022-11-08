#pragma once

#include <iostream>
#include <vector>
#include "vec.hpp"

template <typename K>
class matrix {
public:
    matrix(int n = 0, int m = 0, K val = K()) : v(n, std::vector<K>(m, val)) {};

    matrix(const matrix& other) : v(other.v) {};

    matrix(std::initializer_list<std::vector<K>> list) : v(list) {};

    matrix<K> &add(const matrix<K> &other) {
        if (this->size() != other.size())
            throw "Matrices must be of the same size";
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] += other.v[i][j];
        return *this;
    }

    matrix<K> &sub(const matrix<K> &other) {
        if (this->size() != other.size())
            throw "Matrices must be of the same size";
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] -= other.v[i][j];
        return *this;
    }

    template <typename T>
    matrix<K> &scl(const T scalar) {
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] *= scalar;
        return *this;
    }

    K trace() const {
        if (this->size()[0] != this->size()[1])
            throw "Matrix must be square";
        K ret = 0;
        for (int i = 0; i < this->size()[0]; i++)
            ret += v[i][i];
        return ret;
    }

    matrix<K> transpose() const {
        matrix<K> ret(this->size()[1], this->size()[0]);
        for (int i = 0; i < this->size()[0]; i++)
            for (int j =0 ; j < this->size()[1]; j++)
                ret[j][i] = this->operator[](i)[j];
        return ret;
    }

    std::vector<size_t> size() const { 
        return {v.size(), (v.size() ? v[0].size() : 0)}; 
    }


    matrix<K> &operator+=(const matrix<K> &other) {
        return add(other);
    }

    matrix<K> operator+(const matrix<K> &other) const {
        matrix<K> ret(*this);
        return ret.add(other);
    }

    template <typename T>
    matrix<K> &operator*=(const T &other) {
        return scl(other);
    }

    template <typename T>
    matrix<K> operator*(const T &other) const {
        matrix<K> ret(*this);
        return ret.scl(other);
    }

    matrix &operator=(const matrix& other) {
        v = other.v;
        return *this;
    }

    std::vector<K> &operator[](int i) { return v[i]; }
    const std::vector<K> &operator[](int i) const { return v[i]; }

    friend std::ostream &operator<<(std::ostream &os, matrix m) {
        os << "[";
        for (int i = 0; i < m.size()[0]; i++) {
            if (i != 0)
                os << " ";
            os << "[";
            for (int j = 0; j < m.size()[1]; j++) {
                os << m[i][j];
                if (j != m.size()[1] - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if (i != m.size()[0] - 1) {
                os << std::endl;
            }
        }
        os << "]";
        return os;
    }

private:
    std::vector<std::vector<K>> v;
};

//fn mul_vec::<K>(&mut self, vec: Vector::<K>) -> Vector::<K>;
//fn mul_mat::<K>(&mut self, mat: Matrix::<K>) -> Matrix::<K>;

template <typename K>
vec<K> mul_vec(const matrix<K> &u, const vec<K> &v) {
    if (u.size()[1] != v.size())
        ERR("Matrix and vector must have compatible sizes");
    vec<K> ret(u.size()[0], 0);
    for (size_t i = 0; i < u.size()[0]; i++)
        for (size_t j = 0; j < u.size()[1]; j++)
            ret[i] += u[i][j] * v[j];
    return ret;
}

template <typename K>
matrix<K> mul_mat(const matrix<K> &u, const matrix<K> &v) {
    if (u.size()[1] != v.size()[0])
        ERR("Matrices must have compatible sizes");
    matrix<K> ret(v.size()[0], u.size()[1], 0);
    for (size_t i = 0; i < u.size()[0]; i++)
        for (size_t j = 0; j < v.size()[1]; j++)
            for (size_t k = 0; k < u.size()[1]; k++)
                ret[i][j] += u[i][k] * v[k][j];
    return ret;
}