#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct SplineCoefficients {
    double a, b, c, d;
};


vector<SplineCoefficients> build_cubic_spline(const vector<double>& x, const vector<double>& y) {
    int n = x.size() - 1;

    
    vector<double> h(n), alpha(n), l(n + 1), mu(n + 1), z(n + 1);
    vector<SplineCoefficients> coefficients(n);

    
    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    
    for (int i = 1; i < n; ++i) {
        alpha[i] = (3.0 / h[i]) * (y[i + 1] - y[i]) - (3.0 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // Решение трехдиагональной системы уравнений (метод прогонки)
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;

    for (int i = 1; i < n; ++i) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;
    double c_n = 0.0;

    // Обратный ход метода прогонки
    for (int i = n - 1; i >= 0; --i) {
        double c_i = z[i] - mu[i] * c_n;
        double b_i = (y[i + 1] - y[i]) / h[i] - h[i] * (c_n + 2.0 * c_i) / 3.0;
        double d_i = (c_n - c_i) / (3.0 * h[i]);

        coefficients[i].a = y[i];
        coefficients[i].b = b_i;
        coefficients[i].c = c_i;
        coefficients[i].d = d_i;

        c_n = c_i;
    }

    return coefficients;
}

// Вычисление значения сплайна в точке x
double evaluate_spline(double x_eval, const vector<double>& x, const vector<SplineCoefficients>& coefficients) {
    int n = x.size() - 1;

    
    int i = 0;
    while (i < n && x_eval > x[i + 1]) {
        ++i;
    }

    // Вычислить значение сплайна на интервале [x[i], x[i+1]]
    double dx = x_eval - x[i];
    const SplineCoefficients& coeff = coefficients[i];
    return coeff.a + coeff.b * dx + coeff.c * dx * dx + coeff.d * dx * dx * dx;
}


void write_to_csv_function(const string& filename, const vector<double>& x_values, const vector<double>& f_values, const vector<double>& spline_values) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи." << endl;
        return;
    }

    
    file << "x;f(x);Spline" << endl;

    
    for (size_t i = 0; i < x_values.size(); ++i) {
        file << fixed << setprecision(6)
             << x_values[i] << ";"
             << f_values[i] << ";"
             << spline_values[i] << endl;
    }

    file.close();
    cout << "Данные успешно записаны в файл: " << filename << endl;
}


void write_to_csv_table(const string& filename, const vector<double>& x_values, const vector<double>& spline_values) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи." << endl;
        return;
    }

   
    file << "x;Spline" << endl;

    
    for (size_t i = 0; i < x_values.size(); ++i) {
        file << fixed << setprecision(6)
             << x_values[i] << ";"
             << spline_values[i] << endl;
    }

    file.close();
    cout << "Данные успешно записаны в файл: " << filename << endl;
}


int main() {
    
    cout << "=== ЧАСТЬ 1: Для функции f(x) ===" << endl;
    int n = 10; // Количество узлов
    vector<double> x_func(n + 1), y_func(n + 1);

    
    for (int i = 0; i <= n; ++i) {
        x_func[i] = -1.0 + 2.0 * i / n;
        y_func[i] = 1.0 / (1.0 + 25.0 * x_func[i] * x_func[i]);
    }

    // Построение кубического сплайна
    vector<SplineCoefficients> spline_func = build_cubic_spline(x_func, y_func);

    
    int num_points = 100; 
    vector<double> test_points(num_points), func_values(num_points), spline_values(num_points);

    for (int i = 0; i < num_points; ++i) {
        test_points[i] = -1.0 + 2.0 * i / (num_points - 1);
        func_values[i] = 1.0 / (1.0 + 25.0 * test_points[i] * test_points[i]);
        spline_values[i] = evaluate_spline(test_points[i], x_func, spline_func);
    }

   
    write_to_csv_function("kub1.csv", test_points, func_values, spline_values);

    
    cout << "\n=== ЧАСТЬ 2: Для таблицы данных ===" << endl;
    vector<double> x_table = {2, 3, 5, 7};
    vector<double> y_table = {4, -2, 6, -3};

    // Построение кубического сплайна
    vector<SplineCoefficients> spline_table = build_cubic_spline(x_table, y_table);

    
    vector<double> test_points_table(num_points), spline_values_table(num_points);

    for (int i = 0; i < num_points; ++i) {
        test_points_table[i] = x_table[0] + (x_table.back() - x_table[0]) * i / (num_points - 1);
        spline_values_table[i] = evaluate_spline(test_points_table[i], x_table, spline_table);
    }

    
    write_to_csv_table("kub2.csv", test_points_table, spline_values_table);

    return 0;
}