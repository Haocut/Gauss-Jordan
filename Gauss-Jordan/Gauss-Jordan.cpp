#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

// 以行向量為單位進行 Gram-Schmidt 正交化
vector<vector<double>> gram_schmidt_rows(const vector<vector<double>>& A) {
    int m = A.size();       // 幾個向量（行數）
    int n = A[0].size();    // 向量維度（列數）
    vector<vector<double>> Q(m, vector<double>(n, 0.0));

    for (int i = 0; i < m; ++i) {
        Q[i] = A[i]; // 初始化為原始向量

        for (int j = 0; j < i; ++j) {
            // 計算 Q[i] 與 Q[j] 的內積
            double dot = 0, norm = 0;
            for (int k = 0; k < n; ++k) {
                dot += Q[i][k] * Q[j][k];
                norm += Q[j][k] * Q[j][k];
            }

            // 投影係數
            double coeff = (norm == 0) ? 0 : dot / norm;

            // 從 Q[i] 減去 Q[j] 的投影部分
            for (int k = 0; k < n; ++k) {
                Q[i][k] -= coeff * Q[j][k];
            }
        }
    }

    return Q;
}

int main() {
    int m, n;
    cout << "請輸入矩陣行數 m 與列數 n（n > m）: ";
    cin >> m >> n;

    vector<vector<double>> A(m, vector<double>(n));

    cout << "請輸入矩陣，每行為一個向量（共 " << m << " 行，每行 " << n << " 個數）:\n";
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    vector<vector<double>> Q = gram_schmidt_rows(A);

    cout << fixed << setprecision(10);
    cout << "\n正交化後的行向量結果（每行為一個正交向量）：\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            cout << Q[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
