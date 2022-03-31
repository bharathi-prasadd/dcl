#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "dcl.h" 

unsigned int signal = 0;
unsigned int print = 1;
char qual[MAXTOKEN];
char datatype[MAXTOKEN];

char *types[] =
{
    "char",
    "int",
	"void"
};

char *qualifiers[] = 
{
    "const",
	"volatile"
};

int main()
{
    printf("Enter declaration:\n");
    while ( gettoken() != EOF )
	{
		if ( tokentype == NAME )
		{
		    if ( bsearch(token, qualifiers, 0, 1) != NULL ) 
		    {
				strcpy(qual, token);
				if ( gettoken() == NAME )
				{
				    if ( bsearch(token, types, 0, 2) != NULL )
						strcpy(datatype, token);
					else 
					{
						printf("Error: Invalid type name %s" , token);
						return -1;
					}
				}
			}
			else if ( bsearch(token, types, 0 ,2 ) != NULL )
			{
				qual[0] = 0;
				strcpy(datatype, token);
			}
			else 
			{
				printf("%s not a valid datatype or qualifier\n", token);
				return -1;
			}
		}
		else 
		{
		    printf("Error: Expected datatype\n");
			return -1;
		}
		if ( dcl() == -1 )
		{
		    printf("Syntax error");
			return -1;
		}
		if (tokentype != '\n' && tokentype != ';')
		{
		    printf("Syntax error\n");
			return -1;
		}
		if (tokentype == ';')									//get the trailing newline in the input buffer
		    getchar();
		printf("%s : %s %s %s\n", name, out, qual, datatype);
		clear_buffer();
		printf("\n\nEnter declaration:\n");
    }
	return 0;
}




