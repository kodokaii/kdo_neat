/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_population.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 13:03:36 by nlaerema         ###   ########.fr       */
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

int	kdo_population_alloc(t_kdo_neat *nn, t_kdo_population *population)
{
	population->genome = malloc(nn->params.genome_target_count
			* sizeof(t_kdo_genome));
	if (!population->genome && nn->params.genome_target_count)
		return (EXIT_FAILURE);
	population->species = malloc(2 * nn->params.species_target_count
			* sizeof(t_kdo_species));
	if (!population->species && nn->params.species_target_count)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	kdo_population_load(t_kdo_neat *nn)
{
	t_kdo_save_population	*population_src;	
	t_kdo_genome			*genome;
	t_uint					i;

	i = 0;
	nn->params.load->genome_index = 0;
	nn->params.load->node_index = 0;
	nn->params.load->link_index = 0;
	population_src = &nn->params.load->population;
	genome = kdo_get_genome(nn);
	while (genome && i < population_src->genome_count)
	{
		kdo_genome_load(nn, genome);
		kdo_push_to_species(nn, kdo_find_species(nn, genome), genome);
		genome = kdo_get_genome(nn);
		i++;
	}
	kdo_free_save(nn->params.load);
	kdo_update_fitness(nn);
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
	kdo_run(nn);
	kdo_update_fitness(nn);
}

void	kdo_save_population(t_kdo_neat *nn)
{
	t_kdo_save_population	*population_dst;
	t_uint					i;

	population_dst = &nn->params.save->population;
	population_dst->input_count = nn->params.input_count;
	population_dst->output_count = nn->params.output_count;
	population_dst->genome_count = nn->population.genome_count;
	population_dst->node_count = 0;
	population_dst->link_count = 0;
	i = 0;
	while (i < nn->population.genome_count)
	{
		population_dst->node_count += nn->population.genome[i].node_count;
		population_dst->link_count += nn->population.genome[i].link_count;
		i++;
	}
}
