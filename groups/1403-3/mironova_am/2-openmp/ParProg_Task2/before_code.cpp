#include <cstdio>
#include <omp.h>
#include <iostream>

using namespace std;

double* ParallelStrassenAlgorithm(double* mtx1, double* mtx2,int n, int min_size);
double* StandartAlgorithm(double* mtx1, double* mtx2, int n);
int IncreaseSize(const int Size, const int base);
void ConvertForStrassenAlgorithm(double* mtx1, double* mtx2, int n, double* mtx1_new, double* mtx2_new);
void ConvertAfterStrassenAlgorithm(double* res, double* res_new, int n);

int main(int argc, char * argv[]) {
	int n;
	int n_temp;
	double* A;
	double* B;
	double* C;
	double* A_temp;
	double* B_temp;
	double* C_temp;
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

	//преобразование данных 
	n_temp = IncreaseSize(n, 2);
	A_temp = new double[n_temp*n_temp];
	B_temp = new double[n_temp*n_temp];
	ConvertForStrassenAlgorithm(A, B, n, A_temp, B_temp);

	omp_set_num_threads(2);
	// запуск и замер параллельной версии
	double time = omp_get_wtime();
	C_temp= ParallelStrassenAlgorithm(A_temp,B_temp,n_temp,1);
	time = omp_get_wtime() - time;

	C_standart = StandartAlgorithm(A, B, n);

	//преобразование данных 
	ConvertAfterStrassenAlgorithm(C_temp,C,n);

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