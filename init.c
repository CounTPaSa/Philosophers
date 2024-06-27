/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:36:52 by merboyac          #+#    #+#             */
/*   Updated: 2024/05/30 15:15:32 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

int	table_init(t_table *table, int ac, char **av)
{
	int	i;

	i = 0;
	table->philo_count = ft_mda_atoi(av[i++]);
	table->time_to_die = ft_mda_atoi(av[i++]);
	table->time_to_eat = ft_mda_atoi(av[i++]);
	table->time_to_sleep = ft_mda_atoi(av[i++]);
	if (ac == 6)
		table->must_eat = ft_mda_atoi(av[i]);
	else
		table->must_eat = -1;
	table->start_time = get_time();
	table->is_anyone_died = false;
	table->stop = false;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_count);
	if (!table->forks)
		return (ft_error("Malloc error"));
	table->philos = (t_philo *)malloc(sizeof(t_philo)
			* table->philo_count);
	if (!table->philos)
		return (free(table->forks), ft_error("Malloc error"));
	return (0);
}

int	philo_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].last_meal_t = table->start_time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].had_enough = false;
		if (pthread_mutex_init(&table->philos[i].had_enough_m, NULL))
			return (destroy_philo_mutex(table, i),
				ft_error("Mutex init error"));
		if (pthread_mutex_init(&table->philos[i].last_meal_m, NULL))
			return (pthread_mutex_destroy(&table->philos[i].had_enough_m),
				destroy_philo_mutex(table, i),
				ft_error("Mutex init error"));
	}
	return (0);
}

int	table_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->is_anyone_died_m, NULL))
		return (ft_error("Mutex init error"));
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (pthread_mutex_destroy(&table->is_anyone_died_m),
			ft_error("Mutex init error"));
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (destroy_table_mutex(table, i),
				ft_error("Mutex init error"));
	}
	return (0);
}

int	philo_thread_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_main, &table->philos[i]))
			return (destroy_philo_thread(table, i),
				ft_error("Thread init error"), 1);
	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(table->philos[i].thread, NULL))
			return (destroy_philo_thread_join(table, i),
				ft_error("Thread join error"), 1);
	return (0);
}

int	monitor_thread_init(t_table *table)
{
	if (pthread_create(&table->monitor_thread, NULL, &monitor, table->philos))
		return (destroy_philo_mutex(table, table->philo_count),
			ft_error("Thread init error"));
	return (0);
}
