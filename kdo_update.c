/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 23:37:54 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_update_fitness(t_kdo_neat *nn)
{
	float	fitness_sum;
	float	fitness_max;
	t_uint	i;

	i = 0;
	fitness_sum = 0.0f;
	fitness_max = 0.0f;
	while (i < nn->population.spacies_count)
	{
		kdo_update_spacies(nn, nn->population.spacies + i);
		fitness_sum += nn->population.spacies[i].fitness_avg;
		fitness_max
			= ft_max_double(fitness_max, nn->population.spacies[i].fitness_max);
		i++;
	}
	nn->population.fitness_avg
		= fitness_sum / (float)kdo_spacies_fill_count(nn);
	nn->population.fitness_max = fitness_max;
}
