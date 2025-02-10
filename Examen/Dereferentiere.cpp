#include <iostream>
using namespace std;

int main() {
	int a = 10;
	cout << &a;  //Afiseaza adresa lui a
	cout << endl << a; //Afiseaza valoarea lui a
	
	int* p = &a;
	int& ref = a;  //Daca modficiam referinta se modifica si a-ul
	cout << endl << p; //Afiseaza adresa la care pointeaza p
	cout << endl << *p; //Afiseaza valoarea la care pointeaza p
	cout << endl << ref; //Afiseaza referinta lui a

	ref += 5;
	cout << endl << a;  //Modificam referinta lui a si asa se schimba si valoarea lui a

}