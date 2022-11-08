#pragma once

#include <iostream>

#define DEBUG

void dbg_out() { std::cerr << std::endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { std::cerr << " " << H; dbg_out(T...);}
#ifdef DEBUG
#define dbg(...) std::cerr << __LINE__ << ": " << #__VA_ARGS__ << " =", dbg_out(__VA_ARGS__);
#else
# define dbg(x)
#endif

void put_out() { std::cerr << std::endl; }
template<typename Head, typename... Tail> void put_out(Head H, Tail... T) { std::cout << H << (sizeof...(T) ? ", " : "") ; put_out(T...);}
#define put(...) {std::cout << #__VA_ARGS__ << " = ", put_out(__VA_ARGS__); std::flush(std::cout);}

#define ERR(s) {dprintf(2, s); exit(1);}


