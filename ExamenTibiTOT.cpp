#include <iostream>
#include<string>
#include<fstream>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Student 
{
    const int id;
    static int anUniv;
    char* materii;
    string nume;
    int varsta;
    double note;
public:
    //constructor fara parametrii
    Student() :id(0) 
    {
        anUniv++;
        this->materii = new char[strlen("NA") + 1];
        strcpy_s(this->materii, strlen("NA") + 1, "NA");
        this->nume = "";
        this->varsta = 18;
        this->note = 0;
    }
    //constructor cu parametrii
    Student( const char* materii, string nume, int varsta, double note) :id(id) 
    {
        anUniv++;
        this->materii = new char[strlen(materii) + 1];
        strcpy_s(this->materii, strlen(materii) + 1, materii);
        this->nume = nume;
        this->varsta = varsta;
        this->note = note;
    }
    //constructor de copiere
    Student(const Student& sursa):id(sursa.id) 
    {
        anUniv++;
        this->materii = new char[strlen(sursa.materii) + 1];
        strcpy_s(this->materii, strlen(sursa.materii) + 1, sursa.materii);
        this->nume = sursa.nume;
        this->varsta = sursa.varsta;
        this->note = sursa.note;
    }
    //operator =
    Student& operator=(const Student& sursa) {
        if (this != &sursa) {

            delete[]this->materii;
            this->materii = new char[strlen(sursa.materii) + 1];
            strcpy_s(this->materii, strlen(sursa.materii) + 1, sursa.materii);

            this->nume = sursa.nume;
            this->varsta = sursa.varsta;
            this->note = sursa.note;
            return *this;
        }
    }
    //destructor //dezaloca memoria atributului dinamic
    ~Student() {
        if (this->materii != nullptr) {
            delete[]this->materii;
        }
    }
    // pt const nu am setteri , in rest pt toti am setteri si getteri
    // pt static nu am valabil (this->)
    //getteri
    int getID()const {
        return this->id;
    }
   static int getAnUniv() {
        return anUniv;
    }
    char* getMaterii() {
        return this->materii;
    }
    string getNume() {
        return this->nume;
    }
    int getVarsta() {
        return this->varsta;
    }
    double getNote() {
        return this->note;
    }
    //setteri
    static void setAnUniv(int AnUniv) {
        anUniv = AnUniv;
    }
    void setMaterii(char* materii) {
        this->materii = materii;
    }
    void setNume(string nume) {
        this->nume = nume;
    }
    void setVarsta(int varsta) {
        this->varsta = varsta;
    }
    void setNote(double note) {
        this->note = note;
    }
   
    friend ostream& operator<<(ostream& out, Student& sursa);
    friend istream& operator>>(istream& in, Student& sursa);
    //operator +, care e la fel cu - , * , / ;
    Student operator+(double pctOficiul) {
        Student student;
        student.note = this->note + pctOficiul;
        return student;
    }
    //Student operator+(const Student& sursa) {
    //    Student student;
    //    student.varsta = this->varsta + sursa.varsta;
    //    return student;
    //}

     // Operator de pre-incrementare (++prefix)
    Student& operator++() {
        ++this->varsta;
        this->note += 1.0;
        return *this;
    }
    // Operator de post-incrementare (postfix++)
    Student operator++(int) {
        Student testStud;
        ++(*this);
        return testStud;
    }
    //operator +=
    Student& operator+=(double bonus) {
        this->note += bonus;
        return *this;
    }
    //Student& operator+=(const Student& sursa) {
    //    // Adăugăm notele
    //    this->note += sursa.note;
    //    return *this;
    //}

    //operator [] indexare
    const char& operator[](int index) const {
        if (index < 0 || index >= strlen(this->materii)) {
            throw out_of_range("Index-ul este in afara limitelor! ");
        }
        return this->materii[index];
    }

    //Operator () pentru actualizarea atributelor
    void operator()(string numeNou, int varstaNoua, double noteNoi) {
        this->nume = numeNou;
        this->varsta = varstaNoua;
        this->note = noteNoi;
    }
    //operator la cast ,   Conversie către int (ID-ul studentului)
    operator int() const {
        return this->id;
    }
    // operator la cast  ,Conversie către char* (Materii)
    operator char* () const {
        if (this->materii == nullptr) {
            return nullptr;
        }
        // Alocam memorie pentru o copie a sirului materii
        char* copie = new char[strlen(this->materii) + 1];
        strcpy_s(copie, strlen(this->materii) + 1, this->materii);
        return copie;
    }

    //serializare // scriere in fisier
    void Serializare(const string& fileName)const {
        ofstream outFile(fileName, ios::app);
        if (!outFile) {
            cerr << "Eroare la deschiderea fisierului" << endl; 
            return;
        }
        outFile << this->id << endl;
       // outFile << this->anUniv<< endl;
        outFile << (this->materii ? this->materii:"NA") << endl;
        outFile << this->nume << endl;
        outFile << this->varsta << endl;
        outFile << this->note << endl;
        outFile.close();
    }

    //deserializare // citire din fisier
    void DeSerealizare(const string& fileName) {
        ifstream inFile(fileName);
        if (!inFile) {
            cerr << "Eroare la deschiderea fisierului" << endl;
            return;
        }

        string linie;

        // Citirea numelui
        if (!getline(inFile, linie) || linie.empty()) {
            cerr << "Eroare: Numele lipseste sau este invalid" << endl;
            return;
        }
        this->nume = linie;

        // Citirea varstei
        if (!getline(inFile, linie) || linie.empty()) {
            cerr << "Eroare: Varsta lipseste sau este invalida" << endl;
            return;
        }
        try {
            this->varsta = stoi(linie);
        }
        catch (const invalid_argument& e) {
            cerr << "Eroare: Varsta nu este un numar valid" << endl;
            return;
        }

        // Citirea notelor
        if (!getline(inFile, linie) || linie.empty()) {
            cerr << "Eroare: Notele lipsesc sau sunt invalide" << endl;
            return;
        }
        try {
            this->note = stod(linie);
        }
        catch (const invalid_argument& e) {
            cerr << "Eroare: Nota nu este un numar valid" << endl;
            return;
        }

        // Citirea materiilor
        if (!getline(inFile, linie)) {
            cerr << "Eroare: Materiile lipsesc sau sunt invalide" << endl;
            return;
        }
        delete[] this->materii;
        this->materii = new char[linie.length() + 1];
        strcpy_s(this->materii, linie.length() + 1, linie.c_str());

        inFile.close();
    }

};



//operator de afisare <<
ostream& operator<<(ostream& out, Student& sursa) {
    out << sursa.id;
    out << sursa.anUniv;
    if (sursa.materii != nullptr) {
        out << sursa.materii;
    }
    out << sursa.nume;
    out << sursa.varsta;
    out << sursa.note;
    return out;
}
//operator de scriere >>
istream& operator>>(istream& in, Student& sursa) {
    in >> sursa.anUniv;
    if (sursa.materii != nullptr) {
        in >> sursa.materii;
    }
    in >> sursa.nume;
    in >> sursa.varsta;
    in >> sursa.note;
    return in;
}

int Student::anUniv = 1;

int main() {
    // Test constructor implicit
    Student s1;
    cout << "Student implicit:" << endl;
    cout << s1 << endl;


    //Test constructor cu parametrii
    Student s2("Matematica, Fizica", "Ion Popescu", 21, 9.5);
    cout << "Student cu parametri:" << endl;
    cout << s2 << endl;


    // Test constructor de copiere
    Student s3(s2);
    cout << "Student copiat:" << endl;
    cout << s3 << endl;

    // Test operator =
    Student s4;
    s4 = s2;
    cout << "Student atribuit:" << endl;
    cout << s4 << endl;

    // Test operator <<
    cout << "Afișare student folosind operatorul <<:" << endl;
    cout << s4 << endl;

    // Test operator +
    Student s5 = s4 + 1.0;
    cout << "Student cu puncte bonus:" << endl;
    cout << s5 << endl;

    // Test operator pre-incrementare
    ++s4;
    cout << "După pre-incrementare:" << endl;
    cout << s4 << endl;

    // Test operator post-incrementare
    s4++;
    cout << "După post-incrementare:" << endl;
    cout << s4 << endl;

    // Test operator +=
    s4 += 2.5;
    cout << "După operator +=:" << endl;
    cout << s4 << endl;

    // Test operator []
    try {
        cout << "Al 2-lea caracter din materii: " << s4[1] << endl;
    }
    catch (const out_of_range& e) {
        cerr << e.what() << endl;
    }

    // Test operator ()
    s4("Maria Ionescu", 22, 10.0);
    cout << "După operator ():" << endl;
    cout << s4 << endl;

    // Test operator cast
    int id = static_cast<int>(s4);
    char* materii = static_cast<char*>(s4);
    cout << "Conversie la int (ID): " << id << endl;
    cout << "Conversie la char* (Materii): " << materii << endl;
    delete[] materii; // Eliberăm memoria pentru char*

    // Test serializare
    cout << "Serializare student:" << endl;
    s4.Serializare("studenti.txt");
    cout << "Student serializat in fisierul studenti.txt" << endl;
    cout << "----------------------------" << endl;
    cout << "Serializare student:" << endl;
    s5.Serializare("studenti.txt");
    cout << "Student serializat in fisierul studenti.txt" << endl;

    // Test deserializare
    Student s6;
    s6.DeSerealizare("studenti.txt");
    cout << "Student deserializat din fisier:" << endl;
    cout << s6 << endl;

    return 0;
}


