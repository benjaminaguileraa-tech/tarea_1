#include <iostream>
#include <vector>
using namespace std;

// CLASE BASE 
class Ejercicio {
public:
    string nombre;
    string tipo;
    int id;
    string nivel;
    int tiempo;
    string descripcion;
    int semana;

    Ejercicio(string nombre, string tipo, int id, string nivel, int tiempo, string descripcion, int semana) {
        this->nombre = nombre;
        this->tipo = tipo;
        this->id = id;
        this->nivel = nivel;
        this->tiempo = tiempo;
        this->descripcion = descripcion;
        this->semana = semana;
        cout << "Se creo el ejercicio " << this->nombre << endl;
    }

    virtual ~Ejercicio() {
        cout << "Se destruyo el ejercicio " << this->nombre << endl;
    }

    virtual void consultarEjercicio() {
        cout << "ID: " << id << endl;
        cout << "Nombre: " << nombre << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Nivel: " << nivel << endl;
        cout << "Tiempo: " << tiempo << " minutos" << endl;
        cout << "Descripcion: " << descripcion << endl;
        if(semana == -1) {
            cout << "Semana ultimo uso: Nunca" << endl;
        } else {
            cout << "Semana ultimo uso: " << semana << endl;
        }
    }

    void actualizarEjercicio(string nombre, string tipo, string nivel, 
                             int tiempo, string descripcion, int semana) {
        this->nombre = nombre;
        this->tipo = tipo;
        this->nivel = nivel;
        this->tiempo = tiempo;
        this->descripcion = descripcion;
        this->semana = semana;
        cout << "Ejercicio actualizado!" << endl;
    }
};

// CLASE CARDIO
class Cardio : public Ejercicio {
public:
    Cardio(string nombre, int id, string nivel, int tiempo, string descripcion, int semana): Ejercicio(nombre, "Cardiovascular", id, nivel, tiempo, descripcion, semana) {
        cout << "  -> Tipo: Cardiovascular" << endl;
    }

    ~Cardio() {} // Destructor

    void consultarEjercicio() {
        cout << " EJERCICIO CARDIOVASCULAR " << endl;
        Ejercicio::consultarEjercicio();
    }
};

// CLASE FUERZA
class Fuerza : public Ejercicio {
public:
    Fuerza(string nombre, int id, string nivel, int tiempo,string descripcion, int semana): Ejercicio(nombre, "Fuerza", id, nivel, tiempo, descripcion, semana) {
        cout << "  -> Tipo: Fuerza" << endl;
    }

    ~Fuerza() {
        // Destructor
    }

    void consultarEjercicio() {
        cout << " EJERCICIO DE FUERZA " << endl;
        Ejercicio::consultarEjercicio();
    }
};

// FUNCIONES AUXILIARES
void limpiarBuffer() {
    cin.clear();
    cin.ignore(1000, '\n'); 
}

string seleccionarTipo() {
    int op;
    cout << "Tipo de ejercicio (1-Cardiovascular, 2-Fuerza): ";
    cin >> op;
    limpiarBuffer();
    if(op == 1) {
        return "Cardiovascular";
    } else {
        return "Fuerza";
    }
}

void crearEjercicio(vector<Ejercicio*>& lista, int& contadorId) {
    string nombre, nivel, descripcion, tipo;
    int tiempo, semana;

    cout << "\n--- CREAR EJERCICIO ---" << endl;
    cout << "Nombre: ";
    getline(cin, nombre);

    tipo = seleccionarTipo();

    cout << "Nivel (Basico/Intermedio/Avanzado/Alto rendimiento): ";
    getline(cin, nivel);

    cout << "Tiempo (minutos): ";
    cin >> tiempo;
    limpiarBuffer();

    cout << "Descripcion: ";
    getline(cin, descripcion);

    cout << "Semana de uso (-1 si nunca se ha usado): ";
    cin >> semana;
    limpiarBuffer();

    int id = contadorId++;

    if(tipo == "Cardiovascular") {
        lista.push_back(new Cardio(nombre, id, nivel, tiempo, descripcion, semana));
    } else {
        lista.push_back(new Fuerza(nombre, id, nivel, tiempo, descripcion, semana));
    }

    cout << "Ejercicio creado con ID: " << id << endl;
}

Ejercicio* buscarPorId(vector<Ejercicio*>& lista, int id) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i]->id == id)
            return lista[i];
    }
    return NULL;
}

void eliminarEjercicio(vector<Ejercicio*>& lista, int id) {
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i]->id == id) {
            delete lista[i];
            // Eliminar del vector
            for(int j = i; j < lista.size() - 1; j++) {
                lista[j] = lista[j + 1];
            }
            lista.pop_back();
            cout << "Ejercicio eliminado" << endl;
            return;
        }
    }
    cout << "No se encontro ejercicio con ID " << id << endl;
}

void buscarPorNivel(vector<Ejercicio*>& lista, string nivel) {
    bool encontrado = false;
    cout << "\n--- EJERCICIOS DE NIVEL " << nivel << " ---" << endl;
    for (int i = 0; i < lista.size(); i++) {
        if (lista[i]->nivel == nivel) {
            lista[i]->consultarEjercicio();
            cout << endl;
            encontrado = true;
        }
    }
    if(!encontrado) {
        cout << "No hay ejercicios de nivel " << nivel << endl;
    }
}

void mostrarTodosEjercicios(vector<Ejercicio*>& lista) {
    cout << "\n=== TODOS LOS EJERCICIOS ===" << endl;
    if(lista.size() == 0) {
        cout << "No hay ejercicios registrados." << endl;
    } else {
        for(int i = 0; i < lista.size(); i++) {
            lista[i]->consultarEjercicio();
            cout << endl;
        }
    }
}

// CLASE RUTINA
class Rutina {
public:
    vector<Ejercicio*> ejercicios;
    int tiempoTotal;
    string nombreCliente;
    int semanaActual;

    Rutina(string nombreCliente, int semana) {
        this->nombreCliente = nombreCliente;
        this->semanaActual = semana;
        this->tiempoTotal = 0;
    }

    bool sePuedeUsar(Ejercicio* e) {
        // Verificar que no se haya usado en la semana actual o la anterior
        if(e->semana == this->semanaActual || e->semana == this->semanaActual - 1) {
            return false;
        }
        return true;
    }

    void crearRutina(vector<Ejercicio*>& disponibles, int cantidad, string nivel) {
        ejercicios.clear();
        tiempoTotal = 0;

        vector<Ejercicio*> candidatos;

        // Filtrar ejercicios por nivel y que no se hayan usado recientemente
        for(int i = 0; i < disponibles.size(); i++) {
            if(disponibles[i]->nivel == nivel && sePuedeUsar(disponibles[i])) {
                candidatos.push_back(disponibles[i]);
            }
        }

        // Si no hay suficientes, agregar ejercicios de otros niveles
        if(candidatos.size() < cantidad) {
            for(int i = 0; i < disponibles.size(); i++) {
                if(disponibles[i]->nivel != nivel && sePuedeUsar(disponibles[i])) {
                    // Verificar que no esté ya en candidatos
                    bool yaEsta = false;
                    for(int j = 0; j < candidatos.size(); j++) {
                        if(candidatos[j]->id == disponibles[i]->id) {
                            yaEsta = true;
                            break;
                        }
                    }
                    if(!yaEsta) {
                        candidatos.push_back(disponibles[i]);
                    }
                }
            }
        }

        // Seleccionar los primeros 'cantidad' ejercicios
        if(candidatos.size() >= cantidad) {
            for(int i = 0; i < cantidad; i++) {
                ejercicios.push_back(candidatos[i]);
                tiempoTotal += candidatos[i]->tiempo;
                candidatos[i]->semana = this->semanaActual; // Marcar como usado
            }
            cout << "\nRutina generada exitosamente!" << endl;
        } else {
            cout << "\nNo hay suficientes ejercicios disponibles." << endl;
            cout << "Ejercicios disponibles que cumplen: " << candidatos.size() << endl;
            cout << "Ejercicios necesarios: " << cantidad << endl;
        }
    }

    void mostrarRutina() {
        if(ejercicios.size() == 0) {
            cout << "No hay ejercicios en esta rutina." << endl;
            return;
        }

        cout << "\n========================================" << endl;
        cout << "RUTINA PARA: " << nombreCliente << endl;
        cout << "Semana: " << semanaActual << endl;
        cout << "========================================" << endl;

        for(int i = 0; i < ejercicios.size(); i++) {
            cout << "\nEjercicio " << i+1 << ":" << endl;
            ejercicios[i]->consultarEjercicio();
            cout << "----------------------------------------" << endl;
        }

        cout << "\nTIEMPO TOTAL ESTIMADO: " << tiempoTotal << " minutos" << endl;
        int horas = tiempoTotal / 60;
        int minutos = tiempoTotal % 60;
        cout << "(Equivalente a " << horas << " horas y " << minutos << " minutos)" << endl;
        cout << "========================================\n" << endl;
    }
};

// MAIN
int main() {
    vector<Ejercicio*> lista;
    int contadorId = 1;
    int semanaGlobal = 1;
    int opcion;

    // Ejercicios de ejemplo precargados
    cout << "=== CARGANDO EJERCICIOS DE EJEMPLO ===" << endl;
    lista.push_back(new Cardio("Correr suave", contadorId++, "Basico", 20, 
                               "Correr a ritmo suave durante 20 minutos", -1));
    lista.push_back(new Cardio("Caminata rapida", contadorId++, "Basico", 30, 
                               "Caminar a paso rapido", -1));
    lista.push_back(new Fuerza("Flexiones", contadorId++, "Intermedio", 15, 
                               "Realizar 3 series de 10 flexiones", -1));
    lista.push_back(new Fuerza("Sentadillas", contadorId++, "Intermedio", 15, 
                               "Realizar 3 series de 15 sentadillas", -1));
    lista.push_back(new Cardio("Intervalos", contadorId++, "Avanzado", 25, 
                               "Alternar sprints con trote suave", -1));
    lista.push_back(new Fuerza("Peso muerto", contadorId++, "Avanzado", 20, 
                               "Realizar 4 series de 8 repeticiones", -1));
    lista.push_back(new Fuerza("Dominadas", contadorId++, "Alto rendimiento", 30, 
                               "Realizar 5 series de 5 dominadas", -1));

    cout << "\n¡Sistema iniciado con " << lista.size() << " ejercicios de ejemplo!" << endl;

    do {
        cout << "\n--- MENU PRINCIPAL ---" << endl;
        cout << "1. Crear ejercicio" << endl;
        cout << "2. Actualizar ejercicio" << endl;
        cout << "3. Eliminar ejercicio" << endl;
        cout << "4. Consultar ejercicio" << endl;
        cout << "5. Buscar por nivel" << endl;
        cout << "6. Generar rutina" << endl;
        cout << "7. Mostrar todos los ejercicios" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";

        cin >> opcion;

        if (cin.fail()) {
            limpiarBuffer();
            cout << "Ingrese un numero valido" << endl;
            continue;
        }

        if(opcion == 1) {
            limpiarBuffer();
            crearEjercicio(lista, contadorId);
        }
        else if(opcion == 2) {
            int id;
            cout << "ID del ejercicio a actualizar: ";
            cin >> id;
            limpiarBuffer();

            Ejercicio* e = buscarPorId(lista, id);
            if(e != NULL) {
                string nombre, nivel, descripcion;
                int tiempo, semana;

                cout << "Nuevo nombre (actual: " << e->nombre << "): ";
                getline(cin, nombre);

                cout << "Nuevo nivel (actual: " << e->nivel << "): ";
                getline(cin, nivel);

                cout << "Nuevo tiempo (actual: " << e->tiempo << "): ";
                cin >> tiempo;
                limpiarBuffer();

                cout << "Nueva descripcion: ";
                getline(cin, descripcion);

                cout << "Nueva semana (actual: " << e->semana << "): ";
                cin >> semana;
                limpiarBuffer();

                e->actualizarEjercicio(nombre, e->tipo, nivel, tiempo, descripcion, semana);
            } else {
                cout << "No se encontro ejercicio con ID " << id << endl;
            }
        }
        else if(opcion == 3) {
            int id;
            cout << "ID del ejercicio a eliminar: ";
            cin >> id;
            eliminarEjercicio(lista, id);
        }
        else if(opcion == 4) {
            int id;
            cout << "ID del ejercicio a consultar: ";
            cin >> id;
            Ejercicio* e = buscarPorId(lista, id);
            if(e != NULL) {
                e->consultarEjercicio();
            } else {
                cout << "No se encontro ejercicio con ID " << id << endl;
            }
        }
        else if(opcion == 5) {
            string nivel;
            cout << "Nivel a buscar (Basico/Intermedio/Avanzado/Alto rendimiento): ";
            limpiarBuffer();
            getline(cin, nivel);
            buscarPorNivel(lista, nivel);
        }
        else if(opcion == 6) {
            if(lista.size() == 0) {
                cout << "No hay ejercicios disponibles. Cree algunos primero." << endl;
                continue;
            }

            int cantidad;
            string nivel;
            string nombreCliente;

            cout << "\n--- GENERAR RUTINA ---" << endl;
            cout << "Nombre del cliente: ";
            limpiarBuffer();
            getline(cin, nombreCliente);

            cout << "Cantidad de ejercicios: ";
            cin >> cantidad;
            limpiarBuffer();

            cout << "Nivel deseado (Basico/Intermedio/Avanzado/Alto rendimiento): ";
            getline(cin, nivel);

            Rutina rutina(nombreCliente, semanaGlobal);
            rutina.crearRutina(lista, cantidad, nivel);
            rutina.mostrarRutina();

            semanaGlobal = semanaGlobal + 1; // Avanzar semana
            cout << "*** Semana avanzada a " << semanaGlobal << " ***" << endl;
        }
        else if(opcion == 7) {
            mostrarTodosEjercicios(lista);
        }
        else if(opcion == 0) {
            cout << "Saliendo del sistema..." << endl;
        }
        else {
            cout << "Opcion no valida. Intente nuevamente." << endl;
        }

    } while(opcion != 0);

    // Liberar memoria
    cout << "\nLiberando memoria..." << endl;
    for(int i = 0; i < lista.size(); i++) {
        delete lista[i];
    }

    cout << "Programa terminado." << endl;

    return 0;
}