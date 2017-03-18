
# include "f_time.h"

# include <time.h>
# include <string.h>

# define OPTIONS_DATE           "DATE"
# define OPTIONS_TIME           "TIME"

# define FORMAT_DATE            "%Y-%m-%d"
# define FORMAT_TIME            "%H:%M:%S"
# define FORMAT_DATE_TIME       FORMAT_DATE " " FORMAT_TIME

enum datetime_type{ LOCAL, UTC };

static int format_datetime(struct fmt_stream * out, const char * options, enum datetime_type type, time_t * timestamp){

    const struct tm * datetime = NULL;
    char buffer[256] = { 0 };
    time_t tmp;

    if(timestamp == NULL){
        (void)time(timestamp = &tmp);
    }

    datetime = ( type == LOCAL ? localtime(timestamp) : gmtime(timestamp) );

    if(options == NULL){
        options = FORMAT_DATE_TIME;
    }else if( strcmp(options, OPTIONS_DATE) == 0 ){
        options = FORMAT_DATE;
    }else if( strcmp(options, OPTIONS_TIME) == 0){
        options = FORMAT_TIME;
    }

    if( strftime(buffer, sizeof(buffer), options, datetime) == 0 ){
        return(FMT_ERROR);
    }

    return( fmt_print_builtin(out, "%s", buffer) );
}

int format_local_datetime(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    (void)id;
    return( format_datetime(out, options, LOCAL, va_arg(*arg, time_t *)) );
}

int format_utc_datetime(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    (void)id;
    return( format_datetime(out, options, UTC, va_arg(*arg, time_t *)) );
}
