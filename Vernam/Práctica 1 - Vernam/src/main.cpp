#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <random>
#include <bitset>
#include <sstream>

// PRÁCTICA 1 - CIFRADO DE VERNAM

/* Implementa en el lenguaje que prefieras el cifrado y descifrado de Vernam según la
descripción que se incluye a continuación:
• El cifrado opera bit a bit, mediante la operación XOR entre el mensaje original y la clave aleatoria. 
• El descifrado opera bit a bit, mediante la operación XOR entre el mensaje cifrado y la clave aleatoria.
Utiliza código ASCII para pasar de letras a bytes y viceversa, cuando se trate de
caracteres imprimibles. */


// -- CLAVE ALEATORIA -- //
std::vector<std::bitset<8>> random_key(int msg_size, std::vector<std::bitset<8>> &vector_clave, std::vector<std::bitset<8>> &vector_final){
    srand(time(NULL));
    for(int i = 0; i<msg_size*8; ++i){
        vector_clave.push_back(std::bitset<8>(rand()%127));
    }

    std::cout<<std::endl;
    std::cout<<"Clave aleatoria: ";
    for(unsigned int i = 0; i<vector_final.size();i++)
        std::cout<<vector_clave[i];
    std::cout<<std::endl;

    return vector_clave;
}


// -- MÉTODO DE CIFRADO -- //
void coded(std::string &coded_msg){

    std::vector<std::bitset<8>> vector_final, vector_clave;
    std::vector<int> vector_aux;
    int msg_size = strlen(coded_msg.c_str());
    std::random_device rand;
    int opcion=2;


    // -- Conversión del mensaje introducido a binario --
    for(int i=0; i<msg_size; i++) {
        vector_final.push_back(std::bitset<8>(coded_msg.c_str()[i]));
    }

    std::cout<<"Mensaje original en binario: ";
    for(unsigned int i=0; i<vector_final.size();i++){
        std::cout<<vector_final[i];
    }
    std::cout<<std::endl;
    std::cout<<"Longitud del mensaje en binario: " << vector_final.size()*8<<std::endl;
    

    // -- Introducción de claves --
    std::cout<<"\n¿Introducir clave aleatoria o por teclado?"<<std::endl;
    std::cout<<"1- Aleatoria."<<std::endl;
    std::cout<<"2- Por teclado."<<std::endl;
    std::cin >> opcion;

    if(opcion==1)
        random_key(msg_size,vector_clave,vector_final);
    
    else{
        std::bitset<8> clave;
        std::string clave_des;
        std::cout<<"Clave: ";
        std::cin >> clave_des;
        
        std::istringstream cl(clave_des);
        for (unsigned int i = 0; i < clave_des.size()/8; i++){
            cl >> clave;
            vector_clave.push_back(clave);
        } 
    }
    

    // -- Cifrado final del mensaje --
    // XOR
    for (unsigned int k = 0; k < vector_final.size(); ++k)
        vector_final[k] = (vector_final[k] ^ vector_clave[k]);

    std::cout<<"Mensaje cifrado en binario: ";
        for (unsigned int k = 0; k < vector_final.size(); ++k)
            std::cout<<vector_final[k];
    std::cout<<std::endl;

    // Traducción del resultado de la XOR a caracteres ASCII
    std::string final_text;
    std::cout<< "Mensaje cifrado: ";
    for (unsigned int i=0; i < vector_final.size(); ++i){
        vector_aux.push_back(vector_final[i].to_ulong()); //to_ulong -> Convierte el resultado de la XOR a numero decimal ASCII
        if(vector_aux[i] >127 ){
            vector_aux[i] = vector_aux[i] % 126;
            final_text = static_cast<char>(vector_aux[i]); //static_cast -> cada elemento del vector lo transforma en un char
            std::cout<< final_text;

        }
        if (vector_aux[i]<33){
            vector_aux[i] += vector_aux[i] % 32;
            final_text = static_cast<char>(vector_aux[i]);
            std::cout<< final_text;
        }
        else{
            final_text = static_cast<char>(vector_aux[i]); //static_cast -> cada elemento del vector lo transforma en un char
            std::cout<< final_text;
        }
    }
    std::cout<<std::endl;
}



// -- MÉTODO DE DESCIFRADO -- //
void decoded(std::string &decoded_msg){

    std::vector<std::bitset<8>> vector_final, vector_clave;
    std::vector<int> vector_aux;
    int msg_size = strlen(decoded_msg.c_str());
    std::random_device rand;
    std::bitset<8> clave;
    std::string clave_des;
    int opcion=2;


    // -- Conversión del mensaje introducido a binario --
    for(int i=0; i<msg_size; i++) {
        vector_final.push_back(std::bitset<8>(decoded_msg.c_str()[i]));
    }

    std::cout<<"Mensaje cifrado en binario: ";
    for(unsigned int i=0; i<vector_final.size();i++){
        std::cout<<vector_final[i];
    }
    std::cout<<std::endl;
    std::cout<<"Longitud del mensaje en binario: " << vector_final.size()*8<<std::endl;


    // -- Introducción de claves --
    std::cout<<"\n¿Introducir clave aleatoria o por teclado?"<<std::endl;
    std::cout<<"1- Aleatoria."<<std::endl;
    std::cout<<"2- Por teclado."<<std::endl;
    std::cin >> opcion;

    if(opcion==1)
        random_key(msg_size,vector_clave,vector_final);
    
    else{
        std::bitset<8> clave;
        std::string clave_des;
        std::cout<<"Clave: ";
        std::cin >> clave_des;
        
        std::istringstream cl(clave_des);
        for (unsigned int i = 0; i < clave_des.size()/8; i++){
            cl >> clave;
            vector_clave.push_back(clave);
        }
    } 


    // -- Cifrado final del mensaje --
    // XOR
    for (unsigned int k = 0; k < vector_final.size(); ++k)
        vector_final[k] = (vector_final[k] ^ vector_clave[k]);

    std::cout<<"Mensaje original en binario: ";
        for (unsigned int k = 0; k < vector_final.size(); ++k)
            std::cout<<vector_final[k];
    std::cout<<std::endl;

    // Traducción del resultado de la XOR a caracteres ASCII
    std::string final_text;
    std::cout<< "Mensaje original: ";

    for (unsigned int i=0; i < vector_final.size(); ++i){
        vector_aux.push_back(vector_final[i].to_ulong()); //to_ulong -> Convierte el resultado de la XOR a numero decimal ASCII
        if(vector_aux[i] >127 ){
            vector_aux[i] = vector_aux[i] % 126;
            final_text = static_cast<char>(vector_aux[i]); //static_cast -> cada elemento del vector lo transforma en un char
            std::cout<< final_text;
        }

        if (vector_aux[i]<33){
            vector_aux[i] += vector_aux[i] % 32;
            final_text = static_cast<char>(vector_aux[i]);
            std::cout<< final_text;
        }

        else{
            final_text = static_cast<char>(vector_aux[i]); //static_cast -> cada elemento del vector lo transforma en un char
            std::cout<< final_text;
        }
    }
    std::cout<<std::endl;
}


// -- MAIN -- //
int main (void){
    int x;
    std::string coded_msg;
    std::string decoded_msg;
    
    std::cout<<"-- IMPLEMENTACIÓN DEL CIFRADO DE VERNAM --\n"<<std::endl;
    std::cout<<"Introduzca la opción que desee realizar: "<<std::endl;
    std::cout<<"1 - Cifrar"<<std::endl;
    std::cout<<"2 - Descifrar"<<std::endl;
    std::cout<<"- En caso de querer salir, pulse cualquier otro número"<<std::endl;
    std::cin>>x;
    std::cout<<std::endl;

    switch(x){
        case 1: std::cout<< "- OPCIÓN DE CIFRADO -";
                std::cout<< "\nIntroduzca el mensaje que desea cifrar"<<std::endl;
                std::cin.ignore(); 
                std::cout<<"Mensaje original: ";
                std::getline(std::cin,coded_msg);
                coded(coded_msg);
                break;
                  
        case 2: std::cout<< "- OPCIÓN DE DESCIFRADO -";
                std::cout<< "\nIntroduzca el mensaje que desea descifrar"<<std::endl;
                std::cin.ignore();
                std::cout<<"Mensaje cifrado: ";
                std::getline(std::cin, decoded_msg);
                decoded(decoded_msg);
                break;

        default: std::cout<<"Gracias por haber usado la máquina de cifrado de Vernam."<<std::endl;
                std::cout<<"Saliendo..."<<std::endl;
                break; 
    }      
}
