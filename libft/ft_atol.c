#include "libft.h"

long	ft_atol(const char *str)
{
	long int	ret;
	int	sign;
	int	i;

	i = 0;
	ret = 0;
	sign = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		if (sign > 0 && ret > (LONG_MAX - (str[i] - '0')) / 10)
		{
			errno = ERANGE;
			return LONG_MAX;
		}
		else if (sign < 0 && -ret < (LONG_MIN + (str[i] - '0')) / 10)
		{
			printf("here");
			errno = ERANGE;
			return LONG_MIN;
		}
		ret = (ret * 10) + (str[i] - '0');
		i++;
	}
	return (ret * sign);
}
