#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Simulación del Servidor de Tiempo
long long obtener_tiempo_servidor() {
    // Retorna la hora actual del servidor en milisegundos
    auto ahora = chrono::system_clock::now();
    auto milisegundos = chrono::duration_cast<chrono::milliseconds>(ahora.time_since_epoch()).count();
    return milisegundos + 50; // Simulamos que el servidor va 50ms adelantado
}

void cliente_cristian() {
    cout << "[Cliente] Solicitando la hora al servidor..." << endl;
    
    // T0: Momento en que el cliente envía la petición
    auto t0 = chrono::steady_clock::now();
    
    // Simulamos retardo de red de ida y vuelta (ej. 30 milisegundos)
    this_thread::sleep_for(chrono::milliseconds(30));
    long long tiempo_servidor = obtener_tiempo_servidor();
    this_thread::sleep_for(chrono::milliseconds(30));
    
    // T1: Momento en que el cliente recibe la respuesta
    auto t1 = chrono::steady_clock::now();

    // Calcula el RTT (Round Trip Time / Tiempo de ida y vuelta)
    long long rtt = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
    cout << "[Cliente] Tiempo de ida y vuelta (RTT): " << rtt << " ms" << endl;

    // Aplicando fórmula de Cristian: Hora actual = Hora del servidor + (RTT / 2)
    long long hora_sincronizada = tiempo_servidor + (rtt / 2);
    
    cout << "[Cliente] Hora del servidor recibida: " << tiempo_servidor << endl;
    cout << "[Cliente] ¡Reloj sincronizado exitosamente a: " << hora_sincronizada << " ms!" << endl;
}

int main() {
    cout << "=== SIMULACIÓN: MÉTODO DE CRISTIAN ===" << endl;
    cliente_cristian();
    return 0;
}