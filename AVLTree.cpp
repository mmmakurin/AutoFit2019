#include "AVLTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool Less(char * s1, char * key) //Сравнить два ключа
{
	return strcmp(s1, key) < 0;
}

Vertex * New(char * x)
{
	Vertex * result = new Vertex();
	result->x = x; //Не копию!
	result->Left = result->Right = NULL;
	return result;
}

int TreeHeight(Vertex* p) //Высота поддерева
{
	if (!p) return 0;
	int height = 0;
	if (p != NULL)
	{
		int l = TreeHeight(p->Left);
		int r = TreeHeight(p->Right);
		int m = (l > r) ? l : r;
		height = m + 1;
	}
	return height;
}

int bfactor(Vertex* p)//Баланс - фактор
{
	int l = TreeHeight(p->Left);
	int r = TreeHeight(p->Right);
	int b_factor = l - r;
	return b_factor;
}

//Вращения
Vertex* RR(Vertex * parent)
{
	Vertex * pivot = parent->Right;
	parent->Right = pivot->Left;
	pivot->Left = parent;
	return pivot;
}

Vertex* LL(Vertex * parent)
{
	Vertex * pivot = parent->Left;
	parent->Left = pivot->Right;
	pivot->Right = parent;
	return pivot;
}

Vertex* LR(Vertex * parent)
{
	Vertex * pivot = parent->Left;
	parent->Left = RR(pivot);
	return LL(parent);
}
Vertex* RL(Vertex * parent)
{
	Vertex * pivot = parent->Right;
	parent->Right = LL(pivot);
	return RR(parent);
}

Vertex * Balance(Vertex * p)
{
	int b_factor = bfactor(p);
	if (b_factor > 1)
		if (bfactor(p->Left) > 0)
			p = LL(p);
		else
			p = LR(p);
	else if (b_factor < -1)
		if (bfactor(p->Right) > 0)
			p = RL(p);
		else
			p = RR(p);
	return p;
}

Vertex * Insert(Vertex * p, Vertex * n) //Основная функциональность добавления
{
	if (p == NULL)
	{
		p = n;
		return p;
	}
	else if (Less(n->x,p->x))
	{
		p->Left = Insert(p->Left, n);
		p = Balance(p);
	}
	else if (Less(p->x,n->x))
	{
		p->Right = Insert(p->Right, n);
		p = Balance(p);
	}
	return p; //При совпадении игнорировать
}

Vertex * Addx(Vertex * p, char * x) //Добавить узел
{
	Vertex * newItem = New(x);
	if (p == NULL)
		p = newItem;
	else
		p = Insert(p, newItem);
	return p;
}

void DeleteTree(Vertex *& p)
{
	if (!p) return;
	DeleteTree(p->Left);
	DeleteTree(p->Right);
	p = NULL;
}

bool Like(char * s1, char * key)
{
	//Строка key полностью содержит s1
	for (unsigned int k = 0; k < strlen(s1); k++)
		if (s1[k] != key[k]) return false;
	return true;
}


Vertex * Find(Vertex * p, char *  x, int index) //Найти
{
	Vertex * result = p;
	while (true)
	{
		if (Like(x, result->x))
		{
			if (--index < 0)
				return result;
		}
		if (Less(x,result->x))
			if (result->Left == NULL) return NULL;
			else result = result->Left;
		else
			if (result->Right == NULL) return NULL;
			else result = result->Right;
	}
}


//Для отладки
void PrintTree(Vertex * p, int Level)
{
	//От меньших к большим
	if (!p) return;
	PrintTree(p->Left, Level + 1);

	for (int k = 0; k < Level; k++) printf("..");
	printf("%s\n", p->x);

	PrintTree(p->Right, Level + 1);
}

//Для отладки
Vertex * DeleteAVL(Vertex * p, char * target)
{
	Vertex * parent;
	if (p == NULL) return NULL; //Защита
	{
		//Левое поддерево
		if (target < p->x)
		{
			p->Left = DeleteAVL(p->Left, target);
			if (bfactor(p) == -2)
			{
				if (bfactor(p->Right) <= 0)
					p = RR(p);
				else
					p = RL(p);
			}
		}
		//Правое поддерево
		else if (target > p->x)
		{
			p->Right = DeleteAVL(p->Right, target);
			if (bfactor(p) == 2)
			{
				if (bfactor(p->Left) >= 0)
					p = LL(p);
				else
					p = LR(p);
			}
		}
		//Найдено!
		else
		{
			if (p->Right != NULL)
			{
				parent = p->Right;
				while (parent->Left != NULL) parent = parent->Left;
				p->x = parent->x;
				p->Right = DeleteAVL(p->Right, parent->x);
				if (bfactor(p) == 2)//Ребаланс
				{
					if (bfactor(p->Left) >= 0)
						p = LL(p);
					else
						p = LR(p);
				}
			}
			else
				return p->Left;
		}
	}
	return p;
}

