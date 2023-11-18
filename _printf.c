#include "main.h"

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buff_ind: Index at which to add the next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Custom printf function
 * @format: Format string.
 * Return: Number of characters printed (excluding null byte).
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
		return (-1);

	va_list list;
	int printed_chars = 0;
	int buff_ind = 0;
	char buffer[BUFF_SIZE];

	va_start(list, format);

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);

			/*
			 * Process format specifier
			 */

			int flags = get_flags(format, &i);
			int width = get_width(format, &i, list);
			int precision = get_precision(format, &i, list);
			int size = get_size(format, &i);

			i++; /*Move to the next character after '%'*/

			/*
			 * Handle the formatted printing
			 */
			int printed = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
			{
				va_end(list);
				return (-1);
			}

			printed_chars += printed;
		}
	}

	/*
	 * Print any remaining characters in the buffer
	 */
	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buff_ind: Index at which to add the next character, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, buffer, *buff_ind);

	*buff_ind = 0;
}

