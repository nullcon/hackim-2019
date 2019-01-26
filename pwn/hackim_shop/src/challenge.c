#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_BOOKS 16

typedef struct BookStruct
{
    size_t index;
    char* name;
    size_t price;
    char copyright[25]; 

} Book;

Book *books[MAX_BOOKS];
unsigned int num_books = 0;
char cp_stmt[25] = "Copyright NullCon Shop";

size_t readint()
{
    char input[20];

    if (fgets(input, 20, stdin) == NULL){
        puts("Err read int");
        exit(-1);
    };

    return strtoul(input, NULL, 10);
}

void menu()
{
    puts("NullCon Shop");
    puts("(1) Add book to cart");
    puts("(2) Remove from cart");
    puts("(3) View cart");
    puts("(4) Check out");
    printf("> ");
}

void add_book()
{
    if (num_books == MAX_BOOKS){
        puts("Cart limit reached!");
        return;
    }

    Book* bk = NULL;
    bk = (Book*) malloc(sizeof(Book));
    char input[4];
    size_t length;
    size_t price;

    printf("Book name length: ");
    
    length = readint();
    if (length > 255){
        puts("Too big!");
        return;
    }

    printf("Book name: ");
    bk->name = (char*) malloc(sizeof(char)*length);
    read(0, bk->name, length);
    if(bk->name[strlen(bk->name)-1]=='\n')
        bk->name[strlen(bk->name)-1] = '\0';
    printf("Book price: ");
    bk->price = readint();

    int i;
    for(i=0; books[i] != NULL; i++);
    books[i] = bk;
    books[i]->index = i;
    num_books++;
    strcpy(books[i]->copyright, cp_stmt);
}

void remove_book()
{
    printf("Book index: ");
    size_t idx = readint();
    if(idx>=num_books)
    {
        puts("Invalid index");
        return;
    }
    free(books[idx]->name);
    free(books[idx]);
    //books[idx]=NULL;
    num_books--;
}

void view_books()
{
    puts("{");
    puts("\t\"Books\" : [");
    for(int i=0; i<MAX_BOOKS; i++)
    {
        if(books[i]==NULL)
            continue;
        size_t idx = books[i]->index;
        puts("\t\t{");
        printf("\t\t\t\"index\": %ld,\n", idx);
        printf("\t\t\t\"name\": \"%s\",\n", books[i]->name);
        printf("\t\t\t\"price\": %ld,\n", books[i]->price);
        printf("\t\t\t\"rights\": \"");
        printf(books[i]->copyright);
        printf("\"\n");
        if (books[i+1] == NULL)
            puts("\t\t}");
        else
            puts("\t\t},");
    }
    puts("\t]");
    puts("}");
}

char print_buf[150] = "";

int main()
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);

    for(;;)
    {
        menu();
        char choice[2];
        if(read(0, choice, 2) == 0)
        {
            perror("Err read option\r\n");
        }
        else
        {
            int ch = atol(choice);
            switch(ch)
            {
                case 1:
                    add_book();
                    break;
                case 2:
                    remove_book();
                    break;
                case 3:
                    view_books();
                    break;
                default:
                    puts("Invalid option");
            }    
        }
    }

}

