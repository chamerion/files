#include <iostream>
#include <limits>

using namespace std;

void pobierz(int A[], int a){
  for(int i=0; i<a; i++)
    cin >> A[i];
}

void wypisz(int A[], int N){
  for(int i=0; i<N; i++)
    cout << A[i] << " ";

  cout << endl;
}

int* TablicaDuzych(int A[], int a, int& b){
  // A - tablica liczb calkowitych dlugosci a; 
  // b - dlugosc nowej tablicy B, przekazana przez referencje.

  // Rozwiazanie polega na zliczeniu a nastepnie przepisaniu
  // tych elementow A[i], ktore sa wieksze lub rowne
  // niz maksimum z A[0, ..., i- 1]. Warto pamietac, ze maksimum
  // zbioru pustego to -oo. 
  // Petla jednokrotna; czas dzialania O(a).
  
  /* Obliczamy dlugosc nowej tablicy B. */
  b = 0;
  
  // maks ustawiamy na "-oo", czyli najmniejsza mozliwa wartosc w typie int.
  int maks = numeric_limits<int>::min();

  // Jesli a > 0, to mozna tez przyjac maks = A[0].

  for(int i=0; i<a; i++)
    if(A[i] >= maks){
      // Element zostanie przepisany do tablicy wtedy, gdy wyniesie
      // co najmniej tyle ile dotychczasowy maks. Ze wzgledu na wybor 
      // wartosci startowej dla maks, element pierwszy zostanie przepisany
      // na pewno.
      maks = A[i];
      b++;
    }
  
  /* Deklaracja nowej tablicy B dlugosci b. */
  int* B = new int[b];

  /* Zapelniamy B wartosciami. */

  // B wymaga wlasnego indeksu.
  int j = 0;

  // Powtornie biegniemy przez A i tak samo jak wyzej sprawdzamy, 
  // ktore elementy przepisac do B. Tym razem faktycznie je przepisujemy,
  // gdyz teraz mamy gdzie.
  maks = numeric_limits<int>::min();

  for(int i=0; i<a; i++)
    if(A[i] >= maks){
      maks = A[i];
      B[j] = A[i];
      j++;
    }

  /* Zwracamy gotowa tablice B */
  return B;
}

int* NajdluzszaPodtablicaWiekszychPodwojona(int A[], int a, int G, int& b){
  // A - tablica liczb calkowitych dlugosci a; 
  // G - liczba calkowita pochodzaca z tresci zadania;
  // b - dlugosc nowej tablicy B, przekazana przez referencje.

  // Rozwiazanie wykorzystuje nastepujaca prosta obserwacje: 
  // fragmenty z wartosciami <= G wystepuja naprzemiennie 
  // z fragmentami, w ktorych wartosci sa > G.
  // Petla jednokrotna; czas dzialania O(a).

  /* Obliczanie dlugosci. */

  // Poczatek maksymalnego fragmentu.
  int start;

  // Poczatek i koniec fragmentu badanego w danej chwili. Znalezienie maksymalnego
  // fragmentu wymaga zaledwie jednego przebiegu przez A, dlatego juz teraz mozna ustawic
  // i na 0. Zmienna j wymaga odswiezenia po kazdej zmianie i.
  int j, i = 0;

  // Zmienna maks przechowuje dlugosc najdluzszego jak dotad fragmentu o wartosciach > G.
  // Mozna ja bezpiecznie ustawic na 0, gdyz jest to najmniejsza mozliwa dlugosc. 
  int maks = 0;


  while(i < a){

    // Pomijamy fragment (byc moze pusty) z wartosciami <= G.
    // Iterowanie konczymy, gdy A[i] > G, lub gdy wyjdziemy poza tablice.
    // Nierownosc i < a warto sprawdzac jako pierwsza, bo jesli okaze sie, ze
    // i >= a, to nierownosc A[i] <= G nie bedzie juz sprawdzana (bo nie ma po co,
    // koniunkcja i tak jest juz falszywa). Dzieki temu nie testujemy wartosci
    // poza zarezerwowana pamiecia.
    while(i < a && A[i] <= G) i++;

    // Czas na fragment z wartosciami >=G. Jego poczatek
    // zapamietujemy w zmiennej j.
    j = i;
    while(i < a && A[i] > G) i++;

    // Tu warto zauwazyc, ze teraz albo i == a, albo i < a i A[i] > G. 
    // W tym drugim przypadku i == j dokladnie wtedy, gdy fragment jest pusty.
    // Tak czy siak, i jest pozycja za fragmentem a jego dlugosc jest rowna i - j.

    // Sprawdzamy, czy nowy fragment ma dlugosc wieksza
    // niz wszystkie poprzednie. Jesli tak, zapamietujemy jego poczatek.
    // Gdy pod if damy i - j > maks, to zapamietamy pierwszy 
    // maksymalny frgament, gdy i - j >= maks, to ostatni. 
    if(i - j > maks){
      start = j;
      maks = i - j;
    }
  }

  /* Deklaracja nowej tablicy. */
  // W stalej N przechowujemy liczbe powtorzen.
  const int N = 2;
  b = N * maks;
  int* B = new int[b];

  /* Przepisanie wartosci. */
  for(int i=0; i<b; i++){
    
    // Przepisujemy z zawijaniem indeksow. 
    B[i] = A[start + i % maks];
  }

  /* Zwracamy gotowa tablice B */
  return B;
}

int main(){
  int a, b, b1, G;
  int* B;
  int* B1;

  cout << "Rozmiar A: "; cin >> a;
  int A[a];
  pobierz(A, a);
  wypisz(A, a);

  B = TablicaDuzych(A, a, b);
  cout << "\nB[]:\n";
  wypisz(B, b);

  cin >> G;
  B1 = NajdluzszaPodtablicaWiekszychPodwojona(A, a, G, b1);
  cout << "\nB1[]:\n";
  wypisz(B1, b1);

  return 0;
}