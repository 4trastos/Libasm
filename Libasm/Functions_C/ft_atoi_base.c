#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int ft_get_base_value(char *base_str)
{
    int i = 0;
    int j = 0;

    if (!base_str)
        return 0;

    while (base_str[i] != '\0')
    {
        if (base_str[i] == ' ' || base_str[i] == '\t' || base_str[i] == '\n' ||
            base_str[i] == '\r' || base_str[i] == '\f' || base_str[i] == '\v' ||
            base_str[i] == '+' || base_str[i] == '-')
            return 0;

        j = i + 1;
        while (base_str[j] != '\0')
        {
            if (base_str[i] == base_str[j])
                return 0;
            j++;
        }
        i++;
    }
    if (i < 2)
        return 0;
    return i;
}

int ft_get_digit_value(char c, char *base_str, int base_len)
{
    int i = 0;
    char aux = c;

    if (aux >= 'A' && aux <= 'F')
    {
        aux = aux + ('a' - 'A');
    }

    while (i < base_len)
    {
        if (base_str[i] == aux)
            return i;
        i++;
    }
    return -1;
}

int ft_atoi_base(char *str, char *base_str)
{
    int i = 0;
    int sign = 1;
    int result = 0;
    int base_val = 0;
    int digit_val = 0;

    base_val = ft_get_base_value(base_str);
    if (base_val == 0)
        return 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
        {
            sign *= -1;
        }
        i++;
    }

    digit_val = ft_get_digit_value(str[i], base_str, base_val);
    while (digit_val != -1)
    {
        result = result * base_val + digit_val;
        i++;
        digit_val = ft_get_digit_value(str[i], base_str, base_val);
    }
    return (sign * result);
}

int main()
{
    // PRUEBAS BÁSICAS (Base 10)
    printf("--- BASE 10 ---\n");
    printf("String: \"   -1234124abcd345\", Base: \"0123456789\" -> Result: %d (Expected: -1234124)\n", ft_atoi_base("   -1234124abcd345", "0123456789"));
    printf("String: \"+42\", Base: \"0123456789\" -> Result: %d (Expected: 42)\n", ft_atoi_base("+42", "0123456789"));
    printf("String: \" --123\", Base: \"0123456789\" -> Result: %d (Expected: 123)\n", ft_atoi_base(" --123", "0123456789"));
    printf("String: \"-0\", Base: \"0123456789\" -> Result: %d (Expected: 0)\n", ft_atoi_base("-0", "0123456789"));
    printf("String: \"2147483647\", Base: \"0123456789\" -> Result: %d (Expected: 2147483647)\n", ft_atoi_base("2147483647", "0123456789"));
    printf("String: \"-2147483648\", Base: \"0123456789\" -> Result: %d (Expected: -2147483648)\n", ft_atoi_base("-2147483648", "0123456789"));
    printf("String: \"hello\", Base: \"0123456789\" -> Result: %d (Expected: 0)\n", ft_atoi_base("hello", "0123456789"));
    printf("String: \"\", Base: \"0123456789\" -> Result: %d (Expected: 0)\n", ft_atoi_base("", "0123456789"));
    printf("String: \"   \", Base: \"0123456789\" -> Result: %d (Expected: 0)\n", ft_atoi_base("   ", "0123456789"));

    // PRUEBAS DE BASES ARBITRARIAS
    printf("\n--- BASES ARBITRARIAS ---\n");
    printf("String: \"101\", Base: \"01\" (Binary) -> Result: %d (Expected: 5)\n", ft_atoi_base("101", "01"));
    printf("String: \"ff\", Base: \"0123456789abcdef\" (Hex) -> Result: %d (Expected: 255)\n", ft_atoi_base("ff", "0123456789abcdef"));
    printf("String: \"FF\", Base: \"0123456789abcdef\" (Hex - case insensitive) -> Result: %d (Expected: 255)\n", ft_atoi_base("FF", "0123456789abcdef"));
    printf("String: \"-1a\", Base: \"0123456789abcdef\" (Hex) -> Result: %d (Expected: -26)\n", ft_atoi_base("-1a", "0123456789abcdef"));
    printf("String: \"77\", Base: \"01234567\" (Octal) -> Result: %d (Expected: 63)\n", ft_atoi_base("77", "01234567"));
    printf("String: \"hello\", Base: \"olleh\" (Base 5) -> Result: %d (Expected: 110)\n", ft_atoi_base("hello", "olleh")); 
    printf("String: \"--2147483648\", Base: \"01\" -> Result: %d (Expected: 0, as not binary)\n", ft_atoi_base("--2147483648", "01"));


    // PRUEBAS DE BASES INVÁLIDAS
    printf("\n--- BASES INVÁLIDAS ---\n");
    printf("String: \"123\", Base: \"\" (Empty) -> Result: %d (Expected: 0)\n", ft_atoi_base("123", ""));
    printf("String: \"123\", Base: \"0\" (Too short) -> Result: %d (Expected: 0)\n", ft_atoi_base("123", "0"));
    printf("String: \"123\", Base: \"00\" (Duplicate) -> Result: %d (Expected: 0)\n", ft_atoi_base("123", "00"));
    printf("String: \"123\", Base: \"01+\" (Contains '+') -> Result: %d (Expected: 0)\n", ft_atoi_base("123", "01+"));
    printf("String: \"123\", Base: \"01-\" (Contains '-') -> Result: %d (Expected: 0)\n", ft_atoi_base("123", "01-"));
    printf("String: \"123\", Base: \"0 1\" (Contains space) -> Result: %d (Expected: 0)\n", ft_atoi_base("123", "0 1"));
    printf("String: \"123\", Base: NULL -> Result: %d (Expected: 0)\n", ft_atoi_base("123", NULL));
    
    return (0);
}