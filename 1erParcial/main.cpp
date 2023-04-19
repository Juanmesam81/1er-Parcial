#include <iostream>
#include <fstream>

using namespace std;

void RegistrarMateria(char* direccion_archivo);
void RegistrarHorario(char* direccion_archivo);
void Matricular(char*** cursos, char*** horario, int n);
void verMaterias(char* direccion_archivo);


int main()
{
    int n = 1;                                          //dim de los espacios para matricular materias
    char*** cursosMatriculados = new char**[n];         // Crear el puntero triple
    for(int i = 0; i < n; i++){                         // Reservar memoria para cada puntero doble
        cursosMatriculados[i] = new char*[4];
        for(int j = 0; j < 4; j++){
            cursosMatriculados[i][j] = new char[30];
        }
    }

    char*** horario = new char**[7];
    for(int i = 0; i < 7; i++){
        horario[i] = new char*[24];
        for(int j = 0; j < 24; j++){
            horario[i][j] = new char[30];
        }
    }
    // Recorrer el puntero triple y asignar "Libre" a cada posición
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 24; j++){
                horario[i][j] = "Libre";
        }
    }

    Matricular(cursosMatriculados, horario, n);
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < 4; ++j){
            cout << cursosMatriculados[i][j] << endl;
        }
        cout << endl;
    }
    //RegistrarMateria("C:\\Users\\computador\\Desktop\\Materias_registradas.txt");
    //RegistrarHorario("C:\\Users\\computador\\Desktop\\Horarios_registrados.txt");
    return 0;
}

void RegistrarMateria(char* direccion_archivo){
    char** materia = new char* [5];
    for (int i = 0; i < 5; i++){
        materia[i] = new char [30];
    }
    cout << "Ingrese el codigo del curso: ";
    cin >> materia[0];
    int tamano = 0;
    while (materia[0][tamano] != '\0' && tamano < 30) {
        tamano++;
    }
    while(tamano != 7){
        cout << endl << "El codigo debe tener una longitud de 7 caracteres, ingrese el codigo correcto: ";
        cin >> materia[0];
        tamano = 0;
        while(materia[0][tamano] != '\0' && tamano < 30){
            tamano++;
        }
    }
    cout << endl;
    cout << "Ingrese el nombre del curso sin espacios: ";
    cin >> materia[1];
    cout << endl;
    cout << "Ingrese las horas de clase por semana del curso: ";
    cin >> materia[2][0];
    while(int(materia[2][0]) - 48 < 1 || int(materia[2][0]) - 48 > 9){
        cout << endl << "Ingrese horas validas de clase por semana del curso: ";
        cin >> materia[2][0];
    }
    cout << endl;
    cout << "Ingrese el numero de creditos del curso: ";
    cin >> materia[4][0];
    while(int(materia[4][0]) - 48 < 1 || int(materia[4][0]) - 48 > 9){
        cout << endl << int(materia[4][0]);
        cout << endl << "Ingrese horas validas de clase por semana del curso: ";
        cin >> materia[4][0];
    }
    cout << endl;
    int x = static_cast<int>(materia[4][0]) - 48;
    x = (x*48)/16;
    int y = static_cast<int>(materia[2][0]) - 48;
    int htps = x - y;
    char htp = char(htps);          //para que htp valga su equivalente en int
    materia[3][0] = htp;

    ofstream archivo_salida(direccion_archivo, ios::app);
    if(archivo_salida.is_open()){
        for(int i = 0; i < 5; i++){
            if(i == 0 || i == 1){
                archivo_salida << materia[i] << ' ';
            }
            else{
                if(i == 3){
                    archivo_salida << int(materia[i][0]) << ' ';  //para poder almacenar el valor entero, no lo que significa en ascii
                }
                else{
                    archivo_salida << materia[i][0] << ' ';
                }
            }
        }
        archivo_salida << endl;
        archivo_salida.close();
    }
    else{
        cout << "Error al abrir el archivo." << endl;
    }
    for (int i = 0; i < 5; i++) {
        delete[] materia[i];
    }
    delete[] materia;
}

void RegistrarHorario(char* direccion_archivo){
    char* codigo = new char[30];
    int NHorarios = 0;
    cout << "Ingrese el codigo de la materia: ";
    cin >> codigo;
    cout << endl << "Ingrese el # de horarios que tendra la materia: ";
    cin >> NHorarios;
    cout << endl;
    char** horario = new char* [NHorarios+1];
    for (int i = 0; i < NHorarios+1; i++){
        horario[i] = new char [30];
    }
    horario[0] = codigo;
    for (int i = 1; i < NHorarios+1; i++){
        cout << "Ingrese el horario " << i << ": ";
        cin >> horario[i];
    }

    ofstream archivo_salida(direccion_archivo, ios::app);
    if(archivo_salida.is_open()){
        for(int i = 0; i < NHorarios+1; i++){
            archivo_salida << horario[i] << '|';
        }
        archivo_salida << endl;
        archivo_salida.close();
    }
    else{
        cout << "Error al abrir el archivo." << endl;
        }
    for (int i = 0; i < NHorarios+1; i++){
        delete[] horario[i];
    }
    delete[] horario;
}

void Matricular(char*** cursos, char*** horario, int n){
    int cont = 0;
    char* codigo = new char[7];
    cout << "Ingrese el codigo de la materia que desea matricular: ";
    cin >> codigo;
    int tamano = 0;
    while(codigo[tamano] != '\0' && tamano < 30){
        tamano++;
    }
    while(tamano != 7){
        cout << endl << "El codigo debe tener una longitud de 7 caracteres, ingrese el codigo correcto: ";
        cin >> codigo;
        tamano = 0;
        while(codigo[tamano] != '\0' && tamano < 30){
            tamano++;
        }
    }
    ifstream archivo("C:\\Users\\computador\\Desktop\\Materias_registradas.txt");
    if (archivo.is_open()){
        char* linea = new char[256];
        while(archivo.getline(linea, 256)){
            cont = 0;
            for(int i = 0; i < 7; i++){
                if(linea[i] == codigo[i]){
                    cont++;
                }
            }
            if(cont == 7){
                break;
            }
        }
        archivo.close();
        //cout << linea << endl;
        int aux = 0;                    //indice de la segunda capa del puntero triple de cursos
        int aux1 = 0;                   //indice de la tercera capa del puntero triple de cursos
        int aux2 = 0;                   //indice de la variable que contiene el renglon completo
        cont = 0;                       //para el # de datos que necesitaremos
        while(cont != 4){
            aux1 = 0;
            while(linea[aux2] != '\0'){
                if(linea[aux2] == ' '){
                   break;
               }
               cursos[n-1][aux][aux1] = linea[aux2];
               aux1++;
               aux2++;
            }
            if(cont == 1){
                aux2 += 2;
            }
            cont++;
            aux++;
            aux2++;
        }
    }
    else{
        cout << "No se pudo abrir el archivo de los cursos." << endl;
    }
    ifstream archivoHorarios("C:\\Users\\computador\\Desktop\\Horarios_registrados.txt");
    if (archivoHorarios.is_open()){
        char* linea1 = new char[256];
        while(archivoHorarios.getline(linea1, 256)){
            cont = 0;
            for(int i = 0; i < 7; i++){
                if(linea1[i] == codigo[i]){
                    cont++;
                }
            }
            if(cont == 7){
                break;
            }
        }
        archivoHorarios.close();
        int aux = 1;
        int aux1 = 0;
        cont = 8;
        for(int i = 0; i < 256; i++){
            if(linea1[i] == '\0'){
                break;
            }
            aux1++;
        }
        cout << "Los horarios de la materia son los siguientes: " << endl << "Horario " << aux << ": ";
        while(cont < aux1){
            if(linea1[cont] == '|'){
                cout << endl;
                cont++;
                aux++;
                if(linea1[cont] != '\0'){
                    cout << "Horario " << aux << ": ";
                }
            }
            cout << linea1[cont];
            cont++;
        }
        cout << endl << endl;
    }
    else{
        cout << "El archivo de los horarios no pudo ser abierto." << endl;
    }
    //Pedir horario elegido al usuario
    char horarioElegido[20];
    cout << "Ingrese el horario que desea, recuerde escribirlo tal cual como se le pedira a continuacion: ";
    cin >> horarioElegido;
    cout << endl;
    tamano = 0;
    while(codigo[tamano] != '\0' && tamano < 20){
        tamano++;
    }
    if(tamano == 4){
        int dia1 = static_cast<int>(horarioElegido[0]) - 48;
        //hora1
    }
}

void verMaterias(char* direccion_archivo){
    ifstream archivo(direccion_archivo);
    if (archivo.is_open()){
        cout << "Las materias registradas en la base de datos son:" << endl << endl;
        char* linea = new char[256];
        while (archivo.getline(linea, 256)){
          cout << linea << endl;
        }
    }
}
