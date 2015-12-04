/*  json_function.c ********************************************************  */
/*                                                                            */
/*         |- By: plo4ox <plo4ox@4ox.com>                                     */
/*         |_                                                                 */
/*           |- Created: 2015/12/04 10:52:16 by plo4ox                        */
/*           |- Updated: 2015/12/04 10:52:21 by plo4ox                        */
/*                                                                            */
/*  ******************************************************** json_function.c  */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <simple_weather.h>

static char	*get_json_matched_elem(char *json, int i, int type)
{
    int		size_ret_str;
    int		index_ret_str;
    char	*ret_str;

    size_ret_str = 0;
    while (json[i] != ':' && json[i] != '\0')
	i++;
    if (json[i] == '\0')
	return (NULL);
    i++;
    index_ret_str = i;
    if (type == INTEGER_VALUE)
    {
	while (json[i] != ',' && json[i] != '}' && json[i] != ']')
	{
	    size_ret_str++;
	    i++;
	}
    }
    else
    {
	i++;
	index_ret_str = i;
	while (json[i] != '\"' && json[i] != '\0')
	{
	    size_ret_str++;
	    i++;
	}
    }
    if (!(ret_str = (char *)malloc(sizeof(char) * (size_ret_str + 1))))
	return (NULL);
    memcpy(ret_str, &json[index_ret_str], size_ret_str);
    ret_str[size_ret_str] = '\0';
    return (ret_str);
}

char		*get_json_elem(char *json, char *path, int type)
{
    int		i;
    int		j;
    int		nb_unused_obj;
    int		nb_unused_arr;
    
    i = 0;
    j = 0;
    nb_unused_obj = 0;
    nb_unused_arr = 0;
    while (json[i] != '\0')
    {
	if (path[j] == '\0')
	    return (get_json_matched_elem(json, i, type));
	if (json[j] == '{' && json[i] == path[j] && nb_unused_obj == 0)
	    j++;
	else if (json[j] == '[' && json[i] == path[j] && nb_unused_arr == 0)
	    j++;
	else if (json[j] == '{')
	    nb_unused_obj++;
	else if (json[j] == '[')
	    nb_unused_arr++;
	else if (json[j] == '}')
	    nb_unused_obj--;
	else if (json[j] == ']')
	    nb_unused_arr--;
	else if (path[j] == json[i] && nb_unused_obj == 0 && nb_unused_arr == 0)
	{
	    int tmpi = i;
	    int tmpj = j;

	    while (path[j] == json[i]
		   && path[j] != '\0' && json[i] != '\0') {
		j++;
		i++;
	    }
	    if (json[i] == '\0')
		return (NULL);
	    else if (json[i] != '\"' && path[j] != '{'
		&& path[j] != '[' && path[j] != '\0') {
		i = tmpi;
		j = tmpj;
	    }
	}
	i++;
    }
    return (NULL);
}
