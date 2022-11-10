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

    matrix<K> row_echelon() {
        matrix<K> ret(*this);
        int lead = 0;
        for (int r = 0; r < ret.size()[0]; r++) {
            if (lead >= ret.size()[1])
                return ret;
            int i = r;
            while (ret[i][lead] == 0) {
                i++;
                if (i == ret.size()[0]) {
                    i = r;
                    lead++;
                    if (lead == ret.size()[1])
                        return ret;
                }
            }
            swap(ret[i], ret[r]);
            double lv = ret[r][lead];
            for (int j = 0; j < ret.size()[1]; j++)
                ret[r][j] /= lv;
            for (int i = 0; i < ret.size()[0]; i++) {
                if (i != r) {
                    lv = ret[i][lead];
                    for (int j = 0; j < ret.size()[1]; j++)
                        ret[i][j] -= lv * ret[r][j];
                }
            }
            lead++;
        }
        return ret;
    }
    
    matrix<K> inverse() {
        if (this->size()[0] != this->size()[1])
            ERR("Matrix must be square\n");
        if (determinant(*this) == 0)
            ERR("Matrix is not invertible\n");

        matrix<K> aug(this->size()[0], this->size()[1] * 2);

        for (int i = 0; i < this->size()[0]; i++)
            for (int j = 0; j < this->size()[1]; j++)
                aug[i][j] = this->operator[](i)[j];
        for (int i = 0; i < this->size()[0]; i++)
            aug[i][i + this->size()[1]] = 1;

        aug = aug.row_echelon();
        matrix<K> ret(this->size()[0], this->size()[0]);
        for (size_t i = 0; i < this->size()[0]; i++) {
            for (int j = 0; j < this->size()[0]; j++) {
                ret[i][j] = aug[i][j + this->size()[1]];
            }
        }
        return ret;

    }

    size_t rank() {
        matrix<K> ret = this->row_echelon();
        size_t r = 0;
        bool f = true;
        for (int i = 0; i < ret.size()[0]; i++, f = true) {
            for (int j = 0; j < ret.size()[1]; j++)
                f &= ret[i][j] == 0;
            r += !f;
        }
        return r;
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

template <typename K>
K determinant(const matrix<K> &m) {
    if (m.size()[0] != m.size()[1])
        ERR("Matrix must be square");
    if (m.size()[0] == 1)
        return m[0][0];
    K ret = 0;
    matrix<K> cur(m.size()[0] - 1, m.size()[1] - 1);
    for (int i = 0; i < m.size()[1]; i++) {
        for (int j = 1; j < m.size()[0]; j++) {
            for (int k = 0; k < m.size()[1]; k++) {
                if (k < i)
                    cur[j - 1][k] = m[j][k];
                else if (k > i)
                    cur[j - 1][k - 1] = m[j][k];
            }
        }
        ret += m[0][i] * determinant(cur) * (i % 2 == 0 ? 1 : -1);
    }
    return ret;
}

matrix<float> projection(float fov, float ratio, float near, float far) {
    return matrix<float>({{1 / (ratio * (float)tan(fov / 2)), 0, 0, 0},
                            {0, 1 / (float)tan(fov / 2), 0, 0},
                            {0, 0, (far + near) / (near - far), 2 * far * near / (near - far)},
                            {0, 0, -1, 0}});
}

