/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 15:26:29 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/15 17:55:00 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)b;
	while (i < len)
	{
		s[i] = c;
		i++;
	}	
	return ((void *)s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
	return ((void)s);
}

long	ft_atoi(char *str)
{
	long	res;

	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (2147483648);
		str++;
		if (*str == 0)
			return (2147483648);
	}
	while ((*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		if ((res > 2147483647) || (res > 2147483648))
			return (2147483648);
		str++;
	}
	if (*str != 0)
		return (2147483648);
	return (res);
}

void	ft_lstaddback(t_philo *node, t_philo *new)
{
	if (!node || !new)
		return ;
	while (node->next != NULL)
		node = node->next;
	node->next = new;
	new->next = NULL;
}

void	lstclear(t_philo *node)
{
	t_philo	*tmp;
	t_philo	*tmp_next;

	if (!node)
		return ;
	tmp = node;
	while (tmp)
	{
		tmp_next = tmp->next;
		free (tmp);
		tmp = tmp_next;
	}
	node = NULL;
}
