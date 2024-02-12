#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

void	put_string(char *string, int *length)
{
	if (!string)
		string = "(null)";
	while (*string)
		*length += write(1, string++, 1);
}

void	put_digit(long int number, int base, int *length)
{
	char	*hexadecimal;

	hexadecimal = "0123456789abcdef";
	if (number < 0)
	{
		number *= -1;
		*length += write(1, "-", 1);
	}
	if (number / base)
		put_digit((number / base), base, length);
	*length += write(1, &hexadecimal[number % base], 1);
}

int	ft_printf(const char *format, ...)
{
	int		length;
	va_list	pointer;

	length = 0;
	va_start(pointer, format);
	while (*format)
	{
		if ((*format == '%'))
		{
			if (*(format + 1) == 's')
				put_string(va_arg(pointer, char *), &length);
			else if (*(format + 1) == 'd')
				put_digit((long int)va_arg(pointer, int), 10, &length);
			else if (*(format + 1) == 'x')
				put_digit((unsigned int)va_arg(pointer, void *), 16, &length);
			format++;
		}
		else
			length += write(1, format, 1);
		format++;
	}
	return (va_end(pointer), length);
}
