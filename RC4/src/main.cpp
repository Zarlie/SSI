#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm> //swap
#include <bitset>
#include <math.h>


//  Método para separar el mensaje
std::vector<int> separation_method(std::string &mensaje_a_separar) {
    std::vector<int> temporal, vct_message;
    std::string aux;
    int result = 0;
    int exp = 0;

    mensaje_a_separar.push_back(',');
    
    for(unsigned int i = 0; i < mensaje_a_separar.size(); ++i){
        aux = mensaje_a_separar[i];
        if((aux != " ") && (aux != ",")){
            temporal.push_back(mensaje_a_separar[i] - 48);
        }
        else{
            for (int j = temporal.size() - 1; j >= 0 ; --j){
                result += temporal[j] * pow(10,exp);
                exp++;
            }

            vct_message.push_back(result);
            result = 0;
            exp = 0;
            temporal.clear();
            temporal.resize(0);
        }
    }
    return vct_message;
}


// Método para introducir la clave
std::vector<int> metodo_clave(){
    std::string aux, clave_;
    std::vector<int> vector_clave;

    std::cout<<"Introduzca una clave por teclado: "<<std::endl;
    std::getline(std::cin,clave_);

    vector_clave = separation_method(clave_);

    return vector_clave;
}


// Método de repetición de la clave
std::vector<int> repeticion_clave(std::vector<int> &vector_clave, std::vector<int> &S){
    unsigned int contador = 0;
    std::vector<int> vector_final_clave;
    int aux;

    // Si la clave es más pequeña que el tamaño del mensaje
    if (vector_clave.size() < S.size()) {
        unsigned int i = 0;
        while (i < S.size()) {
            if (contador >= vector_clave.size()) {
                contador = 0;
            }
            else {
                aux = vector_clave[contador];
                vector_final_clave.push_back(aux);
                contador++;
                ++i;
            }
        }
    }
    // Si la clave es más larga que el mensaje, se envía un mensaje de error
    else{
        std::cout << "Error. El tamaño de la clave debe ser menor de 256" << std::endl;
    }
    return vector_final_clave;
}


// Método para pasar un vector de string a un vector de int
std::vector<int> vector_string_to_int(std::vector<std::string> &texto){
    std::vector<int> texto_int;
    for (unsigned int i = 0; i < texto.size(); ++i){
        for(unsigned int j = 0; j < texto[i].length(); ++j){
            char ch = texto[i].at(j);
            texto_int.push_back(((int)ch) - 48);
        }
    }
    return texto_int;
}


// Método KSA
std::vector<int> metodo_KSA(){
    std::vector<int> S, K, aux_key;
    std::vector<std::string> key_;
    
    // Se inicializa S
    for (unsigned int i = 0; i < 256; ++i) {
        S.push_back(i);
    }
    
    // Llamada al método que crea la clave
    aux_key = metodo_clave();

    // Se expande la clave al tamaño máximo posible
    K = repeticion_clave(aux_key, S);
    
    unsigned int j = 0;
    for(unsigned int i = 0; i < 256; ++i) {
        j = ( j + S[i] + K[i] ) % 256;
        std::swap(S[i],S[j]);
    }
    
    return S;
}


// Método PRGA
std::vector<int> metodo_PRGA(std::vector<int> &S, std::vector<int> vector_message){
    unsigned int i = 0, j = 0, k = 0;
    std::vector<int> F;
 
    while (k < vector_message.size()) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        std::swap(S[i], S[j]);
        unsigned int t = ((S[i] + S[j]) % 256);

        F.push_back(S[t]);

        k++;
    }
    return F;   // Retornamos el Key_Stream
}


// -- CIFRADO -- //
std::vector<int> encrypt(std::string &original_message){
    std::vector<int> S, Key_Stream, Cript_Msg, Vector_message;

    Vector_message = separation_method(original_message);

    S = metodo_KSA();
    Key_Stream = metodo_PRGA(S, Vector_message);
    Cript_Msg = Vector_message;

    // XOR = Suma OR Exclusiva
    for(int i = 0; i < Key_Stream[i];i++){
        Cript_Msg[i] ^= Key_Stream[i];
    }

    std::cout << std::endl;
    std::cout << "> MENSAJE ENCRIPTADO:" << std::endl;
    std::cout <<"- Mensaje encriptado en decimal:"<<std::endl;
    for(unsigned int i = 0; i< Cript_Msg.size();i++){
        std::cout << Cript_Msg[i] << std::endl;
    }

    std::cout <<"- Mensaje encriptado en binario:"<<std::endl;
    for(unsigned int i = 0; i < Cript_Msg.size(); i++){
        std::cout << std::bitset<8>(Cript_Msg[i])<<std::endl;
    }
    return Cript_Msg;
}


// -- DESCIFRADO -- //
void decrypt(std::vector<int> &Criptograma) {
    std::vector<int> S, Key_Stream, temporal, vct_message;

    std::cout << "Su mensaje encriptado es: " << std::endl;
    for(unsigned int i = 0; i< Criptograma.size();i++){
        std::cout << Criptograma[i] << " ";
    }
    std::cout<<std::endl;

    S = metodo_KSA();
    Key_Stream = metodo_PRGA(S,Criptograma); // Llamada al método de generación del Key_Stream

    for(int i = 0; i < Key_Stream[i]; i++){
        Criptograma[i] ^= Key_Stream[i];
    }

    std::cout <<"> MENSAJE ORIGINAL:"<<std::endl;
    for(unsigned int i = 0; i<Criptograma.size(); i++){
        std::cout << Criptograma[i] << ",";
    }
    std::cout<<std::endl;
}


int main() {
    int x;
    std::string original_message;
    std::vector<int> cript_message;

    std::cout << "-- IMPLEMENTACIÓN DEL CIFRADO RC4 --\n" << std::endl;
    std::cout << "--> Introduzca la opción que desee realizar: " << std::endl;
    std::cout << "1. Cifrar y descrifrar" << std::endl;
    std::cout << "En caso de querer salir, pulse cualquier otro número" << std::endl;
    std::cin >> x;
    std::cout << std::endl;

    switch(x) {
        case 1: std::cout << "[- OPCIÓN DE CIFRADO -]" << std::endl;
                std::cout << "Introduzca el mensaje que desea cifrar: " << std::endl;
                std::cin.ignore();
                std::getline(std::cin, original_message);
                cript_message = encrypt(original_message);
                std::cout << std::endl;

                std::cout << "[- OPCIÓN DE DESCIFRADO -]" << std::endl;
                decrypt(cript_message);
                break;
                
        default: std::cout << "Saliendo..." << std::endl;
                break;
    }
}