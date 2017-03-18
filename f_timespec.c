
# include "f_timespec.h"

# include <time.h>
# include <string.h>

# ifdef HAS_TIMESPEC_H
#   include <timespec.h>
# endif

# define DATE_TIME(_)           _("DATE_TIME",          "%Y-%m-%dT%H:%M:%S,%%06ld%%s", 0)
# define SIMPLE_DATE_TIME(_)    _("SIMPLE_DATE_TIME",   "%Y-%m-%d %H:%M:%S",           0)
# define DATE(_)                _("DATE",               "%Y-%m-%d",                    0)
# define TIME(_)                _("TIME",               "%H:%M:%S,%%06ld%%s",          0)
# define HOURS_MINUTES(_)       _("HOURS_MINUTES",      "%H:%M",                       0)
# define SIMPLE_TIME(_)         _("SIMPLE_TIME",        "%H:%M:%S",                    0)
# define YEAR(_)                _("YEAR",               "%Y",                          0)
# define YEAR_MONTH(_)          _("YEAR_MONTH",         "%Y-%m",                       0)
# define WEEK(_)                _("WEEK",               "%Y-W%W",                      0)
# define WEEK_DAY(_)            _("WEEK_DAY",           "%Y-W%W-%d",                   0)
# define TIMESTAMP(_)           _("TIMESTAMP",          "%ld",                         1)
# define TIMESTAMP_NSEC(_)      _("TIMESTAMP_NSEC",     "%ld%06d",                     1)
# define TIMESTAMP_MSEC(_)      _("TIMESTAMP_MSEC",     "%ld%03d",                     1000)

# define OPTION(A, B, T)        A
# define FORMAT(A, B, T)        B
# define TSTAMP(A, B, T)        T

# define IS_LOCAL(X)            ( X[0] == 'L' && X[1] == 'O' && X[2] == 'C' && X[3] == 'A' && X[4] == 'L' )
# define IS_OPTION(A, B)        ( strcmp(A, B(OPTION)) == 0 )

# define CHECK_DEFAULT_OPTION(DATE_TIME) \
    if(options == NULL || *options == '\0' || IS_OPTION(options, DATE_TIME) ){ \
        options = DATE_TIME(FORMAT); \
    }
# define CHECK_OTHER_OPTION(PREDEFINED_FORMAT) \
    else if( IS_OPTION(options, PREDEFINED_FORMAT) ){ \
        options = PREDEFINED_FORMAT(FORMAT); \
        if(PREDEFINED_FORMAT(TSTAMP)){ \
            print_ts = PREDEFINED_FORMAT(TSTAMP); \
        } \
    }

int format_timespec(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    struct timespec * timespec = va_arg(*arg, void *);
    int print_ts = 0;
    int is_local = 0;
    const struct tm * datetime = NULL;
    time_t * timestamp;
    char buffer[256] = { 0 };
    struct timespec tmp;

    (void)id;

    if(options != NULL && IS_LOCAL(options) ){
        options += ( options[5] == ':' ? 6 : 5 );
        is_local = 1;
    }

    CHECK_DEFAULT_OPTION(DATE_TIME)
    CHECK_OTHER_OPTION(SIMPLE_DATE_TIME)
    CHECK_OTHER_OPTION(DATE)
    CHECK_OTHER_OPTION(TIME)
    CHECK_OTHER_OPTION(HOURS_MINUTES)
    CHECK_OTHER_OPTION(SIMPLE_TIME)
    CHECK_OTHER_OPTION(YEAR)
    CHECK_OTHER_OPTION(YEAR_MONTH)
    CHECK_OTHER_OPTION(WEEK)
    CHECK_OTHER_OPTION(WEEK_DAY)
    CHECK_OTHER_OPTION(TIMESTAMP)
    CHECK_OTHER_OPTION(TIMESTAMP_NSEC)
    CHECK_OTHER_OPTION(TIMESTAMP_MSEC)

    if(timespec == NULL){
        (void)timespec_get(timespec = &tmp, TIME_UTC);
    }

    if(print_ts){
        return( fmt_print_builtin(out, options, (long)timespec->tv_sec, (int)(timespec->tv_nsec / print_ts)) );
    }

    timestamp = &timespec->tv_sec;
    datetime = ( is_local ? localtime(timestamp) : gmtime(timestamp) );

    if( strftime(buffer, sizeof(buffer), options, datetime) == 0 ){
        return(FMT_ERROR);
    }

    return( fmt_print_builtin(out, buffer, timespec->tv_nsec, is_local ? "" : "Z") );
}
