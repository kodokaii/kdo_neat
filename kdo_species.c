/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_species.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/05 20:08:09 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static t_uint	_child_count(t_kdo_neat *nn, t_kdo_species *species_src)
{
	t_uint	child_count;

	child_count = (t_uint)
		((species_src->fitness_avg * (float)nn->params.genome_target_count)
			/ (nn->old_population.fitness_avg
				* nn->old_population.species_count));
	if (nn->params.genome_target_count
		< nn->population.genome_count + child_count)
		child_count
			= nn->params.genome_target_count - nn->population.genome_count;
	return (child_count);
}

static float	_fitness_sum(t_kdo_neat *nn, t_kdo_species *species)
{
	t_list	*current;
	t_uint	parent_count;
	float	fitness_sum;

	fitness_sum = 0.0f;
	parent_count = (float)species->genome_count
		* nn->params.survival_limit;
	current = species->genome;
	while (parent_count--)
	{
		fitness_sum += ((t_kdo_genome *)current->data)->fitness;
		current = current->next;
	}
	return (fitness_sum);
}

static t_kdo_genome	*_get_parent1(t_kdo_species *species, float fitness_sum)
{
	t_list	*current;
	float	random_fitness;
	float	current_fitness_sum;

	random_fitness = fitness_sum * ft_randf();
	current = species->genome;
	current_fitness_sum = ((t_kdo_genome *)current->data)->fitness;
	while (current_fitness_sum < random_fitness)
	{
		current = current->next;
		current_fitness_sum += ((t_kdo_genome *)current->data)->fitness;
	}
	return (current->data);
}

static t_kdo_genome	*_get_parent2(t_kdo_species *species,
					t_kdo_genome *parent1, float fitness_sum)
{
	t_list	*current;
	float	random_fitness;
	float	current_fitness_sum;

	random_fitness = (fitness_sum - parent1->fitness) * ft_randf();
	current = species->genome;
	if (current->data == parent1)
		current = current->next;
	current_fitness_sum = ((t_kdo_genome *)current->data)->fitness;
	while (current_fitness_sum < random_fitness)
	{
		current = current->next;
		if (current->data != parent1)
			current_fitness_sum += ((t_kdo_genome *)current->data)->fitness;
	}
	return (current->data);
}

void	kdo_crossover_species(t_kdo_neat *nn, t_kdo_species *species_src)
{
	t_uint			child_count;
	t_kdo_species	*species_dst;
	t_kdo_genome	*parent1;
	t_kdo_genome	*parent2;
	float			fitness_sum;

	ft_lstsort(&species_src->genome, kdo_genome_fitness_cmp);
	child_count = _child_count(nn, species_src);
	fitness_sum = _fitness_sum(nn, species_src);
	if (child_count)
	{
		species_dst = kdo_get_species(nn);
		species_dst->no_progress_count = species_src->no_progress_count;
		parent1 = kdo_dup_genome(nn, species_src->genome->data);
		kdo_push_to_species(nn, species_dst, parent1);
		while (--child_count && 2 <= species_src->genome_count)
		{
			parent1 = _get_parent1(species_src, fitness_sum);
			parent2 = _get_parent2(species_src, parent1, fitness_sum);
			parent1 = kdo_dup_genome(nn, parent1);
			kdo_crossover_genome(parent1, parent2);
			kdo_push_to_species(nn, species_dst, parent1);
		}
	}
}
