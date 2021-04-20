#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct tree {
	int value;
    struct tree* right;
    struct tree* left;
} tree;

// Инициализация дерева
void init(tree** t)
{
    *t = malloc(sizeof(tree));
    (*t)->right = NULL;
    (*t)->left = NULL;
    (*t)->value = -2147483648;
}

// Удалить все элементы из дерева
void clean(tree* t)
{
    if (t != NULL) 
	{
        if (t->right != NULL)
            clean(t->right);
        if (t->left != NULL)
            clean(t->left);
        free(t);
    }
}

tree* find(tree* t, int value)
{
    if (t->value == value)
        return t;
    else 
	{
        if (value < t->value)
		{
            if (t->left != NULL)
                return (find(t->left, value));
            else
                return NULL;
        }
        else 
		{
            if (t->right != NULL)
                return (find(t->right, value));
            else
                return NULL;
        }
    }
}

int find_with_output(tree* t, int value)
{
    if (t->value == value) 
	{
        printf("_ ");
        if (t->left != NULL) //левый потомок
            printf("%d ", (int)t->left->value);
        else
            printf("_ ");
        if (t->right != NULL) //правый потомок
            printf("%d", (int)t->right->value);
        else
            printf("_");
    }
    else 
	{
        if (value < t->value) 
		{
            if (t->left != NULL) 
			{
                if (t->left->value == value)
				 {
                    printf("%d ", (int)t->value); //предок
                    if ((t->left->left) != NULL) //левый потомок
                        printf("%d ", (int)t->left->left->value);
                    else
                        printf("_ ");
                    if ((t->left->right) != NULL) //правый потомок
                        printf("%d", (int)t->left->right->value);
                    else
                        printf("_");
                }
                else
                    return (find_with_output(t->left, value));
            }
            else
                return 1;
        }
        else 
		{
            if (t->right != NULL) 
			{
                if (t->right->value == value) 
				{
                    printf("%d ", (int)t->value); //предок
                    if ((t->right->left) != NULL) //левый потомок
                        printf("%d ", (int)t->right->left->value);
                    else
                        printf("_ ");
                    if ((t->right->right) != NULL) //правый потомок
                        printf("%d", (int)t->right->right->value);
                    else
                        printf("_");
                }
                else
                    return (find_with_output(t->right, value));
            }
            else
                return 1;
        }
    }
    return 0;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value)
{
    if (t->value == -2147483648) 
	{
        t->value = value;
        return 0;
    }
    if (t->value == value)
        return 1;
    if (value > (t->value)) 
	{
        if ((t->right) != NULL)
            return (insert(t->right, value));
        else 
		{
            t->right = malloc(sizeof(tree));
            t->right->right = NULL;
            t->right->left = NULL;
            t->right->value = value;
            return 0;
        }
    }
    else 
	{
        if ((t->left) != NULL)
            return (insert(t->left, value));
        else 
		{
            t->left = malloc(sizeof(tree));
            t->left->right = NULL;
            t->left->left = NULL;
            t->left->value = value;
            return 0;
        }
    }
}

int find_deep(tree* t)
{
    int r_leaf = 0, l_leaf = 0;
    if ((t->right) != NULL)
        r_leaf = find_deep(t->right);
    if ((t->left) != NULL)
        l_leaf = find_deep(t->left);
    if (r_leaf > l_leaf)
        return (r_leaf + 1);
    return (l_leaf + 1);
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree** t, int value)
{
    if ((*t)->value == value) 
	{
        if ((*t)->right != NULL) 
		{
            tree *temp = (*t)->right, *temp2;
            if (temp->left != NULL) 
			{
                while (temp->left->left != NULL)
                    temp = temp->left;
                (*t)->value = temp->left->value;
                temp2 = temp->left;
                temp->left = temp2->right;
                free(temp2);
            }
            else 
			{
                temp = NULL;
                (*t)->value = (*t)->right->value;
                temp = (*t)->right;
                (*t)->right = (*t)->right->right;
                free(temp);
            }
        }
        else 
		{
            tree* temp;
            temp = (*t);
            (*t) = (*t)->left;
            free(temp);
            temp = NULL;
        }
        return 0;
    }
    else 
	{
        if (value < ((*t)->value)) 
		{
            if ((*t)->left != NULL) //Идем искать влево
                return (remove_node(&((*t)->left), value));
            else
                return 1;
        }
        else 
		{
            if (((*t)->right) != NULL) //Идем искать вправо
                return (remove_node(&((*t)->right), value));
            else
                return 1;
        }
    }
}

// Удалить минимальный элемент из поддерева
// Вернуть значение удаленного элемента
int remove_min(tree* t)
{
    tree *temp = t, *temp2;
	int val;
    if (temp->left != NULL) 
	{
        while (temp->left->left != NULL)
            temp = temp->left;
		val = temp->left->value;
        temp2 = temp->left;
        temp->left = temp2->right;
        free(temp2);
    }
    else 
	{
        temp = t->right;
		val = t->value;
        free(t);
        t = temp;
    }
    return val;
}

// Выполнить правое вращение поддерева,
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(tree** t)
{
    if (*t == NULL)
        return 1;
    tree *y = (*t)->right, *x = (*t)->left, *temp = malloc(sizeof(tree));
    if (x != NULL) 
	{
        temp->right = (*t);
    	temp->left = x->left;
    	temp->right->right = y;
    	temp->right->left = x->right;
    	temp->value = x->value;
    	free(x);
    	(*t) = temp;
    	return 0;
    }
    return 1;
}

// Выполнить левое вращение поддерева
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(tree** t)
{
    if (*t == NULL)
        return 1;
    tree *x = (*t)->left, *y = (*t)->right, *temp = malloc(sizeof(tree));
    if (y != NULL) 
	{
        temp->right = y->right;
    	temp->left = (*t);
    	temp->left->right = y->left;
    	temp->left->left = x;
    	temp->value = y->value;
    	free(y);
    	(*t) = temp;
    	return 0;
    }
    return 1;
}

// Вывести все значения из поддерева
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
int print_tree(tree* t)
{
    if (t == NULL) 
	{
        printf("-\n");
        return 1;
    }
    tree* temp = t;
    int deep = 0, i, j, k, m;
    int* arr;
    deep = find_deep(t);
    arr = (int*)malloc(sizeof(int));
    for (i = 0; i < deep; i++) 
	{
        if (i != 0) 
		{
            arr = (int*)realloc(arr, i * sizeof(int));
            for (j = 0; j < i; j++)
                arr[j] = 0;
        }
        j = 1;
        m = i;
        while (m != 0)
		{
            j = j * 2;
            m--;
        }
        while (j != 0) 
		{
            k = 0;
            temp = t;
            for (k = 0; k < i; k++) 
			{
                if (arr[k] == 0) 
				{
                    if ((temp->left) != NULL)
                        temp = temp->left;
                    else 
					{
                        k = -1;
                        break;
                    }
                }
                else 
				{
                    if ((temp->right) != NULL)
                        temp = temp->right;
                    else 
					{
                        k = -1;
                        break;
                    }
                }
            }
            if (i != 0) 
			{
                m = i - 1;
                arr[m]++;
                while (true) 
				{
                    if (arr[m] == 2) 
					{
                        arr[m] = 0;
                        m--;
                        if (m < 0)
                            break;
                        else
                            arr[m]++;
                    }
                    else
                        break;
                }
            }
            if (k == -1)
                printf("_");
            else
                printf("%d", (int)temp->value);
            j--;
            if (j != 0)
                printf(" ");
        }
        printf("\n");
    }
    return 1;
}

int count_all_nodes(tree* t)
{
    if (t == NULL)
        return 0;
    int r_leaf = 0, l_leaf = 0;
    l_leaf = count_all_nodes(t->left);
    r_leaf = count_all_nodes(t->right);
    return (l_leaf + r_leaf + 1);
}

void width_bypass(tree* t)
{
    if (t == NULL) 
	{
        printf("-\n");
        return;
    }
    tree* temp = t;
    int deep = 0, i, j, k, m, spaces = 0;
    int* arr;
    deep = find_deep(t);
    arr = (int*)malloc(sizeof(int));
    for (i = 0; i < deep; i++) 
    {
        if (i != 0) 
        {
            arr = (int*)realloc(arr, i * sizeof(int));
            for (j = 0; j < i; j++)
                arr[j] = 0;
        }
        j = 1;
        m = i;
        while (m != 0) 
        {
            j = j * 2;
            m--;
        }
        while (j != 0) 
        {
            k = 0;
            temp = t;
            for (k = 0; k < i; k++) 
            {
                if (arr[k] == 0) {
                    if ((temp->left) != NULL)
                        temp = temp->left;
                    else {
                        k = -1;
                        break;
                    }
                }
                else {
                    if ((temp->right) != NULL)
                        temp = temp->right;
                    else {
                        k = -1;
                        break;
                    }
                }
            }
            if (i != 0) 
            {
                m = i - 1;
                arr[m]++;
                while (1) {
                    if (arr[m] == 2) {
                        arr[m] = 0;
                        m--;
                        if (m < 0)
                            break;
                        else
                            arr[m]++;
                    }
                    else
                        break;
                }
            }
            if (k != -1)
            {
                if (spaces == 1) {
                    printf(" ");
                    spaces = 1;
                }
                printf("%d", (int)temp->value);
                spaces = 1;
            }
            j--;
        }
    }
    return;
}


int main()
{
    tree* t;
    int i, a;
    init(&t);

    for (i = 0; i < 7; i++) 
	{
        scanf("%d", &a);
        insert(t, a);
    }
    
    width_bypass(t);
    printf("\n");

    clean(t);
    t = NULL;

    return 0;
}  