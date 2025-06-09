#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double EPS = 1e-9;  // 誤差容許值（浮點數比較用）

double determinant(vector<vector<double>> matrix) {
    int n = matrix.size();
    double det = 1.0;

    for (int i = 0; i < n; ++i) {
        // 找出目前列以下最大絕對值的列（pivot）
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (fabs(matrix[j][i]) > fabs(matrix[pivot][i])) {
                pivot = j;
            }
        }

        // 如果該列為0，行列式為0
        if (fabs(matrix[pivot][i]) < EPS)
            return 0.0;

        // 換行：如果 pivot 不是 i，需改變符號
        if (i != pivot) {
            swap(matrix[i], matrix[pivot]);
            det *= -1;
        }

        // 用 pivot 值更新行列式乘積
        det *= matrix[i][i];

        // 消去 i 列以下的其他列
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    return det;
}

int main() {
    int n;
    cout << "請輸入方矩陣的大小 n: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));

    cout << "請輸入矩陣內容（以空格分隔，每列換行）：" << endl;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> matrix[i][j];

    double result = determinant(matrix);

    cout << "行列式的值為: " << result << endl;

    return 0;
}