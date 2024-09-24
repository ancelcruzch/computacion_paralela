#include <iostream>
#include <cstdlib>  // Para usar rand() y srand()
#include <ctime>    // Para usar time() y generar números aleatorios
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para crear una matriz con números aleatorios
int** crearMatriz(int filas, int columnas) {
    // Crear una matriz de punteros (filas)
    int** matriz = new int*[filas];

    // Asignar memoria para cada columna en cada fila
    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }

    // Llenar la matriz con números aleatorios entre 0 y 99
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            matriz[i][j] = rand() % 100;  // Número aleatorio entre 0 y 99
        }
    }

    return matriz;
}

// Función para liberar la memoria de la matriz
void liberarMatriz(int** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];  // Liberar cada fila
    }
    delete[] matriz;  // Liberar el arreglo de punteros
}

/* +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+- */

int** multiplicarMatrices(int** A, int filasA, int columnasA, int** B, int filasB, int columnasB) {
    // Verificar si las matrices son compatibles para la multiplicación
    if (columnasA != filasB) {
        cout << "Error: Las matrices no se pueden multiplicar. Columnas de A deben ser igual a filas de B." << endl;
        return nullptr;
    }

    // Crear la matriz resultado
    int** C = new int*[filasA];
    for (int i = 0; i < filasA; i++) {
        C[i] = new int[columnasB];
    }

    // Inicializar la matriz resultado en ceros
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            C[i][j] = 0;
        }
    }

    // Multiplicación de matrices
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < columnasB; j++) {
            for (int k = 0; k < columnasA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}


// Multiplicaicon por Bloques..
const int BLOQUE = 4;  // Tamaño del bloque
int** multiplicarPorBloques(int** A, int filasA, int columnasA, int** B, int filasB, int columnasB) {
    // Verificar si las matrices son compatibles para la multiplicación
    if (columnasA != filasB) {
        cout << "Error: Las columnas de A deben ser igual a las filas de B." << endl;
        return nullptr;
    }

    // Crear la matriz resultado C
    int** C = new int*[filasA];
    for (int i = 0; i < filasA; i++) {
        C[i] = new int[columnasB];
        for (int j = 0; j < columnasB; j++) {
            C[i][j] = 0;  // Inicializar la matriz C con ceros
        }
    }

    // Seis bucles anidados: tres para los bloques y tres para los elementos dentro de los bloques
    for (int i_bloque = 0; i_bloque < filasA; i_bloque += BLOQUE) {
        for (int j_bloque = 0; j_bloque < columnasB; j_bloque += BLOQUE) {
            for (int k_bloque = 0; k_bloque < columnasA; k_bloque += BLOQUE) {
                // Multiplicación de los elementos dentro del bloque
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

    return C;  // Devolver la matriz resultante C
}


void mostrarMatriz(int** matriz, int filas, int columnas){
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}


int main() {
    // Inicializar el generador de números aleatorios con una semilla basada en el tiempo actual
    srand(100);

    // Solicitar número de filas y columnas
    int a = 4;
    int b = 6;
    int c = 8;

    // Multiplicacion de matrices de forma clasica..
    for(int i=0; i<5; i++){
        // Crear la matriz con números aleatorios
        int** matriz_1 = crearMatriz(a, b);
        int** matriz_2 = crearMatriz(b, c);

        cout << "Matriz A: " << a << "x" << b << endl;
        //mostrarMatriz(matriz_1, a, b);
        cout << "Matriz B: " << b << "x" << c << endl;
        //mostrarMatriz(matriz_2, b, c);


        cout << "VERSION CLASICA: " << endl;
        auto inicio1 = high_resolution_clock::now();
        int** result = multiplicarMatrices(matriz_1, a, b, matriz_2, b, c);
        auto fin1 = high_resolution_clock::now();

        // Calcular la duración
        auto duracion1 = duration_cast<nanoseconds>(fin1 - inicio1);
        //mostrarMatriz(result, a, c);
        cout << "El tiempo transcurrido es: " << duracion1.count() << " nanosegundos." << endl;

        cout << "VERSION POR BLOQUES: " << endl;
        auto inicio2 = high_resolution_clock::now();
        int** result2 = multiplicarPorBloques(matriz_1, a, b, matriz_2, b, c);
        auto fin2 = high_resolution_clock::now();

        //mostrarMatriz(result2, a, c);
        auto duracion2 = duration_cast<nanoseconds>(fin2 - inicio2);
        //mostrarMatriz(result2, a, c);
        cout << "El tiempo transcurrido es: " << duracion2.count() << " nanosegundos." << endl;

        a *= 5; b *= 5; c *= 5;
    }




    return 0;
}
