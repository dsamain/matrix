#include <iostream>
#include "matrix.hpp"
#include "vec.hpp"

using namespace std;

#define DEBUG

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}
#ifdef DEBUG
#define dbg(...) cerr << __LINE__ << ": " << #__VA_ARGS__ << " =", dbg_out(__VA_ARGS__);
#else
# define dbg(x)
#endif

int main() {

    {
        vec<int> v(5, 1);
        cout << v << endl;

        matrix<int> m(3, 3, 42);
        cout << m << endl;
    }

    {
        cout << "\n_____________ADD_SUB_SCL_____________\n\n";

        vec<int> v(5, 1);
        vec<int> v2(5, 3);
        v.add(v2);
        cout << "v: " << v << endl;

        v.sub(v2);
        cout << "v: " << v << endl;

        v.scl(42);
        cout << "v: " << v << endl;

        matrix<int> m(2, 2, 1);
        matrix<int> m2(2, 2, 3);
        m.add(m2);
        cout << "m: \n" << m << endl;

        m.sub(m2);
        cout << "m: \n" << m << endl;

        m.scl(42);
        cout << "m: \n" << m << endl;
    }

    {
        cout << "\n_____________Linear_combination_____________\n\n";
        //int arr[5] = {1, 2, 3, 4, 5};
        vector<vec<int>> v = {{1, 2, 3}, {3, 2, 1}, {0, 0, 0}};
        vector<int> coefs = {1, 2, 3};



        vec<int> res = linear_combination(v, coefs);
        for (int i = 0; i < v.size(); i++) {
            cout << (i == 0 ? "  " : "+ ") << v[i] << " * " << coefs[i] << endl;
        }
        cout << "= " << res << endl;

    }


}