//
// Created by Dominik Cegiełka <224478@edu.p.lodz.pl> on 05.11.2019.
//

#include "../include/zespolona.h"
#include "../include/simple_function.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> 

#define SIN(x) sin(x * M_PI/180) 
#define COS(x) cos(x * M_PI/180)

using namespace std;

ostream& operator<< (ostream& output, const Complex& c)
{
	return output << "[" << c.Re << "," << c.Im << "]";
}

vector<Complex> create_polygon() {
    int vertices;
    cout << "Podaj ilosc wierzcholkow wielokata: ";
    cin >> vertices;
    vector<Complex> polygon;
    for (int i = 0; i < vertices; ++i) {
        Complex tmp;
        cout << "Podaj wspolrzedne "<<i+1<<" wierzcholka: ";
        cin >> tmp.Re >> tmp.Im ;
        polygon.push_back(tmp);
    }
    return polygon;
}

void polygon_print(vector<Complex> polygon)
{
	for (int i = 0; i < polygon.size(); i++) {
		if (abs(polygon[i].Re) < 0.000000000000001) polygon[i].Re = round(polygon[i].Re);
		if (abs(polygon[i].Im) < 0.000000000000001) polygon[i].Im = round(polygon[i].Im);
		//cout << fixed;
        //cout<<"["<<setprecision(5)<<polygon[i].Re<<","<< setprecision(5) << polygon[i].Im<<"]"<<endl;
		//cout.precision(15);
		//cout << "[" << polygon[i].Re << "," << polygon[i].Im << "]" << endl;
		cout << polygon[i] <<", ";
	}
	cout<<endl;

}

double polygon_area(vector<Complex> polygon)
{
    //Sholeace formula
    double area = 0.0;
    int j = (int)polygon.size()-1;
    for (int i = 0; i < polygon.size(); i++) {
        area += (polygon[j].Re + polygon[i].Re) * (polygon[j].Im - polygon[i].Im);
        j = i;
    }
    return abs(area/2.0);
}

double distanceOfPoints(Complex z, Complex z0)
{
    return sqrt(pow((z.Re - z0.Re), 2) + pow((z.Im - z0.Im ), 2));
}

double polygon_circuit(vector<Complex> polygon)
{
	double circuit = distanceOfPoints(polygon[polygon.size() - 1], polygon[0]);
	//cout <<" 1 wartosc: "<< circuit;
    for (int i = 0; i < polygon.size()-1; i++)
    {
          circuit+=distanceOfPoints(polygon[i+1],polygon[i]);
    }
    return circuit;
}

Complex polygon_centroid(vector<Complex> polygon)
{
	Complex centroid;
	centroid.Re = 0;
	centroid.Im = 0;
	for (int i = 0; i < polygon.size(); i++)
	{
		centroid.Re += polygon[i].Re;
		centroid.Im += polygon[i].Im;
		//cout << centroid.Re << " , " << centroid.Im << endl;
	}
	centroid.Re /= polygon.size();
	centroid.Im /= polygon.size();
	return centroid;
}

vector<Complex> polygon_move(vector<Complex> polygon, Complex mv)
{
	vector<Complex> polygon_moved;
	for(int i=0;i<polygon.size();i++)
	{
		polygon_moved.push_back(add(polygon[i], mv));
	}
	return polygon_moved;
}


vector<Complex> polygon_scale(vector<Complex> polygon, double scale)
{
	Complex scale_polygon;
	scale_polygon.Re = scale;
	scale_polygon.Im = 0;
	vector<Complex> polygon_scaled;

	for (int i = 0; i < polygon.size(); i++)
	{
		polygon_scaled.push_back(mul(polygon[i], scale_polygon));
	}
	polygon_print(polygon_scaled);
	Complex scaled_centroid = polygon_centroid(polygon_scaled);
	//cout << scaled_centroid << endl;
	Complex first_centroid = polygon_centroid(polygon);
	//cout << first_centroid << endl;
	vector<Complex> tmp = polygon_move(polygon_scaled, sub(first_centroid, scaled_centroid));
	return tmp;
}

Complex point_rotate(Complex point, Complex reference_point, double angle)
{
	Complex point_shifted = sub(point, reference_point);
	Complex point_rotated;
	point_rotated.Re = (point_shifted.Re * COS(angle) - point_shifted.Im * SIN(angle));
	point_rotated.Re += reference_point.Re;
	point_rotated.Im = (point_shifted.Re * SIN(angle) + point_shifted.Im * COS(angle));
	point_rotated.Im += reference_point.Im;
	return point_rotated;
}

vector<Complex> polygon_rotate(vector<Complex> polygon, Complex reference_point, double angle)
{
	vector<Complex> polygon_rotated;
	for(int i=0;i<polygon.size();i++) {
		polygon_rotated.push_back(point_rotate(polygon[i], reference_point, angle));
	}
	return polygon_rotated;
}


void zad2()
{
	bool check;
    vector<Complex> polygon1=create_polygon();
    char choice;
	do
	{
		cout << "Wybierz operacje na wielokacie, ktora chcesz wykonac: \n"
		<< "1.Oblicz pole \n2.Oblicz obwod \n3.Przesunąć wielokąt \n4.Obrócić wielokąt \n5.Przeskalować wielokąt \n6.Nowy wielokat \n7.Wyjdz"
		<<"\nOperacja nr: ";
		cin >> choice;
		switch(choice) {
		    case '1' : {
		        cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                cout<<"Pole wielokata: "<<polygon_area(polygon1)<<endl;
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
		    }
		    case '2': {
                cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                cout<<"Obwod wielokata: "<< polygon_circuit(polygon1)<<endl;
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
		    }
		    case '3': {
                cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                //cout <<"Wspolrzedne srodka: "<< polygon_centroid(polygon1) << endl;
                Complex wektor;
                cout<<"Podaj o ile chcesz przesunac wielokat wzgledem osi OX oraz OY: ";
                cin>>wektor.Re>>wektor.Im;
                vector<Complex> polygon2 = polygon_move(polygon1, wektor);
                cout<<"Wspolrzedne wierzcholkow wielokata po przesunieciu o wektor ["<<wektor.Re<<","<<wektor.Im<<"]:"<<endl;
                polygon_print(polygon2);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
		    }
		    case '4' : {
		        double angle;
		        Complex point;
                cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                //cout <<"Wspolrzedne srodka: "<< polygon_centroid(polygon1) << endl;
                cout<<"Podaj o jaki kat chcesz obrocic wielokat: ";
                cin>>angle;
                cout<<"Podaj punkt do obrocenia: ";
                cin>>point.Re>>point.Im;
                vector<Complex> polygon2= polygon_rotate(polygon1, point, angle);
                cout<<"Wspolrzedne wierzcholkow wielokata po obrocie o "<<angle<<" stopni"<<endl;
                polygon_print(polygon2);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
		    }
		    case '5': {
		        double scale;
                cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                //cout <<"Wspolrzedne srodka: "<< polygon_centroid(polygon1) << endl;
                cout<<"Podaj skale 1:";
                cin>>scale;
                vector<Complex> polygon3 = polygon_scale(polygon1, scale);
                cout<<"Wspolrzedne wierzcholkow wielokata po przeskalowaniu. Skala 1:"<<scale<<":"<<endl;
                polygon_print(polygon3);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
		    }
            case '6': {
                polygon1=create_polygon();
                cout<<"Wczytane wspolrzedne wierzcholkow wielokata: ";
                polygon_print(polygon1);
                cout << "Czy chcesz wykonac inna operacje? [0 - NIE, 1 - TAK]? ";
                cin >> check;
                break;
            }

            case '7': {
                check=0;
                break;
            }

            default: {
                cout << "Podałeś złą opcje, spróbuj jeszcze raz!" << endl;
                cin >> choice;
            }
		}
	} while (check);
}