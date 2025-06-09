#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Vector = vector<double>;
using Matrix = vector<Vector>;

// ========== 與 HW04 相同的函式 ==========
double dot(const Vector& a, const Vector& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); ++i)
        result += a[i] * b[i];
    return result;
}

double norm2(const Vector& v) {
    return dot(v, v);
}

Vector subtract(const Vector& a, const Vector& b) {
    Vector result(a.size());
    for (size_t i = 0; i < a.size(); ++i)
        result[i] = a[i] - b[i];
    return result;
}

Vector scalarMul(const Vector& v, double scalar) {
    Vector result(v.size());
    for (size_t i = 0; i < v.size(); ++i)
        result[i] = v[i] * scalar;
    return result;
}

// Gram-Schmidt（HW04 導入）
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
// ========================================

// 產生 1, x, x^2 的值向量（行向量）在 [-1, 1] 區間內
Matrix generateLegendreBasis(int sampleCount) {
    Matrix basis(3, Vector(sampleCount));
    for (int i = 0; i < sampleCount; ++i) {
        double x = -1.0 + 2.0 * i / (sampleCount - 1);
        basis[0][i] = 1.0;
        basis[1][i] = x;
        basis[2][i] = x * x;
    }
    return basis;
}

void printMatrix(const Matrix& M) {
    for (const auto& row : M) {
        for (double val : row)
            cout << val << " ";
        cout << endl;
    }
}

int main() {
    int sampleCount = 150;

    cout << "正在生成標準基底（1, x, x^2）在 [-1, 1] 上的 " << sampleCount << " 個取樣點..." << endl;

    Matrix basis = generateLegendreBasis(sampleCount);

    cout << "\n進行 Gram-Schmidt 正交化..." << endl;
    Matrix Q = gramSchmidt(basis);

    cout << "\n正交後的三個向量（每行為向量在各取樣點的值）：" << endl;
    printMatrix(Q);

    cout << "\n可與雷建德多項式進行對比：" << endl;
    cout << "P0(x) = 1\nP1(x) = x\nP2(x) = (3x^2 - 1)/2 ≈ x^2 - 1/3\n";

    return 0;
}
