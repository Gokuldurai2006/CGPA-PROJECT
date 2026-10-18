
#include <stdio.h>
#include <string.h>

#define MAX_GRADES 20
#define MAX_GRADE_LENGTH 10

char gradeNames[MAX_GRADES][MAX_GRADE_LENGTH];
float gradePoints[MAX_GRADES];
int numberOfGrades = 0;

// Configure the grading system
void configureGrades(void)
{
    printf("\n===== GRADE CONFIGURATION =====\n");

    printf("Enter number of grade categories (1-%d): ",
           MAX_GRADES);

    if (scanf("%d", &numberOfGrades) != 1 ||
        numberOfGrades < 1 ||
        numberOfGrades > MAX_GRADES)
    {
        printf("Invalid number of grade categories!\n");
        numberOfGrades = 0;
        return;
    }

    for (int i = 0; i < numberOfGrades; i++)
    {
        printf("\nEnter grade name %d: ", i + 1);
        scanf("%9s", gradeNames[i]);

        // Prevent duplicate grade names
        for (int j = 0; j < i; j++)
        {
            if (strcmp(gradeNames[i], gradeNames[j]) == 0)
            {
                printf("Duplicate grade! Enter a different grade.\n");
                i--;
                goto next_grade;
            }
        }

        printf("Enter grade point for %s: ", gradeNames[i]);

        if (scanf("%f", &gradePoints[i]) != 1 ||
            gradePoints[i] < 0 || gradePoints[i] > 10)
        {
            printf("Invalid grade point! Use a value from 0 to 10.\n");
            numberOfGrades = 0;
            return;
        }

        next_grade:
        ;
    }

    printf("\nGrade specifications saved successfully!\n");
}

// Display configured grades
void displayGrades(void)
{
    if (numberOfGrades == 0)
    {
        printf("\nNo grade specifications configured yet.\n");
        return;
    }

    printf("\n===== YOUR GRADE TABLE =====\n");
    printf("%-15s %-15s\n", "Letter Grade", "Grade Point");

    for (int i = 0; i < numberOfGrades; i++)
    {
        printf("%-15s %-15.2f\n",
               gradeNames[i], gradePoints[i]);
    }
}

int main(void)
{
    configureGrades();
    displayGrades();

    return 0;
}
