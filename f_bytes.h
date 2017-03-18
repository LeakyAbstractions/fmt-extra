
# ifndef BYTES_FORMATTER
# define BYTES_FORMATTER

# include <fmt.h>

int format_bytes(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

# endif
