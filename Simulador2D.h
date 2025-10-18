#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream>

template <typename T>
class Simulador2D {
private:
    // Matriz de la cuadrícula (Dinámica y Genérica)
    T **_grid;
    int _filas;
    int _columnas;

    // Vector de Fuentes (Dinámico y Genérico)
    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    // Vector de Constantes (Estático)
    float _constantes[3]; // [0] = Coeficiente de Difusión, [1] = DeltaX, [2] = DeltaT

    // Métodos privados auxiliares
    void liberarGrid();
    void copiarGrid(T** origen, T** destino, int filasMin, int colMin);
    
public:
    // Constructor
    Simulador2D(int f, int c);
    
    // Destructor
    ~Simulador2D();
    
    // Constructor de copia
    Simulador2D(const Simulador2D<T>& otro);
    
    // Operador de asignación
    Simulador2D<T>& operator=(const Simulador2D<T>& otro);
    
    // Métodos principales
    void redimensionarGrid(int nuevaF, int nuevaC);
    void agregarFuente(T valor);
    void simularPaso();
    
    // Métodos de acceso
    void setValor(int fila, int col, T valor);
    T getValor(int fila, int col) const;
    void setConstante(int indice, float valor);
    float getConstante(int indice) const;
    
    // Visualización
    void imprimir() const;
    void imprimirFuentes() const;
    
    // Getters
    int getFilas() const { return _filas; }
    int getColumnas() const { return _columnas; }
    int getNumFuentes() const { return _numFuentes; }
};

// ==================== IMPLEMENTACIÓN ====================

// Constructor
template <typename T>
Simulador2D<T>::Simulador2D(int f, int c) : _filas(f), _columnas(c), _numFuentes(0), _capacidadFuentes(10) {
    _grid = new T*[_filas];
    for (int i = 0; i < _filas; i++) {
        _grid[i] = new T[_columnas];
        for (int j = 0; j < _columnas; j++) {
            _grid[i][j] = T(0);
        }
    }
    _fuentes = new T[_capacidadFuentes];
    _constantes[0] = 0.0f;
    _constantes[1] = 1.0f;
    _constantes[2] = 0.01f;
}

// Destructor
template <typename T>
Simulador2D<T>::~Simulador2D() {
    liberarGrid();
    delete[] _fuentes;
}

// Liberar memoria del grid
template <typename T>
void Simulador2D<T>::liberarGrid() {
    for (int i = 0; i < _filas; i++) {
        delete[] _grid[i];
    }
    delete[] _grid;
}

// Copiar grid
template <typename T>
void Simulador2D<T>::copiarGrid(T** origen, T** destino, int filasMin, int colMin) {
    for (int i = 0; i < filasMin; i++) {
        for (int j = 0; j < colMin; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

// Constructor de copia
template <typename T>
Simulador2D<T>::Simulador2D(const Simulador2D<T>& otro) 
    : _filas(otro._filas), _columnas(otro._columnas), 
      _numFuentes(otro._numFuentes), _capacidadFuentes(otro._capacidadFuentes) {
    
    _grid = new T*[_filas];
    for (int i = 0; i < _filas; i++) {
        _grid[i] = new T[_columnas];
        for (int j = 0; j < _columnas; j++) {
            _grid[i][j] = otro._grid[i][j];
        }
    }
    
    _fuentes = new T[_capacidadFuentes];
    for (int i = 0; i < _numFuentes; i++) {
        _fuentes[i] = otro._fuentes[i];
    }
    
    for (int i = 0; i < 3; i++) {
        _constantes[i] = otro._constantes[i];
    }
}

// Operador de asignación
template <typename T>
Simulador2D<T>& Simulador2D<T>::operator=(const Simulador2D<T>& otro) {
    if (this != &otro) {
        liberarGrid();
        delete[] _fuentes;
        
        _filas = otro._filas;
        _columnas = otro._columnas;
        _numFuentes = otro._numFuentes;
        _capacidadFuentes = otro._capacidadFuentes;
        
        _grid = new T*[_filas];
        for (int i = 0; i < _filas; i++) {
            _grid[i] = new T[_columnas];
            for (int j = 0; j < _columnas; j++) {
                _grid[i][j] = otro._grid[i][j];
            }
        }
        
        _fuentes = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; i++) {
            _fuentes[i] = otro._fuentes[i];
        }
        
        for (int i = 0; i < 3; i++) {
            _constantes[i] = otro._constantes[i];
        }
    }
    return *this;
}

// Redimensionar grid
template <typename T>
void Simulador2D<T>::redimensionarGrid(int nuevaF, int nuevaC) {
    T** nuevoGrid = new T*[nuevaF];
    for (int i = 0; i < nuevaF; i++) {
        nuevoGrid[i] = new T[nuevaC];
        for (int j = 0; j < nuevaC; j++) {
            nuevoGrid[i][j] = T(0);
        }
    }
    
    int minFilas = (_filas < nuevaF) ? _filas : nuevaF;
    int minCols = (_columnas < nuevaC) ? _columnas : nuevaC;
    copiarGrid(_grid, nuevoGrid, minFilas, minCols);
    
    liberarGrid();
    _grid = nuevoGrid;
    _filas = nuevaF;
    _columnas = nuevaC;
}

// Agregar fuente
template <typename T>
void Simulador2D<T>::agregarFuente(T valor) {
    if (_numFuentes >= _capacidadFuentes) {
        _capacidadFuentes *= 2;
        T* nuevoVector = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; i++) {
            nuevoVector[i] = _fuentes[i];
        }
        delete[] _fuentes;
        _fuentes = nuevoVector;
    }
    
    _fuentes[_numFuentes] = valor;
    _numFuentes++;
}

// Simular paso de difusión
template <typename T>
void Simulador2D<T>::simularPaso() {
    T** nuevoGrid = new T*[_filas];
    for (int i = 0; i < _filas; i++) {
        nuevoGrid[i] = new T[_columnas];
        for (int j = 0; j < _columnas; j++) {
            nuevoGrid[i][j] = _grid[i][j];
        }
    }
    
    for (int i = 1; i < _filas - 1; i++) {
        for (int j = 1; j < _columnas - 1; j++) {
            T arriba = _grid[i-1][j];
            T abajo = _grid[i+1][j];
            T izquierda = _grid[i][j-1];
            T derecha = _grid[i][j+1];
            
            T promedio = (arriba + abajo + izquierda + derecha) / T(4);
            nuevoGrid[i][j] = promedio;
        }
    }
    
    liberarGrid();
    _grid = nuevoGrid;
}

// Establecer valor
template <typename T>
void Simulador2D<T>::setValor(int fila, int col, T valor) {
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas) {
        _grid[fila][col] = valor;
    }
}

// Obtener valor
template <typename T>
T Simulador2D<T>::getValor(int fila, int col) const {
    if (fila >= 0 && fila < _filas && col >= 0 && col < _columnas) {
        return _grid[fila][col];
    }
    return T(0);
}

// Establecer constante
template <typename T>
void Simulador2D<T>::setConstante(int indice, float valor) {
    if (indice >= 0 && indice < 3) {
        _constantes[indice] = valor;
    }
}

// Obtener constante
template <typename T>
float Simulador2D<T>::getConstante(int indice) const {
    if (indice >= 0 && indice < 3) {
        return _constantes[indice];
    }
    return 0.0f;
}

// Imprimir grid
template <typename T>
void Simulador2D<T>::imprimir() const {
    for (int i = 0; i < _filas; i++) {
        std::cout << "|";
        for (int j = 0; j < _columnas; j++) {
            std::cout << " ";
            std::cout.width(5);
            std::cout.precision(1);
            std::cout << std::fixed << _grid[i][j];
            std::cout << " |";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Imprimir fuentes
template <typename T>
void Simulador2D<T>::imprimirFuentes() const {
    std::cout << "\nFuentes de calor (" << _numFuentes << "):" << std::endl;
    for (int i = 0; i < _numFuentes; i++) {
        std::cout << "Fuente " << (i+1) << ": " << _fuentes[i] << std::endl;
    }
}

#endif
