#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
int stack_index = -1;

#define push(A)	stack[++stack_index] = (A)
#define pop	stack[stack_index--]
#define current	stack[stack_index]

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

/* reads the next token into `this` and classify it */
void
get_token()
{
    char *str = this.string;

    /* discard whitespace */
    do {
	*str = getchar();
    } while (*str == ' ' || *str == '\t');

    if (isalnum(*str)) {
	/* read the rest */
	while (isalnum(*++str = getchar())) ;
	ungetc(*str, stdin);
	*str = '\0';

	this.type = classify_string();
	return;
    }

    /* for other not alnum the token type is itself */
    this.type = *str;
    *++str = '\0';

    return;
}

void
read_to_first_identifier()
{
    do {
	get_token();
	push(this);
    } while (this.type != IDENTIFIER);

    printf("%s is ", this.string);
    pop;

    get_token();
}

/* --- Parsing Routines ---
 *
 * Work on the current token and always
 * read the next one at the end.
 */

void
deal_with_function_args()
{
    /* read past closing `)` */
    while (this.type != ')') get_token();
    get_token();

    printf("function returning ");
}

void
deal_with_arrays()
{
    printf("array ");
    get_token(); /* read size or `]` */

    /* print size if given */
    if (isdigit(*this.string)) {
	printf("with size %s ", this.string);
	get_token(); /* read `]` */
    }

    printf("of ");
    get_token();
}

/* prints pointers on stack, if any */
void
deal_with_pointers()
{
    while (current.type == '*') {
	printf("pointer to ");
	pop;
    }
}

void
deal_with_declarator()
{
    if (this.type == '[')
	deal_with_arrays();

    if (this.type == '(')
	deal_with_function_args();

    /* while there is content on the stack */
    while (stack_index >= 0) {
	deal_with_pointers();
	if (current.type == '(') {
	    /* simple parenthesis */
	    pop;
	    get_token(); /* should be the matching `)` */
	    deal_with_declarator();
	} else {
	    printf("%s ", pop.string);
	}
    }
}

int
main(int argc, char **argv)
{
    read_to_first_identifier();
    deal_with_declarator();

    printf("\n");

    return 0;
}
