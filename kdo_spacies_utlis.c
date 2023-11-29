/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies_utlis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 23:36:45 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_reset_spacies(t_kdo_spacies *spacies)
{
	kdo_free_spacies(spacies);
	ft_bzero(spacies, sizeof(t_kdo_spacies));
}

void	kdo_push_to_spacies(t_kdo_neat *nn,
		t_kdo_spacies *spacies, t_kdo_genome *genome)
{
	t_list	*genome_element;

	genome_element = ft_lstnew(genome);
	if (!genome_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstsort_merge(&spacies->genome,
		genome_element, &kdo_genome_cmp);
	spacies->genome_count++;
}

t_kdo_spacies	*kdo_find_spacies(t_kdo_neat *nn, t_kdo_genome *genome)
{
	t_uint	spacies_index;
	float	spacies_score;
	t_uint	best_index;
	float	best_score;

	spacies_index = 0;
	best_index = 0;
	best_score = 3.402823466e+38F;
	while (spacies_index < nn->population.spacies_count
		&& nn->population.spacies[spacies_index].genome_count)
	{
		spacies_score = kdo_compatibility_score(nn, genome,
				nn->population.spacies[spacies_index].genome->data);
		if (spacies_score < best_score)
		{
			best_score = spacies_score;
			best_index = spacies_index;
		}
		spacies_index++;
	}
	if (nn->params.compatibility_limit < best_score
		&& spacies_index < nn->population.spacies_count)
		return (nn->population.spacies + spacies_index);
	return (nn->population.spacies + best_index);
}

void	kdo_update_spacies(t_kdo_neat *nn, t_kdo_spacies *spacies)
{
	t_list	*current;
	float	current_fitness;
	float	fitness_sum;
	float	fitness_max;

	fitness_max = 0.0f;
	fitness_sum = 0.0f;
	current = spacies->genome;
	while (current)
	{
		current_fitness = ((t_kdo_genome *)current->data)->fitness;
		fitness_sum += current_fitness;
		fitness_max = ft_max_double(fitness_max, current_fitness);
		current = current->next;
	}
	spacies->fitness_avg
		= fitness_sum / (float)ft_max_uint(spacies->genome_count, 1);
	spacies->no_progress_count++;
	if (nn->params.dropoff_age <= spacies->no_progress_count)
		spacies->fitness_avg *= 0.01;
	if (spacies->fitness_max < fitness_max
		|| nn->params.dropoff_age <= spacies->no_progress_count)
		spacies->no_progress_count = 0;
	spacies->fitness_max = fitness_max;
}

t_uint	kdo_spacies_fill_count(t_kdo_neat *nn)
{
	t_uint	i;

	i = 0;
	while (i < nn->population.spacies_count
		&& nn->population.spacies[i].genome_count)
		i++;
	return (i);
}