//
// Created by student on 12.10.2019.
//
#include <iostream>
#include "../include/zespolona.h"
#include <cmath>


using namespace std;

Complex add(Complex z1,Complex z2)
{
    Complex result;
    result.Re = z1.Re + z2.Re;
    result.Im = z1.Im + z2.Im;
    return result;
}

Complex sub(Complex z1, Complex z2)
{
    Complex result;
    result.Re = z1.Re - z2.Re;
    result.Im = z1.Im - z2.Im;
    return result;
}

Complex mul(Complex z1, Complex z2)
{
    Complex result;
    result.Re = ((z1.Re * z2.Re) - (z1.Im * z2.Im));
    result.Im = ((z1.Re * z2.Im) + (z1.Im * z2.Re));
    return result;
}

Complex div(Complex z1, Complex z2, bool &cond)
{
    Complex result;
	result.Re = 0.0;
	result.Im = 0.0;
    if (((z2.Re * z2.Re) + (z2.Im * z2.Im)) > 0) {
        result.Re = (((z1.Re * z2.Re) + (z1.Im * z2.Im)) / ((z2.Re * z2.Re) + (z2.Im * z2.Im)));
        result.Im = (((z1.Im * z2.Re) - (z1.Re * z2.Im)) / ((z2.Re * z2.Re) + (z2.Im * z2.Im)));
        cond = true;
        return result;
    }
    else {
        cout << "Mianownik musi być większy od 0."<<endl;
        cond = false;
		return result;
    }
}

double abs(Complex z1) {
    double wynikModZ;
    wynikModZ = sqrt((z1.Re * z1.Re) + (z1.Im * z1.Im));
    return wynikModZ;
}

double arg(Complex x)
{
    return atan2(x.Im, x.Re);
}

/*double sin_cos(Complex x, double z, char wybor){
    double wynik=0;
    switch(wybor) {
        case 'c' : {
            //wynik = x.Re / z;
            wynik = cos(arg(x));
            return wynik;
        }
        case 's': {
            //wynik = x.Im / z;
            wynik = sin(arg(x));
            return wynik;
        }
        default: {
            cout<<"Bledny parametr";
        }
    }
}*/
void zad1() {
    Complex l1, l2, tmp;
    char choice;
    bool check;
    cout << "Podaj część rzeczywistą i część urojoną pierwszej liczby: ";
    cin >> l1.Re >> l1.Im;
    cout << "Podaj część rzeczywistą i część urojoną drugiej liczby: ";
    cin >> l2.Re >> l2.Im;
    do{
        /*double zx=abs(l1)*(cos(arg(l1))+sin(arg(l1)));
        cout<<zx<<endl;*/
        cout << endl << "Podaj jaką operacje na liczbach zespolonych z1 = (" << l1.Re << "," << l1.Im << ") i z2 = ("
             << l2.Re << "," << l2.Im << ") chcesz wykonać: "
             << endl << "1.Dodawanie" << endl << "2.Odejmowanie" << endl << "3.Mnożenie"
             << endl << "4.Dzielenie" << endl << "5.Moduły z liczb" << endl << "6.Argumenty z liczb"
             << endl << "Operacja nr: ";
        cin >> choice;
        switch(choice) {
            case '1': {
                tmp = add(l1, l2);
                cout << "z1 + z2 = (" << tmp.Re << ", " << tmp.Im<<"i)"<<endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '2': {
                tmp = sub(l1, l2);
                cout << "z1 - z2 = (" << tmp.Re << ", " << tmp.Im<<"i)"<<endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '3': {
                tmp = mul(l1, l2);
                cout << "z1 * z2 = (" << tmp.Re << ", " << tmp.Im<<"i)"<<endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '4': {
                bool check;
                tmp = div(l1, l2,check);
                if(check) cout << "z1 * z2 = (" << tmp.Re << ", " << tmp.Im<<"i)"<<endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '5':
            {
                cout << "|z1| = " << abs(l1) << endl;
                cout << "|z2| = " << abs(l2) << endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '6':
            {
                cout << "arg z1 = " << arg(l1) << endl;
                cout << "arg z2 = " << arg(l2) << endl;
                cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
                /*case '5': {
                    double modZ, sinX, cosX, z, argw;
                    modZ = modLiczby(l1);
                    cout<<"|z|= "<<modZ<<endl;
                    argw=arg(l1);
                    cout<<"arg(z)"<<argw<<endl;
                    //cosX = sin_cos(l1, modZ, 'c');
                    //sinX = sin_cos(l1, modZ, 's');
                    cosX=cos(argw);
                    sinX=sin(argw);
                    cout<<"cosX: "<<cosX<<"     "<<"sinX: "<<sinX<<endl;
                    z = (modZ * (cosX + sinX));
                    cout<<"'z' = "<<z<<endl;
                    cout << "Czy chcesz wykonac jeszcze raz? [0 - NIE, 1 - TAK]? ";
                    cin >> check;
                    break;
                }*/
            default: {
                cout << "Podałeś złą opcje, spróbuj jeszcze raz!" << endl;
                cin >> choice;
            }
        }
    }while(check);

}
