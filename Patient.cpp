//#include <iostream>
//#include <string>
//using namespace std;
//
//class Patient {
//    int id;
//    char* name;
//    string address;
//    int medicalInvestigationsCount;
//    string* medicalInvestigations;
//    int birthYear;
//    static int patientsCount;
//public:
//    Patient() : id(0), address("Unknown"), medicalInvestigationsCount(0), birthYear(0) {
//        this->name = nullptr;
//        this->medicalInvestigations = nullptr;
//        patientsCount++;
//    }
//
//    Patient(int _id, const char* _name, string _address, int _medicalInvestigationsCount, string* _medicalInvestigations, int _birthYear)
//        : id(_id), address(_address), medicalInvestigationsCount(_medicalInvestigationsCount), birthYear(_birthYear) {
//        this->name = new char[strlen(_name) + 1];
//        strcpy_s(this->name, strlen(_name) + 1, _name);
//
//        if (_medicalInvestigations != nullptr) {
//            this->medicalInvestigations = new string[_medicalInvestigationsCount];
//            for (int i = 0; i < _medicalInvestigationsCount; i++) {
//                this->medicalInvestigations[i] = _medicalInvestigations[i];
//            }
//        }
//        else {
//            this->medicalInvestigations = nullptr;
//        }
//
//        patientsCount++;
//    }
//
//    Patient(const Patient& p) : id(p.id), address(p.address), medicalInvestigationsCount(p.medicalInvestigationsCount), birthYear(p.birthYear) {
//        this->name = new char[strlen(p.name) + 1];
//        strcpy_s(this->name, strlen(p.name) + 1, p.name);
//
//        if (p.medicalInvestigations != nullptr) {
//            this->medicalInvestigations = new string[p.medicalInvestigationsCount];
//            for (int i = 0; i < p.medicalInvestigationsCount; i++) {
//                this->medicalInvestigations[i] = p.medicalInvestigations[i];
//            }
//        }
//        else {
//            this->medicalInvestigations = nullptr;
//        }
//
//        patientsCount++;
//    }
//
//    Patient& operator=(const Patient& p) {
//        if (this != &p) {
//            delete[] this->name;
//            delete[] this->medicalInvestigations;
//
//            this->id = p.id;
//            this->address = p.address;
//            this->medicalInvestigationsCount = p.medicalInvestigationsCount;
//            this->birthYear = p.birthYear;
//
//            this->name = new char[strlen(p.name) + 1];
//            strcpy_s(this->name, strlen(p.name) + 1, p.name);
//
//            if (p.medicalInvestigations != nullptr) {
//                this->medicalInvestigations = new string[p.medicalInvestigationsCount];
//                for (int i = 0; i < p.medicalInvestigationsCount; i++) {
//                    this->medicalInvestigations[i] = p.medicalInvestigations[i];
//                }
//            }
//            else {
//                this->medicalInvestigations = nullptr;
//            }
//        }
//        return *this;
//    }
//
//    ~Patient() {
//        if (this->medicalInvestigations != nullptr) {
//            delete[] medicalInvestigations;
//        }
//        if (this->name != nullptr) {
//            delete[] name;
//        }
//        patientsCount--;
//    }
//
//    //Getters
//    int getId() const {
//        return this->id;
//    }
//
//    const char* getName() const {
//        return this->name;
//    }
//
//    string getAddress() const {
//        return this->address;
//    }
//
//    int getMedicalInvestigationsCount() const {
//        return this->medicalInvestigationsCount;
//    }
//
//    string* getMedicalInvestigstions() const {
//        return this->medicalInvestigations;
//    }
//
//    int getBirthYear() const {
//        return this->birthYear;
//    }
//
//    //Setters
//
//    void setName(const char* _name) {
//        this->name = new char[strlen(_name) + 1];
//        strcpy_s(this->name, strlen(_name) + 1, _name);
//    }
//
//    void setMedicalInvestigations(int _medicalInvestigationsCount, string* _medicalInvestigations) {
//        if (_medicalInvestigations != nullptr) {
//            this->medicalInvestigations = new string[_medicalInvestigationsCount];
//            for (int i = 0; i < _medicalInvestigationsCount; i++) {
//                this->medicalInvestigations[i] = _medicalInvestigations[i];
//            }
//        }
//        else {
//            this->medicalInvestigations = nullptr;
//        } 
//    }
//
//    //Operator citire si afisare
//    friend ostream& operator<<(ostream& out, const Patient& p) {
//        out << "\nId: " << p.id;
//        out << "\nName: " << p.name;
//        out << "\nAddress: " << p.address;
//        out << "\nMedical Investigations Count: " << p.medicalInvestigationsCount;
//        out << "\nMedical Investigations: ";
//        for (int i = 0; i < p.medicalInvestigationsCount; i++) {
//            out << p.medicalInvestigations[i] << " ";
//        }
//        return out;
//    }
//
//    friend istream& operator>>(istream& in, Patient& p) {
//        cout << "\nFill in the id: ";
//        in >> p.id;
//
//        //Pentru char*
//        cout << "Fill in the name: ";
//        char aux[100];
//        //in.getline(aux, 100);
//        in >> ws;
//        in.getline(aux, 99);
//        if (p.name != nullptr) {
//            delete[] p.name;
//        }
//        p.name = new char[strlen(aux) + 1];
//        strcpy_s(p.name, strlen(aux) + 1, aux);
//
//        cout << "Fill in the address: ";
//        in >> p.address;
//
//
//        cout << "Fill in the medical investigations count: ";
//        in >> p.medicalInvestigationsCount;
//
//        //Pentru string*
//        if (p.medicalInvestigations != nullptr) {
//            delete[] p.medicalInvestigations;
//        }
//
//        p.medicalInvestigations = new string[p.medicalInvestigationsCount];
//        cout << "Fill in the medical investigations:\n ";
//        for (int i = 0; i < p.medicalInvestigationsCount; i++) {
//            in >> p.medicalInvestigations[i];
//        }
//
//        cout << "Fill in the birth year: ";
//        in >> p.birthYear;
//
//        return in;
//    }
//
//    // Cast operator
//    explicit operator int() const {
//        return this->id;
//    }
//
//    // Operator negation
//    bool operator!() const {
//        return this->medicalInvestigationsCount == 0;
//    }
//
//};
//
//int Patient::patientsCount = 0;
//
//int main() {
//    string medicInv[] = { "m1", "m2", "m3" };
//    Patient p1(1234, "Cristi", "Bucuresti", 3, medicInv, 2002);
//    cout << p1.getName();
//
//    cout << "\n\n------Testare operatorul =-------";
//    Patient p2;
//    p2 = p1; // Copiere corectă cu operatorul suprascris
//    cout << endl << p2.getName();
//
//    cout << "\n\n------Testare operaotrul de afisare-------";
//    cout << p2;
//
//    cout << "\n\n------Testare operaotrul de citire-------";
//    Patient p3;
//    cin >> p3;
//
//    cout << "\n---------Testare operaotrul de negatie---------";
//    if (!p3) {
//        cout << "\nNu are investigatii medicale";
//    }
//    else {
//        cout << "\nAre investigatii medicale";
//    }
//
//    cout << "\n\n------Testare operaotrul cast-------";
//    int patient_id = (int)p2;
//    cout << patient_id;
//
//    return 0;
//}
