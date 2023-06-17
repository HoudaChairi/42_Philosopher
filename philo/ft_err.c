/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 19:46:28 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/16 12:20:16 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_err(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int	check(char **argv, t_data *data)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 2147483648 || check_err(argv[i])
			|| data->nbr_philo == 0 || data->nbr_philo > 200
			|| data->nbr_eat == 0 || data->t_die == 0
			|| data->t_eat == 0 || data->t_sleep == 0)
			return (2);
		i++;
	}
	return (0);
}
