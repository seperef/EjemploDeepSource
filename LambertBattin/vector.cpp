//
// Created by seperef on 15/03/2023.
//

#include "vector.h"
#include <cmath>


//Pre: v es un vector de números reales y n es un entero que indica la dimensión del vector
//Post: devuelve la norma del vector v
double norm(double v[], int n) {
    double suma = 0;
    int i;
    if(n <= 0)
        throw "Empty vector";
    for(i = 0; i < n; i++)
        suma += v[i]*v[i];
    return (sqrt(suma));
}

//Pre: v1 es un vector de numeros reales de dimensión n1, v2 es un vector de números reales de dimensión n2
//Post: devuelve el producto escalar de dos vectores si tienen el mismo tamaño y no hay ninguno vacío
double dot(double v1[], double v2[], int n1, int n2){
    double suma = 0;
    int i;
    if(n1 <= 0 || n2 <= 0) {
        throw "Error en los vectores (al menos uno vacio)";
    }else if(n1 != n2){
        throw "Vectores de distintos tamaños";
    }else{
        for(i = 0; i < n1; i++)
            suma += v1[i] * v2[i];
    }
    return suma;
}

//Pre: v1 es un vector de números reales de dimensión n1, v2 es un vector de números reales de dimensión n2
        //v es un vector de números reales de dimensión 3 y pv es un puntero a números reales
//Post: devuelve en v el producto vectorial de los dos vectores (v1, v2) si tienen el mismo tamaño y no son ninguno vacío
void cross(double v1[], double v2[], int n1, int n2, double v[]){

    double sum = 0;

    if(n1 <= 0 || n2 <=0){
        throw "Error en los vectores (al menos uno vacío)";
    }else if(n1 != n2){
        throw "Vectores de distintos tamaños";
    }else {
        v[0] = v1[1] * v2[2] - v1[2] * v2[1];
        v[1] = v1[2] * v2[0] - v1[0] * v2[2];
        v[2] = v1[0] * v2[1] - v1[1] * v2[0];

    }
}