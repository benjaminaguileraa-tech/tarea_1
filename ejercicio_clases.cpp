#include "ejercicio_clases.h"

// --- CLASE EJERCICIO ---
Ejercicio::Ejercicio(string nombre, string tipo, int id, string nivel, int tiempo, string descripcion, int semana) {
    this->nombre = nombre;
    this->tipo = tipo;
    this->id = id;
    this->nivel = nivel;
    this->tiempo = tiempo;
    this->descripcion = descripcion;
    this->semana = semana;
}

Ejercicio::~Ejercicio() {}

void Ejercicio::consultarEjercicio() {
    cout << "ID: " << id << " | Nombre: " << nombre << " | Tipo: " << tipo 
         << " | Nivel: " << nivel << " | Tiempo: " << tiempo << " min | Semana: " << semana << endl;
    cout << "Descripción: " << descripcion << endl;
}

void Ejercicio::actualizarEjercicio(string nombre, string tipo, string nivel, int tiempo, string descripcion, int semana) {
    this->nombre = nombre;
    this->tipo = tipo;
    this->nivel = nivel;
    this->tiempo = tiempo;
    this->descripcion = descripcion;
    this->semana = semana;
}

// --- CLASE CARDIO ---
Cardio::Cardio(string nombre, int id, string nivel, int tiempo, string descripcion, int semana, int nivelImpacto)
    : Ejercicio(nombre, "Cardio", id, nivel, tiempo, descripcion, semana) {
    this->nivelImpacto = nivelImpacto;
}

void Cardio::consultarEjercicio() {
    Ejercicio::consultarEjercicio(); // Reutiliza el código de la clase padre
    cout << "Nivel de impacto: " << nivelImpacto << "/10" << endl;
}

// --- CLASE FUERZA ---
Fuerza::Fuerza(string nombre, int id, string nivel, int tiempo, string descripcion, int semana, int pesoRecomendado)
    : Ejercicio(nombre, "Fuerza", id, nivel, tiempo, descripcion, semana) {
    this->pesoRecomendado = pesoRecomendado;
}

void Fuerza::consultarEjercicio() {
    Ejercicio::consultarEjercicio();
    cout << "Peso recomendado: " << pesoRecomendado << " kg" << endl;
}

// --- CLASE RUTINA ---
Rutina::Rutina(string cliente, int semanaActual) {
    this->cliente = cliente;
    this->semanaActual = semanaActual;
    this->duracionTotal = 0;
}

void Rutina::crearRutina(vector<Ejercicio*>& catalogo, int cantidad, string nivel) {
    int agregados = 0;
    for (Ejercicio* ej : catalogo) {
        if (agregados >= cantidad) break;
        
        // RESTRICCIÓN: Mismo nivel y no repetido de la semana anterior
        if (ej->nivel == nivel && ej->semana != (semanaActual - 1)) {
            ejerciciosSeleccionados.push_back(ej);
            duracionTotal += ej->tiempo;
            agregados++;
        }
    }
    if (agregados < cantidad) {
        cout << "Aviso: Solo se encontraron " << agregados << " ejercicios válidos." << endl;
    }
}

void Rutina::mostrarRutina() {
    cout << "\n--- Rutina para " << cliente << " (Semana " << semanaActual << ") ---" << endl;
    for (Ejercicio* ej : ejerciciosSeleccionados) {
        ej->consultarEjercicio();
        cout << "----------------------" << endl;
    }
    cout << "** Duración total estimada: " << duracionTotal << " minutos. **" << endl;
}
