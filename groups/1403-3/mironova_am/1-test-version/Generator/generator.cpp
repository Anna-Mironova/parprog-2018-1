#include <cstdio>
#include <random>
#include <ctime>
#include <chrono>

using namespace std;

int n_tests[] = { 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 100, 200, 300, 400, 500,
600, 700, 800, 900, 1000 };
int IncreaseSize(const int Size, const int base);

int main(int argc, char * argv[])
{
	FILE * f1;
	// �������������� ����� stdout � ���� matr.in
	freopen_s(&f1, "..//matr.in", "wb", stdout);
	// ������ ��������� ��������� ����� � seed ������ ���������� ������� � ������ �����
	default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
	// ������ ����������� ������������� ��������� �������� ���� double � ���������
	// [-10000, 10000]
	uniform_real_distribution <double> distribution(-1e4, 1e4);
	// ����� ������ ������
	int n = 8;
	// ���� �������� ����� ����� � ���������� ��������� ������, �� ���� ������ �� n_tests
	if (argc > 1)
		n = n_tests[atoi(argv[1])];
	//����������� �����������  �������,����� ��� ���� �������� 2 
	int n_new = IncreaseSize(n, 2);
	// ���������� � �������� ���� ����������� ������
	fwrite(&n_new, sizeof(n_new), 1, stdout);
	// ������ ��������� ������ ��� ������ �������
	double * cur = new double[n_new];
	for (int i = 0; i < n_new; i++)
	{
		cur[i] = 0;
	}
	// ���������� ������ �������
	for (int i = 0; i < n; i++)
	{
		// ��������� ���������� ������� �� ������������ ������������� ��������� ������ �������
		for (int j = 0; j < n; j++)
			cur[j] = distribution(generator);
		// ���������� ������ � �������� ���� � ����
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
	// ���������� ���������� ������ �������
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