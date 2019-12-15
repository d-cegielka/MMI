//
// Created by student on 18.11.2019.
//

#ifndef MMI_MATRIX_FUNCTION_H
#define MMI_MATRIX_FUNCTION_H

double** create_matrix(int &rows, int &cols);
void remove_matrix(int rows, double **matrix);
void print_matrix(int rows, int cols, double **matrix);
double **add_matrix(int rows,int cols, double **matrix1, double **matrix2);
double **sub_matrix(int rows,int cols, double **matrix1, double **matrix2);
double **mul_sc_matrix(int rows,int cols1,  double **matrix, double scalar);
double **mul_matrix(int rows, int cols1 , int cols2,  double **matrix1, double **matrix2);
double **trans_matrix(int rows, int cols, double **matrix);
void getMinor(double **matrix, double **matrixTemp, int outRow, int outCol, int n);
double det(double **matrix, int n);
double **adjugateMatrix(double **matrix, int n);

void zad3();

#endif //MMI_MATRIX_FUNCTION_H
