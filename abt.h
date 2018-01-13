#ifndef ABT_H
#define ABT_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum{ASTNODE_ARITH_OP, ASTNODE_LOGIC_OP, ASTNODE_COMPARE, ASTNODE_ASSIGN, ASTNODE_IDENT, ASTNODE_NUM,
    ASTNODE_IF, ASTNODE_IFELSE, ASTNODE_WHILE, ASTNODE_STLIST} ASTNodeType;

// Define all operation types (add, mult, etc) here.
typedef enum{ADD_OP, MULT_OP, SUB_OP, DIV_OP,LE_OP, LT_OP, GE_OP, GT_OP, NE_OP, EQ_OP, OR_OP, AND_OP,
    LOADI_OP, LOADAI_OP, STOREAI_OP, JMP_OP, CBR_OP, LABEL_OP} ASTOp;

typedef struct ASTNode ASTNode;
struct ASTNode{
	ASTNodeType type; 
    ASTOp op; // The actual operation (add, mult, etc)
	int num;  //Need to store the actual value for number nodes
	char *name; //Need to store the actual variable name for ident nodes
	ASTNode* left; // Left child
	ASTNode* right; // Right child
    ASTNode* elseNode;
    char *regNum;
    char* labelNum;
	
	



};
// Symbol Table
struct SymbolTable {
    char *ident;
    char *regNum;
    struct SymbolTable *next;
};
ASTNode* CreateIdentNode(char *name);

ASTNode* CreateStatementListNode(ASTNode *statement, ASTNode *statementList);

ASTNode* CreateMultNode(ASTNode *left, ASTNode *right);

ASTNode* CreateDivNode(ASTNode *left, ASTNode *right);

ASTNode* CreateAddNode(ASTNode *left, ASTNode *right);

ASTNode* CreateSubNode(ASTNode *left, ASTNode *right);

ASTNode* CreateOrNode(ASTNode *left, ASTNode *right);

ASTNode *CreateNumNode(int num);

ASTNode* CreateAndNode(ASTNode *left, ASTNode *right);

ASTNode* CreateIfNode(ASTNode *condition, ASTNode *body, ASTNode *elseNode);

//ASTNode* CreateIfElseNode(ASTNode *condition, ASTNode *stList1, ASTNode *stList2);

ASTNode* CreateWhileNode(ASTNode *condition, ASTNode *loop);

ASTNode* CreateAssignNode(char *name, ASTNode *right);

ASTNode* CreateLENode(ASTNode *left, ASTNode *right);

ASTNode* CreateGENode(ASTNode *left, ASTNode *right);

ASTNode* CreateLTNode(ASTNode *left, ASTNode *right);

ASTNode* CreateGTNode(ASTNode *left, ASTNode *right);

ASTNode* CreateNENode(ASTNode *left, ASTNode *right);

ASTNode* CreateEQNode(ASTNode *left, ASTNode *right);


void AddDeclaration(char *name);

struct  SymbolTable *GetSymbolTable(char *name);

bool isEntryDeclared(char *name);

void PrintTable();



// This is the function that generates ILOC code after the construction of the AST
void GenerateILOC(ASTNode *nod,FILE * out);

void Emit(ASTOp op, char *str1, char *str2, char *dest);
char *GetNextReg();

char *GetLabel();

char* itoa(int value, char *result, int base);

char *append(char *str1, char *str2);



#endif
