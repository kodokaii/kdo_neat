/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/13 21:42:40 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

int	main(int argc, char *argv[])
{
	(void)argv;
	if (1 < argc)
	{
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
		printf("rng = %f\n", (float)ft_rand() / (float)INT_MAX);
	}
	return (0);
}
