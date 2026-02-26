1. Millisecond timer wrapper (gettimeofday + usleep warm‑up)
Goal: Get comfortable with time measurement at ms precision.

Implement in time_utils.c:
long    get_timestamp_ms(void); – returns “now” in milliseconds since program start (call gettimeofday, subtract start time).
void    precise_usleep(long ms); – sleeps approximately ms milliseconds using usleep inside a loop (e.g. calling usleep(500) in a while loop until enough time has passed according to gettimeofday).
Write a tiny main that:
Prints start = get_timestamp_ms().
Calls precise_usleep(1000) (1 second).
Prints end and end - start.
Relates to philosophers: all log timestamps and action durations depend on these two functions.