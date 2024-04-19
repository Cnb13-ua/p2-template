// Programación 2 - Práctica 2
// DNI:50385214B
// Nombre:Christian Nacher Bravo
//Christian Nacher Bravo
//DNI: 50385214B

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

const int KMAXNAME = 50;
const int KMAXPASSWORD = 5;

// Registro para las preguntas
struct Question {
    unsigned int id;
    unsigned int unit;
    string question;
    string answer;
};

// Registro para los profesores
struct Teacher {
    char name[KMAXNAME];
    char password[KMAXPASSWORD];
    unsigned int answered;
};

// Registro para la base de datos
struct Database {
    unsigned int nextId;
    vector<Question> questions;
    vector<Teacher> teachers;
};

// Tipos de errores posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_UNIT,
    ERR_CHAR,
    ERR_FILE,
    ERR_NAME,
    ERR_DUPLICATED,
    ERR_PASSWORD,
    ERR_NO_QUESTIONS,
    ERR_ID,
    ERR_ARGS
};

/* Función que muestra los mensajes de error
e: tipo de error a mostrar
return: nada
*/
void error(Error e) {
    switch (e) {
    case ERR_OPTION:
        cout << "ERROR: wrong option" << endl;
        break;
    case ERR_EMPTY:
        cout << "ERROR: empty string" << endl;
        break;
    case ERR_UNIT:
        cout << "ERROR: wrong unit" << endl;
        break;
    case ERR_CHAR:
        cout << "ERROR: wrong char" << endl;
        break;
    case ERR_FILE:
        cout << "ERROR: cannot open file" << endl;
        break;
    case ERR_NAME:
        cout << "ERROR: wrong teacher name" << endl;
        break;
    case ERR_DUPLICATED:
        cout << "ERROR: duplicated name" << endl;
        break;
    case ERR_PASSWORD:
        cout << "ERROR: wrong password" << endl;
        break;
    case ERR_NO_QUESTIONS:
        cout << "ERROR: no pending questions" << endl;
        break;
    case ERR_ID:
        cout << "ERROR: wrong id" << endl;
        break;
    case ERR_ARGS:
        cout << "ERROR: wrong arguments" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add question" << endl
         << "2- Batch add questions" << endl
         << "3- Delete question" << endl
         << "4- Add teacher" << endl
         << "5- Add answers" << endl
         << "6- View answers" << endl
         << "7- View statistics" << endl
         << "8- Export questions" << endl
         << "q- Quit" << endl
         << "Option: ";
}





int BuscarTeacher(const vector<Teacher>& listTeacher, const string& nombre) {
    for (unsigned int i = 0; i < listTeacher.size(); i++) {
        if (nombre == listTeacher[i].name) {
            return i;
        }
    }
    return -1;
}




string filtrarEspacios(string nombre){
    nombre.erase(remove_if(nombre.begin(), nombre.end(), ::isspace), nombre.end());//Gracias al tutorial de youtube por salvarme la vida, quita espacios del principio y del final
    return nombre;
}

int Contar_caracter(const string linea){
    int numero_veces=0;
    for(unsigned int i=0;i<linea.size();i++){
        if(linea[i]=='|'){
            numero_veces++;
        }
    }
    return numero_veces;
}

int countVerticalBars(const string& line) {
    return count(line.begin(), line.end(), '|');
}














void addQuestion(Database &data) {
    string unitStr;
    int unit;
    string text;
    bool unit_correct=true;
    do{
        unit_correct=true;
        // Pedir al usuario que introduzca el número de tema
        cout << "Enter unit: ";
        getline(cin, unitStr);

        // Verificar si se introdujo una cadena vacía
        if (unitStr.empty()) {
            error(ERR_EMPTY);
            return;
        }

        // Convertir la cadena a un entero
        try {
            unit = stoi(unitStr);
        } catch (invalid_argument&) {
            error(ERR_UNIT);
            unit_correct=false;

        }

        if (unit < 1 || unit > 5) {
            error(ERR_UNIT);
            unit_correct=false;

        }
    }while(unit_correct==false);
    do {
        // Pedir al usuario que introduzca el texto de la pregunta
        cout << "Enter question: ";
        getline(cin, text);

        // Verificar si se introdujo una cadena vacía
        if (text.empty()) {
            error(ERR_EMPTY);
            return;
        }

        // Verificar si el texto contiene el carácter de barra vertical
        if (text.find('|') != string::npos) {
            error(ERR_CHAR);
            continue;
        }

    } while (text.find('|') != string::npos); // Repetir el bucle si se encuentra el carácter '|'

    // Crear una nueva pregunta con un identificador único
    Question newQuestion;
    newQuestion.id = data.nextId++;
    newQuestion.unit = unit;
    newQuestion.question = text;

    // Agregar la nueva pregunta al vector de preguntas en la base de datos
    data.questions.push_back(newQuestion);


}





void batchAddQuestions(Database &data) {
    string nom_fichero;
    bool error_ocurred = false;
    bool error_file= false;
    do{
        error_file=false;
        error_ocurred = false;
        cout << "Enter filename: ";
        getline(cin, nom_fichero);

        if (nom_fichero.empty()) {
            error(ERR_EMPTY);
            return;
        }
        ifstream fichero(nom_fichero);
        if (!fichero.is_open()) {
            error(ERR_FILE);
            error_file = true;
        }
        if(error_file==false) {
            string linea;
            int num_linea = 0;
            int num_preguntas = 0;
            int num_pre_corr = 0;

            unordered_set<int> lineas_con_error;

            while (getline(fichero, linea)) {
                num_linea++;

                // Ignorar líneas vacías
                if (linea.empty()) continue;

                // Verificar si la línea contiene solo espacios en blanco
                bool is_blank_line = all_of(linea.begin(), linea.end(), [](char c) { return isspace(c); });
                if (is_blank_line) continue;

                num_preguntas++;

                // Verificar el número de barras verticales
                int num_vertical_bars = countVerticalBars(linea);
                if (num_vertical_bars > 2 && !lineas_con_error.count(num_linea)) {
                    cout << "Error line " << num_linea << endl;
                    lineas_con_error.insert(num_linea);
                    error_ocurred = true;
                    continue;
                }

                stringstream ss(linea);
                string unidad_str, pregunta, respuesta;

                getline(ss, unidad_str, '|');
                getline(ss, pregunta, '|');

                // Verificar si hay una respuesta después de la pregunta
                if (ss.peek() == '|') {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                getline(ss, respuesta, '|');

                // Verificar si el último carácter de la pregunta es "|"
                if (!pregunta.empty() && pregunta.back() == '|') {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                // Verificar si hay dos barras verticales y el último carácter es una barra vertical
                if (num_vertical_bars == 2 && linea.back() == '|') {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                // Verificar el número de campos
                if (unidad_str.empty() || pregunta.empty()) {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                // Verificar que el número de tema sea válido
                int unidad;
                try {
                    unidad = stoi(unidad_str);
                    if (unidad < 1 || unidad > 5) {
                        throw invalid_argument("Invalid unit");
                    }
                } catch (const invalid_argument &ia) {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                // Verificar que la respuesta no contenga barras verticales
                if (respuesta.find('|') != string::npos) {
                    cout << "Error line " << num_linea << endl;
                    error_ocurred = true;
                    continue;
                }

                Question newQuestion;
                newQuestion.id = data.nextId++;
                newQuestion.unit = unidad;
                newQuestion.question = pregunta;
                newQuestion.answer = respuesta;
                data.questions.push_back(newQuestion);
                num_pre_corr++;
            }

            fichero.close();

            if (error_ocurred) {
                cout << "Summary: " << num_pre_corr << "/" << num_preguntas << " questions added" << endl;
            }
        }
    }while(error_file==true);
}















void deleteQuestion(Database &data) {
    string idStr;
    int idToDelete;

    do {
        // Pedir al usuario que introduzca el identificador de la pregunta a eliminar
        cout << "Enter question id: ";
        getline(cin, idStr);

        // Verificar si se introdujo una cadena vacía
        if (idStr.empty()) {
            error(ERR_EMPTY);
            return;
        }

        // Convertir la cadena a un entero
        try {
            idToDelete = stoi(idStr);
        } catch (invalid_argument&) {
            error(ERR_ID);
            continue; // Volver a pedir el identificador
        }

        // Buscar la pregunta con el identificador proporcionado
        auto it = find_if(data.questions.begin(), data.questions.end(), [idToDelete](const Question& q) {
            return q.id == static_cast<unsigned int>(idToDelete);
        });

        // Verificar si se encontró la pregunta
        if (it != data.questions.end()) {
            // Eliminar la pregunta del vector
            data.questions.erase(it);
            return;
        } else {
            // Mostrar error si no se encontró la pregunta con el identificador proporcionado
            error(ERR_ID);
        }
    } while (true); // Repetir hasta que se proporcione un identificador válido
}


string encryptPassword(const string& password) {
    string encryptedPassword;
    for (char digit : password) {
        switch (digit) {
        case '0': encryptedPassword += 'T'; break;
        case '1': encryptedPassword += 'R'; break;
        case '2': encryptedPassword += 'W'; break;
        case '3': encryptedPassword += 'A'; break;
        case '4': encryptedPassword += 'G'; break;
        case '5': encryptedPassword += 'M'; break;
        case '6': encryptedPassword += 'Y'; break;
        case '7': encryptedPassword += 'F'; break;
        case '8': encryptedPassword += 'P'; break;
        case '9': encryptedPassword += 'D'; break;
        default:  encryptedPassword += digit; break; // Si no es un dígito, mantenerlo igual
        }
    }
    return encryptedPassword;
}

void addTeacher(Database &data) {
    Teacher newTeacher;
    string nombre_aux;
    string pasword_aux;
    bool nombre_correcto = true;
    bool valid_password=true;


    do{
        nombre_correcto=true;
        cout << "Enter teacher name: ";
        getline(cin,nombre_aux );


        if (nombre_aux == "") {
            error(ERR_EMPTY);
            return;
        }

        // Validar el nombre
        for(unsigned int i = 0; i < nombre_aux.size(); i++) {
            if (!isalpha(nombre_aux[i]) && nombre_aux[i] != ' ') {
                nombre_correcto = false;
                break;
            }
        }

        if (!nombre_correcto) {
            error(ERR_NAME);
            nombre_correcto=false;
            continue;
        }

        // Eliminar espacios en blanco al principio y al final del nombre
        nombre_aux = filtrarEspacios(nombre_aux);

        if (nombre_aux.length() < 3 || nombre_aux.length() >= KMAXNAME - 1) {
            error(ERR_NAME);
            nombre_correcto=false;
            continue;
        }


        int existe_aux;
        existe_aux=BuscarTeacher(data.teachers, nombre_aux);
        if(existe_aux!=-1){
            error(ERR_DUPLICATED);
            nombre_correcto=false;
            continue;

        }




        for (char c : nombre_aux) {
            if (!isalpha(c) && c != ' ') {
                error(ERR_NAME);
                nombre_correcto=false;
                continue;
            }
        }
    }while(nombre_correcto==false);


    do{

        valid_password=true;
        cout << "Enter password: ";
        getline(cin,pasword_aux);


        if (pasword_aux == "") {
            error(ERR_EMPTY);
            return;
        }

        // Validar la contraseña
        for(unsigned int i = 0; i < pasword_aux.size(); i++) {
            if (!isdigit(pasword_aux[i])) {
                valid_password = false;
                break;
            }
        }

        if (!valid_password || pasword_aux.size() != 4) {
            error(ERR_PASSWORD);
            valid_password=false;
            continue;
        }
    }while(valid_password==false);
    // Encriptar la contraseña
    string encryptedPassword = encryptPassword(pasword_aux);

    // Guardar la contraseña encriptada
    strcpy(newTeacher.password, encryptedPassword.c_str());

    // Copiar el nombre del profesor
    strncpy(newTeacher.name, nombre_aux.c_str(), KMAXNAME);

    // Inicializar el contador de preguntas respondidas
    newTeacher.answered = 0;

    // Guardar al final del vector de profesores en la base de datos
    data.teachers.push_back(newTeacher);



}




void addAnswer(Database &data) {
    string name;
    string password;
    int posicion_teacher;

    do {
        cout << "Enter teacher name: ";
        getline(cin, name);

        if (name.empty()) {
            error(ERR_EMPTY);
            return;
        }

        posicion_teacher = BuscarTeacher(data.teachers, name);

        if (posicion_teacher == -1) {
            error(ERR_NAME);
            continue;
        }

        break; // Salir del bucle si el nombre es válido
    } while (true);

    do {
        // Pedir la contraseña
        cout << "Enter password: ";
        getline(cin, password);

        if (password.empty()) {
            error(ERR_EMPTY);
            continue;
        }

        // Encriptar la contraseña ingresada por el usuario
        string encryptedPassword = encryptPassword(password);

        // Comparar la contraseña encriptada con la almacenada en la base de datos
        if (encryptedPassword != data.teachers[posicion_teacher].password) {
            error(ERR_PASSWORD);
            continue;
        }

        // Bucle para contestar preguntas
        while (true) {
            bool foundPendingQuestion = false;
            for (const auto& question : data.questions) {
                if (question.answer.empty()) {
                    foundPendingQuestion = true;
                    cout << question.id << ". (" << question.unit << ") " << question.question << endl;
                }
            }

            if (!foundPendingQuestion) {
                error(ERR_NO_QUESTIONS);
                return;
            }

            break; // Salir del bucle si hay preguntas pendientes
        }
        break; // Salir del bucle si la contraseña es válida
    } while (true);

    do {
        string idStr;
        cout << "Enter question id: ";
        getline(cin, idStr);

        if (idStr.empty()) {
            error(ERR_EMPTY);
            return;
        }

        if (idStr == "b") {
            return;
        }

        int idToAnswer;
        try {
            idToAnswer = stoi(idStr);
        } catch (invalid_argument&) {
            error(ERR_ID);
            continue;
        }

        auto questionToAnswer = find_if(data.questions.begin(), data.questions.end(), [&](const Question& q) {
            return q.id == static_cast<unsigned int>(idToAnswer);
        });

        if (questionToAnswer == data.questions.end() || !questionToAnswer->answer.empty()) {
            error(ERR_ID);
            continue;
        }

        // Bucle para responder la pregunta
        do {
            string answer;
            cout << "Enter answer: ";
            getline(cin, answer);

            // Verificar si la respuesta está vacía
            if (answer.empty()) {
                error(ERR_EMPTY);
                return;
            }

            // Verificar si la respuesta contiene el carácter '|'
            if (answer.find('|') != string::npos) {
                error(ERR_CHAR);
                continue;
            }

            questionToAnswer->answer = answer;
            data.teachers[posicion_teacher].answered++;

            break; // Salir del bucle si la respuesta es válida
        } while (true);

        break; // Salir del bucle si se ha seleccionado una pregunta válida
    } while (true);
}


void viewAnswers(Database& data) {

    for (const auto& question : data.questions) {
        if (!question.answer.empty()) {
            cout << question.id << ". (" << question.unit << ") " << question.question << ": " << question.answer << endl;
        }
    }

}



void viewStatistics(Database& data) {
    int preguntasTotales=data.questions.size();
    int preguntasRespondidas=0;
    for (const auto& question : data.questions) {
        if (!question.answer.empty()) {
            preguntasRespondidas++;
        }
    }
    cout<<"Total number of questions: "<<preguntasTotales<<endl;
    cout<<"Number of questions answered: "<<preguntasRespondidas<<endl;
    for(unsigned int i=0;i<data.teachers.size();i++){
        cout<<data.teachers[i].name<<": "<<data.teachers[i].answered<<endl;
    }

}
















void exportQuestions(Database& data){
    string file;
    ofstream fichero(file);
    bool file_correcto=false;
    while(file_correcto==false){
        file_correcto=true;
        cout<<"Enter filename: ";
        getline(cin,file);

        if(file==""){
            error(ERR_EMPTY);
            return;
        }




        fichero.open(file);
        if(fichero.is_open()){
            for(unsigned int i=0;i<data.questions.size();i++){
                if(data.questions[i].answer!=""){
                    fichero<<data.questions[i].unit<<"|"<<data.questions[i].question<<"|"<<data.questions[i].answer<<endl;

                }
                else{
                    fichero<<data.questions[i].unit<<"|"<<data.questions[i].question<<endl;

                }

            }

        }
        else{
            error(ERR_FILE);
            file_correcto=false;
            continue;
        }
        fichero.close();
    }

}




void guardarProfesoresEnArchivo(Database& data) {
    ofstream fichero("teachers.bin", ios::out | ios::binary);
    if (!fichero.is_open()) {
        error(ERR_FILE);
        return;
    }

    for (const Teacher& teacher : data.teachers) {
        // Escribir la longitud de los campos de cadena antes de los datos
        int nameLength = strlen(teacher.name);
        int passwordLength = strlen(teacher.password);

        fichero.write(reinterpret_cast<const char*>(&nameLength), sizeof(int));
        fichero.write(teacher.name, nameLength);
        fichero.write(reinterpret_cast<const char*>(&passwordLength), sizeof(int));
        fichero.write(teacher.password, passwordLength);

        // Escribir answered como entero directamente
        fichero.write(reinterpret_cast<const char*>(&teacher.answered), sizeof(int));
    }

    fichero.close();
}

void cargarProfesoresEnArchivo(Database& data) {
    Teacher teacher;
    ifstream fichero("teachers.bin", ios::binary);
    if (!fichero.is_open()) {
        error(ERR_FILE);
        return;
    }

    while (fichero.read(reinterpret_cast<char*>(&teacher), sizeof(Teacher))) {
        data.teachers.push_back(teacher);
    }

    fichero.close();
}





void Arguments(int argc, char *argv[], Database &data) {

    bool statsOption = false;
    string filename;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                filename = argv[i + 1];

                ++i;
            } else {
                error(ERR_ARGS);
                return;
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            statsOption = true;
        } else {
            error(ERR_ARGS);
            return;
        }
    }



    if (statsOption) {
        viewStatistics(data);
        exit(0); // Salir del programa después de mostrar las estadísticas
    }
}

















// Función principal
int main(int argc, char *argv[]) {
    Database data;
    data.nextId = 1;
    char option;
    Arguments(argc, argv, data);

    do {
        showMenu();
        cin >> option;
        cin.ignore(); // Limpiar el buffer de entrada después de leer la opción

        switch(option) {
        case '1':
            addQuestion(data);
            break;
        case '2':
            batchAddQuestions(data);
            break;
        case '3':
            deleteQuestion(data);
            break;
        case '4':
            addTeacher(data);
            break;
        case '5':
            addAnswer(data);
            break;
        case '6':
            viewAnswers(data);
            break;
        case '7':
            viewStatistics(data);
            break;
        case '8':
            exportQuestions(data);
            break;
        case 'q':
            guardarProfesoresEnArchivo(data);
            // Salir del programa guardando los profesores en fichero
            break;
        default:
            error(ERR_OPTION);
        }
    } while(option != 'q');

    return 0;
}


