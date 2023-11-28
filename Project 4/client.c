//Zach Taylor
//CSCI 3240
//Project 4
//This program runs a client and server based interactions where the server takes in a request from the user (using the read() function) and does the appropriate commands to the records.csv file.
//In this program you can (1)add an employee to the records.csv file
//                        (2)Search by Name
//                        (3)Search by Zip Code
//                        (4)Search by Salary
//                        (5)Terminate
//Once the server does the does the right action correlating to the given command it will send back the user the information by using the write() function 
#include "csapp.h"
#include <stdio.h>        //Pre-Processor Directives 

void print_menu();        //print menu function prototype

static void result(int result) {   //function of result() that will help aid in the warning messages that we get when doing the scanf function
    (void)result; // Use the result to avoid the result warning message 
}
//When I was running the code with out the result( scanf()) I got alot of warning messages that said "Unused result" of scanf() function.
//To help aid these warning messages I created a function that would Hold the result so that it would say "unused result". 
int main(int argc, char *argv[])  
{
    int clientfd;  //file descriptor to communicate with the server
    char *host, *port;
    size_t n; 
    char buffer [MAXLINE]; //MAXLINE = 8192 defined in csapp.h
    bzero(buffer,MAXLINE); 
    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	    exit(0);
    }
    host = argv[1];
    port = argv[2];

    //client file descriptor that will hold the host and the port 
    clientfd = Open_clientfd(host, port);
    int user_choice;
    int w_result;    //variable declarations 

    //Calling the print menu function that will display the options to the user of the program
    print_menu();    
    w_result = scanf("%d", &user_choice);  //using the scanf function to take in user input and if it is bad then it will display a B for bad 
    if(w_result != 1){
        printf("B");
    }
    //I deciced to use a while true loop when implementing this becuase I figured that inside oof it I could have an option that would breakout when the user enters 5 to terminate the loop
    while(1){
        //Option 1:Sending a new employee to the records.csv file
        if(user_choice == 1){ 
            printf("\n"); //New line character for printing purposes
            char first_name[MAXLINE];
            char last_name[MAXLINE];
            char Department[MAXLINE];   //Character arrays to temporarily hold data that will be sent to the server 
            char zip_code[MAXLINE];
            char salary[MAXLINE];
            char choice[] = "1";      
            n = write(clientfd,choice,strlen(choice));                //Writing to the server option 1 since the user selected option 1
            printf("Enter First Name: ");                             //Asking for the First Name
            result(scanf("%s", first_name));                         //getting the user's input 
            getchar();                                                //getchar() function to get the newline character 
            n = write(clientfd,first_name,strlen(first_name));         //writing to the server the first name to be added to the records.csv
            printf("Enter Last Name: ");                               //Asking for the Last Name
            result(scanf("%s", last_name));                            //getting the user's input 
            getchar();                                                 //calling the getchar function 
            n = write(clientfd,last_name,strlen(last_name));          //then writing to the server the last name 
            printf("Enter Zip Code: ");                               //Promting the user for the Zip Code
            result(scanf("%s", zip_code));                            //getting the user's input 
            getchar();                                                //calling the getchar function 
            n = write(clientfd,zip_code,strlen(zip_code));            //then writing the data back to the server 
            printf("Enter Department: ");                             //Same until line you reach line 78
            result(fgets(Department, sizeof(Department), stdin));
            Department[strcspn(Department, "\n")] = '\0';
            n = write(clientfd,Department,strlen(Department));
            printf("Enter Salary: ");
            result(scanf("%s", salary));
            getchar();
            n = write(clientfd,salary,strlen(salary));            
            printf("Message from the server:\n");                //Displaying a message to the user that you are now displaying the input recieved from the server 
            n = read(clientfd,buffer,MAXLINE);                   //Here you are now reading in the input from the server and Displaying that to the user 
            printf("%s\n",buffer);                               //Displaying the contents of the server here 
            bzero(buffer,MAXLINE);                   //Then here you are using the built in C function bzero() that will clear out the buffer so that old messages will not be contained in the buffer prints
            if(n<0){                     //If n (which was set equal to the previous read from the server) is less than zero then that means an error has occured in receiving the message from the server 
                perror("Error!!"); //Printing out an Error message to let the user know that something got lost in connecting back to the client 
            }
        }
        else if(user_choice == 2){ //If the user selects option 2 then we can drop into here and execute code from lines 86 to 105
            printf("\n");         //Printing out a new line so that when we prompt the user a question it will not be underneath the menu selection
            char first_name [MAXLINE];
            char last_name [MAXLINE];       //Character arrays to temporarily hold data that will be sent to the server
            char choice[] = "2";           //Since we are in option 2 we can send the character array of "2" to the server 
            n = write(clientfd,choice,strlen(choice));    
            printf("Enter First Name: ");        
            result(scanf("%s",first_name));                        //Prompting and asking the user for the appropriate information for option 2
            getchar();                                             //Then using the scanf function to take in the user input 
            n = write(clientfd,first_name,strlen(first_name));     //Then using the write() function to send the information to the server
            printf("Enter Last Name: ");
            result(scanf("%s",last_name));                         
            getchar();
            n = write(clientfd,last_name,strlen(last_name));
            if(n<0)
                perror("Error!!");
            printf("Message from the server: \n");          //Printing out the information sent back from the server
            n = read(clientfd,buffer,MAXLINE);              //Using the read() function so that we can read back the information sent back from the server
            printf("%s\n",buffer);                        //Printing out the message from the buffer
            printf("\n");                                
            bzero(buffer,MAXLINE);                        //Clearing out the buffer 
        }
        else if(user_choice == 3){       //If the user selects option 3 the execute lines 110 throught line 123
            printf("\n");              //Printing out a new line so that when we prompt the user a question for option 3 it will not be directly underneath the menu selection
            char zip_code[MAXLINE];    //Temporary character array of zip_code that will hold the zip code that the user enters 
            char choice[] = "3";
            n = write(clientfd,choice,strlen(choice));
            printf("Enter Zip Code: ");                         //Prompting and asking the user for the appropriate information for option 3
            result(scanf("%s", zip_code));                      //Then using the scanf function to take in the user input
            getchar();                                          //Then using the write() function to send the information to the server
            n = write(clientfd,zip_code,strlen(zip_code));
            if(n<0)   
                perror("Error!!");                               //Printing out the information sent back from the server
            printf("Message from the server:\n");                 
            n = read(clientfd,buffer,MAXLINE);                    //resetting the buffer so that we can take on more information
            printf("%s\n",buffer);
            bzero(buffer,MAXLINE);
        }
        else if(user_choice == 4){     //If the user selects option 4 the execute lines 125 throught line 144
            printf("\n");              //Printing out a new line so that when we prompt the user a question it will not be underneath the menu selection
            char comparison[MAXLINE];
            char salary[MAXLINE];      //Character arrays to temp hold information form the user that will be sent to the server
            char choice[] = "4";
            n = write(clientfd,choice,strlen(choice));
            printf("Enter Salary: ");                      //Prompting the user for the salary and the comparison type 
            result(scanf("%s", salary));                   //Writing the character arrays that hold the information to the server using the read() function 
            getchar();                                     
            n = write(clientfd,salary,strlen(salary));
            printf("Enter Comparison Type [’>’,’<’,’==’,’>=’,’<=’]: ");
            result(scanf("%s",comparison));
            getchar();
            n = write(clientfd,comparison,strlen(comparison));
            if(n<0)
                perror("Error!!");  
             printf("Message from the server:\n");       //Printing out the information sent back from the server
             n = read(clientfd,buffer,MAXLINE);
             printf("%s\n",buffer);            //resetting the buffer so that we can take on more information
            bzero(buffer,MAXLINE);
        }
        else if(user_choice == 5){   //Since option 5 is the option that terminates everything...
            char choice[] = "5";      //We will pass in option 5 to the server and break out of the while loop 
            n = write(clientfd,choice,strlen(choice)); //Writing to the server just "5" since we want to close everything on server side
            break;
        }
        print_menu();                  //while loop recurring condition
        user_choice = 0;               //setting the user's choice back to zero
        w_result = scanf("%d", &user_choice);  
        if(w_result != 1){
            printf("B");
        }
        }
    
        printf("Connection Closed!!\n"); //Once the user has selected option 5 now and is out of the while loop we can now display a message that the connection has closed between the Server and Client
        return 0; //returning zero back to the main function 
}
//function of void print_menu() defined below
void print_menu(){                  //In this function I am prompting the user of all of the available options that he or she can pick from 
    printf("(1) Add record\n");
    printf("(2) Search by Name\n");
    printf("(3) Search by Zip Code\n");
    printf("(4) Search by Salary\n");
    printf("(5) Terminate\n");
    printf("Select an option [1,2,3,4 or 5]: ");
}
