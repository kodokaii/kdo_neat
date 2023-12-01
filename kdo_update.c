/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 00:34:46 by nlaerema         ###   ########.fr       */
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
	while (i < nn->population.species_count)
	{
		kdo_update_species(nn, nn->population.species + i);
		fitness_sum += nn->population.species[i].fitness_avg;
		fitness_max
			= ft_max_double(fitness_max, nn->population.species[i].fitness_max);
		i++;
	}
	nn->population.fitness_avg
		= fitness_sum / (float)nn->population.species_count;
	nn->population.fitness_max = fitness_max;
}
