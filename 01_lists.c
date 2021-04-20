#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>


typedef struct node 
{ 						// создание ноды связанного списка
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;

// инициализация пустого списка
void init(node **head)
{
    *head = (node*)malloc(sizeof(node));
	(*head)->value = 0;
    (*head)->next = NULL;
}
// удалить все элементы из списка
void clean(node *head)
{
    node *temp = head;
    do
    {
        temp = temp->next;
        free(head);
        head = temp;
    } while (head != NULL);
}
// проверка на пустоту списка
bool is_empty(node *head)
{
    if (head == NULL)
	{
        return 0;
	}
    else
	{
        return 1;
	}
}
// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(node *head, int value)
{
    node *temp = head;
    while (true)
    {
        if (temp == NULL)
		{
            return NULL;
		}
        if ((temp->value) == value)
		{
            return ((node*)temp);
		}
        temp = temp->next;
    }
}
// вставка значения в конец списка, вернуть 0 если успешно
int push_back(node *head, int value)
{
    node *temp = (node*)malloc(sizeof(node));
    temp = head;
    while (temp->next != NULL)
	{
        temp = temp->next;
	}
    temp->next = (node*)malloc(sizeof(node));
    temp = temp->next;
    temp->value = value;
    temp->next = NULL;
    return 0;
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(node **head, int value)
{
    node *temp = (node*)malloc(sizeof(node));
    temp->value = value;
    temp->next = (*head);
    (*head) = temp;
    return 0;
}
// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value)
{
    node *temp = (node*)malloc(sizeof(node));
	node *temp1;
    temp1 = (node*)n->next;
    n->next =(node*)temp;
    temp->value = value;
    temp->next = temp1;
    return 0;
}
// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(node *head, int value)
{
    node *temp = head;
    if (head != NULL)
    {
        while (true)
        {
            if ((temp->next) == NULL)
			{
				return 1;
			}               
            if ((temp->next->value) == value)
            {
                node *temp1 = (node*)malloc(sizeof(node));
                temp1 = temp->next->next;
                free(temp->next);
                temp->next = temp1;
                return 0;
            }
            temp = temp->next;
        }
    }
    else
	{
        return 1;
	}
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    node *head, *temp;
    int n, i, a, k, m, t, b, j, x, z;

    scanf("%d", &n);
    init(&head);

    for (i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        push_back(head, a);
    }
	
	node *temp_ptr = (node*)malloc(sizeof(node));
    temp_ptr = head->next;
    free(head);
	head = temp_ptr;
    print(head);

    for (i = 1; i <= 3; i++)
    {
        scanf("%d", &k);
        if (find(head, k) == NULL)
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
    push_back(head, m);
    print(head);

    scanf("%d", &t);
    push_front(&head, t);
    print(head);

    scanf("%d", &j);
    scanf("%d", &x);
	temp_ptr = (node*)head;
	for (i = 1; i < j; i++)
	{
		temp_ptr = temp_ptr->next;
	}
    insert_after(temp_ptr, x);
    print(head);

    scanf("%d", &z);
    if (head->value == z)
    {
        temp = head->next;
        free(head);
        head = temp;
    }
    else
	{
		remove_node(head, z);
	}	
    print(head);
    clean(head);
    return 0;
}