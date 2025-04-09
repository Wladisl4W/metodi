#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;


double f(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

// Вычисление базисных полиномов Лагранжа
double lagrange_basis(int i, const vector<double>& nodes, double x) {
    double result = 1.0;
    for (size_t j = 0; j < nodes.size(); ++j) {
        if (i != j) {
            result *= (x - nodes[j]) / (nodes[i] - nodes[j]);
        }
    }
    return result;
}

// Интерполяционный полином Лагранжа
double lagrange_interpolation(const vector<double>& nodes, const vector<double>& values, double x) {
    double result = 0.0;
    for (size_t i = 0; i < nodes.size(); ++i) {
        result += values[i] * lagrange_basis(i, nodes, x);
    }
    return result;
}

// Генерация равноотстоящих узлов
vector<double> generate_equidistant_nodes(int n) {
    vector<double> nodes(n + 1);
    for (int i = 0; i <= n; ++i) {
        nodes[i] = -1.0 + 2.0 * i / n;
    }
    return nodes;
}

// Генерация Чебышевских узлов
vector<double> generate_chebyshev_nodes(int n) {
    vector<double> nodes(n + 1);
    for (int i = 0; i <= n; ++i) {
        nodes[i] = cos(M_PI * (2.0 * i + 1.0) / (2.0 * (n + 1)));
    }
    return nodes;
}


void write_to_file(const string& filename, const vector<double>& x_values,
                   const vector<double>& f_values, const vector<double>& equidistant_interp,
                   const vector<double>& chebyshev_interp) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл для записи." << endl;
        return;
    }

    
    file << "x;f(x);Equidistant;Chebyshev" << endl;

   
    for (size_t i = 0; i < x_values.size(); ++i) {
        file << fixed << setprecision(6)
             << x_values[i] << ";"
             << f_values[i] << ";"
             << equidistant_interp[i] << ";"
             << chebyshev_interp[i] << endl;
    }

    file.close();
    cout << "Данные успешно записаны в файл: " << filename << endl;
}

int main() {
    setlocale(LC_ALL, "ru");

    int n = 15;

    // Генерация узлов
    vector<double> equidistant_nodes = generate_equidistant_nodes(n);
    vector<double> chebyshev_nodes = generate_chebyshev_nodes(n);

    // Значения функции в узлах
    vector<double> equidistant_values(n + 1);
    vector<double> chebyshev_values(n + 1);
    for (int i = 0; i <= n; ++i) {
        equidistant_values[i] = f(equidistant_nodes[i]);
        chebyshev_values[i] = f(chebyshev_nodes[i]);
    }

    // Точки для интерполяции
    int num_points = 100;
    vector<double> x_values(num_points);
    vector<double> f_values(num_points);
    vector<double> equidistant_interp(num_points);
    vector<double> chebyshev_interp(num_points);

    for (int i = 0; i < num_points; ++i) {
        x_values[i] = -1.0 + 2.0 * i / (num_points - 1);
        f_values[i] = f(x_values[i]);
        equidistant_interp[i] = lagrange_interpolation(equidistant_nodes, equidistant_values, x_values[i]);
        chebyshev_interp[i] = lagrange_interpolation(chebyshev_nodes, chebyshev_values, x_values[i]);
    }

    
    write_to_file("output.csv", x_values, f_values, equidistant_interp, chebyshev_interp);

    return 0;
}