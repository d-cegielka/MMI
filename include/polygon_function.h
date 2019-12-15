//
// Created by Dominik Cegiełka <224478@edu.p.lodz.pl> on 05.11.2019.
//

#ifndef MMI_POLYGON_FUNCTION_H
#define MMI_POLYGON_FUNCTION_H
#include <vector>

using namespace std;

vector<Complex> create_polygon();
void polygon_print(vector<Complex> polygon);
double distanceOfPoints(Complex z, Complex z0);
double polygon_area(vector<Complex> polygon);
double polygon_circuit(vector<Complex> polygon);
Complex polygon_centroid(vector<Complex> polygon);
vector<Complex> polygon_move(vector<Complex> polygon, Complex mv);
vector<Complex> polygon_scale(vector<Complex> polygon, double scale);
Complex point_rotate(Complex point, Complex reference_point, double angle);
vector<Complex> polygon_rotate(vector<Complex> polygon, Complex reference_point, double angle);
void zad2();
#endif //MMI_POLYGON_FUNCTION_H
