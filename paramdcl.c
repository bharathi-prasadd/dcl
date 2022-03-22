#include <stdio.h>
#include "dcl.h"
#include <string.h>
#include <ctype.h>

char params[MAXTOKEN];
char param_name[MAXTOKEN];


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
