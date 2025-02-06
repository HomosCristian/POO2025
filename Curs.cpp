#include <iostream>
using namespace std;

class Curs {
	int id;
	char* denumire;
	int nrOre;
	int nrStudenti;
	string* studenti;
	static int nrStudentiMax;
public:
	Curs() : id(0), nrOre(0), nrStudenti(0) {
		this->denumire = new char[strlen("Unknown") + 1];
		strcpy_s(this->denumire, strlen("Unkown") + 1, "Unkown");

		this->studenti = nullptr;
	}

	Curs(int _id, const char* _denumire, int _nrOre, int _nrStudenti, string* _studenti) :id(_id), nrOre(_nrOre), nrStudenti(_nrStudenti) {
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);

		if (_nrStudenti > 0 && _studenti != nullptr) {
			this->studenti = new string[_nrStudenti];
			for (int i = 0; i < _nrStudenti; i++) {
				this->studenti[i] = _studenti[i];
			}
		}
		else {
			this->studenti = nullptr;
			this->nrStudenti = 0;
		}
	}

	Curs(const Curs& c) :id(c.id), nrOre(c.nrOre), nrStudenti(c.nrStudenti) {
		this->denumire = new char[strlen(c.denumire) + 1];
		strcpy_s(this->denumire, strlen(c.denumire) + 1, c.denumire);

		if (c.nrStudenti > 0 && c.studenti != nullptr) {
			this->studenti = new string[c.nrStudenti];
			for (int i = 0; i < c.nrStudenti; i++) {
				this->studenti[i] = c.studenti[i];
			}
		}
		else {
			this->studenti = nullptr;
			this->nrStudenti = 0;
		}
	}

	Curs operator=(const Curs& c) {
		if (this != &c) {
			delete[] this->denumire;
			delete[] this->studenti;

			this->id = c.id;
			this->nrStudenti = c.nrStudenti;
			this->nrOre = c.nrOre;

			this->denumire = new char[strlen(c.denumire) + 1];
			strcpy_s(this->denumire, strlen(c.denumire) + 1, c.denumire);

			if (c.nrStudenti > 0 && c.studenti != nullptr) {
				this->studenti = new string[c.nrStudenti];
				for (int i = 0; i < c.nrStudenti; i++) {
					this->studenti[i] = c.studenti[i];
				}
			}
			else {
				this->studenti = nullptr;
				this->nrStudenti = 0;
			}
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Curs& c) {
		out << "\nId: " << c.id;
		out << "\nDenumire: " << c.denumire;
		out << "\nNr ore: " << c.nrOre;
		out << "\nNr studenti: " << c.nrStudenti;
		out << "\nStudenti: ";
		for (int i = 0; i < c.nrStudenti; i++) {
			out << c.studenti[i] << " ";
		}

		return out;
	}

	friend istream& operator>>(istream& in, Curs& c) {
		cout << "Introduceti id-ul cursulu: ";
		in >> c.id;

		cout << "Introduceti denumire cursului: ";
		char buffer[100];
		in >> ws;
		in.getline(buffer, 99);
		if (c.denumire != nullptr) {
			delete[] c.denumire;
		}
		c.denumire = new char[strlen(buffer) + 1];
		strcpy_s(c.denumire, strlen(buffer) + 1, buffer);

		cout << "Introduceti numarul de ore: ";
		in >> c.nrOre;

		cout << "Introduceti numarul studentilor: ";
		in >> c.nrStudenti;

		if (c.studenti != nullptr) {
			delete[] c.studenti;
		}

		cout << "Introduceti studenti: ";
		c.studenti = new string[c.nrStudenti];
		for (int i = 0; i < c.nrStudenti; i++) {
			in >> c.studenti[i];
		}
		
		return in;
	}

	~Curs() {
		delete[] this->denumire;
		delete[] this->studenti;
	}

};

int Curs::nrStudentiMax = 30;

int main() {
	string studenti[] = {"s1", "s2", "s3"};
	Curs c1, c2(123, "Econometrie", 2, 3, studenti);

	cout << c1 << endl;
	cout << c2 << endl;
	c1 = c2;
	cout << c1 << endl;

	Curs c3;
	cin >> c3;

	return 0;
}