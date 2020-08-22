#include "main.h"

int main()
{
	FILE* file_pointer = fopen("files/text3.txt", "r");

	if (file_pointer != NULL)
	{
		struct LIST* list = NULL; //it is first element on list
		//list_print(list);

        printf("\n= = = File = = =\n");
		while (!feof(file_pointer)) //while it is not end of file
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
		} //cycle for first symbol to last symbol
		printf("\n= = = End file = = =\n");

		list_print(list);

		int length = list_length(list);
		struct ArrayElement* array = (struct ArrayElement*)calloc(length, sizeof(struct ArrayElement));

		if (array == NULL)
		{
			printf("array not created!!!\n");
		} //if array not created
		else
		{
			struct LIST* temp;
			int i;
			for (temp = list, i = 0; temp != NULL; i++, temp = temp->next)
			{
				array[i].counter = temp->counter;
				array[i].symbol = temp->symbol;
			}

			list = list_clean(list); //clean list

			//array_print(array, length);
			array_bubbleSort(array, length);
			//array_print(array, length);

			Shannon_Fano(
				createTree(' ', 0, "0"),
				array,
				length,
				0,
				"_",
				"_"
			);

			array_print(array, length);

			//free(array);
		} //if array created

		fclose(file_pointer);
	} //if file opened
	else
	{
		printf("FILE not openned!!!\n");
	} // if file not opened

	return 0;
}

struct NodeTree* createTree(char symbol, int counter, char* code)
{
	struct NodeTree* new_node = (struct NodeTree*)malloc(sizeof(struct NodeTree));
	if (new_node != NULL)
	{
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

	i = start + 1;
	while(abs(sum_vhodov - (sum2 + array[i].counter)) < abs(sum_vhodov - sum2)
		&& i < end)
	{
		sum2 += array[i].counter;
		i++;
	}

	Shannon_Fano(node, array, i - 1, start, "0", code);
	Shannon_Fano(node, array, end, i, "1", code);
}

void list_print(struct LIST* node)
{
	printf("\n= = = List = = =\n");
	printf("| %6s | %7s |\n", "symbol", "counter");
	printf("| %6s | %7s |\n", "------", "-------");

	for (struct LIST* temp = node; temp != NULL; temp = temp->next)
	{
        if (temp->symbol == '\n')
        {
            printf("| %6s | %7d |\n", "\\n", temp->counter);
        }
        else
        {
            printf("| %6c | %7d |\n", temp->symbol, temp->counter);
        }
	}

	printf("= = = End list = = =\n");
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
	struct LIST* temp = node;
	int i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return i;
}

struct LIST* list_clean(struct LIST* node)
{
	while (node != NULL)
	{
		struct LIST* node_for_clean = node;
		node = node->next;
		free(node_for_clean);
	}
	return node;
}

void array_print(struct ArrayElement* array, int length)
{
	printf("\n= = = Array = = =\n");
	printf("| %-8s | %-8s | %-8s | %-16s |\n", "array[i]", "counter", "symbal", "code");
	printf("| %-8s | %-8s | %-8s | %-16s |\n", "--------", "--------", "--------", "----------------");
	for (int i = 0; i < length; i++)
	{
        printf("| %-8d ", i);
        printf("| %-8d ", array[i].counter);

        if (array[i].symbol == '\n')
        {
            printf("| %-8s ", "\\n");
        }
        else
        {
            printf("| %-8c ", array[i].symbol);
        }

        printf("| %-16s ", array[i].code);
        printf("|\n");
	}
	printf("= = = End array = = =\n");
}

void array_bubbleSort(struct ArrayElement* array, int length)
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
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
