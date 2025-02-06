
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include<string>
using namespace std;


class Examen
{
    const int id;
    static int nr;
    char* materia;
    double note;
    string nume;
    float taxa;
public:
    Examen() :id(0) {
        nr++;
        this->materia = new char[strlen("NA") + 1];
        strcpy(this->materia, "NA");
        this->note = 0;
        this->nume = "";
        this->taxa = 0;
    }

    Examen(const char* materie, double note, string nume, float taxa) :id(nr++) {
        this->materia = new char[strlen(materie) + 1];
        strcpy(this->materia, materie);
        this->note = note;
        this->nume = nume;
        this->taxa = taxa;
    }

    Examen(const Examen& sursa) : id(nr++) {
        this->materia = new char[strlen(sursa.materia) + 1];
        strcpy(this->materia, sursa.materia);
        this->note = sursa.note;
        this->nume = sursa.nume;
        this->taxa = sursa.taxa;
    }

    ~Examen() {
        if (this->materia != nullptr) {
            delete[]this->materia;
        }
    }

    Examen& operator=(const Examen& sursa) {
        if (this != nullptr) {
            this->materia = new char[strlen(sursa.materia) + 1];
            strcpy(this->materia, sursa.materia);
        }
        this->note = sursa.note;
        this->nume = sursa.nume;
        this->taxa = sursa.taxa;
        return *this;
    }
#pragma region Set si Get
    int getId() const {
        return this->id;
    }
    static int getNr() {
        return nr;
    }
    char* getMaterie() {
        return this->materia;
    }
    double getNota() {
        return this->note;
    }
    string getNume() {
        return this->nume;
    }
    float getTaxa() {
        return this->taxa;
    }

    void setNr(int nr) {
        this->nr = nr;
    }
    void setMaterie(char* materie) {
        this->materia = materie;
    }
    void setNota(double nota)
    {
        this->note = nota;
    }
    void setNume(string nume) {
        this->nume = nume;
    }
    void setTaxa(float taxa) {
        this->taxa = taxa;
    }

#pragma endregion

    friend ostream& operator<<(ostream& out,  Examen& sursa);
    friend istream& operator>>(istream& in, Examen& sursa);
   
    Examen& operator+=(float taxaBonus) {
        Examen examen;
        examen.taxa += taxaBonus;
        return *this;
    }
    //pre-incrementare ++
    Examen& operator++() {
        ++this->taxa;
        return *this;
    }
    //post 
    Examen operator++(int) {
        Examen exam;
        ++(*this);
        return *this;
    }
    const char& operator[](int index)const {
        if (index < 0 || index >= strlen(this->materia)) {
            throw out_of_range("index in afara limitelor");
        }
        return this->materia[index];
    }
    void operator()(string numeNou, double noteNoi, float taxaNoua) {
        this->nume = numeNou;
        this->note = noteNoi;
        this->taxa = taxaNoua;
    }

    operator char* () const {
        if (this->materia == nullptr) {
            return  this->materia;
        }

        char* copie = new char[strlen(materia) + 1];
        strcpy(copie, materia);
        return copie;

    }
    bool operator<(const Examen& sursa) {
        if (this->materia != nullptr && sursa.materia != nullptr) {
            return strcmp(this->materia, sursa.materia);
        }
        return false;
    }

    void Seerializare(const string& fileName)const {
        ofstream outFile(fileName, ios::app);
        if (!outFile) {
            cerr << "probleme cu fisierul" << endl;
            return;
        }
        outFile << this->id << endl;
        outFile << (this->materia ? this->materia : "NA") << endl;
        outFile << this->nume << endl;
        outFile << this->note << endl;
        outFile << this->taxa << endl;
        outFile.close();
    }

};

class Colocviu : public Examen{
private:
    int data;
    string tipul;
public:
    Colocviu() {
        this->data = 0;
        this->tipul = "";
    }

    Colocviu(const char* materie, double note, string nume, float taxa, int data, string tipul) :Examen (materie,note,nume,taxa){
        this->data = data;
        this->tipul = tipul;
    }

    Colocviu& operator=(const Colocviu& sursa) {
        Examen::operator=(sursa);
        this->data = sursa.data;
        this->tipul = sursa.tipul;
        return *this;
    }

    friend ostream& operator<<(ostream& out, const Colocviu& sursa);

    //fara constr de copiere daca nu avem char* in Clasa is-a


    void TipExamen() {
        cout << "Examen tip colocviu" << endl;
    }
};


ostream& operator<<(ostream& out, Examen& sursa) {
    out << sursa.id;
    out << sursa.nr;
    if (sursa.materia != nullptr) {
        out << sursa.materia;
    }
    out << sursa.nume;
    out << sursa.note;
    out << sursa.taxa;
    return out;
}

istream& operator>>(istream& in, Examen& sursa) {
    in >> sursa.nr;
    if (sursa.materia != nullptr) {
        in >> sursa.materia;
    }
    in >> sursa.nume;
    in >> sursa.note;
    in >> sursa.taxa;
    return in;
}


ostream& operator<<(ostream& out, const Colocviu& sursa) {
    out << (Examen)sursa << endl;
    out << sursa.data << endl;
    out << sursa.tipul << endl;
    return out;
}

int Examen::nr = 1;


int main()
{
    Examen e1;
    Examen e2(" POO ",5," Tiberiu ",100);
    e1 = e2;

    e1 += 2;
    cout << e1 << endl;

    if (e1.getNota() < e2.getNota()) {
        cout << "Examenul e1 este mai mic decat examenul e2." << endl;
    }
    else {
        cout << "Examenul e1 nu este mai mic decat examenul e2." << endl;
    }

    e2 + 2;
    cout << e2 << endl;

    ofstream fout;
    fout.open("salvare.txt", ofstream::out);
    if (fout.is_open()) {
        fout << e2;
        fout.close();
    }

    Colocviu c1;
    Colocviu c2("DAM", 10, " Tiberiu ", 120, 10, " Scris");

    cout << c1 << endl;
    cout << c2 << endl;

    c2.Seerializare("Verificare.txt");
}


