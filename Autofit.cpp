/*
автодополение введенного слова по изначально заданному словарю

построить дерево - словарь
предложить подходящие варианты слов по введенной части

*/
#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

char ** voc = NULL; //Словарик
int N = 0; //размер словарика

//Одно слово на строке
void LoadText(char * filename)
{
	FILE * F = fopen(filename, "r");
	//Посчитать строки
	char buffer[100];
	while (!feof(F))
	{
		fgets(buffer, sizeof(buffer), F);
		N++;
	}
	//Выделить память
	voc = new char*[N];
	fseek(F, 0, SEEK_SET);

	//Загрузить
	N = 0;
	while (!feof(F))
	{
		fgets(buffer, sizeof(buffer), F);
		voc[N] = new char[strlen(buffer) + 1];
		strcpy(voc[N++], buffer);
	}

	fclose(F);
}

Vertex * Root = NULL;

void CreateTree()
{
	for (int k = 0; k < N; k++)
		Root = Addx(Root, voc[k]);
}

const char Esc = 27;
const char Enter = 13;
const char Tab = '\t';
const char BackSpace = '\b';

//Вывести на экран:
//Вводимое слово - верхняя строка
//Найденные подсказки (с номерами) 

void gotoLine(int line)
{
	COORD p = { 1, (short)line};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

char text[80] = "";
char helpers[10][80];

void ShowScreen()
{
	//Вводимое слово - верхняя строка
	gotoLine(1);
	printf("%40s", "");
	gotoLine(1);
	printf("Введено: %s",text);

	//Найденные подсказки (с номерами) - с третьей строки
	for (int i = 0; i < 10; i++)
	{
		gotoLine(4+i);
		printf("%40s", "");
		gotoLine(4 + i);
		printf("%d %s", i, helpers[i]);
	}
	gotoLine(15);
	printf("\nBackspace - удалить последний символ\n");
	printf("Tab - выбрать подсказку\n");
	printf("Esc - очистить слово\n");
	printf("Enter - окончить\n");
	gotoLine(0);
}

int main()
{
	system("chcp 1251>nul"); //Кодировка
	//Загрузить словарь
	LoadText("voc.txt");
	//Создать дерево
	CreateTree();
	//Ввод слов с подсказкой:
	char key = Esc;
	while (true)
	{
		//Найти первые несколько подсказок
		for (int k = 0; k < 10; k++)
		{
			Vertex *v = Find(Root, text, k);
			if (v)
			{
				strcpy(helpers[k], v->x);
			}
			else
				helpers[k][0] = 0;
		}


		ShowScreen();

		while (!_kbhit()); //Ждать нажатия
		key = _getch(); //Новый символ

		//если нажат Esc - сбросить
		if (key == Esc)
		{
			text[0] = 0;
			continue;
		}
		//если нажатTab - ждать цифры (если несколько вариантов)
		if (key == Tab)
		{
			if (!helpers[0][0]) continue; //Нет вариантов
			if (!helpers[1][0]) //Единственный вариант
			{
				strcpy(text, helpers[0]);
				continue;
			}
			gotoLine(0);
			printf("Введите цифру от 0 до 9 для выбора подсказки");
			key = _getch();
			gotoLine(0);
			printf("%70s","");
			key = key - '0';
			strcpy(text, helpers[key]);
			continue;
		}
		//если нажат Enter - закончить работу
		if (key == Enter) 
			break;

		//иначе
		int l = strlen(text);
		if (key == BackSpace)
		{
			if (l > 0)
				text[--l] = 0;
			continue;
		}
		text[l++] = key;
		text[l] = 0;
	}

}