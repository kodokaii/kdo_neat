/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_population_utlis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 12:24:10 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_reset_population(t_kdo_population *population)
{
	t_uint	i;

	i = 0;
	while (i < population->genome_count)
		kdo_reset_genome(population->genome + i++);
	population->genome_count = 0;
	i = 0;
	while (i < population->spacies_count)
		kdo_reset_spacies(population->spacies + i++);
	population->fitness_max = 0.0f;
	population->fitness_avg = 0.0f;
}

void	kdo_population_alloc(t_kdo_neat *nn, t_kdo_population *population)
{
	population->genome = ft_calloc(nn->params.genome_target_count,
			sizeof(t_kdo_genome));
	population->genome_count = 0;
	population->spacies = ft_calloc(2 * nn->params.spacies_target_count,
			sizeof(t_kdo_spacies));
	population->spacies_count = 2 * nn->params.spacies_target_count;
}

void	kdo_population_init(t_kdo_neat *nn, t_kdo_population *population)
{
	t_uint	i;

	i = 0;
	kdo_population_alloc(nn, population);
	while (i < nn->params.genome_target_count)
	{
		kdo_genome_init(nn, population->genome + i++);
		population->genome_count++;
	}
}
