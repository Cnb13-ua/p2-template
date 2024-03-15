// Programación 2 - Práctica 1
// DNI:50385214B
// Nombre: Christian Nacher Bravo
#include <iostream>
#include <vector>

using namespace std;

const int MAXSUBJECT = 50;


// Registro para las fechas
struct Date {
    int day;
    int month;
    int year;
};

// Registro para las frases épicas
struct Phrase {
    string text;
    Date date;
    int rating;
};

// Registro para los profesores
struct Teacher {
    string name;
    string nickname;
    char subject[MAXSUBJECT];
    int rating;
    vector<Phrase> listPhrases;
};

// Registro para los cursos
struct AcademicYear {
    int id;
    vector<Teacher> listTeachers;
};

// Tipos de error posibles
enum Error {
    ERR_OPTION,
    ERR_EMPTY,
    ERR_DUPLICATED,
    ERR_NOT_EXIST,
    ERR_RATING
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
        case ERR_DUPLICATED:
            cout << "ERROR: duplicated value" << endl;
            break;
        case ERR_NOT_EXIST:
            cout << "ERROR: value does not exist" << endl;
            break;
        case ERR_RATING:
            cout << "ERROR: number out of range" << endl;
    }
}

/* Función que muestra el menú de opciones
return: nada
*/
void showMenu() {
    cout << "1- Add academic year" << endl
         << "2- Delete academic year" << endl
         << "3- Add teacher" << endl
         << "4- Delete teacher" << endl
         << "5- Show teacher" << endl
         << "6- Add phrase" << endl
         << "7- Summary" << endl
         << "q- Quit" << endl
         << "Option: ";
}














void addAcademicYear(vector <AcademicYear> &listYears){
    string year;
    int newYear;
    bool duplicated = true;

    //Comprobamos si el valor que va a introducir el usuario es duplicado
    while(duplicated){
        duplicated = false;

        cout <<  "Enter academic year: " << endl;
        getline(cin,year);

        //A su vez comprobamos si es una cadena vacía
        if(year == ""){
            error(ERR_EMPTY);
            return;
        }

        //Convertimos el dato introducido a entero
        newYear = stoi(year);
        

        for(unsigned int i = 0;i < listYears.size();i++){


            if(newYear == listYears[i].id){
                error(ERR_DUPLICATED);
                duplicated = true;
            }
        }
    }

   
    //Creamos un nuevo struct que poner en el vector
    AcademicYear newStruct;
    newStruct.id = newYear;

   
    //Metemos el struct al vector
    listYears.push_back(newStruct);
cout<<"Year added succesfully. ";
    return;
}






























void deleteAcademicYear(vector<AcademicYear> &listYears) {
    int newYear;
    bool duplicated = false;
    int position = 0;
    string year;
   
    
    while(!duplicated){
	

    cout << "Enter the year: ";
    getline(cin, year);

    if (year == "") {
        error(ERR_EMPTY);
        return;
    }

 newYear = stoi(year);
    

    for ( int i = 0; i < listYears.size(); ++i) {
        if(newYear == listYears[i].id){
        	duplicated = true;
        	position = i;
		}
    }

    if (!duplicated) {
        error(ERR_NOT_EXIST);
        
    }
}

    // Borrar el año academico en la posición encontrada.
    listYears.erase(listYears.begin() + (position - 1));
    cout << "Year deleted successfully." << endl;
}















void addTeacher(vector<AcademicYear> &listYears, vector<Teacher> &listTeachers){
    int newYear;
    bool duplicated = false;
    string year;
    
    cout << "Enter the year: ";
    getline(cin, year);
    
    if(year == ""){
        error(ERR_EMPTY);
        return;
    }
    
    newYear = stoi(year);

    // Verificar si el año académico ya existe
    for(unsigned int i = 0; i < listYears.size(); i++) {
        if(newYear == listYears[i].id) {
            duplicated = true;
            break;  // Salir del bucle si el año ya existe
        }
    }

    if (!duplicated) {
        error(ERR_NOT_EXIST);
        return;
    }
    
    cout << "Year exists." << endl;

    string name;
    cout << "Enter teacher's name: ";
    getline(cin, name);

    if (name == "") {
        error(ERR_EMPTY);
        return;
    }

    // Verificar si el nombre del profesor ya existe
    for(unsigned int i = 0; i < listTeachers.size(); i++) {
        if(name == listTeachers[i].name) {
            error(ERR_DUPLICATED);
            return;
        }
    }

    // Crear y agregar el nuevo profesor
    Teacher newTeacher;
    newTeacher.name = name;
    cout<<"Teacher added succesfully. ";
   
    
    string mote;
    cout<<"Enter nickname: ";
    getline (cin,mote);
    newTeacher.nickname=mote;
    cout<<"Nickanme added succesfully. ";
    
    
    
    
   
   
   string aux;
   char subject[MAXSUBJECT] ;
   string subj;
   int contador;
   cout<<"Enter subject: ";
   getline(cin, aux);
   if (aux == "") {
        error(ERR_EMPTY);
        return;
    }
   for(int i=0;i<=aux.size();i++){
       if(i<MAXSUBJECT-1){
           subject[i]=aux[i];
           contador++;
      
       }else{break;}
   }
   if(contador<MAXSUBJECT){
    subject[contador]='\0';
    }
    for(int j=0;j<MAXSUBJECT;j++){
        newTeacher.subject[j]=subject[j];
    }
   
    cout<<"Subject added sucesfully. ";
    
    
    
    
    
    int rate;
    string rate_aux;
    cout<<"Enter rating. ";
    getline(cin,rate_aux);
    if(rate_aux==""){
        rate_aux='0';
        rate=stoi(rate_aux);
    }
    else if(rate= stoi(rate_aux), rate<1 or rate >5){
        error(ERR_RATING);
        return;
    }
    newTeacher.rating=rate;
    cout<<"Rating added succesfully. ";
    
    
    
     listTeachers.push_back(newTeacher);
    cout << "Teacher added successfully." << endl;
    
    
    
    
}

    
    
    
    
    
    
void deleteTeacher (vector<Teacher> &listTeachers){
    string name;
    bool duplicated = false;
    int position=0;
    
    while(!duplicated){
        cout << "Enter the teacher´s name: ";
    getline(cin, name);
    
    if (name == "") {
        error(ERR_EMPTY);
        return;
    }
    // Verificar si el nombre del profesor ya existe
   for ( int i = 0; i < listTeachers.size(); ++i) {
        if(name == listTeachers[i].name){
        	duplicated = true;
        	position = i;
		}
    }
    
    if (!duplicated) {
        error(ERR_NOT_EXIST);
        return;
    }
    
    
    
}

// Borrar el profesor en la posición encontrada.
    listTeachers.erase(listTeachers.begin() + position);
    cout << "Teacher deleted successfully." << endl;
    
}






void showTeacher (vector<AcademicYear> &listYears, vector<Teacher> &listTeachers){
    int newYear;
    
   
    
    
    
    
    
    
    
    
    string name;
    bool duplicated = false;
    cout << "Enter teacher's name: ";
    getline(cin, name);

    if (name == "") {
        error(ERR_EMPTY);
        return;
    }
    
    
    
        // Verificar si el año académico ya existe
    for(unsigned int i = 0; i < listTeachers.size(); i++) {
        if(name == listTeachers[i].name) {
            duplicated = true;
            break;  // Salir del bucle si el año ya existe
        }
    }

    if (!duplicated) {
        error(ERR_NOT_EXIST);
        return;
    }
    
    AcademicYear newStruct;
    newStruct.id = newYear;
    
     for (const auto &year : listYears) {
     for (const auto &teacher : listTeachers) {
        if (name == teacher.name) {
            duplicated = true;
            cout << "Academic year: " <<year.id<< endl;
            cout << "Name: " << teacher.name << endl;
            if (!teacher.nickname.empty())
                cout << "Nickname: " << teacher.nickname << endl;
                 if (teacher.subject[0] != '\0') // Comprobar si hay un subject definido
                cout << "Subject: " << teacher.subject << endl;
            if (teacher.rating > 0) {
                cout << "Rating: ";
                for (int i = 0; i < teacher.rating; ++i)
                    cout << "*";
                cout << endl;
            }
    
    
    
     // Mostrar frases épicas del profesor
            cout << "Epic Phrases:" << endl;
            int index = 1;
            for (const auto &phrase : teacher.listPhrases) {
                cout << "Phrase " <<index << ". ";
                if (phrase.date.year != 0 || phrase.date.month != 0 || phrase.date.day != 0)
                    cout << "(" << phrase.date.year << "-" << phrase.date.month << "-" << phrase.date.day << ") ";
                if (phrase.rating != 0)
                    cout << "[" << phrase.rating << "] ";
                cout << ": " << phrase.text << endl;
                ++index;
            }
    
    
}

     }
}
}










void addPhrase(vector<AcademicYear> &listYears, vector<Teacher> &listTeachers) {
    int dia;
    int mes;
    int ano;
    string fecha;
    char dia_aux[4];
    char mes_aux[4];
    char ano_aux[6];
    string name;
    int rate;
    string rate_aux;
    cout << "Enter teacher's name: ";
    getline(cin, name);

    if (name == "") {
        error(ERR_EMPTY);
        return;
    }

    bool teacherFound = false;
    for (auto &teacher : listTeachers) {
        if (name == teacher.name) {
            teacherFound = true;

            Phrase newPhrase;

            cout << "Enter the phrase: ";
            getline(cin, newPhrase.text);

            if (newPhrase.text.empty()) {
                error(ERR_EMPTY);
                return;
            }

            
            
            
            
            
            cout << "Enter date (year-month-day): ";
    getline(cin,fecha);
    int pos_str=0;
    int contador=0;
    if(fecha==""){
        dia=0;
        mes=0;
        ano=0;
    }
    else{
    for(int i=0;i<fecha.size();i++){
        if(fecha[i]!='-'){
            ano_aux[pos_str]=fecha[i];
            pos_str++;
            contador++;
        }
        else{
            contador++;
            break;
        }
    }
    pos_str=0;
    for(int j=contador;j<fecha.size();j++){
        if(fecha[j]!='-'){
            mes_aux[pos_str]=fecha[j];
            pos_str++;
            contador++;
        }
        else{
            contador++;
            break;
        }
    }
    pos_str=0;
    for(int x=contador;x<fecha.size();x++){
        if(fecha[x]!='-'){
            dia_aux[pos_str]=fecha[x];
            pos_str++;
        }
        else{
            break;
        }
    }
    ano = (ano_aux[0] != '\0') ? atoi(ano_aux) : 0;
    mes = (mes_aux[0] != '\0') ? atoi(mes_aux) : 0;
    dia = (dia_aux[0] != '\0') ? atoi(dia_aux) : 0;
    }
    newPhrase.date.year=ano;
    newPhrase.date.month=mes;
    newPhrase.date.day=dia;

            
            
            
            
            
            
            

            cout << "Enter the rating: ";
            getline(cin, rate_aux);
            if (rate_aux == "") {
                rate_aux = '0'; // Asignar "0" como cadena en lugar de '0' como carácter
                rate = stoi(rate_aux);
            }
            
            else if (rate = stoi(rate_aux),rate < 1 || rate > 10) {
                error(ERR_RATING);
                return;
            }
            newPhrase.rating = rate;

            teacher.listPhrases.push_back(newPhrase);

            cout << "Phrase added successfully." << endl;

            break;
        }
    }

    if (!teacherFound) {
        error(ERR_NOT_EXIST);
    }
}
























int main(){
    char option;
    vector<AcademicYear>listYears;
    vector<Teacher>listTeachers;
     
    
    
    do{
        showMenu();
        cin >> option;
        cin.get(); // Para evitar que el salto de línea se quede en el buffer de teclado y luego pueda dar problemas si usas "getline"
        
        switch(option){
            case '1': // Llamar a la función "addAcademicYear" para crear un nuevo curso
            addAcademicYear(listYears);
                break;
            case '2': // Llamar a la función "deleteAcademicYear" para eliminar un curso
            deleteAcademicYear(listYears);
                break;
            case '3': // Llamar a la función "addTeacher" para crear un nuevo profesor
            addTeacher(listYears,listTeachers);
                break;
            case '4': // Llamar a la función "deleteTeacher" parar eliminar un profesor
            deleteTeacher(listTeachers);
                break;
            case '5': // Llamar a la función "showTeacher" para mostrar la información del profesor
            showTeacher(listYears,listTeachers);
                break;
            case '6': // Llamar a la función "addPhrase" para añadir una nueva frase
            addPhrase(listYears,listTeachers);
                break;
            case '7': // Llamar a la función "summary" para mostrar un resumen de las frases por curso
                break;
            case 'q': break;
            default: error(ERR_OPTION);
        }
    }while(option!='q');
}









