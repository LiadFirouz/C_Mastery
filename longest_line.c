#include <stdio.h>
#define MAXLINE 1000   /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    
    if (max > 0)  /* there was a line */
        printf("%s", longest);
    
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    // המשימה שלך:
    // 1. רוץ בלולאה כל עוד:
    //    - יש מקום במערך (i < lim-1)
    //    - לא הגענו לסוף קובץ (EOF)
    //    - לא הגענו לסוף שורה ('\n')
    // 2. תעתיק את התו למערך s[i]
    
    // ... הקוד שלך כאן ...

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    
    s[i] = '\0'; // סגירת מחרוזת ב-C חייבת להסתיים באפס!
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    
    // המשימה שלך:
    // תעתיק תאים מ-from ל-to באמצעות לולאת while
    // עד שתגיע לתו המסיים '\0'.
}