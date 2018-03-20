#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

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
	//преобразуем размерность  матрицы,чтобы она была степенью 2 
	// в бинарных файлах размерность уже преобразованная и матрицы дополнены нулями
	int n_new = IncreaseSize(n, 2);
	fwrite(&n_new, sizeof(n_new), 1, stdout);
	double * cur = new double[n_new];
	for (int i = 0; i < n_new; i++)
	{
		cur[i] = 0;
	}

	//генерация 1-ой матрицы
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cur[j] = distribution(generator);
		fwrite(cur, sizeof(*cur), n_new, stdout);
	}
	for (int i = 0; i < n_new; i++)
	{
		cur[i] = 0;
	}
	for (int i = n; i < n_new; i++)
	{
		fwrite(cur, sizeof(*cur), n_new, stdout);
	}

	//генерация 2-ой матрицы
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cur[j] = distribution(generator);
		fwrite(cur, sizeof(*cur), n_new, stdout);
	}
	for (int i = 0; i < n_new; i++)
	{
		cur[i] = 0;
	}
	for (int i = n; i < n_new; i++)
	{
		fwrite(cur, sizeof(*cur), n_new, stdout);
	}
	fclose(f1);
	return 0;
}