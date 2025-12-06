#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STUDENT_FILE "student.txt"
#define CREDENTIAL_FILE "credentials.txt"
struct Student
{
    int roll;
    char name[50];
    int marks;
};
char currentRole[10];
char currentUser[50];

/* Function prototypes added to fix implicit declaration errors */
int loginSystem(void);
void mainMenu(void);
void adminMenu(void);
void userMenu(void);
void staffMenu(void);
void guestMenu(void);
void addStudent(void);
void displayStudents(void);
void searchStudent(void);
void updateStudent(void);
void deleteStudent(void);

/*------------------MAIN------------------*/
int main()
{
    if (loginSystem())
    {
        mainMenu();
    }
    else
    {
        printf("\n Access Denied. Exiting...\n");
    }
    return 0;
}
int loginSystem()
{
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[10];
    printf("===== Login ======\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp)
    {
        printf("Error: credentials.txt not found! \n");
        return 0;
    }
    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3)
    {
        if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0)
        {
            strcpy(currentRole, fileRole);
            strcpy(currentUser, fileUser);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
/*------------ main menu----------------*/
void mainMenu()
{
    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        guestMenu();
}
void adminMenu()
{
    int choice;
    do
    {
        printf("\n======ADMIN MENU=======\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3.Search student\n");
        printf("4. Update student\n");
        printf("5. delete student\n");
        printf("6. logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            updateStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

/* ----------------- Append after your adminMenu() ----------------- */

/* User menu */
void userMenu()
{
    int choice;
    do
    {
        printf("\n======USER MENU=======\n");
        printf("1. Display students\n");
        printf("2. Search student\n");
        printf("3. logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

/* Staff menu */
void staffMenu()
{
    int choice;
    do
    {
        printf("\n======STAFF MENU=======\n");
        printf("1. Display students\n");
        printf("2. Search student\n");
        printf("3. Update student\n");
        printf("4. logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            searchStudent();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

/* Guest menu */
void guestMenu()
{
    int choice;
    do
    {
        printf("\n======GUEST MENU=======\n");
        printf("1. Display students\n");
        printf("2. logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            displayStudents();
            break;
        case 2:
            printf("Logging out...\n");
            return;
        default:
            printf("Invalid choice!\n");
        }
    } while (1);
}

/* Add a student (simple, names without spaces) */
void addStudent()
{
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");
    if (!fp)
    {
        printf("Error: cannot open %s\n", STUDENT_FILE);
        return;
    }
    printf("Enter roll number: ");
    scanf("%d", &s.roll);
    printf("Enter name (no spaces): ");
    scanf("%s", s.name);
    printf("Enter marks: ");
    scanf("%d", &s.marks);

    fprintf(fp, "%d %s %d\n", s.roll, s.name, s.marks);
    fclose(fp);
    printf("Student added successfully.\n");
}

/* Display all students */
void displayStudents()
{
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp)
    {
        printf("No student records found.\n");
        return;
    }
    printf("\n--- Student List ---\n");
    printf("%-8s %-20s %-6s\n", "Roll", "Name", "Marks");
    printf("--------------------------------\n");
    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) == 3)
    {
        printf("%-8d %-20s %-6d\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

/* Search student by roll */
void searchStudent()
{
    int target;
    struct Student s;
    FILE *fp;

    printf("Enter roll number to search: ");
    scanf("%d", &target);

    fp = fopen(STUDENT_FILE, "r");
    if (!fp)
    {
        printf("No student records found.\n");
        return;
    }

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll == target)
        {
            printf("\nStudent found:\n");
            printf("Roll: %d\nName: %s\nMarks: %d\n", s.roll, s.name, s.marks);
            fclose(fp);
            return;
        }
    }
    printf("Student with roll %d not found.\n", target);
    fclose(fp);
}

/* Update student (search by roll and replace name/marks) */
void updateStudent()
{
    int target;
    struct Student s;
    FILE *fp, *temp;
    int found = 0;

    printf("Enter roll number to update: ");
    scanf("%d", &target);

    fp = fopen(STUDENT_FILE, "r");
    if (!fp)
    {
        printf("No student records found.\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Error: cannot create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll == target)
        {
            found = 1;
            printf("Existing record - Roll:%d Name:%s Marks:%d\n", s.roll, s.name, s.marks);
            printf("Enter new name (no spaces): ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%d", &s.marks);
        }
        fprintf(temp, "%d %s %d\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (!found)
    {
        printf("Student with roll %d not found. No update performed.\n", target);
        remove("temp.txt");
        return;
    }

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);
    printf("Student record updated successfully.\n");
}

/* Delete student by roll */
void deleteStudent()
{
    int target;
    struct Student s;
    FILE *fp, *temp;
    int found = 0;

    printf("Enter roll number to delete: ");
    scanf("%d", &target);

    fp = fopen(STUDENT_FILE, "r");
    if (!fp)
    {
        printf("No student records found.\n");
        return;
    }
    temp = fopen("temp.txt", "w");
    if (!temp)
    {
        printf("Error: cannot create temporary file.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d %s %d", &s.roll, s.name, &s.marks) == 3)
    {
        if (s.roll == target)
        {
            found = 1;
            /* skip writing this record to delete it */
            continue;
        }
        fprintf(temp, "%d %s %d\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    if (!found)
    {
        printf("Student with roll %d not found. No deletion performed.\n", target);
        remove("temp.txt");
        return;
    }

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);
    printf("Student record deleted successfully.\n");
}