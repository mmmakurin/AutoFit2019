#pragma once
//Узел дерева
typedef struct Vertex
{
	char * x;
	Vertex * Left;
	Vertex * Right;
} Vertex;

Vertex * New(char * x);//Создать. x - ключ
void PrintTree(Vertex * p, int Level); //Вывести 
Vertex * Find(Vertex * p, char * x, int index= 0); //Найти похожий, который index по счету

Vertex * Addx(Vertex * p, char * x); //Добавить узел
void DeleteTree(Vertex * &p); //Удалить дерево
Vertex * DeleteAVL(Vertex * p, char * x); //Удалить узел

