#include <iostream>
#include <fstream>

using namespace std;

void RegistrarMateria(char* direccion_archivo);

int main()
{
    RegistrarMateria("C:\\Users\\computador\\Desktop\\Materias_registradas.txt");
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
