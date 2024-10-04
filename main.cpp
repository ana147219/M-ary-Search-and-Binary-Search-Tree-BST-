#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <stdio.h>


using namespace std;

typedef struct Node
{
	int k, low, high;
	struct Node* left = nullptr;
	struct Node* right = nullptr;
	struct Node* parent;
	struct Node* duplicate = nullptr;
}node;

void push(node** stack, int* top, node* t)
{
	if (*top == 0) *top = 1;
	else *top = *top + 1;
	stack[*top] = t;
}

node* pop(node** stack, int* top)
{
	if (*top == 0)
	{
		cout << "Underflow";
		return nullptr;
	}
	node* next = stack[*top];
	*top = *top - 1;
	return next;
}

bool empty(node** stack, int top)
{
	if (top == 0) return true;
	else return false;
}

void insert(node** queue, int* front, int* rear, int size, node* x)
{
	*rear = (*rear + 1);
	if (*front == 0) *front = 1;
	queue[*rear] = x;
}
node* get(node** queue, int* front, int* rear, int size)
{
	node* x = queue[*front];
	if (*front == *rear) *front = *rear = 0;
	else *front = (*front + 1);
	return x;
}
bool q_empty(node** queue, int* front, int* rear)
{
	if (*front == *rear) return true;
	else return false;
}
int dimension()
{
	int n;
	while (true)
	{
		cout << "Unesite dimeziju niza: ";
		cin >> n;
		if (n > 0) break;
		else
			cout << "Nekorektna duzina niza; ponovo unesite parametar" << endl;
	}
	return n;
}

int* manuel_array(int k)
{
	int x;
	bool flag = false;
	int* array = new int[k];
	for (int i = 0;i < k;i++)
	{
		cout << "Unesite element niza: ";
		cin >> x;
		for (int j = 0;j < i;j++)
		{
			if (x == array[j])
			{
				i--;
				flag = true;
			}
		}
		if (flag)
		{
			cout << "Ponovljena vrednost kljuca;ponovo unesite element" << endl;
			flag = false;
		}
		else
			array[i] = x;
	}
	return array;
}

int* read_from_file(int* n)
{
	*n = 9;
	int* array = new int[*n];
	char file[50];
	while (true)
	{
		cout << "Uneiste ime fajla: ";
		cin >> file;
		FILE* f = fopen(file, "r");
		if (f != nullptr)
		{
			for (int i = 0;i < *n;i++) fscanf(f, "%d", &array[i]);
			fclose(f);
			break;
		}
		else cout << "Nepostojeci fajl" << endl;
	}
	return array;
}

int* random(int k, int low, int high)
{
	int* array = new int[k];
	for (int i = 0;i < k;i++)
	{
		bool flag = true;
		int x = low + rand() % ((high + 1) - low);
		for (int j = 0;j < i;j++)
		{
			if (x == array[j])
			{
				i--;
				flag = false;
			}
		}
		if (flag) array[i] = x;
	}
	return array;
}

int* form_array(int* n)
{
	cout << "Odaberite jednu od sledecih opcija:" << endl;
	cout << "1. Unos niza kljuceva" << endl;
	cout << "2. Generisanje niza kljuceva" << endl;
	int option;
	cin >> option;
	int* array = nullptr;
	if (option == 1)
	{
		int x;
		cout << "Odaberite jednu od sledecih opcija:" << endl;
		cout << "1. Rucni unos niza kljuceva" << endl;
		cout << "2. Unos niza kljuceva iz datoteke" << endl;
		cin >> x;
		if (x == 1)
		{
			array = manuel_array(*n);
		}
		else
			array = read_from_file(n);
	}
	else if (option == 2)
	{
		int low, high;
		cout << "Unesite donju granicu niza: ";
		cin >> low;
		cout << "Unesite gornju granicu niza: ";
		cin >> high;
		array = random(*n, low, high);
	}
	sort(array, array + *n, greater<int>());
	return array;
}

int mary_search(int* array, int low, int m, int k, int n, int* eval)
{
	int cnt, high, mid;
	high = n - 1;
	while (low <= high)
	{
		mid = (high - low) / m;
		for (int i = 0;i < m;i++)
		{
			cnt = low + mid;
			if (i == (m - 1)) cnt = high;
			*eval = *eval + 1;
			if (k <= array[low] && k >= array[cnt]) break;
			low = cnt + 1;
		}
		if (k == array[cnt - 1])
		{
			return (cnt - 1);
			*eval += 1;
		}
		else if (k == array[low]) return (low);
		high = cnt - 1;
	}
	return -1;
}

int* optimal_mary(int* array, int* keys, int n, int s, int m, int* eval)
{
	int* P = new int[s];
	int i, j, low = 0;
	for (i = 0;i < s;i++) P[i] = -1;
	i = j = 0;
	while (i < n && j < s)
	{
		P[j] = mary_search(array, low, m, keys[j], n, eval);
		if (P[j] >= 0) low = P[j] + 1;
		++j;
		i = low;
	}
	return P;
}

node* create(int k, int low, int high)
{
	node* t = new node;
	t->k = k;
	t->parent = nullptr;
	t->low = low;
	t->high = high;
	return t;
}

void left_part(node** stack, int* top, int low, int high, node* next, int* array)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		next->left = create(array[mid], (mid + 1), high);
		next->left->parent = next;
		high = mid - 1;
		next = next->left;
		push(stack, top, next);
	}
	next->left = nullptr;
}

node* form_tree(int* array, int n, node** stack, int* top)
{
	sort(array, array + n);
	node* next;
	int low = 0, high = n - 1;
	int mid = (low + high) / 2;
	node* root = create(array[mid], mid + 1, high);
	high = mid - 1;
	push(stack, top, root);
	left_part(stack, top, low, high, root, array);
	while (empty(stack, *top) == false)
	{
		next = pop(stack, top);
		low = next->low;
		high = next->high;
		if (low <= high)
		{
			mid = (low + high) / 2;
			next->right = create(array[mid], mid + 1, high);
			next->right->parent = next;
			high = mid - 1;
			next = next->right;
			push(stack, top, next);
			left_part(stack, top, low, high, next, array);
		}
		else
		{
			next->right = nullptr;
		}
	}
	return root;
}

node* BST_search(node* root, int k, int* cnt)
{
	node* t = root;
	while (t != nullptr && k != t->k)
	{
		*cnt += 1;
		if (k > t->k) t = t->right;
		else t = t->left;
	}
	return t;
}

bool is_leafe(node* t)
{
	if (t->left == nullptr && t->right == nullptr) return true;
	else return false;
}

void menu_tree(node* root, node** stack, int* top, int x)
{
	if (root == nullptr)
	{
		cout << "Stablo je obrisano";
		return;
	}
	if (x == 1)
	{
		int k;
		cout << "Unesite vrednost kljuca koji zelite da dodate: ";
		cin >> k;
		node* nouvel = create(k, 0, 0);
		node* t = root;
		node* parent = nullptr;
		while (t != nullptr && k != t->k)
		{
			parent = t;
			if (k > t->k) t = t->right;
			else t = t->left;
		}
		if (parent == nullptr) root = nouvel;
		else if (t == nullptr)
		{
			if (nouvel->k > parent->k) parent->right = nouvel;
			else parent->left = nouvel;
		}
		else if (t != nullptr)
		{
			node* pom = t;
			while (pom->duplicate != nullptr) pom = pom->duplicate;
			pom->duplicate = nouvel;
		}
	}
	else if (x == 2)
	{
		int k, s;
		cout << "Unesite vrednost kljuca koji trazite: ";
		cin >> k;
		if (BST_search(root, k, &s) != nullptr) cout << "Kljuc postoji u stablu";
		else cout << "Kljuc ne postoji u stablu";
	}
	else if (x == 3)
	{
		int size = 10000;
		node** queue = new node * [size];
		int front = 0, rear = 0;
		node* next = root;
		node* fake = create(-1, 0, 0);
		insert(queue, &front, &rear, size, next);
		insert(queue, &front, &rear, size, nullptr);
		while (queue[front] != nullptr)
		{
			next = get(queue, &front, &rear, size);
			cout << next->k << " ";
			if (next->left != nullptr) insert(queue, &front, &rear, size, next->left);
			else if (next->left == nullptr && next->k != -1)
				insert(queue, &front, &rear, size, fake);
			if (next->right != nullptr) insert(queue, &front, &rear, size, next->right);
			else if (next->right == nullptr && next->k != -1)
				insert(queue, &front, &rear, size, fake);
			if (queue[front] == nullptr)
			{
				cout << endl;
				next = get(queue, &front, &rear, size);
				insert(queue, &front, &rear, size, next);
			}
		}
	}
	else if (x == 4)
	{
		double average = 0;
		int s, cnt;
		int* S;
		cout << "Unesite duzinu sekvence, zatim i kljuceve: ";
		cin >> s;
		S = manuel_array(s);
		sort(S, S + s, greater<int>());
		for (int i = 0;i < s;i++)
		{
			cnt = 1;
			node* next = BST_search(root, S[i], &cnt);
			average += cnt;
		}
		average = average / s;
		cout << endl << "Prosecan broj koraka potreban za pretrazivanje ovih kljuceva: " << average;
	}
}

double evaluation(int* array, int* keys, int n, int s, int m)
{
	int eval, index, average = 0;
	for (int i = 0;i < s;i++)
	{
		eval = 0;
		index = mary_search(array, 0, m, keys[i], n, &eval);
		average += eval;
	}
	return ((average * 1.0) / s);
}

void menu(int* array, int n)
{
	cout << endl << "Odaberite jednu od sledecih opcija:" << endl;
	cout << "1. Pretraga niza m-arnom pretragom" << endl;
	cout << "2. Optimizovana pretraga niza na niz kljuceva m-arnom pretragom" << endl;
	cout << "3. Evaluacija performansi m-arnog pretrazivanja" << endl;
	cout << "4. Evaluacija performansi optimizovanog m-arnog pretrazivanja" << endl;
	cout << "5. Formiranje stabla na osnovu uredjenog niza kljuceva" << endl;
	cout << "6. Prekid programa" << endl;
	int option;
	cin >> option;

	while (true)
	{
		if (option == 1)
		{
			int k, m, low = 0, eval = 0;
			cout << "Unesite parametar pretrage: ";
			cin >> m;
			cout << "Unesite vrednost kljuca: ";
			cin >> k;
			int index = mary_search(array, low, m, k, n, &eval);
			cout << index << endl;
		}
		else if (option == 2)
		{
			int m, s, eval;
			int* P;
			cout << "Unesite duzinu niza kljuceva: ";
			cin >> s;
			int* keys = manuel_array(s);
			sort(keys, keys + s, greater<int>());
			cout << "Sortiran niz kljuceva: ";
			for (int i = 0;i < s;i++) cout << keys[i] << " ";
			cout << endl << "Unesite parametar pretrage: ";
			cin >> m;
			P = optimal_mary(array, keys, n, s, m, &eval);
			for (int i = 0;i < s;i++) cout << P[i] << " ";
		}
		else if (option == 3)
		{
			double average;
			int m = 2, s;
			int* S;
			cout << "Unesite duzinu sekvence kljuceva: ";
			cin >> s;
			S = manuel_array(s);
			sort(S, S + s, greater<int>());
			for (int i = 2;i < 7;i++)
			{
				average = evaluation(array, S, n, s, i);
				cout << "Prosecan broj koraka za pretrazivanje ove sekvence kljuceva za m=" << i << " je: " << average << endl;
			}
		}
		else if (option == 4)
		{
			double average;
			int m = 2, s, eval;
			int* S, * pom;
			cout << "Unesite duzinu sekvence kljuceva: ";
			cin >> s;
			S = manuel_array(s);
			sort(S, S + s, greater<int>());
			for (int i = 2;i < 7;i++)
			{
				eval = 0;
				pom = optimal_mary(array, S, n, s, i, &eval);
				average = eval * 1.0 / s;
				cout << "Prosecan broj koraka za pretrazivanje ove sekvence kljuceva za m=" << i << " je: " << average << endl;
			}
		}
		else if (option == 5)
		{
			node** stack = new node * [10000];
			int top = 0;
			node* root = form_tree(array, n, stack, &top);
			int x;
			cout << "1. Umetanje novog kljuca u stablo" << endl;
			cout << "2. Pretraga stabla na zadati kljuc" << endl;
			cout << "3. Formatiran ispis sadrzaja stabla" << endl;
			cout << "4. Evaluacija performansi pretrazivanja u BST-u" << endl;
			cout << "5. Brisanje stabla iz memorije" << endl;
			cout << "6. Povratak na prethodne opcije" << endl;
			while (true)
			{
				cout << endl << "Izaberite jednu od stavki: " << endl;
				cin >> x;
				cout << endl;
				if (x == 6) break;
				else if (x == 5)
				{
					node* next = root;
					while (next != nullptr)
					{
						push(stack, &top, next);
						next = next->left;
					}
					while (empty(stack, top) == false)
					{
						next = pop(stack, &top);
						if (next->k > 0)
						{
							next->k = (next->k) * (-1);
							push(stack, &top, next);
							next = next->right;
							while (next != nullptr)
							{
								push(stack, &top, next);
								next = next->left;
							}
						}
						else
						{
							cout << "Obrisan cvor sa kljucem" << next->k << endl;
							delete next;
						}
					}
					root = nullptr;
				}
				menu_tree(root, stack, &top, x);
			}
		}
		else if (option == 6) break;
		sort(array, array + n, greater<int>());
		cout << endl << "Odaberite jednu od prethodnih opcija: ";
		cin >> option;
	}
}

int main()
{
	int n = dimension();
	int* array = form_array(&n);
	for (int i = 0;i < n;i++) cout << array[i] << " ";
	menu(array, n);
}
