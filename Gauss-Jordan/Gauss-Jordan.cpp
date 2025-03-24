#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void gaussJordan(vector<vector<double>>& matrix, vector<vector<double>>& inverse) {
    int n = matrix.size();

    for (int i = 0; i < n; ++i) {
        // 尋找主元
        double maxEl = abs(matrix[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix[k][i]) > maxEl) {
                maxEl = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        // 如果主元為0，則反矩陣不存在
        if (maxEl == 0) {
            cout << "反矩陣不存在！" << endl;
            return;
        }

        // 交換行
        swap(matrix[maxRow], matrix[i]);
        swap(inverse[maxRow], inverse[i]);

        // 將主元化為1
        double div = matrix[i][i];
        for (int k = 0; k < n; ++k) {
            matrix[i][k] /= div;
            inverse[i][k] /= div;
        }

        // 消去其他行的該列
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double c = matrix[k][i];
                for (int j = 0; j < n; ++j) {
                    matrix[k][j] -= c * matrix[i][j];
                    inverse[k][j] -= c * inverse[i][j];
                }
            }
        }
    }

    // 輸出反矩陣
    cout << "反矩陣:" << endl;
    for (const auto& row : inverse) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "輸入方矩陣的階數 n: ";
    cin >> n;

    // 使用 vector 來動態分配矩陣
    vector<vector<double>> matrix(n, vector<double>(n));
    vector<vector<double>> inverse(n, vector<double>(n, 0));

    // 初始化反矩陣為單位矩陣
    for (int i = 0; i < n; ++i) {
        inverse[i][i] = 1;
    }

    cout << "輸入矩陣元素:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "原始矩陣:" << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    gaussJordan(matrix, inverse);

    return 0;
}
