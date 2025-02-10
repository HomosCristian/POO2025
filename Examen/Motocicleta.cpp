#include <iostream>
#include <fstream>
using namespace std;

/* 
	Aplicatie cu 3 clase: -Motocicleta(clasa principala)
						  -Dealership (HAS A Motocicleta)
						  -MotocicletaAutoma(IS A Motocicleta)
						  -Transmisie(clasa enum folosita in MotocicletaAutomata) 
*/

class AbstractPur {
public:
	virtual void afiseazaMesaj() = 0; //Trebuie initializat neaparat

	virtual ~AbstractPur() {

	}
};

class Motocicleta : public AbstractPur {
protected:
	char* marca;
	string denumire;
	int anFabricatie;
	int capacitate;
	int nrModele;
	string* model;
	bool esteElectric;
public:
	//Constructor Default
	Motocicleta() : denumire("Unknown"), anFabricatie(1900), capacitate(0), nrModele(0), esteElectric(false) {
		this->marca = new char[strlen("Unknown") + 1];
		strcpy_s(this->marca, strlen("Unknown") + 1, "Unknown");

		this->model = nullptr;
	}

	//Contructor cu toti parametrii
	Motocicleta(const char* _marca, string _denumire, int _anFabricatie, int _capacitate, int _nrModele, const string* _model, bool _esteElectric)
		: anFabricatie(_anFabricatie), denumire(_denumire), capacitate(_capacitate), nrModele(_nrModele), esteElectric(_esteElectric) {
		this->marca = new char[strlen(_marca) + 1];
		strcpy_s(this->marca, strlen(_marca) + 1, _marca);

		if (_nrModele > 0 && _model != nullptr) {
			this->model = new string[_nrModele];
			for (int i = 0; i < _nrModele; i++) {
				this->model[i] = _model[i];
			}
		}
		else {
			this->model = nullptr;
			this->nrModele = 0;
		}
	}

	//Constructor de copiere
	Motocicleta(const Motocicleta& m)
		: anFabricatie(m.anFabricatie), denumire(m.denumire), capacitate(m.capacitate), nrModele(m.nrModele), esteElectric(m.esteElectric) {
		this->marca = new char[strlen(m.marca) + 1];
		strcpy_s(this->marca, strlen(m.marca) + 1, m.marca);

		if (m.nrModele > 0 && m.model != nullptr) {
			this->model = new string[m.nrModele];
			for (int i = 0; i < m.nrModele; i++) {
				this->model[i] = m.model[i];
			}
		}
		else {
			this->model = nullptr;
			this->nrModele = 0;
		}
	}

	//Supraincarcare operator=
	Motocicleta operator=(const Motocicleta& m) {
		if (this != &m) {
			delete[] this->marca;
			delete[] this->model;

			this->denumire = m.denumire;
			this->anFabricatie = m.anFabricatie;
			this->capacitate = m.capacitate;
			this->esteElectric = m.esteElectric;
			this->nrModele = m.nrModele;

			this->marca = new char[strlen(m.marca) + 1];
			strcpy_s(this->marca, strlen(m.marca) + 1, m.marca);

			if (m.nrModele > 0 && m.model != nullptr) {
				this->model = new string[m.nrModele];
				for (int i = 0; i < m.nrModele; i++) {
					this->model[i] = m.model[i];
				}
			}
			else {
				this->model = nullptr;
				this->nrModele = 0;
			}
		}
		return *this;
	}

	//Suparaincarcare operator cast int
	explicit operator int() {
		return this->capacitate;
	}

	//Suparaincarcare operator!
	bool operator!() {
		return this->capacitate > 600;
	}

	//Supraincarcare operator1!=
	bool operator!=(const Motocicleta& m) {
		return this->capacitate != m.capacitate;
	}

	//Supraincarcare operator +, care e la fel cu - , * , / ;
	friend Motocicleta operator+(Motocicleta& m, int valoare);  //Operator+ folosind friend

	//Operator- 
	Motocicleta operator-(int valoare) {
		Motocicleta copie = *this;
		copie.capacitate -= valoare;
		return copie;
	}

	//Operator++ PRE
	Motocicleta& operator++() {  //preincrementare
		this->anFabricatie += 1;
		return *this;
	}

	//operator++ POST
	Motocicleta operator++(int) { //postincrementare
		Motocicleta copie = *this;  // Salvează starea curentă înainte de modificare
		++(*this);                  // Folosim pre-incrementarea pentru a modifica obiectul
		return copie;               // Returnează copia (starea anterioară)
	}

	//Operator*
	Motocicleta operator*(int _valoare) {  //Aici modificam si returnam o copie
		Motocicleta m = *this;
		m.anFabricatie = _valoare;
		return m;
	}

	//Operator*=
	Motocicleta& operator*=(int _valoare) {
		this->anFabricatie = _valoare;  //Aici modificam obiectul direct
		return *this;
	}

	//Operator-=
	Motocicleta& operator-=(const Motocicleta& m) {
		this->capacitate -= m.capacitate;
		return *this;
	}

	//Operator[]
	string& operator[](int _index) {  //Punem string& ca sa poata fi si modificat merge si fara& dar nu va putea fi modificat
		return this->model[_index];
	}

	//Supraincarcare operator==
	bool operator==(const Motocicleta& m) {
		if (strcmp(this->marca, m.marca) != 0)
			return false;
		if (this->denumire != m.denumire)
			return false;
		if (this->anFabricatie != m.anFabricatie)
			return false;
		if (this->capacitate != m.capacitate)
			return false;
		if (this->esteElectric != m.esteElectric)
			return false;
		if (this->nrModele != m.nrModele)
			return false;
		for (int i = 0; i < this->nrModele; i++)
			if (this->model[i] != m.model[i])
				return false;
		return true;
	}

	//Getters
	string getDenumire() const {
		return this->denumire;
	}

	int getAnFabricatie() const {
		return this->anFabricatie;
	}

	int getCapacitate() const {
		return this->capacitate;
	}

	int getEsteElectric() const {
		return this->esteElectric;
	}

	const char* getMarca() const {
		return this->marca;
	}

	const string* getModele() const {
		return this->model;
	}
	
	//Setters
	void setDenumire(string _denumire) {
		this->denumire = _denumire;
	}

	void SetAnFabricatie(int _anFabricatie) {
		this->anFabricatie = _anFabricatie;
	}

	void SetCapacitate(int _capacitate) {
		this->capacitate = _capacitate;
	}

	void setEsteElectric(bool _esteElectric) {
		this->esteElectric = _esteElectric;
	}

	void setMarca(const char* _denumire) {
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->marca, strlen(_denumire) + 1, _denumire);
	}

	void setModele(int _nrModele, const string* _model) {
		if (_nrModele > 0 && _model != nullptr) {
			this->model = new string[_nrModele];
			for (int i = 0; i < _nrModele; i++) {
				this->model[i] = _model[i];
			}
		}
		else {
			this->model = nullptr;
			this->nrModele = 0;
		}
	}

	//Destructor
	~Motocicleta() {
		delete[] this->marca;
		delete[] this->model;
	}

	//Suparaincarcare operator<< (aifsare)
	friend ostream& operator<<(ostream& out, const Motocicleta& m) {
		out << "\nMarca: " << m.marca;
		out << "\nDenumire: " << m.denumire;
		out << "\nCapacitate: " << m.capacitate;
		out << "\nAnul fabricatiei: " << m.anFabricatie;
		out << "\nEste electric: " << m.esteElectric;
		out << "\nNumarul de modele: " << m.nrModele;
		out << "\nModele: ";
		for (int i = 0; i < m.nrModele; i++) {
			out << m.model[i] << " ";
		}
		return out;
	}

	//Scriere in fisier txt
	friend ofstream& operator<<(ofstream& out, const Motocicleta& m) {
		out << m.marca;
		out << endl << m.denumire;
		out << endl << m.capacitate;
		out << endl << m.anFabricatie;
		out << endl << m.esteElectric;
		out << endl << m.nrModele;
		out << endl;
		for (int i = 0; i < m.nrModele; i++) {
			out << m.model[i] << " ";
		}
		return out;
	}

	//Serializare
	void writeToFile(fstream& f) {
		//Scriere char*(marca)
		int lg = strlen(this->marca) + 1; //Scriere lungime sir
		f.write((char*)&lg, sizeof(int));
		f.write(this->marca, lg); //Scriere sir de caractere

		//Scriere string(denumire)
		lg = this->denumire.length() + 1; //Scriere lungime sir
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire.data(), lg);//Scriere sir de caractere si data() returneaza chiar char*

		//Scriere int(anFabricatie, capacitate)
		f.write((char*)&this->anFabricatie, sizeof(int));
		f.write((char*)&this->capacitate, sizeof(int));
		
		//Scriere int(nrModele) si string*(modele)
		f.write((char*)&this->nrModele, sizeof(int));
		for (int i = 0; i < nrModele; i++) {
			lg = this->model[i].length() + 1; //Scriere lungime sir
			f.write((char*)&lg, sizeof(int));
			f.write(this->model[i].data(), lg);//Scriere sir de caractere si data() returneaza chiar char*
		}

		//Scriere bool(esteElectric)
		f.write((char*)&this->esteElectric, sizeof(bool));
	}

	//Supraincarcare operator>> (citire)
	friend istream& operator>>(istream& in, Motocicleta& m) {
		cout << "Introdcueti marca motocicletei: ";
		char buffer[100];
		in >> ws;
		in.getline(buffer, 99);
		if (m.marca != nullptr) {
			delete[] m.marca;
		}
		m.marca = new char[strlen(buffer) + 1];
		strcpy_s(m.marca, strlen(buffer) + 1, buffer);

		cout << "Introduceti denumirea motocicletei: ";
		in >> m.denumire;

		cout << "Introduceti capacitatea motocicletei: ";
		in >> m.capacitate;

		cout << "Introduceti anul fabricatiei al motocicletei: ";
		in >> m.anFabricatie;

		cout << "Introduceti daca motocicleta este electrica: ";
		in >> m.esteElectric;

		cout << "Introduceti numarul de modele: ";
		in >> m.nrModele;

		cout << "Introduceti modele: ";
		m.model = new string[m.nrModele];
		for (int i = 0; i < m.nrModele; i++) {
			in >> m.model[i];
		}
		return in;
	}

	//Citire din fisier txt
	friend ifstream& operator>>(ifstream& in, Motocicleta& m) {
		char buffer[100];
		in >> ws;
		in.getline(buffer, 99);
		if (m.marca != nullptr) {
			delete[] m.marca;
		}
		m.marca = new char[strlen(buffer) + 1];
		strcpy_s(m.marca, strlen(buffer) + 1, buffer);

		in >> m.denumire;

		in >> m.capacitate;

		in >> m.anFabricatie;

		in >> m.esteElectric;

		in >> m.nrModele;

		m.model = new string[m.nrModele];
		for (int i = 0; i < m.nrModele; i++) {
			in >> m.model[i];
		}
		return in;
	}

	//Deserializare
	void readFromFile(fstream& f) {
		//Dezalocare zona de memorie pentru memoria alocata anterior de obj this
		if (this->marca != nullptr) {
			delete[] this->marca;
			this->marca = nullptr;
		}
		if (this->model != nullptr) {
			delete[] this->model;
			this->model = nullptr;
		}

		//Citire char*(marca)
		int lg;
		f.read((char*)&lg, sizeof(int));
		this->marca = new char[lg + 1];
		f.read(this->marca, lg);

		//Citire string(denumire)
		//int lg;
		f.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg + 1];
		f.read(buffer, lg);
		this->denumire = buffer;

		//Citire int(anFabricatie, capacitate)
		f.read((char*)&this->anFabricatie, sizeof(int));
		f.read((char*)&this->capacitate, sizeof(int));

		//Citire int(nrModele) si string*(modele)
		f.read((char*)&this->nrModele, sizeof(int));
		for (int i = 0; i < nrModele; i++) {
			int lg;
			f.read((char*)&lg, sizeof(int));
			char* buffer = new char[lg + 1];
			f.read(buffer, lg);
			this->denumire = buffer;
		}

		//Citire bool(esteElectric)
		f.read((char*)&this->esteElectric, sizeof(bool));
	}

	//Functie clasa abstracta 
	void afiseazaMesaj() {
		cout<< "\nMotocicleta manuala";
	}

	//Fucntie virtuala
	virtual void afiseazaTipulClasei() {
		cout<<"\nClasa Motocicleta";
	}


};

class Dealership { // HAS A Motocicleta
	const int id;
	string denumire;
	Motocicleta** listaMotociclete;
	int nrMotociclete;
	static int nrDealership;
public:
	//Constructor default
	Dealership() : id(1000 + (++Dealership::nrDealership)), denumire("Unknown"), nrMotociclete(0) {
		this->listaMotociclete = nullptr;
	}

	//Constructor cu toti param
	Dealership(string _denumire, Motocicleta** _listaMotociclete, int _nrMotociclete) : id(1000 + (++Dealership::nrDealership)), denumire(_denumire), nrMotociclete(_nrMotociclete) {
		if (_listaMotociclete != nullptr && _nrMotociclete > 0) {
			this->nrMotociclete = _nrMotociclete;
			this->listaMotociclete = new Motocicleta * [_nrMotociclete];
			for (int i = 0; i < _nrMotociclete; i++) {
				this->listaMotociclete[i] = new Motocicleta(*_listaMotociclete[i]);
			}
		}
	}

	//Constructor de copiere
	Dealership(const Dealership& d) : id(1000 + (++Dealership::nrDealership)), denumire(d.denumire), nrMotociclete(d.nrMotociclete) {
		if (d.listaMotociclete != nullptr && d.nrMotociclete > 0) {
			this->nrMotociclete = d.nrMotociclete;
			this->listaMotociclete = new Motocicleta * [d.nrMotociclete];
			for (int i = 0; i < d.nrMotociclete; i++) {
				this->listaMotociclete[i] = new Motocicleta(*d.listaMotociclete[i]);
			}
		}
	}

	//Supraincarcare operator=
	Dealership& operator=(const Dealership& d) {
		if (this != &d) {
			delete[] this->listaMotociclete;

			this->denumire = d.denumire;
			this->nrMotociclete = d.nrMotociclete;
			this->listaMotociclete = new Motocicleta * [d.nrMotociclete];
			for (int i = 0; i < d.nrMotociclete; i++) {
				this->listaMotociclete[i] = new Motocicleta(*d.listaMotociclete[i]);
			}
		}
		else {
			this->listaMotociclete = nullptr;
			this->nrMotociclete = 0;
		}
		return *this;
	}

	//Destructor
	~Dealership() {
		//for (int i = 0; i < this->nrMotociclete; i++) {
		//	delete this->listaMotociclete[i];
		//}
		delete[] this->listaMotociclete;
		this->listaMotociclete = nullptr;
	}

	friend ostream& operator<<(ostream& out, const Dealership& d) {
		out << "\nId: " << d.id;
		out << "\nDenumire: " << d.denumire;
		out << "\nNumar Motociclete: " << d.nrMotociclete;
		out << "\nLista Motociclete: ";
		for (int i = 0; i < d.nrMotociclete; i++) {
			out << *d.listaMotociclete[i];
		}
		return out;
	}
};

enum Transmisie{
	AUTOMATA, ECLUTCH, CVT
};

class MotocicletaAutomata : public Motocicleta { //IS A Motocicleta
	Transmisie transmisie;
public:
	//Constructor default
	MotocicletaAutomata() : transmisie(Transmisie::AUTOMATA), Motocicleta() {

	}

	//Constructor cu toti parametrii
	MotocicletaAutomata(const char* _marca, string _denumire, int _anFabricatie, int _capacitate, int _nrModele, const string* _model, bool _esteElectric, Transmisie _transmisie) : transmisie(_transmisie), Motocicleta(_marca, _denumire, _anFabricatie, _capacitate, _nrModele, _model, _esteElectric) {

	}

	//Constructor de copiere
	MotocicletaAutomata(const MotocicletaAutomata& m) : Motocicleta(m), transmisie(m.transmisie){

	}

	MotocicletaAutomata& operator=(const MotocicletaAutomata& m) {
		if (this != &m) {
			Motocicleta::operator=(m); //Upcast implicit
			this->transmisie = m.transmisie;
		}
		return *this;
	}

	//Destructor
	~MotocicletaAutomata() {

	}

	//Supraincarcare operator<<
	friend ostream& operator<<(ostream& out, const MotocicletaAutomata& m) {
		out << Motocicleta(m); //Apleul explicit din clasa principala
		out << "\nModel Transmisie: " << m.transmisie;
		return out;
	}

	//Functie clasa abstracta
	void afiseazaMesaj() {
		cout<< "\nMotocicleta auttomata";
	}

	//Functie virtuala
	void afiseazaTipulClasei() {
		cout<< "\nClasa MotocicletaAutomata";
	}
};

int Dealership::nrDealership = 0;

//Operator+ folosind friend
Motocicleta operator+(Motocicleta& m, int valoare) {
	Motocicleta copie = m;
	copie.capacitate += valoare;
	return copie;
}

int main() {
	//Testare cosntructor default
	Motocicleta m1; 
	cout << "CONSTRUCTOR DEFAULT" << m1 << endl;

	//Testare constructor cu toti parametrii
	string model[] = { "650", "400", "ZX6R" };
	Motocicleta m2("Kawasaki", "Ninja", 2019, 649, 3, model, false);
	cout << "\nCONSTRUCTOR CU TOTI PARAMETRII" << m2 << endl;

	//Testare constructor de copiere
	Motocicleta m3(m2);
	cout << "\nCONSTRUCTOR DE COPIERE" << m3 << endl;

	//Testare operator=
	Motocicleta m4;
	m4 = m3;
	cout << "\nOPERATOR=" << m4 << endl;

	//Testare citire obiect de la tastatura
	//Motocicleta m5;
	//cout << endl;
	//cin >> m5;

	//Testare operator!
	cout << "\nOPERATOR!";
	if (!m2) {
		cout << "\nCapacitate mai mare de 600cc\n";
	}
	else {
		cout<< "\nCapacitate mai mica de 600cc\n";
	}

	//Testare operator!=
	cout << "\nOPERATOR!=";
	if (m2!=m3) {
		cout << "\nCapacitati diferite\n";
	}
	else {
		cout << "\nCapacitati la fel\n";
	}

	//Testare operator cast la int
	cout << "\nOPERATOR(int)\n";
	int cap = (int)m2;
	cout << cap << endl;

	//Testare operator==
	cout << "\nOPERATOR==\n";
	cout << (m2 == m3);

	//Testare HAS A
	Motocicleta* lista[] = { &m1, &m2 };
	Dealership d1("Kawasaki", lista, 2);
	cout << "\n\nTESTARE HAS A" << d1;

	//Tstare IS A
	MotocicletaAutomata ma1("Kawasaki", "Ninja", 2024, 125, 3, model, false, Transmisie::CVT);
	cout << "\n\nTESTARE IS A" << ma1;

	//Tstare fisiere txt
	ofstream g("motociclete.txt");
	g << m2;
	g.close();

	ifstream f("motociclete.txt");
	Motocicleta m5;
	f >> m5;
	cout <<"\n\nTESTARE CITIRE DIN FISIER TXT" << m5;

	//Testare fisiere binare
	fstream fileOut("motociclete.bin", ios::out | ios::binary); //Fisier de scriere in el
	Motocicleta m6;
	m6.writeToFile(fileOut);
	fileOut.close();

	fstream fileIn("motociclete.bin", ios::in | ios::binary); //Fisier de citire din el
	Motocicleta m7;
	m7.readFromFile(fileIn);
	cout << "\n\nTSTARE FISIER BINAR";
	cout << m7;

	//Testare functia virtuala din clasa de baza (afiseazaTipulClasei)
	cout << "\n\nTESTARE FUNCTIE VIRTUALA";
	m2.afiseazaTipulClasei();
	ma1.afiseazaTipulClasei();

	//Testare clasa AbstractPur
	cout << "\n\nTESTARE CLASA ABSTRACTA";
	m2.afiseazaMesaj();
	ma1.afiseazaMesaj();

	//Testare operator+ friend
	cout << "\n\nTESTARE OPERATOR+ FRIEND";
	Motocicleta m10 = m2 + 50;
	cout << m10;

	//Testare operator- 
	cout << "\n\nTESTARE OPERATOR-";
	m10 = m10 - 50;
	cout << m10;

	cout << "\n\nTESTARE OPERATOR*";
	m3 = m3 * 15;
	cout << m3;

	//Testare operator++
	cout << "\n\nTESTARE PREINCREMENTARE";
	cout<< ++m4;

	cout << "\n\nTESTARE POSTINCREMENTARE";
	cout<< m4++;
	
	cout << "\n\nTESTARE OPERATOR-=";
	m4 -= m3;
	cout << m4;

	cout << "\n\nTESTARE OPERATOR[]";
	cout<< endl<< m4[2];

}