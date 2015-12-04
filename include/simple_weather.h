/*  simple_weather.h *******************************************************  */
/*                                                                            */
/*         |- By: plo4ox <plo4ox@4ox.com>                                     */
/*         |_                                                                 */
/*           |- Created: 2015/12/04 10:51:39 by plo4ox                        */
/*           |- Updated: 2015/12/04 10:51:45 by plo4ox                        */
/*                                                                            */
/*  ******************************************************* simple_weather.h  */

#ifndef SIMPLE_WEATHER_H
# define SIMPLE_WEATHER_H

# define OPENWEATHERAPI_USER_KEY "" // Your API Key here :: http://openweathermap.org/api
# define OPENWEATHERAPI_LINK	"http://api.openweathermap.org/data/2.5"

# define DEFAULT_TOWN		"Paris"
# define INTEGER_VALUE		0
# define STRING_VALUE		1
# define BUFSZ			512
# define CURL_TIMEOUT		20L

char		*get_json_elem(char *json, char *path, int type);
char		*get_weather_url(int ac, char **av);
int		curl_weather_url(char *weather_url, char **res_json);
char		*ft_join_all_string(int nbArgs, ...);

#endif
