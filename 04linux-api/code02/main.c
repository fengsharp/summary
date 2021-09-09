#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main()
{
    int cnt = 0;

    while (1)
    {
        FILE *file = fopen("/tmp/del.txt", "w");
        if (file == NULL)
        {
            // perror("fopen()");
            break;
        }
        ++cnt;
    }
    printf("max cnt: %d\n", cnt);

    sleep(3600);
    
    return 0;
}