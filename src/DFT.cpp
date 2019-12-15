//
// Created by Dominik Cegiełka <224478@edu.p.lodz.pl> on 09.12.2019.
//

#include "../include/DFT.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "../libs/matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

double *load_data(int &N)
{
    cout << "Podaj liczbe probek ciagu wejsciowego/punktow czestotliwosci: ";
    cin >> N;
    double *x = new double[N];
    cout<<"Wczytywanie probek."<<endl;
    for (int n = 0; n < N; ++n) {
        cout<<"Podaj x["<<n<< "]: ";
        cin>>x[n];
    }
    return x;
}

void IDFT_print(double* x, int N)
{
    vector<double> tab_x(N), tab_y;
    for (int i = 0; i < N; i++) {
        if (abs(x[i]) < 0.00000000001) x[i]= round(x[i]);
        if (abs(x[i]) < 0.00000000001) x[i]= round(x[i]);
        cout << x[i] << ", ";
        tab_y.push_back(x[i]);
    }
    cout<<endl;
    iota(tab_x.begin(),tab_x.end(),1);
    plt::plot(tab_x,tab_y);
    plt::xlabel("Time [s]",{});
    plt::ylabel("Amplitude",{});

}

void DFT_print(Complex* X, double* x, int N)
{
    vector<double> tab_x(N), tab_y, tab_x_re, tab_x_im, tab_org_y;
    for (int i = 0; i < N; i++) {
        if (abs(X[i].Re) < 0.00000000001) X[i].Re = round(X[i].Re);
        if (abs(X[i].Im) < 0.00000000001) X[i].Im = round(X[i].Im);
        cout << "[" << X[i].Re << "," << X[i].Im << "], ";
        tab_y.push_back(sqrt(pow(X[i].Re,2)+pow(X[i].Im,2)));
        tab_x_re.push_back(X[i].Re);
        tab_x_im.push_back(X[i].Im);
        tab_org_y.push_back(x[i]);
    }
    cout<<endl;
    iota(tab_x.begin(),tab_x.end(),1);
    plt::figure_size(1920, 520);

    plt::subplot(1,3,1);
    plt::title("Time Domain Signal");
    plt::named_plot("",tab_x,tab_org_y);
    plt::xlabel("Time [s]",{});
    plt::ylabel("Amplitude",{});

    plt::subplot(1,3,2);
    plt::scatter(tab_x,tab_y,20.0,{});
    plt::title("DFT");
    plt::xlabel("Frequency [Hz]",{});
    plt::ylabel("Amplitude",{});

    plt::subplot(1,3,3);
    plt::title("Real and Imaginary Part of X");
    plt::named_plot("X.IM",tab_x,tab_x_im);
    plt::named_plot("X.RE",tab_x,tab_x_re);
    plt::xlabel("Frequency [Hz]",{});
    plt::ylabel("Amplitude",{});
    plt::legend();
}

Complex *DFT(int N, double *x)
{
    Complex *X = new Complex[N];
    for (int k = 0; k < N; ++k) {
        X[k].Re = 0;
        X[k].Im = 0;
        for (int n = 0; n < N ; ++n) {
            X[k].Re += x[n] * cos(n * k * 2 * M_PI / N);
            X[k].Im -= x[n] * sin(n * k * 2 * M_PI / N);
        }
    }
    return X;
}

double *inverse_DFT(int N, Complex *X)
{
    double *x = new double[N];
    for (int k = 0; k < N; ++k) {
        x[k] = 0;
        for (int n = 0; n < N ; ++n) {
            x[k] += X[n].Re * cos(n * k * 2 * M_PI / N);
            x[k] -= X[n].Im * sin(n * k * 2 * M_PI / N);
        }
        x[k] /= N;
    }
    return x;
}

void zad4()
{
    /*int N =  8;
    double *x = new double[N]{0,0.7,1,0.7,0,-0.7,-1,-0.7};*/
    int N = 16;
    double *x = new double[N]{0.672957, -0.453061, -0.835088, 0.980334,
                              0.972232, 0.640295,0.791619,-0.042803,
                              0.282745, 0.153629, 0.939992, 0.588169,
                              0.189058, 0.461301, -0.667901, -0.314791 };
   /* int N;
    double *x = load_data(N);*/
    Complex *X;
    bool check;
    char choice;
    do
    {
        cout << "Wybierz operacje, ktora chcesz wykonac: \n"
             << "1.DFT \n2.IDFT \n3.Wczytaj nowe próbki \n4.Wyjdz"
             <<"\nOperacja nr: ";
        cin >> choice;
        switch(choice) {
            case '1' : {
                X = DFT(N,x);
                DFT_print(X, x, N);
                plt::show();
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '2': {
                double *inverseX = inverse_DFT(N,X);
                plt::title("Inverse DFT Signal");
                IDFT_print(inverseX, N);
                plt::show();
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '3': {
                x = load_data(N);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case '4': {
                check = false;
                break;
            }
            default: {
                cout << "Podałeś złą opcje, spróbuj jeszcze raz!" << endl;
                cin >> choice;
            }
        }
    } while (check);
    delete [] x;
}