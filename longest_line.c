#include <stdio.h>
#define MAXLINE 1000   /* maximum input line size */

<<<<<<< HEAD
int get_line(char line[], int maxline);
=======
int getline(char line[], int maxline);
>>>>>>> 8bdb5b7a64647b5afb5506ac69011c5aedc31ea3
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];    /* current input line */
    char longest[MAXLINE]; /* longest line saved here */

    max = 0;
<<<<<<< HEAD
    while ((len = get_line(line, MAXLINE)) > 0)
=======
    while ((len = getline(line, MAXLINE)) > 0)
>>>>>>> 8bdb5b7a64647b5afb5506ac69011c5aedc31ea3
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    
    if (max > 0)  /* there was a line */
        printf("%s", longest);
    
    return 0;
}

/* getline: read a line into s, return length */
<<<<<<< HEAD
int get_line(char s[], int lim)
{
    int c, i;
    
    for(   i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
        
=======
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

>>>>>>> 8bdb5b7a64647b5afb5506ac69011c5aedc31ea3
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    
<<<<<<< HEAD
    s[i] = '\0';
=======
    s[i] = '\0'; // סגירת מחרוזת ב-C חייבת להסתיים באפס!
>>>>>>> 8bdb5b7a64647b5afb5506ac69011c5aedc31ea3
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    
<<<<<<< HEAD
    while((from[i] != '\0')) {
        to[i] = from[i];
        i++;
    }
    to[i]='\0';

=======
    // המשימה שלך:
    // תעתיק תאים מ-from ל-to באמצעות לולאת while
    // עד שתגיע לתו המסיים '\0'.
>>>>>>> 8bdb5b7a64647b5afb5506ac69011c5aedc31ea3
}