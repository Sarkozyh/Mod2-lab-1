#include <stdio.h>
#include <malloc.h>

void cut(char string[], int _continue) {				// �������, ���������� ��������� ���������� ����� ���������� ���� ������ 
	printf("Input string: ");							// ������� ������� ������ �� �����
	printf("%s\n", string);
	int open = 0;										// ������� ����� ���������� ����������� ������			
	int close = 0;										// ������� ����� ���������� ����������� ������
	int size = strlen((char*)string) / sizeof(char);	// ������ ����������� �������
	_continue = findInner(string, &open, &close);		// ��������, ����������� ���� �� ��� � ������ ������
	printf("Text into inner braces: ");
	for (int i = open; i < close; i++) {				// ����� ����������� ������ �� �����
		printf("%c", string[i]);
	}
	printf("\n");
	char* tmp;											// ��������������� ������������ ������, ��� ���������, ������������ ������ ���������� ���� ������
	int newSize = size - (close - open  + 2);			// ������ ������ ������� (������ ������ - ������ ������ � ������� - ���������� ������)
	tmp = (char*)malloc((newSize) * sizeof(char));		// ��������� ������ ��� �������
	int j = 0;											// ������ ������ �������
	for (int i = 0; i < strlen((char*)string) / sizeof(char); i++) {  // ������ ����������� � ����� ������
		if (i < open - 1 || i > close) {				// ���� ������� ����� �� ��������� ������,
			tmp[j] = string[i];							// �� ���������� ������ � ����� ������
			j++;
		}
	}
	tmp[newSize] = '\0';								// ��������� ����� ����� ������
	if (_continue >= 0) {								// ���� � ������ ��� ���� ������
		cut(tmp, _continue);							// ���������� ��������
	}
	else {												// ����� ������� ������
		printf("Text outside braces: ");
		printf("%s\n", string);
	}
	//free(tmp);	
	*tmp = NULL;
	free(*tmp);// ����������� ���������� ����������� ������
}


int findInner(char string[], int *op, int *cl) {
	int count = 0;										// "�������" ������
	int open = -1;										// ������� ����������� ������ (���� -1, �� ������ �� �������)
	int close = -1;										// ������� ����������� ������ (���� -1, �� ������ �� �������)
	int tmp = 0;										// ������� ���������� ����������� ������
	int max = 0;										// ������������ "�������" ������
	for (int i = 0; i < strlen((char*)string) / sizeof(char) + 1; i++) {	// ����� ����� ���������� ���� ������
		if (string[i] == '{') {							// ���� ����� ����������� ������
			open = i;									// �� �������� �� �������
			count++;									// ����������� "�������"
		}
		if (string[i] == '}' && open > 0) {				// ���� ����� ����������� ������
			if (max <= count) {							// ���� �� "�������" > ������������
				max = count;							// ��������� ����� ������������ "�������"
				close = i;								// ��������� ������� ����������� ������
			}
			tmp = open;									// ��������� ������� ���������� ����������� ������
			count--;									// ��������� "�������"
		}
	}
	if (open > close)									// ���� ������� ��������� ��������� ����������� ������ ������, ��� ������� ������� ��������� �����������
		open = tmp;										// ����������� �������� ������� ����������� ������ �������� ����������
	*op = open + 1;										// �������� �� ������� ������� ������ ������ � �������
	*cl = close;										// �������� ������� ����� "��������" ����������� ������
	if (open >= close) {								// ���� ������� ����������� ������ �� ������, ��� �����������
		return -1;										// ���������� ��������, ��������������� ��������
	}
	return 0;											// ���������� ��������, ������������ ��������
}


void isPalindrom(char string[], int arrSize) {			// �������, ��������� ��� ���������� � ������ � ��������� �� � ������ ��� ��� �� �����
	float palindromSizeMax = 0;							// ������ ������ �������� ����������
	int palindromStartMax = 0;							// ������� ������ �������������� ����������
	int palindromEndMax = 0;							// ������� ����� �������������� ����������
	for (int i = 1; i < arrSize - 1; i++) {				// ����� ������ �������� ���������� � ������
		int palindromStart = i;							// ��������� ���������� ������� ������� ������� �������
		int palindromEnd = i;
		float palindromSize = 0;
		if (palindromSize == 0) {						// ���� � ���������� �������� ���������� ��������,
			if (string[palindromStart - 1] == string[palindromEnd + 1]) { //�� ���������� ����������� �������
				palindromStart = palindromStart - 1;
				palindromEnd = palindromEnd + 2;
				palindromSize += 1.5;					// ����������� ������� ������� ���������� �� 1.5
			}
		}
		while (string[palindromStart - 1] == string[palindromEnd] && palindromEnd < arrSize && palindromStart > 0) {	// ���� ������ ����� ������� 
				//��������� ������ ���������� ����� ������� ����� �������� �������� ����� ���������� � ��� �� ������� �� ������� ������
			palindromStart--;							// ������� ������ ������ ���������� �� 1 �����
			palindromEnd++;								// � ������ ����� ���������� �� 1 ������
			palindromSize++;							// � ����������� ������ ���������� ���������� �� 1
		}
		if (palindromSize > palindromSizeMax) {			// ���� ������ ���������� ���������� ������ ������ ������ �������� ���������� ����������
			palindromStartMax = palindromStart;			// ������ ������� � ������ ������������� ���������� �� ������� � ������ �������� ��������
			palindromEndMax = palindromEnd;				
			palindromSizeMax = palindromSize;			
		}
	}
	if (palindromSizeMax > 0) {							// ���� ����� ���������� ���������� ������ 0
		printf("The biggest palindrom is: ");			// ������� ��� �� �����
		for (int i = palindromStartMax; i < palindromEndMax; i++) {
			printf("%c", string[i]);
		}
		printf("\n");
		int newSize = arrSize - palindromSizeMax * 2;	// ��������� ������ ������ ��� ����������, ������� ������ ����� ���������� �� ������ ������ ����������� �� 2 (��������� �� 2 ���������� ������ ���� ������� ���������� ����� �� ������ � ���� ������������)
		char* temp = (char*)malloc(newSize * sizeof(char)); // �������� ������ ��� ������ ��� ����������
		int k = 0;
		for (int i = 0; i < arrSize; i++) {				// ���������� �������� � ���� ������
			if (i < palindromStartMax || i >= palindromEndMax) {	// ���� ������ �� ����������� ����������
				temp[k] = string[i];					// �� ���������� ��� � ����� ������
				k++;
			}
		}
		temp[newSize] = '\0';							// ��������� ����� ����� ������
		printf("The string without the biggest palindrom is: ");	// ������� ������ ��� ���������� �� �����
		printf("%s\n", temp);
		isPalindrom(temp, newSize);						// �������� ����� � ������� ����������� �� ��� ���, ���� �� �� ��������� � ������
		*temp = NULL;
		free(*temp);
	}
	
}

void palindroms(char string[]) {
	printf("Input string: ");									// ������� ������� ������ �� �����
	printf("%s", string);
	int size = strlen((char*)string) / sizeof(char);	// ������ ����������� �������
	int newSize = 0;									// ������ ������� ����� �������� ��������
	for (int i = 0; i < size; i++) {					// ����������� ���������� �������� ������ ������� �� 1, ���� ������ � ��� �� ����� �������
		if (string[i] != ' ')
			newSize++;
	}
	char* newString = (char*)malloc(newSize * sizeof(char));	// �������� ������ ��� ����� ������
	int j = 0;
	for (int i = 0; i < size; i++) {					// ���������� � ���� ������� ������ ��� ��������
		if (string[i] != ' ') {
			newString[j] = string[i];
			j++;
		}
	}
	newString[newSize] = '\0';
	isPalindrom(newString, newSize);					// �������� ����������� ������� ������ �����������
	*newString = NULL;
	free(*newString);
}


int main() {
	//char string[23] = { "r{a}s{dva {chetire}t}i\0" };		// ���� 1
	//char string[26] = { "r{a}}s{dva{{ {chetire}t}i\0" };	// ���� 2
	char string[27] = { "r{a}}s{dva{{} {chetire}t}i\0" };	// ���� 3
	cut(string, 1);
	printf("\n\n");
	palindroms("abcder");
}