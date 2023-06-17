/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:31:47 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/17 19:09:46 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_memory(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->mutex_done);
	while (data->done != data->nbr_philo)
	{
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->mutex_done);
		pthread_mutex_lock(&data->mutex_done);
	}
	pthread_mutex_unlock(&data->mutex_done);
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&data->fork[i]);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->mutex_check);
	pthread_mutex_destroy(&data->mutex_done);
	lstclear(data->head_philo);
	free(data);
}

int	check_death(t_data *data, t_philo *head)
{
	pthread_mutex_lock(&head->time_eat);
	if ((current_time() - head->last_time_eat >= (size_t)head->data->t_die)
		&& (head->nbr_meals != data->nbr_eat))
	{
		pthread_mutex_unlock(&head->time_eat);
		print_status(head, "died", 1);
		pthread_mutex_lock(&data->mutex_check);
		data->check = 0;
		pthread_mutex_unlock(&data->mutex_check);
		return (1);
	}
	pthread_mutex_unlock(&head->time_eat);
	return (0);
}

void	*monitor(t_data *data)
{
	t_philo	*head;

	while (1)
	{
		head = data->head_philo;
		while (head != NULL)
		{
			pthread_mutex_lock(&data->mutex_done);
			if (data->done == data->nbr_philo)
			{
				pthread_mutex_lock(&data->mutex_check);
				data->check = 0;
				pthread_mutex_unlock(&data->mutex_check);
				pthread_mutex_unlock(&data->mutex_done);
				return (NULL);
			}
			pthread_mutex_unlock(&data->mutex_done);
			if (check_death(data, head))
				return (NULL);
			head = head->next;
		}
	}
	return (NULL);
}
