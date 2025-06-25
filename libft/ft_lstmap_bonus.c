/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklymova <eklymova@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:22:14 by eklymova          #+#    #+#             */
/*   Updated: 2024/10/29 14:05:48 by eklymova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_node;
	void	*p1;

	new = (NULL);
	while (lst)
	{
		p1 = f(lst->content);
		if (!p1)
		{
			ft_lstclear(&new, del);
			break ;
		}
		new_node = ft_lstnew(p1);
		if (!new_node)
		{
			ft_lstclear(&new, del);
			del(p1);
			break ;
		}
		ft_lstadd_back(&new, new_node);
		lst = lst->next;
	}
	return (new);
}
