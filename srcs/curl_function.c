/*  curl_function.c ********************************************************  */
/*                                                                            */
/*         |- By: plo4ox <plo4ox@4ox.com>                                     */
/*         |_                                                                 */
/*           |- Created: 2015/12/04 10:52:00 by plo4ox                        */
/*           |- Updated: 2015/12/04 10:52:08 by plo4ox                        */
/*                                                                            */
/*  ******************************************************** curl_function.c  */

#include <string.h>
#include <curl/curl.h>
#include <simple_weather.h>

static size_t	write_callback(void *ptr, size_t size, size_t nmemb, void *userdata)
{
    char	**res;
    
    res = (char **) userdata;
    *res = strndup(ptr, (size_t) (size * nmemb));
    return ((size * nmemb));
}

char		*get_weather_url(int ac, char **av)
{
    char	*res;
    char	*town;

    if (ac > 1)
	town = av[1];
    else
	town = DEFAULT_TOWN;
    
    res = ft_join_all_string(8, OPENWEATHERAPI_LINK
			     , "/forecast?q=", town
			     , "&units=", "metric"
			     , "&appid=", OPENWEATHERAPI_USER_KEY
			     , "&cnt=1");
    return (res);
}

int		curl_weather_url(char *weather_url, char **res_json)
{
    CURL	*curl;
    CURLcode	res;

    curl = curl_easy_init();
    if (curl)
    {
	curl_easy_setopt(curl, CURLOPT_URL, weather_url);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, CURL_TIMEOUT);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, res_json);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	return (res);
    }
    else
	return (CURLE_FAILED_INIT);
}
