#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_LEN 256
int lengthOfLongestSubstring(char *s)
{
    int ret = 0; // abcabcbb

    char *pStart = s;
    char *pCursor = s;
    int mapArr[CHAR_LEN];
    memset(mapArr, -1, sizeof(mapArr));

    while (*pCursor != '\0')
    {
        int index = (int)(*pCursor);
        if (mapArr[index] != -1)
        {
            int len = (pCursor - pStart);
            ret = (ret < len) ? len : ret;
            char* pNewStart = (s + mapArr[index] + 1);
            pStart = (pStart > pNewStart) ? pStart : pNewStart;
        }

        mapArr[index] = (pCursor - s);
        ++pCursor;
    }

    int len = (pCursor - pStart);
    ret = (ret < len) ? len : ret;
    return ret;
}

int main()
{
    int ret = 0;

    char *str1 = "abcabcbb"; // 3
    ret = lengthOfLongestSubstring(str1);
    printf("%d\n", ret);

    char *str2 = "bbbbb"; // 1
    ret = lengthOfLongestSubstring(str2);
    printf("%d\n", ret);

    char *str3 = "pwwkew"; // 3
    ret = lengthOfLongestSubstring(str3);
    printf("%d\n", ret);

    char *str4 = ""; // 0
    ret = lengthOfLongestSubstring(str4);
    printf("%d\n", ret);

    char *str5 = "dvdf"; // 3
    ret = lengthOfLongestSubstring(str5);
    printf("%d\n", ret);

    char *str6 = "abba"; // 2
    ret = lengthOfLongestSubstring(str6);
    printf("%d\n", ret);

    return 0;
}