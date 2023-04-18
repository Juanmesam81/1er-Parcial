#include <iostream>
#include <fstream>

using namespace std;

void RegistrarMateria(char* direccion_archivo);
void RegistrarHorario();

int main()
{
    //RegistrarMateria("C:\\Users\\computador\\Desktop\\Materias_registradas.txt");
    RegistrarHorario();
    return 0;
}

void RegistrarMateria(char* direccion_archivo){
    char** materia = new char* [5];
    for (int i = 0; i < 5; i++){
        materia[i] = new char [30];
    }
    cout << "Ingrese el codigo del curso: ";
    cin >> materia[0];
    cout << endl;
    cout << "Ingrese el nombre del curso: ";
    cin >> materia[1];
    cout << endl;
    cout << "Ingrese las horas de clase por semana del curso: ";
    cin >> materia[2][0];
    cout << endl;
    cout << "Ingrese el numero de creditos del curso: ";
    cin >> materia[4][0];
    cout << endl;
    int x = (((materia[4][0] - 48)*48)/16);
    int y = materia[2][0] - 48;
    int htps = x - y;
    char htp = htps + 48;
    materia[3][0] = htp;

    ofstream archivo_salida(direccion_archivo, ios::app);

        if (archivo_salida.is_open()) {
            for(int i = 0; i < 5; i++){
                if(i == 0 || i == 1){
                    archivo_salida << materia[i] << ' ';
                }
                else{
                    archivo_salida << materia[i][0] << ' ';
                }
            }
            archivo_salida << endl;
            archivo_salida.close();
        }
        else {
            cout << "Error al abrir el archivo." << endl;
        }
}

void RegistrarHorario(){
    char codigo[30];
    int NHorarios = 0;
    cout << "Ingrese el codigo de la materia: ";
    cin >> codigo;
    cout << endl << "Ingrese el # de horarios que tendra la materia: ";
    cin >> NHorarios;
    cout << endl;
    char** horario = new char* [NHorarios+2];
    for (int i = 0; i < NHorarios+2; i++){
        horario[i] = new char [30];
    }
    horario[0] = codigo;
    horario[1][0] = NHorarios + 48;
    for (int i = 2; i < NHorarios+2; i++){
        cout << "Ingrese el horario " << i-1 << ": ";
        cin >> horario[i];
    }

    ofstream archivo_salida("C:\\Users\\computador\\Desktop\\Horarios_registrados.txt", ios::app);

        if (archivo_salida.is_open()){
            for(int i = 0; i < NHorarios+2; i++){
                if(i == 1){
                    archivo_salida << horario[i][0] << endl;
                }
                else{
                    archivo_salida << horario[i] << endl;
                }
            }
            archivo_salida.close();
        }
        else {
            cout << "Error al abrir el archivo." << endl;
        }
}
