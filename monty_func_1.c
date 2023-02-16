#include "monty.h"

/**
 * monty_push - Pushes a value to a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 * @op_toks: op_toks
 */
void monty_push(stack_t **stack, unsigned int line_number, char **op_toks)
{
	stack_t *tmp, *new_stack;
	int i;

	new_stack = (stack_t *)malloc(sizeof(stack_t));
	if (new_stack == NULL)
	{
		set_op_tok_error(malloc_error(), op_toks);
		return;
	}

	if (op_toks[1] == NULL)
	{
		set_op_tok_error(no_int_error(line_number), op_toks);
		free(new_stack);
		return;
	}

	for (i = 0; op_toks[1][i]; i++)
	{
		if (op_toks[1][i] == '-' && i == 0)
			continue;
		if (op_toks[1][i] < '0' || op_toks[1][i] > '9')
		{
			set_op_tok_error(no_int_error(line_number), op_toks);
			return;
		}
	}
	new_stack->n = atoi(op_toks[1]);

	if (check_mode(*stack) == STACK) /* STACK mode insert at front */
	{
		tmp = (*stack)->next;
		new_stack->prev = *stack;
		new_stack->next = tmp;
		if (tmp)
			tmp->prev = new_stack;
		(*stack)->next = new_stack;
	}
	else /* QUEUE mode insert at end */
	{
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		new_stack->prev = tmp;
		new_stack->next = NULL;
		tmp->next = new_stack;
	}
}

/**
 * monty_pall - Prints the values of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 * @op_toks: op_toks
 */
void monty_pall(stack_t **stack, unsigned int line_number, char **op_toks)
{
	stack_t *tmp = (*stack)->next;
	(void) op_toks;

	while (tmp)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
	(void)line_number;
}

/**
 * monty_pint - Prints the top value of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 * @op_toks: op_toks
 */
void monty_pint(stack_t **stack, unsigned int line_number, char **op_toks)
{
	if ((*stack)->next == NULL)
	{
		set_op_tok_error(pint_error(line_number), op_toks);
		return;
	}

	printf("%d\n", (*stack)->next->n);
}


/**
 * monty_pop - Removes the top value element of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 * @op_toks: op_toks
 */
void monty_pop(stack_t **stack, unsigned int line_number, char **op_toks)
{
	stack_t *next = NULL;

	if ((*stack)->next == NULL)
	{
		set_op_tok_error(pop_error(line_number), op_toks);
		return;
	}

	next = (*stack)->next->next;
	free((*stack)->next);
	if (next)
		next->prev = *stack;
	(*stack)->next = next;
}

/**
 * monty_swap - Swaps the top two value elements of a stack_t linked list.
 * @stack: A pointer to the top mode node of a stack_t linked list.
 * @line_number: The current working line number of a Monty bytecodes file.
 * @op_toks: op_toks
 */
void monty_swap(stack_t **stack, unsigned int line_number, char **op_toks)
{
	stack_t *tmp;

	if ((*stack)->next == NULL || (*stack)->next->next == NULL)
	{
		set_op_tok_error(short_stack_error(line_number, "swap"), op_toks);
		return;
	}

	tmp = (*stack)->next->next;
	(*stack)->next->next = tmp->next;
	(*stack)->next->prev = tmp;
	if (tmp->next)
		tmp->next->prev = (*stack)->next;
	tmp->next = (*stack)->next;
	tmp->prev = *stack;
	(*stack)->next = tmp;
}
