#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "./printers.c"


void print_pass_int(int original, int copy);
void print_fail_int(int original, int copy);
void print_test_title(char *title);
void    print_str_comparison(char *original, char *copy);
void    print_int_comparison(int original, int copy);

typedef int (*CharTypeChecker)(int);
typedef size_t (*CheckStringContent)(const char*);


typedef enum {
    MEMSET_FUNC,
    BZERO_FUNC,
    MEMCPY_FUNC,
    MEMMOVE_FUNC,
    STRLCPY_FUNC,
    STRLCAT_FUNC,
    TOUPPER_FUNC,
    TOLOWER_FUNC,
    STRCHR_FUNC,
    STRRCHR_FUNC,
    STRNCMP_FUNC,
    MEMCHR_FUNC,
    MEMCMP_FUNC,
    STRNSTR_FUNC,
    ATOI_FUNC,
    STRDUP_FUNC,
} StringManipulationFunction;


void string_manipulation_test(char *title, char **tests_a, char **tests_b, StringManipulationFunction func_type) {
    print_test_title(title);

    for (int i = 0; tests_a[i] != NULL; i++) {
        printf("Inputs: '%s' | '%s' - ", tests_a[i], tests_b[i]);


        char *a = malloc(ft_strlen(tests_a[i]) + 1);
        char *b = malloc(ft_strlen(tests_b[i]) + 1);
        strcpy(a, tests_a[i]);
        strcpy(b, tests_b[i]);

        size_t len_a = ft_strlen(a);
        size_t len_b = ft_strlen(b);

        char *tmp_a = malloc(len_a + 1);
        char *tmp_b = malloc(len_b + 1);
        char *dest_tmp = malloc(len_a+ 1);
        char *src_tmp = malloc(len_b + 1);
        strcpy(tmp_a, tests_a[i]);
        strcpy(tmp_b, tests_b[i]);
        // Ensure that destination doesn't overlap with source
        strcpy(dest_tmp, tmp_a);
        strcpy(src_tmp, tmp_b);


        int return_a;
        int return_b;
        char *return_char_a;
        char *return_char_b;

        switch (func_type) {
            case MEMSET_FUNC:
                return_char_a = (char*)memset(a, '*', sizeof(char) * 7);
                return_char_b = (char*)ft_memset(b, '*', sizeof(char) * 7);
                print_str_comparison(return_char_a, return_char_b);
                break;
            case BZERO_FUNC:
                bzero(a, strlen(a));
                ft_bzero(b, strlen(b));
                print_str_comparison(a, b);
                break;
            case MEMCPY_FUNC:
                memcpy(dest_tmp, src_tmp, len_a + 1);
                ft_memcpy(a, b, len_a + 1);
                print_str_comparison(dest_tmp, a);
                break;
            case MEMMOVE_FUNC:
                memmove(dest_tmp, src_tmp, 13 - i);
                ft_memmove(a, b, 13 - i);
                print_str_comparison(dest_tmp, a);
                break;
            case STRLCPY_FUNC:
                return_a = strlcpy(dest_tmp, src_tmp, 13 - i);
                return_b = ft_strlcpy(a, b, 13 - i);
                // printf("return a: %d, return b: %d\n", return_a, return_b);
                print_str_comparison(dest_tmp, a);
                break;
            case STRLCAT_FUNC:
                strlcat(dest_tmp, src_tmp, strlen(dest_tmp) + 5);
                ft_strlcat(a, b, strlen(a) + 5);
                print_str_comparison(dest_tmp, a);
                break;
            case TOUPPER_FUNC:
                return_a = toupper(a[0]); 
                return_b = ft_toupper(b[0]);
                print_str_comparison((char*)&return_a, (char*)&return_b);
                break;
            case TOLOWER_FUNC:
                return_a = tolower(a[0]); 
                return_b = ft_tolower(b[0]);
                print_str_comparison((char*)&return_a, (char*)&return_b);
                break;
            case STRCHR_FUNC:
                return_char_a = strchr(a, 's'); 
                return_char_b = ft_strchr(b, 's');
                print_str_comparison(return_char_a, return_char_b);
                break;
            case STRRCHR_FUNC:
                return_char_a = strrchr(a, 's'); 
                return_char_b = ft_strrchr(b, 's');
                print_str_comparison(return_char_a, return_char_b);
                break;
            case STRNCMP_FUNC:
                return_a = strncmp(a, b, strlen(a)); 
                return_b = ft_strncmp(a, b, strlen(a));
                print_int_comparison(return_a, return_b);
                break;
            case MEMCHR_FUNC:
                return_char_a = (char*)memchr(a, 'i', 25); 
                return_char_b = (char*)ft_memchr(b, 'i', 25);
                print_str_comparison(return_char_a, return_char_b);
                break;
            case MEMCMP_FUNC:
                return_a = memcmp(a, b, strlen(a)); 
                return_b = ft_memcmp(a, b, strlen(a)); 
                print_int_comparison(return_a, return_b);
                break;
            case STRNSTR_FUNC:
                return_char_a = strnstr(dest_tmp, src_tmp, 50);
                return_char_b = ft_strnstr(a, b, 50);
                print_str_comparison(return_char_a, return_char_b);
                break;
            case ATOI_FUNC:
                return_a = atoi(a);
                return_b = ft_atoi(b);
                print_int_comparison(return_a, return_b);
                break;
            case STRDUP_FUNC:
                return_char_a = strdup(a);
                return_char_b = ft_strdup(b);
                print_str_comparison(return_char_a, return_char_b);
                free(return_char_a);
                free(return_char_b);
                break;
            default:
                // Handle unsupported function type
                break;
        }

        free(a);
        free(b);
        free(tmp_a);
        free(tmp_b);
        free(dest_tmp);
        free(src_tmp);
    }
}


void test_string_content(CheckStringContent original_function, CheckStringContent my_function, char* title)
{
    print_test_title(title);

    char *tests[] = {
        "Hello World",
        "Numb3rs && Ch4rs",
        "Str\twith\ttabs"
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        int original= original_function(tests[i]);
        int copy = my_function(tests[i]);

        printf("Input: '%s' - ", tests[i]);
        if (original == copy)
            print_pass_int(original, copy);
        else
            print_fail_int(original,copy);
    }
}

void test_different_char_types(CharTypeChecker char_type_checker, CharTypeChecker my_checker, char *title)
{
    print_test_title(title);
    const char testing_chars[] = {
        '\x80',
        '\0',
        '+',
        '&',
        '0',
        ' ',
        'a',
        'B'
    };

    for (unsigned long i = 0; i < sizeof(testing_chars); ++i)
    {
        int original = char_type_checker(testing_chars[i]);
        int copy = my_checker(testing_chars[i]);
        
        printf("Inputs: '%c' - ", testing_chars[i]);
        if (original == copy)
            print_pass_int(original, copy);
        else
            print_fail_int(original,copy);
    }
}


void test_calloc(char *title)
{
    print_test_title(title);

    int idx = 0; 
    int n_tests = 5;

    while (idx <= n_tests)
    {
        int i = 0;
        int max_size = idx * idx;

        printf("Inputs: '%d' | '%lu' - ", max_size + 1, sizeof(char));

        char *test_a = (char *)calloc(max_size + 1, sizeof(char)); 
        char *test_b = (char *)ft_calloc(max_size + 1, sizeof(char));
        print_str_comparison(test_a, test_b);

        printf("Allocated outputs with content: ");
        // Initialize content for test_a and test_b
        for (i = 0; i < max_size; ++i)
        {
            test_a[i] = 'A' + i;
            test_b[i] = 'A' + i;
        }

        // Null terminate the strings this is why the + 1 when calling calloc
        test_a[max_size] = '\0';
        test_b[max_size] = '\0';

        print_str_comparison(test_a, test_b);
        printf("********************\n");

        idx++;
        free(test_a);
        free(test_b);
    }
}

void	test_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	
	out = ft_substr(s, start, len);
	print_input_str(s);
	/* printf("The output from %u to %ld is...\n", start, len); */
	print_nbr_values("The start index is", start);
	print_nbr_values("Number of elements to copy", len);
	print_nbr_values("The original len is", ft_strlen(s));
	print_output_str(out);
	print_nbr_values("The output str len is", ft_strlen(out));
	printf("\n\n");
}

void	test_strjoin(char const *s1, char const *s2)
{
	char	*out;
	
	out = ft_strjoin(s1, s2);
	print_input_str(s1);
	print_input_str(s2);
	print_output_str(out);
	print_nbr_values("The s1 len is", ft_strlen(s1));
	print_nbr_values("The s2 len is", ft_strlen(s2));
	print_nbr_values("The output str len is", ft_strlen(out));
	printf("\n\n");
}

void	test_strim(char const *s1, char const *set)
{
	char	*out;
	
	out = ft_strtrim(s1, set);
	print_input_str(s1);
	print_str_definition("set to trim", set);
	print_output_str(out);
	printf("\n\n");
}


#define MAX_STRING_SIZE 256

int main()
{

    char *tests_a[] = {
        "Hello how are you doing?\0",
        "I'm using multipl€ ic0ns & numbers\0",
        "12232-,,,.fshaj\10k 43_-fd\0",
        "tabla\ttablao\ttablita\0",
        "main short\0",
        NULL
    };
   // For same content 
    char *tests_b[] = {
        "Hello how are you doing?\0",
        "I'm using multipl€ ic0ns & numbers\0",
        "12232-,,,.fshaj\10k 43_-fd\0",
        "tabla\ttablao\ttablita\0",
        "main short\0",
        NULL
    };
    // For different content
    char *tests_c[] = {
        "Replacing the first\0",
        "Continu€ R€placing!!1!1\0",
        "These\10 are more normal chars\0",
        "i like\ttabs\tabs\0",
        "the c options is much larger\0",
        NULL
    };

    // For comparison - similarity check
    char *tests_d[] = {
        "Hello how are you doing?\0",
        "I'm using multipl€ ic0ns or numbers\0",
        "13232-,,,.fshaj\10k 43_-fd\0",
        "tabla\ttablao\ttab\0",
        "main short\0",
        NULL
    };

    // Search for content within... 
    char *haystack[] = {
        "Hello how are you doing?",
        "",
        "12232-,,,.fshaj\10k 43_-fd",
        "tabla\ttablao\ttablita",
        "main short",
        NULL
    };

    char *needle[] = {
        "are you",
        "multipl€",
        "nothing",
        "tablao",
        "",
        NULL
    };

    char *atoi_test[] = {
        "42",
        "  -42",
        "     42",
        "   +42,33",
        "    +-42",
        "-2147483648",
        "2147483647",
        NULL
    };

    // Char type functions
    test_different_char_types(&isdigit, &ft_isdigit, "Testing isdigit()");   
    test_different_char_types(&isalpha, &ft_isalpha, "Testing isalpha()");   
    test_different_char_types(&isalnum, &ft_isalnum, "Testing isalnum()");   
    test_different_char_types(&isascii, &ft_isascii, "Testing isascii()");   
    test_different_char_types(&isprint, &ft_isprint, "Testing isprint()");   


    // Test length
    test_string_content(&strlen, &ft_strlen, "Testing strlen()");

    // Manipulate content of strings
    string_manipulation_test("Testing memset()", tests_a, tests_b, MEMSET_FUNC);
    string_manipulation_test("Testing bzero()", tests_a, tests_b, BZERO_FUNC);
    string_manipulation_test("Testing memcpy()", tests_a, tests_c, MEMCPY_FUNC);
    string_manipulation_test("Testing memmove()", tests_a, tests_c, MEMMOVE_FUNC);
    string_manipulation_test("Testing strlcpy()", tests_a, tests_c, STRLCPY_FUNC);
    string_manipulation_test("Testing strlcat()", tests_a, tests_c, STRLCAT_FUNC);
    string_manipulation_test("Testing toupper()", tests_a, tests_b, TOUPPER_FUNC);
    string_manipulation_test("Testing tolower()", tests_a, tests_b, TOLOWER_FUNC);
    string_manipulation_test("Testing strchr()", tests_a, tests_b, STRCHR_FUNC);
    string_manipulation_test("Testing strrchr()", tests_a, tests_b, STRRCHR_FUNC);
    string_manipulation_test("Testing strncmp()", tests_a, tests_d, STRNCMP_FUNC);
    string_manipulation_test("Testing memchr()", tests_a, tests_b, MEMCHR_FUNC);
    string_manipulation_test("Testing memcmp()", tests_a, tests_d, MEMCMP_FUNC);
    string_manipulation_test("Testing strnstr()", haystack, needle, STRNSTR_FUNC);
    string_manipulation_test("Testing atoi()", atoi_test, atoi_test, ATOI_FUNC);
    string_manipulation_test("Testing strdup()", tests_a, tests_b, STRDUP_FUNC);

    
    // Speficic memory allocations
    test_calloc("Testing calloc()");

	// Non-system functions
	print_test_title("Testing substr()");
	test_substr("Hello World but so long", 5, 99999);
	test_substr("Hello World but so long", 5, 10);
	test_substr("Hello World but so long", 5, 1);
	test_substr("Hello World but so long", 5, 2);
	test_substr("Hello World but so long", 0, 12);
	test_substr("Hello World but so long", 6, 0);

	print_test_title("Testing strjoin()");
	test_strjoin("Hello", " World");
	test_strjoin("Chao", " World");
	test_strjoin("Manu ", " Chao");
	test_strjoin("", "Prev is empty");
	test_strjoin("Next is empty", "");
	test_strjoin("", "");

	print_test_title("Testing strtrim()");
	test_strim("      Yay!!    ", " ");
	test_strim("__alcachofa__", "_");
	test_strim("-+-cc+/c/+-*cosillas+++/--c/+c", "+-/c");
    return 0;
}
