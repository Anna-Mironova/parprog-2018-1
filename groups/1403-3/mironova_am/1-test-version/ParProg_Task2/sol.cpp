#include <cmath>
#include <cstdlib>

// логарифм по основанию base
int log(const int Size, const int base) {
	return int(log(Size) / log(base));
}

// проверяем является ли размер матрицы степенью base
bool IsSizePowerBase(const int Size, const int base) {
	bool res;
	if (int(pow(base, log(Size, base))) == Size)
		res = true;
	else
		res = false;
	return res;
}

// увеличиваем размер матрицы до ближайшей степени base
int IncreaseSize(const int Size, const int base) {
	int res;
	if (!IsSizePowerBase(Size, base))
		res = 1 << (log(Size, base) + 1);
	else
		res = 1 << (log(Size, base));
	return res;
}

// сложение матриц
double* Add(double* mtx1, double* mtx2,int n) {

	double * result= new double[n*n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i*n + j] = mtx1[i*n + j] +mtx2[i*n + j];
		}
	}
	return result;
}

// вычитание матриц
double* Sub(double* mtx1, double* mtx2, int n) {

	double * result = new double[n*n];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i*n + j] = mtx1[i*n + j] - mtx2[i*n + j];
		}
	}
	return result;
}

// Обычный метод умножения матриц
double* StandartAlgorithm(double* mtx1, double* mtx2, int n) {
	double * result = new double[n*n];
	for (int i = 0; i < n*n; i++) {
		result[i] = 0;
	}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					result[i*n+j] += mtx1[i*n+k] * mtx2[k*n+j];
				}
			}
		}
	return result;
}

// Алгоритм Штрассена умножения матриц
double* ConsistentStrassenAlgorithm(double* mtx1, double* mtx2, int n, int min_size) {
	
	double* result;
	if (n <= min_size) {
		result = StandartAlgorithm(mtx1, mtx2,n);
	} else {
		result = new double[n*n];

		double** mtx1_temp = new double*[n];
		double** mtx2_temp = new double*[n];
		double** result_temp = new double*[n];
		for (int i = 0; i < n; i++) {
			mtx1_temp[i] = mtx1 + i*n;
			mtx2_temp[i] = mtx2 + i*n;
			result_temp[i] = result + i*n;
		}

		n /= 2; // Матрица разбивается на 4 блока с половинными размерами

		double* A11 = new double[n*n]; double*	A12 = new double[n*n];
		double* A21 = new double[n*n]; double* A22 = new double[n*n];
		double* B11 = new double[n*n]; double* B12 = new double[n*n];
		double* B21 = new double[n*n]; double* B22 = new double[n*n];
		double* C11 = new double[n*n]; double* C12 = new double[n*n];
		double* C21 = new double[n*n]; double* C22 = new double[n*n];
		double* P1 = new double[n*n];
		double* P2 = new double[n*n];
		double* P3 = new double[n*n];
		double* P4 = new double[n*n];
		double* P5 = new double[n*n];
		double* P6 = new double[n*n];
		double* P7 = new double[n*n];

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				A11[i*n + j]= mtx1_temp[i][j];
				A12[i*n + j] = mtx1_temp[i][j + n];
				A21[i*n + j] = mtx1_temp[i + n][j];
				A22[i*n + j] = mtx1_temp[i + n][j + n];

				B11[i*n + j] = mtx2_temp[i][j];
				B12[i*n + j] = mtx2_temp[i][j + n];
				B21[i*n + j] = mtx2_temp[i + n][j];
				B22[i*n + j] = mtx2_temp[i + n][j + n];
			}
		}

		//Производим рекурсивный процесс до тех пор,пока размер матриц не станет достаточно малым
		P1 = ConsistentStrassenAlgorithm(Add(A11, A22, n), Add(B11, B22, n), n, min_size);
		P2 = ConsistentStrassenAlgorithm(Add(A21, A22, n), B11, n, min_size);
		P3 = ConsistentStrassenAlgorithm(A11, Sub(B12, B22, n), n, min_size);
		P4 = ConsistentStrassenAlgorithm(A22, Sub(B21, B11, n), n, min_size);
		P5 = ConsistentStrassenAlgorithm(Add(A11, A12, n), B22, n, min_size);
		P6 = ConsistentStrassenAlgorithm(Sub(A21, A11, n), Add(B11, B12, n), n, min_size);
		P7 = ConsistentStrassenAlgorithm(Sub(A12, A22, n), Add(B21, B22, n), n,min_size);

		//Находим результирующие блоки 
		C11 = Sub(Add(Add(P1, P4, n), P7, n), P5, n); // P1 + P4 + P7 - P5
		C12 = Add(P3, P5, n);		                  // P3 + P5;
		C21 = Add(P2, P4, n);                         // P2 + P4;
		C22 = Sub(Add(Add(P1, P3, n), P6, n), P2, n); // P1 + P3 + P6 - P2


		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				result_temp[i][j] = C11[i*n + j];
				result_temp[i][j + n] = C12[i*n + j];
				result_temp[i + n][j] = C21[i*n + j];
				result_temp[i + n][j + n] = C22[i*n + j];
			}
		}

		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
		delete[] P1; delete[] P2; delete[] P3; delete[] P4;
		delete[] P5; delete[] P6; delete[] P7;
		delete[] mtx1_temp; delete[] mtx2_temp; delete[] result_temp;
	}
	return result;
}

void ConvertForStrassenAlgorithm(double* mtx1, double* mtx2,int n, double* mtx1_new, double* mtx2_new )
{
	int n_new = IncreaseSize(n, 2);
	if (n == n_new) {
		for (int i = 0; i < n*n; i++)  {
			mtx1_new[i] = mtx1[i];
			mtx2_new[i] = mtx2[i];
		}
	} else {
		double** mtx1_temp = new double*[n];
		double** mtx2_temp = new double*[n];
		for (int i = 0; i < n; i++) {
			mtx1_temp[i] = mtx1 + i*n;
			mtx2_temp[i] = mtx2 + i*n;
		}
		for (int i = 0; i < n_new*n_new; i++){
			mtx1_new[i] = 0;
			mtx2_new[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mtx1_new[i*n_new + j] = mtx1_temp[i][j];
				mtx2_new[i*n_new + j] = mtx2_temp[i][j];
			}
		}
		delete[] mtx1_temp;
		delete[] mtx2_temp;
	}
}

void ConvertAfterStrassenAlgorithm(double* res, double* res_new, int n)
{
	if (n == IncreaseSize(n, 2)) {
		for (int i = 0; i < n*n; i++) {
			res_new[i] = res[i];
		}
	} else {
		int n_new = IncreaseSize(n, 2);
		double** result_temp = new double*[n_new];
		for (int i = 0; i <  n_new; i++) {
			result_temp[i] = res + i* n_new;
		}
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				res_new[i*n + j] = result_temp[i][j];
			}
		}
	}
}
