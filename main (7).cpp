#include <iostream>
#include <vector>
#include <string>
#include "ejercicio_clases.h" // Importante: aquí conectamos con tus clases

using namespace std;

// Función auxiliar para limpiar el buffer de entrada
void limpiarBuffer() {
    cin.clear();
    fflush(stdin);
}

int main() {
    vector<Ejercicio*> catalogo;
    int opcion;

    // Datos de prueba iniciales (opcional)
    catalogo.push_back(new Cardio("Trote", 1, "Básico", 30, "Trote suave en maquina", 1, 3));
    catalogo.push_back(new Fuerza("Sentadillas", 2, "Intermedio", 45, "4 series de 12 repeticiones", 1, 40));

    do {
        cout << "\n--- SISTEMA DE GESTION: GIMNASIO POO ---" << endl;
        cout << "1. Agregar Ejercicio (Cardio/Fuerza)" << endl;
        cout << "2. Consultar Catalogo de Ejercicios" << endl;
        cout << "3. Generar Rutina Semanal para Cliente" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int tipo, id, tiempo, extra, sem;
                string nom, niv, desc;
                
                cout << "Tipo (1. Cardio / 2. Fuerza): "; cin >> tipo;
                cout << "ID: "; cin >> id;
                limpiarBuffer();
                cout << "Nombre: "; getline(cin, nom);
                cout << "Nivel (Basico/Intermedio/Avanzado/Alto rendimiento): "; getline(cin, niv);
                cout << "Tiempo (min): "; cin >> tiempo;
                limpiarBuffer();
                cout << "Descripcion: "; getline(cin, desc);
                cout << "Ultima semana usado: "; cin >> sem;

                if (tipo == 1) {
                    cout << "Nivel de impacto (1-10): "; cin >> extra;
                    catalogo.push_back(new Cardio(nom, id, niv, tiempo, desc, sem, extra));
                } else {
                    cout << "Peso recomendado (kg): "; cin >> extra;
                    catalogo.push_back(new Fuerza(nom, id, niv, tiempo, desc, sem, extra));
                }
                cout << "¡Ejercicio agregado con exito!" << endl;
                break;
            }

            case 2: {
                cout << "\n--- CATALOGO ACTUAL ---" << endl;
                for (Ejercicio* e : catalogo) {
                    e->consultarEjercicio();
                    cout << "-----------------------" << endl;
                }
                break;
            }

            case 3: {
                string cliente, nivelRutina;
                int cant, semAct;
                
                limpiarBuffer();
                cout << "Nombre del Cliente: "; getline(cin, cliente);
                cout << "Semana actual: "; cin >> semAct;
                cout << "Cantidad de ejercicios deseados: "; cin >> cant;
                limpiarBuffer();
                cout << "Nivel de la rutina: "; getline(cin, nivelRutina);

                Rutina nuevaRutina(cliente, semAct);
                nuevaRutina.crearRutina(catalogo, cant, nivelRutina);
                nuevaRutina.mostrarRutina();
                break;
            }

            case 4:
                cout << "Saliendo del sistema..." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
        }
    } while (opcion != 4);

    // Liberar memoria de los punteros al cerrar
    for (Ejercicio* e : catalogo) {
        delete e;
    }

    return 0;
}
