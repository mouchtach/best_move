/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:31:47 by ymouchta          #+#    #+#             */
/*   Updated: 2025/02/16 21:21:02 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	go_top_double(t_list **stack_a, t_list **stack_b, t_list **tmp, int pos)
{
	while (pos == 1 && (*tmp)->index && (*tmp)->target->index)
	{
		rr(stack_a, stack_b);
		set_index(stack_a, stack_b);
	}
	while (pos == 0 && (*tmp)->index && (*tmp)->target->index)
	{
		rrr(stack_a, stack_b);
		set_index(stack_a, stack_b);
	}
}

static void	prepar_to_push(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	tmp = get_min_cost(*stack_b);
	if (tmp->index != 0 && tmp->target->index != 0)
	{
		if (tmp->position == 1 && tmp->target->position == 1)
			go_top_double(stack_a, stack_b, &tmp, 1);
		else if (tmp->position == 0 && tmp->target->position == 0)
			go_top_double(stack_a, stack_b, &tmp, 0);
		else
		{
			ft_move_node_a_to_top(stack_a, tmp->target->data);
			ft_move_node_b_to_top(stack_b, tmp->data);
		}
	}
	if (tmp->target->index == 0)
		ft_move_node_b_to_top(stack_b, tmp->data);
	else if (tmp->index == 0)
		ft_move_node_a_to_top(stack_a, tmp->target->data);
	else
		return ;
}

void	push_swap(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp;

	push_if_range(stack_a, stack_b);
	tmp = *stack_b;
	while (tmp)
	{
		set_target(stack_a, stack_b);
		set_index(stack_a, stack_b);
		set_cost(stack_a, stack_b);
		set_position(stack_a, stack_b);
		prepar_to_push(stack_a, stack_b);
		pa(stack_a, stack_b);
		tmp = *stack_b;
	}
	ft_move_node_a_to_top(stack_a, get_min_stack(*stack_a));
}

int	main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
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
	if (count <= 3)
		ft_sort_if_three(&stack_a, &stack_b, count);
	else 
		push_swap(&stack_a, &stack_b);
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	return (0);
}
