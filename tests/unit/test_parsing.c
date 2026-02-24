# include "../../include/philo.h"
#include "minunit.h"
#include <stdlib.h>
#include <string.h>

/* ── Tests ─────────────────────────────────────────────── */

int	parse_args(int argc, char const **argv, t_data *data);


static int test_valid_args_minimum(void)
{
    printf("test_valid_args_minimum\n");
    t_data data;
    const char *argv[] = {"./philo", "5", "800", "200", "200"};
    mu_assert_intcmp("Should succeed with 5 args", parse_args(5, argv, &data), 0);
    return (0);
}

static int test_valid_args_with_optional(void)
{
    printf("test_valid_args_with_optional\n");
    t_data data;
    const char *argv[] = {"./philo", "5", "800", "200", "200", "7"};
    mu_assert_intcmp("Should succeed with 6 args", parse_args(6, argv, &data), 0);
    return (0);
}

static int test_invalid_negative_numbers(void)
{
    printf("test_invalid_negative_numbers\n");
    t_data data;
    const char *argv[] = {"./philo", "-5", "800", "200", "200"};
    mu_assert_intcmp("Should fail with negative philosopher count", parse_args(5, argv, &data), 1);
    
    const char *argv2[] = {"./philo", "5", "-800", "200", "200"};
    mu_assert_intcmp("Should fail with negative time_to_die", parse_args(5, argv2, &data), 1);
    return (0);
}

static int test_invalid_non_numeric(void)
{
    printf("test_invalid_non_numeric\n");
    t_data data;
    const char *argv[] = {"./philo", "abc", "800", "200", "200"};
    mu_assert_intcmp("Should fail with non-numeric arg", parse_args(5, argv, &data), 1);
    
    const char *argv2[] = {"./philo", "5", "800ms", "200", "200"};
    mu_assert_intcmp("Should fail with mixed alphanumeric", parse_args(5, argv2, &data), 1);
    return (0);
}

static int test_invalid_zero_values(void)
{
    printf("test_invalid_zero_values\n");
    t_data data;
    const char *argv[] = {"./philo", "0", "800", "200", "200"};
    mu_assert_intcmp("Should fail with zero philosophers", parse_args(5, argv, &data), 1);
    return (0);
}

static int test_null_data_pointer(void)
{
    printf("test_null_data_pointer\n");
    const char *argv[] = {"./philo", "5", "800", "200", "200"};
    mu_assert_intcmp("Should handle NULL data pointer", parse_args(5, argv, NULL), 1);
    return (0);
}

int	main(void)
{
    mu_run_test(test_valid_args_minimum);
    mu_run_test(test_valid_args_with_optional);
    mu_run_test(test_invalid_negative_numbers);
    mu_run_test(test_invalid_non_numeric);
    mu_run_test(test_invalid_zero_values);
    mu_run_test(test_null_data_pointer);
    printf("\n");
    mu_summary();
}