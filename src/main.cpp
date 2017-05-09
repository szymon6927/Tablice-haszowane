#include<iostream>
#include <cstring>

using namespace std;

const unsigned int tablica_rozmiar = 839;

struct Dane
{
	Dane(const char* od_k, const char* do_k, int wartosc) : wartosc(wartosc) {
		 int i = 0;
		 do {
			 od_kogo[ i ] = *od_k;
			 i++ ;
		 } while (*od_k++);

		 i = 0;
		 do {
			 do_kogo[ i ] = *do_k;
			 i++ ;
		 } while (*do_k++);
	}

	Dane() {}

	int wartosc;
	char od_kogo[18]; // 18 bo 16 znak _ i koniec "\0"
	char do_kogo[18];
};

struct Wezel
{
	Dane dane;
	Wezel* nastepny;
};

class Lista
{
public:
	Lista() : glowa(nullptr) { }
	~Lista() { czysc_liste(); }

	Wezel *glowa;

	bool czy_pusta() {
		return glowa == nullptr;
	}

	void czysc_liste() {
		if (czy_pusta()) {
			return;
		}

		Wezel *temp = glowa;
		Wezel *temp1;
		while(temp != nullptr)
		{
		  temp1 = temp->nastepny;
		  delete temp;
		  temp = temp1;
		}
//		do {
//			temp1 = temp->nastepny;
//			delete temp1;
//			temp = temp1;
//		} while (temp != nullptr);

	}
	void wstaw(Dane& dane) {
		Wezel *nowy;
		nowy = new Wezel;
		nowy->dane.wartosc = dane.wartosc;
		moj_strcpy(nowy->dane.od_kogo ,dane.od_kogo);
		moj_strcpy(nowy->dane.do_kogo ,dane.do_kogo);
		nowy->nastepny = glowa;
		glowa = nowy;
	}
	void moj_strcpy(char *d, char *s) {
	   while ((*d++ = *s++) != '\0');
	}
};

class HashTablica {
private:
	Lista tablica[tablica_rozmiar];
public:
	HashTablica() {}
	~HashTablica() {}

	unsigned int funkcja_haszujaca(const char* od_kogo, const char* do_kogo) {
		unsigned int poczatek = 0;
		unsigned int hash = poczatek;

		while (*od_kogo) {
			hash = hash * 101 + *od_kogo++;
		}

		while (*do_kogo) {
			hash = hash * 101 + *do_kogo++;
		}

//		cout << hash % tablica_rozmiar << "\n";
		return hash % tablica_rozmiar;
	}

	bool moj_strcmp(char *src1, char *src2)
	{
	    int i = 0;
	    while((src1[i]!='\0') && (src2[i]!='\0'))
	    {
	        if(src1[i] > src2[i] || src1[i] < src2[i])
	            return false;
	        i++;
	    }
	    return true;
	}

	void wstaw(Dane& dane) {
//		cout << "Wstaw z hashtable: " << dane.od_kogo << "  " << dane.do_kogo << "\n";
		int key = funkcja_haszujaca(dane.od_kogo, dane.do_kogo);

		Wezel *temp = tablica[key].glowa;
		while (temp != nullptr)
		{
//			cout << dane.od_kogo << " : " << temp->dane.od_kogo << "\n";
			if (moj_strcmp(dane.od_kogo, temp->dane.od_kogo) && moj_strcmp(dane.do_kogo, temp->dane.do_kogo)) {
//				cout << "sa takie same \n";
				break;
			}
			temp = temp->nastepny;
		}
		if (temp == nullptr) {
			//wstawaimy bo lista pusta
			tablica[key].wstaw(dane);
//			cout << "wstawiam \n";
		}
		else {
			//sumujemy bo dwa elementy o tym samym kluszu
			temp->dane.wartosc = dane.wartosc + temp->dane.wartosc;
//			cout << "Wartosc " << temp->dane.wartosc << "\n";
		}
	}

	void wyswietl_przelew(char* od_kogo, char* do_kogo) {
		int key = funkcja_haszujaca(od_kogo, do_kogo);
//		cout << "hash z przelew " << key << "\n";

		Wezel *temp = tablica[key].glowa;
		while (temp != nullptr)
		{
			if (moj_strcmp(od_kogo, temp->dane.od_kogo) && moj_strcmp(do_kogo, temp->dane.do_kogo)) {
				break;
			}
			temp = temp->nastepny;
		}
		if (temp == nullptr) {
			cout << "0\n";
		}
		else {
			cout << temp->dane.wartosc << "\n";
		}
	}

};


int main()
{
	HashTablica htablica;

	char znak;
	int wartosc;
	char od_kogo[18]; // 18 bo 16 znak _ i koniec "\0"
	char do_kogo[18];

	while (cin >> znak) {


		if (znak == '+') {
			cin >> ws;
			cin >> od_kogo;
			cin >> ws;
			cin >> do_kogo;
			cin >> ws;
			cin >> wartosc;
			Dane dane(od_kogo, do_kogo, wartosc);
			htablica.wstaw(dane);
		}
		else if (znak == '?') {
			cin >> ws;
			cin >> od_kogo;
			cin >> ws;
			cin >> do_kogo;
			htablica.wyswietl_przelew(od_kogo, do_kogo);
		}

	}

    return 0;
}
