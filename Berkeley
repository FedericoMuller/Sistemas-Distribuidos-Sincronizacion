#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <numeric>

using namespace std;

// Simulamos el tiempo local de cada máquina en segundos (con pequeños desvíos)
vector<int> tiempos_maquinas = {1000, 1005, 992, 1010}; // Maestro en índice 0 (tiempo 1000)

void maestro_berkeley() {
    cout << "[Maestro] Iniciando sincronización de relojes..." << endl;
    int n = tiempos_maquinas.size();
    
    // 1. Maestro solicita la hora a todos los esclavos
    vector<int> diferencias(n);
    int tiempo_maestro = tiempos_maquinas[0];
    
    cout << "[Maestro] Mi hora es: " << tiempo_maestro << endl;
    for (int i = 0; i < n; ++i) {
        diferencias[i] = tiempos_maquinas[i] - tiempo_maestro;
        cout << "[Maestro] Diferencia con Máquina " << i << " es: " << diferencias[i] << "s" << endl;
    }

    // 2. Calcula el promedio de las diferencias
    int suma = accumulate(diferencias.begin(), diferencias.end(), 0);
    int promedio_ajuste = suma / n;
    cout << "[Maestro] Ajuste promedio calculado: " << promedio_ajuste << "s" << endl;

    // 3. Envía el ajuste a cada máquina
    for (int i = 0; i < n; ++i) {
        int ajuste_necesario = promedio_ajuste - diferencias[i];
        tiempos_maquinas[i] += ajuste_necesario;
        cout << "[Máquina " << i << "] Hora ajustada a: " << tiempos_maquinas[i] << "s" << endl;
    }
}

int main() {
    cout << "=== SIMULACIÓN: ALGORITMO DE BERKELEY ===" << endl;
    maestro_berkeley();
    return 0;
}