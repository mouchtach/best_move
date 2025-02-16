/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymouchta <ymouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 10:31:35 by ymouchta          #+#    #+#             */
/*   Updated: 2025/02/16 21:26:13 by ymouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	ft_sort(int **tab, int count)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	if (!tab)
		return ;
	while (i < count)
	{
		j = i + 1;
		while (j < count)
		{
			if (*tab[i] > *tab[j])
			{
				tmp = *tab[i];
				*tab[i] = *tab[j];
				*tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	tab[i] = NULL;
}

int	ft_get_cost(t_list *stack, t_list *tmp)
{
	int	len;
	int	coust;

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

int	**ft_sort_int_tab(int **tab, int count)
{
	int	**sort_int;
	int	i;

	i = 0;
	sort_int = NULL;
	sort_int = (int **)malloc(sizeof(int *) * (count + 1));
	if (!sort_int)
		return (ft_free_int(&sort_int), ft_free_int(&tab), NULL);
	while (i < count)
	{
		sort_int[i] = malloc(sizeof(int));
		if (!sort_int[i])
			return (ft_free_int(&sort_int), ft_free_int(&tab), NULL);
		*sort_int[i] = *tab[i];
		i++;
	}
	ft_sort(sort_int, count);
	return (sort_int);
}
