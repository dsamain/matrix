#pragma once

#include <iostream>
#include <vector>

template <typename K>
class vec {
public:
    vec(int n = 0, K val = K()) : v(n, val) {};

    vec(const vec& other) : v(other.v) {};

    vec(std::initializer_list<K> list) : v(list) {};

    void add(vec<K> &other) {
        if (v.size() != other.v.size())
            throw "Vectors must be of the same size";
        for (int i = 0; i < v.size(); i++)
            v[i] += other.v[i];
    }

    void sub(vec<K> &other) {
        if (v.size() != other.v.size())
            throw "Vectors must be of the same size";
        for (int i = 0; i < v.size(); i++)
            v[i] -= other.v[i];
    }

    void scl(K scalar) {
        for (int i = 0; i < v.size(); i++)
            v[i] *= scalar;
    }

    //fn sub(&mut self, v: &Vector<K>);
    //fn scl(&mut self, a: K);

    size_t size() const { return v.size(); }


    vec &operator=(const vec& other) {
        v = other.v;
        return *this;
    }

    K &operator[](int i) { return v[i]; }

    friend std::ostream &operator<<(std::ostream &os, vec &v) {
        os << "[";
        for (int i = 0; i < v.size(); i++) {
            os << v[i];
            if (i != v.size() - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }

private:
    std::vector<K> v;
};

template <typename K>
vec<K> linear_combination(std::vector<vec<K>> u, std::vector<K> &coefs) {
    for (int i = 1; i < u.size(); i++)
        if (u[i].size() != u[0].size())
            throw "Vectors must be of the same size";
    if (u.size() != coefs.size())
        throw "Vectors and coefficients must be of the same size";
    
    vec<K> ret((u.size() ? u[0].size() : 0));
    for (int i = 0; i < u.size(); i++) {
        u[i].scl(coefs[i]);
        ret.add(u[i]);
    }

    return ret;
}