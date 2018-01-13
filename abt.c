#include "abt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct  SymbolTable *head = NULL;
int regNum = 0;
int labelNum =0;
FILE * PrintFile =NULL; 

void CheckEntry(char *name) {
    if(isEntryDeclared(name)) {
    // Do nothing
} else {
    printf("Error: IDENT %s has not been declared.\n", name);
    exit(1);
}
}
    
ASTNode *CreateNumNode(int num)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_NUM;
    node->num = num;
    return node;
}
ASTNode *CreateIdentNode(char* name)
{
   CheckEntry(name);
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type =  ASTNODE_IDENT;
    node->name = name;
    return node;

}
ASTNode *CreateAddNode(ASTNode *left, ASTNode *right)
{
     ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = ADD_OP;
    node->left = left;
    node->right = right;
    return node;
    
}
ASTNode* CreateSubNode(ASTNode *left, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = SUB_OP;
    node->left = left;
    node->right = right;
    return node;
    
}
ASTNode* CreateMultNode(ASTNode *left, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = MULT_OP;
    node->left = left;
    node->right = right;
    return node;
    
}
ASTNode* CreateDivNode(ASTNode *left, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ARITH_OP;
    node->op = DIV_OP;
    node->left = left;
    node->right = right;
    return node;
    
}
ASTNode* CreateAssignNode(char *name, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_ASSIGN;
    node->name = name;
    node->left = CreateIdentNode(name);;
    node->right = right;
    return node;
}
ASTNode* CreateStatementListNode(ASTNode *statement, ASTNode *statementList)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_STLIST;
    node->left = statement;
    node->right = statementList;
    return node;
}

ASTNode* CreateOrNode(ASTNode *left, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_LOGIC_OP;
    node->op = OR_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateAndNode(ASTNode *left, ASTNode *right)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_LOGIC_OP;
    node->op = AND_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateIfNode(ASTNode *condition, ASTNode* body, ASTNode *elseNode)
{
ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
node->type = ASTNODE_IF;
node->left = condition;
node->right = body;
node->elseNode = elseNode;
return node;
}
ASTNode* CreateWhileNode(ASTNode *condition, ASTNode *loop)
{
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_WHILE;
    node->left = condition ;
    node->right = loop;
    return node;
}
ASTNode* CreateLENode(ASTNode *left, ASTNode *right) {
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = LE_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateGENode(ASTNode *left, ASTNode *right) {
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = GE_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateLTNode(ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = LT_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateGTNode(ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = GT_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateNENode(ASTNode *left, ASTNode *right) {
   ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = NE_OP;
    node->left = left;
    node->right = right;
    return node;
}
ASTNode* CreateEQNode(ASTNode *left, ASTNode *right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = ASTNODE_COMPARE;
    node->op = EQ_OP;
    node->left = left;
    node->right = right;
    return node;
}
void AddDeclaration(char* name){
    struct SymbolTable *add = (struct SymbolTable *) malloc(sizeof(struct SymbolTable));
    if(NULL== add) printf("\n Symbol Table Declaration failed \n");
    add->ident = name;
    add->regNum = NULL;
    add->next =NULL;
    
    struct SymbolTable *tail  = head;
    if(tail){
      do {
      if(0 == strcmp(name, tail->ident)) {
          printf("Error: IDENT %s has already been declared .\n",name);
          exit(1);
      }
      if(tail->next !=NULL) tail = tail->next;
    } while(tail->next);
     tail->next = add;
}else {
    head = add;
   }
}

struct SymbolTable *GetSymbolTable(char *name) {
    struct SymbolTable *ptr = head;
    while(ptr !=NULL) {
    if(ptr->ident !=NULL && 0 == strcmp(name, ptr->ident)) {
        return ptr;
}
    ptr =  ptr->next;
}
   return NULL;
} 
 bool isEntryDeclared(char *name) {
   return (NULL != GetSymbolTable(name));
}
void PrintTable() {
 struct SymbolTable *ptr = head;
 int counter;
 while( ptr != NULL) {
   printf("%d: ident:%s register:%s counter", counter, ptr->ident, ptr->regNum);
   ptr = ptr->next;
   counter++;
}
 printf("\n");

}
/**
 * C++ version 0.4 char* style "itoa":
 * Written by Luke Chmela
 * Released under GPLv3;
 */
char* itoa(int value, char* result, int base) {
    //check that the base if valid
    if(base < 2 || base > 36) { *result = '\0'; return result;}
    
    char* ptr = result, *ptr1 =result, tmp_char;
    int tmp_value;
    
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        [35 + (tmp_value -value * base)];
    } while (value);
    
    // Aplly negative sign
    if(tmp_value < 0) *ptr++ = '_';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++= tmp_char;
    }
    return result;
    }


void GenerateILOC(ASTNode *node, FILE *out) {
   PrintFile = out;
     
   // Traverse nodes by DFS
   if(node->left !=NULL && (node->type != ASTNODE_IF) && (node->type != ASTNODE_WHILE)){
    GenerateILOC(node->left, NULL);
}
   if((node->right != NULL) && (node->type !=ASTNODE_STLIST) && (node->type != ASTNODE_WHILE)){
   GenerateILOC(node->right, NULL);
}

switch(node->type) {
        char *newLabel;
    case ASTNODE_ASSIGN:
       Emit(STOREAI_OP, node->right->regNum, NULL, append("rarp, @", node->left->name));
       break;
    case ASTNODE_IDENT:
        node->regNum = GetSymbolTable(node->name)->regNum;
        if(node->regNum == NULL) node->regNum = GetNextReg();
        Emit(LOADAI_OP, "rarp", append("@", node->name), node->regNum);
        GetSymbolTable(node->name)->regNum = node->regNum;
        break;
     case ASTNODE_NUM:
        node->regNum = GetNextReg();
        char numToString[5];
        itoa(node->num, numToString, 10);
        Emit(LOADAI_OP, numToString, NULL, node->regNum);
        break;
     case ASTNODE_ARITH_OP:
        node->regNum = GetNextReg();
        Emit(node->op, node->left->regNum, node->right->regNum, node->regNum);
        break;
    case ASTNODE_LOGIC_OP:
        node->regNum =GetNextReg();
        Emit(node->op, node->left->regNum, node->right->regNum, node->regNum);
        break;
    case ASTNODE_COMPARE:
        node->regNum =GetNextReg();
        Emit(node->op, node->left->regNum, node->right->regNum, node->regNum);
        break;
    case ASTNODE_STLIST:
        if(node->right !=NULL){
            GenerateILOC(node->right,NULL);
         }
             break;
    case ASTNODE_WHILE:
              //char *newLabel;
             if(node->labelNum == NULL) node->labelNum = GetLabel();
                Emit(LABEL_OP, node->labelNum, NULL, NULL);
                GenerateILOC(node->left, NULL);
                node->right->labelNum = GetLabel();
                newLabel = GetLabel();
                Emit(CBR_OP, node->left->regNum, NULL, append(node->right->labelNum,append(",",newLabel)));
                Emit(LABEL_OP, node->right->labelNum, NULL, NULL);
                if(node->right !=NULL) GenerateILOC(node->right, NULL);
                Emit(JMP_OP, node->labelNum, NULL, NULL);
                Emit(LABEL_OP, newLabel, NULL, NULL);
                break;
    case ASTNODE_IF:
             //char *newLabel;
             if(node->labelNum == NULL) node->labelNum = GetLabel();
             Emit(LABEL_OP, node->labelNum, NULL, NULL);
             GenerateILOC(node->left, NULL);
             node->right->labelNum = GetLabel();
             
             if(NULL != node->elseNode){
                 node->elseNode->labelNum = GetLabel();
                 Emit(CBR_OP, node->left->regNum, NULL, append(node->right->labelNum, append(",", node->elseNode->labelNum)));
                 newLabel = GetLabel();
             } else {
                 newLabel = GetLabel();
                 Emit(CBR_OP, node->left->regNum, NULL, append(node->right->labelNum,append(",",newLabel)));
             }
             Emit(LABEL_OP, node->right->labelNum, NULL, NULL);
              if(node->right !=NULL) GenerateILOC(node->right, NULL);
              Emit(JMP_OP, newLabel, NULL, NULL);
             
             if(node->elseNode != NULL) {
                 Emit(LABEL_OP, node->elseNode->labelNum, NULL, NULL);
                 GenerateILOC(node->elseNode, NULL);
             }
             Emit(LABEL_OP, newLabel, NULL, NULL);
             break;
             default:
             printf("Something went wrong during transversing nodes");
             break;
             }
             }
void Emit(ASTOp op, char *str1, char *str2, char *dest) {
    char * opcode;
    switch (op) {
        case LOADAI_OP:
            opcode = "loadAI";
            break;
        case LOADI_OP:
            opcode = "loadi";
            break;
        case STOREAI_OP:
            opcode = "storeAI";
            break;
        case JMP_OP:
            opcode = "jumpi";
            break;
        case CBR_OP:
            opcode = "cbr";
            break;
        case ADD_OP:
            opcode = "add";
            break;
        case SUB_OP:
            opcode = "sub";
            break;
        case MULT_OP:
            opcode = "mult";
            break;
        case DIV_OP:
            opcode = "div";
            break;
        case OR_OP:
            opcode = "or";
            break;
        case GE_OP:
            opcode = "cmp_GE";
            break;
        case GT_OP:
            opcode = "cmp_GT";
            break;
        case LE_OP:
            opcode = "cmp_LE";
            break;
        case LT_OP:
            opcode = "cmp_LT";
            break;
            
        case EQ_OP:
            opcode = "cmp_EQ";
            break;
        case NE_OP:
            opcode = "cmp_NE";
            break;
        case LABEL_OP:
            //do nothing
            break;
        default:
            printf("Error: During Emit Call Function");
                   exit(1);
                   break;
    }
    if(op ==LABEL_OP) fprintf(PrintFile, "\n%s: ", str1);
    else if (str2 == NULL && dest == NULL) fprintf(PrintFile, "%s => %s\n",opcode, str1);
    else if(str2 !=NULL)fprintf(PrintFile, "%s, %s, %s => %s\n", opcode, str1, str2, dest);
    else fprintf(PrintFile, "%s %s => %s\n", opcode, str1, dest);
    
    }
    char *GetLabel() {
        char *insert ="L";
        char label[5];
        itoa(labelNum, label, 10);
        labelNum++;
        return append(insert,label);
    }
    char *GetNextReg(){
        char *insert ="r";
        char reg[5];
        itoa(regNum, reg, 10);
        regNum++;
        return append(insert,reg);
        
}
    char *append(char *str1, char *str2){
        char *newStr;
        strcat(newStr,str1);
        strcat(newStr,str2);
        return newStr;
    }
                 
             
                
             









