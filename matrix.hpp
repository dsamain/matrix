#pragma once

#include <iostream>
#include <vector>

template <typename K>
class matrix {
public:
    matrix(int n = 0, int m = 0, K val = K()) : v(n, std::vector<K>(m, val)) {};

    matrix(const matrix& other) : v(other.v) {};

    void add(matrix<K> &other) {
        if (this->size() != other.size())
            throw "Matrices must be of the same size";
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] += other.v[i][j];
    }

    void sub(matrix<K> &other) {
        if (this->size() != other.size())
            throw "Matrices must be of the same size";
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] -= other.v[i][j];
    }

    void scl(K scalar) {
        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                v[i][j] *= scalar;
    }

    std::vector<size_t> size() const { return {v.size(), (v.size() ? v[0].size() : 0)}; }


    matrix &operator=(const matrix& other) {
        v = other.v;
        return *this;
    }

    std::vector<K> &operator[](int i) { return v[i]; }

    friend std::ostream &operator<<(std::ostream &os, matrix &m) {
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