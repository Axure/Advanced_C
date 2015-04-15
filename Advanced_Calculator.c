#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#undef _DEBUG

#ifdef _DEBUG

#endif

int get_precedence(const char ch);
int get_order(const char ch);
int get_type(const char ch);

typedef struct Node * pNode;
typedef struct Node
{
    void * pElement;
    pNode pPrev, pNext;
} Node;

typedef struct List * pList;
typedef struct List {
    pNode pHead, pTail;
    int elementSize;
} List;

typedef void(*PrintFunction)(void *);

void unit_test();
void init_list(List* pList, int size);
void destroy_list(List* pList);
void add_head(List* pList, void * pElement);
void add_tail(List* pList, void * pElement);
void print_list(List* pList, PrintFunction printFunction);
void print_nested_list(List* pList, PrintFunction printFunction);
void destroy_nested_list(List* pList);

/* I want to combine va_list with pseudo-generics */

void print_number(void * pNumber);


typedef struct Token {
    union {
        int number;
        char operation;
    } content;
    void * address;
    int type;
} Token;

void print_token(void * pToken);

typedef List Stack;
void * get_top(const Stack* pStack);
void * stack_pop(Stack* pStack);

List read_token_list();

typedef struct TreeNode * pTreeNode;
typedef struct TreeNode
{
    void * pElement;
    pTreeNode pParent, pLeft, pRight;
} TreeNode;
typedef struct Tree
{
    pTreeNode pRoot;
    int elementSize;
} Tree;


void init_tree(Tree* pTree, int size);
pTreeNode new_treenode(int size, void* pContent);
void set_to_left(TreeNode* pParent, TreeNode* pLeftChild);
void set_to_right(TreeNode* pParent, TreeNode* pRughtChild);
void destroy_tree(TreeNode* pRoot);
void destroy_treenode(TreeNode* pOldTreeNode);
List to_nested_list(List* pOldList);
Tree get_ast(List* pList);
int eval_ast(Tree* pTree);

int eval_binary_operation(char operation, int x, int y);

int main(int argc, char const *argv[])
{
#define _DEBU
    const char * _debug = "-x";
    printf("Argument number is %d, argument 2 is %s\n", argc, argv[1]);
    if (argc >= 2 && strcmp(argv[1], _debug) == 0)
    {
        printf("Entering deubg mode!...\n");
        
        
#ifdef _DEBUG
        printf("Debug function is running!");
        printf("Debug function is not running!");
#endif
    }
    unit_test();
    return 0;
}


void unit_test()
{
    List myList;
    List* pMyList = &myList;
    init_list(pMyList, sizeof(int));
    int i;
    i = 3;
    add_tail(pMyList, &i);
    add_tail(pMyList, &i);
    
    i = 4;
    add_tail(pMyList, &i);
    add_tail(pMyList, &i);
    add_tail(pMyList, &i);
    add_tail(pMyList, &i);
    print_list(pMyList, print_number);
    
#ifdef _DEBUG
    
    printf("Tail address is %p \n", pMyList->pTail);
    printf("Tail prev address is %p \n", pMyList->pTail->pPrev);
    
    printf("\nTop is: ");
    print_number(get_top(pMyList));
    
    stack_pop(pMyList);
    printf("Tail address is %p \n", pMyList->pTail);
    printf("\nTop is: ");
    print_number(get_top(pMyList));
    stack_pop(pMyList);
    printf("Tail address is %p \n", pMyList->pTail);
    printf("\nTop is: ");
    print_number(get_top(pMyList));
    stack_pop(pMyList);
    printf("Tail address is %p \n", pMyList->pTail);
    printf("\nTop is: ");
    print_number(get_top(pMyList));
    stack_pop(pMyList);
    printf("\nTop is: ");
    print_number(get_top(pMyList));
    printf("\n");
    
#endif
    print_list(pMyList, print_number);
    
    List newList = read_token_list();
    print_list(&newList, print_token);
    
    List refinedList;
    refinedList = to_nested_list(&newList);
    
#ifdef _DEBUG
    printf("Succeessfully converted to nested list!\n");
#endif
    print_nested_list(&refinedList, print_token);
    // #undef _DEBUG
    print_list(&refinedList, print_token);
    
    
    
    Token token1, token2;
    token1.content.number = 3;
    token1.type = 1;
    memcpy(&token2, &token1, sizeof(Token));
    print_token(&token1);
    print_token(&token2);
    
    printf("Size of Token is %lu.\n", sizeof(Token));
    
    
    destroy_list(pMyList);
    destroy_list(&newList);
    
    Tree newAst = get_ast(&refinedList);
    printf("Result is %d.\n", eval_ast(&newAst));
}

int get_precedence(char ch)
{
    /* What is more small? */
    if (ch == '\\' || ch == '%') return 4;
    if (ch == '+' || ch == '-') return 5;
    if (ch == '*' || ch == '/') return 6;
    if (ch == '^') return 7;
    
    return 100;
    
}

int get_order(char ch)
{
    if (ch == '^') return -1;
    else return 1;
}

int get_type(const char ch)
{
    if (ch >= 48 && ch <= 57) return 1;
    if (ch == '+' || ch == '-' || ch == '\\' || ch == '/' || ch == '^' || ch == '*' || ch == '%') return 2;
    if (ch == '(' || ch == ')') return 8;
    if (1) return 4; /* Defaults to complex functions */
    /* Actually I don't want non-long functions in long mode */
    /* And invalid expression checker. We have to do that */
    /* Maybe you can register your own functions in an array and we can use hash? */
    return 8;
}

void init_list(List* pList, int size)
{
    pList->pHead = NULL;
    pList->pTail = NULL;
    pList->elementSize = size;
}

void destroy_list(List* pList)
{
    Node* _pHead = pList->pHead;
    Node* _pAuxNode;
    while (_pHead != NULL)
    {
        _pAuxNode = _pHead;
        _pHead = _pHead->pNext;
        free(_pAuxNode);
    }
}

void add_head(List* pList, void * pElement)
{
    void * newPointer = malloc(pList->elementSize);
    memcpy(newPointer, pElement, pList->elementSize);
    
    Node* newNode = (pNode)malloc(sizeof(Node));
    newNode->pElement = newPointer;
    
    newNode->pNext = pList->pHead;
    newNode->pPrev = NULL;
    
    if (pList->pHead == NULL)
    {
        pList->pHead = newNode;
        pList->pTail = newNode;
    }
    else
    {
        pList->pHead->pPrev = newNode;
        pList->pHead = newNode;
    }
    
    
    
}

void add_tail(List* pList, void * pElement)
{
#ifdef _DEBUG
    printf("\nadd_tail: Element size is %d.\n", pList->elementSize);
#endif
    void * newPointer = malloc(pList->elementSize);
    memcpy(newPointer, pElement, pList->elementSize);
    
    Node* newNode = (pNode)malloc(sizeof(Node));
    newNode->pElement = newPointer;
    
    newNode->pPrev = pList->pTail;
    newNode->pNext = NULL;
    
    if (pList->pTail == NULL)
    {
        pList->pTail = newNode;
        pList->pHead = newNode;
    }
    else
    {
        pList->pTail->pNext = newNode;
        
        pList->pTail = newNode;
        
#ifdef _DEBUG
        printf("Added tail address is %p \n", pList->pTail);
#endif
    }
    
    
}

void print_list(List* pList, PrintFunction printFunction)
{
    Node* _pHead = pList->pHead;
    while (_pHead != NULL)
    {
#ifdef _DEBUG
        printf("address %p \n", _pHead);
#endif
        
        printFunction(_pHead->pElement);
        _pHead = _pHead->pNext;
    }
    printf("\n");
}

void print_nested_list(List* pOldList, PrintFunction printFunction)
{
    Node* _pHead = pOldList->pHead;
    
    Stack _tokenStack;
    Stack* _pTokenStack = &_tokenStack;
    init_list(_pTokenStack, sizeof(Token));
    
    while (_pHead != NULL)
    {
#ifdef _DEBUG
        printf("print_nested_list: address %p, element type is %d\n", _pHead, ((Token*)(_pHead->pElement))->type);
#endif
        if (((Token*)(_pHead->pElement))->type != -1)
        {
#ifdef _DEBUG
            printf("print_nested_list: Encountered normal element. Element ASCII is %d.\n", ((Token*)(_pHead->pElement))->content.number);
#endif
            printFunction(_pHead->pElement);
        }
        else
        {
            printf("{#%d}", ((Token*)(_pHead->pElement))->content.number);
            add_head(_pTokenStack, _pHead->pElement);
        }
        
        _pHead = _pHead->pNext;
#ifdef _DEBUG
        printf("print_nested_list: pHead is currently at %p.\n", _pHead);
#endif
    }
    printf("\n");
    Token* _pToken = (Token*)stack_pop(_pTokenStack);
    while (_pToken != NULL)
    {
        printf("#%d: ", _pToken->content.number);
        print_nested_list((pList)_pToken->address, printFunction);
        _pToken = (Token*)stack_pop(_pTokenStack);
    }
    
}


void print_number(void * pNumber)
{
    printf("%d ", *(int *)pNumber);
}

void print_token(void * pToken)
{
    
    switch (((Token *)pToken)->type)
    {
        case 1:
            
#ifdef _DEBUG_1
            
            printf("\nprint_token: Debugging!\n");
#endif
            
            printf("%d", ((Token *)pToken)->content.number);
            break;
            
        case -1:
#ifdef _DEBUG
            printf("\n===\nprint_token: Address is %p.\nFormula id is %d.\n===\n", ((Token *)pToken)->address, ((Token *)pToken)->content.number);
#endif
            break;
        default:
            printf("%c", ((Token *)pToken)->content.operation);
            break;
    }
}

void * get_top(const Stack* pStack)
{
    if (pStack->pHead != NULL)
    {
        return pStack->pTail->pElement;
    }
    else
    {
        return NULL;
    }
}

void * stack_pop(Stack* pStack)
{
    if (pStack->pTail != NULL)
    {
        
#ifdef _DEBUG
        printf("Stack %p is Not Null!\n", pStack);
#endif
        
        void * _pAux;
        _pAux = pStack->pTail->pElement;
        
#ifdef _DEBUG
        print_number(_pAux);
        printf("\n");
#endif
        
        
        if (pStack->pTail->pPrev != NULL)
        {
            pStack->pTail = pStack->pTail->pPrev;
            free(pStack->pTail->pNext);
            pStack->pTail->pNext = NULL;
        }
        else
        {
            free(pStack->pTail);
            pStack->pTail = NULL;
            pStack->pHead = NULL;
        }
        
        
        return _pAux;
    }
    return NULL;
}




List read_token_list()
{
    List newList;
    List* pNewList = &newList;
    init_list(pNewList, sizeof(Token));
    
    
    
    char ch;
    Token _tempToken;
    _tempToken.type = 0; /* Empty type? */
    
    
    
    while((EOF != (ch = getchar()) && ch != '\n'))
    {
        
        /* Things are a little bit different from the polynomial case, as you have to record all the chars. */
#ifdef _DEBUG
        printf("Got character %c!\n", ch);
#endif
        switch (get_type(ch))
        /* Be ware of the getchar() complex situation */
        {
            case 1: /* Receives a digit */
#ifdef _DEBUG
                printf("A digit! %d\n", ch - 48);
#endif
                if (_tempToken.type == 0)
                {
                    _tempToken.type = 1;
                    _tempToken.content.number = ch - 48;
                } else {
                    if (_tempToken.type == 1)
                    {
                        _tempToken.content.number = 10 * _tempToken.content.number + ch - 48;
                    }
                }
                
                break;
            case 2: /* Receives a binary */
                if (_tempToken.type == 0)
                {
                    
                }
                if (_tempToken.type == 1)
                {
                    add_tail(pNewList, &_tempToken);
                    _tempToken.type = 2;
                    _tempToken.content.operation = ch;
                    add_tail(pNewList, &_tempToken);
                    _tempToken.type = 0;
                }
                if (_tempToken.type == -8)
                {
                    _tempToken.type = 2;
                    _tempToken.content.operation = ch;
                    add_tail(pNewList, &_tempToken);
                    _tempToken.type = 0;
                }
                break;
                /* Other cases are invalid? */
                
            case 4: /* Receives an unary operation */
                if (_tempToken.type == 0)
                {
                    _tempToken.type = 4;
                    _tempToken.content.operation = ch;
                    add_tail(pNewList, &_tempToken);
                    _tempToken.type = 0;
                }
                if (_tempToken.type == 4)
                {
                    
                    /* We don't currently deal with this case */
                }
                break;
                
            case 8: /* Receives a bracket */
                if (_tempToken.type == 0)
                {
                    
                }
                if (_tempToken.type == 1)
                {
                    add_tail(pNewList, &_tempToken);
                }
                
                _tempToken.type = 8;
                _tempToken.content.operation = ch;
                add_tail(pNewList, &_tempToken);
                if (_tempToken.content.operation == '(')
                {
                    _tempToken.type = 0;
                }
                else
                {
                    _tempToken.type = -8;
                }
                
                break;
                
            default:
                break;
                
        }
        
    }
    
    /* We should check that if something is left here ! */
    if (_tempToken.type == 1)
    {
        add_tail(pNewList, &_tempToken);
    }
    
    return newList;
}

List to_nested_list(pList pOldList)
{
    int count = 1;
    
    Node* _pHead = pOldList->pHead;
    
    Stack scopeStack;
    Stack* pScopeStack = &scopeStack;
    init_list(pScopeStack, sizeof(pList));
    
    List resultList;
    List* pResultList = &resultList;
    init_list(pResultList, sizeof(Token));
    // add_tail(pScopeStack, (void*)&pResultList);
    
    pList _pCurrentList = pResultList;
#ifdef _DEBUG
    printf("to_nested_list: pResultList element size is %d.\n", sizeof(Token));
    printf("to_nested_list: pCurrent element size is %d.\n", _pCurrentList->elementSize);
#endif
    
    pList _pNewList;
    
    Token _tempToken;
    
    while (_pHead != NULL)
    {
        Token* pToken = (Token*)(_pHead->pElement);
#ifdef _DEBUG
        printf("to_nested_list: Current token is: ");
        print_token(pToken);
        printf(", type is %d, address is %p.\n", pToken->type, _pHead);
#endif
        if (pToken->type == 8) {
#ifdef _DEBUG
            printf("pToken type is %d. pToken is %c.\n", pToken->type, pToken->content.operation);
#endif
            if (pToken->content.operation == '(')
            {
                _pNewList = (List*)malloc(sizeof(List));
#ifdef _DEBUG
                printf("to_nested_list: \n\nEntering! Current stack tops at %p\n\n", _pNewList);
                printf("Size of Node is %d.\n", sizeof(Node));
                printf("Size of Token is %d.\n", sizeof(Token));
#endif
                init_list(_pNewList, sizeof(Token));
                
                
                _tempToken.type = -1;
                _tempToken.content.number = count;
#ifdef _DEBUG
                printf("~~~~~\nAdded formula count is %d.\n~~~~~\n", count);
#endif
                _tempToken.address = (void*)_pNewList;
                add_tail(_pCurrentList, (void*)(&_tempToken));
#ifdef _DEBUG
                printf("to_nested_list: Address token is: ");
                print_token(&_tempToken);
                printf("\n");
                
                printf("Entering address is %p\n", _pCurrentList);
#endif
                count += 1;
                add_tail(pScopeStack, (void*)&_pCurrentList);
                _pCurrentList = _pNewList;
                
                
#ifdef _DEBUG
                printf("\n\nto_nested_list: ENTERING! Current stack tops at %p\n\n", _pNewList);
#endif
            }
            else
            {
#ifdef _DEBUG
                printf("Leaving!\n");
#endif
                _pCurrentList = *(List**)stack_pop(pScopeStack);
#ifdef _DEBUG
                printf("Leaving address is %p\n", _pCurrentList);
                
                printf("\n\nto_nested_list: LEAVING! Current stack tops at %p\n\n", _pCurrentList);
#endif
            }
        }
        else
        {
#ifdef _DEBUG
            printf("to_nested_list: TOKEN being added is: ");
            print_token((pToken));
            
            
            printf("Current list is at %p.\n", _pCurrentList);
#endif
            add_tail(_pCurrentList, _pHead->pElement);
#ifdef _DEBUG
            printf(", type is %d, address is %p.\n", ((Token*)get_top(_pCurrentList))->type, get_top(_pCurrentList));
#endif
        }
        _pHead = _pHead->pNext;
        if (_pHead == NULL)
        {
#ifdef _DEBUG
            printf("NULL!\n");
#endif
        }
        else
        {
#ifdef _DEBUG
            printf("Next address is %p!\n", _pHead);
            printf("to_nested_list: Next is: ");
            print_token((Token*)_pHead->pElement);
            printf("\n");
#endif
        }
        
    }
#ifdef _DEBUG
    printf("Element size of result list is %d.\n", resultList.elementSize);
#endif
    return resultList;
}

void init_tree(Tree* pTree, int size)
{
    pTree->pRoot = NULL;
    pTree->elementSize = size;
}

pTreeNode new_treenode(int size, void* pContent)
{
    TreeNode* pNewTreeNode;
    printf("new_treenode Entered new tree_node.\n");
    pNewTreeNode = (pTreeNode)malloc(size);
    pNewTreeNode->pLeft = NULL;
    pNewTreeNode->pRight = NULL;
    pNewTreeNode->pParent = NULL;
    
    printf("new_treenode: pContent is now at %p.\n", pContent);
    printf("new_treenode: pTreeNode is now at %p.\n", pNewTreeNode);
    
    pNewTreeNode->pElement = pContent;
    
    return pNewTreeNode;
}

void set_to_left(TreeNode* pParent, TreeNode* pLeftChild)
{
    printf("Parent is at %p.\n", pParent);
    pParent->pLeft = pLeftChild;
    pLeftChild->pParent = pParent;
    
}


void set_to_right(TreeNode* pParent, TreeNode* pRightChild)
{
    pParent->pRight = pRightChild;
    pRightChild->pParent = pParent;
}

/* We don't need to worry about brackets anymore */

Tree get_ast(pList pList)
{
    
    Tree newTree;
    Tree* pNewTree = &newTree;
    init_tree(pNewTree, sizeof(Token));
    
    
    TreeNode* pCurrent = NULL;
    TreeNode* _pAuxTreeNode;
    
    Stack symbolStack; /* We store the address.. OMG! */
    Stack* pSymbolStack = &symbolStack;
    init_list(pSymbolStack, sizeof(pTreeNode));
    
    
    /* Traverse the token list */
    
    Node* _pHead = pList->pHead;
    Token _tempToken;
    
    
    /* We need to store all the data of the scopes. Scopes are just stackes */
    Tree _AuxTree;
    while (_pHead != NULL)
    {
        printf("get_ast: Pointer is now at %p.\n", _pHead);
        /* We need to switch to cases here! */
        _tempToken = *(Token*)_pHead->pElement;

        _pAuxTreeNode = new_treenode(sizeof(Token), _pHead->pElement);
        
        printf("\n===\nToken is ");
        print_token(&_tempToken);
        printf("\n===\n");
        switch (_tempToken.type)
        {
            case -1:
                
                _AuxTree = get_ast((List*)(((Token*)(pCurrent->pElement))->address));
                ((Token*)(_pAuxTreeNode->pElement))->address = &_AuxTree;
                if (pCurrent == NULL)
                {
                    pCurrent = _pAuxTreeNode;
                }
                else
                {
                    
                    set_to_right(pCurrent, _pAuxTreeNode);
                }
                
                break;
                
            case 1:
                printf("get_ast: Type is 1!\n");
                if (pCurrent == NULL)
                {
                    pCurrent = _pAuxTreeNode;
                }
                else
                {
                    
                    pCurrent->pRight = _pAuxTreeNode;
                    _pAuxTreeNode->pParent = pCurrent;
                }
                
                break;
                
            case 2:
                
                while (pCurrent->pParent != NULL && get_precedence(((Token*)(pCurrent->pElement))->content.operation) > get_precedence(_tempToken.content.operation))
                {
                    pCurrent = pCurrent->pParent;
                }
                
                if (pCurrent->pParent == NULL && ((Token*)(pCurrent->pElement))->type == 1)
                {
                    printf("get_ast: Parent is NULL!\n");
                    set_to_left(_pAuxTreeNode, pCurrent);
                    pCurrent = _pAuxTreeNode;
                }
                else
                {
                    if (get_precedence(((Token*)(pCurrent->pElement))->content.operation) > get_precedence(_tempToken.content.operation))
                    {
                        
                        printf("get_ast: Interesting at root!\n");
                        set_to_left(_pAuxTreeNode, pCurrent);
                        pCurrent = _pAuxTreeNode;
                    }
                    
                    if (get_precedence(((Token*)(pCurrent->pElement))->content.operation) < get_precedence(_tempToken.content.operation))
                    {
                        /* If current precedence is lower than the new precedence */
                        set_to_left(_pAuxTreeNode, pCurrent->pRight);
                        set_to_right(pCurrent, _pAuxTreeNode);
                        pCurrent = _pAuxTreeNode;
                        
                    }
                    else
                    {
                        /* If current precedence is equal to the new precedence */
                        if (((Token*)(pCurrent->pElement))->content.operation == _tempToken.content.operation && get_order(_tempToken.content.operation) == -1)
                        {
                            set_to_left(_pAuxTreeNode, pCurrent->pRight);
                            set_to_right(pCurrent, _pAuxTreeNode);
                            pCurrent = _pAuxTreeNode;
                        }
                        else
                        {
                            set_to_left(pCurrent->pParent, _pAuxTreeNode);
                            set_to_right(_pAuxTreeNode, pCurrent);
                            pCurrent = _pAuxTreeNode;
                            
                        }
                        
                    }
                    
                }
                
                break;
                
            default:
                break;
        }
        _pHead = _pHead->pNext;
        
    }
    
    while (pCurrent->pParent != NULL)
    {
        pCurrent = pCurrent->pParent;
    }
    newTree.pRoot = pCurrent;
    return newTree;
}


int eval_ast(Tree* pTree)
{
    TreeNode* pRoot = pTree->pRoot;
    Token currentToken = *(Token*)(pRoot->pElement);
    if (currentToken.type == 1) return currentToken.content.number;
    if (currentToken.type == -1) return eval_ast((Tree*)(currentToken.address));
    if (currentToken.type == 2)
    {
        Tree leftSubTree, rightSubTree;
        init_tree(&leftSubTree, sizeof(Token));
        leftSubTree.pRoot = pRoot->pLeft;
        init_tree(&rightSubTree, sizeof(Token));
        rightSubTree.pRoot = pRoot->pRight;
        return eval_binary_operation(currentToken.content.operation, eval_ast(&leftSubTree), eval_ast(&rightSubTree));
    }
    return -1;
}

int eval_binary_operation(char operation, int x, int y)
{
    switch (operation)
    {
        case '+':
            return x + y;
            break;
        case '-':
            return x + y;
            break;
            
        case '*':
            return x * y;
            break;
            
            
            
        case '\\':
            return x / y;
            break;
            
        case '%':
            return x % y;
            break;
            
        case '^':
            return pow(x, y);
            break;
        default:
            return -1;
            break;
    }
}