#include <stdio.h>
#include <string.h>


#define COLOR_RED     "\x1b[38;5;176m"
#define COLOR_GREEN   "\x1b[38;5;78m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_YELLOW  "\x1b[38;5;178m"
#define COLOR_CYAN "\x1b[36m"

void	print_input_str(char *str)
{
	printf("Original str: ");
	printf(COLOR_YELLOW"%s\n"COLOR_RESET, str);
}

void	print_str_definition(char *def, char *str)
{
	printf("%s: ", def);
	printf(COLOR_YELLOW"%s\n"COLOR_RESET, str);
}

void	print_output_str(char *str)
{
	printf("Output str: ");
	printf(COLOR_CYAN"%s\n"COLOR_RESET, str);
}

void	print_nbr_values(char *def, void *value)
{
	printf("%s: ", def);
	printf(COLOR_RED"%ld\n"COLOR_RESET, (size_t)value);
}

void print_pass_str(char *original, char *copy)
{
    printf(COLOR_YELLOW"expected: %s "COLOR_RESET, original);
    printf(COLOR_GREEN"result: %s | PASS\n"COLOR_RESET, copy);
}

void print_fail_str(char *original, char *copy)
{
    printf(COLOR_YELLOW"expected: %s "COLOR_RESET, original);
    printf(COLOR_RED"result: %s | FAIL\n"COLOR_RESET, copy);
}

void    print_str_comparison(char *original, char *copy)
{
    if (original == NULL && copy == NULL)
    {
        printf(COLOR_CYAN"expected: (null) result: (null)\n"COLOR_RESET);
        return;
    }
    
    if (original == NULL)
    {
        print_fail_str("(null)", copy);
        return;
    }

    if (copy == NULL)
    {
        print_fail_str(original, "(null)");
        return;
    }
    if (strcmp(original, copy) == 0) {
        print_pass_str(original, copy);
        return;
    }
    print_fail_str(original, copy);
}

void print_pass_int(int original, int copy)
{
    printf(COLOR_YELLOW"expected: %d "COLOR_RESET, original);
    printf(COLOR_GREEN"result: %d | PASS\n"COLOR_RESET, copy);
}
void print_fail_int(int original, int copy)
{
    printf(COLOR_YELLOW"expected: %d "COLOR_RESET, original);
    printf(COLOR_RED"result: %d | FAIL\n"COLOR_RESET, copy);
}


void    print_int_comparison(int original, int copy)
{
    if (original == copy)
        print_pass_int(original, copy);
    else
        print_fail_int(original,copy);
}

void print_test_title(char *title) {
    printf("\n");
    int idx = 0;
    while (title[idx] != 0)
        idx++;

    while (idx > -4) 
    {
        idx--;
        printf("-");
    }
    printf("\n| ");
    idx = 0;
    while (title[idx] != 0)
    {
        printf("%c", title[idx]);
        idx++;
    }
    printf(" |\n");
    while (idx > -4)
    {
        idx--;
        printf("-");
    }
    printf("\n");
}


