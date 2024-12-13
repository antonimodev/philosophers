/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:25:03 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/13 14:02:23 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <stdbool.h>

typedef struct s_params
{
	int	philos_num;
	int	eat_times;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
}	t_params;

// parse.c
bool	check_av(char **av, bool (*function)(void *));
bool	is_number(void *param);
bool	init_params(t_params *params, char **av);
int		ft_atoi(char *str);

// philosophers_utils.c
void	ft_bzero(void *ptr, size_t n);


#endif