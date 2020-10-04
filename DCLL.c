#include<stdio.h>
#include<stdlib.h>

struct node
{
    struct node *prev;
    int info;
    struct node *next;
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
        printf("\n\n********** CIRCULAR DOUBLY LINKED LIST **********\n");
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
    p = last->next;
    do
    {
        printf("%d ",p->info);
        p = p->next;
    }while(p != last->next);
    printf("\n");
}

struct node *addtoempty(struct node *last, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;

    last = temp;
    last->next = last;
    last->prev = last;
    return last;
}

struct node *addatbeg(struct node *last, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    if(last == NULL)
    {
        last = temp;
        last->next = last;
        last->prev = last;
        return last;
    }
    temp->next = last->next;
    temp->prev = last;
    last->next = temp;
    temp->next->prev = temp;
    return last;
}

struct node *addatend(struct node *last, int data)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;

    if(last == NULL)
    {
        temp = last;
        last->next = last;
        last->prev = last;
        return last;
    }
    temp->next = last->next;
    temp->prev = last;
    last->next = temp;
    temp->next->prev = temp;
    last = last->next;
    return last;
}

struct node *addafter(struct node *last, int data, int item)
{
    struct node *temp,*p;
    p = last->next;
    do
    {
        if(p->info == item)
        {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->info = data;

            temp->next = p->next;
            temp->prev = p;
            p->next = temp;
            temp->next->prev = temp;

            if(p == last) // inserted after last node
                last = addatend(last,data);
            return last;
        }
        p = p->next;
    } while(p != last->next);
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
    if(last->next == last && last->info == data) // deletion of only node
    {
        temp = last;
        last = NULL;
        free(temp);
        return last;
    }
    if(last->next->info == data) // deletion of first node
    {
        temp = last->next;
        last->next = temp->next;
        last->next->prev = last->next;
        free(temp);
        return last;
    }

    // deletion in between
    p = last->next; // points to first node
    while(p->next != last)
    {
        if(p->next->info == data)
        {
            temp = p->next;
            p->next = temp->next;
            p->next->prev = p;
            free(temp);
            return last;
        }
        p = p->next;
    }
    if(last->info == data) // deletion of last node
    {
        temp = last;
        last = temp->prev;
        last->next = temp->next;
        temp->next->prev = last;

        free(temp);
        return last;
    }
    printf("Element %d not found\n",data);
    return last;
}
