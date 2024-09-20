/* Coding Assignment 1 */
/* Name: Nadia Thonu */
/* id: 1001983393 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int number;
    struct node *next_ptr;
}
NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->number = Number;
    newNode->next_ptr = NULL;

    if (*LinkedListHead == NULL)
    {
        *LinkedListHead = newNode;
    }
    else
    {
        NODE *temp = *LinkedListHead;

        while (temp->next_ptr != NULL)
        {
            temp = temp->next_ptr;
        }

        temp->next_ptr = newNode;
    }
}

void ReadFileIntoLL(int argc,  char *argv[], NODE **LLH)
{
    FILE *file = fopen(argv[1],"r");

    if(!file)
    {
        printf("Exiting : No such file or directory\n");
        exit(0);
    }
    char buffer [50];
    int cnt=0;
    int sum=0;

    while(file!=NULL && fgets(buffer,20,file))
    {
        int num=atoi(buffer);
        AddNodeToLL(num,LLH);
        cnt++;
        sum+=num;
    }
    fclose(file);
    printf("\n%d records were read for a total sum of %d\n", cnt, sum);
}

void PrintLL(NODE *LLH)
{
    NODE* head =LLH;
    int cnt=0;
    int sum=0;

    while(head!=NULL)
    {
        cnt++;
        sum+=head->number;

        #ifdef PRINT
            printf("\n%p %d ",head,head->number);

            if(head->next_ptr==NULL)
            {
                printf("(nil)\n");
            }
            else
            {
                printf("%p\n",head->next_ptr);
            }
        #endif

        head=head->next_ptr;
    }

    #ifdef PRINT
        printf("\n%d records were read for a total sum of %d\n", cnt, sum);
    #endif
}

void FreeLL(NODE **LLH)
{
    NODE *temp=*LLH;
    int cnt=0;
    int sum=0;

    while((*LLH)!=NULL)
    {
        cnt++;
        sum+=(*LLH)->number;

        #ifdef PRINT
            printf("\nFreeing %p %d ", temp, temp->number);

            if(temp->next_ptr==NULL)
            {
                printf("(nil)\n");
            }
            else
            {
                printf("%p\n",temp->next_ptr);
            }
        #endif // PRINT

        *LLH = (*LLH)->next_ptr;
        free(temp);
        temp=*LLH;
    }

    printf("\n%d nodes were deleted for a total sum of %d\n", cnt, sum);
}


int main(int argc, char * argv[])
{
    if(argc ==1)
    {
        printf("\nFile must be provided on command line...exiting\n");
        exit(0);
    }

    NODE *LLH = NULL;
    clock_t start, end;

    start = clock();
    ReadFileIntoLL(argc, argv, &LLH);
    end = clock();
    printf("\n%ld tics to write the file into the linked list\n", end-start);

    start = clock();
    PrintLL(LLH);
    end = clock();

    #ifdef PRINT
    printf("\n%ld tics to print the linked list\n", end-start);
    #endif

    start = clock();
    FreeLL(&LLH);
    end = clock();
    printf("\n%ld tics to free the linked list\n", end-start);

    return 0;
}
