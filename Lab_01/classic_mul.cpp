#include <iostream>
#include <cstdlib> // Para usar rand() y srand()
#include <ctime>   // Para usar time() y generar números aleatorios
#include <chrono>
#include <thread> // Para usar sleep_for

using namespace std;
using namespace std::chrono;

int **crearMatriz(int filas, int columnas) {
    int **matriz = new int *[filas];
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = rand() % 100;
        }
    }
    return matriz;
}

void liberarMatriz(int **matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int **multiplicarMatrices(int **A, int filasA, int columnasA, int **B, int filasB, int columnasB) {
    if (columnasA != filasB) {
        cout << "Error: Las matrices no se pueden multiplicar. Columnas de A deben ser igual a filas de B." << endl;
        return nullptr;
    }

    int **C = new int *[filasA];
    for (int i = 0; i < filasA; i++) {
        C[i] = new int[columnasB];
        for (int j = 0; j < columnasB; j++) {
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

int main(int argc, char *argv[]) {
    srand(100);

    int a = 4;
    int b = 6;
    int c = 8;

    for (int iter = 0; iter < 3; ++iter) { // Ejecutar varias veces para asegurar la captura
        cout << "Iteración #" << iter + 1 << endl;

        int **matriz_1 = crearMatriz(a, b);
        int **matriz_2 = crearMatriz(b, c);

        cout << "Matriz A: " << a << "x" << b << endl;
        cout << "Matriz B: " << b << "x" << c << endl;

        auto inicio1 = high_resolution_clock::now();
        int **result = multiplicarMatrices(matriz_1, a, b, matriz_2, b, c);
        auto fin1 = high_resolution_clock::now();
        auto duracion1 = duration_cast<microseconds>(fin1 - inicio1);
        cout << "El tiempo transcurrido es: " << duracion1.count() << " microsegundos." << endl;
        cout << "\n";
        liberarMatriz(result, a);
        liberarMatriz(matriz_1, a);
        liberarMatriz(matriz_2, b);

        // Aumentar tamaño de matrices para la siguiente iteración
        a *= 10;
        b *= 10;
        c *= 10;

        std::this_thread::sleep_for(std::chrono::seconds(1)); // Pausa para darle tiempo a Instruments
    }

    return 0;
}
