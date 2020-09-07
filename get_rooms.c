/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljerk <ljerk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 19:34:06 by ljerk             #+#    #+#             */
/*   Updated: 2020/09/04 20:40:07 by ljerk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/lemin.h"

//записать комнату со строки
int get_room(char* line, t_room *room)
{
	int i;

	i = 0;
	while(line[i] != '\0')
	{
		if(line[i] == ' ')
		{
			room->name = ft_strnew(i);
			ft_strncpy(room->name, line, i);
			line += i + 1;
			room->x = ft_atoi(line);
			line += numlen(room->x);
			room->y = ft_atoi(line);
			return 1;
		}
		i++;
	}
	return 0;
}


//добавить комнаты к существующим
int add_room(t_lemin *lem, char* line)
{
	t_room* tmp;
	int i = -1;

	tmp = (t_room*)malloc(sizeof(t_room) * ++(lem->num_rooms));
	while(++i != lem->num_rooms - 1)
		tmp[i] = lem->rooms[i];
	get_room(line, &tmp[i]);
	/* 
	если раскомментить то вылетает ошибка, не понимаю почему(ljerk)
	 */
	free(lem->rooms);
	free(line);//раскоментил, ошибок нет не щнаю почему (icanker)
	lem->rooms = tmp;
	return 1;
}

//добавочная функция для проверки комнат
void exit_get_room(char* line)
{
	if (!check_room(line))
	{
		ft_putstr("get_room");
		exit(1);
	}
}

/*парсинг комнат:
					обработка всех ошибок
					считывание количества муравьев
					считывание старта/конца
					считывание комнаты
					игнорирование комментариев и невалидных строк
*/
char *get_rooms(t_lemin *lem, char* line)
{
	while(get_next_line(lem->fd, &line) && check_line(line))
	{
		if (!ft_strcmp(line, "##start"))
		{
			get_next_line(lem->fd, &line);
			exit_get_room(line);
			lem->id_start_room = lem->num_rooms;
			add_room(lem, line);

		}
		else if (!ft_strcmp(line, "##end"))
		{
			get_next_line(lem->fd, &line);
			exit_get_room(line);
			lem->id_end_room = lem->num_rooms;
			add_room(lem, line);
		}
		else if (line[0] == '#') {
			free(line);
		}
		else
			add_room(lem, line);
	}
	return line;
}
