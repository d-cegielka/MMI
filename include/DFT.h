//
// Created by student on 09.12.2019.
//

#ifndef MMI_DFT_H
#define MMI_DFT_H

#include "zespolona.h"

double *load_data(int &N);
Complex *DFT(int N, double *x);
void X_print(Complex *X);
double *inverse_DFT(int N, Complex *X);
void zad4();

#endif //MMI_DFT_H
