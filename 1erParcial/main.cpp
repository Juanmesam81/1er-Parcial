#include <iostream>
#include <fstream>

using namespace std;

void RegistrarMateria(char* direccion_archivo);
void RegistrarHorario(char* direccion_archivo);
void Matricular(char*** &cursos, char* codigo, int n);
void MatricularHorario(char*** &horario, char*** &cursos, char* codigo, int n);
void verMaterias(char* direccion_archivo);
void verHorario(char*** horario);
void aumentarMatriz(char*** &cursos, int* &pAn);


int main()
{
    int n = 1;                                          //dim de los espacios para matricular materias
    int *pAn = &n;                                      //para enviar n y modificar n por referencia en la funcion aumentarMatriz
    int control = 9;                                    //variable para manejar los switch
    int AdmoEst = 2;
    cout << "Bienvenido, escriba 0 para ingresar como administrador y 1 para ingresar como estudiante: ";
    cin >> AdmoEst;
    cout << endl << endl;
    if(AdmoEst == 0){
        while(control != 0){
            cout << "Menu:" << endl << endl << "1. Registrar cursos" << endl << "2. Registrar horarios" << endl << "Ingrese 0 para finalizar el programa" << endl << endl;
            switch(control){
                case 0:
                cout << "Has elegido finalizar el programa" << endl << endl;
                    exit(0);
                case 1:
                    cout << "Has elegido el literal 1: Registrar cursos" << endl << endl;
                    RegistrarMateria("C:\\Users\\computador\\Desktop\\Materias_registradas.txt");
                    break;
                case 2:
                    cout << "Has elegido el literal 2: Registrar horarios" << endl << endl;
                    RegistrarHorario("C:\\Users\\computador\\Desktop\\Horarios_registrados.txt");
                    break;
            }
        }
    }
    if(AdmoEst == 1){
        //triple puntero para los cursos que se elijan matricular
        char*** cursosMatriculados = new char**[n];         // Crear el puntero triple
        for(int i = 0; i < n; i++){                         // Reservar memoria para cada puntero doble
            cursosMatriculados[i] = new char*[5];
            for(int j = 0; j < 5; j++){
                cursosMatriculados[i][j] = new char[30];
            }
        }

        //triple puntero para el horario
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
                    horario[i][j] = "**********";
            }
        }
        char usuarioEstudiante[30];
        char contraseñaEstudiante[30];
        char* codigo;
        int tamano;
        cout << "Ingrese su usuario institucional: ";
        cin >> usuarioEstudiante;
        cout << endl << "Ingrese su contrasena: ";
        cin >> contraseñaEstudiante;
        cout << endl << endl << "Bienvenido " << usuarioEstudiante << endl << endl;
        while(control != 0){
            cout << "Menu:" << endl << endl << "1. Matricular cursos" << endl << "2. Ver horario actual" << endl << "3. Sugerir horarios de estudio" << endl << "Ingrese 0 para finalizar el programa" << endl << endl;
            cout << "Ingrese el literal elegido: ";
            cin >> control;
            cout << endl << endl;
            switch (control){
                case 0:
                    cout << "Has elegido finalizar el programa" << endl << endl << "Cursos:" << endl; ;
                    for(int i = 0; i < n; i++){
                        cout << "Curso " << i+1 << ": ";
                            for(int j = 0; j < 5; j++){
                                cout << cursosMatriculados[i][j] << " - ";
                            }
                        cout << endl;
                    }
                    cout << endl << endl << "Horarios: " << endl << endl;
                    for(int i = 0; i < 7; i++){
                        cout << "Dia " << i+1 << ":" << endl;
                        for(int j = 0; j < 24; j++){
                            cout << horario[i][j];
                        }
                    }
                    exit(0);
                    break;
                case 1:
                    cout << "Has elegido el literal 1: Matricular cursos" << endl << endl ;
                    codigo = new char[7];
                    cout << "Ingrese el codigo de la materia que desea matricular: ";
                    cin >> codigo;
                    tamano = 0;
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
                    Matricular(cursosMatriculados, codigo, n);
                    for(int i = 0; i < n; i++){
                        cout << "Curso " << i+1 << ": ";
                            for(int j = 0; j < 5; j++){
                                cout << cursosMatriculados[i][j] << " - ";
                            }
                        cout << endl;
                    }
                    MatricularHorario(horario, cursosMatriculados, codigo, n);
                    aumentarMatriz(cursosMatriculados, pAn);
                    cout << endl;
                    for(int i = 0; i < n; i++){
                        cout << "Curso " << i+1 << ": ";
                            for(int j = 0; j < 5; j++){
                                cout << cursosMatriculados[i][j] << " - ";
                            }
                        cout << endl;
                    }
                    delete[] codigo;
                    break;
                case 2:
                    cout << "Has elegido el literal 2: Ver horario actual" << endl << endl;
                    verHorario(horario);
                    break;
                case 3:
                    cout << "Has elegido el literal 3: Sugerir horarios de estudio" << endl << endl;

                    break;
            }
        }
    }
    return 0;
}

void RegistrarMateria(char* direccion_archivo){
    char** materia = new char* [5];
    for (int i = 0; i < 5; i++){
        materia[i] = new char [30];
    }
    cout << endl << "Ingrese el codigo del curso: ";
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
    cout << endl << endl;
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
    cout << endl << "Ingrese el codigo de la materia: ";
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

void Matricular(char*** &cursos, char* codigo, int n){
    int cont = 0;
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
        int aux = 0;                    //indice de la segunda capa del puntero triple de cursos
        int aux1 = 0;                   //indice de la tercera capa del puntero triple de cursos
        int aux2 = 0;                   //indice de la variable que contiene el renglon completo
        cont = 0;                       //para el # de datos que necesitaremos
        while(cont != 5){
            aux1 = 0;
            while(linea[aux2] != '\0'){
                if(linea[aux2] == ' '){
                   break;
               }
               cursos[n-1][aux][aux1] = linea[aux2];
               aux1++;
               aux2++;
            }
            cont++;
            aux++;
            aux2++;
        }
    }
    else{
        cout << "No se pudo abrir el archivo de los cursos." << endl;
    }
}

void MatricularHorario(char*** &horario, char*** &cursos, char* codigo, int n){
    ifstream archivoHorarios("C:\\Users\\computador\\Desktop\\Horarios_registrados.txt");
    if (archivoHorarios.is_open()){
        char* linea1 = new char[256];
        while(archivoHorarios.getline(linea1, 256)){
            int cont = 0;
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
        int cont = 8;
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
    cout << "Ingrese el horario que desea escribiendo en el siguiente formato, 1ro la inicial del dia, luego las horas. Si el horario tiene varios dias escriba siguiendo el formato que se le pedira." << endl << endl;
    if(cursos[n-1][2][0] == '2'){
        char dia;
        int hora1;
        int hora2;
        cout << "Ingrese la inicial del dia en mayuscula: ";
        cin >> dia;
        if(dia == 'L' || dia == 'l') dia = '0';
        if(dia == 'M' || dia == 'm') dia = '1';
        if(dia == 'W' || dia == 'w') dia = '2';
        if(dia == 'J' || dia == 'j') dia = '3';
        if(dia == 'V' || dia == 'v') dia = '4';
        if(dia == 'S' || dia == 's') dia = '5';
        cout << endl << "Ingrese la 1ra hora del dia en formato de 24 hrs: ";
        cin >> hora1;
        cout << endl << "Ingrese la 2ra hora del dia: ";
        cin >> hora2;
        horario[dia-48][hora1] = cursos[n-1][1];
        horario[dia-48][hora2] = cursos[n-1][1];
    }
    if(cursos[n-1][2][0] == '4'){
        char dia1;
        char dia2;
        int hora1;
        int hora2;
        cout << "Ingrese la inicial del 1er dia en mayuscula: ";
        cin >> dia1;
        if(dia1 == 'L' || dia1 == 'l') dia1 = '0';
        if(dia1 == 'M' || dia1 == 'm') dia1 = '1';
        if(dia1 == 'W' || dia1 == 'w') dia1 = '2';
        if(dia1 == 'J' || dia1 == 'j') dia1 = '3';
        if(dia1 == 'V' || dia1 == 'v') dia1 = '4';
        if(dia1 == 'S' || dia1 == 's') dia1 = '5';
        cout << endl << "Ingrese la inicial del 2do dia en mayuscula: ";
        cin >> dia2;
        if(dia2 == 'L' || dia2 == 'l') dia2 = '0';
        if(dia2 == 'M' || dia2 == 'm') dia2 = '1';
        if(dia2 == 'W' || dia2 == 'w') dia2 = '2';
        if(dia2 == 'J' || dia2 == 'j') dia2 = '3';
        if(dia2 == 'V' || dia2 == 'v') dia2 = '4';
        if(dia2 == 'S' || dia2 == 's') dia2 = '5';
        cout << endl << "Ingrese la 1ra hora del dia en formato de 24 hrs: ";
        cin >> hora1;
        cout << endl << "Ingrese la 2ra hora del dia: ";
        cin >> hora2;
        cout << endl << endl;
        horario[dia1-48][hora1] = cursos[n-1][1];
        horario[dia1-48][hora2] = cursos[n-1][1];
        horario[dia2-48][hora1] = cursos[n-1][1];
        horario[dia2-48][hora2] = cursos[n-1][1];
    }
    if(cursos[n-1][2][0] == '7'){
        char dia1;
        char dia2;
        char dia3;
        int hora1;
        int hora2;
        int hora3;
        int hora4;
        int hora5;
        cout << "Ingrese la inicial del 1er dia en mayuscula: ";
        cin >> dia1;
        if(dia1 == 'L' || dia1 == 'l') dia1 = '0';
        if(dia1 == 'M' || dia1 == 'm') dia1 = '1';
        if(dia1 == 'W' || dia1 == 'w') dia1 = '2';
        if(dia1 == 'J' || dia1 == 'j') dia1 = '3';
        if(dia1 == 'V' || dia1 == 'v') dia1 = '4';
        if(dia1 == 'S' || dia1 == 's') dia1 = '5';
        cout << endl << "Ingrese la inicial del 2do dia en mayuscula: ";
        cin >> dia2;
        if(dia2 == 'L' || dia2 == 'l') dia2 = '0';
        if(dia2 == 'M' || dia2 == 'm') dia2 = '1';
        if(dia2 == 'W' || dia2 == 'w') dia2 = '2';
        if(dia2 == 'J' || dia2 == 'j') dia2 = '3';
        if(dia2 == 'V' || dia2 == 'v') dia2 = '4';
        if(dia2 == 'S' || dia2 == 's') dia2 = '5';
        cout << endl << "Ingrese la 1ra hora del dia en formato de 24 hrs: ";
        cin >> hora1;
        cout << endl << "Ingrese la 2ra hora del dia: ";
        cin >> hora2;
        cout << endl << "Ingrese la inicial del 3er dia en mayuscula: ";
        cin >> dia3;
        if(dia3 == 'L' || dia3 == 'l') dia3 = '0';
        if(dia3 == 'M' || dia3 == 'm') dia3 = '1';
        if(dia3 == 'W' || dia3 == 'w') dia3 = '2';
        if(dia3 == 'J' || dia3 == 'j') dia3 = '3';
        if(dia3 == 'V' || dia3 == 'v') dia3 = '4';
        if(dia3 == 'S' || dia3 == 's') dia3 = '5';
        cout << endl << "Ingrese la 1ra hora del 3er dia en formato de 24 hrs: ";
        cin >> hora3;
        cout << endl << "Ingrese la 2ra hora del 3er dia: ";
        cin >> hora4;
        cout << endl << "Ingrese la 3ra hora del 3er dia: ";
        cin >> hora5;
        cout << endl << endl;
        horario[dia1-48][hora1] = cursos[n-1][1];
        horario[dia1-48][hora2] = cursos[n-1][1];
        horario[dia2-48][hora1] = cursos[n-1][1];
        horario[dia2-48][hora2] = cursos[n-1][1];
        horario[dia3-48][hora3] = cursos[n-1][1];
        horario[dia3-48][hora4] = cursos[n-1][1];
        horario[dia3-48][hora5] = cursos[n-1][1];
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

void verHorario(char*** horario) {
    const int longitud_horario = 10;
    cout << "El horario es el siguiente:" << endl << endl;
    cout << "\tLunes\t\tMartes\t\tMiercoles\tJueves\t\tViernes\t\tSabado\t\tDomingo\t" << endl << endl;
    for(int hora = 0; hora < 24; ++hora){
        cout << hora << ":00\t";
        for(int dia = 0; dia < 7; ++dia){
            char* horario_actual = horario[dia][hora];
            int longitud_actual = 0;
            for(int i = 0; i < 30 && horario_actual[i] != '\0'; ++i){
                ++longitud_actual;
            }
            cout << horario_actual;
            for(int i = 0; i < longitud_horario - longitud_actual; ++i){
                cout << ' ';
            }
            cout << '\t';
        }
        cout << endl;
    }
    cout << endl;
}

void aumentarMatriz(char*** &cursos, int* &pAn){
    // Crear un puntero temporal para almacenar los datos originales
        char*** ptrTemporal = new char**[*pAn];

        // Copiar los datos del puntero triple original al temporal
        for(int i = 0; i < *pAn; i++){
            ptrTemporal[i] = new char*[5];
            for(int j = 0; j < 5; j++){
                ptrTemporal[i][j] = new char[30];
                for(int k = 0; k < 30; k++){
                    ptrTemporal[i][j][k] = cursos[i][j][k];
                }
            }
        }

        // Liberar la memoria del puntero triple original
        for(int i = 0; i < *pAn; i++){
            for(int j = 0; j < 5; j++){
                delete[] cursos[i][j];
            }
            delete[] cursos[i];
        }
        delete[] cursos;

        // Aumentar n
        *pAn += 1;
        // Crear un nuevo puntero triple con el tamaño actualizado
        cursos = new char**[*pAn];
        for(int i = 0; i < *pAn; i++){
            cursos[i] = new char*[5];
            for(int j = 0; j < 5; j++){
                cursos[i][j] = new char[30];
            }
        }
        // Copiar los datos del puntero temporal al nuevo puntero triple
        for(int i = 0; i < *pAn - 1; i++){;
            for(int j = 0; j < 5; j++){
                for(int k = 0; k < 30; k++){
                    cursos[i][j][k] = ptrTemporal[i][j][k];
                }
            }
        }

        //Liberar la memoria del puntero temporal
        for (int i = 0; i < *pAn - 1; i++){
            for(int j = 0; j < 5; j++){
                delete[] ptrTemporal[i][j];
            }
            delete[] ptrTemporal[i];
        }
        delete[] ptrTemporal;
}
