/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grui-ant <grui-ant@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:25:35 by grui-ant          #+#    #+#             */
/*   Updated: 2026/06/18 14:25:44 by grui-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE 
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
int		gl_strlen(char *s);
char	*gnl_strchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
void	shift(char *read_buffer);

#endif
