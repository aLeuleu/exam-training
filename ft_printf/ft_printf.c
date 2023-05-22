#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int	ft_putchar(char c ){
	return (write(1,&c,1));
}

int	ft_putstr(char *str){

	int i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	ft_strchr(char *str, char c){

	if (!str)
		return 0;
	int i = 0;
	while (str[i] && str[i] != c)
		i++;
	return(str[i] == c);
}

int	ft_putnbr(long int n){

	int res = 0;

	if (n < 0 ){
		n = -n;
		res += ft_putchar('-');
	}

	if (n > 9)
		res += ft_putnbr(n/10);
	return (res + ft_putchar('0' + n%10));
}

int		ft_putnbr_hex(unsigned int n){

	int res = 0;

	if (n > 15)
		res += ft_putnbr_hex(n /16);

	int digit = n%16;
	if (digit < 10)
		return (res + ft_putchar('0' + digit));
	else
		return (res + ft_putchar('a' + digit - 10));
}

int		switch_printf(char format, va_list *args){

	if (format == 's')
		return (ft_putstr(va_arg(*args, char*)));
	if (format == 'd')
		return (ft_putnbr(va_arg(*args, long int)));
	if (format == 'x')
		return (ft_putnbr_hex(va_arg(*args, unsigned int)));
	return (0);
}

int		ft_printf(char *str, ...){
	va_list	args;
	int		total_len =0;
	int		tmp_len;
	int		i = 0;

	va_start(args, str);

	if(!str)
		return (-1);

	while(str[i])
	{
		tmp_len = 0;
		if (str[i] == '%' && str[i + 1] && ft_strchr("sdx", str[i + 1]))
			tmp_len += switch_printf(str[i++ + 1], &args);
		else
			tmp_len += ft_putchar(str[i]);
		total_len += tmp_len;
		i++;
	}

	va_end(args);

	return(total_len);
}

// int	main(){
// 	int res[7];
// 	res[0] = ft_printf("Vanilla text.\n");
// 	res[1] = ft_printf("42 : %d.\n", 42);
// 	res[2] = ft_printf("INT_MIN : %d.\n", INT_MIN);
// 	res[3] = ft_printf("INT_MAX : %d.\n", INT_MAX);
// 	res[4] = ft_printf("INT_MAX : %x.\n", INT_MAX);
// 	res[5] = ft_printf("INT_MIN : %x.\n", INT_MIN);
// 	res[6] = ft_printf("Hello my name is %s and i love %d\n", "aurelien", 42);

// 	for (int i = 0; i < 7; i++)
// 	{
// 		printf("%d\n", res[i]);
// 	}
// }