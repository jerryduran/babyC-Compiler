%{
	#include <stdio.h>
	#include "abt.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here 
%initial-action 
{

}
%token GT ">"
%token LT "<"
%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM

//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Goal
%type <node> Statement
%type <node> Assignment
%type <node> Expr
%type <node> Term
%type <node> Factor
%type <node> DeclarationList
%type <node> Declaration
%type <node> StatementList
%type <node> If
%type <node> While
%type <node> Condition
%type <node> Compare
//%type <node> LHS
// Add the rest of the types for the grammar's symbols


%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:

Goal: "main" '(' ')' '{' DeclarationList StatementList '}'    {gASTRoot=$6;} // Store the AST root node in gASTRoot
;

DeclarationList:  | Declaration DeclarationList // Note that a DeclarationList may be empty
;

Declaration: "int" IDENT ';' {AddDeclaration($2); printf("Processing declaration of %s\n", $2);}
;
Factor: IDENT 		{$$ = CreateIdentNode($1); printf("Creating IDENT node for %s\n", $1);}
	| NUM 		{$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
| '('Expr')'	{$$ = $2; printf("Creating Expression node in parentheses \n");}
;

StatementList: {$$ = NULL} 
               | Statement StatementList	{$$ = CreateStatementListNode($1,$2);printf("Adding a Statement to a Statement list \n");};
Statement: Assignment {$$=$1;}
| If {$$=$1;}
| While {$$=$1;}
;
Term: Factor {$$ = $1;}
| Term '*' Factor {$$ = CreateMultNode($1, $3);printf("Creating Multiplication node \n");}
| Term '/' Factor {$$ = CreateDivNode($1, $3); printf("Creating Division node \n");}
;
Expr: Term {$$=$1;}
| Expr '+' Term {$$ = CreateAddNode($1, $3);printf("Creating Addition node \n");}
| Expr '-' Term {$$= CreateSubNode($1, $3);printf("Creating Subtract node \n");}
;
Assignment: IDENT '=' Expr ';' {$$=CreateAssignNode($1, $3); printf("Creating Assignment node \n");}
//LHS: IDENT { $$ = CreateIdentNode($1); printf("Creating left-hand IDENT node for %s\n",$1);}
;
If: "if" '(' Condition ')' '{' StatementList '}' {$$= CreateIfNode($3, $6, NULL);printf("Creating if Statement node \n");}
| "if" '(' Condition ')' '{' StatementList '}' "else" '{' StatementList '}' {$$= CreateIfNode($3, $6, $10);printf("Creating if-else Statement node \n");}
;
While: "while" '(' Condition ')' '{' StatementList '}' {$$=CreateWhileNode($3, $6);printf("Creating while loop node \n");}
;
Condition: Compare {$$=$1;}
| Compare "||" Compare {$$=CreateOrNode($1, $3);printf("Creating Or node \n");}
| Compare "&&" Compare {$$=CreateAndNode($1, $3);printf("Creating And node \n");}
;
Compare: Expr LE Expr {$$=CreateLENode($1,$3);printf("Creating Compare node \n");}
|Expr LT Expr {$$=CreateLTNode($1,$3);printf("Creating Compare node \n");}
|Expr GE Expr {$$=CreateGENode($1,$3);printf("Creating Compare node \n");}
|Expr GT Expr {$$=CreateGTNode($1,$3);printf("Creating Compare node \n");}
|Expr EQ Expr {$$=CreateEQNode($1,$3);printf("Creating Compare node \n");}
|Expr NE Expr {$$=CreateNENode($1,$3);printf("Creating Compare node \n");}
;
%%
