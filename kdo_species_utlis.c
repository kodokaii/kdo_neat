/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_species_utlis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 18:52:34 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_species	*kdo_get_species(t_kdo_neat *nn)
{
	t_kdo_species	*species;

	if (nn->population.species_count < nn->params.species_target_count * 2)
	{
		species = nn->population.species + nn->population.species_count;
		ft_bzero(species, sizeof(t_kdo_species));
		nn->population.species_count++;
		return (species);
	}
	return (NULL);
}

void	kdo_push_to_species(t_kdo_neat *nn,
		t_kdo_species *species, t_kdo_genome *genome)
{
	t_list	*genome_element;

	genome_element = ft_lstnew_alloc(&nn->population.alloc, genome);
	if (!genome_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstadd_back(&species->genome, genome_element);
	species->genome_count++;
}

t_kdo_species	*kdo_find_species(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_uint			species_index;
	float			species_score;
	t_uint			best_index;
	float			best_score;
	t_kdo_species	*species;

	species = NULL;
	species_index = -1;
	best_index = 0;
	best_score = 3.402823466e+38F;
	while (++species_index < nn->population.species_count)
	{
		species_score = kdo_compatibility_score(nn, genome,
				nn->population.species[species_index].genome->data);
		if (species_score < best_score)
		{
			best_score = species_score;
			best_index = species_index;
		}
	}
	if (nn->params.compatibility_limit < best_score)
		species = kdo_get_species(nn);
	if (!species)
		species = nn->population.species + best_index;
	return (species);
}

void	kdo_update_species(t_kdo_neat *nn, t_kdo_species *species)
{
	t_list	*current;
	float	current_fitness;
	float	fitness_sum;
	float	fitness_max;

	fitness_max = 0.0f;
	fitness_sum = 0.0f;
	current = species->genome;
	while (current)
	{
		current_fitness = ((t_kdo_genome *)current->data)->fitness;
		fitness_sum += current_fitness;
		fitness_max = ft_max_double(fitness_max, current_fitness);
		current = current->next;
	}
	species->fitness_avg
		= fitness_sum / (float)ft_max_uint(species->genome_count, 1);
	species->no_progress_count++;
	if (nn->params.dropoff_age <= species->no_progress_count)
		species->fitness_avg *= 0.01;
	if (species->fitness_max < fitness_max
		|| nn->params.dropoff_age <= species->no_progress_count)
		species->no_progress_count = 0;
	species->fitness_max = fitness_max;
}
