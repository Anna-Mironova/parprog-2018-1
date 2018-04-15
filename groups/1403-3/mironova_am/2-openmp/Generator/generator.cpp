#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

int main(int argc, char * argv[]) {
	FILE * f1;
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	int n ;
	string fileName = "matr";
	if (argc == 2) {
		n = atoi(argv[1]);
	}
	else {
		if (argc == 3)
		{
			n = atoi(argv[1]);
			fileName = argv[2];
		}
		else {
			//по умолчанию
			n = 16; 
		}
	}

	freopen_s(&f1, ("..//Tests/" + fileName + ".in").c_str(), "wb", stdout);
	fwrite(&n, sizeof(n), 1, stdout);
	double * cur = new double[n];

	//генерация 1-ой матрицы
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cur[j] = distribution(generator);
		fwrite(cur, sizeof(*cur), n, stdout);
	}

	//генерация 2-ой матрицы
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cur[j] = distribution(generator);
		fwrite(cur, sizeof(*cur), n, stdout);
	}

	fclose(f1);
	return 0;
}