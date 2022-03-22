//#include "dcl.h"
#include <string.h>
char *bsearch(char *s_string, char *s[], unsigned int left, unsigned int right)
{
    if ( left >= right ) 
         return NULL;
    if (strcmp(s_string, *(s + (left + right)/2) ) == 0)
         return *(s + (left + right)/2);
    else if ( strcmp(s_string, *(s + (left + right)/2) ) <= 0)
        bsearch(s_string, s, left, ( (left + right)/2 - 1  ));
    else if ( strcmp(s_string, *(s + (left + right)/2) ) >= 0)
        bsearch(s_string, s,( (left + right)/2 + 1 ), right);
}
