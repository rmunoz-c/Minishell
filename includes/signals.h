/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogueir <enogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:34:31 by enogueir          #+#    #+#             */
/*   Updated: 2025/06/16 22:34:33 by enogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	handle_parent_signal(int sign);
void	handle_child_signal(int sign);
void	setup_signals(void);
void	setup_child_signals(void);

#endif
