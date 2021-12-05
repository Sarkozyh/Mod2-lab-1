#include <stdio.h>
#include <malloc.h>

void cut(char string[], int _continue) {				// Функция, рекурсивно выводящая содержимое самой внутренней пары скобок 
	printf("Input string: ");							// Выводим входную строку на экран
	printf("%s\n", string);
	int open = 0;										// Позиция самой внутренней открывающей скобки			
	int close = 0;										// Позиция самой внутренней закрывающей скобки
	int size = strlen((char*)string) / sizeof(char);	// Размер переданного массива
	_continue = findInner(string, &open, &close);		// Параметр, указывающий есть ли еще в строке скобки
	printf("Text into inner braces: ");
	for (int i = open; i < close; i++) {				// Вывод содержимого скобок на экран
		printf("%c", string[i]);
	}
	printf("\n");
	char* tmp;											// Вспосогательный динамический массив, без фрагмента, находящегося внутри внутренней пары скобок
	int newSize = size - (close - open  + 2);			// Размер нового массива (старый размер - размер строки в скобках - количество скобок)
	tmp = (char*)malloc((newSize) * sizeof(char));		// Выделение памяти для массива
	int j = 0;											// Индекс нового массива
	for (int i = 0; i < strlen((char*)string) / sizeof(char); i++) {  // Запись содержимого в новый массив
		if (i < open - 1 || i > close) {				// Если символы лежат за пределами скобок,
			tmp[j] = string[i];							// то записываем символ в новый массив
			j++;
		}
	}
	tmp[newSize] = '\0';								// Указываем конец новой строки
	if (_continue >= 0) {								// Если в строке еще есть скобки
		cut(tmp, _continue);							// Используем рекурсию
	}
	else {												// Инача выводим строку
		printf("Text outside braces: ");
		printf("%s\n", string);
	}
	//free(tmp);	
	*tmp = NULL;
	free(*tmp);// Освобождаем выделенную динамически память
}


int findInner(char string[], int *op, int *cl) {
	int count = 0;										// "Глубина" скобок
	int open = -1;										// Позиция открывающей скобки (Если -1, то скобка не найдена)
	int close = -1;										// Позиция закрывающей скобки (Если -1, то скобка не найдена)
	int tmp = 0;										// Позиция предыдущей открывающей скобки
	int max = 0;										// Максимальная "глубина" скобок
	for (int i = 0; i < strlen((char*)string) / sizeof(char) + 1; i++) {	// Поиск самой внутренней пары скобок
		if (string[i] == '{') {							// Если нашли открывающую скобку
			open = i;									// То указывем ее позицию
			count++;									// Увеличиваем "глубину"
		}
		if (string[i] == '}' && open > 0) {				// Если нашли закрывающую скобку
			if (max <= count) {							// Если ее "глубина" > максимальной
				max = count;							// Указываем новую максимальную "глубину"
				close = i;								// Указываем позицию закрывающей скобки
			}
			tmp = open;									// Указываем позицию предыдущей открывающей строки
			count--;									// Уменьшаем "Глубину"
		}
	}
	if (open > close)									// Если позиция последней найденной открывающей скобки больше, чем позиция позиция последней закрывающей
		open = tmp;										// Присваеваем значению позиции открывающей скобки значание предыдущей
	*op = open + 1;										// Передаем из функции позицию начала текста в скобках
	*cl = close;										// Передаем позицию самой "глубокой" закрывающей скобки
	if (open >= close) {								// Если позиция открывающей скобки не меньше, чем закрывающей
		return -1;										// Возвращаем значание, останавливающее рекурсию
	}
	return 0;											// Возвращаем значение, продолжающее рекурсию
}


void isPalindrom(char string[], int arrSize) {			// Функция, находящая все палиндромы в строке и выводящая их с строку без них на экран
	float palindromSizeMax = 0;							// Длинна самого большого палиндрома
	int palindromStartMax = 0;							// Позиция начала самогобольшого палиндрома
	int palindromEndMax = 0;							// Позиция конца самогобольшого палиндрома
	for (int i = 1; i < arrSize - 1; i++) {				// Поиск самого большого палиндрома в строке
		int palindromStart = i;							// Серединой палиндрома считаем текущий элемент массива
		int palindromEnd = i;
		float palindromSize = 0;
		if (palindromSize == 0) {						// Если в палиндроме нечетное количество символов,
			if (string[palindromStart - 1] == string[palindromEnd + 1]) { //То пропускаем центральный элемент
				palindromStart = palindromStart - 1;
				palindromEnd = palindromEnd + 2;
				palindromSize += 1.5;					// Увеличиваем счетчик размера палиндрома на 1.5
			}
		}
		while (string[palindromStart - 1] == string[palindromEnd] && palindromEnd < arrSize && palindromStart > 0) {	// Пока символ перед текущим 
				//элементом начала палиндрома равен символу после текущего элемента конца палиндрома и они не выходят за пределы строки
			palindromStart--;							// Смещаем индекс начала полиндрома на 1 влево
			palindromEnd++;								// А индекс конца палиндрома на 1 вправл
			palindromSize++;							// И увеличиваем размер найденного палиндрома на 1
		}
		if (palindromSize > palindromSizeMax) {			// Если длинна найденного палиндрома больше длинны самого длинного найденного палиндрома
			palindromStartMax = palindromStart;			// Меняем границы и размер максимального палиндрома на границы и размер текущего текущего
			palindromEndMax = palindromEnd;				
			palindromSizeMax = palindromSize;			
		}
	}
	if (palindromSizeMax > 0) {							// Если длина найденного палиндрома больше 0
		printf("The biggest palindrom is: ");			// Выводим его на экран
		for (int i = palindromStartMax; i < palindromEndMax; i++) {
			printf("%c", string[i]);
		}
		printf("\n");
		int newSize = arrSize - palindromSizeMax * 2;	// Вычисляем размер строки без палиндрома, вычитая размер этого палиндрома из длинны строки умноженного на 2 (умножение на 2 происходит потому счет размера полиндрома велся от центра в двух направлениях)
		char* temp = (char*)malloc(newSize * sizeof(char)); // Выделяем память под строку без палиндрома
		int k = 0;
		for (int i = 0; i < arrSize; i++) {				// Записываем значения в ноый массив
			if (i < palindromStartMax || i >= palindromEndMax) {	// Если символ не принадлежит палиндрому
				temp[k] = string[i];					// То записываем его в новый массив
				k++;
			}
		}
		temp[newSize] = '\0';							// Указываем конец новой строки
		printf("The string without the biggest palindrom is: ");	// Выводим строку без палиндрома на экран
		printf("%s\n", temp);
		isPalindrom(temp, newSize);						// Проводим поиск и удаение палиндромов до тех пор, пока их не останется в строке
		*temp = NULL;
		free(*temp);
	}
	
}

void palindroms(char string[]) {
	printf("Input string: ");									// Выводим входную строку на экран
	printf("%s", string);
	int size = strlen((char*)string) / sizeof(char);	// Размер переданного массива
	int newSize = 0;									// Размер массива после удаления пробелов
	for (int i = 0; i < size; i++) {					// Увеличиваем переменную значения нового массива на 1, если символ в нем не равен пробелу
		if (string[i] != ' ')
			newSize++;
	}
	char* newString = (char*)malloc(newSize * sizeof(char));	// Выделяем память под новый массив
	int j = 0;
	for (int i = 0; i < size; i++) {					// Записываем в него входную строку без пробелов
		if (string[i] != ' ') {
			newString[j] = string[i];
			j++;
		}
	}
	newString[newSize] = '\0';
	isPalindrom(newString, newSize);					// Вызываем рекурсивную функцию поиска палиндромов
	*newString = NULL;
	free(*newString);
}


int main() {
	//char string[23] = { "r{a}s{dva {chetire}t}i\0" };		// Тест 1
	//char string[26] = { "r{a}}s{dva{{ {chetire}t}i\0" };	// Тест 2
	char string[27] = { "r{a}}s{dva{{} {chetire}t}i\0" };	// Тест 3
	cut(string, 1);
	printf("\n\n");
	palindroms("abcder");
}