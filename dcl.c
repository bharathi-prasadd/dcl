#include <stdio.h>
#include <string.h>
#include "dcl.h"

char name[MAXTOKEN];
char out[1000];


int dcl (void)
{
    int ns = 0;
	while ( gettoken() == '*' )
		ns++;
    if ( direct_dcl() == -1 )
		return -1;
	while ( ns-- > 0 )
		strcat(out, " Pointer to ");
	return 0;
}

int direct_dcl(void)
{
    if (tokentype == '(' )
    {
		dcl();
	    if (tokentype != ')')
		{
	    	printf("Error expected )\n");
			return -1;
		}
    }
	else if (tokentype == NAME )
	{
		if (signal == 0)
		    strcpy(name,token);
		else if (signal == 1)
		{
		    strcat(out, token);
	        strcat(out, " of type ");
		}
	}
	else
	{
		printf("Error: Expected NAME or (dcl)\n");
		return -1;
	}
	while (( gettoken() ) == PARENS || tokentype == BRACKET || tokentype == '(')
	{
		if (tokentype == PARENS)
				strcat(out , " Function returning");
		else if (tokentype == BRACKET )
		{
		    strcat(out , " Array");
			strcat(out , token);
			strcat(out, " of");
		}
		else if (tokentype == '(')
		    param_dcl();
	}
	return 0;
}
