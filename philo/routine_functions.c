/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:26:16 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/17 19:28:41 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	current_time(void)
{
	struct timeval	tv;
	size_t			timestamp_in_ms;

	gettimeofday(&tv, NULL);
	timestamp_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (timestamp_in_ms);
}

void	my_usleep(size_t start_time, int time, t_data *data)
{
	pthread_mutex_lock(&data->mutex_check);
	while (current_time() - start_time < (size_t)time && data->check)
	{
		pthread_mutex_unlock(&data->mutex_check);
		usleep(100);
		pthread_mutex_lock(&data->mutex_check);
	}
	pthread_mutex_unlock(&data->mutex_check);
	
}

void	print_status(t_philo *philo, char *s, int is_dead)
{
	pthread_mutex_lock(&philo->data->print);
	pthread_mutex_lock(&philo->data->mutex_check);
	if (philo->data->check)
	{
		printf("%ld %d %s\n", (current_time() - philo->data->starting_time),
			philo->id, s);
		if (!is_dead)
			pthread_mutex_unlock(&philo->data->print);
	}
	pthread_mutex_unlock(&philo->data->mutex_check);
}

void	eat(t_philo *philo)
{
	print_status(philo, "is eating", 0);
	pthread_mutex_lock(&philo->time_eat);
	philo->last_time_eat = current_time();
	pthread_mutex_unlock(&philo->time_eat);
	pthread_mutex_lock(&philo->data->mutex_meals);
	philo->nbr_meals++;
	pthread_mutex_unlock(&philo->data->mutex_meals);
	my_usleep(current_time(), philo->data->t_eat, philo->data);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping", 0);
	my_usleep(current_time(), philo->data->t_sleep, philo->data);
	print_status(philo, "is thinking", 0);
}
