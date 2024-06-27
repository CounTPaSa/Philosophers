/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:33:04 by merboyac          #+#    #+#             */
/*   Updated: 2024/06/01 15:00:46 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TAKE_FORK	"has taken a fork"
# define EATING		"is eating"
# define SLEEPING	"is sleeping"
# define THINKING	"is thinking"
# define DIED		"died"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int					id;
	int					had_enough;
	int					meals_eaten;
	long				last_meal_t;
	pthread_mutex_t		had_enough_m;
	pthread_mutex_t		last_meal_m;
	pthread_t			thread;
	struct s_table		*table;
}						t_philo;

typedef struct s_table
{
	pthread_t			monitor_thread;
	bool				stop;
	int					philo_count;
	int					must_eat;
	bool				is_anyone_died;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	pthread_mutex_t		is_anyone_died_m;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	t_philo				*philos;
}						t_table;

int			ft_mda_atoi(char *str);
int			ft_error(char *str);
long		get_time(void);
void		destroy_table_mutex(t_table *table, int limit);
void		destroy_philo_mutex(t_table *table, int limit);
void		destroy_philo_thread(t_table *table, int limit);
void		destroy_philo_thread_join(t_table *table, int limit);
void		clean_up(t_table *table);
void		*monitor(void *arg);
void		*philo_main(void *arg);
void		print(t_philo philo, char *str);
void		ft_usleep(time_t time);
long		get_time_diff(long start);
int			philo_init(t_table *table);
int			table_init(t_table *table, int ac, char **av);
int			table_mutex_init(t_table *table);
int			philo_init(t_table *table);
int			monitor_thread_init(t_table *table);
int			philo_thread_init(t_table *table);
void		kill_print(t_philo philo, char *str);
void		print(t_philo philo, char *str);
int			one_philo(t_philo *philo);
int			ft_is_num(char *str);

#endif