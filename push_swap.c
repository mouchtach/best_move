/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:31:47 by ymouchta          #+#    #+#             */
/*   Updated: 2025/02/12 15:50:59 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "push_swap.h"
#include <stdio.h>

void    ft_print_stacks(t_list *stack_a, t_list *stack_b)
{
    printf("\033[1;35m===========\033[0m\n");
    printf("\033[1;35mstack_a\033[0m\n");
    if (!stack_a)
        printf("\033[1;35mEMPTY!\033[0m\n");
    while (stack_a)
    {
        
        printf("\033[1;35m---\033[0m\n");
        printf("\033[1;31m| %d |\033[0m\n", stack_a->data);
        printf("\033[1;35m --- \033[0m\n");
        stack_a = stack_a->next;
    }
    printf("\033[1;35m===========\033[0m\n");
    printf("\033[1;35mstack_b\033[0m\n");
    if (!stack_b)
        printf("\033[1;35mEMPTY!\033[0m\n");
    while (stack_b)
    {
        
        printf("\033[1;35m---\033[0m\n");
        printf("\033[1;31m| %d |\033[0m\n", stack_b->data);
        printf("\033[1;35m --- \033[0m\n");
        stack_b = stack_b->next;
    }
}
int		get_range(t_list *stack)
{
	t_list *tmp;
	int		total;

	tmp = stack;
	total = 0;
	while(tmp)
	{
		total += tmp->data;
		tmp = tmp->next;
	}
	return (total / ft_lstsize(stack));
}
void	push_if_range(t_list **stack_a, t_list **stack_b)
{
	t_list *tmp;
	int 	range;

	range = get_range(*stack_a);
	// printf("%d;", range);
	tmp = *stack_a;
	while (tmp && ft_lstsize(*stack_a) > 3)
	{
		if(tmp->data <= range)
		{
			ft_move_node_a_to_top(stack_a , tmp->data);
			pb(stack_a, stack_b);
			tmp = *stack_a;
		}
		else 
			tmp = tmp->next;
	}
	tmp = *stack_a;
	while (ft_lstsize(*stack_a) > 3)
		pb(stack_a, stack_b);
	if (ft_lstsize(*stack_a) == 3)
		ft_sort_three(stack_a);
}

void	set_target(t_list **stack_a, t_list **stack_b)
{
	t_list	tmp_b;
	t_list  tmp_a;

	tmp_b = *stack_b;
	tmp_a = *stack_a;

	set_big_target();
	while (tmp_b)
	{
		tmp_b->target = tmp_a;
		while (tmp_a)
		{
			if(tmp_a->data > tmp_b->data && tmp_a->data < tmp_b->target->data)
				tmp_b->target = tmp_a;
			else 
				tmp_a = tmp_a->next;
		}
		tmp_a = *stack_a;
		tmp_b = tmp_b->next;
	}
}
void	push_swap(t_list **stack_a, t_list **stack_b)
{
	t_list *tmp;

	
	push_if_range(stack_a, stack_b);

	while (tmp)
	{
		set_target();
	}
	ft_print_stacks(*stack_a, *stack_b);



}


int	main(int argc, char **argv)
{
	t_list *stack_a;
	t_list *stack_b;
 
	int		**int_argv;
	int		count;

	stack_a = NULL;
	stack_b = NULL;
	int_argv = get_int_arg(argc, argv, &count);
	if (!int_argv)
		return (0);
	stack_a = ft_create_stack(int_argv, count);
	if (!stack_a)
		return (ft_free_int(&int_argv), 1); 
	push_swap(&stack_a, &stack_b);

	// if (count <= 5)
	// 	ft_sort_if_tive(&stack_a, &stack_b, count);
	// else
	// {
	// 	ft_push_if_range(&stack_a, &stack_b, count);
	// 	finish_sort(&stack_a, &stack_b);
	// }
	return (0);
}
