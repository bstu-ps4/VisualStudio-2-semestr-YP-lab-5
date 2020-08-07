#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LIST
{
	struct LIST* next;
	char symbol;
	int counter;
};

struct ArrayElement
{
	char symbol;
	int counter;
	char* code;
};

struct NodeTree
{
	struct NodeTree* top;
	struct NodeTree* left;
	struct NodeTree* right;
	char symbol;
	int counter;
	char* code;
};

struct NodeTree* createTree(char symbol, int counter, char* code)
{
	struct NodeTree* new_node = (struct NodeTree*)malloc(sizeof(struct NodeTree));
	if (new_node != NULL) {
		new_node->left = NULL;
		new_node->right = NULL;
		new_node->symbol = symbol;
		new_node->counter = counter;
		new_node->code = (char*)calloc(strlen(code), sizeof(char));
		if (new_node->code != NULL)
		{
			strcpy(new_node->code, code);
		}
	}
	return new_node;
}

void addingTree(struct NodeTree* node, char symbol, int counter, char* code)
{
	while (node != NULL)
	{
		if (node->counter > counter)
		{
			node = node->left;
		}
		else if (node->counter < counter)
		{
			node = node->right;
		}
		else
		{
			return;
		}
	}
}

void Shannon_Fano(
	struct NodeTree* node,
	struct ArrayElement* array,
	int end,
	int start,
	char* vetka,
	char* fullvetka
)
{
	addingTree(node, array[start].symbol, array[start].counter, vetka);
	char* code = (char*)calloc(strlen(fullvetka) + strlen(vetka), sizeof(char));
	code = strcat(code, fullvetka);
	code = strcat(code, vetka);

	if (start == end)
	{
		array[start].code = (char*)calloc(strlen(code), sizeof(char));
		strcpy(array[start].code, code);
		return;
	}
	int i;
	int sum_vhodov = 0;
	for (i = start; i <= end; i++)
	{
		sum_vhodov += array[i].counter;
	}

	int sum2;
	sum_vhodov /= 2;
	sum2 = array[start].counter;

	for
		(
			i = start + 1;
			abs(sum_vhodov - (sum2 + array[i].counter))
			<
			abs(sum_vhodov - sum2)
			&&
			i < end;
			i++
			)
	{
		sum2 += array[i].counter;
	}

	Shannon_Fano(node, array, i - 1, start, "0", code);
	Shannon_Fano(node, array, end, i, "1", code);
}

void list_print(struct LIST* node)
{
	printf("\n\nLIST:\n");

	if (node == NULL)
	{
		printf("NULL\n");
	}

	struct LIST* temp = node;
	while (temp != NULL)
	{
		printf("%-5d - %c\n", temp->counter, temp->symbol);
		temp = temp->next;
	}

	printf("\n\n");
}

struct LIST* list_addNode(struct LIST* node, char symbol)
{
	struct LIST* new_node = (struct LIST*)malloc(sizeof(struct LIST));
	if (new_node == NULL)
	{
		return node;
	}
	else
	{
		new_node->next = node;
		new_node->symbol = symbol;
		new_node->counter = 1;
		return new_node;
	}
}

int list_length(struct LIST* node)
{
	int i;
	struct LIST* temp;
	for (temp = node, i = 0; temp != NULL; temp = temp->next, i++) {

	}
	return i;
}

void array_print(struct ArrayElement* array, int length)
{
	printf("\n\nArray:\n");
	int i;
	for (i = 0; i < length; i++)
	{
		printf("array[%4d] = { counter: %4d; symbol: %c; code: %s }\n", i, array[i].counter, array[i].symbol, array[i].code);
	}
	printf("\n\n");
}

void array_bubbleSort(struct ArrayElement* array, int length)
{
	int i, j;
	for (i = 0; i < length; i++)
	{
		for (j = 0; j < length; j++)
		{
			if (array[i].counter > array[j].counter)
			{
				struct ArrayElement temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}

int main()
{
	FILE* file_pointer = fopen("files/text3.txt", "r");

	if (file_pointer != NULL)
	{
		struct LIST* list = NULL;

		list_print(list);

		while (!feof(file_pointer))
		{
			char symbol = getc(file_pointer);

			struct LIST* temp = list;
			while (temp != NULL)
			{
				if (temp->symbol == symbol)
				{
					(temp->counter)++;
					break;
				}

				temp = temp->next;
			}

			if (temp == NULL)
			{
				list = list_addNode(list, symbol);
			}

			printf("%c", symbol);
		}


		list_print(list);




		int length = list_length(list);
		printf("%d", length);
		struct ArrayElement* array = (struct ArrayElement*)calloc(length, sizeof(struct ArrayElement));



		if (array == NULL)
		{
			printf("array not created!!!\n");
		}
		else
		{

			struct LIST* temp;
			int i;
			for (temp = list, i = 0; temp != NULL; i++, temp = temp->next)
			{
				array[i].counter = temp->counter;
				array[i].symbol = temp->symbol;
			}


			array_print(array, length);
			array_bubbleSort(array, length);
			array_print(array, length);

			Shannon_Fano(
				createTree(' ', 0, "0"),
				array,
				length,
				0,
				"",
				""
			);

			array_print(array, length);

			free(array);
		} 

		fclose(file_pointer);
	}
	else
	{
		printf("FILE not openned!!!\n");
	} 

	return 0;
}
