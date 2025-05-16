#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

struct student{
    std::string imie;
    std::string nazwisko;
    int Punkty;
};

void wczytajStudentow(student *&tab, int liczba_studentow){
    tab = new student[liczba_studentow];
    std::ifstream plik;
    std::string nazwaPliku = "studenci.csv";
    plik.open(nazwaPliku);
    if(!plik.is_open()){
        std::cout << "Nie udalo sie otworzyc pliku\n";
        return;
    }

    char sredniki;
    for(int i=0; i<2; i++){
        plik >> sredniki;
    }
    std::string linia, pomoc;
    std::stringstream ss(linia);
    for(int i=0; i<liczba_studentow; i++){
        plik>> linia;
        std::stringstream ss(linia);
        std::getline(ss, tab[i].imie, ';');
        std::getline(ss, tab[i].nazwisko, ';');
        std::getline(ss, pomoc);
        tab[i].Punkty = std::atoi(pomoc.c_str());
    }


    plik.close();


}

void wyswietlStudentow(student *tab, int liczba_studentow){
    std::cout << "Imie\tNazwisko\tPunkty\n";
    for(int i=0; i<liczba_studentow; i++){
        std::cout << tab[i].imie << "\t" << tab[i].nazwisko << "\t" << tab[i].Punkty << "\n";
    }
}

void podzielNaDwieCzesci(student *tab, int liczba_studentow){
    int warunek = 10;

    student *tab1 = new student[liczba_studentow];
    student *tab2 = new student[liczba_studentow];
    int liczba1 = 0, liczba2 = 0;

    for(int i=0; i<liczba_studentow; i++){
        if(tab[i].Punkty <= warunek){
            tab1[liczba1] = tab[i];
            liczba1++;
        }
        else{
            tab2[liczba2] = tab[i];
            liczba2++;
        }
    }

    std::cout << "1. Czesc Tablicy: (Studenci ktorzy otrzymali <= 10 punktow) \n";
    wyswietlStudentow(tab1, liczba1);
    std::cout << "2. Czesc Tablicy: (Studenci ktorzy otrzymal >10 punktow)\n";
    wyswietlStudentow(tab2, liczba2);

    for(int i=0; i<liczba1; i++){
        tab[i] = tab1[i];
    }

    for(int i=liczba1; i<liczba_studentow; i++){
        tab[i] = tab2[i-liczba1];
    }

    delete[] tab1;
    delete[] tab2;
}

void podzielNaTrzyCzesci(student *tab, int liczba_studentow){
    int warunek = 3;
    student *tab1 = new student[liczba_studentow];
    student *tab2 = new student[liczba_studentow];
    student *tab3 = new student[liczba_studentow];
    int liczba1 = 0, liczba2 = 0, liczba3 = 0;

    for(int i=0; i<liczba_studentow; i++){
        if(tab[i].Punkty % warunek == 0){
            tab1[liczba1] = tab[i];
            liczba1++;
        }
        else if(tab[i].Punkty % warunek == 1){
            tab2[liczba2] = tab[i];
            liczba2++;
        }
        else{
            tab3[liczba3] = tab[i];
            liczba3++;
        }
    }

    std::cout << "1. Czesc Tablicy: (Studenci ktorzy otrzymali punkty podzielne przez 3) \n";
    wyswietlStudentow(tab1, liczba1);
    std::cout << "2. Czesc Tablicy: (Studenci ktorzy otrzymali punkty podzielne przez 3 z reszta 1)\n";
    wyswietlStudentow(tab2, liczba2);
    std::cout << "3. Czesc Tablicy: (Studenci ktorzy otrzymali punkty podzielne przez 3 z reszta 2)\n";
    wyswietlStudentow(tab3, liczba3);
    for(int i=0; i<liczba1; i++){
        tab[i] = tab1[i];
    }

    for(int i=liczba1; i<liczba_studentow; i++){
        if(i < liczba1 + liczba2){
            tab[i] = tab2[i-liczba1];
        }
        else{
            tab[i] = tab3[i-liczba1-liczba2];
        }
    }

    delete[] tab1;
    delete[] tab2;
    delete[] tab3;

}

void usunStudentow(student *&tab){
    delete[] tab;
    tab = nullptr;
}

int main(){
    std::string nazwa_pliku;
    int liczba_studentow;
    std::ifstream plik;
    student *tab = nullptr;
    nazwa_pliku="studenci.csv";
    int wybor;
    do{
        std::cout << "1. Wczytaj studentow z pliku\n";
        std::cout << "2. Podział na 2 części\n";
        std::cout << "3. Podział na 3 części\n";
        std::cout << "4. Wyjdz\n";
        std::cin >> wybor;

        if(wybor==1){
            plik.open(nazwa_pliku);
            if(!plik.is_open()){
                std::cout << "Nie udalo sie otworzyc pliku\n";
                return 1;
            }
            plik >> liczba_studentow;
            wczytajStudentow(tab, liczba_studentow);
        }
        else if(wybor==2){
            if(tab == nullptr){
                std::cout << "Nie wczytano studentow\n";
                continue;
            }
            std::cout<< "Studenci przed podziałem:\n";
            wyswietlStudentow(tab, liczba_studentow);
            podzielNaDwieCzesci(tab, liczba_studentow);
            std::cout<< "Studenci po podziale:\n";
            wyswietlStudentow(tab, liczba_studentow);


            // Podział na 2 części
        }

        else if(wybor==3){
            if(tab == nullptr){
                std::cout << "Nie wczytano studentow\n";
                continue;
            }
            std::cout<< "Studenci przed podziałem:\n";
            wyswietlStudentow(tab, liczba_studentow);
            podzielNaTrzyCzesci(tab, liczba_studentow);
            std::cout<< "Studenci po podziale:\n";
            wyswietlStudentow(tab, liczba_studentow);
            // Podział na 3 części
        }
        else if(wybor==4){
            std::cout << "Koniec programu\n";
            if(tab != nullptr){
                usunStudentow(tab);
            }
        }
        else{
            std::cout << "Niepoprawny wybor, sprobuj ponownie\n";
        }
    }while(wybor!=4);

return 0;}