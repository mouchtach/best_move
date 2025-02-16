/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:31:47 by ymouchta          #+#    #+#             */
/*   Updated: 2025/02/16 17:16:43 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void print_stacks(t_list *stack_a, t_list *stack_b)
{
    printf("\nSTACKS:\n");
    printf("┌────────────────────────────┬────────────────────────────┐\n");
    printf("│         Stack A           │         Stack B           │\n");
    printf("├──────┬───────┬───────┬────┼──────┬───────┬───────┬────┤\n");
    printf("│ cost │ Data  │ Target│    │ cost │ Data  │ Target│    │\n");
    printf("├──────┼───────┼───────┼────┼──────┼───────┼───────┼────┤\n");

    while (stack_a || stack_b)
    {
        printf("│");

        // Print Stack A
        if (stack_a)
        {
            printf(" %4d │ %5d │ %5d │    ", stack_a->cost, stack_a->data,
                   stack_a->target ? stack_a->target->data : -1);
            stack_a = stack_a->next;
        }
        else
            printf("      │       │       │    ");

        printf("│");

        // Print Stack B
        if (stack_b)
        {
            printf(" %4d │ %5d │ %5d │    ", stack_b->cost, stack_b->data,
                   stack_b->target ? stack_b->target->data : -1);
            stack_b = stack_b->next;
        }
        else
            printf("      │       │       │    ");

        printf("│\n");
    }

    printf("└──────┴───────┴───────┴────┴──────┴───────┴───────┴────┘\n\n");
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
void	set_min_target(t_list **stack_a, t_list **node)
{
	t_list *tmp;
	t_list *small;


	tmp = *stack_a;
	small = *stack_a;
	while (tmp)
	{
		if(small->data > tmp->data)
			small = tmp;
		tmp = tmp->next;
	}
	(* node)->target = small;
}
void	set_target(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp_b;
	t_list  *tmp_a;

	tmp_b = *stack_b;
	tmp_a = *stack_a;

	while (tmp_b)
	{
		tmp_b->target = tmp_a;
		while (tmp_a)
		{
			if(tmp_a->data > tmp_b->data )
			{
				if (tmp_b->data > tmp_b->target->data || tmp_a->data < tmp_b->target->data)
					tmp_b->target = tmp_a;
			}
			tmp_a = tmp_a->next;
		}
		if(tmp_b->data > tmp_b->target->data)
			set_min_target(stack_a, &tmp_b);
		tmp_a = *stack_a;
		tmp_b = tmp_b->next;
	}
}

void set_index(t_list **stack_a, t_list **stack_b)
{
	t_list *tmp;
	int		index;

	index = 0;
	tmp = * stack_a;
	while (tmp)
	{
		tmp->index = index;
		index++;
		tmp = tmp->next;
	}
	tmp = *stack_b;
	index = 0;
	while (tmp)
	{
		tmp->index = index;
		index++;
		tmp = tmp->next;
	}
}
int ft_get_cost(t_list *stack, t_list *tmp)
{
	int	len;
	int coust;

	coust = 0;
	len = tmp->index;
	if (len == 0)
		return (0);
	if ((int)tmp->index <= ft_lstsize(stack) / 2)
	{
		while (len-- > 0)
			coust++;
	}
	else
	{
		while (len++ < ft_lstsize(stack))
			coust++;
	}
	return (coust);
}

void	set_cost(t_list **stack_a, t_list **stack_b)
{
	t_list	*tmp_b;

	tmp_b = *stack_b;
	while (tmp_b)
	{
		tmp_b->cost =  ft_get_cost(*stack_b, tmp_b) + ft_get_cost(*stack_a, tmp_b->target);
		tmp_b = tmp_b->next;	
	}
}

t_list	*get_min_cost(t_list	*stack)
{
	t_list *small;

	small = stack;
	while (stack)
	{
		if (small->cost > stack->cost)
			small = stack;
		stack = stack->next;
	}
	return(small);
}

void	set_position(t_list **stack_a, t_list **stack_b)
{
	t_list *tmp;
	int		len_a;
	int		len_b;

	tmp = *stack_a;
	len_a = ft_lstsize(*stack_a);
	len_b = ft_lstsize(*stack_b);
	while (tmp)
	{
		if(tmp->index <= len_a / 2)
			tmp->position = 1;
		else 
			tmp->position = 0;
		tmp = tmp->next;
	}
	tmp = *stack_b;
	while (tmp)
	{
		if(tmp->index <= len_b / 2)
			tmp->position = 1;
		else 
			tmp->position = 0;
		tmp = tmp->next;
	}
}

void	go_top_double(t_list **stack_a, t_list **stack_b, t_list **tmp, int pos)
{
	
	while(pos == 1 && (*tmp)->index && (*tmp)->target->index)
	{
		rr(stack_a, stack_b);
		set_index(stack_a, stack_b);
	}
	while(pos == 0 && (*tmp)->index && (*tmp)->target->index)
	{
		rrr(stack_a, stack_b);
		set_index(stack_a, stack_b);
	}
}
void	push_to_target(t_list **stack_a, t_list **stack_b)
{
	t_list *tmp;

	tmp = get_min_cost(*stack_b);
	if (tmp->index != 0 && tmp->target->index != 0)
	{
		if(tmp->position == 1 && tmp->target->position == 1)
			go_top_double(stack_a, stack_b, &tmp, 1);
		else if(tmp->position == 0 && tmp->target->position == 0)
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
	t_list *tmp;

	
	push_if_range(stack_a, stack_b);

	tmp = *stack_b;

	while (tmp)
	{
		set_target(stack_a, stack_b);
		set_index(stack_a, stack_b); 
		set_cost(stack_a, stack_b);
		set_position(stack_a, stack_b);
		push_to_target(stack_a, stack_b);
		pa(stack_a, stack_b);
		tmp = *stack_b;
	}
	ft_move_node_a_to_top(stack_a, get_min_stack(*stack_a));
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
	ft_free_stack(&stack_a);
	ft_free_stack(&stack_b);
	return (0);
}
