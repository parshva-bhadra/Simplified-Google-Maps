#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "priority_queue.h"
#include "time.h"

int main()
{
    int choice, repeat, n, degree;
    PtrAdjList G;
    timeHistoryTable *T;

    printf("WELCOME TO ROUTING!\n");
    printf("Mini Project of Group 29 under TA Mr. Tanish Lad\n");
    printf("\nBy\nAditya Malhotra(2020101052)\nParshva Bhadra(2020101001)\nAnubhav Pal(2020112012)\nKarnati Jahnavi(2020102052)\nAaryan Sharma(2020115008)\n\n");

    printf("Please enter the total number of vertices: \n");
    scanf("%d", &degree);

    G = CreateEmptyGraph(degree);
    T = createEmptyTimeHistoryTable(degree);

MENU:
    printf("\nMenu:\n");
    printf("To add an edge, Press 1\n");
    printf("To delete an edge, Press 2\n");
    printf("To update distance, Press 3\n");
    printf("To update number of cars, Press 4\n");
    printf("To find shortest distance, Press 5\n");
    printf("To find least time, Press 6\n");
    printf("To find a safe path, Press 7\n");
    printf("To print the graph, Press 8\n");
    printf("To print the time history table, Press 9\n");
    printf("To exit the program, Press 10\n\n");
    scanf("%d", &choice);

    if (choice < 1 || choice >= 11)
    {
        printf("\nInvalid Command! Please Choose Again.\n");
        goto MENU;
    }

    if (choice == 1)
    {

        printf("\nYou have selected to add an edge.\n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT1:
        scanf("%d", &n);

        if (n == 1)
        {
            int vertex1, vertex2, cars;
            double length;

        POINT11:
            printf("\nEnter the vertices between which you want to insert an edge: \n");
            scanf("%d%d", &vertex1, &vertex2);
            printf("Enter the length of the edge: \n");
            scanf("%lf", &length);
            printf("Enter the number of cars on the edge: \n");
            scanf("%d", &cars);
            InsertEdge(G, vertex1, vertex2, length, cars);

            printf("\nReady for next task\n");
            printf("Do you want to add another edge?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT12:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT11;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT12;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT1;
        }
    }

    if (choice == 2)
    {

        printf("\nYou have selected to delete an edge.\n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT2:
        scanf("%d", &n);

        if (n == 1)
        {
            int vertex1, vertex2;

        POINT21:
            printf("Enter the vertices between which you want to delete the edge:\n");
            scanf("%d%d", &vertex1, &vertex2);
            DeleteEdge(G, vertex1, vertex2);

            printf("\nReady for next task\n");
            printf("Do you want to delete another edge?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT22:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT21;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT22;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT2;
        }
    }

    if (choice == 3)
    {
        printf("You have selected to update distance.\n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT3:

        scanf("%d", &n);

        if (n == 1)
        {
            int vertex1, vertex2;
            double new_length;

        POINT31:
            printf("Enter the vertices between which you want to update distance:\n");
            scanf("%d%d", &vertex1, &vertex2);
            printf("Enter the new distance:\n");
            scanf("%lf", &new_length);
            UpdateDis(G, vertex1, vertex2, new_length);

            printf("\nReady for next task\n");
            printf("Do you want to update another distance?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT32:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT31;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT32;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command. Please Enter Again.\n");
            goto POINT3;
        }
    }

    if (choice == 4)
    {
        printf("You have selected to update number of cars. \n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT4:
        scanf("%d", &n);

        if (n == 1)
        {
            int vertex1, vertex2;
            int new_cars;

        POINT41:
            printf("Enter the vertices between which you want to update number of cars:\n");
            scanf("%d%d", &vertex1, &vertex2);
            printf("Enter the updated number of cars:\n");
            scanf("%d", &new_cars);
            UpdateCars(G, vertex1, vertex2, new_cars);

            printf("\nReady for next task\n");
            printf("Do you want to update another number of cars?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT42:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT41;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT42;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT4;
        }
    }

    if (choice == 5)
    {
        printf("You have selected to find shortest distance.\n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT5:
        scanf("%d", &n);

        if (n == 1)
        {
            int source, destination;

        POINT51:
            printf("Enter the source of the path: \n");
            scanf("%d", &source);
            printf("Enter the destination of the path: \n");
            scanf("%d", &destination);
            shortest_distance_choice4(G, source, destination);

            printf("\nReady for next task\n");
            printf("Do you want to find shortest distance between another source and destination?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT52:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT51;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT52;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT5;
        }
    }

    if (choice == 6)
    {

        printf("You have selected to find least time. \n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT6:
        scanf("%d", &n);

        if (n == 1)
        {
            int source, destination;

        POINT61:
            printf("Please enter the source of path:\n");
            scanf("%d", &source);
            printf("Please enter the destination of the path:\n");
            scanf("%d", &destination);
            shortest_time_choice5(G, source, destination);

            printf("\nReady for next task\n");
            printf("Do you want to find least time between another source and destination?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT62:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT61;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT62;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT6;
        }
    }

    if (choice == 7)
    {

        printf("You have selected to find a safe distance.\n");
        printf("To calculate safe distance we need data of the previous five dats\n");
        printf("To continue, Press 1\nTo go back to the main menu, Press 0\n");

    POINT7:
        scanf("%d", &n);

        if (n == 1)
        {
            int m;
            printf("Welcome to safe path Menu\n");
            printf("To add data for previous five days, Press 1\n");
            printf("To calculate safe path, Press 2\n");
            printf("To go back to the Main Menu, Press 0\n");
            printf("Enter your choice: ");
            scanf("%d", &m);
            if (m == 1)
            {
                int vertex1,vertex2;
                double t1, t2, t3, t4, t5;
            POINT70:
                printf("Please enter the vertices between which you want to add data:\n");
                scanf("%d%d", &vertex1, &vertex2);
                printf("Enter the time taken for the last five days\n");
                scanf("%lf %lf %lf %lf %lf", &t1, &t2, &t3, &t4, &t5);
                addTimeNode(G, T, vertex1, t1, t2, t3, t4, t5, vertex2);
                printf("Ready for next task\n");
                printf("To add data for previous five days, Press 1\n");
                printf("To calculate safe path, Press 2\n");
                printf("To go back to the Main Menu, Press 0\n");
            }

            if (m == 2)
            {
                int source, destination;
            POINT71:
                printf("Please enter the source of path: \n");
                scanf("%d", &source);
                printf("Please enter the destination of the path:\n");
                scanf("%d", &destination);
                SafeAlgorithmStart(T, G, source, destination);
                printf("Ready for next task\n");
                printf("To add data for previous five days, Press 1\n");
                printf("To calculate safe path, Press 2\n");
                printf("To go back to the Main Menu, Press 0\n");
            }
        POINT72:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT70;
            }
            if (repeat == 2)
            {
                goto POINT71;
            }
            if(repeat==0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter again.\n");
                goto POINT72;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter again.\n");
            goto POINT7;
        }
    }

    if (choice == 8)
    {
        printf("You have selected to print the graph.\n");
        printf("To continue, Press 1\n To go back to the main menu , Press 0\n");
    POINT8:
        scanf("%d", &n);
        if (n == 1)
        {
        POINT81:
            PrintList(G);
            printf("\nSuccessfully printed the graph.\n");
            printf("Do you want to print the graph again?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT82:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT81;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT82;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT8;
        }
    }

    if (choice == 9)
    {
        printf("You have selected to print the time history table.\n");
        printf("To continue, Press 1\n To go back to the main menu , Press 0\n");
    POINT9:
        scanf("%d", &n);

        if (n == 1)
        {
        POINT91:
            printTimeHistoryTable(T);
            printf("\nSuccessfully printed the time history table. \n");
            printf("Do you want to print the time history table again?\n");
            printf("If YES, Press 1 \nIf No, Press 0\n");

        POINT92:
            scanf("%d", &repeat);
            if (repeat == 1)
            {
                goto POINT91;
            }
            if (repeat == 0)
            {
                goto MENU;
            }
            if (repeat != 1 || repeat != 0)
            {
                printf("Invalid Command! Please Enter Again.\n");
                goto POINT92;
            }
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT9;
        }
    }

    if (choice == 10)
    {

        printf("You have selected to exit the program. \n");
        printf("To continue, Press 1\nTo stay in the main menu, Press 0\n");

    POINT10:
        scanf("%d", &n);

        if (n == 1)
        {
            DeleteList(G);
            deleteMemoryOfTable(T);
            printf("Thank You, Have a nice day!\n");
            goto EXIT;
        }

        if (n == 0)
        {
            goto MENU;
        }

        if (n != 0 || n != 1)
        {
            printf("Invalid Command! Please Enter Again.\n");
            goto POINT10;
        }
    }
EXIT:
    return 0;
}