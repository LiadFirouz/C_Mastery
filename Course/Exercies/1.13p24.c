#include <stdio.h>

#define MAX 100
#define IN 1
#define OUT 0

int main()
{
    int c;
    int wordSize = 0;
    int state = OUT;
    int array[MAX] = {0};

    // שלב 1: איסוף נתונים (מכונת מצבים) - זהה לפתרון הקודם
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            if (state == IN)
            {
                state = OUT;
                if (wordSize > 0 && wordSize < MAX)
                {
                    array[wordSize]++;
                }
                wordSize = 0;
            }
        }
        else
        {
            if (state == OUT)
            {
                state = IN;
            }
            wordSize++;
        }
    }

    if (state == IN && wordSize > 0 && wordSize < MAX)
    {
        array[wordSize]++;
    }

    // שלב 2: הכנה להדפסה אנכית
    int maxHeight = 0;
    int maxWidth = 0;

    // מציאת העמודה הגבוהה ביותר והמילה הארוכה ביותר
    for (int i = 1; i < MAX; i++)
    {
        if (array[i] > maxHeight)
        {
            maxHeight = array[i]; // גובה ציר ה-Y
        }
        if (array[i] > 0)
        {
            maxWidth = i; // גבול ציר ה-X כדי למנוע הדפסת סתם רווחים
        }
    }

    printf("\nVertical Word Length Histogram:\n");
    printf("-------------------------------\n");

    // שלב 3: הדפסה מלמעלה למטה
    // הלולאה החיצונית רצה מהשורה הגבוהה ביותר ועד לבסיס (0)
    for (int row = maxHeight; row > 0; row--)
    {
        // הלולאה הפנימית רצה על פני כל העמודות הרלוונטיות
        for (int i = 1; i <= maxWidth; i++)
        {
            if (array[i] > 0)
            { // מתייחסים רק לעמודות שיש בהן נתונים
                // האם העמודה הנוכחית הגיעה לגובה של השורה שאנחנו מדפיסים כרגע?
                if (array[i] >= row)
                {
                    printf(" # "); // מדפיסים לבנה של הגרף
                }
                else
                {
                    printf("   "); // מדפיסים אוויר (רווחים) כדי לשמור על היישור
                }
            }
        }
        printf("\n"); // יורדים קומה למטה
    }

    // שלב 4: הדפסת ציר ה-X (המספרים בתחתית הגרף)
    for (int i = 1; i <= maxWidth; i++)
    {
        if (array[i] > 0)
        {
            printf("%2d ", i);
        }
    }
    printf("\n");

    return 0;
}