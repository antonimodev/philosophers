/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antonimo <antonimo@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 11:41:52 by antonimo          #+#    #+#             */
/*   Updated: 2024/12/13 14:05:25 by antonimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_params params;

	ac--;
	av++;
	if (ac == 5)
	{
		ft_bzero(&params, sizeof(t_params));
		if (!init_params(&params, av))
			return (2);
		printf("GUCCI\n");
	}
	else
		printf("Error: invalid number of arguments\n");
	return (2);
}
