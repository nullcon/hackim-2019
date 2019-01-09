#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SIZE 20

int main()
{
        setbuf(stdin, NULL);
        setbuf(stdout, NULL);
        int coins[SIZE]; 
        int8_t num=0;

        char *box, choice[2];
        printf("Create a tressure box?\r\n");
        scanf("%2s", choice);
        if (choice[0] != 'y' && choice[0] != 'Y')
        {
                printf("Bye!\r\n");
                return 0;
        }

        printf("name: ");
        box = (char *)malloc(100*(sizeof(char)));
        strcpy(box, "Tressure Box: ");
        scanf("%50s", box+14);
        strcat(box, " created!\r\n");

        printf("How many coins do you have?\r\n");
        scanf("%hhu", &num);
        if (num > SIZE)
        {
                perror("Coins that many are not supported :/\r\n");
                exit(1);
        }

        for (uint8_t i=0; i<(uint8_t)num; i++)
        {
                scanf("%d", &coins[i]);
        }
        printf(box);
        free(box);
        return 0;
}