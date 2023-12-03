/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/03 00:54:21 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

static void	_save_link(t_kdo_save_link **link_dst, t_kdo_link *link_src)
{
	(*link_dst)->to_id = link_src->to->id;
	(*link_dst)->weight = link_src->weight;
	(*link_dst)->enable = link_src->enable;
	(*link_dst)++;
}

static void	_save_node(t_kdo_save_node **node_dst, t_kdo_save_link **link_dst,
			t_kdo_node *node_src)
{
	t_list	*current;

	(*node_dst)->link_count = node_src->link_count;
	(*node_dst)->bias = node_src->bias;
	(*node_dst)->activation_index = node_src->activation_index;
	(*node_dst)->layer = node_src->layer;
	(*node_dst)->type = node_src->type;
	(*node_dst)->id = node_src->id;
	current = node_src->link;
	while (current)
	{
		_save_link(link_dst, current->data);
		current = current->next;
	}
	(*node_dst)++;
}

static void	_save_genome(t_kdo_save_genome **genome_dst,
		t_kdo_save_node **node_dst,
		t_kdo_save_link **link_dst,
		t_kdo_genome *genome_src)
{
	t_list	*current;

	(*genome_dst)->node_count = genome_src->node_count;
	(*genome_dst)->link_count = genome_src->link_count;
	current = genome_src->node;
	while (current)
	{
		_save_node(node_dst, link_dst, current->data);
		current = current->next;
	}
	(*genome_dst)++;
}

static void	_save_population(t_kdo_save_neat *nn_save, t_kdo_neat *nn)
{
	t_uint	i;

	nn_save->population.generation_count = nn->generation_being;
	nn_save->population.input_count = nn->params.input_count;
	nn_save->population.output_count = nn->params.output_count;
	nn_save->population.genome_count = nn->population.genome_count;
	nn_save->population.node_count = 0;
	nn_save->population.link_count = 0;
	i = 0;
	while (i < nn->population.genome_count)
	{
		nn_save->population.node_count += nn->population.genome[i].node_count;
		nn_save->population.link_count += nn->population.genome[i].link_count;
		i++;
	}
}

void	kdo_neat_save(t_kdo_neat *nn, t_kdo_save_neat *nn_save)
{
	t_kdo_save_genome	*genome;
	t_kdo_save_node		*node;
	t_kdo_save_link		*link;
	t_uint				i;

	_save_population(nn_save, nn);
	genome
		= malloc(nn_save->population.genome_count * sizeof(t_kdo_save_genome));
	node = malloc(nn_save->population.node_count * sizeof(t_kdo_save_node));
	link = malloc(nn_save->population.link_count * sizeof(t_kdo_save_link));
	if (!genome || !node || !link)
	{
		free(genome);
		free(node);
		free(link);
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	}
	nn_save->genome = genome;
	nn_save->node = node;
	nn_save->link = link;
	i = 0;
	while (i < nn->population.genome_count)
		_save_genome(&genome, &node, &link, nn->population.genome + i++);
}
