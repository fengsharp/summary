#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*TokenCallbak)(size_t index, const char *token);
void parse_token(const char *str, const char splite, TokenCallbak funcToken);
void on_token(size_t index, const char *token);

int main()
{
    const char *str = "/backup/tools/jdk1.5.0_18/bin/:/usr/lib/qt-3.3/bin:/usr/kerberos/bin:/backup/tools/jdk1.5.0_18/bin/:/usr/lib/ccache:/usr/local/bin:/usr/bin:/bin:/home/lixianjing/bin";
    parse_token(str, ':', on_token);

    return 0;
}

void parse_token(const char *str, const char splite, TokenCallbak funcToken)
{
    char *strCopy = strdup(str);
    typedef enum _State
    {
        OUT,
        IN,
    } State;

    typedef struct _StateContext
    {
        State curState;
        int cnt;
        const char *tokenStart;
        char *cursor;
    } StateContext;

    StateContext context = { .curState = OUT, .cnt = 0, .tokenStart = NULL, .cursor = strCopy };
    while (*context.cursor != '\0')
    {
        switch (context.curState)
        {
            case OUT:
            {
                if (*context.cursor != ' ' && *context.cursor != splite)
                {
                    ++context.cnt;
                    context.tokenStart = context.cursor;
                    context.curState = IN;
                }
            }
            break;
            case IN:
            {
                if (*context.cursor == ' ' || *context.cursor == splite)
                {
                    *context.cursor = '\0';
                    funcToken(context.cnt, context.tokenStart);
                    context.tokenStart = NULL;
                    context.curState = OUT;
                }
            }
            break;
            default:
            break;
        }
        ++context.cursor;
    }

    if (context.curState == IN)
    {
        funcToken(context.cnt, context.tokenStart);
    }

    free(strCopy);    
}

void on_token(size_t index, const char *token)
{
    printf("%zu %s\n", index, token);
}