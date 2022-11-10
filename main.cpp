#include "inc.hpp"

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
        cout << "v, v2 : " << v << " " << v2 << endl;
        put(v.add(v2));
        put(v.sub(v2));
        put(v.sub(v2));
        put(v.scl(42));

        matrix<int> m(2, 2, 1);
        matrix<int> m2(2, 2, 3);
        cout << "m, m2 : " << m << " " << m2 << endl;
        put_m(m.add(m2));
        put_m(m.sub(m2));
        put_m(m.scl(42));
    }

    {
        cout << "\n_____________Linear_combination_____________\n\n";
        vector<vec<int> > v = {{1, 2, 3}, {3, 2, 1}, {0, 0, 0}};
        vector<int> coefs = {1, 2, 3};

        vec<int> res = linear_combination(v, coefs);
        for (int i = 0; i < v.size(); i++) {
            cout << (i == 0 ? "  " : "+ ") << v[i] << " * " << coefs[i] << endl;
        }
        cout << "= " << res << endl;

    }
    {   cout << "\n_____________lerp_____________\n\n";

        put(lerp(vec<float>({1, 1, 1}), vec<float>({-1,-1,-1}), 0.5));
        put(lerp(vec<int>({4, 8, 16}), vec<int>({-1, 12, 14}), 0.5));
        put(lerp(vec<int>({1}), vec<int>({0}), 0));
        put(lerp(0, 42, 0.5));


    }
    { cout << "\n_____________dot_____________\n\n";

        //cout << dot(vec<int>(3, 1), vec<int>(3, 1)) << endl;
        put(dot(vec<int>({1, 2, 4, 8}), vec<int>(4, -1)));
        put(dot(vec<int>({10, 3, 1}), vec<int>({3, 3, 3})));
        put(dot(vec<int>({10, 3, 1}), vec<int>({3, 3, 3})));
    }
    { cout << "\n_____________Norm_____________\n\n";

        vec<int> v({1,2,3}), v2({0,0,0}), v3({-1, -2, -3}), v4({42, -5, 0});
        put(v, v2, v3, v4);
        put((v.norm_1(), v.norm(), v.norm_inf()   ));
        put(v2.norm_1(), v2.norm(), v2.norm_inf());
        put(v3.norm_1(), v3.norm(), v3.norm_inf());
        put(v4.norm_1(), v4.norm(), v4.norm_inf());
    }
    { cout << "\n_____________Cosine_____________\n\n";
        put(angle_cos(vec<int>({1,2,3}), vec<int>({4,5,6})));
        put(angle_cos(vec<int>({1,1}), vec<int>({1,0})));
        put(angle_cos(vec<int>({-1,1}), vec<int>({1,-1})));
    }
    { cout << "\n_____________Cross_product_____________\n\n";
        put(cross_product(vec<double>({1,2,3}), vec<double>({4,5,6})));
        put(cross_product(vec<double>({4,2,-3}), vec<double>({-2,-5,16})));
        put(cross_product(vec<double>({0,0,1}), vec<double>({1,0,0})));
    }
    { cout << "\n_____________Matrix_multiplication_____________\n\n";
        put_m(mul_vec(matrix<int>({{1, 2}, {3, 4}}), vec<int>({2, 2})));
        put_m(mul_vec(matrix<int>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}), vec<int>({1, 2, 3})));
        put_m(mul_mat(matrix<int>({{1, 0}, {0, 1}}), matrix<int>({{1, 2}, {3, 4}})));
        put_m(mul_mat(matrix<int>({{3, 1}, {42, 69}}), matrix<int>({{1, 2}, {3, 4}})));
    }
    { cout << "\n_____________Trace_____________\n\n";
        put(matrix<int>({{1, 2}, {3, 4}}).trace());
        put(matrix<int>({{1, 0}, {0, 1}}).trace());
        put(matrix<int>({{-2, -8, 4}, {1, -23, 4}, {0, 6, 4}}).trace());
    }
    { cout << "\n_____________Transpose_____________\n\n";
        put_m(matrix<int>({{-2, -8, 4}, {1, -23, 4}, {0, 6, 4}}).transpose());
        put_m(matrix<int>({{1,3,5}, {2,5,6}}).transpose());
        put_m(matrix<int>({{1}, {1}, {1}}).transpose());
    }
    { cout << "\n_____________Reduced_row_echelon_____________\n\n";
        put_m(matrix<double>({{1.,2.},{2.,4.}}).row_echelon());
        put_m(matrix<double>({{8., 5., -2., 4., 28.}, {4., 2.5, 20., 4., -4.}, {8., 5., 1., 4., 17.}}).row_echelon());
        put_m(matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}).row_echelon());
    }
    { cout << "\n_____________Determinant_____________\n\n";
        put(determinant(matrix<int>({{2, 0, 0}, {0, 2, 0}, {0, 0, 2}})));
        put(determinant(matrix<double>({{8., 5., -2., 4.}, {4., 2.5, 20., 4.}, {8., 5., 1., 4.}, {28., -4., 17., 1.}})));
        put(determinant(matrix<int>({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}})));
    }
    { cout << "\n_____________Inverse_____________\n\n";
        put_m(matrix<double>({{8., 5., -2.}, {4., 7., 20.}, {7., 6., 1.} }).inverse());
        put_m(matrix<double>({{2., 0., 0.}, {0., 2., 1.}, {0., 0., 2.} }).inverse());
        put_m(matrix<double>({{4., 2.5, 20., 4.}, {8., 5., 1., 4.}, {28., -4., 17., 1.}, {8., 5., -2., 3.}}).inverse());
    }
    { cout << "\n_____________Rank_____________\n\n";
        put(matrix<int>({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}).rank());
        put(matrix<int>({ {1, 2, 0, 0}, {2, 4, 0, 0}, {2, 4, 0, 0}, {-1, 2, 1, 1} }).rank());
        put(matrix<int>({{1, 2, 3}, {2, 4, 6}, {3, 6, 9}}).rank());
        put(matrix<int>({{0, 0}, {0, 0}}).rank());
    }
    { cout << "\n_____________Projection_____________\n\n";
        put_m(projection(90, 1, 1, 15));
    }
}