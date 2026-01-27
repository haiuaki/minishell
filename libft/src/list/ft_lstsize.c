/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juljin <juljin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:24:36 by juljin            #+#    #+#             */
/*   Updated: 2025/11/11 17:09:21 by juljin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	// Example usage of ft_lstsize
	t_list *head = ft_lstnew("Node 1");
	head->next = ft_lstnew("Node 2");
	head->next->next = ft_lstnew("Node 3");

	int size = ft_lstsize(head);
	printf("List size: %d\n", size); // Expected output: List size: 3

	// Free the list
	while (head)
	{
		t_list *temp = head;
		head = head->next;
		free(temp);
	}

	return (0);
}
*/