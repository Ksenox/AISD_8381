// Задание: посчитать число всех гирек заданного бинарного коромысла.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

#define N 501


// Бинарное коромысло
typedef struct BinCor {
	unsigned int length1;
	unsigned int length2;
	unsigned int weight1;
	unsigned int weight2;
	struct BinCor* cor_1;
	struct BinCor* cor_2;
} BinCor;


// вывод сообщений об ошибках
void errorMassage(int error_number, char* str, int index) {
	printf("\nОшибка! Вы ввели некорректные данные:\n");
	switch (error_number) {
	case 1:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Ожидался символ - '('.\n");
		break;
	case 2:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Ожидался символ - ')'.\n");
		break;
	case 3:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Ожидалось значение от 1 до 9.\n");
		break;
	case 4:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Ожидался пробел.\n");
		break;
	case 5:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Отсутствует закрывающая скобка.\n");
		break;
	case 6:
		printf("Символ №%d - '%c'.\n", index + 1, str[index]);
		printf("Ожидалось значение от 1 до 9 или '('.\n");
		break;
	case 7:
		printf("После символа №%d присутствуют лишние символы.\n", index + 1);
		break;
	}
}


BinCor* initBinCorElement() { // Инициализация элемента списка
	BinCor* element = (BinCor*)malloc(sizeof(BinCor));
	element->length1 = 0;
	element->length2 = 0;
	element->weight1 = 0;
	element->weight2 = 0;
	element->cor_1 = NULL;
	element->cor_2 = NULL;
	return element;
}


// считывание и создание бинарного коромысла
// функция возвращает 1, если возникла ошибка
int readBinCorElement(char* str, int index_1, int index_2, BinCor** element) {
	*element = initBinCorElement();

	if (str[index_1++] != '(') {
		errorMassage(1, str, index_1 - 1);
		return 1;
	}
	if (str[index_2--] != ')') {
		errorMassage(2, str, index_2 + 1);
		return 1;
	}

	// считывание левого плеча
	if (str[index_1++] != '(') { // открывающая скобка левого плеча
		errorMassage(1, str, index_1 - 1);
		return 1;
	}
	// первое число(длина)
	if (!isdigit(str[index_1]) || str[index_1] == '0') {
		errorMassage(3, str, index_1);
		return 1;
	}
	while (1) { // считывание числа
		if (isdigit(str[index_1])) {
			(*element)->length1 = (*element)->length1 * 10 + str[index_1] - '0';
			index_1++;
		}
		else {
			break;
		}
	}
	if (str[index_1++] != ' ') { // пробел после первого числа
		errorMassage(4, str, index_1 - 1);
		return 1;
	}
	if (isdigit(str[index_1]) && str[index_1] != 0) { // случай, если гирька
		while (1) {
			if (isdigit(str[index_1])) {
				(*element)->weight1 = (*element)->weight1 * 10 + str[index_1] - '0';
				index_1++;
			}
			else {
				break;
			}
		}
	}
	else if (str[index_1] == '(') { // случай, если ещё одно коромысло
		int bracket_count = 0;
		int index;
		// поиск закрывающей скобки
		for (index = index_1; index < index_2; index++) {
			if (str[index] == '(')
				bracket_count++;
			if (str[index] == ')')
				bracket_count--;
			if (bracket_count == 0) {
				if (readBinCorElement(str, index_1, index, &((*element)->cor_1))) {
					return 1;
				}
				index_1 = index + 1;
				break;
			}
		}
		if (bracket_count != 0) {
			errorMassage(5, str, index_1);
			return 1;
		}
	}
	else {
		errorMassage(6, str, index_1);
		return 1;
	}
	if (str[index_1++] != ')') { // закрывающая скобка левого плеча
		errorMassage(2, str, index_1 - 1);
		return 1;
	}


	if (str[index_1++] != ' ') { // пробел между плечами
		errorMassage(4, str, index_1 - 1);
		return 1;
	}


	// считывание правого плеча
	if (str[index_1++] != '(') { // открывающая скобка прового плеча
		errorMassage(1, str, index_1 - 1);
		return 1;
	}
	// первое число(длина)
	if (!isdigit(str[index_1]) || str[index_1] == 0) {
		errorMassage(3, str, index_1);
		return 1;
	}
	while (1) { // считывание числа
		if (isdigit(str[index_1])) {
			(*element)->length2 = (*element)->length2 * 10 + str[index_1] - '0';
			index_1++;
		}
		else {
			break;
		}
	}
	if (str[index_1++] != ' ') { // пробел после первого числа
		errorMassage(4, str, index_1 - 1);
		return 1;
	}
	if (isdigit(str[index_1]) && str[index_1] != '0') { // случай, если гирька
		while (1) {
			if (isdigit(str[index_1])) {
				(*element)->weight2 = (*element)->weight2 * 10 + str[index_1] - '0';
				index_1++;
			}
			else {
				break;
			}
		}
	}
	else if (str[index_1] == '(') { // случай, если ещё одно коромысло
		int bracket_count = 0;
		int index;
		// поиск закрывающей скобки
		for (index = index_1; index < index_2; index++) {
			if (str[index] == '(')
				bracket_count++;
			if (str[index] == ')')
				bracket_count--;
			if (bracket_count == 0) {
				if (readBinCorElement(str, index_1, index, &((*element)->cor_2))) {
					return 1;
				}
				index_1 = index + 1;
				break;
			}
		}
		if (bracket_count != 0) {
			errorMassage(5, str, index_1);
			return 1;
		}
	}
	else {
		errorMassage(6, str, index_1);
		return 1;
	}
	if (str[index_1] != ')') { // закрывающая скобка левого плеча
		errorMassage(2, str, index_1);
		return 1;
	}

	// проверка на лишние символы
	if (index_2 != index_1) {
		errorMassage(7, str, index_1);
		return 1;
	}

	return 0;
}


// создание бинарного коромысла
// функция возвращает 1, если возникла ошибка
int createBinCor(char* str, BinCor** binCor) {
	int index_1 = 0;
	int index_2 = strlen(str) - 2;

	return readBinCorElement(str, index_1, index_2, binCor);
}


// Возвращаемое значение равно количеству всех
// гирек в заданном бинарном коромысле.
unsigned int numbers(const BinCor binCor, int deep_of_recursion) {
	int result = 0;

	for (int i = 0; i < deep_of_recursion; i++)
		printf("     ");
	printf("левое  плечо: ");
	if (binCor.cor_1 == NULL) {
		printf("гиря (+1).\n");
		result++;
	}
	else {
		printf("коромысло:\n");
		result += numbers(*(binCor.cor_1), deep_of_recursion + 1);
	}

	for (int i = 0; i < deep_of_recursion; i++)
		printf("     ");
	printf("правое плечо: ");
	if (binCor.cor_2 == NULL) {
		printf("гиря (+1).\n");
		result++;
	}
	else {
		printf("коромысло:\n");
		result += numbers(*(binCor.cor_2), deep_of_recursion + 1);
	}

	return result;
}


// очистка памяти
void free_memory(BinCor* binCor) {
	if (binCor != NULL) {
		free(binCor->cor_1);
		free(binCor->cor_2);
	}
	free(binCor);
}



int main(void)
{
	setlocale(LC_ALL, "Russian");
	char str[N]; // строка для ввода
	BinCor* binCor = NULL; // бинарное коромысло


	// начало считывания и обработки данных
	printf("\nПрограмма выводит общее число гирек в указанном бинарном коромысле.\n");
	printf("\nБинарное коромысло записывается в виде:\n");
	printf("(ПЛЕЧО ПЛЕЧО)\n");
	printf("Плечо имеет следующий вид:\n");
	printf("(ДЛИНА ГРУЗ)\n");
	printf("В качестве груза может выступать ещё одно бинарное коромысло или груз (число).\n");
	printf("\nВведите бинарное коромысло (не больше 500 символов): ");
	fgets(str, N, stdin);

	// обработка данных и проверка на ошибки
	if (createBinCor(str, &binCor)) {
		printf("Программа завершила работу.\n\n");
		free_memory(binCor);
		return 0;
	}
	printf("\nВведены корректные данные.\n\n");
	// конец считывания и обработки данных

	// вывод результата
	printf("Ход работы алгоритма:\n\n");
	printf("\nОбщее количество гирек: %u.\n\n", numbers(*binCor, 1));

	free_memory(binCor);

	return 0;
}
