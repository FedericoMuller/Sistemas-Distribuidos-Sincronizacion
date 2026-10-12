#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <algorithm>

using namespace std;

mutex mtx;

// Estructura para representar un mensaje o petición con marca de tiempo Lamport
struct Request {
    int timestamp;
    int pid;
    bool operator<(const Request& other) const {
        if (timestamp == other.timestamp)
            return pid > other.pid; // Desempate por ID de proceso
        return timestamp > other.timestamp; // Min-heap para la cola de prioridad
    }
};

priority_queue<Request> cola_global;
int reloj_logico = 0;

void proceso(int id, int orden_esperado) {
    mtx.lock();
    reloj_logico++;
    int mi_tiempo = reloj_logico;
    cout << "[Proceso " << id << "] Genera evento con reloj lógico: " << mi_tiempo << endl;
    cola_global.push({mi_tiempo, id});
    mtx.unlock();

    this_thread::sleep_for(chrono::milliseconds(100 * id)); // Simula retardo de red

    mtx.lock();
    // Verificamos si es el turno de este proceso según Lamport
    if (!cola_global.empty() && cola_global.top().pid == id) {
        cout << ">>> [Proceso " << id << "] ¡Es mi turno! Ejecutando tarea en orden correcto (Secuencia esperada)." << endl;
        cola_global.pop();
    } else {
        cout << "--- [Proceso " << id << "] Esperando turno en la cola..." << endl;
    }
    mtx.unlock();
}

int main() {
    cout << "=== SIMULACIÓN: ALGORITMO DE LAMPORT (Orden P1, P2, P3, P4) ===" << endl;
    vector<thread> hilos;

    // Lanzamos los 4 procesos
    for (int i = 1; i <= 4; ++i) {
        hilos.emplace_back(proceso, i, i);
    }

    for (auto& h : hilos) {
        h.join();
    }

    cout << "=== Ejecución finalizada ===" << endl;
    return 0;
}