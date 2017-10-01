#include <string.h>

#define MAXTOKENLEN 64
#define MAXTOKENS   128

struct token {
    char type;
    char string[MAXTOKENLEN];
};

enum token_type {
    TYPE,
    QUALIFIER,
    IDENTIFIER
};

/* main token stack */
struct token stack[MAXTOKENS];

/* current token */
struct token this;

/* returns the type of the current token */
enum token_type
classify_string()
{
    char *str = this.string;

    if  (  !strcmp(str, "void")
	|| !strcmp(str, "char")
	|| !strcmp(str, "short")
	|| !strcmp(str, "int")
	|| !strcmp(str, "long")
	|| !strcmp(str, "signed")
	|| !strcmp(str, "unsigned")
	|| !strcmp(str, "float")
	|| !strcmp(str, "double")
	|| !strcmp(str, "struct")
	|| !strcmp(str, "union")
	|| !strcmp(str, "enum")
    ) return TYPE;

    if  (!strcmp(str, "volatile"))
	return QUALIFIER;

    if  (!strcmp(str, "const")) {
	strcpy(str, "readonly");
	return QUALIFIER;
    }

    return IDENTIFIER;
}

int
main(int argc, char **argv)
{
    return 0;
}
