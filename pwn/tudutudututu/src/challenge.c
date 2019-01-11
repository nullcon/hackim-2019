#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TODOS 16

struct todo {
    char *topic;
    char *desc;
};

struct todo *todos[MAX_TODOS];
unsigned int num_todos = 0;

void readstr(char* buf)
{
    if(fgets(buf, 512, stdin) == NULL)
        puts("Err read string");

    if (buf[strlen(buf)-1] == '\n')
        buf[strlen(buf)-1] = '\0';
}

int readint()
{
    char buf[512];
    if(fgets(buf, 512, stdin) == NULL)
        return -1;
    return atoi(buf);
}

void print_todos(){
    if (num_todos == 0)
        puts("No todos");
    for (int i = 0; i < num_todos; i++){
        printf("%s - %s\n", todos[i]->topic, todos[i]->desc);
    }
}

struct todo *find_todo(char *topic){
    for (int i = 0; i < num_todos; i++){
        if (!strcmp(topic, todos[i]->topic)){
            return todos[i];
        }
    }
    return NULL;
}

void create_todo(char *topic){
    if (num_todos == MAX_TODOS){
        puts("Max todo limit reached!");
        return;
    }

    struct todo *todo = (struct todo *)malloc(sizeof(struct todo));
    if (todo == NULL){
        puts("Err todo allocation");
        exit(-1);
    };

    todo->topic = strdup(topic);
    if (todo->topic == NULL){
        puts("Err topic duplication");
        exit(-1);
    }

    todos[num_todos++] = todo;
}

void delete_todo(struct todo *todo){
    free(todo->topic);

    if (todo->desc != NULL){
        free(todo->desc);
    }

    free(todo);

    for (int i = 0; i < num_todos; i++){
        if (todos[i] == todo){
            todos[i] = todos[num_todos - 1];
            num_todos--;
            break;
        }
    }
}

void set_desc(struct todo *todo){
    char input[4];
    size_t length;

    if (todo->desc != NULL){
        free(todo->desc);
    }

    printf("Desc length: ");
    if (fgets(input, 4, stdin) == NULL){
        puts("Err desc length read");
        return;
    };

    length = strtoul(input, NULL, 10);
    if (length > 255){
        puts("Too big!");
        return;
    }

    todo->desc = (char *)malloc(length+1);
    if (todo->desc == NULL){
        puts("Err desc allocation");
        exit(-1);
    }

    printf("Desc: ");
    if (fgets(todo->desc, length+1, stdin) == NULL){
        puts("Err desc read");
        return;
    }

    puts("Description successfully set!");
}

void menu(){
    puts("Menu:");
    puts("(1) Create a new todo");
    puts("(2) Set description for a todo");
    puts("(3) Delete an existing todo");
    puts("(4) Print todos");
    puts("(5) Exit");
}

int process_cmd(uint cmd){
    struct todo *todo;
    char *topic;
    char buf[512];

    switch(cmd)
    {
        case 1:
            printf("topic: ");

            readstr(buf);
            
            topic = buf;
            create_todo(topic);
            printf("Created todo \"%s\"\n", topic);    
            break;
        case 2:
            printf("topic: ");

            readstr(buf);
            
            topic = buf;
            todo = find_todo(topic);
            if (todo == NULL){
                puts("Unknown todo");
                return 0;
            }

            set_desc(todo);
            break;
        case 3:
            printf("topic: ");

            readstr(buf);
            
            topic = buf;
            todo = find_todo(topic);
            if (todo == NULL){
                puts("Unknown todo");
                return 0;
            }

            delete_todo(todo);
            printf("Deleted todo \"%s\"\n", topic);
            break;
        case 4:
            print_todos();
            break;
        case 5:
            return 1;
        default:
            puts("Invalid option");
            menu();

    }

    
    return 0;
}

void command_loop(){
    uint choice;
    menu();
    while(1){
        printf("\n> ");

        choice = readint();
        if (choice == -1)
            break;
        
        if (process_cmd(choice)){
            return;
        }
    }
}

int main(int argc, char **argv){
    setbuf(stdout, NULL);
    command_loop();
}

