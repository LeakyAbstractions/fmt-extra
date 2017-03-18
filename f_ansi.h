
# ifndef ANSI_FORMATTER
# define ANSI_FORMATTER

# include <fmt.h>

enum ansi_color{

    ANSI_NONE = -1,
    ANSI_BLACK,
    ANSI_RED,
    ANSI_GREEN,
    ANSI_YELLOW,
    ANSI_BLUE,
    ANSI_MAGENTA,
    ANSI_CYAN,
    ANSI_WHITE
};

enum ansi_intensity{

    ANSI_DEFAULT_INTENSITY = 0,
    ANSI_LIGHT = 100,
    ANSI_DARK = 200
};

int format_ansi(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

int format_ansi_color(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

int format_ansi_color_reset(struct fmt_stream * out, const char * id, const char * options, va_list * arg);

# endif
