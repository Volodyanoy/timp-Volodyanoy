#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct list
{
    struct node *head;  // начало списка
    struct node *tail;  // конец списка
} list;

typedef struct node
{
    int value;          // значение, которое хранит узел 
    struct node *next;	// ссылка на следующий элемент списка
    struct node *prev;	// ссылка на предыдущий элемент списка
} node;
// инициализация пустого списка
void init(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}
// удалить все элементы из списка
void clean(list *l)
{
	node *temp1 = l->head, *temp2;
	while (temp1->next != NULL)	
	{
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	} 
	free (temp1);
	l->head = NULL;
}
// проверка на пустоту списка
bool is_empty(list *l)
{
	if (l->head == NULL)
	{
		return true;
	}
	return false;
}
// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value)
{
	if (l->head == NULL)
	{
		return NULL;
	}
	node *temp = l->head;
	while (temp->next != NULL)
	{
		if (temp->value == value)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
	node *node_added = (node*) malloc(sizeof(node));
	node_added->value = value;
	node_added->next = NULL;
	if (l->head == NULL)
	{
		node_added->prev = NULL;
		l->head = node_added;
	}
	else if (l->head->next == NULL)
	{
		node_added->prev = l->head;
		l->head->next = node_added;
	}
	else
	{
		node_added->prev = l->tail;
		l->tail->next = node_added;
	}
	l->tail = node_added;
    return 0;
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value)
{
	node *node_added = (node*) malloc(sizeof(node));
	node_added->value = value;
	node_added->prev = NULL;
	if (l->head == NULL)
	{
		node_added->next = NULL;
		l->tail = node_added;
	}
	else if (l->head->next == NULL)
	{
		node_added->next = l->head;
		l->tail->prev = node_added;
	}
	else
	{
		node_added->next = l->head;
		l->head->prev = node_added;
	}
	l->head = node_added;
    return 0;
}
// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value, list*l)
{
	node *node_added = (node*) malloc(sizeof(node));
	if (n->next == NULL)
	{
		node_added->prev = n;
		n->next = node_added;
		l->tail = node_added;
		node_added->value=value;
		return 0;
	}
	node_added->value = value;
	node_added->prev = n;
	node_added->next = n->next;
	n->next->prev = node_added;
	n->next = node_added;
    return 0;
}
// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(node *n, int value, list* l)
{
	node *node_added = (node*) malloc(sizeof(node));
	if (n->prev == NULL)
	{
		node_added->next = n;
		n->prev = node_added;
		l->head = node_added;
		node_added->value=value;
		return 0;
	}
	node_added->value = value;
	node_added->prev = n->prev;
	n->prev->next = node_added;
	node_added->next = n;
	n->prev = node_added;
    return 0;
}
// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value)
{
	if (l->head == NULL) 
	{
        return 1;
    }
	node *temp = l->head;
	while (temp->value != value)
	{
		if (temp->next == NULL)//если нет такого элемента
		{
			return 1;
		}
		temp = temp->next;
	}
	if (temp == l->head)
	{
		temp->next->prev = NULL;
		l->head = temp->next;
	}
	else if (temp == l->tail)
	{
		temp->prev->next = NULL;
		l->tail = temp->prev;	
	}
	else
	{
		temp->prev->next = temp->next;
    	temp->next->prev = temp->prev;
	}
	free(temp);
    return 0;
}
// удалить последний элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_last(list *l, int value)
{
	if (l->tail == NULL) 
	{
        return 1;
    }
	node *temp = l->tail;
	while (temp->value != value)
	{
		if (temp->prev == NULL)
		{
			return 1;
		}
		temp = temp->prev;
	}
	if (temp == l->head)
	{
		temp->next->prev = NULL;
		l->head = temp->next;
	}
	else if (temp == l->tail)
	{
		temp->prev->next = NULL;
		l->tail = temp->prev;	
	}
	else
	{
		temp->prev->next = temp->next;
    	temp->next->prev = temp->prev;
	}
	free(temp);
    return 0;
}
// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l)
{
	node *temp = l->head;
	while (temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}
// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l)
{
	node *temp = l->tail;
	while (temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->prev;
    }
    printf("\n");
}


int main()
{
	list* l1;
    int n, i, a, k, m, t, j, x, u, y, z, r;

    scanf("%d", &n);
	init(l1);

    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        push_back(l1, a);
    }
    print(l1);

    for (i = 1; i <= 3; i++)
    {
        scanf("%d", &k);
        if (find(l1, k) == NULL)
		{
            printf("0 ");
		}
        else
		{
            printf("1 ");
		}
    }
	printf("\n");

    scanf("%d", &m);
    push_back(l1, m);
    print_invers(l1);

    scanf("%d", &t);
    push_front(l1, t);
    print(l1);

    scanf("%d", &j);
    scanf("%d", &x);
	node *temp_ptr = l1->head;
	for (i = 1; i < j; i++)
	{
		temp_ptr = temp_ptr->next;
	}
    insert_after(temp_ptr, x, l1);
    print_invers(l1);

	scanf("%d", &u);
    scanf("%d", &y);
	temp_ptr = l1->head;
	for (i = 1; i < u; i++)
	{
		temp_ptr = temp_ptr->next;
	}
    insert_before(temp_ptr, y, l1);
    print(l1);

    scanf("%d", &z);
	remove_first(l1, z);
    print_invers(l1);

    scanf("%d", &r);
	remove_last(l1, r);
    print(l1);

    clean(l1);
    return 0;
}
