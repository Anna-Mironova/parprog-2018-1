#include <cstdio>
#include <cmath>
#include <string>
using namespace std;
// Используется для взаимодействия с тестирующей системой
////////////////////////////////////////////////////////////////////////////////////////////
/*
// Checker может устанавливать вот эти три вердикта:
AC = Accepted = Решение выдаёт корректный результат на данном тесте
WA = Wrong Answer = Решение выдаёт некорректный результат на данном тесте
PE = Presentation Error = Ошибка формата выходных данных
// Остальные вердикты checker не может устанавливать
NO = No verdict = Вердикт отсутствует
CE = Compilation Error = Ошибка компиляции
ML = Memory Limit Exceeded = Превышено ограничение по памяти
TL = Time Limit Exceeded = Превышено ограничение по времени работы RE = Runtime Error = Ошибка времени исполнения программы
IL = Idle Limit Exceeded = Превышено время простоя (бездействия) программы
DE = Deadly Error = Ошибка тестирующей системы
*/

enum verdict { NO = 1, AC, WA, CE, ML, TL, RE, IL, PE, DE };
class result {
private:
	FILE * bur;
public:
	enum ext_cls { NO = 1, VERDICT, MESSAGE, TIME, MEMORY };

	result(bool read = false)
	{
		if (read) fopen_s(&bur, "..//result.txt", "r");
		else fopen_s(&bur, "..//result.txt", "w");
	}

	~result()
	{
		fclose(bur);
	}

	void write_type(ext_cls t)
	{
		fwrite(&t, sizeof(t), 1, bur);
	}

	// Сообщить тестирующей системе, что решение получило один из вердиктов verdict
	void write_verdict(verdict v)
	{
		write_type(ext_cls::VERDICT);
		fwrite(&v, sizeof(v), 1, bur);
	}
	// Написать сообщение от checker'a пользователю.
	//   Например, что решение верное, или неверное.
	// Использовать только латинские буквы и знаки препинания
	void write_message(string str)
	{
		write_type(ext_cls::MESSAGE);
		int l = str.size();
		fwrite(&l, sizeof(l), 1, bur);
		fwrite(&str[0], sizeof(str[0]), l, bur);
	}
	// Сообщить тестирующей системе время работы программы участника,
	//   вычисленное с помощью before_code
	// x имеет размерность 100 нс = 10 ^ (-7) сек
	void write_time(long long x) {
		write_type(ext_cls::TIME);
		fwrite(&x, sizeof(x), 1, bur);
	}
	// Сообщить тестирующей системе, память затребованную программой участника
	void write_memory(unsigned long long x) {
		write_type(ext_cls::MEMORY);
		fwrite(&x, sizeof(x), 1, bur);
	}
} checker_result;

double* StandartAlgorithm(double* mtx1, double* mtx2, int n) {
	double * result = new double[n*n];
	for (int i = 0; i < n*n; i++) {
		result[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				result[i*n + j] += mtx1[i*n + k] * mtx2[k*n + j];
			}
		}
	}
	return result;
}

bool Test(double* mtx1, double* mtx2, double* strassen_result, int n) {
	double* res = StandartAlgorithm(mtx1, mtx2, n);
	bool flag = true;

	// Вычисляем ошибку, как квадрат нормы разности решений
	double diff = 0.0;
	for (int i = 0; i < n * n; i++)
		for (int i = 0; i < n*n; i++)
		{
			diff += (res[i] - strassen_result[i]) * (res[i] - strassen_result[i]);
		}
	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
	if (diff < 1e-6) {
		flag = true;
	}
	else {
		flag = false;
	}
	return flag;
}

int main() {
	FILE * f1;
	FILE * f2;
	double res_time;
	int n;
	double* res,*A,*B;

	freopen_s(&f1, "..//matr.out", "rb", stdin);
	fread(&res_time, sizeof(res_time), 1, stdin);
	fread(&n, sizeof(n), 1, stdin);
	res = new double[n*n];
	fread(res, sizeof(*res), n*n, stdin);
	fclose(f1);

	freopen_s(&f2, "..//matr.in", "rb", stdin);
	fread(&n, sizeof(n), 1, stdin);
	A = new double[n*n];
	B = new double[n*n];
	fread(A, sizeof(*A), n*n, stdin);
	fread(B, sizeof(*B), n*n, stdin);

	
	if (Test(A,B,res,n)) {
		checker_result.write_message("AC. Numbers are equal.");
		checker_result.write_verdict(verdict::AC);
	}
	else
	{
		checker_result.write_message("WA. Output is not correct.");
		checker_result.write_verdict(verdict::WA);
	}

	checker_result.write_time(res_time * 1e7);
	fclose(f2);
	return 0;
}
