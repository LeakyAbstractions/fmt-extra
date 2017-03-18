
# ifndef TIME_FORMATTER
# define TIME_FORMATTER

# include <fmt.h>

int format_local_datetime(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

int format_utc_datetime(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

# endif
