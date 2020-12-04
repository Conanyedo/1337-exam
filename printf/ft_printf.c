/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 22:50:24 by ybouddou          #+#    #+#             */
/*   Updated: 2020/12/02 19:49:42 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//*************** additional functions ***********************

static int		ft_intlen(int n, int sign)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (((len == 0) ? 1 : len) + sign);
}

static char		*ft_convert(int nlen, int sign, int n)
{
	char	*a;

	if (!(a = (char *)malloc((sizeof(char) * nlen + 1))))
		return (NULL);
	a[nlen] = '\0';
	while (--nlen >= sign)
	{
		a[nlen] = n % 10 + 48;
		n = n / 10;
	}
	if (nlen >= 0)
		a[nlen] = '-';
	return (a);
}

void			ft_itoa(int n)
{
	int		nlen;
	char	*a;
	int		sign;

	nlen = 0;
	sign = 0;
	if (n == -2147483648)
	{
		a = ft_strdup("-2147483648");
		ft_putstr(a);
		free(a);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		sign = 1;
	}
	nlen = ft_intlen(n, sign);
	a = ft_convert(nlen, sign, n);
	ft_putstr(a);
	free(a);
}

static char		*ft_ispace(const char *s)
{
	while (((*s == ' ') || (*s == '\t') ||
				(*s == '\n') || (*s == '\v') ||
				(*s == '\f') || (*s == '\r')))
		s++;
	return ((char *)s);
}

int				ft_atoi(const char *s)
{
	int			sign;
	long int	n;
	long int	prev;

	n = 0;
	sign = 1;
	s = ft_ispace(s);
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		prev = n;
		n = n * 10 + sign * (*s - '0');
		if (sign == 1 && prev > n)
			return (-1);
		else if (sign == -1 && prev < n)
			return (0);
		s++;
	}
	return (n);
}

static char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	j;
	char			*sub;

	if (!s)
		return (NULL);
	if (!*s || start > ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	j = 0;
	if (!(sub = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (s[i])
	{
		if (i == start)
		{
			while (s[i] && j < len)
				sub[j++] = s[i++];
			sub[j] = '\0';
			return (sub);
		}
		i++;
	}
	return (NULL);
}

void			substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;

	sub = ft_substr(s, start, len);
	ft_putstr(sub);
	free(sub);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

char	*ft_strdup(const char *s)
{
	unsigned int	i;
	unsigned int	j;
	char			*copy;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	if (!(copy = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (j < i)
	{
		copy[j] = s[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

size_t	ft_strlen(const char *s)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

//****************** S specifier *************************************

int		ft_len(char *s, int len, t_flag fl)
{
	int		n;

	if (fl.w > len)
	{
		n = fl.w - len;
		while (n--)
			ft_putchar(' ');
		ft_putstr(s);
		return (fl.w);
	}
	ft_putstr(s);
	if (fl.w < 0)
	{
		fl.w *= -1;
		n = (fl.w < len) ? 0 : (fl.w - len);
		while (n--)
			ft_putchar(' ');
		if (fl.w > len)
			return (fl.w);
	}
	return (len);
}

static int	ft_width_s(char *s, t_flag fl)
{
	int		n;
	int		len;

	len = ft_strlen(s);
	if (fl.w < 0)
	{
		fl.w *= -1;
		substr(s, 0, fl.p);
		n = (fl.p > len) ? (fl.w - len) : (fl.w - fl.p);
		if (fl.w < fl.p)
			n = 0;
		while (n--)
			ft_putchar(' ');
		if (len > fl.p && len > fl.w && fl.p > 0 && fl.w < fl.p)
			return (fl.p);
		if (fl.p >= len && fl.p > fl.w && len > fl.w)
			return (len);
		return (fl.w);
	}
	if (fl.w > fl.p)
	{
		n = fl.w - fl.p;
		while (n--)
			ft_putchar(' ');
		substr(s, 0, fl.p);
		return (fl.w);
	}
	else
		substr(s, 0, fl.p);
	return (fl.p);
}

static int	ft_width_flag(char *s, t_flag fl)
{
	int		n;
	int		len;

	len = ft_strlen(s);
	if (fl.w < 0)
	{
		fl.w *= -1;
		substr(s, 0, fl.p);
		n = (fl.p > len) ? (fl.w - len) : (fl.w - fl.p);
		if (fl.w < fl.p)
			n = 0;
		while (n--)
			ft_putchar(' ');
		if (len > fl.p && len > fl.w && fl.p > 0 && fl.w < fl.p)
			return (fl.p);
		if (fl.p >= len && fl.p > fl.w && len > fl.w)
			return (len);
		return (fl.w);
	}
	if (fl.p >= len && fl.w > len)
	{
		n = fl.w - len;
		while (n--)
			ft_putchar(' ');
		ft_putstr(s);
		return (fl.w);
	}
	else if (len > fl.p && fl.w > len)
	{
		n = fl.w - fl.p;
		while (n--)
			ft_putchar(' ');
		substr(s, 0, fl.p);
		return (fl.w);
	}
	ft_putstr(s);
	return (len);
}

int			s_printf(char *s, t_flag fl)
{
	int		count;
	int		len;

	count = 0;
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if ((len >= fl.w && fl.p < 0) || (fl.p < 0 && fl.w > len))
		return (ft_len(s, len, fl));
	if ((len >= fl.w) && (len >= fl.p))
		count += ft_width_s(s, fl);
	else
		count += ft_width_flag(s, fl);
	return (count);
}

int		s_checker(const char **str, va_list arg, t_flag flags)
{
	char			*s;
	unsigned int	i;
	int				count;

	count = 0;
	s = va_arg(arg, char *);
	count += s_printf(s, flags);
	(*str)++;
	return (count);
}

//****************** D specifier *************************************

static int	digit(int i)
{
	int		n;

	n = 0;
	if (i == 0)
		return (0);
	if (i == -2147483648)
		return (10);
	if (i < 0)
		i *= -1;
	while (i >= 10)
	{
		i = i / 10;
		n++;
	}
	return (n + 1);
}

int			ft_digit(int i, int d, t_flag fl)
{
	int		n;
	int		minus;

	minus = (i < 0) ? 1 : 0;
	d = (i == 0) ? 1 : d;
	ft_itoa(i);
	if (fl.w < 0)
	{
		fl.w *= -1;
		n = fl.w - d - minus;
		n = (n < 0) ? 0 : n;
		while (n--)
			ft_putchar(' ');
		if (d >= fl.w && d >= fl.p)
			return (d + minus);
		return (fl.w);
	}
	return (d + minus);
}

int			ft_prec(int i, int d, int minus, t_flag fl)
{
	int		n;

	n = fl.p - d;
	while (n--)
		ft_putchar('0');
	if (i == -2147483648)
		ft_putstr("2147483648");
	else if (i != 0)
		ft_itoa(i);
	if (fl.w < 0)
	{
		fl.w *= -1;
		n = fl.w - fl.p - minus;
		n = (n < 0) ? 0 : n;
		if (fl.w < fl.p)
			n = 0;
		while (n--)
			ft_putchar(' ');
		if (fl.w <= fl.p)
			return (fl.p + minus);
		return (fl.w);
	}
	return (fl.p + minus);
}

static int	ft_precision_d(int i, int d, t_flag fl)
{
	int		minus;

	minus = 0;
	if ((d == 0 && d > fl.p) || d > fl.p)
	{
		if (i != 0 || fl.p < 0)
			ft_itoa(i);
		return (fl.p);
	}
	if (i < 0)
	{
		ft_putchar('-');
		i *= -1;
		minus = 1;
	}
	if ((d == 0 && fl.p >= d) || fl.p >= d)
		return (ft_prec(i, d, minus, fl));
	if (i != 0)
		ft_itoa(i);
	return (fl.p);
}

static int	ft_width_d(int i, int d, t_flag fl)
{
	int		n;
	int		minus;

	minus = 0;
	if (i < 0)
		minus = 1;
	if ((d == 0 && fl.p >= d) || fl.p >= d)
	{
		n = fl.w - fl.p - minus;
		while (n--)
			ft_putchar(' ');
		ft_precision_d(i, d, fl);
	}
	else if ((d == 0 && d > fl.p) || d > fl.p)
	{
		n = fl.w - d - minus;
		if (fl.p < 0 && d == 0)
			n = fl.w - 1;
		while (n--)
			ft_putchar(' ');
		ft_precision_d(i, d, fl);
	}
	return (fl.w);
}

int			d_printf(int i, t_flag fl)
{
	int		d;
	int		count;

	count = 0;
	d = digit(i);
	if (fl.p >= fl.w && fl.p >= d)
		count += ft_precision_d(i, d, fl);
	else if (fl.w > d && fl.w > fl.p)
		count += ft_width_d(i, d, fl);
	else if (d >= fl.w && d >= fl.p)
		count = ft_digit(i, d, fl);
	return (count);
}

int		d_checker(const char **str, va_list arg, t_flag flags)
{
	unsigned int	i;
	int				count;

	count = 0;
	i = va_arg(arg, int);
	count += d_printf(i, flags);
	(*str)++;
	return (count);
}

//****************** X specifier *************************************

static void	*ft_rev(char *hex)
{
	int		i;
	int		len;
	char	tmp;

	i = 0;
	len = ft_strlen(hex) - 1;
	while (i < len)
	{
		tmp = hex[i];
		hex[i++] = hex[len];
		hex[len--] = tmp;
	}
	return (hex);
}

char		*converter(unsigned int n, char x)
{
	int		i;
	int		temp;
	char	*hex;

	i = 0;
	hex = (char *)malloc(sizeof(char) * 20);
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			hex[i++] = 48 + temp;
		else
			hex[i++] = (x - 33) + temp;
		n /= 16;
	}
	hex[i] = '\0';
	hex = ft_rev(hex);
	return (hex);
}

int		ft_len_x(char *s, int len, t_flag fl)
{
	int		n;

	if (fl.p < 0 || *s != '0')
	{
		len = (*s == '0') ? 1 : len;
		ft_putstr(s);
	}
	if (fl.w < 0)
	{
		fl.w *= -1;
		n = (fl.w < len) ? 0 : (fl.w - len);
		while (n--)
			ft_putchar(' ');
		if (fl.w > len)
			return (fl.w);
	}
	return (len);
}

int		neg_width_x(char *s, int len, t_flag fl)
{
	int		n;

	len = 0;
	if (fl.w < 0)
	{
		fl.w *= -1;
		n = (fl.w > fl.p) ? (fl.w - fl.p) : 0;
		if (*s != '0')
			ft_putstr(s);
		while (n--)
			ft_putchar(' ');
		if (fl.p > fl.w)
			return (fl.p);
		return (fl.w);
	}
	return (fl.p);
}

static int	ft_precision_x(char *s, int len, t_flag fl)
{
	int		n;

	len = ((*s == '0') ? 0 : ft_strlen(s));
	if (len > fl.p)
	{
		ft_putstr(s);
		return (fl.p);
	}
	if (fl.p > len)
	{
		n = fl.p - len;
		while (n--)
			ft_putchar('0');
		if (fl.w < 0)
			return (neg_width_x(s, len, fl));
	}
	if (*s != '0')
		ft_putstr(s);
	return (fl.p);
}

static int	ft_width_x(char *s, int len, t_flag fl)
{
	int		n;

	n = 0;
	if (fl.p >= len)
	{
		n = fl.w - fl.p;
		while (n--)
			ft_putchar(' ');
		ft_precision_x(s, len, fl);
	}
	else if (len >= fl.p)
	{
		n = fl.w - len;
		while (n--)
			ft_putchar(' ');
		ft_precision_x(s, len, fl);
	}
	return (fl.w);
}

int			x_printf(char *s, t_flag fl)
{
	int		len;
	int		count;

	count = 0;
	len = ((*s == '0') ? 0 : ft_strlen(s));
	if (len >= fl.w && len >= fl.p)
		return (ft_len_x(s, len, fl));
	if (fl.p > fl.w && fl.p > len)
		count += ft_precision_x(s, len, fl);
	else if (fl.w > len)
	{
		len = (*s == '0' && fl.p == 0) ? 0 : ft_strlen(s);
		count += ft_width_x(s, len, fl);
	}
	return (count);
}

int		x_checker(const char **str, va_list arg, t_flag flags)
{
	unsigned long int	i;
	char				*s;
	int					count;

	count = 0;
	i = va_arg(arg, unsigned int);
	if (i == 0)
		s = ft_strdup("0");
	else
		s = converter(i, **str);
	count += x_printf(s, flags);
	free(s);
	(*str)++;
	return (count);
}

//******************** printf ********************

int		print(const char **s)
{
	int		count;

	count = 0;
	while (**s && **s != '%')
	{
		ft_putchar(**s);
		(*s)++;
		count++;
	}
	return (count);
}

static void	ft_width(const char **s, t_flag *fl, int arg)
{
	fl->w = 0;
	if (**s >= '0' && **s <= '9')
	{
		fl->w = ft_atoi(*s);
		while (**s >= '0' && **s <= '9')
			(*s)++;
	}
}

static void	ft_precision(const char **s, t_flag *fl, int arg)
{
	fl->p = -1;
	if (**s == '.')
	{
		(*s)++;
		if (**s >= '0' && **s <= '9')
		{
			fl->p = ft_atoi(*s);
			while (**s >= '0' && **s <= '9')
				(*s)++;
		}
		else
			fl->p = 0;
	}
}

int			ft_printf(const char *str, ...)
{
	va_list			arg;
	int				count;
	t_flag			flags;

	count = 0;
	va_start(arg, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			ft_width(&str, &flags, 1);
			ft_precision(&str, &flags, 1);
			if (*str == 's')
				count += s_checker(&str, arg, flags);
			else if (*str == 'd')
				count += d_checker(&str, arg, flags);
			else if (*str == 'x')
				count += x_checker(&str, arg, flags);
		}
		count += print(&str);
	}
	va_end(arg);
	return (count);
}

int		main()
{
	int	r;
	int	r1;
	
	r1 = ft_printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	printf(" | %d\n", r1);
	r = printf("s10w4p ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s` ~%10.4s`\n", "", "toto", "0123456789", "tjehurthteutuiehteute", NULL);
	printf(" | %d\n", r);
}