#include <iostream>
#include <cmath>
#include <cstdlib>

//Repuesta de A envía a B
int envio (int x, int s, int N, int e){
    int y;

    if (e == 0) {
        y = x % N;
    }
    else {
        y = (x*s) % N;
    }
    return y;
}

//Verificacion de la respuesta de A
void verificacion(int y, int a, int v, int N, int e){
    std::cout << "a = " << a << ", y = " << y << std::endl;
    if (e == 0) {
        std::cout << "Comprobar que " << y << "² ≡ " << a << " (mod " << N << ")" << std::endl;
        if (((int)(pow(y,2)) % N) == (a % N)){
            std::cout << "Se acepta la verificación" << std::endl;
        } 
        else {
            std::cout << "No se acepta la verificación" << std::endl;
        }
    }
    else {
        std::cout << "Comprobar que " << y << "² ≡ " << a <<"*" << v << " (mod " << N << ")" << std::endl; 
        if (((int)(pow(y,2)) % N) == (a*v) % N){
            std::cout << "Se acepta la verificación" << std::endl;
        }
        else {
            std::cout << "No se acepta la verificación" << std::endl;
        }
    }
}

//Comprueba si un número es primo
bool primo(int p){

    int divisor = 1, divisores = 0;
    do{
        if (p % divisor == 0){
            divisores++;
        }
        divisor++;
    } while(divisor <= p);

    if (divisores == 2) {
        return true;
    } 
    else{
        return false;
    }
}

//Comprueba si un número es coprimo de otro
bool mcd (int n, int m){
    bool coprimos= true;
    for (int i = 2; i <= n; i++){
        if (n % i == 0 && m % i == 0){ //comprueba si tienen un divisor comun   
            coprimos = false;
        }
    }
    return coprimos;
}


int main() {
    
    int p = 0, q = 0, s = 0, iteraciones = 0, N = 0, v = 0, x = 0, e = 0;
    int y,a;

    std::cout << "Práctica 10. Fiat-Shamir" << std::endl;
    std::cout << "Introduzca un número primo 'p': ";
    std::cin >> p;
    while (primo(p) == false){
        std::cout << "Error. Introduzca un número primo 'p': ";
        std::cin >> p;
    }

    std::cout << "Introduzca un número primo 'q': ";
    std::cin >> q;    
    while (primo(q) == false){
        std::cout << "Error. Introduzca un número primo 'q': ";
        std::cin >> q;
    }

    N = p * q;

    std::cout << "Introduzca un número 's': ";
    std::cin >> s;
    while ((mcd(s,N) == false) || (s > N)){
        std::cout << "Error. Introduzca un número 's' que sea coprimo de 'N', de la forma 0<s<N: ";
        std::cin >> s;   
    }
    

    mcd(s,N);
    
    v = ((int)(pow(s,2))) % N;

    std::cout << "Introduzca el número de iteraciones: ";
    std::cin >> iteraciones;

    std::cout << "N = " << N << std::endl;
    std::cout << "v = " << v << std::endl;
    
    
    for (int i = 0; i < iteraciones; i++){
        std::cout << "Iteracion " << i + 1 <<": ";
        std::cout << "Introduzca un número secreto 'x': ";
        std::cin >> x;
        while (x < 0 || x > N){
            std::cout << "Error. Introduzca un número 'x' de la forma 0<x<N: ";
            std::cin >> x;        
        }
        // std::cout << "Introduzca un bit 'e' entre 0 y 1: ";
        // std::cin >> e;
        
        srand(time(NULL));
        e = rand() % 2;
        std::cout << "e = " << e << std::endl;

        a = ((int)(pow(x,2))) % N;
        y = envio(x,s,N,e);
        verificacion(y,a,v,N,e);
    }
}

