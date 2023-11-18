/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_random.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/16 20:43:30 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_list	*kdo_get_random_link(t_kdo_node *node)
{
	return (ft_lstget(node->link, ft_rand() % node->link_count));
}

t_list	*kdo_get_random_node(t_kdo_genome *genome)
{
	return (ft_lstget(genome->node, ft_rand() % genome->node_count));
}

t_list	*kdo_get_node_free_link(t_kdo_genome *genome)
{
	t_list	*node;
	t_uint	node_index;
	t_uint	after_node_count;

	node_index = ft_rand() % genome->node_count;
	after_node_count = genome->node_count - node_index - 1;
	node = ft_lstget(genome->node, node_index);
	while (((t_kdo_node *)(node->data))->link_count == after_node_count)
	{
		ft_lstnext_roll(&node, genome->node);
		if (!after_node_count)
			after_node_count = genome->node_count;
		after_node_count--;
	}
	return (node);
}

t_list	*kdo_get_node_no_link_yet(t_list *node_from)
{
	t_list	*node;
	t_uint	node_index;

	node_index = ft_rand() % ft_lstsize(node_from->next);
	node = ft_lstget(node_from->next, node_index);
	while (kdo_node_is_link(node_from->data, node->data))
		ft_lstnext_roll(&node, node_from->next);
	return (node);
}

t_list	*kdo_get_linked_node(t_kdo_genome *genome)
{
	t_list	*node;

	node = kdo_get_random_node(genome);
	while (!((t_kdo_node *)(node->data))->link_count)
		ft_lstnext_roll(&node, genome->node);
	return (node);
}
