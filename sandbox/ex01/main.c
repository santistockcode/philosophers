# include "ex01.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

long long get_timestamp_ms(t_data *data);
void precise_usleep(long long ms);
long long ms_from_tv(struct timeval start_time);

void	messages(char *str, long long ts)
{
	printf("%s %lld\n", str, ts);
}

int init_data(t_data **data)
{
    struct timeval tv;
    int ret_gtod;
    long long now;

    ret_gtod = gettimeofday(&tv, NULL);
    if (ret_gtod < 0)
        return (-1);
    now = ms_from_tv(tv);
    *data = (t_data *)malloc(sizeof(t_data *));
    if (!(*data))
        return (printf("malloc error"), -1);
    (*data)->start_time = now;
    return (0);
}



int main(void)
{
    t_data *data;
    long long start;
    long long end;

    if (init_data(&data) != 0)
        return (1);
    start = get_timestamp_ms(data);
    messages("start", start);
    precise_usleep(1000);
    end = get_timestamp_ms(data);
    messages("end", end);
    messages("end - start", end - start);
    free(data);
    return (0);
}
