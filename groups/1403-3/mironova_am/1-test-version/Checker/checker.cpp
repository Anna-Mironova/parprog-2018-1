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

bool Test(double* standart_result, double* strassen_result, int n) {
	bool flag = true;

	// Вычисляем ошибку, как квадрат нормы разности решений
	double diff = 0.0;
	for (int i = 0; i < n * n; i++) {
		diff += (standart_result[i] - strassen_result[i]) * (standart_result[i] - strassen_result[i]);
	}
	// Проверяем, что ошибка мала, тогда сообщаем, что решение корректно, иначе - некорректно.
	if (diff < 1e-5) {
		flag = true;
	} else {
		flag = false;
	}
	return flag;
}

int main(int argc, char * argv[]) {
	FILE * f1;
	FILE * f2;
	double res_time;
	int n_ans;
	int n_sol;
	double *res_ans;
	double *res_sol;

	string fileName = "matr";
	if (argc == 2) {
		fileName = argv[1];
	}

	freopen_s(&f1, ("..//Tests/" + fileName + ".sol").c_str(), "rb", stdin);
	fread(&res_time, sizeof(res_time), 1, stdin);
	fread(&n_sol, sizeof(n_sol), 1, stdin);
	res_sol = new double[n_sol*n_sol];
	fread(res_sol, sizeof(*res_sol), n_sol*n_sol, stdin);
	fclose(f1);

	freopen_s(&f2, ("..//Tests/" + fileName + ".ans").c_str(), "rb", stdin);
	fread(&n_ans, sizeof(n_ans), 1, stdin);
	res_ans = new double[n_ans*n_ans];
	fread(res_ans, sizeof(*res_ans), n_ans*n_ans, stdin);
	fclose(f2);

	if (n_ans == n_sol) {
		if (Test(res_ans, res_sol, n_sol)) {
			checker_result.write_message("AC. Numbers are equal.");
			checker_result.write_verdict(verdict::AC);
		} else {
			checker_result.write_message("WA. Output is not correct.");
			checker_result.write_verdict(verdict::WA);
		}
	} else {
		checker_result.write_message("WA. Matrix sizes are not equal.");
		checker_result.write_verdict(verdict::WA);
	}

	checker_result.write_time(res_time * 1e7);
	return 0;
}
