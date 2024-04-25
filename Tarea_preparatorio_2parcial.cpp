#include <iostream>
#include <string>

using namespace std;

struct Estudiante {
    int id;
    string nombres;
    string apellidos;
    float nota1;
    float nota2;
    float nota3;
    float nota4;
};

int main() {
    int n;
    cout << "Ingrese la cantidad de estudiantes: ";
    cin >> n;

    Estudiante estudiantes[n];
    for (int i = 0; i < n; i++) {
        cout << "Estudiante " << i + 1 << endl;
        cout << "ID: ";
        cin >> estudiantes[i].id;
        cout << "Nombres: ";
        cin.ignore();
        getline(cin, estudiantes[i].nombres);
        cout << "Apellidos: ";
        getline(cin, estudiantes[i].apellidos);
        cout << "Nota 1: ";
        cin >> estudiantes[i].nota1;
        cout << "Nota 2: ";
        cin >> estudiantes[i].nota2;
        cout << "Nota 3: ";
        cin >> estudiantes[i].nota3;
        cout << "Nota 4: ";
        cin >> estudiantes[i].nota4;
    }

    for (int i = 0; i < n; i++) {
        float promedio = (estudiantes[i].nota1 + estudiantes[i].nota2 + estudiantes[i].nota3 + estudiantes[i].nota4) / 4;
        cout << "Estudiante " << i + 1 << endl;
        cout << "ID: " << estudiantes[i].id << endl;
        cout << "Nombres: " << estudiantes[i].nombres << endl;
        cout << "Apellidos: " << estudiantes[i].apellidos << endl;
        cout << "Promedio: " << promedio << endl;
        if (promedio >= 60) {
            cout << "Estado: Aprobado" << endl;
        } else {
            cout << "Estado: Reprobado" << endl;
        }
        cout << endl;
    }

    return 0;
}

