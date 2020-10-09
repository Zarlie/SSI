#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>


// Cálculo de la retroalimentación
std::bitset<1> LFSR(std::vector<int> &D) {
    int aux = 0;
    if (D.size() == 25) {
        int bit7 = D[7], bit11 = D[11], bit20 = D[20], bit24 = D[24];
        std::bitset<1> p1(bit7), p2(bit11), p3(bit20), p4(bit24);
        std::bitset<1> xor_ = p1 ^ p2 ^ p3 ^ p4;
        aux = xor_[0];
        D.insert(D.begin(),aux);
        
        return xor_;
    }

    else if (D.size() == 31) {
        int bit11 = D[11], bit15 = D[15], bit23 = D[23], bit30 = D[30];
        std::bitset<1> p1(bit11), p2(bit15), p3(bit23), p4(bit30);
        std::bitset<1> xor_ = p1 ^ p2 ^ p3 ^ p4;
        aux = xor_[0];
        D.insert(D.begin(),aux);
        return xor_;
    }
    
    else if (D.size() == 34) {
        int bit3 = D[3], bit23 = D[23], bit28 = D[28], bit33 = D[33];
        std::bitset<1> p1(bit3), p2(bit23), p3(bit28), p4(bit33);
        std::bitset<1> xor_ = p1 ^ p2 ^ p3 ^ p4;
        aux = xor_[0];
        D.insert(D.begin(),aux);
        return xor_;
    }

    else if (D.size() == 39) {
    int bit3 = D[3], bit27 = D[27], bit35 =  D[35], bit38 = D[38];
        std::bitset<1> p1(bit3), p2(bit27), p3(bit35), p4(bit38);
        std::bitset<1> xor_ = p1 ^ p2 ^ p3 ^ p4;
        aux = xor_[0];
        D.insert(D.begin(),aux);
        return xor_;
    }  
}

// Función para realizar un "swap" en un registro
std::vector<int> shift(std::vector<int> &R) {
    std::vector<int> R1;
    int aux = R[1], aux2 = R[0];
    
    R1.push_back(aux);
    R1.push_back(aux2);
    
    return R1;
}

// Método para convertir un vector de enteros a una variable de tipo int
int vector_to_int(std::vector<int> V){
    reverse(V.begin(), V.end());
    int decimal = 1;
    int total = 0;
    
    for (auto& it : V){
        total += it * decimal;
        decimal *= 10;
    }
    return total;
}

// Método que convierte un binario a una variable de tipo int
int cases(int &R_int) {
    if(R_int == 00){
        return 0;
    }
    else if (R_int == 01) {
        return 1;
    }
    else if (R_int == 10) {
        return 2;
    }
    else if (R_int == 11) {
        return 3;
    }
}


// Método Generador: Nos devuelve el valor de R1 para poder operar en la siguiente iteración
std::vector<int> generador (std::vector<int> &D1, std::vector<int> &D2, std::vector<int> &D3, std::vector<int> &D4, std::vector<int> &R) {
    int caja1, caja2, division, R1_int, R1_final;
    std::bitset<1> resultado_final, aux;
    std::vector<int> R2, R1;

    // Swap de posiciones
    R1 = shift(R);
    R2 = shift(R1);
    
    R1_int = vector_to_int(R1);
    R1_final = cases(R1_int);
    
    caja1 = D1[24] + D2[30] + D3[32] + D4[38];
    caja2 = caja1 + R1_final;
    division = caja2 / 2;

    std::bitset<2> result_div(division);
    std::bitset<2> T1(R1_int);
    std::bitset<2> T2, xor1, xor2;

    T2[0] = R2[1];
    T2[1] = R2[1]^R2[0];

    xor1 = result_div ^ T2;
    xor2 = xor1 ^ T1;

    aux[0] = R1[1];

    resultado_final = LFSR(D1) ^ LFSR(D2) ^ LFSR(D3) ^ LFSR(D4) ^ aux;
    std::cout << "Salida: " <<resultado_final;
    std::cout<<std::endl;
    
    R1[0] = xor2[1];
    R1[1] = xor2[0];

    return R1;  
}



int main() {
    // Declaración de nuestros 4 registros lineales de desplazamiento con retroalimentación
    std::vector<int> D1 = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::vector<int> D2 = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::vector<int> D3 = {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    std::vector<int> D4 = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};
    std::vector<int> R1 = {0,1};
    int salida;

    std::cout << "PRÁCTICA 5 - GENERADOR E0 DE BLUETOOTH" << std::endl;
    std::cout<<std::endl;
    std::cout << "Semilla del primer registro: ";
    for (unsigned int i = 0; i < D1.size(); i++){
        std::cout << D1[i];
    }
    std::cout<<std::endl;

    std::cout << "Semilla del segundo registro: ";
    for (unsigned int i = 0; i < D2.size(); i++){
        std::cout << D2[i];
    }
    std::cout<<std::endl;
    
    std::cout << "Semilla del tercer registro: ";
    for (unsigned int i = 0; i < D3.size(); i++){
        std::cout << D3[i];
    }
    std::cout<<std::endl;

    std::cout << "Semilla del cuarto registro: ";
    for (unsigned int i = 0; i < D4.size(); i++){
        std::cout << D4[i];
    }
    std::cout<<std::endl;

    std::cout << "Semilla de R1: ";
    for (unsigned int i = 0; i < R1.size(); i++){
        std::cout << R1[i];
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout << "Introduce el número de bits de salida: ";
    std::cin >> salida;

    
    for (int i = 0; i < salida; i++){
        std::cout << std::endl;
        std::cout << "Desplazamiento " << i << ":" << std::endl;
        
        R1 = generador(D1,D2,D3,D4,R1);
    }
    std::cout << std::endl;
}