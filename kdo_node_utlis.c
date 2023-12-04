/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_node_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/12/04 16:30:18 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_node	*kdo_get_node(t_kdo_neat *nn,
		t_uint layer, t_node_type type, t_uint id)
{
	t_kdo_node	*node;

	node = ft_malloc(&nn->population.alloc, sizeof(t_kdo_node));
	if (!node)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	node->link = NULL;
	node->link_count = 0;
	node->input = 0.0f;
	node->output = 0.0f;
	node->bias = (ft_randf() * 2) - 1;
	node->activation_index = 0;
	node->layer = layer;
	node->type = type;
	node->id = id;
	return (node);
}

void	kdo_node_init(t_kdo_neat *nn,
			t_kdo_genome *genome_from, t_kdo_node *node)
{
	t_list	*current;

	if (node->type == INPUT_NODE)
	{
		current = genome_from->node;
		while (current)
		{
			if (((t_kdo_node *)current->data)->type == OUTPUT_NODE)
				kdo_add_link(nn, genome_from, node,
					kdo_get_link(nn, current->data));
			current = current->next;
		}
	}
}

t_kdo_node	*kdo_find_node_id(t_kdo_genome *genome_dst, t_uint id)
{
	t_list	*current;

	current = genome_dst->node;
	while (current && ((t_kdo_node *)current->data)->id != id)
		current = current->next;
	if (!current)
		return (NULL);
	return (current->data);
}

t_bool	kdo_node_is_link(t_kdo_node *node_from, t_kdo_node *node_to)
{
	t_list	*current_link;

	current_link = node_from->link;
	while (current_link)
	{
		if (((t_kdo_link *)current_link->data)->to == node_to)
			return (FT_TRUE);
		current_link = current_link->next;
	}
	return (FT_FALSE);
}

void	kdo_add_node(t_kdo_neat *nn,
		t_kdo_genome *genome_from, t_kdo_node *node)
{
	t_list	*node_element;

	node_element = ft_lstnew_alloc(&nn->population.alloc, node);
	if (!node_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstadd_back(&genome_from->node, node_element);
	genome_from->node_count++;
	nn->max_node_count
		= ft_max_uint(nn->max_node_count, genome_from->node_count);
}
