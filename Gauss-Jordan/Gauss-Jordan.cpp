#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Vector = vector<double>;
using Matrix = vector<Vector>;

// 向量內積
double dot(const Vector& a, const Vector& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

// 向量長度平方
double norm2(const Vector& v) {
    return dot(v, v);
}

// 向量減法
Vector subtract(const Vector& a, const Vector& b) {
    Vector result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        result[i] = a[i] - b[i];
    return result;
}

// 向量乘以常數
Vector scalarMul(const Vector& v, double scalar) {
    Vector result(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        result[i] = v[i] * scalar;
    return result;
}

// Gram-Schmidt 正交化（對行向量）
Matrix gramSchmidt(const Matrix& A) {
    int m = A.size();       // 行數
    Matrix Q;

    for (int i = 0; i < m; ++i) {
        Vector vi = A[i];

        for (const auto& q : Q) {
            double proj_coeff = dot(vi, q) / norm2(q);
            vi = subtract(vi, scalarMul(q, proj_coeff));
        }

        Q.push_back(vi);
    }

    return Q;
}

// 印出矩陣
void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (double val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    int m, n;
    cout << "請輸入矩陣行數 m 與列數 n（n > m）: ";
    cin >> m >> n;

    Matrix A(m, Vector(n));
    cout << "請輸入矩陣（每列為一個向量）：" << endl;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    Matrix Q = gramSchmidt(A);

    cout << "\n正交化後的矩陣（每列為一個正交基底向量）：" << endl;
    printMatrix(Q);

    return 0;
}
