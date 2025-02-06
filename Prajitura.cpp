#include <iostream>
using namespace std;

class Prajitura {
	char* denumire;
	int nrCalorii;
	int nrIngrediente;
	int* gramajIngrediente;
	bool esteVegan;
	static int nrPrajituri;
public:
	Prajitura() : nrCalorii(0), nrIngrediente(0), esteVegan(false) {
		this->denumire = new char[strlen("Unknown") + 1];
		strcpy_s(this->denumire, strlen("Unknown") + 1, "Unknown");
		this->gramajIngrediente = nullptr;
		nrPrajituri++;
	}

	Prajitura(const char* _denumire, int _nrCalorii, int _nrIngrediente, int* _gramajIngrediente, bool _esteVegan) : nrCalorii(_nrCalorii), nrIngrediente(_nrIngrediente), esteVegan(_esteVegan) {
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);

		if (_gramajIngrediente != nullptr && _nrIngrediente > 0) {
			this->gramajIngrediente = new int[_nrIngrediente];
			for (int i = 0; i < _nrIngrediente; i++) {
				this->gramajIngrediente[i] = _gramajIngrediente[i];
			}
		}
		else {
			this->gramajIngrediente = nullptr;
			this->nrIngrediente = 0;
		}
		nrPrajituri++;
	}

	Prajitura(const Prajitura& p) : nrCalorii(p.nrCalorii), nrIngrediente(p.nrIngrediente), esteVegan(p.esteVegan) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);

		if (p.gramajIngrediente != nullptr && p.nrIngrediente > 0) {
			this->gramajIngrediente = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->gramajIngrediente[i] = p.gramajIngrediente[i];
			}
		}
		else {
			this->gramajIngrediente = nullptr;
			this->nrIngrediente = 0;
		}
		nrPrajituri++;
	}

	Prajitura operator=(const Prajitura& p) {
		if (this != &p) {
			delete[] this->denumire;
			delete[] this->gramajIngrediente;

			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);

			this->nrCalorii = p.nrCalorii;

			this->nrIngrediente = p.nrIngrediente;

			if (p.gramajIngrediente != nullptr && p.nrIngrediente > 0) {
				this->gramajIngrediente = new int[this->nrIngrediente];
				for (int i = 0; i < this->nrIngrediente; i++) {
					this->gramajIngrediente[i] = p.gramajIngrediente[i];
				}
			}
			else {
				this->gramajIngrediente = nullptr;
				this->nrIngrediente = 0;
			}

			this->esteVegan = p.esteVegan;
		}
		return *this;
	}

	const char* getDenumire() const {
		return this->denumire;
	}

	int* getGramajIngrediente() const {
		return this->gramajIngrediente;
	}

	void setDenumire(const char* _denumire) {
		this->denumire = new char[strlen(_denumire) + 1];
		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);
	}

	void setGramajIngrediente(int _nrIngrediente, int* _gramajIngrediente) {
		if (_gramajIngrediente != nullptr && _nrIngrediente > 0) {
			this->gramajIngrediente = new int[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++) {
				this->gramajIngrediente[i] = _gramajIngrediente[i];
			}
		}
		else {
			this->gramajIngrediente = nullptr;
			this->nrIngrediente = 0;
		}
	}

	~Prajitura() {
		delete[] this->denumire;
		delete[] this->gramajIngrediente;
		nrPrajituri--;
	}

	friend ostream& operator<<(ostream& out, const Prajitura& p) {
		out << "\nDenumire: " << p.denumire;
		out << "\nNr calorii: " << p.nrCalorii;
		out << "\nNr ingrediente: " << p.nrIngrediente;

		out << "\nGramaj ingrediente: ";
		for (int i = 0; i < p.nrIngrediente; i++) {
			out << p.gramajIngrediente[i] << " ";
		}

		out << "\nEste vegan: " << p.esteVegan;
		return out;
	}

	friend istream& operator>>(istream& in, Prajitura& p) {
		cout << "Introduceti denumirea prajiturii: ";
		char buffer[100];
		in >> ws;
		in.getline(buffer, 99);
		if (p.denumire != nullptr) {
			delete[] p.denumire;
		}
		p.denumire = new char[strlen(buffer) + 1];
		strcpy_s(p.denumire, strlen(buffer) + 1, buffer);

		cout << "Introduceti numarul de calorii: ";
		in >> p.nrCalorii;

		cout << "Introduceti numarul de ingrdiente: ";
		in >> p.nrIngrediente;

		if (p.nrIngrediente <= 0) {
			p.gramajIngrediente = nullptr;
			p.nrIngrediente = 0;
		}
		else {
			p.gramajIngrediente = new int[p.nrIngrediente];
			cout << "Introduceti gramaj ingrediente: ";
			for (int i = 0; i < p.nrIngrediente; i++) {
				in >> p.gramajIngrediente[i];


			}
		}
		return in;
	}

	explicit operator int() {
		return this->nrCalorii;
	}

	bool operator!() {
		return this->nrIngrediente > 5;
	}

	int GetGramajTotal() {
		int gramajTotal = 0;
		for (int i = 0; i < this->nrIngrediente; i++) {
			gramajTotal = gramajTotal + this->gramajIngrediente[i];
		}
		return gramajTotal;
	}

};

int Prajitura::nrPrajituri = 0;

int main() {
	int gramajIngrediente[] = { 3, 6, 23, 12 };
	Prajitura p1, p2("Clatite", 100, 4, gramajIngrediente, false);

	cout << p1 << endl;
	cout << "\n----------Testare constructor cu toti parametrii si supraincarcare operator afisare----------" << p2 << endl;

	cout << "\n----------Testare supraincarcare operator cast----------" << endl;
	int nrCalorii = int(p2);
	cout << nrCalorii << endl;

	cout << "\n----------Testare supraincarcare operator negare----------";
	if (!p2) {
		cout << "\nAre mai mult de 5 ingrediente";
	}
	else {
		cout << "\nNu are mai mult de 5 ingrediente";
	}

	cout << "\n\n----------Testare metoda GetGramajTotal()----------";
	cout << endl << p2.GetGramajTotal() << endl;

	cout << "\n----------Testare supraincarcare operator citire----------\n";
	Prajitura p3;
	cin >> p3;

	return 0;
}