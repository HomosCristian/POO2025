#include <iostream>
using namespace std;

class Comanda {
	const int id;
	char* nume;
	int nrProduse;
	string* produse;
	static int nrComenzi;
public: 

	Comanda() :id(++Comanda::nrComenzi), nrProduse(0) {
		this->nume = new char[strlen("Unkown") + 1];
		strcpy_s(this->nume, strlen("Unkown") + 1, "Unkown");

		this->produse = 0;
	}

	Comanda(const char* _nume, int _nrProduse, string* _produse) : id(++Comanda::nrComenzi), nrProduse(_nrProduse) {
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);

		if (_produse != nullptr && _nrProduse > 0) {
			this->produse = new string[_nrProduse];
			for (int i = 0; i < _nrProduse; i++) {
				this->produse[i] = _produse[i];
			}
		}
		else {
			this->produse = nullptr;
			this->nrProduse = 0;
		}
	}

	Comanda(const Comanda& c) :id(++Comanda::nrComenzi), nrProduse(c.nrProduse) {
		this->nume = new char[strlen(c.nume) + 1];
		strcpy_s(this->nume, strlen(c.nume) + 1, c.nume);

		if (c.produse != nullptr && c.nrProduse > 0) {
			this->produse = new string[c.nrProduse];
			for (int i = 0; i < c.nrProduse; i++) {
				this->produse[i] = c.produse[i];
			}
		}
		else {
			this->produse = nullptr;
			this->nrProduse = 0;
		}
	}

	Comanda operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->nume;
			delete[] this->produse;

			this->nrProduse = c.nrProduse;

			this->nume = new char[strlen(c.nume) + 1];
			strcpy_s(this->nume, strlen(c.nume) + 1, c.nume);

			if (c.nrProduse > 0 && c.produse!=nullptr) {
				this->produse = new string[c.nrProduse];
				for (int i = 0; i < c.nrProduse; i++) {
					this->produse[i] = c.produse[i];
				}
			}
			else {
				this->produse = nullptr;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {
		out << "\nId: " << c.id;
		out << "\nNume: " << c.nume;
		out << "\nNr produse : " << c.nrProduse;
		out << "\nProduse: ";
		for (int i = 0; i < c.nrProduse; i++) {
			out << c.produse[i] << " ";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Comanda& c) {
		cout << "Introduceti numele: ";
		char buffer[100];
		in >> ws;
		in.getline(buffer, 100);
		if (c.nume != nullptr) {
			delete[] c.nume;
		}
		c.nume = new char[strlen(buffer) + 1];
		strcpy_s(c.nume, strlen(buffer) + 1, buffer);

		cout << "Introduceti nr produselor: ";
		in >> c.nrProduse;

		cout << "Introduceti produsele: ";
		c.produse = new string[c.nrProduse];
		for (int i = 0; i < c.nrProduse; i++) {
			in >> c.produse[i];
		}

		return in;
	}

	//Getters

	const char* getNume() const {
		return this->nume;
	}

	string* getProduse() const {
		return this->produse;
	}

	//Setters

	void setNume(const char* _nume) {
		delete[] this->nume;
		this->nume = new char[strlen(_nume) + 1];
		strcpy_s(this->nume, strlen(_nume) + 1, _nume);
	}

	void setProduse(int _nrProduse, string* _produse) {
		delete[] this->produse;

		if (this->produse != nullptr && this->nrProduse > 0) {
			this->produse = new string[_nrProduse];
			for (int i = 0; i < _nrProduse; i++) {
				this->produse[i] = _produse[i];
			}
		}
		else {
			this->produse = nullptr;
			this->nrProduse = 0;
		}
	}

	bool operator!() {
		return this->nrProduse > 5;
	}

	bool operator!=(const Comanda& c) {
		return this->nrProduse != c.nrProduse;
	}

	explicit operator int() {
		return this->nrProduse;
	}

	//Comanda operator+(int i) {
	//	Comanda temp = *this;
	//	temp.nrProduse = this->nrProduse + 1;
	//	return temp;
	//}

	//Comanda& operator++() {
	//	++this->nrProduse;
	//	return *this;
	//}

	~Comanda() {
		delete[] this->nume;
		delete[] this->produse;
	}
};

int Comanda::nrComenzi = 0;


int main() {
	// Test Constructor implicit
	Comanda c1;
	cout << c1 << endl;

	// Test Constructor cu parametri
	string produse[] = { "Laptop", "Mouse", "Tastatura" };
	Comanda c2("Comanda Electronice", 3, produse);
	cout << c2 << endl;

	// Test Constructor de copiere
	Comanda c3(c2);
	cout << c3 << endl;

	// Test Operator=
	Comanda c4;
	c4 = c2;
	cout << c4 << endl;

	if (!c2) {
		cout <<endl << "Comanda c1 are mai mult de 5 produse.\n";
	}
	else {
		cout<< endl << "Comanda c1 are mai putin sau egal cu 5 produse.\n";
	}

	if (c1 != c2) {
		cout << "Comenzile c1 și c2 au un număr diferit de produse.\n";
	}
	else {
		cout << "Comenzile c1 și c2 au același număr de produse.\n";
	}

	int nrProduseC1 = int(c1);
	cout << "Numărul de produse din c1 (folosind conversia explicită): " << nrProduseC1 << endl;



	//// Testăm operatorul +
	//Comanda c5 = c1 + 2; // Adăugăm 2 produse la c1
	//cout << "c3 după adăugarea a 2 produse la c1:\n" << c5 << endl;

	// Testăm operatorul ++ (pre-incrementare)
	//++c2;
	//cout << "c1 după pre-incrementare (++c1):\n" << c2 << endl;

	return 0;
}