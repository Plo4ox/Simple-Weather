/*  main.c *****************************************************************  */
/*                                                                            */
/*         |- By: plo4ox <plo4ox@4ox.com>                                     */
/*         |_                                                                 */
/*           |- Created: 2015/12/04 10:52:27 by plo4ox                        */
/*           |- Updated: 2015/12/04 10:52:32 by plo4ox                        */
/*                                                                            */
/*  ***************************************************************** main.c  */

#include    <stdlib.h>
#include    <stdio.h>
#include    <curl/curl.h>
#include    <string.h>
#include    <simple_weather.h>

void	    print_weather(char *res_json)
{
    char    *temp;
    char    *weather;
    char    *description;
    char    *town;

    town = get_json_elem(res_json, "{city{name", STRING_VALUE);
    if (!town)
    {
	fprintf(stderr, "I can't get the weather data, sorry :)\n");
	return ;
    }
    temp = get_json_elem(res_json, "{list[{main{temp", INTEGER_VALUE);
    weather = get_json_elem(res_json, "{list[{weather{main", STRING_VALUE);
    description = get_json_elem(res_json, "{list[{weather{description", STRING_VALUE);
    printf("%s // [%s°C] - %s { %s }\n", town, temp, weather, description);
    if (description)
	free(description);
    if (weather)
	free(weather);
    if (temp)
	free(temp);
    if (town)
	free(town);
}

int	    main(int ac, char **av)
{
    char    *res_json;
    char    *weather_url;
    int	    res;
    
    weather_url = get_weather_url(ac, av);
    if ((res_json = (char *)malloc(sizeof(char) * BUFSZ)) && weather_url)
    {
	res = curl_weather_url(weather_url, &res_json);
	if (res == CURLE_OK && strlen(res_json) > 0)
	{
	    print_weather(res_json);
	    free(res_json);
	}
	else
	    fprintf(stderr, "I can't get the weather data, sorry :)\n");
	free(weather_url);
    }
    else
	fprintf(stderr, "I can't get the weather data, sorry :)\n");
    return (0);
}
