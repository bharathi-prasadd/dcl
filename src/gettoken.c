#include "dcl.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int tokentype;
char token[MAXTOKEN];


int getch(void);
void ungetch(int c);

int gettoken(void)
{
    char *p = token;
	int c;
	while ( ( c = getch() ) == ' ' || c == '\t' )
		;
	if ( c == '(' )
	{
		if ( (c = getch() ) == ')' )
		{
		    strcpy(token , "()" );
		    return tokentype = PARENS ;
		}
		ungetch(c);
		return tokentype = '(';
	}
	else if ( c == '[' )
	{
		*p++ = c;
		while( ( c = getch()) != ']')
				*p++ = c;
		*p++ = ']';
		*p = '\0'; 
		return tokentype = BRACKET;
	}
	else if ( isalpha(c) )
	{
		*p++ = c;
		while (isalnum(c = getch() ) )
		    *p++ = c;
		ungetch(c);
		*p = '\0';
		return tokentype = NAME;
	}
	return tokentype = c;
}

int bufpos = 0;
int buffer[MAXTOKEN];

int getch(void )
{
    return ( (bufpos == 0) ? getchar() : buffer[--bufpos] );
}

void ungetch( int c)
{
    if (bufpos < MAXTOKEN)
        buffer[bufpos++] = c;
    else
	{
		printf("Error: Stack overflow\n");
    }
}

void clear_buffer(void)
{
    bufpos = 0;
}

