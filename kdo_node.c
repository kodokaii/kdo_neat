/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/16 13:31:06 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_node	*kdo_get_node(t_kdo_neat *nn,
		t_uint layer, t_node_type type, t_uint id)
{
	t_kdo_node	*node;

	node = ft_buf_alloc(&nn->population.genome_buf.node,
			nn->population.genome_buf.node_count * sizeof(t_kdo_node),
			sizeof(t_kdo_node));
	if (!node)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	node->link = NULL;
	node->link_count = 0;
	node->input = 0.0f;
	node->bias = (ft_randf() * 2) - 1;
	node->activation_index = 0;
	node->layer = layer;
	node->type = type;
	node->id = id;
	nn->population.genome_buf.node_count++;
	return (node);
}

void	kdo_mutate_node(t_kdo_neat *nn, t_kdo_node *node)
{
	float	rng;

	rng = ft_randf();
	if (rng <= nn->params.function_change_prob)
		node->activation_index = ft_rand() % nn->activation_func_count;
	if (rng <= nn->params.weight_random_prob)
		node->bias = (ft_randf() * 2) - 1;
	else if (rng <= nn->params.weight_shift_prob)
		node->bias += ((ft_randf_norm() * 2) - 1) / 10;
}

void	kdo_feed_forward_node(t_kdo_neat *nn, t_kdo_node *node)
{
	float	output;
	t_list	*current;

	output = (nn->activation_func[node->activation_index])
		(node->input + node->bias);
	current = node->link;
	while (current)
	{
		kdo_feed_forward_link(current->content, output);
		current = current->next;
	}
	node->input = 0;
}

t_bool	kdo_node_is_link(t_kdo_node *node_from, t_kdo_node *node_to)
{
	t_list	*current_link;

	current_link = node_from->link;
	while (current_link)
	{
		if (((t_kdo_link *)current_link->content)->to == node_to)
			return (FT_TRUE);
		current_link = current_link->next;
	}
	return (FT_FALSE);
}

void	kdo_add_node(t_kdo_neat *nn, t_kdo_genome *genome, t_kdo_node *node,
		int (*cmp)())
{
	t_list	*node_element;

	node_element = ft_lstnew(node);
	if (!node_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	ft_lstsort_merge(&genome->node, node_element, cmp);
	genome->node_count++;
}
