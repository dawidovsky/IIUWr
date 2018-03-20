#include "Prosta.hpp"
#include <iostream>

using namespace std;

int main()
{
  try
  {
    cout << endl << "  ! Punkt !  " << endl;
    cout << "Punkt domyslny: " << Punkt() << endl;
    cout << "Punkt po wspolrzednych: " << Punkt(1.0,3.0) << endl;
    cout << "Punkt " << Punkt() << " przesuniety o wektor " << Wektor(1.0,1.0)
    << " wynosi: " << Punkt(Punkt(),Wektor(1.0,1.0)) << endl << endl;

    cout << "  ! Wektor !  " << endl;
    cout << "Wektor domyslny: "<< Wektor() << endl;
    cout << "Wektor po wspolrzednych: " << Wektor(2.0, 2.0)<<endl;
    cout << "Zlozenie wektora "<<Wektor(2.0, 2.0) << " oraz " << Wektor(0.0, -2.0)
    <<" wynosi: "<< skladanieWektorow(Wektor(2.0, 2.0),Wektor(0.0, -2.0)) << endl << endl;

    cout << "  ! Prosta !  " << endl;
    cout << "Domyslna prosta: "<<Prosta() << endl;
    cout << "Prosta przechodzaca przez punkt domyslny i punkt "<<Punkt(1.0, 1.0)<<": "
    << Prosta(Punkt(), Punkt(1.0, 1.0))<< endl;

    cout << "Prosta na podstawie wektora:"<< Wektor(1.0, 1.0) <<" i prostopadla do niego: "
    << Prosta(Wektor(1.0, 1.0)) << endl;

    cout << "Prosta na podstawie wspolczynnikow: "<<Prosta(0.0, 0.0, 3.0) << endl;
    cout << "Prosta: "<<Prosta(1.0, 2.0, 3.0)<<" przesunieta o wektor: "<<Wektor(1.0,3.0)
    <<" jest rowna: "<<Prosta(Prosta(1.0, 2.0, 3.0), Wektor(1.0, 3.0))<< endl;

    cout << "Czy prosta " << Prosta(3.0,1.0,1.0) << " jest rownolegla do wektora " << Wektor(1.0,3.0)
    << " : "<< Prosta(3.0,1.0,1.0).czyWektorRownolegly(Wektor(1.0,3.0)) << endl;

    cout << "Czy prosta " << Prosta(4.0,2.0,9.0) << " jest prostopadla do wektora " << Wektor(1.0,3.0)
    << " : "<< Prosta(4.0,2.0,9.0).czyWektorProstopadly(Wektor(1.0,3.0)) << endl;

    cout << "Czy punkt " << Punkt(0.0,-1.0) << " lezy na prostej " << Prosta(1.0,1.0,1.0)
    << " : " << Prosta(1.0,1.0,1.0).czyPunktProsta(Punkt(0.0,-1.0)) << endl;

    cout << "Czy proste " << Prosta(1.0,1.0,1.0) << " i " << Prosta(-1.0,-2.0,2.0) << " sa prostopadle: "
    << czyProstopadle(Prosta(1.0,1.0,1.0),Prosta(-1.0,-2.0,2.0)) << " " << endl;

    cout << "Czy proste " << Prosta(1.0,10.0,15.0) << " i " << Prosta(1.0,-2.0,2.0) << " sa rownolegle: "
    << czyRownolegle(Prosta(1.0,10.0,15.0),Prosta(1.0,-2.0,2.0)) << endl;

    cout << "Proste " << Prosta(1.0,10.0,15.0) << " i " << Prosta(1.0,-2.0,2.0) << " przecinaja sie "
    "w punkcie: " << punktPrzeciecia(Prosta(1.0,10.0,15.0),Prosta(1.0,-2.0,2.0)) << endl;

  }
  catch(invalid_argument &err)
  {
    cerr << err.what() << endl;
  }
}
