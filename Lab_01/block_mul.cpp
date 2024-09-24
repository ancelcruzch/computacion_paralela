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

const int BLOQUE = 4; // Tamaño del bloque
int **multiplicarPorBloques(int **A, int filasA, int columnasA, int **B, int filasB, int columnasB) {
    if (columnasA != filasB) {
        cout << "Error: Las columnas de A deben ser igual a las filas de B." << endl;
        return nullptr;
    }

    int **C = new int *[filasA];
    for (int i = 0; i < filasA; i++) {
        C[i] = new int[columnasB];
        for (int j = 0; j < columnasB; j++) {
            C[i][j] = 0;
        }
    }

    for (int i_bloque = 0; i_bloque < filasA; i_bloque += BLOQUE) {
        for (int j_bloque = 0; j_bloque < columnasB; j_bloque += BLOQUE) {
            for (int k_bloque = 0; k_bloque < columnasA; k_bloque += BLOQUE) {
                for (int i = i_bloque; i < min(i_bloque + BLOQUE, filasA); i++) {
                    for (int j = j_bloque; j < min(j_bloque + BLOQUE, columnasB); j++) {
                        for (int k = k_bloque; k < min(k_bloque + BLOQUE, columnasA); k++) {
                            C[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
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

        auto inicio2 = high_resolution_clock::now();
        int **result2 = multiplicarPorBloques(matriz_1, a, b, matriz_2, b, c);
        auto fin2 = high_resolution_clock::now();
        auto duracion2 = duration_cast<microseconds>(fin2 - inicio2);
        cout << "El tiempo transcurrido es: " << duracion2.count() << " microsegundos." << endl;
        cout << "\n";

        liberarMatriz(result2, a);
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
