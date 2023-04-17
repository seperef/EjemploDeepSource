//
// Created by seperef on 15/03/2023.
//

#include <iostream>
#include <cmath>
#include "vector.h"

using namespace std;

int main(){
    double v[] = {1,1,1};

    double v1[] = {1,2,3};
    double v2[] = {1,2,3};

    //Test norma de un vector
    if(norm(v, 3) - sqrt(3.0) < pow(10, -12))
        cout << "Test de norm() correcto" << endl;
    else
        cout << "Test de norm() erroneo" << endl;


    //Test producto escalar
    if(dot(v1,v2,3,3) - 9 < pow(10, -12))
        cout << "Test de pow() correcto" << endl;
    else
        cout << "Test de pow() incorrecto" << endl;


    //Test producto vectorial
    double *vp;
    cross(v1,v2,3,3,v);
    if((v[0] == 0) && (v[1] == 0) && (v[2] == 0)){
        cout << "Test de cross() correcto" << endl;
    }else{
        cout << "Test de cross() incorrecto" << endl;
    }


    return 0;
}