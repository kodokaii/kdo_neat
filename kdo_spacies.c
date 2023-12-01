/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_spacies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/01 19:32:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_uint	_child_count(t_kdo_neat *nn, t_kdo_spacies *spacies_src)
{
	t_uint	child_count;

	child_count = (t_uint)
		((spacies_src->fitness_avg / nn->old_population.fitness_avg)
			* (float)nn->params.genome_target_count + 1.0f);
	if (nn->params.genome_target_count
		< nn->population.genome_count + child_count)
		child_count
			= nn->params.genome_target_count - nn->population.genome_count;
	return (child_count);
}

float	_fitness_sum(t_kdo_neat *nn, t_kdo_spacies *spacies)
{
	t_list	*current;
	t_uint	parent_count;
	float	fitness_sum;

	fitness_sum = 0.0f;
	parent_count = (float)spacies->genome_count
		* nn->params.survival_limit;
	current = spacies->genome;
	while (parent_count--)
	{
		fitness_sum += ((t_kdo_genome *)current->data)->fitness;
		current = current->next;
	}
	return (fitness_sum);
}

t_kdo_genome	*_get_parent1(t_kdo_spacies *spacies, float fitness_sum)
{
	t_list	*current;
	float	random_fitness;
	float	current_fitness_sum;

	random_fitness = fitness_sum * ft_randf();
	current = spacies->genome;
	current_fitness_sum = ((t_kdo_genome *)current->data)->fitness;
	while (current_fitness_sum < random_fitness)
	{
		current = current->next;
		current_fitness_sum += ((t_kdo_genome *)current->data)->fitness;
	}
	return (current->data);
}

t_kdo_genome	*_get_parent2(t_kdo_spacies *spacies,
					t_kdo_genome *parent1, float fitness_sum)
{
	t_list	*current;
	float	random_fitness;
	float	current_fitness_sum;

	random_fitness = (fitness_sum - parent1->fitness) * ft_randf();
	current = spacies->genome;
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

void	kdo_crossover_spacies(t_kdo_neat *nn, t_kdo_spacies *spacies_src)
{
	t_uint			child_count;
	t_kdo_spacies	*spacies_dst;
	t_kdo_genome	*parent1;
	t_kdo_genome	*parent2;
	float			fitness_sum;

	if (2 <= spacies_src->genome_count)
	{
		ft_lstsort(&spacies_src->genome, kdo_genome_fitness_cmp);
		child_count = _child_count(nn, spacies_src);
		fitness_sum = _fitness_sum(nn, spacies_src);
		if (child_count && fitness_sum)
		{
			spacies_dst = kdo_get_spacies(nn);
			spacies_dst->no_progress_count = spacies_src->no_progress_count;
			while (child_count--)
			{
				parent1 = _get_parent1(spacies_src, fitness_sum);
				parent2 = _get_parent2(spacies_src, parent1, fitness_sum);
				parent1 = kdo_dup_genome(nn, parent1);
				kdo_crossover_genome(parent1, parent2);
				kdo_push_to_spacies(nn, spacies_dst, parent1);
			}
		}
	}
}
