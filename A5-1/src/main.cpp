#include <iostream>
#include <bitset>
#include <vector>

// Salida z(t)
std::bitset<1> output(std::bitset<19> &R1, std::bitset<22> &R2,std::bitset<23> &R3){
    return (R1[18] ^ R2[21] ^ R3[22]);
}


// Cálculo de desplazamientos
std::bitset<1> LSFR1(std::bitset<19> &p) {
    std::bitset<1> xor_result = p[18] + p[17] + p[16] + p[13];
    p <<= 1;
    p[0] = xor_result[0];
    return xor_result;
}

std::bitset<1> LSFR2(std::bitset<22> &p) {
    std::bitset<1> xor_result = p[21] + p[20];
    p <<= 1;
    p[0] = xor_result[0];
    return xor_result;
}

std::bitset<1> LSFR3(std::bitset<23> &p) {
    std::bitset<1> xor_result = p[22] + p[21] + p[20] + p[7];
    p <<= 1;
    p[0] = xor_result[0];
    return xor_result;
}




// Desplazamiento de bits
std::bitset<1> shift(std::bitset<19> &R1, std::bitset<22> &R2, std::bitset<23> &R3) {
    // Fijarse en los bits 9,11 y 11 para el desplazamiento
    // Contemplar casos, según la mayoría de estos bits, los registros se desplazarán o quedarán inmóviles
    std::bitset<1> a9, b11, c11;

    // Salida z(t)
    std::bitset<1> salida;
    salida = output(R1,R2,R3);
    std::cout << "La salida del polinomio z(t) es: " << salida << std::endl;

    // Función mayoría
    std::cout << "F(" << R1[8] << "," << R2[10] << "," << R3[10] << ") = " ;
    std::bitset<1> F = ((R1[8]&R2[10]) ^ (R1[8]&R3[10]) ^ (R2[10]&R3[10]));

    if (R1[8] == F[0]) {
        a9 = LSFR1(R1);
    }
    if (R2[10] == F[0]){
        b11 = LSFR2(R2);
    }
    if (R3[10] == F[0]) {
        c11 = LSFR3(R3);
    }

    return (F);
}



int main() {
    // Ejemplos de la profe: 
    // LFSR1: 1001000100011010001
    // LFSR2: 0101100111100010011010
    // LFSR3: 10111100110111100001111
    std::bitset<19> R1(std::string("1001000100011010001"));
    std::bitset<22> R2(std::string("0101100111100010011010"));
    std::bitset<23> R3(std::string("10111100110111100001111"));
    int despl;

    std::cout << "PRÁCTICA 4 - CIFRADO A5/1" << std::endl;
    std::cout << "Introduce el número de desplazamientos: ";
    std::cin >> despl;

    for (int i = 0; i < despl; i++){
        std::cout << std::endl;
        std::cout << "Desplazamiento " << i << ":" << std::endl;
        std::cout << "LSFR 1: " << R1 << std::endl;
        std::cout << "LSFR 2: " << R2 << std::endl;
        std::cout << "LSFR 3: " << R3 << std::endl;
        std::cout << shift(R1,R2,R3) << std::endl;
    }
}