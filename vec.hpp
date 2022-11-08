#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "macro.hpp"

template <typename K>
class vec {
public:
    vec(int n = 0, K val = K()) : v(n, val) {};

    vec(const vec& other) : v(other.v) {};

    vec(std::initializer_list<K> list) : v(list) {};

    vec<K> &add(const vec<K> &other) {
        if (v.size() != other.v.size())
            ERR("Vectors must be of the same size");
        for (int i = 0; i < v.size(); i++)
            v[i] += other.v[i];
        return *this;
    }

    vec<K> &sub(const vec<K> &other) {
        if (v.size() != other.v.size())
            ERR("Vectors must be of the same size");
        for (int i = 0; i < v.size(); i++)
            v[i] -= other.v[i];
        return *this;
    }

    template <typename T>
    vec<K> &scl(const T scalar) {
        for (int i = 0; i < v.size(); i++)
            v[i] *= scalar;
        return *this;
    }

    //fn norm_1::<V>(&mut self) -> f32;
    //fn norm::<V>(&mut self) -> f32;
    //fn norm_inf::<V>(&mut self) -> f32;

    float norm_1() const {
        return norm_p(1);
    }

    // norm_2
    float norm() const {
        return norm_p(2);
    }

    // sup norm
    float norm_inf() const {
        float ret = 0; 
        for (const K &e : v)
            ret = std::max(ret, (float)(e < 0 ? -e : e));
        return ret;
    }

    float norm_p(float p) const {
        double tot = 0;
        for (const K &e : v)
            tot += pow((e < 0 ? -e : e), p);
        return pow(tot, 1 / p);
    } 


    size_t size() const { return v.size(); }


    vec<K> &operator+=(const vec<K> &other) {
        return add(other);
    }

    vec<K> operator+(const vec<K> &other) const {
        vec<K> ret(*this);
        return ret.add(other);
    }

    template <typename T>
    vec<K> &operator*=(const T &other) {
        return scl(other);
    }

    template <typename T>
    vec<K> operator*(const T &other) const {
        vec<K> ret(*this);
        return ret.scl(other);
    }

    vec &operator=(const vec& other) {
        v = other.v;
        return *this;
    }

    K &operator[](int i) { return v[i]; }
    const K &operator[](int i) const { return v[i]; }

    typename std::vector<K>::iterator begin() { return v.begin(); }
    typename std::vector<K>::const_iterator begin() const { return v.begin(); }
    typename std::vector<K>::iterator end() { return v.end(); }
    typename std::vector<K>::const_iterator end() const { return v.end(); }

    friend std::ostream &operator<<(std::ostream &os, vec v) {
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
            ERR("Vectors must be of the same size");
    if (u.size() != coefs.size())
        ERR("Vectors and coefficients must be of the same size");
    
    vec<K> ret((u.size() ? u[0].size() : 0));
    for (int i = 0; i < u.size(); i++) {
        u[i].scl(coefs[i]);
        ret.add(u[i]);
    }

    return ret;
}

template <typename K>
K dot(const vec<K> &u, const vec<K> &v) {
    if (u.size() != v.size())
        ERR("dot: Vectors must be of the same size");
    K ret = 0;
    for (size_t i = 0; i < u.size(); i++)
        ret += u[i] * v[i];
    return ret;
}

template <typename K>
float angle_cos(const vec<K> &u, const vec<K> &v) {
    if (!u.size() || u.size() != v.size())
        ERR("angle_cos: Invalid input\n");
    return dot(u, v) / (u.norm() * v.norm());
}
    