#include "shell.h"

/**
 * add_start_node - Adds a node to the start of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the node.
 * @number: Node idx used by history.
 *
 * Return: Size of list.
 */

str_list *add_start_node(str_list **head, const char *str, int number)
{
	str_list *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(str_list));
	if (!new_head)
		return (NULL);
	mem_set((void *)new_head, 0, sizeof(str_list));
	new_head->number = number;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * node_end - Adds a node to the end of the list.
 * @head: Address of pointer to the head node.
 * @str: Str field of the node.
 * @number: Node idx used by history.
 *
 * Return: Size of list.
 */

str_list *node_end(str_list **head, const char *str, int number)
{
	str_list *add_start_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	add_start_node = malloc(sizeof(str_list));
	if (!add_start_node)
		return (NULL);
	mem_set((void *)add_start_node, 0, sizeof(str_list));
	add_start_node->number = number;
	if (str)
	{
		add_start_node->str = str_dup(str);
		if (!add_start_node->str)
		{
			free(add_start_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = add_start_node;
	}
	else
		*head = add_start_node;
	return (add_start_node);
}

/**
 * print_string_list - Prints str element of a str_list linked list.
 * @ptr: Pointer to the first node.
 *
 * Return: Size of list.
 */

size_t print_string_list(const str_list *ptr)
{
	size_t i = 0;

	while (ptr)
	{
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		i++;
	}
	return (i);
}

/**
 * rm_start_node - Deletes a node at a given idx.
 * @head: Address of pointer to the first node.
 * @idx: Index of the node to delete.
 *
 * Return: 1 || 0
 */

int rm_start_node(str_list **head, unsigned int idx)
{
	str_list *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!idx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * freel - Frees all nodes of a list.
 * @head_ptr: Address of pointer to the head node.
 */

void freel(str_list **head_ptr)
{
	str_list *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
