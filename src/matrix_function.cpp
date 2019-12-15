//
// Created by student on 18.11.2019.
//
#include <iostream>
#include <iomanip>
#include "../include/matrix_function.h"

using namespace std;

double **create_matrix(int &rows, int &cols)
{
    cout<<"Podaj rozmiar macierzy:";
    cin >> rows >> cols;
    double **tab = new double *[rows];
    for (int i = 0; i < rows; i++) {
        tab[i] = new double[cols];
        for (int j = 0; j < cols; j++) {
            cout << "Podaj liczbe [" << i << "," << j << "]: ";
            cin >> tab[i][j];
        }
    }
    return tab;
}

void remove_matrix(int rows, double **matrix)
{
    for (int i = 0; i < rows; ++i) {
        delete [] matrix[i];
    }
    delete [] matrix;
}

void print_matrix(int rows, int cols, double **matrix)
{
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << setw(8)<<matrix[i][j] << " ";
        }
        cout << endl;
    }
}

double **add_matrix(int rows,int cols, double **matrix1, double **matrix2)
{
    double **result = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        result[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;

}

double **sub_matrix(int rows,int cols, double **matrix1, double **matrix2)
{
    double **result = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        result[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

double **mul_sc_matrix(int rows,int cols, double **matrix, double scalar)
{
    double **result = new double *[rows];
    for (int i = 0; i < rows; ++i) {
        result[i] = new double[cols];
        for (int j = 0; j < cols; ++j) {
            result[i][j] = matrix[i][j] * scalar;
        }
    }
    return result;
}

double **mul_matrix(int rows1, int cols2 , int cols1,  double **matrix1, double **matrix2)
{
    //rows1; cols2; cols1;
    double **result = new double *[rows1];
    for (int i = 0; i < rows1; ++i) {
        result[i] = new double[cols2];
        for (int j = 0; j < cols2; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < cols1; ++k) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

double **trans_matrix(int rows, int cols, double **matrix)
{
    double **matrixT = new double *[cols];
    for (int i = 0; i < cols; i++) {
        matrixT[i] = new double[rows];
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrixT[j][i] = matrix[i][j];
        }
    }
    return matrixT;
}

void getMinor(double **matrix, double **matrixTemp, int outRow, int outCol, int n) {
    int x = 0, y = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != outRow && j != outCol) {
                matrixTemp[x][y] = matrix[i][j];
                y++;
                if (y == n - 1) {
                    y = 0;
                    x++;
                }
            }
        }
    }
}

double det(double **matrix, int n)
{
    double sum = 0;
    int multiplier = 1;
    double **matrixTemp = new double *[n];
    for (int i = 0; i < n; i++) {
        matrixTemp[i] = new double[n];
    }
    if(n == 1){
        remove_matrix(n - 1, matrixTemp);
        return matrix[0][0];
    }
    
    for (int i = 0; i < n; i++) {
        getMinor(matrix, matrixTemp, 0, i, n);
        
        sum += multiplier * matrix[0][i] * det(matrixTemp, n - 1);
        multiplier *= -1;
    }
    remove_matrix(n - 1, matrixTemp);
    return sum;
}

double **adjugateMatrix(double **matrix, int n)
{
    int multiplier = 1;
    double **result = new double *[n];
    double **temp = new double *[n];
    for (int i = 0; i < n; i++) {
        result[i] = new double[n];
        temp[i] = new double[n];
    }

    if (n == 1) {
        remove_matrix(n,temp);
        result[0][0] = 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            getMinor(matrix, temp, i, j, n);

            if ((i + j) % 2 == 0) multiplier = 1;
            else
                multiplier = -1;

            result[j][i] = multiplier * (det(temp, n - 1));
        }
    }
    remove_matrix(n,temp);
    return result;
}

void zad3()
{
    bool check;
    double **matrix_temp;
    int rows1, cols1, rows2, cols2, rowstemp = 1, colstemp = 1;
    cout << "Wczytywanie pierwszej macierzy" << endl;
    double **matrix1 = create_matrix(rows1, cols1);
    cout << "Wczytywanie drugiej macierzy" << endl;
    double **matrix2 = create_matrix(rows2, cols2);
    int choice;
    do
    {
        cout << "Wybierz operacje na macierzach, ktora chcesz wykonac: \n"
             << "1.Dodaj macierze \n2.Odejmnij macierze \n3.Mnozenie przez skalar \n4.Mnozenie macierzy "
                "\n5.Transponowanie macierzy \n6.Wyznacznik macierzy \n7.Macierz dopełnień algebraicznych "
                "\n8.Macierz dołączona \n9.Macierz odwrotna \n10.Wczytaj macierze \n11.Wypisz macierze \n12.Wyjdz"
             <<"\nOperacja nr: ";
        cin >> choice;
        switch(choice) {
            case 1 : {
                if(rows1 == rows2 && cols1 == cols2) {
                    rowstemp = rows1;
                    colstemp = cols1;
                    print_matrix(rowstemp, colstemp, matrix1);
                    cout<<"\t + "<<endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    cout<<"\t = "<<endl;
                    matrix_temp = add_matrix(rowstemp, colstemp, matrix1, matrix2);
                    //cout<<"Wynik dodawania macierzy"<<endl;
                    print_matrix(rowstemp, colstemp, matrix_temp);
                } else cout << "Macierze musza miec jednakowy rozmiar!" << endl;
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 2: {
                if(rows1 == rows2 && cols1 == cols2) {
                    rowstemp = rows1;
                    colstemp = cols1;
                    print_matrix(rowstemp, colstemp, matrix1);
                    cout<<"\t - "<<endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    cout<<"\t = "<<endl;
                    matrix_temp = sub_matrix(rowstemp, colstemp, matrix1, matrix2);
                    //cout<<"Wynik odejmowania macierzy"<<endl;
                    print_matrix(rowstemp, colstemp, matrix_temp);
                } else cout << "Macierze musza miec jednakowy rozmiar!" << endl;
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 3: {
                char wybor;
                cout << "Wybierz macierz ktora chcesz pomnozyc [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin>>wybor;
                if(wybor == '1')
                {
                    rowstemp = rows1;
                    colstemp = cols1;
                    print_matrix(rowstemp, colstemp, matrix1);
                    double scalar;
                    cout<<"Podaj skalar:";
                    cin>>scalar;
                    matrix_temp = mul_sc_matrix(rowstemp, colstemp, matrix1,scalar);
                    cout << "Wynik mnozenia macierzy pierwszej przez skalar" << endl;
                    print_matrix(rowstemp, colstemp, matrix_temp);
                } else if(wybor == '2')
                {
                    rowstemp = rows2;
                    colstemp = cols2;
                    double scalar;
                    cout<<"Podaj skalar:";
                    cin>>scalar;
                    matrix_temp = mul_sc_matrix(rowstemp, colstemp, matrix2, scalar);
                    cout << "Wynik mnozenia macierzy drugiej przez skalar" << endl;
                    print_matrix(rowstemp, colstemp, matrix_temp);
                } else cout << "Bledny wybor macierzy!";
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 4 : {
                if(cols1 == rows2)
                {
                    rowstemp = rows1;
                    colstemp = cols2;
                    matrix_temp = mul_matrix(rowstemp, colstemp, cols1, matrix1, matrix2); //rowstemp = rows1; colstemp = cols2
                    cout << "Wynik mnozenia macierzy" << endl;
                    print_matrix(rowstemp, colstemp, matrix_temp);
                } else cout << "Macierzy nie mozna pomnozyc! \nLiczba kolumn pierwszej macierzy musi byc rowna liczbe wierszy drugiej macierzy."<<endl;
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 5: {
                char wybor;
                cout << "Wybierz macierz ktora chcesz transponowac [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin >> wybor;
                if(wybor == '1')
                {
                    rowstemp = rows1;
                    colstemp = cols1;
                    cout << "Macierz przed transponowaniem" << endl;
                    print_matrix(rowstemp, colstemp, matrix1);
                    matrix_temp = trans_matrix(rowstemp, colstemp, matrix1);
                    cout << "Macierz po transponowaniu" << endl;
                    print_matrix(colstemp, rowstemp, matrix_temp);
                }
                else if(wybor == '2')
                {
                    rowstemp = rows2;
                    colstemp = cols2;
                    cout << "Macierz przed transponowaniem" << endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    matrix_temp = trans_matrix(rowstemp, colstemp, matrix2);
                    cout << "Macierz po transponowaniu" << endl;
                    print_matrix(colstemp, rowstemp, matrix_temp);
                } else cout << "Bledny wybor macierzy!" << endl;

                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 6: {
                double detMatrix;
                char wybor;
                cout<< "Wybierz dla której macierzy chcesz obliczyć wyznacznik  [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin >> wybor;
                if (wybor == '1') {
                    rowstemp = rows1;
                    colstemp = cols1;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix1);
                    cout<<endl;
                    if (rowstemp == colstemp) {
                        detMatrix = det(matrix1,rowstemp);
                        cout << "Wyznacznik macierzy: " << detMatrix << endl;
                    } else cout << "Macierz nie jest kwadratowa!" << endl;

                } else if (wybor == '2') {
                    rowstemp = rows2;
                    colstemp = cols2;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    if (rowstemp == colstemp) {
                        detMatrix = det(matrix2,rowstemp);
                        cout << "Wyznacznik macierzy:" << detMatrix << endl;
                    } else cout << "Macierz nie jest kwadratowa!" << endl;
                } else cout << "Bledny wybor macierzy!" << endl;

                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 7:{
                char wybor;
                cout<< "Wybierz dla której macierzy chcesz obliczyć macierz dopełnień algebraicznych [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin >> wybor;
                if (wybor == '1') {
                    rowstemp = rows1;
                    colstemp = cols1;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix1);
                    cout<<endl;
                    if (rowstemp == colstemp) {
                        matrix_temp = trans_matrix(rowstemp, colstemp,adjugateMatrix(matrix1, rowstemp));
                        cout << "Macierz dopełnień: " <<endl;
                        print_matrix(rowstemp,colstemp,matrix_temp);
                    } else cout << "Macierz nie jest kwadratowa!" << endl;

                } else if (wybor == '2') {
                    rowstemp = rows2;
                    colstemp = cols2;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    cout<<endl;
                    if (rowstemp == colstemp) {
                        matrix_temp = trans_matrix(rowstemp, colstemp,adjugateMatrix(matrix2, rowstemp));
                        cout << "Macierz dopełnień: " <<endl;
                        print_matrix(rowstemp,colstemp,matrix_temp);
                    } else cout << "Macierz nie jest kwadratowa!" << endl;
                } else cout << "Bledny wybor macierzy!" << endl;

                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 8:{
                char wybor;
                cout<< "Wybierz dla której macierzy chcesz obliczyć macierz dołączoną [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin >> wybor;
                if (wybor == '1') {
                    rowstemp = rows1;
                    colstemp = cols1;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix1);
                    cout<<endl;
                    if (rowstemp == colstemp) {
                        matrix_temp = adjugateMatrix(matrix1, rowstemp);
                        cout << "Macierz dołączona: " <<endl;
                        print_matrix(rowstemp,colstemp,matrix_temp);
                    } else cout << "Macierz nie jest kwadratowa!" << endl;

                } else if (wybor == '2') {
                    rowstemp = rows2;
                    colstemp = cols2;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    cout<<endl;
                    if (rowstemp == colstemp) {
                        matrix_temp = adjugateMatrix(matrix2, rowstemp);
                        cout << "Macierz dopełnień: " <<endl;
                        print_matrix(rowstemp,colstemp,matrix_temp);
                    } else cout << "Macierz nie jest kwadratowa!" << endl;
                } else cout << "Bledny wybor macierzy!" << endl;

                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 9:{
                //jezeli wyznacznik jest rowny 0 to nie mozna obliczyc
                char wybor;
                cout
                        << "Wybierz dla której macierzy chcesz obliczyć macierz odwrotną [1 - macierz pierwsza, 2 - macierz druga]: ";
                cin >> wybor;
                if (wybor == '1') {
                    rowstemp = rows1;
                    colstemp = cols1;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix1);
                    if (rowstemp == colstemp) {
                        double currentDet = det(matrix1,rowstemp);
                        if(currentDet != 0){
                            matrix_temp = mul_sc_matrix(rowstemp,rowstemp,adjugateMatrix(matrix1,rowstemp),(1/currentDet));
                            cout << "Macierz odwrotna:" << endl;
                            print_matrix(colstemp, rowstemp, matrix_temp);
                        } else
                            cout << "Nie można obliczyć macierzy odwrotnej! Wybrana macierz jest osobliwa (det = 0) ";
                    }else cout << "Macierz nie jest kwadratowa!" << endl;

                } else if (wybor == '2') {
                    rowstemp = rows2;
                    colstemp = cols2;
                    cout << "Wczytana macierz:" << endl;
                    print_matrix(rowstemp, colstemp, matrix2);
                    if (rowstemp == colstemp) {
                        double currentDet = det(matrix2,rowstemp);
                        if(currentDet != 0){
                            matrix_temp = mul_sc_matrix(rowstemp,rowstemp,trans_matrix(rowstemp, rowstemp, adjugateMatrix(matrix2,rowstemp)),(1/currentDet));
                            cout << "Macierz odwrotna:" << endl;
                            print_matrix(colstemp, rowstemp, matrix_temp);
                        } else
                            cout << "Nie można obliczyć macierzy odwrotnej! Wybrana macierz jest osobliwa (det = 0) ";
                    }else cout << "Macierz nie jest kwadratowa!" << endl;
                } else cout << "Bledny wybor macierzy!" << endl;

                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }
            case 10: {
                remove_matrix(rows1, matrix1);
                remove_matrix(rows2, matrix2);
                remove_matrix(rowstemp, matrix_temp);
                cout << "Wczytywanie pierwszej macierzy" << endl;
                matrix1 = create_matrix(rows1, cols1);
                cout << "Wczytywanie drugiej macierzy" << endl;
                matrix2 = create_matrix(rows2, cols2);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }

            case 11: {
                cout << "Macierz pierwsza" << endl;
                print_matrix(rows1, cols1, matrix1);
                cout << "Macierz druga" << endl;
                print_matrix(rows2, cols2, matrix2);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }

            case 12: {
                check = false;
                break;
            }

            default: {
                cout << "Podałeś złą opcje, spróbuj jeszcze raz!" << endl;
                cin >> choice;
            }
        }
    } while (check);
    remove_matrix(rows1, matrix1);
    remove_matrix(rows2, matrix2);
    remove_matrix(rowstemp, matrix_temp);
}