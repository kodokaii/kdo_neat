/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kdo_neat.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaerema <nlaerema@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 10:58:17 by nlaerema          #+#    #+#             */
/*   Updated: 2023/11/13 14:02:00 by nlaerema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KDO_NEAT_H
# define KDO_NEAT_H

# include "libft/libft.h"

# ifndef KDO_POPULATION_COUNT
#  define KDO_POPULATION_COUNT 100
# endif

# ifndef KDO_INPUT_COUNT
#  define KDO_INPUT_COUNT 2
# endif

# ifndef KDO_OUTPUT_COUNT
#  define KDO_OUTPUT_COUNT 2
# endif

struct			s_kdo_link;
struct			s_kdo_node;
typedef float	(*t_kdo_activation_func)(float in);

typedef enum e_node_type
{
	INPUT_NODE,
	HIDDEN_NODE,
	OUTPUT_NODE,
}	t_node_type;

typedef struct s_kdo_link
{
	struct s_kdo_node	*to;
	float				weight;
	t_bool				enable;
}	t_kdo_link;

typedef struct s_kdo_node
{
	t_list				*link;
	t_uint				link_count;
	float				input;
	float				bias;
	t_uint				activation_func;
	t_uint				layer;
	t_node_type			type;
	t_uint				id;
}	t_kdo_node;

typedef struct s_kdo_genome
{
	t_list	*node_list;
	t_bst	*node_sort;
	t_uint	node_count;
	t_uint	link_count;
	t_uint	spacies;
	float	fitness;
	t_uint	id;
}	t_kdo_genome;

typedef struct s_kdo_population
{
	t_buf			*all_link;
	t_buf			*all_node;
	t_kdo_genome	all_genome[KDO_POPULATION_COUNT];
	t_buf			*old_link;
	t_buf			*old_node;
	t_kdo_genome	old_genome[KDO_POPULATION_COUNT];
	t_buf			*best_link;
	t_buf			*best_node;
	t_kdo_genome	best_genome;
	t_uint			generation_count;
	t_uint			spacies_count;
}	t_kdo_population;

float	kdo_identity(float in);
float	kdo_step(float in);
float	kdo_relu(float in);
float	kdo_softsign(float in);
float	kdo_sigmoid(float in);

#endif
