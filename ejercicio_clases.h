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
