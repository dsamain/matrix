#pragma once

template <typename V>
V lerp(V u, V v, float t) {
    return u * (1 - t) + v * t;
}

template <typename K>
K dot(const vec<K> &u, const vec<K> &v) {
    if (u.size() != v.size())
        throw "dot: Vectors must be of the same size";
    K ret = 0;
    for (size_t i = 0; i < u.size(); i++)
        ret += u[i] * v[i];
    return ret;
}