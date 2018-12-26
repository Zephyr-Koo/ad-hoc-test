#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 10
#define STAFF_FILE "staff.bin"
#pragma warning (disable:4996)

typedef struct
{
    int day, month, year;
}Date;

typedef struct
{
    char staffName[30], staffID[10], dept[15];
    Date datejoined;
    char qualification[35];

}Staff;

int nStaff = 6;

void SaveExistingStaffForFirstTime();
void StaffMenu(), EXIT();
void AddStaffInformation();
void SearchStaffInformationMenu();
void SearchName(), SearchDate();
void DisplayStaffInformation();
void ModifyStaffInformation();
void DeleteStaffInformation();

int main()
{
    SaveExistingStaffForFirstTime();
    StaffMenu();

    system("pause");
    return 0;
}

void SaveExistingStaffForFirstTime()
{
    Staff staff[MAX_SIZE] =
    {
        { "Cheah Kar Yan","K2055","Doctor",10,10,2008,"Doctor of Medicine (USCI)" },
        { "Cheah Ker Xin","M2500","Doctor",10,03,2010,"MBBS MD (UK)" },
        { "Chia Sook Jing","K5033","Nurse",10,10,2008,"Bachelor of Nursing (UTAR)" },
        { "Soh Guo Chuen","L5300","Nurse",05,03,2010,"Bachelor In Nursing (UCSI)" },
        { "Wee Chu Lim","K0345","Doctor",25,01,2009,"Bachelor Doctor Surgery (SEGI)" },
        { "Soh Guo Chen","L5200","Nurse",05,03,2010,"Bachelor In Nursing (IMU)" }
    };

    FILE *fInput = fopen(STAFF_FILE, "rb");

    if (fInput == NULL)
    {
        FILE *fOutput = fopen(STAFF_FILE, "wb");

        for (int i = 0; i < 6; ++i)
        {
            fwrite(&staff[i], sizeof(Staff), 1, fOutput);
        }

        fclose(fOutput);
    }
}

void StaffMenu()
{
    int choice;
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    puts(" MENU OF STAFF INFORMATION  ");
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    puts("1.Add     Staff Information");
    puts("2.Modify  Staff Information");
    puts("3.Search  Staff Information");
    puts("4.Display Staff Information");
    puts("5.Delete  Staff Information");
    puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    puts("\n");

    printf("Please keyin your choice : ");
    do {
        scanf("%d", &choice);
        if (choice == 1)
        {
            system("cls");
            AddStaffInformation();
        }
        else if (choice == 2)
        {
            system("cls");
            ModifyStaffInformation();
        }
        else if (choice == 3)
        {
            system("cls");
            SearchStaffInformationMenu();
        }
        else if (choice == 4)
        {
            system("cls");
            DisplayStaffInformation();
        }
        else if (choice == 5)
        {
            system("cls");
            DeleteStaffInformation();
        }
        else if (choice == 6)
        {
            system("cls");
            EXIT();
        }
        else
            printf("Please choose the correct choice !! \n\n Please keyin your choice :");

    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6);
};

void SearchStaffInformationMenu()
{
    int choice;
    puts("");
    puts("--------------------------------------------------");
    printf("||       ~~ Search Staff Information ~~       ||\n");
    printf("||  1. Search By Staff Name                   ||\n");
    printf("||  2. Search By Date Joined                  ||\n");
    printf("||  3. Back To The Staff Menu                 ||\n");
    puts("--------------------------------------------------");

    printf("Please choose your choice ( Staff Name - 1 | Date Joined - 2 | Back To Staff Menu - 3 ) : ");

    do
    {
        scanf("%d", &choice);
        rewind(stdin);

        if (choice == 1)
        {
            system("cls");
            SearchName();
        }
        else if (choice == 2)
        {
            system("cls");
            SearchDate();
        }
        else if (choice == 3)
        {
            system("cls");
            StaffMenu();
        }
        else
            printf("PLEASE KEY IN THE CORRECT INPUT !! =) \n ");
    } while (choice != 1 && choice != 2 && choice != 3);
};

void SearchName()
{
    Staff staff;

    FILE *fStaff = fopen(STAFF_FILE, "rb");

    if (fStaff == NULL)
    {
        printf("Error open file ! ");
        exit(-1);
    }
    char searchName[30], answer;
    int count = 0;

    puts("===================================================");
    puts("||         1. Search By Staff Name               ||");
    puts("===================================================");

    do
    {


        printf("Please key in the staff Name : ");
        rewind(stdin);
        scanf("%[^\n]", &searchName);

        fread(&staff, sizeof(Staff), 1, fStaff);

        if (strcmp(searchName, staff.staffName) == 0)
        {
            puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
            printf("                ~~~ RESULT OF THE SEARCH BY NAME ~~~               \n");
            printf("    STAFF ID      : %s \n", staff.staffID);
            printf("    NAME          : %s \n", staff.staffName);
            printf("    DEPARTMENT    : %s \n", staff.dept);
            printf("    DATE JOINED   : %02d - %02d - %4d \n", staff.datejoined.day, staff.datejoined.month, staff.datejoined.year);
            printf("    QUALIFICATION : %s \n", staff.qualification);
            puts("\n");
        }
        puts("\n");
        printf("Do you want to continue ?");
        scanf("%c", &answer);
        rewind(stdin);
        if (answer == 'N' || answer == 'n')\
        {
            int ans;
            printf("Do You Want Back To The Search Function ? ( 1. Yes || 2.No || ) :");
            scanf("%d", &ans);
            rewind(stdin);

            if (ans == 1)
            {
                system("cls");
                SearchStaffInformationMenu();
            }
            else if (ans == 2)
            {
                break;
            }
        }
    } while (answer == 'Y' || answer == 'y');
    fclose(fStaff);
};

void SearchDate()
{
    FILE *fStaff = fopen(STAFF_FILE, "rb");
    if (fStaff == NULL)
    {
        printf("Error open file ! ");
        exit(-1);
    }
    int searchMth, searchYr;
    int count = 0;
    char answer;
    puts("===================================================");
    puts("||         2. Search By Date Joined              ||");
    puts("===================================================");

    do {
        Staff staff;
        printf("Search Employees which joined Month and Year ? : ");
        scanf("%d %d", &searchMth, &searchYr);
        rewind(stdin);

        do
        {
            if (!feof(fStaff))
            {
                fread(&staff, sizeof(Staff), 1, fStaff);
            }
            if (searchMth == staff.datejoined.month && searchYr == staff.datejoined.year)
            {
                puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                printf("           ~~~ RESULT OF THE SEARCH BY DATE JOINED  ~~~               \n");
                printf("    STAFF ID      : %s \n", staff.staffID);
                printf("    NAME          : %s \n", staff.staffName);
                printf("    DEPARTMENT    : %s \n", staff.dept);
                printf("    DATE JOINED   : %02d - %02d - %4d \n", staff.datejoined.day, staff.datejoined.month, staff.datejoined.year);
                printf("    QUALIFICATION : %s \n", staff.qualification);

                puts("\n");
            }

        } while (!feof(fStaff));
        fclose(fStaff);

        puts("\n");
        printf("Do you want to repeat ?");
        scanf("%c", &answer);
        rewind(stdin);
        if (answer == 'N' || answer == 'n')\
        {
            int ans;
            printf("Do You Want Back To The Search Function ? ( 1. Yes || 2.No || ) :");
            scanf("%d", &ans);
            rewind(stdin);
            if (ans == 1)
            {
                system("cls");
                SearchStaffInformationMenu();
            }
            else if (ans == 2)
            {
                break;
            }
        }
    } while (answer == 'Y' || answer == 'y');
}

void AddStaffInformation()
{
    char addreply;

    do
    {
        FILE *fStaff = fopen(STAFF_FILE, "ab");

        if (fStaff == NULL)
        {
            printf("Error open file ! ");
            exit(-1);
        }

        puts("===============================================");
        puts("||      ADD STAFF INFORMATION SECTION        ||");
        puts("===============================================");

        puts("~ Do You Want To Add New Information For New Staff ? ( Yes - Y || No - N ): ");
        rewind(stdin);
        scanf("%c", &addreply);
        rewind(stdin);

        if (addreply == 'Y' || addreply == 'y')
        {
            Staff newStaff;

            puts("~~~ ADD NEW INFORMATION ~~~ \n");
            puts("1. Enter Staff Name                      : ");
            scanf("%[^\n]", &newStaff.staffName);
            rewind(stdin);
            puts("2. Enter Staff ID                        : ");
            scanf("%s", &newStaff.staffID);
            rewind(stdin);
            puts("3. Enter Dept of Staff                   : ");
            scanf("%s", &newStaff.dept);
            rewind(stdin);
            puts("4. Enter date joined of the staff        : ");
            scanf("%d %d %d", &newStaff.datejoined.day, &newStaff.datejoined.month, &newStaff.datejoined.year);
            rewind(stdin);
            puts("5. Enter the qualification of the staff  : ");
            scanf("%[^\n]", &newStaff.qualification);
            rewind(stdin);

            fwrite(&newStaff, sizeof(Staff), 1, fStaff);
        }
        else if (addreply == 'N' || addreply == 'n')
        {
            printf("No new input data will be add into the module . \n");
        }
        else if (addreply != 'Y' || addreply != 'y' || addreply != 'N' || addreply != 'n')
        {
            printf("Only Can keyin Y or N , means Yes - Y ; No - N .\n\n");
        }

        fclose(fStaff);

        int answer;

        printf("Do You Want Back To The Menu ? ( 1. Yes || 2.No ) :");
        scanf("%d", &answer);
        rewind(stdin);

        system("cls");

        if (answer == 1)
        {
            StaffMenu();
        }
    } while (addreply == 'Y' || addreply == 'y');
}

void DisplayStaffInformation()
{
    FILE *fOutput = fopen(STAFF_FILE, "rb");
    int count = 0;

    if (fOutput == NULL)
    {
        printf("Error open file ! ");
        exit(-1);
    }

    puts("");
    puts("=============================================");
    puts("||    DISPLAY STAFF INFORMATION SECTION    ||");
    puts("=============================================");
    puts("");

    do
    {
        Staff staff;

        fread(&staff, sizeof(Staff), 1, fOutput);

        if (!feof(fOutput))
        {
            count++;

            printf("No. %d \n", count);
            printf("    STAFF ID      : %s \n", staff.staffID);
            printf("    NAME          : %s \n", staff.staffName);
            printf("    DEPARTMENT    : %s \n", staff.dept);
            printf("    DATE JOINED   : %02d - %02d - %4d \n",
                staff.datejoined.day, staff.datejoined.month, staff.datejoined.year);
            printf("    QUALIFICATION : %s \n", staff.qualification);
        }
    } while (!feof(fOutput));

    fclose(fOutput);

    int answer;
    printf("\nDo You Want Back To The Menu ? ( 1. Yes || 2.No ) :");
    scanf("%d", &answer);
    rewind(stdin);

    if (answer == 1)
    {
        system("cls");
        StaffMenu();
    }
    else
    {
        printf("\n Thank You ~ \n");
        system("pause");
        exit(-1);
    }
}

void ModifyStaffInformation()
{
    char ans;	int answer;
    char modifyID[20];
    char modifyReply;

    FILE *fStaff = fopen(STAFF_FILE, "rb");
    if (fStaff == NULL)
    {
        printf("Error open file ! ");
        exit(-1);
    }
    puts("=======================================================");
    puts("||      MODIFY STAFF INFORMATION SECTION             ||");
    puts("=======================================================");

    do
    {
        puts("~ Do You Want To Modify Information Of Staff ? ( Yes - Y || No - N ): ");
        rewind(stdin);
        scanf("%c", &modifyReply);
        rewind(stdin);

        if (modifyReply == 'Y' || modifyReply == 'y')
        {
            Staff staff[MAX_SIZE];

            int i = 0;
            printf("Enter Staff ID : ");
            gets(modifyID);

            do
            {

                fread(&staff[i], sizeof(Staff), 1, fStaff);

                if (!feof(fStaff))
                {
                    if (strcmp(modifyID, staff[i].staffID) == 0)
                    {
                        printf("Enter The Modify Staff ID                       : ");
                        rewind(stdin);
                        scanf("%s", &staff[i].staffID);
                        printf("Enter The Modify Staff Name                     : ");
                        rewind(stdin);
                        scanf("%[^\n]", &staff[i].staffName);
                        printf("Enter The Modify Staff Department               : ");
                        rewind(stdin);
                        scanf("%s", &staff[i].dept);
                        printf("Enter The Modify Staff Date Joined (DD-MM-YYYY) : ");
                        rewind(stdin);
                        scanf("%d %d %d", &staff[i].datejoined.day, &staff[i].datejoined.month, &staff[i].datejoined.year);
                        printf("Enter The Modify Staff Qualification            : ");
                        rewind(stdin);
                        scanf("%[^\n]", &staff[i].qualification);
                    }

                    i++;
                }

            } while (!feof(fStaff));

            fclose(fStaff);

            FILE * fOutput = fopen(STAFF_FILE, "wb");

            if (fOutput != NULL)
            {
                for (int j = 0; j < i; ++j)
                {
                    fwrite(&staff[j], sizeof(staff[j]), 1, fOutput);
                }
            }

            printf("Modify Successfully ! \n");

            fclose(fOutput);

            printf("Do You Want To Continue ? ( Y - Yes || N - No )");
            rewind(stdin);
            scanf("%c", &ans);

            if (ans == 'n' || ans == 'N')
            {
                system("cls");
                DisplayStaffInformation();
            }

            printf("Do You Want To Back To The Menu ? ( 1. Yes || 2. No ) ");
            scanf("%d", &answer);
            rewind(stdin);

            if (answer == 1)
            {
                system("cls");
                StaffMenu();
            }
            else if (answer == 2)
            {
                break;
            }
        }
    } while (ans == 'Y' || ans == 'y');
}

void DeleteStaffInformation()
{
    FILE *fStaff = fopen(STAFF_FILE, "rb");
    if (fStaff == NULL)
    {
        printf("Error open file ! ");
        exit(-1);
    }

    Staff staff[MAX_SIZE];
    int i = 0;

    char idSearchDelete[20];
    int answer;

    do
    {

        fread(&staff[i], sizeof(Staff), 1, fStaff);

        if (!feof(fStaff))
        {
            i++;
        }
    } while (!feof(fStaff));

    fclose(fStaff);

    puts("======================================================");
    puts("||        DELETE STAFF INFORMATION SECTION          ||");
    puts("======================================================");
    puts("");

    int isFound = 0;
    int indexDelete = -1;

    do
    {
        puts("~ Do You Want To Delete Staff Information ? ( 1.Yes | 2.No )");
        scanf("%d", &answer);
        rewind(stdin);

        if (answer == 1)
        {
            printf("\nPlease Enter The Staff ID That You Want To Delete : ");
            scanf("%s", &idSearchDelete);
            rewind(stdin);

            for (int j = 0; j < i; ++j)
            {
                if (strcmp(idSearchDelete, staff[j].staffID) == 0)
                {
                    isFound = 1;
                    indexDelete = j;

                    break;
                }
            }

            if (isFound == 1)
            {
                printf("The Deleted Will Succesfull \n");

                FILE *fStaff = fopen(STAFF_FILE, "wb");

                for (int j = 0; j < i; ++j)
                {
                    if (j == indexDelete)
                        continue;

                    fwrite(&staff[j], sizeof(staff[j]), 1, fStaff);
                }

                fclose(fStaff);
            }
            else
            {
                puts("There Are No Any Information Will Be Delete !");
            }
        }
        else if (answer == 2)
        {
            printf("There Are No Any Information Will Be Delete ! \n");
        }

        puts("\nDo You Want To Continue ? (1.Yes || 2.No) ");
        scanf("%d", &answer);
        rewind(stdin);

        if (answer == 2)
        {
            int ans;
            printf("Do You Want Back To The Menu ? ( 1. Yes || 2.No  ) :");
            scanf("%d", &ans);
            rewind(stdin);

            if (ans == 1)
            {
                system("cls");
                StaffMenu();
            }
            else if (ans == 2)
            {
                break;
            }
        }
    } while (answer != 2);
}

void EXIT()
{
    puts("EXIT....");
}
