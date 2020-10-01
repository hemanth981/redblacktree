#include<stdlib.h>
#include<stdio.h>

typedef struct rbtree node;
struct rbtree
{
    int data;
    node*left,*right;
    int colour;    //1=red, 0=black
};

void paren(node*tree)
{
    printf("( ");
    if(tree!=NULL)
    {
        printf("%d ",tree->data);
        if(tree->colour==1)
            printf("R ");
        else if(tree->colour==0)
            printf("B ");
        else
            {
                printf("U ");   //UNKNOWN COLOUR
            }
            
        paren(tree->left);
        paren(tree->right);
        printf(") ");
    }
    else
        printf(") ");
}

int checkrbtree_base(node*root,int*value)
    {
        int r,l;//RETURN -2 if not BST
        if(root==NULL)
        return -1;
        if(root->colour==1)
        {
            if(root->left!=NULL&&root->left->colour==1)
            return -2;
            if(root->right!=NULL&&root->right->colour==1)
            return -2;    
        }
        l=checkrbtree_base(root->left, value);
        if(!(*value<root->data))   //check if prev val < cur data(inorder should be ascending)
            {return -2;}
        *value=root->data;      //update *value to cur node(inorder)
//printf("<%d>", *value);
        r=checkrbtree_base(root->right, value); 
        //CHECKING FOR BST PART DONE
        //FOUND NOT BST/AVL IN SOME SUBTREE, SO NOT AVL
        if(l==-2||r==-2)
            return -2;
        //check if rbt and return height
            if(l==r)//black height of left=right
                {
                    if(root->colour==0)
                    return l+1;
                    else
                    return l;
                }
            else
                return -2;        
    }

int isRedBlack(node*tree)
{
    int value=-99999;
    if(tree==NULL)
    return 1;
    else
    {
        if(tree->colour!=0)
        return 0;
    }
    value= checkrbtree_base(tree, &value);
    if(value==-2)
    return 0;
    else
    return 1;
    
}

node* pareninsert(node*tree)
{
    //CREATE CHILD
    int el;char ch=getchar();
    if(ch=='(')
    {
        if(scanf("%d ",&el)==1)
        {
            node*new = (node*)malloc(sizeof(node));
            new->data = el;
            scanf("%c ",&ch);
            if(ch=='B')
                new->colour=0;
            else if(ch=='R')
                new->colour=1;
            new->left=pareninsert(new);
            new->right=pareninsert(new);
            getchar();getchar();
            return new;
        }
        else
        {
            getchar();getchar();
            return NULL;
        }
    }
}
int main()
{
    node*tree=pareninsert(tree);
    //paren(tree);
    printf("%d",isRedBlack(tree));
}

// Try examples

/*
( 33 B ( 13 R ( 11 B ( ) ( ) ) ( 21 B ( 15 R ( ) ( ) ) ( 31 R ( ) ( ) ) ) ) ( 53 B ( 41 B ( ) ( ) ) ( 61 R ( ) ( ) ) ) )



( 33 B ( 13 R ( 11 B ( ) ( ) ) ( 21 B ( 15 R ( ) ( ) ) ( 31 R ( ) ( ) ) ) ) ( 53 B ( 41 R ( ) ( ) ) ( 61 R ( ) ( ) ) ) )

*/
