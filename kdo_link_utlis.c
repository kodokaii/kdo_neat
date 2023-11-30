/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_link_utlis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/30 13:58:46 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

t_kdo_link	*kdo_get_link(t_kdo_neat *nn, t_kdo_node *to)
{
	t_kdo_link	*link;

	link = malloc(sizeof(t_kdo_link));
	if (!link)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	link->to = to;
	link->weight = (ft_randf() * 2) - 1;
	link->enable = FT_TRUE;
	return (link);
}

void	kdo_add_link(t_kdo_neat *nn, t_kdo_genome *genome_from,
		t_kdo_node *node_from, t_kdo_link *link)
{
	t_list	*link_element;

	link_element = ft_lstnew(link);
	if (!link_element)
		kdo_neat_cleanup(nn, ERRLOC, EXIT_FAILURE);
	kdo_layer_propagation(link, node_from->layer);
	ft_lstsort_merge(&node_from->link, link_element, kdo_link_id_cmp);
	node_from->link_count++;
	genome_from->link_count++;
	nn->max_link_count
		= ft_max_uint(nn->max_link_count, genome_from->link_count);
}
