/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:41:11 by merboyac          #+#    #+#             */
/*   Updated: 2024/05/30 15:02:31 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000 + time.tv_sec * 1000));
}

long	get_time_diff(long start)
{
	return (get_time() - start);
}

void	ft_usleep(time_t time)
{
	time_t	wake_up;

	wake_up = get_time() + time;
	while (get_time() < wake_up)
		usleep(250);
}
