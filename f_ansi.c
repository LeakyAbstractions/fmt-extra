
# include "f_ansi.h"

# define ANSI_TEXT_LIGHT                "light-"
# define ANSI_TEXT_DARK                 "dark-"
# define ANSI_TEXT_BLACK                "black"
# define ANSI_TEXT_RED                  "red"
# define ANSI_TEXT_GREEN                "green"
# define ANSI_TEXT_YELLOW               "yellow"
# define ANSI_TEXT_BLUE                 "blue"
# define ANSI_TEXT_MAGENTA              "magenta"
# define ANSI_TEXT_CYAN                 "cyan"
# define ANSI_TEXT_WHITE                "white"
# define ANSI_TEXT_RESET                "reset"
# define ANSI_TEXT_FONT                 "font-"
# define ANSI_TEXT_FONT_OFF             "/font"
# define ANSI_TEXT_BOLD                 "bold"
# define ANSI_TEXT_BOLD_OFF             "/bold"
# define ANSI_TEXT_DIM                  "dim"
# define ANSI_TEXT_DIM_OFF              "/dim"
# define ANSI_TEXT_ITALIC               "italic"
# define ANSI_TEXT_ITALIC_OFF           "/italic"
# define ANSI_TEXT_UNDERLINED           "underlined"
# define ANSI_TEXT_UNDERLINED_OFF       "/underlined"
# define ANSI_TEXT_BLINK                "blink"
# define ANSI_TEXT_BLINK_OFF            "/blink"
# define ANSI_TEXT_BLINK_RAPID          "blink-rapid"
# define ANSI_TEXT_NEGATIVE             "negative"
# define ANSI_TEXT_NEGATIVE_OFF         "/negative"
# define ANSI_TEXT_CONCEALED            "concealed"
# define ANSI_TEXT_CONCEALED_OFF        "/concealed"
# define ANSI_TEXT_CROSSED_OUT          "crossed-out"
# define ANSI_TEXT_CROSSED_OUT_OFF      "/crossed-out"
# define ANSI_TEXT_FRAMED               "framed"
# define ANSI_TEXT_FRAMED_OFF           "/framed"
# define ANSI_TEXT_ENCIRCLED            "encircled"
# define ANSI_TEXT_ENCIRCLED_OFF        "/encircled"
# define ANSI_TEXT_OVERLINED            "overlined"
# define ANSI_TEXT_OVERLINED_OFF        "/overlined"
# define ANSI_ESCAPE(STRING)            "\x1b[" STRING
# define ANSI_SGR(STRING)               ANSI_ESCAPE(STRING "m")
# define ANSI_CHAR_NULL                 '\0'
# define ANSI_CHAR_COLOR_SEPARATOR      '|'
# define ANSI_CHAR_CODE_SEPARATOR       '|'
# define ANSI_CHAR_COLOR_BOTH           '*'
# define ANSI_FG_COLOR                  30
# define ANSI_BG_COLOR                  40
# define PARSE_INTENSITY_VALUE(VALUE)   ( (VALUE) >= ANSI_DARK ? ANSI_DARK : (VALUE) >= ANSI_LIGHT ? ANSI_LIGHT : ANSI_DEFAULT_INTENSITY )
# define PARSE_COLOR_VALUE(VALUE)       ( (VALUE) < ANSI_BLACK || (VALUE) > ANSI_WHITE ? ANSI_NONE : (VALUE) )
# define PARSE_INTENSITY_NAME(NAME)     ( read_token((NAME), ANSI_TEXT_DARK) ? ANSI_DARK : read_token((NAME), ANSI_TEXT_LIGHT) ? ANSI_LIGHT : ANSI_DEFAULT_INTENSITY )
# define PARSE_COLOR_NAME(NAME)         ( \
    read_token((NAME), ANSI_TEXT_BLACK)     ? ANSI_BLACK : \
    read_token((NAME), ANSI_TEXT_RED)       ? ANSI_RED : \
    read_token((NAME), ANSI_TEXT_GREEN)     ? ANSI_GREEN : \
    read_token((NAME), ANSI_TEXT_YELLOW)    ? ANSI_YELLOW : \
    read_token((NAME), ANSI_TEXT_BLUE)      ? ANSI_BLUE : \
    read_token((NAME), ANSI_TEXT_MAGENTA)   ? ANSI_MAGENTA : \
    read_token((NAME), ANSI_TEXT_CYAN)      ? ANSI_CYAN : \
    read_token((NAME), ANSI_TEXT_WHITE)     ? ANSI_WHITE : \
    ANSI_NONE \
)

static int read_token(const char * * text, const char * token){

    const char * tmp = *text;

    for(; *tmp == *token || *token == ANSI_CHAR_NULL; tmp++, token++){
        if(*token != ANSI_CHAR_NULL){ continue; }
        *text = tmp;
        return(1);
    }

    return(0);
}

int parse_ansi_code(const char * * options){

    switch(**options){
        case '/':
            if( read_token(options, ANSI_TEXT_FONT_OFF) ){           return(10); }
            if( read_token(options, ANSI_TEXT_BOLD_OFF) ){           return(21); }
            if( read_token(options, ANSI_TEXT_DIM_OFF) ){            return(22); }
            if( read_token(options, ANSI_TEXT_ITALIC_OFF) ){         return(23); }
            if( read_token(options, ANSI_TEXT_UNDERLINED_OFF) ){     return(24); }
            if( read_token(options, ANSI_TEXT_BLINK_OFF) ){          return(25); }
            if( read_token(options, ANSI_TEXT_NEGATIVE_OFF) ){       return(27); }
            if( read_token(options, ANSI_TEXT_CONCEALED_OFF) ){      return(28); }
            if( read_token(options, ANSI_TEXT_CROSSED_OUT_OFF) ){    return(29); }
            if( read_token(options, ANSI_TEXT_FRAMED_OFF) ){         return(54); }
            if( read_token(options, ANSI_TEXT_ENCIRCLED_OFF) ){      return(54); }
            if( read_token(options, ANSI_TEXT_OVERLINED_OFF) ){      return(55); }
            break;
        case 'b':
            if( read_token(options, ANSI_TEXT_BOLD) ){               return(1);  }
            if( read_token(options, ANSI_TEXT_BLINK_RAPID) ){        return(6);  }
            if( read_token(options, ANSI_TEXT_BLINK) ){              return(5);  }
            break;
        case 'c':
            if( read_token(options, ANSI_TEXT_CONCEALED) ){          return(8);  }
            if( read_token(options, ANSI_TEXT_CROSSED_OUT) ){        return(9);  }
            break;
        case 'd':
            if( read_token(options, ANSI_TEXT_DIM) ){                return(2);  }
            break;
        case 'e':
            if( read_token(options, ANSI_TEXT_ENCIRCLED) ){          return(52); }
            if( read_token(options, ANSI_TEXT_OVERLINED) ){          return(53); }
            break;
        case 'f':
            if( read_token(options, ANSI_TEXT_FONT) ){
                char f = **options;
                if(f >= '1' && f <= '9'){ (*options)++; f -= '0';    return(10 + f); }
            }
            if( read_token(options, ANSI_TEXT_FRAMED) ){             return(51); }
            break;
        case 'i':
            if( read_token(options, ANSI_TEXT_ITALIC) ){             return(3);  }
            break;
        case 'n':
            if( read_token(options, ANSI_TEXT_NEGATIVE) ){           return(7);  }
            break;
        case 'o':
            if( read_token(options, ANSI_TEXT_OVERLINED) ){          return(53); }
            break;
        case 'r':
            if( read_token(options, ANSI_TEXT_RESET) ){              return(0);  }
            break;
        case 'u':
            if( read_token(options, ANSI_TEXT_UNDERLINED) ){         return(4);  }
            break;
        default:
            break;
    }

    return(-1);
}

int format_ansi(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    int total = 0;

    (void)id;

    if(options == NULL){

        total = fmt_print_builtin(out, ANSI_ESCAPE("%s"), va_arg(*arg, const char *));

    }else while(*options){

        int written = 0;
        int code = parse_ansi_code(&options);

        if(*options == ANSI_CHAR_CODE_SEPARATOR){
            options++;
        }else if(*options != ANSI_CHAR_NULL){
            return(FMT_ERROR);
        }

        if(code == -1){ return(FMT_ERROR); }

        written = fmt_print_builtin(out, ANSI_SGR("%d"), code);
        if(written == FMT_ERROR){ return(FMT_ERROR); }

        total += written;
    }

    return(total);
}

int format_ansi_color(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    enum ansi_intensity intensity = ANSI_DEFAULT_INTENSITY;
    enum ansi_color foreground = ANSI_NONE;
    enum ansi_color background = ANSI_NONE;
    const char * intensity_code = NULL;

    (void)id;

    if(options == NULL){

        int value = va_arg(*arg, int);

        intensity  = PARSE_INTENSITY_VALUE(value);
        foreground = PARSE_COLOR_VALUE( (int)(value - intensity) );

    }else if(options[0] == ANSI_CHAR_COLOR_SEPARATOR && options[1] == ANSI_CHAR_NULL){

        int value = va_arg(*arg, int);

        background = PARSE_COLOR_VALUE(value);

    }else if(options[0] == ANSI_CHAR_COLOR_BOTH && options[1] == ANSI_CHAR_NULL){

        int value1 = va_arg(*arg, int);
        int value2 = va_arg(*arg, int);

        intensity  = PARSE_INTENSITY_VALUE(value1);
        foreground = PARSE_COLOR_VALUE( (int)(value1 - intensity) );
        background = PARSE_COLOR_VALUE(value2);

    }else{

        intensity  = PARSE_INTENSITY_NAME(&options);
        foreground = PARSE_COLOR_NAME(&options);

        if(*options == ANSI_CHAR_COLOR_SEPARATOR){
            options++;
            background = PARSE_COLOR_NAME(&options);
            if(*options != ANSI_CHAR_NULL){ background = ANSI_NONE; }
        }else if(*options != ANSI_CHAR_NULL){
            foreground = ANSI_NONE;
        }
    }

    if(foreground == ANSI_NONE && background == ANSI_NONE){ return(0); }

    intensity_code = (intensity == ANSI_LIGHT ? ";1" : intensity == ANSI_DARK ? ";2" : "");

    if(foreground != ANSI_NONE && background != ANSI_NONE){

        return( fmt_print_builtin(out, ANSI_SGR("%d;%d%s"), ANSI_FG_COLOR + foreground, ANSI_BG_COLOR + background, intensity_code) );
    }

    return( fmt_print_builtin(out, ANSI_SGR("%d%s"), background == ANSI_NONE ? ANSI_FG_COLOR + foreground : ANSI_BG_COLOR + background, intensity_code) );
}

int format_ansi_color_reset(struct fmt_stream * out, const char * id, const char * options, va_list * arg){

    (void)id;
    (void)options;
    (void)arg;

    return(  fmt_print_builtin( out, ANSI_SGR("39;49;22") )  );
}
