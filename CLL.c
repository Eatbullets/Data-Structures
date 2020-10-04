#include<stdio.h>
#include<stdlib.h>

struct node
{
    int info;
    struct node *link;
};

struct node *create_list(struct node *last);
void display(struct node *last);
struct node *addtoempty(struct node *last, int data);
struct node *addatbeg(struct node *last, int data);
struct node *addatend(struct node *last, int data);
struct node *addafter(struct node *last, int data, int item);
struct node *del(struct node *last, int data);

int main()
{
    int choice, data, item;
    struct node *last = NULL;

    while(1)
    {
        printf("\n\n********** CIRCULAR SINGLY LINKED LIST **********\n");
        printf("1.Create List\n");
        printf("2. Display\n");
        printf("3. Add to empty list\n");
        printf("4. Add to beginning\n");
        printf("5. Add to end\n");
        printf("6. Add after\n");
        printf("7. Delete\n");
        printf("8. Quit\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: last = create_list(last); break;
            case 2: display(last); break;
            case 3: printf("Enter element to insert : "); scanf("%d",&data); last = addtoempty(last,data); break;
            case 4: printf("Enter element to insert : "); scanf("%d",&data); last = addatbeg(last,data); break;
            case 5: printf("Enter element to insert : "); scanf("%d",&data); last = addatend(last,data); break;
            case 6: printf("Enter element to insert : "); scanf("%d",&data); printf("Enter element after which to insert : "); scanf("%d",&item); last = addafter(last,data,item); break;
            case 7: printf("Enter element to delete : "); scanf("%d",&data); last = del(last,data); break;
            case 8: exit(1);
            default: printf("Wrong choice!\n");
        }
    }
}

struct node *create_list(struct node *last)
{
    int i,n,data;
    printf("Enter no. of nodes : ");
    scanf("%d",&n);
    last = NULL;
    if(n == 0)
        return last;
    printf("Enter element to be inserted : ");
    scanf("%d",&data);
    last = addtoempty(last,data);
    for(i=2 ; i<=n ; i++)
    {
        printf("Enter element to be inserted : ");
        scanf("%d",&data);
        last = addatend(last,data);
    }
    return last;
}

void display(struct node *last)
{
    struct node *p;
    if(last == NULL)
    {
        printf("Empty list!\n");
        return;
    }
    p = last->link;
    do
    {
        printf("%d ",p->info);
        p = p->link;
    } while(p != last->link);
    printf("\n");
}

struct node *addtoempty(struct node *last, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;

    last = temp;
    last->link = last;
    return last;
}

struct node *addatbeg(struct node *last, int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;

    temp->link = last->link;
    last->link = temp;
    return last;
}

struct node *addatend(struct node *last, int data)
{
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;

    temp->link = last->link; // ORDER IMP
    last->link = temp;
    last = temp;
    return last;
}

struct node *addafter(struct node *last, int data, int item)
{
    struct node *temp,*p;
    p = last->link;
    do
    {
        if(p->info == item)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->info = data;

            temp->link = p->link;
            p->link = temp;

            if(p == last) // inserted after last node
                last = temp;

            return last;
        }
        p = p->link;
    } while(p != last->link);
    printf("Element %d not present in the list\n",item);
    return last;
}

struct node *del(struct node *last, int data)
{
    struct node *temp,*p;
    if(last == NULL)
    {
        printf("List is empty\n");
        return last;
    }
    if(last->link == last && last->info == data) // deletion of only node
    {
        temp = last;
        last = NULL;
        free(temp);
        return last;
    }
    if(last->link->info == data) // deletion of first node
    {
        temp = last->link;
        last->link = temp->link;
        free(temp);
        return last;
    }

    // deletion in between
    p = last->link; // points to first node
    while(p->link != last)
    {
        if(p->link->info == data)
        {
            temp = p->link;
            p->link = temp->link;
            free(temp);
            return last;
        }
        p = p->link;
    }
    if(last->info == data) // deletion of last node, READ AGAIN
    {
        temp = last;
        p->link = last->link;
        last = p;
        free(temp);
        return last;
    }
    printf("Element %d not found\n",data);
    return last;
}
