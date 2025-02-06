#include <iostream>
using namespace std;

class Biblioteca {
	const int id;
	char* nume;
	int nrCarti;
	int nrGenuri;
	string* genuri;
	static int nrBiblioteca;
public:
	Biblioteca(): id(1000+(++Biblioteca::nrBiblioteca)), nrCarti(0), nrGenuri(0) {
		this->nume = new char[strlen("Unkown") + 1];
		strcpy_s(this->nume, strlen("Unkown") + 1, "Unkown");

		this->genuri = nullptr;
	}

	Biblioteca(const char* _nume, int _nrCarti, int _nrGenuri, string* _genuri) : id(1000 + (++Biblioteca::nrBiblioteca)), nrCarti(_nrCarti), nrGenuri(_nrGenuri) {
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);

		if (_nrGenuri > 0 && _genuri != nullptr) {
			this->genuri = new string[_nrGenuri];
			for (int i = 0; i < _nrGenuri; i++) {
				this->genuri[i] = _genuri[i];
			}
		}
		else {
			this->genuri = nullptr;
			this->nrGenuri = 0;
		}
	}

	Biblioteca(const Biblioteca& b) :id(1000 + (++Biblioteca::nrBiblioteca)), nrCarti(b.nrCarti), nrGenuri(b.nrGenuri) {
		this->nume = new char[strlen(b.nume) + 1];
		strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);

		if (b.nrGenuri > 0 && b.genuri != nullptr) {
			this->genuri = new string[b.nrGenuri];
			for (int i = 0; i < b.nrGenuri; i++) {
				this->genuri[i] = b.genuri[i];
			}
		}
		else {
			this->genuri = nullptr;
			this->nrGenuri = 0;
		}
	}

	Biblioteca operator=(const Biblioteca& b) {
		if (this != &b) {
			delete[] this->nume;
			delete[] this->genuri;

			
			this->nrCarti = b.nrCarti;
			this->nrGenuri = b.nrGenuri;

			this->nume = new char[strlen(b.nume) + 1];
			strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);

			if (b.nrGenuri > 0 && b.genuri != nullptr) {
				this->genuri = new string[b.nrGenuri];
				for (int i = 0; i < b.nrGenuri; i++) {
					this->genuri[i] = b.genuri[i];
				}
			}
			else {
				this->genuri = nullptr;
				this->nrGenuri = 0;
			}

		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Biblioteca& b) {
		out << "\nId: " << b.id;
		out << "\nNume: " << b.nume;
		out << "\nNr carti: " << b.nrCarti;
		out << "\nNr genuri: " << b.nrGenuri;
		out << "\nGneuri: ";
		for (int i = 0; i < b.nrGenuri; i++) {
			out << b.genuri[i] << " ";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Biblioteca& b) {
		cout << "Intrduceti numele: ";
		char buffer[100];
		in >> ws;
		in.getline(buffer, 99);
		if (b.nume!=nullptr) {
			delete[] b.nume;
		}
		b.nume = new char[strlen(buffer) + 1];
		strcpy_s(b.nume, strlen(buffer) + 1, buffer);

		cout << "Introduceti numar carti: ";
		in >> b.nrCarti;

		cout << "Introduceti numar genuri: ";
		in >> b.nrGenuri;

		cout << "Introduceti genuri: ";
		b.genuri = new string[b.nrGenuri];
		for (int i = 0; i < b.nrGenuri; i++) {
			in >> b.genuri[i];
		}

		return in;
	}

	explicit operator int() {
		return this->nrCarti;
	}

	bool operator!() {
		return this->nrCarti > 20;
	}

	bool operator<(const Biblioteca& b) {
		return this->nrCarti < b.nrCarti; 
	}

	bool operator!=(const Biblioteca& b) {
		if (this->nrCarti != b.nrCarti) {
			return true;
		}
		else {
			return false;
		}
	}

	Biblioteca operator+(int i) {
		Biblioteca temp = *this;
		temp.nrCarti = temp.nrCarti + i;
		return temp;
	}

	Biblioteca& operator++() { //preincrementare
		++this->nrCarti;
		return *this;
	}





	~Biblioteca() {
		delete[] this->nume;
		delete[] this->genuri;
	}
};

int Biblioteca::nrBiblioteca;

int main() {
	string genuri[] = { "Horror", "Thriller", "Comedie" };
	Biblioteca b1, b2("GHBJK", 2, 3, genuri);

	cout << b1 << endl;
	cout << b2 << endl << endl;

	/*Biblioteca b3;
	cin >> b3;

	cout << b3 << endl;*/

	if (b1 != b2) {
		cout << "diferite";
	}
	else {
		cout << "la fel";
	}

	b2 = b2 + 3;
	cout <<endl << b2;

	++b2;
	cout << endl << b2;

	return 0;
}