#include <iostream>
using namespace std;

class Proiect {
	char* denumire;
	string dataIncepre;
	int nrEtape;
	float* procentRealizare;
	float buget;  //>0
	static int nrProiecte;
	int durataProiect;
public:
	Proiect() : dataIncepre("01.01.2024"), nrEtape(0), buget(0), durataProiect(0) {
		this->denumire = new char[strlen("Unknown") + 1];
		strcpy_s(this->denumire, strlen("Unknown") + 1, "Unknown");

		this->procentRealizare = nullptr;
		Proiect::nrProiecte++;
	}

	Proiect(const char* _denumire, string _dataIncepere, int _nrEtape, float _buget, int _durataProiect) : dataIncepre(_dataIncepere), nrEtape(_nrEtape), durataProiect(_durataProiect) {
		this->denumire = new char[strlen(_denumire) + 1];

		if (_buget > 0) {
			this->buget = _buget;
		}
		else {
			this->buget = 0;
		}

		strcpy_s(this->denumire, strlen(_denumire) + 1, _denumire);
		this->procentRealizare = nullptr;
		Proiect::nrProiecte++;
	}

	Proiect(const Proiect& p) : dataIncepre(p.dataIncepre), nrEtape(p.nrEtape), buget(p.buget), durataProiect(p.durataProiect) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);

		if (p.nrEtape > 0 && p.procentRealizare != nullptr) {
			this->procentRealizare = new float[p.nrEtape];
			for (int i = 0; i < p.nrEtape; i++) {
				this->procentRealizare[i] = p.procentRealizare[i];
			}
		}
		else {
			//this->nrEtape = 0;
			this->procentRealizare = nullptr;
		}
		Proiect::nrProiecte++;
	}

	Proiect& operator=(const Proiect& p) {
		if (this != &p) {
			delete[] this->denumire;
			delete[] this->procentRealizare;

			this->dataIncepre = p.dataIncepre;
			this->nrEtape = p.nrEtape;
			this->buget = p.buget;
			this->durataProiect = p.durataProiect;
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy_s(this->denumire, strlen(p.denumire) + 1, p.denumire);

			if (p.nrEtape > 0 && p.procentRealizare != nullptr) {
				this->procentRealizare = new float[p.nrEtape];
				for (int i = 0; i < p.nrEtape; i++) {
					this->procentRealizare[i] = p.procentRealizare[i];
				}
			}
			else {
				//this->nrEtape = 0;
				this->procentRealizare = 0;
			}

			Proiect::nrProiecte++;
		}
		return *this;
	}

	//Getters
	const float* getProcentRealizare() const {
		return this->procentRealizare;
	}

	//Setters
	void setProcentRealizare(int _nrEtape, float* _procentRealizare) {
		delete[] this->procentRealizare;

		this->nrEtape = _nrEtape;
		if (_nrEtape > 0 && _procentRealizare != nullptr) {
			this->procentRealizare = new float[_nrEtape];
			for (int i = 0; i < _nrEtape; i++) {
				this->procentRealizare[i] = _procentRealizare[i];
			}
		}
		else {
			this->nrEtape = 0;
			this->procentRealizare = nullptr;
		}
	}

	~Proiect() {
		delete[] this->denumire;
		delete[] this->procentRealizare;
	}

	Proiect& operator++(int _buget) {
		this->buget = this->buget + _buget;
		return *this;
	}

	bool operator!() {

	}

	friend ostream& operator<<(ostream& out, const Proiect& p) {
		out << "\nDenumire: " << p.denumire;
		out << "\nData incepere: " << p.dataIncepre;
		out << "\nNr etape: " << p.nrEtape;
		out << "\nProcente realizare: ";
		if (p.nrEtape > 0 && p.procentRealizare != nullptr) {

			for (int i = 0; i < p.nrEtape; i++) {
				out << p.procentRealizare[i] << " ";
			}
		}

		out << "\nBuget: " << p.buget;
		out << "\nDurata proiect: " << p.durataProiect;
		out << "\nTotal proiecte: " << Proiect::nrProiecte;
		return out;
	}

	bool verificaStareProiect() {
		int contor;
		for (int i = 0; i < this->nrEtape; i++) {
			if (this->procentRealizare[i] == 100) {
				contor++;
			}
		}
		if (contor == this->nrEtape) {
			return true;
		}
		else {
			return false;
		}
	}
};

int Proiect::nrProiecte = 0;

int main() {
	Proiect p1, p2("POO", "11.11.2024", 2, 40, 2);
	cout << "Testare constructor default si operator <<" << endl << p1 << endl;
	cout << endl << "Testare constructor cu parametrii" << endl << p2 << endl;

	Proiect p3(p2);
	cout << endl << "Testare constructor de copiere" << endl << p3 << endl;

	Proiect p4;
	p4 = p2;
	cout << endl << "Testare operator =" << endl << p4 << endl;


	float procente[] = { 2, 3 };
	p4.setProcentRealizare(2, procente);
	cout << endl << "Testare setter" << endl << p4 << endl;

	cout << endl << "Testare getter" << endl;
	p4.getProcentRealizare();

	cout << endl << "Testare metoda" << endl;
	return 0;
}