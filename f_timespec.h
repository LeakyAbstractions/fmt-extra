
# ifndef TIMESPEC_FORMATTER
# define TIMESPEC_FORMATTER

# include <fmt.h>

int format_timespec(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

# endif
