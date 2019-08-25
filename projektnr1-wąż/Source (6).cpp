#include <iostream>
#include <conio.h>												// _getch() i _kbhit()
#include <windows.h>											//system("cls") i Sleep(int x)
#include <time.h>
using namespace std;
const int iloscwierszy = 24;									//Wartosci dla okna 80x25.
const int ilosckolumn = 79;
const int iloscpol = (iloscwierszy-2)*(ilosckolumn - 2);		//Ilosc pol po uwzgl ramki.
void zrobpole(char pole[][ilosckolumn])							//Tworzenie pola gry.
{
	for (int i = 0; i < iloscwierszy; i++)
		for (int j = 0; j < ilosckolumn; j++)
			if (i == 0 || i == iloscwierszy - 1 || j == 0 || j == ilosckolumn - 1)	//Ramka. Jesli chcemy usunac musimy zmienic warunek w 138 linii.
				pole[i][j] = '0';
			else
				pole[i][j] = ' ';
}
void wypis(char pole[][ilosckolumn])							//Wypisywanie calej tablicy z polem.
{
	for (int i = 0; i < iloscwierszy; i++)
	{
		for (int j = 0; j < ilosckolumn; j++)
			cout<<pole[i][j];
		cout << endl;
	}
}
void ruch(char klawisz, char &ruchpop, int &x, int &y)			//W zaleznosci od wybranego kierunku zmieniamy wspolrzedna x lub y.
{
	switch (klawisz)
	{
		case 'w':
		switch (ruchpop)
		{
			case 's':											//Zabezpieczenie na "zawracanie" weza.
			y++;
			ruchpop = 's';
			break;
			default:
			y--;
			ruchpop = 'w';
		}
		break;
		case 'a':
		switch (ruchpop)
		{
			case 'd':											//Zabezpieczenie na "zawracanie" weza.
			x++;
			ruchpop = 'd';
			break;
			default:
			x--;
			ruchpop = 'a';
		}
		break;
		case 's':
		switch (ruchpop)
		{
			case 'w':											//Zabezpieczenie na "zawracanie" weza.
			y--;
			ruchpop = 'w';
			break;
			default:
			y++;
			ruchpop = 's';
		}
		break;
		case 'd':
		switch (ruchpop)
		{
			case 'a':											//Zabezpieczenie na "zawracanie" weza.
			x--;
			ruchpop = 'a';
			break;
			default:
			x++;
			ruchpop = 'd';
		}
		break;
	}
}
void jedzenie(char pole[][ilosckolumn])
{
	int xj, yj;
	do {
		xj = (rand() % (ilosckolumn-2)) + 1;					//Losowanie miejsca umieszczenia jedzenia (z uwzgl. ramki).
		yj = (rand() % (iloscwierszy-2)) + 1;
	} while (pole[yj][xj] == 'o');								//Zabezpieczenie na wylosowanie "w wezu".
	pole[yj][xj] = '*';
}
void przesuntab(char tabruchow[], int dlugosc)					//Przesuniecie wartosci o 1 w prawo. pierwsza wartosc zostaje na swoim miejscu.
{
	for (int i = dlugosc - 1; i > 0; i--)
		tabruchow[i] = tabruchow[i - 1];
}
int main()
{
	srand(time(NULL));
	int dlugosc = 5;										//Waz na poczatku ma dlugosc 5.
	int xp = 6, xk = xp - dlugosc + 1, yp = 3, yk = 3;		//Zaczynamy od wspolrzednych (3,6) dla glowy i (3,2) dla ogona (w,k).
	char klawisz;
	char tabruchow[iloscpol];
	char pole[iloscwierszy][ilosckolumn];
	zrobpole(pole);
	for (int i = 0; i < dlugosc; i++)						//Zaczynamy ruchem w prawo.
		tabruchow[i] = 'd';
	char ruchpop = tabruchow[0];
	char ruchpopk = tabruchow[dlugosc - 1];
	bool zjadl = false, koniec = false, nieprzep = false;
	int wynik = 0;
	for (int i = xk; i < xp + 1; i++)						//Umieszczenie poczatkowego weza w polu.
		for (int j = yp; j < yk + 1; j++)
			pole[j][i] = 'o';
	cout << "Witaj w grze Waz" << endl;
	cout << "Sterowanie:" << endl;
	cout << "w - do gory" << endl;
	cout << "s - w dol" << endl;
	cout << "a - w lewo" << endl;
	cout << "d - w prawo" << endl;
	cout << "UWAGA! Wyjscie poza ramke powoduje koniec gry!" << endl;
	cout << "Wcisnij dowolny przycisk, aby kontynuowac.";
	_getch();													//Pobiera jeden znak i przechodzi dalej. Znajduje siê w pliku nag³ówkowym <conio.h>
	system("cls");												//Odswiezanie ekranu konsoli. Znajduje sie w pliku naglowkowym <windows.h>
	jedzenie(pole);												//Umieszczenie jedzenia.
	wypis(pole);												//Wypis aktualnego polozenia elementow.
	Sleep(250);
	do {
		system("cls");											//Odswiezanie ekranu powoduje "miganie".
		if (_kbhit())											//Sprawdza, czy w buforze klawiatury sa jakies znaki (czy byl wcisniety klawisz).
			klawisz = _getch();									//Jezeli tak, to pobiera.
		else
			klawisz = ruchpop;									//Jezeli nie - idzie tak jak wczesniej.
		if (klawisz > 64 && klawisz < 91)						//Zabezpieczenie na rozna wielkosc liter.
			klawisz = klawisz + 32;
		if (klawisz != 'a' && klawisz != 'd' && klawisz != 's' && klawisz != 'w')	//Zabezpieczenie na inne znaki niz w,a,s, lub d.
			klawisz = ruchpop;
		przesuntab(tabruchow, dlugosc);							//Umozliwienie zapamietania aktualnego ruchu.
		ruch(klawisz, ruchpop, xp, yp);							//Przesuniecie wspolrzednych "glowy" weza.
		if (xp == 0 || xp == ilosckolumn - 1 || yp == iloscwierszy - 1 || yp == 0)		//Zabezpieczenie na najechanie na ramke.
			koniec = true;
		else
		{
			tabruchow[0] = ruchpop;								//Zapamietanie kolejnosci ruchow.
			switch (pole[yp][xp])								//Co zrobic gdy "glowa" napotka na czesc weza, jedzenie, lub puste pole. 
			{
				case 'o' :
				if (xk != xp || yk != yp)						//Uwzglednienie, ze narazie przesunieta jest "glowa", lecz nie "ogon".
					koniec = true;
				nieprzep = true;								//Zabezpieczenie na puste miejsca w wezu.
				break;
				case '*':
				zjadl = true;									//Pod wplywem jedzenia roznie od razu.
				dlugosc++;
				if (dlugosc == iloscpol)						//Zabezpieczenie na najdluzszego mozliwego weza.
					koniec = true;
				wynik++;
				pole[yp][xp] = 'o';
				break;
				default:
				pole[yp][xp] = 'o';								//Zwykle przesuniecie.
			}
			if (!zjadl)											//W przypadku zjedzenia ogon nieprzesuniety, bo waz od razu sie wydluzyl.
			{
				if(!nieprzep)									//Zabezpieczenie na wypadek glowy weza tuz za ogonem.
					pole[yk][xk] = ' ';
				ruch(tabruchow[dlugosc - 1], ruchpopk, xk, yk); //Przesuniecie "ogona".
			}
			else
				jedzenie(pole);									//Wylosowanie nowego polozenia jedzenia.
			zjadl = false;										//Odswierzenie informacji o zjedzeniy i polozeniu obok ogona dla nowego ruchu.
			nieprzep = false;
			if (!koniec)										//Jezeli gra skonczona (przed wyjsciem lub zjedzeniem siebie) to nie wypisujemy.
				wypis(pole);
		}
		Sleep(250);
	} while (!koniec);
	cout << "Twoj wynik to: " << wynik << endl;
	cout << "Wcisnij dowolny przycisk aby zakonczyc.";
	_getch();													//Przy getch() i kbhit() kompilator prosi o dodanie do ich nazwy "_" na poczatku.
	return 1;
}