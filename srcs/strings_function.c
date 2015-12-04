/*  strings_function.c *****************************************************  */
/*                                                                            */
/*         |- By: plo4ox <plo4ox@4ox.com>                                     */
/*         |_                                                                 */
/*           |- Created: 2015/12/04 10:53:00 by plo4ox                        */
/*           |- Updated: 2015/12/04 10:53:06 by plo4ox                        */
/*                                                                            */
/*  ***************************************************** strings_function.c  */

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <simple_weather.h>

static void	ft_free_str_tab(char ***tab)
{
    int		i;

    i = -1;
    if (*tab != NULL)
    {
	while ((*tab)[++i] != NULL)
	{
	    free((*tab)[i]);
	    (*tab)[i] = NULL;
	}
	free(*tab);
    }
    *tab = NULL;
}

static char	*ft_arr_to_str(char **vars, size_t str_size)
{
    char	*str;
    int		i;
    int		last_str_size;
    
    if (!(str = (char *)malloc(sizeof(char) * str_size + 1)))
	return (NULL);
    last_str_size = 0;
    i = -1;
    while (vars[++i])
    {
	strcpy(str + last_str_size, vars[i]);
	last_str_size += strlen(vars[i]);
    }
    str[str_size] = '\0';
    return (str);
}

char		*ft_join_all_string(int nbArgs, ...)
{
    va_list	ap;
    char	*str;
    char	**vars;
    int		str_size;
    int		i;
    
    str_size = 0;
    va_start(ap, nbArgs);
    if (!(vars = (char **)malloc(sizeof(char *) * (nbArgs + 1))))
	return (NULL);
    vars[nbArgs] = NULL;
    for (i = 0; i < nbArgs; i++)
    {
	vars[i] = strdup(va_arg(ap, char *));
	str_size += strlen(vars[i]);
    }
    va_end(ap);
    str = ft_arr_to_str(vars, str_size);
    ft_free_str_tab(&vars);
    return (str);
}
