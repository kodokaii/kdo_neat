/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_population.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/04 18:56:00 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_reset_population(t_kdo_population *population)
{
	ft_reset(&population->alloc);
	population->genome_count = 0;
	population->species_count = 0;
	population->fitness_max = 0.0f;
	population->fitness_avg = 0.0f;
}

void	kdo_population_alloc(t_kdo_neat *nn, t_kdo_population *population)
{
	population->genome = malloc(nn->params.genome_target_count
			* sizeof(t_kdo_genome));
	population->genome_count = 0;
	population->species = malloc(2 * nn->params.species_target_count
			* sizeof(t_kdo_species));
	population->species_count = 0;
}

void	kdo_population_init(t_kdo_neat *nn)
{
	t_kdo_genome	*genome;

	genome = kdo_get_genome(nn);
	while (genome)
	{
		kdo_genome_init(nn, genome);
		kdo_push_to_species(nn, kdo_find_species(nn, genome), genome);
		genome = kdo_get_genome(nn);
	}
}

void	kdo_save_population(t_kdo_neat *nn)
{
	t_uint	i;

	nn->params.save->population.generation_count = nn->generation_being;
	nn->params.save->population.input_count = nn->params.input_count;
	nn->params.save->population.output_count = nn->params.output_count;
	nn->params.save->population.genome_count = nn->population.genome_count;
	nn->params.save->population.node_count = 0;
	nn->params.save->population.link_count = 0;
	i = 0;
	while (i < nn->population.genome_count)
	{
		nn->params.save->population.node_count
			+= nn->population.genome[i].node_count;
		nn->params.save->population.link_count
			+= nn->population.genome[i].link_count;
		i++;
	}
}
