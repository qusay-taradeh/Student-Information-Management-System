/*******************************************Student Program*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Definition of student attributes*/
struct student;
typedef struct student* ptr;

typedef struct student
{
    int studentID;
    char studentName[25];
    char studentAddress[15];
    int classID;
    char dateOfEnrollment[10]; //i.e: 10/10/2010 ->10 chars.

    ptr left;
    ptr right;
};

typedef ptr BST; //BST: Binary Search Tree to store students info.
typedef ptr Pos; //Pos: temporary tree

BST initializeTree(BST tree) //initialize given tree to make it ready to use.
{
    if(tree!= NULL)
    {
        initializeTree(tree->left);
        initializeTree(tree->right);
        free(tree);
    }
    return NULL;
}

Pos findMin(BST tree) //finds left leaf node
{
    if(tree == NULL)
        return NULL;

    else if(tree->left == NULL)
        return tree;

    else
        return findMin(tree->left);
}

Pos findStudent(BST tree, int studentID) //finds student with respect to his/her ID number
{
    if(tree == NULL)
        return NULL;

    else if(studentID < tree->studentID)
        return findStudent(tree->left, studentID);

    else if(studentID > tree->studentID)
        return findStudent(tree->right, studentID);

    else
        return tree;
}

BST insertStudent(BST tree, int studentID, char studentName[25], char studentAddress[15], int classID, char dateOfEnrollment[10]) // insertion of students and sorting with respect to student ID.
{
    if(tree == NULL) //creates new node with given student info.
    {
        tree = (ptr)malloc(sizeof(struct student));
        tree->studentID = studentID;
        strcpy(tree->studentName,studentName);
        strcpy(tree->studentAddress,studentAddress);
        tree->classID = classID;
        strcpy(tree->dateOfEnrollment,dateOfEnrollment);
        tree->left = NULL;
        tree->right = NULL;
    }

    else if(studentID < tree->studentID) //will go left till accent to leaf node
    {
        tree->left = insertStudent(tree->left, studentID, studentName, studentAddress, classID, dateOfEnrollment);
    }

    else if(studentID > tree->studentID) //will go right till accent to leaf node
    {
        tree->right = insertStudent(tree->right, studentID, studentName, studentAddress, classID, dateOfEnrollment);
    }

    return tree;
}

BST deleteStudent(BST tree, int studentID) // deletes student given his/her ID
{
    Pos tempSt; //temporary node
    if(tree == NULL)
        printf("Student is not excited!\n");

    else if(studentID < tree->studentID) //will be going left
        tree->left = deleteStudent(tree->left, studentID);

    else if(studentID > tree->studentID) //will be going right
        tree->right = deleteStudent(tree->right, studentID);

    else if(tree->left && tree->right) //two children so find the ID then replace it with min ID in right subtree.
    {
        tempSt = findMin(tree->right);
        tree->studentID = tempSt->studentID;
        tree->right = deleteStudent(tree->right, tree->studentID);
    }
    else // a child or zero children
    {
        tempSt = tree;
        if(tree->left == NULL)
            tree = tree->right;

        else if(tree->right == NULL)
            tree = tree->left;

        free(tempSt);
    }
    return tree;
}

BST deleteStudentName(BST tree, char studentName[25]) // deletes student given his/her name
{
    Pos tempSt; //temporary node
    if(tree == NULL)
        printf("Student of this name is not excited!\n");

    else if(strcmp(studentName, tree->studentName) < 0) //will be going left
        tree->left = deleteStudentName(tree->left, studentName);

    else if(strcmp(studentName, tree->studentName) > 0) //will be going right
        tree->right = deleteStudentName(tree->right, studentName);

    else if(tree->left && tree->right) //two children so find the ID then replace it with min name in right subtree.
    {
        tempSt = findMin(tree->right);
        strcpy(tree->studentName, tempSt->studentName);
        tree->right = deleteStudentName(tree->right, tree->studentName);
    }
    else // a child or zero children
    {
        tempSt = tree;
        if(tree->left == NULL)
            tree = tree->right;

        else if(tree->right == NULL)
            tree = tree->left;

        free(tempSt);
    }
    return tree;
}

void printInorder(BST tree) //prints info in order so exactly will print ascending on the screen
{
    if(tree!=NULL)
    {
        printInorder(tree->left);
        printf("%-10d %-25s %-15s %-10d %s\n",tree->studentID,tree->studentName,tree->studentAddress,tree->classID,tree->dateOfEnrollment);
        printInorder(tree->right);
    }
}


void printInorderInFile(BST tree, FILE *data) //prints info in order so exactly will print ascending in given file
{
    if(tree!=NULL)
    {
        printInorderInFile(tree->left,data);
        fprintf(data, "%d  %s  %s  %d  %s\n",tree->studentID,tree->studentName,tree->studentAddress,tree->classID,tree->dateOfEnrollment);
        printInorderInFile(tree->right,data);
    }
}

void citySearch(BST tree, char city[]) // search and print all student info. with same given city name
{
    if(tree!=NULL)
    {
        citySearch(tree->left,city);
        if(strcmp(city,tree->studentAddress)==0)
        {
            printf("%-10d %-25s %-15s %-10d %s\n",tree->studentID,tree->studentName,tree->studentAddress,tree->classID,tree->dateOfEnrollment);
            printf("\n");
        }
        citySearch(tree->right,city);
    }
}

void classIDSearch(BST tree, int cId) // search and print all student info. with same given class ID
{
    if(tree!=NULL)
    {
        classIDSearch(tree->left, cId);
        if(cId == tree->classID)
        {
            printf("%-10d %-25s %-15s %-10d %s\n",tree->studentID,tree->studentName,tree->studentAddress,tree->classID,tree->dateOfEnrollment);
            printf("\n");
        }
        classIDSearch(tree->right, cId);
    }
}

BST sortNames(BST tree, int studentID, char studentName[25], char studentAddress[15], int classID, char dateOfEnrollment[10]) // insertion of students and sorting with respect to student Name.
{
    if(tree == NULL)
    {
        tree = (ptr)malloc(sizeof(struct student));
        tree->studentID = studentID;
        strcpy(tree->studentName,studentName);
        strcpy(tree->studentAddress,studentAddress);
        tree->classID = classID;
        strcpy(tree->dateOfEnrollment,dateOfEnrollment);
        tree->left = NULL;
        tree->right = NULL;
    }

    else if(strcmp(studentName, tree->studentName) < 0)
    {
        tree->left = sortNames(tree->left, studentID, studentName, studentAddress, classID, dateOfEnrollment);
    }

    else if(strcmp(studentName, tree->studentName) > 0)
    {
        tree->right = sortNames(tree->right, studentID, studentName, studentAddress, classID, dateOfEnrollment);
    }

    return tree;
}

void menu() // main menu of choices
{
    printf("==============================Menu==============================\n");
    printf("1.  Insert a student with all associated data.\n");
    printf("2.  Find a student with his/her ID, and updating any information.\n");
    printf("3.  List all students in lexicographic order of their names.\n");
    printf("4.  Search for a city and list all students from that city in lexicographic order of their names.\n");
    printf("5.  List all students by their class in lexicographic order of their names.\n");
    printf("6.  Delete a student given his/her ID.\n");
    printf("7.  Save all students in file studentsData.\n");
    printf("8.  Exit.\n\n");
}

void controller() // controls operation in our program
{
    /*
    =============================Parameters==================================
    data: studentData.txt file contains info. of students, to append new data.
    id: student ID.
    name: student name.
    address: student address "city".
    date: student date of enrollment.
    cId: student class ID.
    choice: choice number from the list.
    studentTree: general tree of students sorted by students IDs.
    nameTree: tree of students sorted by students names.
    temp, temp2: temporary node to represent founded student.
    */
    FILE *data;
    data = fopen("studentsData.txt","r");
    int id;
    char name[25];
    char address[15];
    char date[10];
    int cId;
    int choice = 0;
    BST studentTree, nameTree;
    Pos temp, temp2;
    studentTree = NULL;
    studentTree = initializeTree(studentTree);
    nameTree = NULL;
    nameTree = initializeTree(nameTree);

    while(fscanf(data,"%d  %s  %s  %d  %s", &id, name, address, &cId, date) != EOF) //loop to load data from the file
    {
        studentTree = insertStudent(studentTree, id, name, address, cId, date); //insertion all students' data.
        nameTree = sortNames(nameTree, id, name, address, cId, date); //insertion all students' data.
    }


    while(1) //main loop to maintain operations.
    {
        menu();
        printf("Enter number of choice you want: ");
        scanf("%d",&choice);

        if(choice == 8) //exit choice
        {
            printf("\n^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^Thanks^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^\n");
            break;
        }

        else if(choice<=0 || choice>8) //invalid choice
            printf("\nEnter valid value please!!\n\n");

        else
            switch(choice) //switch statement of options
            {
            case 1: //adding student.
                printf("\nID: ");
                scanf("%d",&id);
                if(id < 0) //invalid ID.
                    while(1)
                    {
                        printf("\nEnter valid ID please!\n");
                        printf("\nID: ");
                        scanf("%d",&id);
                        if(id >= 0)
                            break;
                    }
                temp = findStudent(studentTree,id); //representation temporary node to edit info.
                if(temp!=NULL)
                {
                    printf("\nStudent of this ID: %d is excited!\n",id);
                    continue;
                }
                printf("\nName: ");
                scanf("%s",name);

                printf("\nAddress: ");
                scanf("%s",address);

                printf("\nClass ID: ");
                scanf("%d",&cId);
                if(cId < 0) //invalid class ID.
                    while(1)
                    {
                        printf("\nEnter valid Class ID please!\n");
                        printf("\nClass ID: ");
                        scanf("%d",&cId);
                        if(cId >= 0)
                            break;
                    }
                printf("\nDate Of Enrollment in number form(i,e:1/1/2000): ");
                scanf("%s",date);

                studentTree = insertStudent(studentTree, id, name, address, cId, date); //insertion all students' data.
                nameTree = sortNames(nameTree, id, name, address, cId, date); //insertion all students' data.
                break;

            case 2: //searching student with ID number.
                printf("\nEnter ID: ");
                scanf("%d", &id);
                if(id < 0) //invalid ID.
                    while(1)
                    {
                        printf("\nEnter valid ID please!\n");
                        printf("\nID: ");
                        scanf("%d",&id);
                        if(id >= 0)
                            break;
                    }
                temp = findStudent(studentTree,id); //representation temporary node to edit info.
                if(temp==NULL)
                {
                    printf("\nStudent of this ID: %d is not excited!\n",id);
                    continue;
                }
                printf("ID         Name                      Address         Class ID   Date Of Enrollment\n");
                printf("--         ----                      -------         --------   ------------------\n");
                printf("%-10d %-25s %-15s %-10d %s\n",temp->studentID,temp->studentName,temp->studentAddress,temp->classID,temp->dateOfEnrollment);
                printf("\n");

                printf("if you need to change any information of this student enter number of choice or 0 to do nothing: \n");
                printf("1.Student ID, 2.Student Name, 3.Student Address, 4.Student Class ID, 5.Student Date Of Enrollment\n");
                scanf("%d",&choice);
                while(1) //loop edit info. of student or not when choice is zero.
                {
                    switch(choice)
                    {
                    case 0: //nothing changed.
                        break;
                    case 1: //change ID.
                        printf("ID: ");
                        scanf("%d",&id);
                        temp2 = findStudent(studentTree,id); //representation temporary node to edit info.
                        if(temp2!=NULL)
                        {
                            printf("\nStudent of this ID: %d is excited!\n",id);
                        }
                        else
                            temp->studentID = id;
                        break;

                    case 2: //change name.
                        printf("Name: ");
                        scanf("%s",name);
                        strcpy(temp->studentName, name);
                        break;

                    case 3: //change address.
                        printf("Address: ");
                        scanf("%s",address);
                        strcpy(temp->studentAddress, address);
                        break;

                    case 4: //change class id.
                        printf("Class ID: ");
                        scanf("%d",&cId);
                        temp->classID = cId;
                        break;

                    case 5: //change date of enrollment.
                        printf("Date Of Enrollment: ");
                        scanf("%s",date);
                        strcpy(temp->dateOfEnrollment, date);
                        break;

                    default : //invalid choice.
                        printf("write valid choice please!! \n");
                    }
                    if(choice>=0 && choice<6) //if statement to continue sequence of program.
                        break;
                    scanf("%d",&choice);
                }
                break;

            case 3: //sorting with respect to the names of students.
                printf("ID         Name                      Address         Class ID   Date Of Enrollment\n");
                printf("--         ----                      -------         --------   ------------------\n");
                printInorder(nameTree);
                printf("\n");
                break;

            case 4: //sorting with respect to the names of students also with given city name.
                printf("\nEnter name of city: ");
                scanf("%s", address);
                printf("ID         Name                      Address         Class ID   Date Of Enrollment\n");
                printf("--         ----                      -------         --------   ------------------\n");
                citySearch(studentTree,address);
                printf("\n");
                break;

            case 5: //sorting with respect to the names of students also with given class ID.
                printf("\n Enter ID number of class: ");
                scanf("%d",&cId);
                if(cId < 0)
                    while(1)
                    {
                        printf("\nEnter valid Class ID please!\n");
                        printf("\nClass ID: ");
                        scanf("%d",&cId);
                        if(cId >= 0)
                            break;
                    }
                printf("ID         Name                      Address         Class ID   Date Of Enrollment\n");
                printf("--         ----                      -------         --------   ------------------\n");
                classIDSearch(studentTree, cId);
                printf("\n");
                break;

            case 6: //deletes student by given ID number of this student.
                printf("\nEnter ID: ");
                scanf("%d", &id);
                if(id < 0) //invalid ID.
                    while(1)
                    {
                        printf("\nEnter valid ID please!\n");
                        printf("\nID: ");
                        scanf("%d",&id);
                        if(id >= 0)
                            break;
                    }

                temp = findStudent(studentTree,id); //representation temporary node to edit info.
                if(temp==NULL)
                {
                    printf("\nStudent of this ID: %d is not excited!\n",id);
                }
                else
                {
                    strcpy(name,temp->studentName);
                    studentTree = deleteStudent(studentTree, temp->studentID);
                    nameTree = deleteStudentName(nameTree, name);
                }
                break;

            case 7: //print students informations in file sorting ID numbers.
                fclose(data);
                data = fopen("studentsData.txt","w");
                printInorderInFile(studentTree,data);
                fprintf(data,"\n");
                printf("\nAll information saved in studentData.txt\n");
                break;
            }
    }
    fclose(data);
    free(initializeTree(studentTree)); //deleting student tree from memory after storing it in the file.
    free(initializeTree(nameTree)); //deleting sorting student names tree from memory but this tree is not in the file.

}

int main()
{
    printf("---------------------------School Classes Program---------------------------\n\n");
    controller();
    return 0;
}
