#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <regex.h>
#include <ctype.h>

//GLOBAL VARIABLES
#define MAX_FILES 100
#define FRMT_OFF "\033[1;39m"
#define FRMT_RED "\033[1;31m"
#define FRMT_GREEN "\033[1;32m"
#define FRMT_YELLOW "\033[1;33m"
#define FRMT_BLUE "\033[1;34m"
#define FRMT_PURPLE "\033[0;35m"
#define FRMT_CYAN  "\033[0;36m"
#define FRMT_WHITE "\033[0;97m"


char *file_names[MAX_FILES];
int file_count = 0;
char current_dir[200]; //Basically char d[200]

// FUNCTIONS
void Intro();
void GetDir();
void WorkingDir();
void PickFeature();
void DelFile();
void SearchFile();
void SortFiles();
void FilterFile();
void OpenFile(int n);
void RenameFile(int n);
void MoveFile(int n);
void FileInfo(int n);
void EncryptFile();
void DecryptFile();
void ZipFile();
void HideFile();
void UnzipFile();
long FileSize(int n);
void GetDir();
void Create();
void ClearScreen();
void EnterToContinue();
void LowerToUpper(char *s);
void ShowFilesInDir();
void Functions();

int main()
{
    current_dir[0]=0; //Init current directory as an empty string.
    char inflp[1];

    do
    {
        ClearScreen(); //Set welcome and menu
        WorkingDir(); //Load given directory as current directory to work upon
        ShowFilesInDir();

        //Perform functions/operations on files & folders.
        PickFeature(0); //First time start with no '0' selected file.

        //repeat all per user inputs.
        printf("\nDo you want me to help you with something else too....I can perform a bunch of other tasks too?\n(y/n) :");
        fflush(stdout);
        scanf("%s",inflp);
        LowerToUpper(inflp);
    }
    while(inflp[0] == 'Y');
    return 0;
}

void ClearScreen()
{
    //Clear the screen
    system("clear");
    Intro();
}

void Intro()
{
    //TITLE/INTRO
    printf("\n=========================== "FRMT_GREEN"WELCOME to FILE MANAGER (using C)" FRMT_OFF" =====================================\n");
    Functions(); //Calling the function Function() to display the functions that can be performed on the files
}

void Functions()
{
    //Displaying the different functions that can be performed on the files
    //Highlighting a letter in each word to make it easier for the user to select a function
    printf(
        FRMT_RED"I"FRMT_OFF"NFO  "
        FRMT_RED"O"FRMT_OFF"PEN  "
        FRMT_RED"R"FRMT_OFF"ENAME  "
        FRMT_RED"M"FRMT_OFF"OVE  "
        FRMT_RED"D"FRMT_OFF"ELETE  "
        FRMT_RED"S"FRMT_OFF"ORTING  "
        FRMT_RED"F"FRMT_OFF"ILTER  FI"
        FRMT_RED"N"FRMT_OFF"D  "
        FRMT_RED"E"FRMT_OFF"NCRYPT  DE"
        FRMT_RED"C"FRMT_OFF"RYPT  "
        FRMT_RED"Z"FRMT_OFF"IP  CRE"
        FRMT_RED"A"FRMT_OFF"TE  "
        FRMT_RED"U"FRMT_OFF"NZIP  "
        FRMT_RED"H"FRMT_OFF"IDE\n===================================================================================================\n");
    fflush(stdout); //To make sure that the code is printed on the screen
}

void EnterToContinue()
{

    char cnt[1];
    
    // Prompt the user to press 'c' to continue
    while(1)
    {
        printf("Enter c to continue :");
        scanf("%s",cnt);
        if(cnt[0] == 'c')
        {
            break;
        }
        else
        {
            printf("\nInvalid input\n");
        }
    }

}

void WorkingDir()
{
    // Checking if the directory is empty
    if(strlen(current_dir)==0)
    {
        // Prompt the user to enter a directory as the directory is empty
        printf("\nWhich directory do you want me to work on :");
        scanf("%s", current_dir);
        GetDir();
    }

    // Checking if the existing directory is the desired directory or not
    else
    {
        // Prompt the user to confirm if the existing directory is the desired directory
        char yn[1];
        printf("\n'%s' is the directory you want me to work on right???\n(y/n): ",current_dir);
        scanf("%s", yn);

        //Using Switch case to handle the user's choice
        switch (yn[0])
        {
        case 'y':
            GetDir(); //Calling the GetDir() function to get the files in the directory
            break;
        case 'n':
            current_dir[0]=0; //Resetting the current directory

            // Prompt the user to enter a new directory as it is not the desired directory
            printf("\nOhh...wrong directory!\n Enter new or working directory :");
            scanf("%s", current_dir);

            ClearScreen();
            GetDir(); //Calling the GetDir() function to get the files in the directory
            break;
        default:
            current_dir[0]=0; //Resetting the current directory

            // Prompt the user to enter a new directory as the input is invalid
            printf("Invalid Input\nI'm going to assume that it was the wrong directory.\n Try to re-enter directory :");
            scanf("%s", current_dir);
        
            ClearScreen();
            GetDir(); //Calling the GetDir() function to get the files in the directory
            break;
        }
    }
}

void GetDir()
{
    // Using Dirent.h to get the files in a directory
    DIR *dir;
    struct dirent *entry;
    file_count = 0;

    // Open the current directory
    dir = opendir(current_dir);

    // Check if the directory can be opened
    if (dir == NULL)
    {
        printf("\nError opening directory\n");
    }
    else
    {
        // Read directory entries
        while ((entry = readdir(dir)) != NULL && file_count < MAX_FILES)
        {
            // Skip "." and ".." entries
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                file_names[file_count] = strdup(entry->d_name);
                file_count++;
            }
        }
        printf("Your working directory : "FRMT_BLUE"%s"FRMT_OFF"\n-------------------------------------------------------------",current_dir);
    }
    // Close the directory
    closedir(dir);
}

void ShowFilesInDir()
{
    // Printing the Files in the Directory
    printf("\nThese are the files present in working directory 👇\n");
    for (int i = 0; i < file_count; i++)
    {
        printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
    }
    printf("\n=====================================================\n");
}

void LowerToUpper(char *s)
{
    // Declare a pointer to traverse the string
    char *p;

    for (p = s; *p; p++)
    {
        //If the character is lowercase, convert it to uppercase
        if (islower(*p))
            *p = toupper(*p);
    }
}

void PickFeature(int n)
{
    //Prompt the user to select a function to perform on the selected file
    printf("\nWhat do you want me to do? \nEnter "FRMT_RED"RED"FRMT_OFF" letter of the file menu item :");
    char opt[1];
    scanf("%s", opt);

    //Convert the user's input to uppercase
    LowerToUpper(opt);

    //Switch case to handle the user's choice
    switch (opt[0])
    {
    case 'N':
        SearchFile(); //Called to search for file in the directory
        break;
    case 'S':
        SortFiles(); //Called to sort the files in the directory
        break;
    case 'F':
        FilterFile();  //Called to filter the files in the directory
        break;
    case 'O':

        // If the user has not selected a file, prompt them to select a file
        if(n==0)
        {
            printf("\nWhich  file? Please enter number shown against files to perform file functions :");
            scanf("%d", &n);
        }
        OpenFile(n);  //Called to open the selected file
        break;
    case 'R':

        // If the user has not selected a file, prompt them to select a file and also the directory of the file
        if(n==0)
        {
            current_dir[0]=0;
            printf("\nEnter the directory of the file :");
            scanf("%s",current_dir);
            ClearScreen();
            GetDir();
            ShowFilesInDir();
            printf("\nWhich  file? Please enter number shown against files to perform file functions :");
            scanf("%d", &n);
        }
        RenameFile(n);  //Called to rename the selected file
        break;
    case 'M':

        // If the user has not selected a file, prompt them to select a file
        if(n==0)
        {
            printf("\nWhich  file? Please enter number shown against files to move it :");
            scanf("%d", &n);
        }
        MoveFile(n); //Called to move the selected file
        break;
    case 'D':

        // If the user has not selected a file, prompt them to select a file and also the directory of the file
        if(n==0)
        {
            current_dir[0]=0;
            printf("\nEnter the directory of the file :");
            scanf("%s",current_dir);
            ClearScreen();
            GetDir();
            ShowFilesInDir();
            printf("\nWhich  file? Please enter number shown against files to delete :");
            scanf("%d", &n);
        }
        DelFile(n);  //Called to delete the selected file
        break;
    case 'I':

        // If the user has not selected a file, prompt them to select a file
        if(n==0)
        {
            printf("\nWhich  file? Please enter number shown against files to perform file functions :");
            scanf("%d", &n);
        }
        FileInfo(n);  //Called to get the details of the selected file
        break;
    case 'E':
        EncryptFile();  //Called to encrypt the selected file
        break;
    case 'C':
        DecryptFile();  //Called to decrypt the selected file
        break;
    case 'Z':
        ZipFile();  //Called to zip the selected file
        break;
    case 'U':
        UnzipFile();  //Called to unzip the selected file
        break;
    case 'H':
        HideFile();  //Called to hide the selected file
        break;
    case 'A':
        Create(); //Called to create a file or a folder
        break;
    default:
        break;
    }

}

void SearchFile()
{
    regex_t regex;
    int return_value;
    char input[50];
    char found = 'N';

    printf("\nEnter a file name to search :");
    scanf("%s", input);
    LowerToUpper(input);

    return_value = regcomp(&regex,input,0);

    for (int i = 0; i < file_count; i++)
    {
        char chk[50];
        strcpy(chk, file_names[i]);
        LowerToUpper(chk);

        return_value = regexec(&regex, chk, 0, NULL, 0);

        if (return_value == 0 )
        {
            if (strlen(chk) == strlen((input)))
            {
                found = 'Y';
                printf(FRMT_RED"%d-"FRMT_OFF"%s\n",i+1,file_names[i]);
            }
        }
        else if (return_value == REG_NOMATCH)
        {
            continue;
        }
        else
        {
            printf("\nAn error occured while checking for file '%s'.\n",file_names[i]);
        }
    }
    if(found == 'Y')
    {
        int n;
        printf("\nFollowing file matched with the input name. Just enter the number shown against the found file to perform file functions :");
        scanf("%d", &n);
        PickFeature(n);
    }
    else if(found =='N')
    {
        printf("File not found\n");
    }
}

void SortFiles()
{
    char c[1];

    // Display the sorting options to the user
    printf("\n"FRMT_RED"a)"FRMT_OFF"\tA --> Z\n" FRMT_RED"b)"FRMT_OFF"\tZ --> A\n"FRMT_RED"c)"FRMT_OFF"\tBy Size (LARGEST TO SMALLEST)\n"FRMT_RED"d)"FRMT_OFF"\tBy Size (SMALLEST TO LARGEST)\n");

    // Prompt the user to select a sorting option
    printf("So how should I sort it??? :");
    scanf("%s", c);

    // If the user selects option 'a', sort the files in ascending alphabetical order
    if (c[0] == 'a')
    {
        // Sort the files using bubble sort algorithm
        for (int i = 0; i < file_count; i++)
        {
            for (int j = i + 1; j < file_count; j++)
            {
                if (strcasecmp(file_names[i], file_names[j]) > 0)
                {
                    char s[200];
                    strcpy(s, file_names[i]);
                    strcpy(file_names[i], file_names[j]);
                    strcpy(file_names[j], s);
                }
            }
        }

        if(file_count>0)
        {
            printf("\nYep!!! Sort by A --> Z has been completed\n\n");

            // Display the sorted files
            for (int i = 0; i < file_count; i++)
            {
                printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
            }
            printf("\n=====================================================\n");
            
            // Prompt the user to select a file and perform a function on the selected file
            int n;
            printf("\nJust enter number shown against the sorted files to perform file functions :");
            scanf("%d", &n);
            PickFeature(n);
        }
    }

    // If the user selects option 'b', sort the files in descending alphabetical order
    if (c[0] == 'b')
    {
        // Sort the files using bubble sort algorithm
        for (int i = 0; i < file_count; i++)
        {
            for (int j = i + 1; j < file_count; j++)
            {
                if (strcasecmp(file_names[i], file_names[j]) < 0)
                {
                    char s[200];
                    strcpy(s, file_names[i]);
                    strcpy(file_names[i], file_names[j]);
                    strcpy(file_names[j], s);
                }
            }
        }

        if(file_count>0)
        {
            printf("\nYep!!! Sort by Z --> A has been completed\n\n");

            // Display the sorted files
            for (int i = 0; i < file_count; i++)
            {
                printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
            }
            printf("\n=====================================================\n");

            // Prompt the user to select a file and perform a function on the selected file
            int n;
            printf("\nJust enter number shown against the sorted files to perform file functions :");
            scanf("%d", &n);
            PickFeature(n);
        }
    }

    // If the user selects option 'c', sort the files by size in descending order
    if (c[0] == 'c')
    {
        // Sort the files using bubble sort algorithm
        for (int i = 0; i < file_count; i++)
        {
            for (int j = i + 1; j < file_count; j++)
            {
                if (FileSize(i) > FileSize(j))
                {
                    char s[200];
                    strcpy(s, file_names[i]);
                    strcpy(file_names[i], file_names[j]);
                    strcpy(file_names[j], s);
                }
            }
        }


        if(file_count>0)
        {
            printf("\nYep!!! Sort by Z --> A has been completed\n\n");

            // Display the sorted files
            for (int i = 0; i < file_count; i++)
            {
                printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
            }
            printf("\n=====================================================\n");

            // Prompt the user to select a file and perform a function on the selected file
            int n;
            printf("\nJust enter number shown against the sorted files to perform file functions :");
            scanf("%d", &n);
            PickFeature(n);
        }
    }

    // If the user selects option 'd', sort the files by size in ascending order
    if (c[0] == 'd')
    {
        // Sort the files
       for (int i = 0; i < file_count; i++)
        {
            for (int j = i + 1; j < file_count; j++)
            {
                if (FileSize(i) > FileSize(j))
                {
                    char s[200];
                    strcpy(s, file_names[i]);
                    strcpy(file_names[i], file_names[j]);
                    strcpy(file_names[j], s);
                }
            }
        }

        if(file_count>0)
        {
            printf("\nYep!!! Sort by size has been completed\n\n");

            //display the sorted files
            for (int i = 0; i < file_count; i++)
            {
                printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
            }
            printf("\n=====================================================\n");

            // Prompt the user to select a file and perform a function on the selected file
            int n;
            printf("\nJust enter number shown against the sorted files to perform file functions :");
            scanf("%d", &n);
            PickFeature(n);
        }
    }

    EnterToContinue();
}

void FilterFile()
{
    printf("\nPlease enter the string (file extension or few characters) with which you want to filter the files :");
    regex_t regex;
    int return_value;
    char input[50];
    scanf("%s", input);
    LowerToUpper(input);
    //Regex to compare for??
    return_value = regcomp(&regex,input,0);
    char found = 'N';
    for (int i = 0; i < file_count; i++)
    {
        char chk[50];
        strcpy(chk, file_names[i]);
        LowerToUpper(chk);
        //Check for matches
        return_value = regexec(&regex, chk, 0, NULL, 0);

        if (return_value == 0 )
        {
            found = 'Y';
            printf(FRMT_RED"%d-"FRMT_OFF"%s\n", i + 1, file_names[i]);
        }
        else if (return_value == REG_NOMATCH)
        {
            continue;
        }
        else
        {
            printf("\nAn error occured during search/filter in in file %s.\n",chk);
        }
    }
    if(found == 'Y')
    {
        int n;
        printf("\nJust enter number shown against the filtered files to perform file functions :");
        scanf("%d", &n);
        PickFeature(n);
    }
    else if(found =='N')
    {
        printf("\nNo match found\n");
    }
}

void OpenFile(int n)
{
    // Declare and initialize the command string
    char cmd[200] = "xdg-open ";

    // Append the selected file's name to the command string and execute it
    strcat(cmd, file_names[n - 1]);
    system(cmd);

    EnterToContinue();
}

void RenameFile(int n)
{
    char nname[50], cmd[200] = "mv ", todir[200];

    // Copy the current directory path to the todir variable
    strcpy(todir,current_dir);

    // Append the directory path and a slash to the command string
    strcat(cmd, todir);
    strcat(cmd,"/");

    // Prompt the user to enter the new name for the file
    printf("\nWhat do you want me to rename it to??? And ya....don't forget the file ext :");
    scanf("%s", nname);

    // Append the old file name, a space, the directory path, a slash, and the new file name to the command string
    strcat(cmd, file_names[n - 1]);
    strcat(cmd, " ");
    strcat(cmd,todir);
    strcat(cmd,"/");
    strcat(cmd, nname);

    // Execute the rename command
    system(cmd);

    // Inform the user that the renaming process has been completed
    printf("\nYep!!! Renaming process has been completed\n");
    EnterToContinue();
}

void MoveFile(int n)
{
    char cmd[200]="mv ", todir[200]; // Declare command and target directory strings

    // Get target directory from user
    printf("\nWhich directory should I move it to? :");
    scanf("%s", todir); 

    // Add filename to command, target directory to command, and execute the command
    strcat(cmd, file_names[n - 1]); // Add filename to command
    strcat(cmd, " ");
    strcat(cmd, todir);
    strcat(cmd, "/");
    system(cmd); 

    printf("\nYep!!! Move process been completed.\n");
    EnterToContinue();

    // Updates the current directory and shows the updated file list
    GetDir();
    ShowFilesInDir();
}

void DelFile(int n)
{
    char cmd[100] = "rm ", todir[200];

    // Copy the current directory path to the todir variable
    strcpy(todir,current_dir);

    // Append the directory path and a slash followed by the file's name to the command string to delete the file
    strcat(cmd, todir);
    strcat(cmd,"/");
    strcat(cmd, file_names[n - 1]);
    system(cmd);

    // Inform the user that the file has been deleted
    printf("\nDeleting...\nThe file has been successfully deleted.\n");
    EnterToContinue();
}

void FileInfo(int n)
{
    // Declare and initialize the command string
    char cmd[200] = "stat ";

    // Inform the user that the file details are being retrieved
    printf("\nHere are the details of the file\n");

    //Using system commands to get the file details
    strcat(cmd, file_names[n - 1]);
    system(cmd);

    EnterToContinue();
}

void EncryptFile()
{
    //Pick a file to encrypt
    int n;
    printf("\nWhich file should I encrypt?");
    scanf("%d", &n);

    //Declare and initialize the command string and other necessary variables
    char chk[100];
    strcpy(chk, file_names[n - 1]);

    FILE *inputFile, *outputFile;

    // File paths
    char inputFilePath[100];
    strcpy(inputFilePath, chk);

    //Adding Encrypted to the new file name
    char outputFilePath[100];
    int j = 0;
    for (int i = 0; i < strlen(chk) + 9; i++)
    {
        if (chk[i] == '.')
        {
            strcat(outputFilePath, "Encrypted");
            j = 9;
        }
        outputFilePath[i + j] = chk[i];
    }

    // Open the input file for reading
    inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL)
    {
        perror("\nError opening output file");
    }

    // Open the output file for writing
    outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL)
    {
        perror("\nError opening output file");
        fclose(inputFile);
    }

    // Read from the input file, convert to uppercase, and write to the output
    // file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL)
    {
        // Perform modifications to the content
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            buffer[i] = (int)buffer[i] ^ 2;
        }

        // Write the modified content to the output file
        fputs(buffer, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("\nFile successfully processed!");

    // Ask the user if they want to delete the original file
    char y[1];
    printf("\nShould I delete the original file??? :");
    scanf("%s", y);

    if (y[0] == 'y')
    {
        //Delete the original file
        char cmd2[100] = "rm ";
        strcat(cmd2, file_names[n-1]);
        system(cmd2);
    }
    else if (y[0] == 'n')
    {
        //Keeping the original file
        printf("\nSure...I won't delete it\n");
    }
    EnterToContinue();
}

void DecryptFile()
{
    //Pick a file to encrypt
    int n;
    printf("\nWhich file should I decrypt?");
    scanf("%d", &n);

    //Declare and initialize the command string and other necessary variables
    char chk[100];
    strcpy(chk, file_names[n - 1]);

    FILE *inputFile, *outputFile;

    // File paths
    char inputFilePath[100];
    strcpy(inputFilePath, chk);

    //Adding Decrypted to the new file name
    char outputFilePath[100];
    int j = 0;
    for (int i = 0; i < strlen(chk) + 9; i++)
    {
        if (chk[i] == '.')
        {
            strcat(outputFilePath, "Decrypted");
            j = 9;
        }
        outputFilePath[i + j] = chk[i];
    }

    // Open the input file for reading
    inputFile = fopen(inputFilePath, "r");
    if (inputFile == NULL)
    {
        perror("\nError opening output file");
    }

    // Open the output file for writing
    outputFile = fopen(outputFilePath, "w");
    if (outputFile == NULL)
    {
        perror("\nError opening output file");
        fclose(inputFile);
    }

    // Read from the input file, convert to uppercase, and write to the output
    // file
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), inputFile) != NULL)
    {
        // Perform modifications to the content
        for (int i = 0; buffer[i] != '\0'; i++)
        {
            buffer[i] = (int)buffer[i] ^ 2;
        }

        // Write the modified content to the output file
        fputs(buffer, outputFile);
    }

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("\nFile successfully processed!");

    // Ask the user if they want to delete the original file
    char y[1];
    printf("\nShould I delete the original file??? :");
    scanf("%s", y);

    if (y[0] == 'y')
    {
        //Delete the original file
        char cmd2[100] = "rm ";
        strcat(cmd2, file_names[n-1]);
        system(cmd2);
    }
    else if (y[0] == 'n')
    {
        //Keeping the original file
        printf("\nSure...I won't delete it\n");
    }
    EnterToContinue();
}

void ZipFile()
{
    char zname[50], cmd[200] = "zip ";

    // Prompt the user to enter a name for the zip file
    printf("\nWhat should we name the zip file??? :");
    scanf("%s", zname);

LOOP:
    int n;
    
    // Prompt the user to select a file to add to the zip file
    printf("\nWhich file should I compress and add to the zipped folder? :");
    scanf("%d", &n);

    // Append the zip file's name, the ".zip" extension, and the selected file's name to the command string
    strcat(cmd, zname);
    strcat(cmd, ".zip ");
    strcat(cmd, file_names[n - 1]);
    system(cmd);

    // Delete the original file
    char cmd2[100] = "rm ";
    strcat(cmd2,file_names[n-1]);
    system(cmd2);
    
    // Ask the user if they want to add another file to the zip file
    char yn[1];
    printf("\nWould you like to add another file to the zip file??? :");
    scanf("%s", yn);

    if (yn[0] == 'y')
    {
        goto LOOP; // If user wants to add another file, go back to the start
    }
    EnterToContinue();
}

void UnzipFile()
{
    // Declare and initialize the command string and other necessary variables
    char cmd[200] = "unzip ";
    int n;

    // Prompt the user to select a file to unzip
    printf("\nWhich file...??? :");
    scanf("%d", &n);

    // Append the selected file's name to the command string and executes the cmd
    strcat(cmd, file_names[n - 1]);
    system(cmd);
    EnterToContinue();
    
    // Delete the original zip file
    char cmd2[100] = "rm ";
    strcat(cmd2,file_names[n-1]);
    system(cmd2);
}

long FileSize(int n)
{
    struct stat file_stat;

    char filename[100];
    strcpy(filename, file_names[n]);

    off_t file_size = 0;

    // Use the stat function to get information about the file
    if (stat(filename, &file_stat) == 0)
    {
        // The size of the file is stored in the st_size field of the struct
        file_size = file_stat.st_size;

        // Print the size of the file
        // printf("Size of %s: %ld bytes\n", filename, file_size);

        // You can now use the 'file_size' variable as needed
    }

    return file_size;
}

void HideFile()
{
    // Declare and initialize the command string and other necessary variables
    char cmd2[200]="cat ",zipname[200],picturename[200],newpicname[200];
    int n;

    // Prompt the user to create a zipped file
    printf("First make a zipped file:\n");
    ZipFile();

    // Clear the screen and display the current directory
    ClearScreen();
    GetDir();
    ShowFilesInDir();

    // Prompt the user to select the recently created zip file
    printf("\nEnter the number against the recently created zip file:");
    scanf("%d",&n);
    strcpy(zipname,file_names[n-1]);

    // Prompt the user to select the image to hide the zip file in
    printf("\nEnter the number against the image you want to use to hide:");
    scanf("%d",&n);
    strcpy(picturename,file_names[n-1]);

    // Build the command string to concatenate the image and the zip file
    strcat(cmd2,picturename);
    strcat(cmd2," ");
    strcat(cmd2,zipname);
    strcat(cmd2," ");

    // Prompt the user to enter the name of the new image
    printf("Enter the new image name which will have hidden folders and the ext should be same as previous image ext:");
    scanf("%s",newpicname);

    // Complete the command string and execute it
    strcat(cmd2,"> ");
    strcat(cmd2,newpicname);
    system(cmd2);

    // Delete the original zip file
    char cmd[100] = "rm ";
    strcat(cmd,zipname);
    system(cmd);

    // Delete the original image
    char cmd1[100] = "rm ";
    strcat(cmd1,picturename);
    system(cmd1);

    // Inform the user that the operation is complete
    printf("Done , if you want to get your hidden files back just unzip the image\n");

    // Pause the program until the user presses a key
    EnterToContinue();
}



void Create()
{
    // Declare variables for the new file/folder name and the system commands
    char newfilefoldername[200],cmd4[200]="touch ",cmd3[200]="mkdir ",y[1];
    
    // Ask the user if they want to create a file or a folder
    printf("Do you want to create a file or a folder? \n");
    printf(FRMT_RED"1-"FRMT_OFF" File\n");
    printf(FRMT_RED"2-"FRMT_OFF" Folder\n");
    printf("Just enter the index against the functions:");
    scanf("%s",y);
    
    // Switch case to handle the user's choice
    switch(y[0])
    {
    case '1':
        // If the user chose to create a file
        printf("Enter the name of the file you want to create: ");
        scanf("%s",newfilefoldername);
        strcat(cmd4,newfilefoldername); // Add the file name to the touch command
        system(cmd4); // Execute the touch command to create the file
        printf("File created successfully!!! \n");
        EnterToContinue(); // Wait for the user to press a key before continuing
        break;
    case '2':
        // If the user chose to create a folder
        printf("Enter the name of folder you want to create: ");
        scanf("%s",newfilefoldername);
        strcat(cmd3,newfilefoldername); // Add the folder name to the mkdir command
        system(cmd3); // Execute the mkdir command to create the folder
        printf("Folder created successfully!!! \n");
        EnterToContinue(); // Wait for the user to press a key before continuing
        break;
    default:
        // If the user entered an invalid choice
        printf("Invalid input\n");
        break;
    }
}