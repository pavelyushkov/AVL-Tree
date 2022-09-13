#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readline.h"

char *readline ( const char * s ){
        printf ( "%s" , s );
        char buf [81] = {0};
        char * res = NULL ;
        int n = 0; int len = 0;
        do {
                n = scanf ( "%80[^\n]" , buf );
                if ( n < 0){
                        if (! res ){
                                return NULL ;
                        }
                } else if ( n > 0){
                        int chunk_len = strlen ( buf );
                        int str_len = len + chunk_len ;
                        res = realloc ( res , str_len + 1);
                        memcpy ( res + len , buf , chunk_len );
                        len = str_len ;
                        res [ len ] = '\0';
                } else {
                        scanf ( "%*c" );
                }
        } while ( n > 0);
        if ( len > 0)
                res [ len ] = '\0';
        else res = calloc (1 , sizeof ( char ));
return res ;
}
