#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

int	ft_strchr(char *str, char c){

	int i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	return(str[i] == c);
}

int		ft_strlen(char *s){
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strjoin(char *s1, char *s2){

	if (!s1){
		s1 = malloc(1);
		s1[0] = 0;
	}
	char *res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	int i = -1;
	while (s1[++i])
		res[i] = s1[i];
	int j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = 0;
	free(s1);
	return (res);
}

char    *read_untill_nl_or_nb(int fd, char *str){

	char *buff = malloc(BUFFER_SIZE + 1);
	int read_bytes = 1;
	while(!ft_strchr(str, '\n') && read_bytes)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		buff[read_bytes] = 0;
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_first_line(char *str)
{

	int i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;

	char *res = (char *)malloc((i + 2));

	int j = -1;
	while (++j < i)
		res[j] = str[j];
	if (str[j] == '\n')
		res[j++] ='\n';
	res[j] = 0;
	return (res);
}



char	*trim_first_line(char *str)
{
	int		i = 0;

	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free(str),NULL);
	char *res = malloc((ft_strlen(str) - i + 1));
	i++;
	int j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	free(str);
	return (res);
}

char *get_next_line(int fd){

	static char*	save;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0) 
		return (NULL);
	save = read_untill_nl_or_nb(fd, save);
	next_line = get_first_line(save);
	save = trim_first_line(save);
	return (next_line);
}

// int	main(){

// 	int fd = open("get_next_line.c", O_RDONLY);

// 	char *line = get_next_line(fd);

// 	while (line){
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }