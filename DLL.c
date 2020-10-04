#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *prev;
    int info;
    struct node *next;
};

struct node *create_list(struct node *start);
void display(struct node *start);
void count(struct node *start);
void search(struct node *start, int data);
struct node *add_to_empty(struct node *start, int data);
struct node *add_at_beg(struct node *start, int data);
struct node *add_at_end(struct node *start, int data);
struct node *addafter(struct node *start, int data, int item); // undone
struct node *addbefore(struct node *start, int data, int item); // undone
struct node *addatpos(struct node *start, int data, int pos); // undone
struct node *del(struct node *start, int data);
struct node *rev(struct node *start);

int main()
{
    struct node *start = NULL;
    int choice, data, pos, item;
    while(1)
    {
        printf("\n\n********** DOUBLE LINKED LIST MENU **********\n\n");
        printf("1.Create List\n");
        printf("2.Display\n");
        printf("3.Count\n");
        printf("4.Search\n");
        printf("5.Add to empty list\n");
        printf("6.Add at beginning\n");
        printf("7.Add at end\n");
        printf("8.Add after node\n");
        printf("9.Add before node\n");
        printf("10.Add at position\n");
        printf("11.Delete\n");
        printf("12.Reverse\n");
        printf("13.Quit\n");
        printf("Enter Choice : \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: start = create_list(start); break;
            case 2: display(start); break;
            case 3: count(start); break;
            case 4: printf("Enter element to search : "); scanf("%d",&data); search(start,data); break;
            case 5: printf("Enter element to insert : "); scanf("%d",&data); start = add_to_empty(start,data); break;
            case 6: printf("Enter element to insert : "); scanf("%d",&data); start = add_at_beg(start,data); break;
            case 7: printf("Enter element to insert : "); scanf("%d",&data); start = add_at_end(start,data); break;
            case 8: printf("Enter element to insert : "); scanf("%d",&data); printf("Enter element after which to insert : "); scanf("%d",&item); start = addafter(start,data,item); break;
            case 9: printf("Enter element to insert : "); scanf("%d",&data); printf("Enter element before which to insert : "); scanf("%d",&item); start = addbefore(start,data,item); break;
            case 10: printf("Enter element to insert : "); scanf("%d",&data); printf("Enter position at which to insert : "); scanf("%d",&pos); start = addatpos(start,data,pos); break;
            case 11: printf("Enter element to delete : "); scanf("%d",&data); start = del(start,data); break;
            case 12: start = rev(start); break;
            case 13: exit(1);
            default:printf("Wrong choice!");
        }
    }
}

struct node *create_list(struct node *start)
{
    int n,data;
    printf("Enter no. of nodes : ");
    scanf("%d",&n);
    start=NULL;
    if(n==0)
        return start;
    printf("Enter the element to be inserted : ");
    scanf("%d",&data);
    start = add_to_empty(start,data);
    for(int i=2 ; i<=n ; i++)
    {
        printf("Enter the element to be inserted : ");
        scanf("%d",&data);
        start = add_at_end(start,data);
    }
    return start;
}

void display(struct node *start)
{
    struct node *p;
    if(start==NULL)
    {
        printf("List is empty!\n");
        return;
    }
    p = start;
    while(p!=NULL)
    {
        printf("%d ",p->info);
        p = p->next;
    }
    printf("\n");
}

void count(struct node *start)
{
    struct node *p=start;
    int cnt = 0;
    while(p != NULL)
    {
        p = p->next;
        cnt++;
    }
    printf("No. of elements are : %d \n\n",cnt);
}

void search(struct node *start, int item)
{
    struct node *p = start;
    int pos=1;
    while(p != NULL)
    {
        if(p->info == item)
        {
            printf("Item %d found at position %d\n",item,pos);
            return;
        }
        p = p->next;
        pos++;
    }
    printf("Item %d not found in list! \n\n",item);
}

struct node *add_to_empty(struct node *start, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->next = NULL;
    temp->prev = NULL;
    start = temp;
    return start;
}

struct node *add_at_beg(struct node *start, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->prev = NULL;
    temp->next = start;
    start->prev = temp;
    start = temp;
    return start;
}

struct node *add_at_end(struct node *start, int data)
{
    struct node *temp,*p;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    p = start;
    while(p->next != NULL)
        p = p->next;
    p->next = temp;
    temp->next = NULL;
    temp->prev = p;
    return start;
}

struct node *addbefore(struct node *start, int data, int item)
{
    // data is the new value to be inserted
    // item is the value before which the node has to be inserted
}

struct node *addafter(struct node *start, int data, int item)
{
    // data is the new value to be inserted
    // item is the value after which the node has to be inserted

}

struct node *addatpos(struct node *start, int data, int pos)
{

}

struct node *del(struct node *start, int data)
{
    struct node *temp;
    if(start == NULL)
    {
        printf("List is empty!\n");
        return start;
    }

    if(start->next == NULL) // Deletion of only node
    {
        if(start->info == data)
        {
            temp = start;
            start = NULL;
            free(temp);
            return start;
        }
        else
        {
            printf("Element %d not found",data);
            return start;
        }
    }

    if(start->info == data) // Deletion of first node
    {
        temp = start;
        start = start->next;
        start->prev = NULL;
        free(temp);
        return start;
    }

    // Deletion in between
    temp = start; // CHECK as in book, it is temp = start->next
    while(temp->next != NULL)
    {
        if(temp->info == data)
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp);
            return start;
        }
        temp = temp->next;
    }

    // Deletion of last node
    if(temp->info == data)
    {
        temp->prev->next = NULL;
        free(temp);
        return start;
    }
    printf("Element %d not found\n",data);
    return start;
}

struct node *rev(struct node *start) // IMP, understand again!
{
    struct node *p1,*p2;
    p1 = start;
    p2 = start->next;
    p1->next = NULL;
    p1->prev = p2;
    while(p2 != NULL)
    {
        p2->prev = p2->next;
        p2->next = p1;
        p1=p2;
        p2 = p2->prev;
    }
    start = p1;
    printf("List reversed\n");
    return start;
}
