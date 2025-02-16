#include "../push_swap.h"

void	rr(t_list **stack_a, t_list **stack_b)
{
    t_list	*tmp;
	t_list	*tmp2;

	if (!stack_a || !*stack_a || !(*stack_a)->next)
		return ;
	tmp = *stack_a;
	tmp2 = *stack_a;
	*stack_a = (*stack_a)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tmp2;
	tmp2->next = NULL;

    if (!stack_b || !*stack_b || !(*stack_b)->next)
		return ;
	tmp = *stack_b;
	tmp2 = *stack_b;
	*stack_b = (*stack_b)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = tmp2;
	tmp2->next = NULL;

	write(1, "rr\n", 3);
}
