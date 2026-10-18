
#include <stdio.h>
#include <string.h>

#define MAX_GRADES 20
#define MAX_GRADE_LENGTH 10

char gradeNames[MAX_GRADES][MAX_GRADE_LENGTH];
float gradePoints[MAX_GRADES];
int numberOfGrades = 0;

// STEP 1: Configure grade specifications
void configureGrades(void)
{
    int count;
    char name[MAX_GRADE_LENGTH];
    float point;

    printf("\n===== GRADE CONFIGURATION =====\n");
    printf("Enter number of grade categories (1-20): ");

    if (scanf("%d", &count) != 1 || count < 1 ||
        count > MAX_GRADES)
    {
        printf("Invalid number of categories!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\nEnter grade name %d: ", i + 1);
        scanf("%9s", name);

        int duplicate = 0;

        for (int j = 0; j < i; j++)
        {
            if (strcmp(name, gradeNames[j]) == 0)
                duplicate = 1;
        }

        if (duplicate)
        {
            printf("Duplicate grade! Enter this category again.\n");
            i--;
            continue;
        }

        printf("Enter grade point for %s (0-10): ", name);

        if (scanf("%f", &point) != 1 ||
            point < 0 || point > 10)
        {
            printf("Invalid point. Restart grade configuration.\n");
            numberOfGrades = 0;
            return;
        }

        strcpy(gradeNames[i], name);
        gradePoints[i] = point;
    }

    numberOfGrades = count;
    printf("\nGrade specifications saved successfully!\n");
}

// Find the grade point entered by the user
float findGradePoint(char grade[])
{
    for (int i = 0; i < numberOfGrades; i++)
    {
        if (strcmp(grade, gradeNames[i]) == 0)
            return gradePoints[i];
    }

    return -1.0;
}

// Display configured grades
void displayGrades(void)
{
    if (numberOfGrades == 0)
    {
        printf("\nConfigure grades first.\n");
        return;
    }

    printf("\n===== GRADE TABLE =====\n");

    for (int i = 0; i < numberOfGrades; i++)
        printf("%s = %.2f\n", gradeNames[i], gradePoints[i]);
}

// STEP 2: Calculate GPA for one semester
void calculateGPA(void)
{
    int semester, n;
    char grade[MAX_GRADE_LENGTH];
    float credit, point;
    float totalCredits = 0, totalPoints = 0;

    if (numberOfGrades == 0)
    {
        printf("\nPlease configure grades first!\n");
        return;
    }

    printf("\nEnter semester number (1-8): ");
    if (scanf("%d", &semester) != 1 ||
        semester < 1 || semester > 8)
    {
        printf("Invalid semester number!\n");
        return;
    }

    printf("Enter number of subjects: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of subjects!\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nSubject %d\n", i + 1);

        printf("Enter subject credit: ");
        if (scanf("%f", &credit) != 1 || credit <= 0)
        {
            printf("Invalid credit!\n");
            return;
        }

        printf("Enter grade: ");
        scanf("%9s", grade);

        point = findGradePoint(grade);

        if (point < 0)
        {
            printf("Grade not found in your grade table!\n");
            return;
        }

        totalCredits += credit;
        totalPoints += credit * point;
    }

    printf("\nSemester %d GPA = %.2f\n",
           semester, totalPoints / totalCredits);
    printf("Total credits = %.2f\n", totalCredits);
}

// STEP 3: Calculate overall CGPA from semester GPAs
void calculateCGPA(void)
{
    int semesters;
    float gpa, credits;
    float totalCredits = 0, totalPoints = 0;

    printf("\nEnter number of completed semesters: ");

    if (scanf("%d", &semesters) != 1 ||
        semesters <= 0 || semesters > 8)
    {
        printf("Enter a number from 1 to 8!\n");
        return;
    }

    for (int i = 0; i < semesters; i++)
    {
        printf("\nSemester %d GPA: ", i + 1);
        if (scanf("%f", &gpa) != 1 ||
            gpa < 0 || gpa > 10)
        {
            printf("Invalid GPA!\n");
            return;
        }

        printf("Semester %d total credits: ", i + 1);
        if (scanf("%f", &credits) != 1 || credits <= 0)
        {
            printf("Invalid credits!\n");
            return;
        }

        totalPoints += gpa * credits;
        totalCredits += credits;
    }

    printf("\nOverall CGPA = %.2f\n",
           totalPoints / totalCredits);
    printf("Total credits = %.2f\n", totalCredits);
}

// MAIN MENU
int main(void)
{
    int choice;

    do
    {
        printf("\n================================\n");
        printf("   GPA AND CGPA CALCULATOR\n");
        printf("================================\n");
        printf("1. Configure Grade Specifications\n");
        printf("2. Calculate GPA\n");
        printf("3. Calculate CGPA\n");
        printf("4. Display Grade Table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");
            return 1;
        }

        switch (choice)
        {
            case 1:
                configureGrades();
                break;

            case 2:
                calculateGPA();
                break;

            case 3:
                calculateCGPA();
                break;

            case 4:
                displayGrades();
                break;

            case 5:
                printf("Thank you for using the calculator!\n");
                break;

            default:
                printf("Invalid choice! Select 1-5.\n");
        }

    } while (choice != 5);

    return 0;
}
