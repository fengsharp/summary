#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBOL_COMMENT '#'
#define SYMBOL_KEYVALUE '='

typedef void (*FuncCommnet)(const char *comment);
typedef void (*FuncGroup)(const char *group);
typedef void (*FuncItem)(const char *itemKey, const char *itemValue);
void ini_parse(const char *str, FuncCommnet funcComment, FuncGroup funcGroup, FuncItem funcItem);

void ini_on_comment(const char *comment);
void ini_on_group(const char *group);
void ini_on_item(const char *itemKey, const char *itemValue);

int main()
{
    const char *str = "[lixianjing]\nname=lixianjing\ngender=male\n[zhangshan]\nname=zhangshan\ngender=male\nage=100\n";

    ini_parse(str, ini_on_comment, ini_on_group, ini_on_item);

    return 0;
}

void ini_parse(const char *str, FuncCommnet funcComment, FuncGroup funcGroup, FuncItem funcItem)
{
    typedef enum _State
    {
        BLANK,
        COMMENT,
        GROUP,
        ITEM_KEY,
        ITEM_VALUE,
    } State;

    typedef struct _StateContext
    {
        State state;

        char *cursor;
        char *comment;
        char *group;
        char *item_key;
        char *item_value;
    } StateContext;

    char *strCopoy = strdup(str);
    StateContext context = {.state = BLANK, .cursor = strCopoy, .comment = NULL, .group = NULL, .item_key = NULL, .item_value = NULL};
    while (*context.cursor != '\0')
    {
        switch (context.state)
        {
        case BLANK:
        {
            if (*context.cursor == SYMBOL_COMMENT)
            {
                context.comment = context.cursor + 1;
                context.state = COMMENT;
            }
            else if (*context.cursor == '[')
            {
                context.group = context.cursor + 1;
                context.state = GROUP;
            }
            else if (*context.cursor != ' ' && *context.cursor != '\n')
            {
                context.item_key = context.cursor;
                context.state = ITEM_KEY;
            }
        }
        break;
        case COMMENT:
        {
            if (*context.cursor == '\n')
            {
                *context.cursor = '\0';
                funcComment(context.comment);
                context.state = BLANK;
            }
        }
        break;
        case GROUP:
        {
            if (*context.cursor == ']')
            {
                *context.cursor = '\0';
                funcGroup(context.group);
                context.state = BLANK;
            }
        }
        break;
        case ITEM_KEY:
        {
            if (*context.cursor == SYMBOL_KEYVALUE)
            {
                *context.cursor = '\0';
                context.state = ITEM_VALUE;
                context.item_value = context.cursor + 1;
            }
        }
        break;
        case ITEM_VALUE:
        {
            if (*context.cursor == '\n')
            {
                *context.cursor = '\0';
                context.state = BLANK;
                funcItem(context.item_key, context.item_value);
            }
        }
        break;
        default:
            break;
        }

        ++context.cursor;
    }

    free(strCopoy);
}

void ini_on_comment(const char *comment)
{
    printf("comment info: %s\n", comment);
}

void ini_on_group(const char *group)
{
    printf("group name: %s\n", group);
}

void ini_on_item(const char *itemKey, const char *itemValue)
{
    printf("\tkey-%s, value-%s\n", itemKey, itemValue);
}