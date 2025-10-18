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

#include "Simulador2D.cpp"

#endif
