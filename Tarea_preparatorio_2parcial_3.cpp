#include <iostream>
#include <fstream>
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
    float promedio;
    string resultado;
};

void mostrarEstudiante(Estudiante& estudiante) {
    cout << "ID: " << estudiante.id << endl;
    cout << "Nombres: " << estudiante.nombres << endl;
    cout << "Apellidos: " << estudiante.apellidos << endl;
    cout << "Nota 1: " << estudiante.nota1 << endl;
    cout << "Nota 2: " << estudiante.nota2 << endl;
    cout << "Nota 3: " << estudiante.nota3 << endl;
    cout << "Nota 4: " << estudiante.nota4 << endl;
    cout << "Promedio: " << estudiante.promedio << endl;
    cout << "Resultado: " << estudiante.resultado << endl;
    cout << endl;
}

void crearEstudiante() {
    Estudiante estudiante;

    cout << "ID: ";
    cin >> estudiante.id;
    cout << "Nombres: ";
    cin.ignore();
    getline(cin, estudiante.nombres);
    cout << "Apellidos: ";
    getline(cin, estudiante.apellidos);
    cout << "Nota 1: ";
    cin >> estudiante.nota1;
    cout << "Nota 2: ";
    cin >> estudiante.nota2;
    cout << "Nota 3: ";
    cin >> estudiante.nota3;
    cout << "Nota 4: ";
    cin >> estudiante.nota4;

    estudiante.promedio = (estudiante.nota1 + estudiante.nota2 + estudiante.nota3 + estudiante.nota4) / 4;
    estudiante.resultado = (estudiante.promedio >= 60) ? "Aprobado" : "Reprobado";

    ofstream archivo("notas.dat", ios::binary | ios::app);
    archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
    archivo.close();
}

void leerEstudiantes() {
    ifstream archivo("notas.dat", ios::binary);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    while (archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        mostrarEstudiante(estudiante);
    }

    archivo.close();
}

void actualizarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a actualizar: ";
    cin >> id;

    fstream archivo("notas.dat", ios::binary | ios::in | ios::out);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;
    while (!encontrado && archivo.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id == id) {
            mostrarEstudiante(estudiante);

            cout << "Ingrese las nuevas notas:" << endl;
            cout << "Nota 1: ";
            cin >> estudiante.nota1;
            cout << "Nota 2: ";
            cin >> estudiante.nota2;
            cout << "Nota 3: ";
            cin >> estudiante.nota3;
            cout << "Nota 4: ";
            cin >> estudiante.nota4;

            estudiante.promedio = (estudiante.nota1 + estudiante.nota2 + estudiante.nota3 + estudiante.nota4) / 4;
            estudiante.resultado = (estudiante.promedio >= 60) ? "Aprobado" : "Reprobado";

            archivo.seekp(-sizeof(Estudiante), ios::cur);
            archivo.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));

            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un estudiante con ese ID." << endl;
    }

    archivo.close();
}

void eliminarEstudiante() {
    int id;
    cout << "Ingrese el ID del estudiante a eliminar: ";
    cin >> id;

    ifstream archivoEntrada("notas.dat", ios::binary);
    if (!archivoEntrada) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    ofstream archivoSalida("temp.dat", ios::binary);
    if (!archivoSalida) {
        cerr << "No se pudo abrir el archivo temporal." << endl;
        return;
    }

    Estudiante estudiante;
    bool encontrado = false;
    while (archivoEntrada.read(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante))) {
        if (estudiante.id != id) {
            archivoSalida.write(reinterpret_cast<char*>(&estudiante), sizeof(Estudiante));
        } else {
            encontrado = true;
        }
    }

    archivoEntrada.close();
    archivoSalida.close();

    if (encontrado) {
        remove("notas.dat");
        rename("temp.dat", "notas.dat");
        cout << "Estudiante eliminado correctamente." << endl;
    } else {
        remove("temp.dat");
        cout << "No se encontró un estudiante con ese ID." << endl;
    }
}

int main() {
    char opcion;
    do {
        cout << "Menu:" << endl;
        cout << "1. Crear estudiante" << endl;
        cout << "2. Leer estudiantes" << endl;
        cout << "3. Actualizar estudiante" << endl;
        cout << "4. Eliminar estudiante" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case '1':
                crearEstudiante();
                break;
            case '2':
                leerEstudiantes();
                break;
            case '3':
                actualizarEstudiante();
                break;
            case '4':
                eliminarEstudiante();
                break;
            case '5':
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
        }

    } while (opcion != '5');

    return 0;
}

