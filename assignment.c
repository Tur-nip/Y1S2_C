#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int password();
void add_task();
void finish_task();
void dashboard();
void edit_task();
void change_pass();
void dashboardfilter(char);
void num_task();

struct tasks {
    char priority[10];
    char name[30];
    char time[10];
    char record[75];
};

int main()
{
    int choice;
    while(1){
        printf("\n\n\nJin's Personal Task Management Menu\n");
        printf("1. Add a task\n");
        printf("2. Finish/Delete a task\n");
        printf("3. Task Dashboard\n");
        printf("4. Display number of tasks\n");
        printf("5. Edit a task\n");
        printf("6. Exit the system\n");
        printf("Enter your choice(1-6):");
        scanf("%d%*c",&choice);
        switch(choice){
            case 1:
                add_task();
                break;
            case 2:
                printf("2");
                break;
            case 3:
                dashboard();
                break;
            case 4:
                num_task();
                break;
            case 5:
                edit_task();
                break;
            case 6:
                printf("Exitting Jin's Task Management System....");
                exit(0);
            default:
                printf("Invalid input!!!! Only input 1 - 5 is valid!!!\n");
                printf("Press any key to try again\n");
                break;
        }
    }
    return 0;
}

void add_task(){
    struct tasks t;
    char repeat = 'Y';
    int choice;
    FILE *f = fopen("task.txt","a");
    do {
        printf("\nChoose the priority of the task (1-3): ");
        printf("\n1. Urgent\n");
        printf("2. Daily\n");
        printf("3. Future\n");
        scanf("%d",&choice);
        if (choice == 1){
            strcpy(t.priority,"Urgent");
        }
        else if (choice == 2){
            strcpy(t.priority,"Daily");
        }
        else if (choice == 3){
            strcpy(t.priority,"Future");
        }
        else {
            printf("Invalid input, please only input (1-3)!!");
        }
        printf("\nEnter the task name: ");
        getchar();
        fgets(t.name,sizeof(t.name),stdin);
        strtok(t.name,"\n");
        printf("\nEnter the due date of the task(MM/DD/YY): ");
        scanf("%s",t.time);
        fprintf(f,"%s:%s:%s\n",t.priority,t.name,t.time);
        printf("\nRecord added....\n");
        printf("\nWant to add another record? (Y/N): ");
        scanf(" %c",&repeat);
    }while (repeat == 'Y' || repeat == 'y');
    fclose(f);
}

void finish_task()
{
    char task_name[50], task_time[8], task_priority[10],record[100];
    char search[50],compare[50];
    FILE *f = fopen("task.txt","r+");
    fseek(f,0,SEEK_SET);
    while (!feof(f)){
        fgets(record,100,f);
        printf("%s",record);
    }
    printf("Enter the task to change: ");
    scanf("%s",&search);
    while(fscanf(f,"%s",&compare) != EOF){
        if(compare == search){
            continue;
        }
    }
}

void dashboard()
{
    int choice;
    char sort;
    printf("\n\n\nChoose which records to be displayed in dashboard:\n");
    printf("1. All\n");
    printf("2. Sorted by Priority\n");
    scanf("%d",&choice);
    if (choice == 1){
        sort = 'a';
        dashboardfilter(sort);
    }
    if (choice == 2){
        printf("\n\nDisplay which type of Priority of tasks:\n");
        printf("1. Urgent\n");
        printf("2. Daily\n");
        printf("3. Future\n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                sort = 'u';
                dashboardfilter('u');
                break;
            case 2:
                sort = 'd';
                dashboardfilter(sort);
                break;
            case 3:
                sort = 'f';
                dashboardfilter(sort);
                break;
            default:
                printf("Invalid input!!!! Returning to Main menu!!!");
                break;
        }
    }
}

void dashboardfilter(char selection)
{
    struct tasks t;
    char typeU[10] = "Urgent", typeD[10] = "Daily", typeF[10] = "Future";
    FILE *f = fopen("task.txt","r");
    printf(" \n\n\n                        Jin's Task Dashboard\n");
    printf("==========================================================================\n");
    printf("|   Task Priority    |          Task Name           |       Task Time    |\n");
    printf("==========================================================================\n");
    if (selection == 'a')
    {
        while (fgets(t.record,sizeof(t.record),f) != EOF)
        {
            sscanf(t.record,"%[^:]:%[^:]:%s",t.priority,t.name,t.time);
            printf("|%20s|%30s|%20s|\n",t.priority,t.name,t.time);
            if (feof(f)){
                 break;
             }
        }
    }
    else if (selection == 'u')
    {

        while (fgets(t.record,sizeof t.record,f) != EOF)
        {
            sscanf(t.record,"%[^:]:%[^:]:%s",t.priority,t.name,t.time);
            if (strcmp(t.priority,"Urgent") != 0){
                 continue;
             }
            printf("|%20s|%30s|%20s|\n",t.priority,t.name,t.time);
            if (feof(f)){
                 break;
            }
        }
    }
    else if (selection == 'd')
    {
        while (fgets(t.record,sizeof t.record,f) != EOF)
        {
            sscanf(t.record,"%[^:]:%[^:]:%s",t.priority,t.name,t.time);
            if (strcmp(t.priority,typeD) == 0)
            {
                printf("|%20s|%30s|%20s|\n",t.priority,t.name,t.time);
            }
            if (feof(f)){
                break;
            }
        }
    }
    else if (selection == 'f')
    {
        while (fgets(t.record,sizeof t.record,f) != EOF)
        {
            sscanf(t.record,"%[^:]:%[^:]:%s",t.priority,t.name,t.time);
            if (strcmp(t.priority,typeF) == 0)
            {
                printf("|%20s|%30s|%20s|\n",t.priority,t.name,t.time);
            }
            if (feof(f)){
                break;
            }
        }
    }
    printf("==========================================================================\n");
    printf("*ignore last line, duplicated record from feof()\n\n\n");
    fclose(f);
}

void edit_task()
{
    struct tasks t;
    int cnt = 1;
    FILE *f = fopen("task.txt","r");
    FILE *w = fopen("mytemp.txt","w");
    printf("Please choose the task to edit: \n");
    while (!feof(f))
        {
            fgets(t.record,sizeof t.record,f);
            sscanf(t.record,"%[^:]:%[^:]:%s",t.priority,t.name,t.time);
            printf("%d.%s\n",cnt,t.name);
            cnt++;
            }
    printf("ignore last line(duplicated)\n");
    printf("Choice: \n");
}

void num_task()
{
    struct tasks t;
    int num;
    FILE *f = fopen("tasks.txt","r");
    fseek(f,0,SEEK_END);
    num = ftell(f)/sizeof(t);
    printf("\nTotal amount of tasks: %d",num);
    fclose(f);
}