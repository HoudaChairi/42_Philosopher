/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:49:36 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/17 19:30:52 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_data *data)
{
	if (data->nbr_philo == 1)
	{
		my_usleep(current_time(), data->t_die, data);
		pthread_mutex_lock(&data->mutex_done);
		data->done++;
		pthread_mutex_unlock(&data->mutex_done);
		return ;
	}
}

void	take_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->fork[philo->id - 1]);
	print_status(philo, "has taken a fork", 0);
	one_philo(data);
	pthread_mutex_lock(&data->fork[(philo->id) % data->nbr_philo]);
	print_status(philo, "has taken a fork", 0);
}

void	*thread_function(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	print_status(philo, "is thinking", 0);
	if (philo->id % 2 == 0)
		my_usleep(current_time(), data->t_eat / 2, data);
	pthread_mutex_lock(&data->mutex_check);
	while (data->check && philo->nbr_meals != data->nbr_eat)
	{
		pthread_mutex_unlock(&data->mutex_check);
		take_forks(data, philo);
		eat(philo);
		pthread_mutex_unlock(&data->fork[philo->id - 1]);
		pthread_mutex_unlock(&data->fork[(philo->id) % data->nbr_philo]);
		sleep_and_think(philo);
		pthread_mutex_lock(&data->mutex_check);
	}
	pthread_mutex_unlock(&data->mutex_check);
	pthread_mutex_lock(&data->mutex_done);
	data->done++;
	pthread_mutex_unlock(&data->mutex_done);
	return (NULL);
}

t_philo	*create_philo(int i, t_data *data)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->id = i + 1;
	philo->data = data;
	philo->nbr_meals = 0;
	philo->last_time_eat = data->starting_time;
	philo->next = NULL;
	pthread_mutex_init(&philo->time_eat, NULL);
	if (i == 0)
		data->head_philo = philo;
	else
		ft_lstaddback(data->head_philo, philo);
	return (philo);
}

void	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = NULL;
	ft_bzero(data->thread, sizeof(pthread_t));
	ft_bzero(data->fork, sizeof(pthread_mutex_t));
	while (++i < data->nbr_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->mutex_check, NULL);
	pthread_mutex_init(&data->mutex_done, NULL);
	pthread_mutex_init(&data->mutex_meals, NULL);
	data->starting_time = current_time();
	i = 0;
	while (i < data->nbr_philo)
	{
		philos = create_philo(i, data);
		pthread_create(&data->thread[i], NULL, &thread_function, philos);
		pthread_detach(data->thread[i]);
		i++;
	}
}
