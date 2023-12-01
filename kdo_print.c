/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>	+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/29 13:32:59 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "kdo_neat.h"

void	kdo_print_link(t_kdo_link *link, int fd)
{
	char	*color;

	color = COLOR_GREEN;
	if (!link->enable)
		color = COLOR_RED;
	dprintf(fd, "%s-(%s%f%s)->%s%u", color, COLOR_WHITE, link->weight, color,
		COLOR_RESET, link->to->id);
}

void	kdo_print_node(t_kdo_node *node, int fd)
{
	t_list	*current;

	current = node->link;
	dprintf(fd, "\nNODE: %u\n(in:%f|b:%f|l:%u|ou:%f)\n",
		node->id, node->input, node->bias, node->layer, node->output);
	while (current)
	{
		kdo_print_link(current->data, fd);
		dprintf(fd, "\n");
		current = current->next;
	}
}

void	kdo_print_genome(t_kdo_genome *genome, int fd)
{
	t_list	*current;	

	current = genome->node;
	dprintf(fd, "\n_GENOME_\n(Nc:%u|Lc:%u|f:%f)\n\n",
		genome->node_count, genome->link_count, genome->fitness);
	while (current)
	{
		dprintf(fd, "%s------%s\n", COLOR_YELLOW, COLOR_RESET);
		kdo_print_node(current->data, fd);
		dprintf(fd, "\n");
		current = current->next;
	}
}

void	kdo_print_species(t_kdo_species *species, int fd)
{
	t_list	*current;

	current = species->genome;
	dprintf(fd, "\n<SPACIES>\n(Gc:%u|NP:%u|fm:%f|fa:%f)\n\n\n",
		species->genome_count, species->no_progress_count,
		species->fitness_max, species->fitness_avg);
	while (current)
	{
		kdo_print_genome(current->data, fd);
		dprintf(fd, "\n%s_______________________%s\n\n",
			COLOR_BLUE, COLOR_RESET);
		current = current->next;
	}
}

void	kdo_print_population(t_kdo_population *pop, int fd)
{
	t_uint	i;

	i = 0;
	dprintf(fd, "\n__POPULATION__\n(Gc:%u|Sc:%u|fm:%f|fa:%f)\n\n\n",
		pop->genome_count, pop->species_count,
		pop->fitness_max, pop->fitness_avg);
	while (i < pop->species_count)
	{
		if (pop->species[i].genome_count)
		{
			kdo_print_species(pop->species + i, fd);
			dprintf(fd, "\n%s=====================================%s\n\n\n\n",
				COLOR_MAGENTA, COLOR_RESET);
		}
		i++;
	}
}
