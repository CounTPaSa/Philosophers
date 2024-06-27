/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:20:57 by merboyac          #+#    #+#             */
/*   Updated: 2024/05/30 16:19:07 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	destroy_table_mutex(t_table *table, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->is_anyone_died_m);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}

void	destroy_philo_mutex(t_table *table, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
	{
		pthread_mutex_destroy(&table->philos[i].had_enough_m);
		pthread_mutex_destroy(&table->philos[i].last_meal_m);
	}
	destroy_table_mutex(table, table->philo_count);
}

void	destroy_philo_thread(t_table *table, int limit)
{
	int	i;

	i = -1;
	table->stop = true;
	while (++i < limit)
		pthread_detach(table->philos[i].thread);
	destroy_philo_mutex(table, table->philo_count);
}

void	destroy_philo_thread_join(t_table *table, int limit)
{
	int	i;

	i = -1;
	while (++i < limit)
		pthread_detach(table->philos[i].thread);
	destroy_philo_thread(table, table->philo_count);
}

void	clean_up(t_table *table)
{
	int	i;

	i = -1;
	pthread_join(table->monitor_thread, NULL);
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos[i].had_enough_m);
		pthread_mutex_destroy(&table->philos[i].last_meal_m);
		pthread_mutex_destroy(&table->philos[i].table->forks[i]);
	}
	pthread_mutex_destroy(&table->is_anyone_died_m);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->philos);
}
