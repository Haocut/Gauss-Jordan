#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
void gaussJordan(vector<vector<double>>& matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    for (int i = 0; i < m; ++i) {
       
        double maxEl = abs(matrix[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < m; ++k) {
            if (abs(matrix[k][i]) > maxEl) {
                maxEl = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        swap(matrix[maxRow], matrix[i]);

        
        double div = matrix[i][i];
        for (int k = 0; k < n; ++k) {
            matrix[i][k] /= div;
        }

        
        for (int k = 0; k < m; ++k) {
            if (k != i) {
                double c = matrix[k][i];
                for (int j = 0; j < n; ++j) {
                    matrix[k][j] -= c * matrix[i][j];
                }
            }
        }
    }
}


int main() {
    int m, n;
    cout << "輸入矩陣的行數 m 和列數 n: ";
    cin >> m >> n;

    
    vector<vector<double>> matrix(m, vector<double>(n));

    cout << "輸入矩陣元素:" << endl;
    for (int i = 0; i < m; ++i) {
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

    gaussJordan(matrix);

    cout << "簡化列梯形矩陣:" << endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }

    return 0;
}
