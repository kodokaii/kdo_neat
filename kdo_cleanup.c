/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/15 20:03:41 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_free_node(t_kdo_node *node)
{
	ft_lstclear(&node->link, NULL);
	node->link_count = 0;
}

void	kdo_free_genome(t_kdo_genome *genome)
{
	ft_lstclear(&genome->node, &kdo_free_node);
	genome->link_count = 0;
	genome->node_count = 0;
}

void	kdo_free_spacies(t_kdo_spacies *spacies)
{
	ft_lstclear(&spacies->genome, &kdo_free_genome);
	spacies->genome_count = 0;
}

void	kdo_free_population(t_kdo_population *population)
{
	t_uint	i;

	i = 0;
	while (i < population->genome_count)
		kdo_free_genome(population->genome + i++);
	population->genome_count = 0;
	i = 0;
	while (i < population->spacies_count)
		kdo_free_genome(population->genome + i++);
	population->spacies_count = 0;
	ft_buf_free(&population->genome_buf.link);
	population->genome_buf.link_count = 0;
	ft_buf_free(&population->genome_buf.node);
	population->genome_buf.node_count = 0;
}

void	kdo_neat_cleanup(t_kdo_neat *nn, char *str_error, int error)
{
	kdo_free_population(&nn->population);
	kdo_free_population(&nn->old_population);
	free(nn->input);
	nn->input = NULL;
	nn->input_count = 0;
	free(nn->output);
	nn->output = NULL;
	nn->output_count = 0;
	ft_dprintf(STDERR_FILENO, "neat: %s\n", str_error);
	exit(error);
}
