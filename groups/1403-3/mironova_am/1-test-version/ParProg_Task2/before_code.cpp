#include <cstdio>
#include <omp.h>
#include <iostream>

using namespace std;

double* ConsistentStrassenAlgorithm(double* mtx1, double* mtx2,int n, int min_size);

int main(int argc, char * argv[]) {
	int n;
	double* A;
	double* B;
	double* C;

	FILE* f1;
	FILE* f2;

	freopen_s(&f1, "..//matr.in", "rb", stdin);
	freopen_s(&f2, "..//matr.out", "wb", stdout);

	// чтение данных 
	fread(&n, sizeof(n), 1, stdin);
	A = new double[n * n];
	B = new double[n * n];
	C = new double[n * n];
	fread(A, sizeof(*A), n*n, stdin);
	fread(B, sizeof(*B), n*n, stdin);

	// запуск и замер последовательной версии
	double time = omp_get_wtime();
	C= ConsistentStrassenAlgorithm(A,B,n,1);
	time = omp_get_wtime() - time;

	// запись результатов
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(C, sizeof(*C), n * n, stdout);

	return 0;
}