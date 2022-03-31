#define MAXTOKEN 100

int dcl(void);
int direct_dcl(void);
int param_dcl(void);

int gettoken(void);
int getch(void);
void ungetch(int c);

char *bsearch(char *s_string, char *s[], unsigned int left, unsigned int right);

void clear_buffer(void);

extern char *types[]; 


extern char *qualifiers[];

enum token__ 
{
 NAME,
 PARENS, 
 BRACKET
} ;

extern enum token__ token___;

extern char name[MAXTOKEN];
extern char datatype[MAXTOKEN];
extern char token[MAXTOKEN];
extern char out[1000];
extern char param_name[MAXTOKEN];

extern unsigned int signal;
extern int tokentype;
extern unsigned int print;
