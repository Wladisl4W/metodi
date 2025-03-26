#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Получает статическую матрицу размеров NxM и вжмыхивает
// её в динамическую
template <int N, int M>
double** staticToDynamic(double templ[N][M]) {
    double** matrix = new double* [N];
    for (int i = 0; i < N; i++) {
        matrix[i] = new double[M];
        for (int j = 0; j < M; j++) {
            matrix[i][j] = templ[i][j];
        }
    }
    return matrix;
}


// Выводит матрицу по размерам
void printMatrix(double** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


// Выводит вектор по размерам
void printVector(double* vector, int n) {
    for (int i = 0; i < n; i++)
        cout << vector[i] << " ";
    cout << endl;
}


// Получает на вход число, по нему выбирает матрицу
// и возвращает её
double** getMatrix(int option) {
    if (option == 1) {
        double templ[3][4] = {
            {1.0, 0.8, 0.64, erf(0.8)},
            {1.0, 0.9, 0.81, erf(0.9)},
            {1.0, 1.1, 1.21, erf(1.1)}
        };
        return staticToDynamic<3, 4>(templ);
    }
    if (option == 2) {
        double templ[3][4] = {
            {0.1, 0.2, 0.3, 0.1},
            {0.4, 0.5, 0.6, 0.3},
            {0.7, 0.8, 0.9, 0.5}
        };
        return staticToDynamic<3, 4>(templ);
    }
    if (option == 3) {
        double templ[2][3] = {
            {1e-4, 1, 1},
            {   1, 2, 4}
        };
        return staticToDynamic<2, 3>(templ);
    }
    if (option == 4) {
        double templ[3][4] = {
            {2.34, -4.21, -11.61, 14.41},
            {8.04, 5.22, 0.27, -6.44},
            {3.92, -7.99, 8.37, 55.56}
        };
        return staticToDynamic<3, 4>(templ);
    }
    if (option == 5) {
        double templ[5][6] = {
            { 4.43, -7.21,  8.05, 1.23, -2.56,  2.62},
            {-1.29,  6.47,  2.96, 3.22,  6.12, -3.97},
            { 6.12,  8.31,  9.41, 1.78, -2.88, -9.12},
            {-2.57,  6.93, -3.74, 7.41,  5.55,  8.11},
            { 1.46,  3.62,  7.83, 6.25, -2.35,  7.23}
        };
        return staticToDynamic<5, 6>(templ);
    }
    return nullptr;
}


// Работает вместе с getMatrix(), возвращает кол-во
// строк в матрице
int getN(int option) {
    if (option == 5) {
        return 5;
    }
    if (option == 0 || option == 1 || option == 2 || option == 4) {
        return 3;
    }
    if (option == 3) {
        return 2;
    }
    return -1;
}


// Работает вместе с getMatrix(), возвращает кол-во
// столбцов в матрице
int getM(int option) {
    if (option == 5) {
        return 6;
    }
    if (option == 1 || option == 2 || option == 4) {
        return 4;
    }
    if (option == 3) {
        return 3;
    }
    return -1;
}


// Возвращает единичную матрицу размера nxn
double** getmatrixIdentity(int n) {
    double** matrixIdentity = new double* [n];
    for (int i = 0; i < n; i++) {
        matrixIdentity[i] = new double[n];
        matrixIdentity[i][i] = 1;
    }
    return matrixIdentity;
}


// Получает строку row длины m и делит каждый элемент
// на divider
void divideRow(double* row, double divider, int m) {
    for (int i = 0; i < m; i++) {
        row[i] /= divider;
    }
}


// Получает две строки row1 и row2 длины m и вычитает
// из row1 row2
void subtractRow(double* row1, double* row2, int m) {
    for (int i = 0; i < m; i++) {
        row1[i] -= row2[i];
    }
}


// Находит строку с максимальным элементом в столбце i
// и меняет местами со строкой i
void swapRows(double** matrix, int n, int i) {
    double max = 0;
    int maxindex = 0;
    for (int j = i; j < n; j++) {
        if (abs(matrix[j][i]) > max) {
            max = abs(matrix[j][i]);
            maxindex = j;
        }
    }
    double* temp = matrix[maxindex];
    matrix[maxindex] = matrix[i];
    matrix[i] = temp;
}


int swapRows2(double** matrix, int n, int i) {
    double max = 0;
    int maxindex = 0;
    for (int j = i; j < n; j++) {
        if (abs(matrix[j][i]) > max) {
            max = abs(matrix[j][i]);
            maxindex = j;
        }
    }
    if (abs(matrix[i][maxindex]) <= 1e-12) {
        for (int k = i; k < n; k++) {
            if (abs(matrix[i][k]) >= 1e-12) {
                return 0;
            }
        }
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < n; k++) {
                cout << setw(5) << "x" << k + 1 << "*" << matrix[j][k] << " ";
            }
            cout << setw(5) << " = " << matrix[j][n] << endl;
        }
        cout << endl;
        return 2;
    }


    double* temp = matrix[maxindex];
    matrix[maxindex] = matrix[i];
    matrix[i] = temp;


    return 1;
}




// Повернуть матрицу горизонтально потом вертикально
void zhmihnutMatrix(double** matrix, int n, int m) {
    m--;
    for (int i = 0; i < n / 2; i++) {
        double* temp = matrix[i];
        matrix[i] = matrix[n - i - 1];
        matrix[n - i - 1] = temp;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            double temp2 = matrix[i][j];
            matrix[i][j] = matrix[i][m - j - 1];
            matrix[i][m - j - 1] = temp2;
        }
    }
}


// Метод Гаусса, тут всё ясно (как же верим)
void gaussMethod(double** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        swapRows(matrix, n, i);
        for (int j = i; j < n; j++) {
            divideRow(matrix[j], matrix[j][i], m);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrix[j], matrix[i], m);
        }
    }
    zhmihnutMatrix(matrix, n, m);
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            divideRow(matrix[j], matrix[j][i], m);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrix[j], matrix[i], m);
        }
    }
}

// Метод Гаусса, тут всё ясно (как же верим)
void gaussMethod2(double** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        int temp = swapRows2(matrix, n, i);
        if (!temp) {
            cout << "No solutions";
            return;
        }
        if (temp == 2) {
            return;
        }
        for (int j = i; j < n; j++) {
            divideRow(matrix[j], matrix[j][i], m);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrix[j], matrix[i], m);
        }
    }


    zhmihnutMatrix(matrix, n, m);


    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            divideRow(matrix[j], matrix[j][i], m);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrix[j], matrix[i], m);
        }
    }
}


// Находит строку с максимальным элементом в столбце i матрицы
// matrixInversed и меняет местами со строкой i вместе с
// матрицеу matrixIdentity(единичная)
void swapRows(double** matrixInversed, double** matrixIdentity, int n, int i) {
    double max = 0;
    int maxindex = 0;
    for (int j = i; j < n; j++) {
        if (abs(matrixInversed[j][i]) > max) {
            max = abs(matrixInversed[j][i]);
            maxindex = j;
        }
    }
    double* temp = matrixInversed[maxindex];
    matrixInversed[maxindex] = matrixInversed[i];
    matrixInversed[i] = temp;
    double* temp2 = matrixIdentity[maxindex];
    matrixIdentity[maxindex] = matrixIdentity[i];
    matrixIdentity[i] = temp2;
}


// Находит обратную матрицу от матрицы matrix
// через метод Гаусса
double** inverseMatrix(double** matrix, int n) {
    double** matrixInversed = new double* [n];
    for (int i = 0; i < n; i++) {
        matrixInversed[i] = new double[n];
        for (int j = 0; j < n; j++) {
            matrixInversed[i][j] = matrix[i][j];
        }
    }
    double** matrixIdentity = getmatrixIdentity(n);
    for (int i = 0; i < n; i++) {
        swapRows(matrixInversed, matrixIdentity, n, i);
        for (int j = i; j < n; j++) {
            divideRow(matrixIdentity[j], matrixInversed[j][i], n);
            divideRow(matrixInversed[j], matrixInversed[j][i], n);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrixInversed[j], matrixInversed[i], n);
            subtractRow(matrixIdentity[j], matrixIdentity[i], n);
        }
    }

    zhmihnutMatrix(matrixInversed, n, n + 1);
    zhmihnutMatrix(matrixIdentity, n, n + 1);


    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            divideRow(matrixIdentity[j], matrixInversed[j][i], n);
            divideRow(matrixInversed[j], matrixInversed[j][i], n);
        }
        for (int j = i + 1; j < n; j++) {
            subtractRow(matrixInversed[j], matrixInversed[i], n);
            subtractRow(matrixIdentity[j], matrixIdentity[i], n);
        }
    }
    zhmihnutMatrix(matrixIdentity, n, n + 1);
    return matrixIdentity;
}


// Находит норму матрицы (норма это максимальная из абсолютных
// сумм столбцов матрицы)
double findMatrixNorm(double** matrix, int n, int m) {
    double max = 0;
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < m; j++) {
            sum += abs(matrix[i][j]);
        }
        if (sum > max) {
            max = sum;
        }
    }
    return max;
}


// Находит обусловленность матрицы (норма матрицы умножить 
// на норму обратной матрицы)
double conditionality(double** matrix, int n, int m) {
    double** matrixInversed = inverseMatrix(matrix, n);
    return findMatrixNorm(matrix, n, n) * findMatrixNorm(matrixInversed, n, n);
}




// Умножает матрицу на вектор, возвращает вектор
double* matrixMultiplyRow(double** matrix, double* answers, int n) {
    double* result = new double[n];
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < n; j++) {
            sum += matrix[i][j] * answers[j];
        }
        result[i] = sum;
    }
    return result;
}


// Находит невязку (я вбил "невязка" в гугл переводчик, он
// сказал что это residual)
double* foundResidual(double** matrix, double* answers, int n, int m) {
    double* result = matrixMultiplyRow(matrix, answers, n);
    double* freeMembers = new double[n];
    for (int i = 0; i < n; i++) {
        freeMembers[i] = matrix[i][m - 1];
        result[i] = abs(result[i] - freeMembers[i]);
    }
    return result;
}



int main() {
    int option;
    cout << "Choose option (1, 5): ";
    cin >> option;
    double** matrix = getMatrix(option);
    int n = getN(option);
    int m = getM(option);
    if (matrix == nullptr) {
        cout << "Bad getMatrix() option\n";
        return -1;
    }

    cout << endl << n << "x" << m << " matrix:" << endl;
    printMatrix(matrix, n, m);

    if (option == 2)
    {
        gaussMethod2(matrix, n, m);
        zhmihnutMatrix(matrix, n, m);
    }
    else
    {
        gaussMethod(matrix, n, m);
        zhmihnutMatrix(matrix, n, m);


        double* row = new double[n];
        for (int i = 0; i < n; i++) {
            cout << "x" << i << " = " << matrix[i][m - 1] << endl;
            row[i] = matrix[i][m - 1];
        }
        cout << endl;
        matrix = getMatrix(option);


        cout << endl;
        matrix = getMatrix(option);
        cout << "Conditionality: " << conditionality(matrix, n, m) << endl << endl;




        row = foundResidual(matrix, row, n, m);
        cout << "Pogreshnosti: \n";
        printVector(row, n);

        for (int i = 0; i < n; i++) {
            delete[]matrix[i];
        }
        delete[]matrix;
        delete[]row;
    }
    return 0;
}
