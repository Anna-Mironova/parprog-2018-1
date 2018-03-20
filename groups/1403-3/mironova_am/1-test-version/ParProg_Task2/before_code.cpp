#include <cstdio>
#include <omp.h>
#include <iostream>

using namespace std;

double* ConsistentStrassenAlgorithm(double* mtx1, double* mtx2,int n, int min_size);
double* StandartAlgorithm(double* mtx1, double* mtx2, int n);

int main(int argc, char * argv[]) {
	int n;
	double* A;
	double* B;
	double* C;
	double* C_standart;

	FILE* f1;
	FILE* f2;

	std::string fileName = "matr";
	if (argc == 2) {
		fileName = argv[1];
	}
	freopen_s(&f1, ("..//Tests/" + fileName + ".in").c_str(), "rb", stdin);

	// чтение данных 
	fread(&n, sizeof(n), 1, stdin);
	A = new double[n * n];
	B = new double[n * n];
	C = new double[n * n];
	fread(A, sizeof(*A), n*n, stdin);
	fread(B, sizeof(*B), n*n, stdin);
	fclose(f1);

	// запуск и замер последовательной версии
	double time = omp_get_wtime();
	C= ConsistentStrassenAlgorithm(A,B,n,1);
	time = omp_get_wtime() - time;

	C_standart = StandartAlgorithm(A, B, n);

	// запись результатов
	freopen_s(&f2, ("..//Tests/" + fileName + ".sol").c_str(), "wb", stdout);
	fwrite(&time, sizeof(time), 1, stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	fwrite(C, sizeof(*C), n * n, stdout);
	fclose(f2);

	freopen_s(&f2, ("..//Tests/" + fileName + ".ans").c_str(), "wb", stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	fwrite(C_standart, sizeof(*C_standart), n * n, stdout);
	fclose(f2);

	return 0;
}