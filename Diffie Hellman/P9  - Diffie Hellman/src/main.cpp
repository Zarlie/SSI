#include <iostream>

int algoritmo(int a, int xAB, int p) {
    int x = 1, y = a % p;
   
    while ((xAB > 0) && (y > 1)){
        if (xAB%2 == 1){
            x = (x * y) % p;
            xAB -= 1;
        }
        else {
            y = (y*y) % p;
            xAB = xAB / 2;
        }
    }
    return x;
}


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


int main() {

    int p = 1, a = 0, xA = 0, xB = 0, yA = 0, yB = 0;
    int kA = 0, kB = 0;

    std::cout << "Algoritmo Diffie-Hellman" << std::endl;
    std::cout << "Introduzca un número primo p: ";
    std::cin >> p;
    while (primo(p) == false){
        std::cout << "Error. Introduzca un número primo: ";
        std::cin >> p;
    }
    
    std::cout << "Introduzca un número a: ";
    std::cin >> a;
    while (a >= p){
        std::cout << "Error. Introduzca 'a' un número menor que p: ";
        std::cin >> a;
    }
    
    std::cout << "Introduzca el número secreto xA: ";
    std::cin.ignore();
    std::cin >> xA;
    std::cout << "Introduzca el número secreto xB: ";
    std::cin.ignore();
    std::cin >> xB;

    yA = algoritmo(a,xA,p);
    yB = algoritmo(a,xB,p);

    std::cout <<"yA: "<< yA << std::endl;
    std::cout <<"yB: "<< yB << std::endl;

    kA = algoritmo(yB,xA,p);
    kB = algoritmo(yA,xB,p);

    if (kA == kB){
        std::cout << "El valor de la clave compartida coincide." << std::endl;
        std::cout<< "k: " << kA <<std::endl;
    }
    else {
        std::cout << "Error. Las claves generadas no coinciden" << std::endl;
    }
}


