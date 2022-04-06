#include "get_next_line.h"

//#define DEBUG 1

size_t		my_strlen(const char *s)
{
	size_t		i;

	if (s == NULL)
	{
#ifdef DEBUG
	printf("my_strlen return NULL\n");
#endif
		return (0);
	}
	i = 0;
	while (s[i] != '\0')
		i++;
#ifdef DEBUG
	printf("my_strlen return %zu\n", i);
#endif
	return (i);
}

char		*my_strchr(const char *s, char c)
{
	size_t		count;
	size_t		i;

	if (s == NULL)
		return (NULL);
	count = my_strlen(s);
	i = 0;
	while (i <= count)
	{
		if (s[i] == c)
		{
#ifdef DEBUG
			printf("my_strchr return %s\n", &s[i]);
#endif
			return ((char *)&s[i]);
		}
		i++;
	}
#ifdef DEBUG
	printf("my_strchr return NULL\n");
#endif
	return (NULL);
}

char	*my_strjoin(const char *s1, const char *s2, char c)
{
	char	*ret;
	int		s1_len;
	int		s2_len;
	int		i;

	if(s1 == NULL || s2 == NULL)
	{
#ifdef DEBUG
		printf("my_strljoin return NULL\n");
#endif
		return (NULL);
	}
	s1_len = my_strlen(s1);
	s2_len = my_strchr(s2, c) - s2;
	if (!(ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
	{
#ifdef DEBUG
		printf("my_strjoin malloc failed  return NULL\n");
#endif
		return (NULL);
	}
	i = 0;
	while (i < s1_len)
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		ret[s1_len + i] = s2[i];
		i++;
	}
	ret[s1_len + i] = '\0';
#ifdef DEBUG
	printf("my_strjoin return %s\n", ret);
#endif
	free((char *)s1);
	return (ret);
}

char	*my_strdup(const char *s, char c)
{
	char		*ret;
	size_t		i;

	if (s == NULL || my_strchr(s, c) == NULL)
	{
#ifdef DEBUG
		printf("my_strdup return NULL\n");
#endif
		return (NULL);
	}
	if (!(ret = (char *)malloc(sizeof(char) * (my_strchr(s, c) - s + 1))))
	{
#ifdef DEBUG
		printf("my_strdup malloc failed  return NULL\n");
#endif
		return (NULL);
	}
	i = 0;
	while (s[i] != c)
	{
		ret[i] = s[i];
		i++;
	}
	ret[i] = '\0';
#ifdef DEBUG
	printf("my_strdup return %s\n", ret);
#endif
	return (ret);
}
