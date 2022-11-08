#pragma once

#include "matrix.hpp"
#include "vec.hpp"

template <typename V>
V lerp(V u, V v, float t) {
    return u * (1 - t) + v * t;
}

template <typename K>
vec<K> cross_product(const vec<K> &u, const vec<K> &v) {
    if (u.size() != 3 || v.size() != 3)
        ERR("cross_product: Vectors must be 3-dimensional\n");

    matrix<K> m({{0, -u[2], u[1]}, 
                 {u[2], 0, -u[0]},
                 {-u[1], u[0], 0}});

    return mul_vec(m, v);
}
