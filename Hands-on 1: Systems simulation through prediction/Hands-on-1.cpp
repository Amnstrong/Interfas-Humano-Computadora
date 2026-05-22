#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
class Experimento {
private:
    double x1;
    double x2;
    double y;

public:
    Experimento(double _x1, double _x2, double _y) {
        x1 = _x1;
        x2 = _x2;
        y = _y;
    }

    double getX1() const {
        return x1;
    }

    double getX2() const {
        return x2;
    }

    double getY() const {
        return y;
    }
};

class LeastSquaredRegressor {
private:
    vector<Experimento> data;

    double B0;
    double B1;
    double B2;

public:

    LeastSquaredRegressor() {
        Dataset();
        B0 = 0;
        B1 = 0;
        B2 = 0;
    }

    // Cargar dataset
    void Dataset() {

        data.push_back(Experimento(41.9, 29.1, 251.3));
        data.push_back(Experimento(43.4, 29.3, 251.3));
        data.push_back(Experimento(43.9, 29.5, 248.3));
        data.push_back(Experimento(44.5, 29.7, 267.5));
        data.push_back(Experimento(47.3, 29.9, 273.0));
        data.push_back(Experimento(47.5, 30.3, 276.5));
        data.push_back(Experimento(47.9, 30.5, 270.3));
        data.push_back(Experimento(50.2, 30.7, 274.9));
        data.push_back(Experimento(52.8, 30.8, 285.0));
        data.push_back(Experimento(53.2, 30.9, 290.0));
        data.push_back(Experimento(56.7, 31.5, 297.0));
        data.push_back(Experimento(57.0, 31.7, 302.5));
        data.push_back(Experimento(63.5, 31.9, 304.5));
        data.push_back(Experimento(65.3, 32.0, 309.3));
        data.push_back(Experimento(71.1, 32.1, 321.7));
        data.push_back(Experimento(77.0, 32.5, 330.7));
        data.push_back(Experimento(77.8, 32.9, 349.0));
    }

    // Entrenar modelo
    void ModeloEntrenado() {

        int n = data.size();

        double sumX1 = 0;
        double sumX2 = 0;
        double sumY = 0;

        double sumX1X1 = 0;
        double sumX2X2 = 0;
        double sumX1X2 = 0;

        double sumX1Y = 0;
        double sumX2Y = 0;

        // Calcular sumatorias
        for (int i = 0; i < n; i++) {

            double x1 = data[i].getX1();
            double x2 = data[i].getX2();
            double y = data[i].getY();

            sumX1 += x1;
            sumX2 += x2;
            sumY += y;

            sumX1X1 += x1 * x1;
            sumX2X2 += x2 * x2;
            sumX1X2 += x1 * x2;

            sumX1Y += x1 * y;
            sumX2Y += x2 * y;
        }

        // Matriz aumentada del sistema
        double A[3][4] = {

            { (double)n, sumX1, sumX2, sumY },

            { sumX1, sumX1X1, sumX1X2, sumX1Y },

            { sumX2, sumX1X2, sumX2X2, sumX2Y }
        };
        // Eliminación Gaussiana
        // Paso 1
        for (int i = 1; i < 3; i++) {

            double factor = A[i][0] / A[0][0];

            for (int j = 0; j < 4; j++) {
                A[i][j] -= factor * A[0][j];
            }
        }

        // Paso 2
        double factor = A[2][1] / A[1][1];

        for (int j = 1; j < 4; j++) {
            A[2][j] -= factor * A[1][j];
        }

        B2 = A[2][3] / A[2][2];

        B1 = (A[1][3] - A[1][2] * B2) / A[1][1];

        B0 = (A[0][3] - A[0][1] * B1 - A[0][2] * B2) / A[0][0];
    }

    // Predicción
    double predicion(double x1, double x2) {

        return B0 + (B1 * x1) + (B2 * x2);
    }

    // Imprimir ecuación
    void ImprimirEcuacion() {

        cout << fixed << setprecision(4);

        cout << "\n=====================================\n";
        cout << "PARAMETROS OPTIMOS\n";
        cout << "=====================================\n";

        cout << "B0 = " << B0 << endl;
        cout << "B1 = " << B1 << endl;
        cout << "B2 = " << B2 << endl;

        cout << "\n=====================================\n";
        cout << "ECUACION DE REGRESION\n";
        cout << "=====================================\n";

        cout << "Yield = "
             << B0
             << " + (" << B1 << " * X1)"
             << " + (" << B2 << " * X2)"
             << endl;
    }

    // Simulación de experimentos
    void simulacionExperimento() {

        cout << "\n=====================================\n";
        cout << "SIMULACION DE EXPERIMENTOS\n";
        cout << "=====================================\n";

        double tests[5][2] = {

            {45.0, 30.0},
            {50.0, 31.0},
            {60.0, 31.5},
            {70.0, 32.0},
            {78.0, 33.0}
        };

        for (int i = 0; i < 5; i++) {

            double x1 = tests[i][0];
            double x2 = tests[i][1];

            double yPred = predicion(x1, x2);

            cout << "\nExperimento " << i + 1 << endl;

            cout << "X1 = " << x1 << endl;
            cout << "X2 = " << x2 << endl;

            cout << "Yield Predicho = "
                 << fixed
                 << setprecision(4)
                 << yPred
                 << endl;
        }
    }
};
int main() {

    LeastSquaredRegressor model;

    model.ModeloEntrenado();

    model.ImprimirEcuacion();

    model.simulacionExperimento();

    return 0;
}