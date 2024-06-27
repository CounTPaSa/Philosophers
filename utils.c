/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:02:20 by merboyac          #+#    #+#             */
/*   Updated: 2024/05/30 16:17:52 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_is_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		if (!(ft_isdigit(s[i])))
			return (0);
		i++;
	}
	return (1);
}

int	ft_mda_atoi(char *str)
{
	unsigned long long		result;
	unsigned int			i;
	int						sign;

	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!(ft_is_num(str)))
		return (ft_error("Not a number"));
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + ((str[i++]) - 48);
		if ((result > 2147483648 && sign == -1)
			|| (result > 2147483647 && sign == 1))
			return (ft_error("Number is too big"));
	}
	return (result * sign);
}

int	ft_error(char *str)
{
	printf("\033[0;31m%s\033[0m\n", str);
	return (1);
}

int	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	print(*philo, TAKE_FORK);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	ft_usleep(philo->table->time_to_die);
	print(*philo, DIED);
	philo->table->stop = true;
	return (1);
}
