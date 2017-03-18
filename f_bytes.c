
# include "f_bytes.h"

# define KB ( (long)1024 )
# define MB ( KB * KB )
# define GB ( MB * KB )

int format_bytes(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    int bytes = va_arg(*arg, int);
    float number = bytes;

    (void)id;
    (void)options;

    if(bytes < KB){
        return( fmt_print_builtin(out, "%d bytes", bytes) );
    }

    if(bytes < MB){
        return( fmt_print_builtin(out, "%.2f KB", number / KB) );
    }

    if(bytes < GB){
        return( fmt_print_builtin(out, "%.2f MB", number / MB) );
    }

    return( fmt_print_builtin(out, "%.2f GB", number / GB) );
}
