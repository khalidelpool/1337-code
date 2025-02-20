/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kel-mous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 17:52:37 by kel-mous          #+#    #+#             */
/*   Updated: 2025/02/16 18:19:32 by kel-mous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(void)
{
	if (id == 0)
		((dup2(pip[at(i, PREV, READ)], 0), close(pip[at(i, PREV, READ)])),
			(dup2(pip[at(i, CURR, WRITE)], 1),
				close(pip[at(i, CURR, WRITE)])), execute(av[i], envp));
	(cleanup(i, pip, av[i + 2]), i++);
}
