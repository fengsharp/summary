#include <stdio.h>
#include <stdlib.h>

int count_world(const char *str);

int main()
{
    const char *str = "it is used to count words. is it easy?";
    int num = count_world(str);
    printf("result: %d\n", num);

    return 0;
}


int count_world(const char *str)
{
    typedef enum _WorldStats
    {
        WORLD_STATS_IN,
        WORLD_STATS_OUT,
    } WorldStats;

    typedef struct _StateContext
    {
        int worldNum;
        WorldStats curStatus;
    } StateContext;
    
    const char *pCursor = str;
    StateContext context = { .worldNum = 0, .curStatus = WORLD_STATS_OUT };

    while (*pCursor != '\0')
    {
        switch (context.curStatus)
        {
            case WORLD_STATS_IN:
            {
                if (*pCursor == ' ')
                {
                    context.curStatus = WORLD_STATS_OUT;
                }
            }
                break;
            case WORLD_STATS_OUT:
            {
                if (*pCursor != ' ')
                {
                    context.curStatus = WORLD_STATS_IN;
                    ++context.worldNum;
                }
            }
                break;
            default:
                break;
        }

        ++pCursor;
    }

    return context.worldNum;
}