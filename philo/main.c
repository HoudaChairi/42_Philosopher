/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:39:34 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/16 20:59:19 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	depart(int ac, char **av, t_data *data)
{
	data->nbr_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->check = 1;
	data->done = 0;
	if (ac == 6)
		data->nbr_eat = ft_atoi(av[5]);
	else
		data->nbr_eat = -1;
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (2);
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_bzero(data, sizeof(t_data));
	depart(ac, av, data);
	if (check(av, data))
		return (free(data), 1);
	create_threads(data);
	monitor(data);
	free_memory(data);
	return (0);
}
