#include<stdio.h>
#include<stdlib.h>
/*
1.Create a sparse matrix
2.Print the sparse matrix
3.Add 1 to matrix at a position
4.Delete 1 from a position
*/
struct sparse{
    int row ; 
    int col ;
    struct sparse *rownext ;
    struct sparse *colnext ;
};
struct sparse * create()
{
    int r,c,count ;
    printf("Enter the number of rows and columns : \n") ;
    scanf("%d %d",&r,&c) ;
    struct sparse *Head = (struct sparse *)malloc(sizeof(struct sparse)) ;
    Head->row = r ;
    Head->col = c ;
    Head->rownext = NULL ;
    Head->colnext = NULL ;
    printf("Enter the number of 1s :\n") ;
    scanf("%d",&count) ;
    int R,C ;
    while(count--)
    {
       printf("Enter the number of rows number and column number : \n") ;
       scanf("%d %d",&R,&C) ;
       struct sparse* new = (struct sparse *)malloc(sizeof(struct sparse)) ;
       int flag = 1 ;
       struct sparse* temp , *temprow = Head , *head = Head ;
       while(head->rownext)
       {
           if(head->rownext->row == R){
               temp = head->rownext ;
               flag = 0 ;
               break ;
           }
           if(head->rownext->row > R){temprow = head ;
           break ;}
           head = head->rownext ;
       }
       if(flag){temp = (struct sparse *)malloc(sizeof(struct sparse)) ;
       temp->rownext = temprow->rownext ;
       temp->colnext = NULL ;
       temprow->rownext = temp ;
       temp->row = R ;
       temp->col = 0 ;}
        while(temp->colnext){
                   if(temp->colnext->col > C) break ;
                   temp = temp->colnext ;
               }
               new->colnext = temp->colnext ;
               temp->colnext = new ;
               new->rownext = NULL ;
               new->row = R ;
               new->col = C ; 
         head = Head ;
         flag = 1 ;
         while(head->colnext)
         {
             if(head->colnext->col == C){
                 temp = head->colnext ;
                 flag = 0 ;
             }
             if(head->colnext->col > C){temprow = head ;
           break ;}
             head = head->colnext ;
         } 
         if(flag){
          temp = (struct sparse *)malloc(sizeof(struct sparse)) ;
       temp->colnext = temprow->colnext ;
       temp->rownext = new ;
       temprow->colnext = temp ;
       temp->row = 0 ;
       temp->col = C ;   
         }
         while(temp->rownext)
         {
             if(temp->rownext->col == C) break ;
             if(temp->rownext->col > C){
                 new->rownext = temp->rownext ;
                 temp->rownext = new ;
             }
         }
    }
return Head ;
}
void print(struct sparse *Head)
{
   int r = Head->row , c = Head->col ;
   struct sparse *head = Head->rownext ;
   for(int i=1;i<=r;i++)
   {
     if(i< head->row || head == NULL)
     {
         for(int j=1;j<=c;j++)
         {
             printf("0 ") ;
         }
     }
     if(i==head->row)
     {
         struct sparse *chead = head->colnext ;
         for(int j=1;j<=c;j++)
         {
             if(j< chead->col || chead == NULL)
              printf("0 ") ;
             if(j==chead->col){
               printf("1 ") ;
               chead = chead->colnext ;
             }
         }
         head = head->rownext ;
         printf("\n") ;
     }
   }
}
void delete(struct sparse *Head,int r , int c)
{
   struct sparse *head = Head->rownext ;
   while(head)
   {
     if(head->row < r) head = head->rownext ;
     if(head->row == r)
     {
         struct sparse *chead = head ;
         while(chead)
         {
             if(chead->colnext->col < c) chead = chead->colnext ;
             if(chead->colnext->col == c){
               chead->colnext = chead->colnext->colnext ;
             }
         }
         break ;
     }
   } 
   head = Head->colnext ;
    while(head)
   {
     if(head->col < r) head = head->colnext ;
     if(head->col == c)
     {
         struct sparse *chead = head ;
         while(chead)
         {
             if(chead->rownext->row < r) chead = chead->rownext ;
             if(chead->rownext->row == r){
                 struct sparse *temp = chead->rownext ;
               chead->rownext = chead->rownext->rownext ;
               free(temp) ;
             }
         }
         break ;
     }
   } 
}
struct sparse *add(struct sparse *Head,int r , int c)
{
   struct sparse *node = (struct sparse *)malloc(sizeof(struct sparse)) ;
   node->row = r ;
   node->col = c ;
   struct sparse *head = Head ;
   struct sparse *chead = Head ;
   int flag = 1 ;
   while(chead->colnext)
   {
       if(chead->colnext->col == c){
           flag = 0 ;
           chead = chead->colnext ;
           break ;
       }
       if(chead->colnext->col > c) break ;
       chead = chead->colnext ;
   } 
   if(flag)
   {
       struct sparse *new = (struct sparse *)malloc(sizeof(struct sparse)) ;
       new->row = 0 ;
       new->col = c ;
       new->colnext = chead->colnext ;
       chead->colnext = new ;
       chead = new ;
   }
   flag = 0 ;
    while(head->rownext)
   {
       if(head->rownext->row == r){
           flag = 0 ;
           head = head->rownext ;
           break ;
       }
       if(head->rownext->row > r) break ;
       head = head->rownext ;
   } 
   if(flag)
   {
       struct sparse *New = (struct sparse *)malloc(sizeof(struct sparse)) ;
       New->row = r ;
       New->col = 0 ;
       New->rownext = head->rownext ;
       head->rownext = New ;
       head = New ;
   }
   flag = 1 ;
   while(chead->colnext)
   {
       if(chead->colnext->col == c){
           printf("Already Exists \n") ;
           return Head ;
       }
       if(chead->colnext->col > c){
         node->colnext = chead->colnext ;
         chead->colnext = node ;
         break ;
         flag = 0 ;
       }
       chead = chead->colnext ;
   }
   if(flag){
    node->colnext = chead->colnext ;
         chead->colnext = node ;   
   }
   flag = 1 ;
   while(head->rownext)
   {
       if(head->rownext->row > r){
         node->rownext = head->rownext ;
         head->rownext = node ; 
         break ;
         flag = 0 ; 
       }
       head = head->rownext ;
   }
   if(flag){
       node->rownext = head->rownext ;
         head->rownext = node ;  
   }
   return Head ;
}
int main()
{
    return 0;
}
int main()
{
	return 0;
}
