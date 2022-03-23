#include <stdio.h>
#include <string.h>
#include "dcl.h"
#include <ctype.h>

char name[MAXTOKEN];
char out[1000];
char params[MAXTOKEN];
char param_name[MAXTOKEN];

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


int param_dcl(void)
{
    if (gettoken() != NAME )		//if function call doesnt have args 
	{
        printf("Expected ) or initialiser list\n");
		return -1;
	}
	if ( bsearch(token, qualifiers, 0 ,1 ) != NULL ) //if valid qualifier (const/volatile)
	{
		strcpy(params, token);
		strcat(params, " ");
		gettoken();
		if ( tokentype == NAME && bsearch(token, types, 0, 2) != NULL ) //dtype
		    strcat(params, token);
		else 
		{
		    printf(" Error: %s not a valid datatype\n", token);		//qualifier not followed by datatype name
		}
	}
	else if ( bsearch(token, types, 0 , 2 ) != NULL ) //datatype (no qualifier)
	{
		strcpy(params, token);	
    }
	else 
	{
		printf("Token %s is neither valid datatype nor valid qualifier\n", token);
		return -1;
	}
	signal = 1;
    if (print == 1)
		 strcat(out, "Function expecting argument(s) ");
	dcl();
	strcat(out, params);
	if (tokentype == ',')
	{
		strcat(out, ",");
		print = 0;
		param_dcl();
		print = 1;
	}
    if (print == 1)
		strcat(out, " returning");
	return 0;
}
