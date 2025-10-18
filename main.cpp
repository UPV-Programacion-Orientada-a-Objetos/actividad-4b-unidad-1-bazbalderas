#include "Simulador2D.h"

void mostrarMenu() {
    cout << "\n===== MENÚ DE OPCIONES =====" << endl;
    cout << "1. Simular 1 Paso" << endl;
    cout << "2. Redimensionar Grid" << endl;
    cout << "3. Mostrar Grid Actual" << endl;
    cout << "4. Salir" << endl;
    cout << "Opción: ";
}

int main() {
    cout << "--- Simulador Genérico de Fluidos (Difusión) ---" << endl;
    
    // INICIALIZACIÓN AUTOMÁTICA DEL SISTEMA
    cout << "\n>> Inicializando Sistema (Tipo FLOAT) <<" << endl;
    cout << "Creando Grid (FLOAT) de 5x5..." << endl;
    
    Simulador2D<float> sim(5, 5);
    
    // AGREGAR FUENTES AUTOMÁTICAMENTE
    cout << "\n>> Agregando Fuentes de Concentración <<" << endl;
    sim.agregarFuente(100.0f);
    cout << "Agregar Fuente 1 (Valor 100.0): Éxito." << endl;
    sim.agregarFuente(50.0f);
    cout << "Agregar Fuente 2 (Valor 50.0): Éxito." << endl;
    
    // APLICAR VALORES INICIALES AUTOMÁTICAMENTE
    cout << "\n>> Aplicando Valores Iniciales <<" << endl;
    sim.setValor(2, 2, 100.0f);
    cout << "Grid[2,2] = 100.0 (Fuente 1)" << endl;
    sim.setValor(4, 0, 50.0f);
    cout << "Grid[4,0] = 50.0 (Fuente 2)" << endl;
    
    // MOSTRAR ESTADO INICIAL
    cout << "\n--- Grid Inicial (Paso 0) ---" << endl;
    sim.imprimir();
    
    // MENÚ INTERACTIVO PARA OPERACIONES
    int opcion;
    int pasoActual = 0;
    bool salir = false;
    
    while (!salir) {
        mostrarMenu();
        cin >> opcion;
        
        switch (opcion) {
            case 1: {
                // Simular 1 paso
                cout << "\nOpción: Simular 1 Paso" << endl;
                cout << "Simulando Propagación..." << endl;
                sim.simularPaso();
                pasoActual++;
                
                cout << "\n--- Grid Después del Paso " << pasoActual << " ---" << endl;
                sim.imprimir();
                break;
            }
            
            case 2: {
                // Redimensionar
                int nuevaF, nuevaC;
                cout << "\nOpción: Redimensionar" << endl;
                cout << "Ingrese nuevas filas: ";
                cin >> nuevaF;
                cout << "Ingrese nuevas columnas: ";
                cin >> nuevaC;
                
                sim.redimensionarGrid(nuevaF, nuevaC);
                cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". Datos copiados." << endl;
                
                cout << "\n--- Grid Redimensionado ---" << endl;
                sim.imprimir();
                break;
            }
            
            case 3: {
                // Mostrar grid actual
                cout << "\n--- Grid Actual (Paso " << pasoActual << ") ---" << endl;
                sim.imprimir();
                break;
            }
            
            case 4: {
                // Salir
                cout << "\nOpción: Salir" << endl;
                cout << "Liberando memoria del Grid y Fuentes... Sistema cerrado." << endl;
                salir = true;
                break;
            }
            
            default:
                cout << "\nOpción inválida. Intente nuevamente." << endl;
                break;
        }
    }
    
    return 0;
}
