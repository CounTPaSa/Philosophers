/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:56:14 by merboyac          #+#    #+#             */
/*   Updated: 2024/05/28 14:57:54 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	kill_print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.table->is_anyone_died_m);
	philo.table->is_anyone_died = true;
	pthread_mutex_unlock(&philo.table->is_anyone_died_m);
	pthread_mutex_lock(&philo.table->print_mutex);
	printf("%ld %d %s\n", get_time_diff(philo.table->start_time), philo.id + 1,
		str);
	pthread_mutex_unlock(&philo.table->print_mutex);
}

void	print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.table->is_anyone_died_m);
	if ((philo.had_enough == false && philo.table->is_anyone_died == false))
	{
		pthread_mutex_lock(&philo.table->print_mutex);
		printf("%ld %d %s\n", get_time_diff(philo.table->start_time),
			philo.id + 1, str);
		pthread_mutex_unlock(&philo.table->print_mutex);
	}
	pthread_mutex_unlock(&philo.table->is_anyone_died_m);
}

int	arg_check(int ac, char **argv)
{
	int	i;

	i = 0;
	ac--;
	while (i < ac)
	{
		if (!ft_is_num(argv[i]))
			return (ft_error("Arguments must be pos and valid integers"));
		if (ft_mda_atoi(argv[i]) <= 0)
			return (ft_error("Arguments must be greater than 0"));
		i++;
	}
	return (0);
}

int	main(int ac, char **argv)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		argv++;
		if (arg_check(ac, argv))
			return (1);
		if (table_init(&table, ac, argv))
			return (1);
		if (table_mutex_init(&table))
			return (1);
		if (philo_init(&table))
			return (1);
		if (monitor_thread_init(&table))
			return (1);
		if (philo_thread_init(&table))
			return (1);
	}
	else
		return (ft_error("Wrong number of arguments"));
	return (clean_up(&table), 0);
}
