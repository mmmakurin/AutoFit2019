/*
������������� ���������� ����� �� ���������� ��������� �������

��������� ������ - �������
���������� ���������� �������� ���� �� ��������� �����

*/
#define _CRT_SECURE_NO_WARNINGS
#include "AVLTree.h"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>

char ** voc = NULL; //��������
int N = 0; //������ ���������

//���� ����� �� ������
void LoadText(char * filename)
{
	FILE * F = fopen(filename, "r");
	//��������� ������
	char buffer[100];
	while (!feof(F))
	{
		fgets(buffer, sizeof(buffer), F);
		N++;
	}
	//�������� ������
	voc = new char*[N];
	fseek(F, 0, SEEK_SET);

	//���������
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

//������� �� �����:
//�������� ����� - ������� ������
//��������� ��������� (� ��������) 

void gotoLine(int line)
{
	COORD p = { 1, (short)line};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

char text[80] = "";
char helpers[10][80];

void ShowScreen()
{
	//�������� ����� - ������� ������
	gotoLine(1);
	printf("%40s", "");
	gotoLine(1);
	printf("�������: %s",text);

	//��������� ��������� (� ��������) - � ������� ������
	for (int i = 0; i < 10; i++)
	{
		gotoLine(4+i);
		printf("%40s", "");
		gotoLine(4 + i);
		printf("%d %s", i, helpers[i]);
	}
	gotoLine(15);
	printf("\nBackspace - ������� ��������� ������\n");
	printf("Tab - ������� ���������\n");
	printf("Esc - �������� �����\n");
	printf("Enter - ��������\n");
	gotoLine(0);
}

int main()
{
	system("chcp 1251>nul"); //���������
	//��������� �������
	LoadText("voc.txt");
	//������� ������
	CreateTree();
	//���� ���� � ����������:
	char key = Esc;
	while (true)
	{
		//����� ������ ��������� ���������
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

		while (!_kbhit()); //����� �������
		key = _getch(); //����� ������

		//���� ����� Esc - ��������
		if (key == Esc)
		{
			text[0] = 0;
			continue;
		}
		//���� �����Tab - ����� ����� (���� ��������� ���������)
		if (key == Tab)
		{
			if (!helpers[0][0]) continue; //��� ���������
			if (!helpers[1][0]) //������������ �������
			{
				strcpy(text, helpers[0]);
				continue;
			}
			gotoLine(0);
			printf("������� ����� �� 0 �� 9 ��� ������ ���������");
			key = _getch();
			gotoLine(0);
			printf("%70s","");
			key = key - '0';
			strcpy(text, helpers[key]);
			continue;
		}
		//���� ����� Enter - ��������� ������
		if (key == Enter) 
			break;

		//�����
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