#include "cstring.h"
namespace sdds {

    // Copies the source character string into the destination
    void strCpy(char *des, const char *src)
    {
        int value = 0;
        for (int i = 0; src[i] != '\0'; i++)
        {
            des[i] = src[i];
            value++;
        }

        des[value] = '\0';
    }

    // Copies the source character string into the destination upto "len"
    // characters. The destination will be null terminated only if the number
    // of the characters copied is less than "len"
    void strnCpy(char *des, const char *src, int len)
    {
        for (int i = 0; i < len; i++)
        {
            des[i] = src[i];
        }
    }

    // Compares two C-strings 
    // returns 0 if they are the same
    // return > 0 if s1 > s2
    // return < 0 if s1 < s2
    int strCmp(const char *s1, const char *s2)
    {
        bool equal = true;
        int num1 = 0;
        int num2 = 0;
        int value1 = 0;
        int value2 = 0;
        for (int i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
        {
            if (s1[i] != s2[i])
            {
                equal = false;
                break;
            }

            num1 += s1[i];
            num2 += s2[i];
            value1++;
            value2++;
        }

        while (s1[value1] != '\0')
        {
            num1 += s1[value1];
            value1++;
        }

        while (s2[value2] != '\0')
        {
            num2 += s2[value2];
            value2++;
        }

        if (equal)
        {
            return 0;
        }
        else if (num1 > num2)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    // returns 0 if they are the same
    // return > 0 if s1 > s2
    // return < 0 if s1 < s2
    int strnCmp(const char *s1, const char *s2, int len)
    {
        int num1 = 0;
        int num2 = 0;
        int value1 = 0;
        int value2 = 0;
        int length = 0;
        bool equal = true;
        for (int i = 0; s1[i] != '\0' && s2[i] != '\0' && i < len; i++)
        {
            if (s1[i] != s2[i])
            {
                equal = false;
                break;
            }

            num1 += s1[i];
            num2 += s2[i];
            value1++;
            value2++;
            length++;
        }

        while (s1[value1] != '\0' && length < len)
        {
            num1 += s1[value1];
            value1++;
        }

        while (s2[value2] != '\0' && length < len)
        {
            num2 += s2[value2];
            value2++;
        }

        if (equal)
        {
            return 0;
        }
        else if (num1 > num2)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    // returns the length of the C-string in characters
    int strLen(const char *s)
    {
        int length = 0;
        for (int i = 0; s[i] != '\0'; i++)
        {
            length++;
        }

        return length;
    }

    // returns the address of first occurrence of "str2" in "str1"
    // returns nullptr if no match is found
    const char *strStr(const char *str1, const char *str2)
    {
        while (*str1 != '\0')
        {
            if ((*str1 == *str2) && strCmp(str1, str2) == 0)
                return str1;
            str1++;
        }

        return nullptr;
    }

    // Concantinates "src" C-string to the end of "des"
    void strCat(char *des, const char *src)
    {
        int value = 0;
        for (int i = 0; des[i] != '\0'; i++)
        {
            value++;
        }

        for (int i = 0; src[i] != '\0'; i++)
        {
            des[value] = src[i];
            value++;
        }

        des[value] = '\0';
    }  
}