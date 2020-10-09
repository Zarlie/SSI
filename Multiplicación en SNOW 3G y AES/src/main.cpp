#include <iostream>
#include <bitset>
#include <vector>

void multiplicacion(std::bitset<8> &primer_byte, std::bitset<8> &segundo_byte, std::bitset<8> &byte_alg){
    std::vector<std::bitset<8>> vector_almacen;
    std::bitset<8> aux, result;
    aux = primer_byte;
    
    std::cout << "Byte 1: " << primer_byte << std::endl;
    std::cout << "Byte 2: " << segundo_byte << std::endl;
    std::cout << "Byte Algoritmo: " << byte_alg << std::endl;
    
    for (unsigned int i = 0; i < primer_byte.size(); ++i) {
        if (segundo_byte[i] == 1) {
            vector_almacen.push_back(aux);
        }
        if (aux[aux.size()-1] == 1){ 
            aux<<=1;
            aux= aux ^ byte_alg;
        }
        else {
            aux <<= 1;
        }          
    }
    
    for (unsigned int i = 0; i < vector_almacen.size(); i++) {
        result = result ^ vector_almacen[i];
    }

    std::cout << "El resultado de la multiplicación es: " << result << std::endl;
}


int main() {
    int opcion, primer_byte, segundo_byte;
    do {
        std::cout<<std::endl;
        std::cout << "PRÁCTICA 6 - MULTIPLICACIÓN EN AES y SNOW 3G" << std::endl;
        std::cout << "Introduzca el primer byte: ";
        std::cin >> primer_byte;
        std::cout << "Introduzca el segundo byte: ";
        std::cin >> segundo_byte;
        std::cout << "Introduzca la opción que desee" << std::endl;
        std::cout << "1. AES" << std::endl;
        std::cout << "2. SNOW 3G" << std::endl;
        std::cout << "> Introduzca cualquier otro número para salir" << std::endl;
        std::cout << "Opción: ";
        std::cin.ignore();
        std::cin >> opcion;
        std::cout << std::endl;

        std::bitset<8> byte_1(primer_byte), byte_2(segundo_byte), byte_AES(std::string("00011011")), byte_SNOW(std::string("10101001"));

            switch (opcion){

                case 1: 
                    multiplicacion(byte_1, byte_2, byte_AES);
                    std::cout << std::endl;
                    break;
                
                case 2:
                    multiplicacion(byte_1, byte_2, byte_SNOW);
                    std::cout<<std::endl;
                    break;
            }
    } while (opcion == 1 || opcion == 2); 
    
    return 0;
}