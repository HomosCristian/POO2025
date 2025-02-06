#include <iostream>
using namespace std;

class Plantatie{
	const int id;
	char* adresa;
	int nrPomi;
	int* varsta;
	static int nrPlantatie;
public: 
	Plantatie() : id(++Plantatie::nrPlantatie), nrPomi(0) {
		this->adresa = new char[strlen("Unkown") + 1];
		strcpy_s(this->adresa, strlen("Unkown") + 1, "Unkown");

		this->varsta = nullptr;
	}

	Plantatie(const char* _adresa, int _nrPomi, int* _varsta) : id(++Plantatie::nrPlantatie), nrPomi(_nrPomi){
		this->adresa = new char[strlen(_adresa) + 1];
		strcpy_s(this->adresa, strlen(_adresa) + 1, _adresa);

		if (_nrPomi > 0 && _varsta != nullptr) {
			this->varsta = new int[_nrPomi];
			for (int i = 0; i < _nrPomi; i++) {
				this->varsta[i] = _varsta[i];
			}
		}
		else {
			this->varsta = 0;
			this->nrPomi = 0;
		}
	}

	Plantatie(const Plantatie& p) : id(++Plantatie::nrPlantatie), nrPomi(p.nrPomi) {
		this->adresa = new char[strlen(p.adresa) + 1];
		strcpy_s(this->adresa, strlen(p.adresa) + 1, p.adresa);

		if (p.nrPomi > 0 && p.varsta != nullptr) {
			this->varsta = new int[p.nrPomi];
			for (int i = 0; i < p.nrPomi; i++) {
				this->varsta[i] = p.varsta[i];
			}
		}
		else {
			this->varsta = 0;
			this->nrPomi = 0;
		}
	}

	Plantatie& operator=(const Plantatie& p) {
		if (this != &p) {
			delete[] this->adresa;
			delete[] this->varsta;

			this->adresa = new char[strlen(p.adresa) + 1];
			strcpy_s(this->adresa, strlen(p.adresa) + 1, p.adresa);

			this->nrPomi = p.nrPomi;

			if (p.nrPomi > 0 && p.varsta != nullptr) {
				this->varsta = new int[p.nrPomi];
				for (int i = 0; i < p.nrPomi; i++) {
					this->varsta[i] = p.varsta[i];
				}
			}
			else {
				this->varsta = 0;
				this->nrPomi = 0;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Plantatie& p) {
		out << "\nId: " << p.id;
		out << "\nAdresa: " << p.adresa;
		out << "\nNr pomi: " << p.nrPomi;
		out << "\nVarste: ";
		for (int i = 0; i < p.nrPomi; i++) {
			out << p.varsta[i] << " ";
		}

		return out;

	}

	friend istream& operator>>(istream& in, Plantatie& p) {
		cout << "Introduceti adresa: ";
		char buffer[100];
		in.getline(buffer, 99);
		if (p.adresa) {
			delete[] p.adresa;
		}
		p.adresa = new char[strlen(buffer) + 1];
		strcpy_s(p.adresa, strlen(buffer) + 1, buffer);

		cout << "Introduceti nr pomi: ";
		in >> p.nrPomi;

		cout << "Introduceti varste: ";
		p.varsta = new int[p.nrPomi];
		for (int i = 0; i < p.nrPomi; i++) {
			in >> p.varsta[i];
		}

		return in;
	}

	explicit operator int() {
		return this->nrPomi;
	}

	bool operator!() {
		return this->nrPomi > 5;
	}

	bool operator!=(const Plantatie& p) {
		return this->nrPomi != p.nrPomi;
	}

	~Plantatie() {
		delete[] this->adresa;
		delete[] this->varsta;
	}
};

int Plantatie::nrPlantatie = 0;

int main() {
	int varste[] = { 1,2,3 };
	Plantatie p1, p2("Bucuresti", 3, varste);

	cout << p1 << endl;

	cout << p2 << endl;

	Plantatie p3(p2), p4;
	p4 = p2;

	cout << p3 << endl;
	cout << p4 << endl;
}