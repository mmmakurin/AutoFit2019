#pragma once
//���� ������
typedef struct Vertex
{
	char * x;
	Vertex * Left;
	Vertex * Right;
} Vertex;

Vertex * New(char * x);//�������. x - ����
void PrintTree(Vertex * p, int Level); //������� 
Vertex * Find(Vertex * p, char * x, int index= 0); //����� �������, ������� index �� �����

Vertex * Addx(Vertex * p, char * x); //�������� ����
void DeleteTree(Vertex * &p); //������� ������
Vertex * DeleteAVL(Vertex * p, char * x); //������� ����

