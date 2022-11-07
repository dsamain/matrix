#include "inc.hpp"

using namespace std;

#define DEBUG

void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...);}
#ifdef DEBUG
#define dbg(...) cerr << __LINE__ << ": " << #__VA_ARGS__ << " =", dbg_out(__VA_ARGS__);
#else
# define dbg(x)
#endif

#define show_func(x) cout << #x << " = " << x << endl;

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
    {   cout << "\n_____________lerp_____________\n\n";

        show_func(lerp(vec<float>({1, 1, 1}), vec<float>({-1,-1,-1}), 0.5));
        show_func(lerp(vec<int>({4, 8, 16}), vec<int>({-1, 12, 14}), 0.5));
        show_func(lerp(vec<int>({1}), vec<int>({0}), 0));
        show_func(lerp(0, 42, 0.5));


    }
    { cout << "\n_____________dot_____________\n\n";

        //cout << dot(vec<int>(3, 1), vec<int>(3, 1)) << endl;
        show_func(dot(vec<int>({1, 2, 4, 8}), vec<int>(4, -1)));
        show_func(dot(vec<int>({10, 3, 1}), vec<int>({3, 3, 3})));
        show_func(dot(vec<int>({10, 3, 1}), vec<int>({3, 3, 3})));
    }
}