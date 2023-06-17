/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchairi <hchairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:40:02 by hchairi           #+#    #+#             */
/*   Updated: 2023/06/17 19:20:06 by hchairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				nbr_eat;
	int				check;
	int				done;
	size_t			starting_time;
	struct s_philo	*head_philo;
	pthread_t		thread[250];
	pthread_mutex_t	fork[250];
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_check;
	pthread_mutex_t	mutex_meals;
	pthread_mutex_t	mutex_done;
}	t_data;

typedef struct s_philo
{
	int					id;
	int					nbr_meals;
	long				last_time_eat;
	pthread_mutex_t		time_eat;
	struct s_data		*data;
	struct s_philo		*next;
}	t_philo;

long	ft_atoi(char *str);
int		check_err(char *s);
int		check(char **argv, t_data *data);
void	create_threads(t_data *data);
void	ft_lstaddback(t_philo *node, t_philo *new);
void	*monitor(t_data *data);
void	ft_bzero(void *s, size_t n);
void	lstclear(t_philo *node);
void	my_usleep(size_t start_time, int time, t_data *data);
void	print_status(t_philo *philo, char *s, int is_dead);
void	eat(t_philo *philo);
void	free_memory(t_data *data);
void	sleep_and_think(t_philo *philo);
size_t	current_time(void);

#endif
