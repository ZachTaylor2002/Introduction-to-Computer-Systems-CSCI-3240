//Zach Taylor
//CSCI 3240
//server.c  
//Project 4
//This server.c will take in the information passed in from the client.c and perform the actions and then write back to the mutiple clients.
#include "csapp.h"
//Declaration of the struct of Arguments
struct Arguments {  //Declaring a struct of "Arguments" that will hold the file descriptor, the client hostname, and the client port 
    int connfd;     //Decided to make this structure becuase the pthread_create function only takes in four arguments and needs this as way to pass in more.  
    char client_hostname[MAXLINE];       
    char client_port[MAXLINE];
};

//Declaration of a mutex and setting it equal to default values 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Declaration of the struct of Struct_Employee_Info
typedef struct {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char zipCode[MAX_LENGTH];
    char department[MAX_LENGTH];
    int salary;

} Struct_Employee_Info;

//definition of the void server function that will take in the connection file descriptor as well as the character arrays of the hostname and port
void serverFunction(int connfd){
    
    FILE *file_object;                        //Declaring a file_object so that operations can be done with the records.csv
    Struct_Employee_Info employees[MAX_SIZE]; //Declaring an array of employees of type Struct_Employee_Info
    char line[MAXLINE];                       //character array of line that will be used to send the information back to the client
    int count = 0;                           //counter variable to keep up with the total amount of people in the employee array
    file_object = fopen("records.csv", "r");   //Opening the file for reading 
    if (file_object == NULL) {
        printf("Unable to open the file.\n");  //Print out an error message if it doesn't open
    }

    //Adding the record from records.csv to the employees structure
    while (fgets(line, sizeof(line), file_object)) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",
               employees[count].firstName, employees[count].lastName,
               employees[count].zipCode, employees[count].department,&employees[count].salary);
        count++;
    }

    fclose(file_object);//closing the file 
    char buffer[MAXLINE]; //MAXLINE = 8192 defined in csapp.h 
    char successMessage[MAXLINE] = "Record added Sucessfully!!\n"; //Messsage here to be sent back for option 1
    size_t n;
    if(n<0){
        perror("Error!!");
    }
    //While loop to continue until we have reached option 5 (which will break out)
    while(1){
         bzero(buffer,MAXLINE);                     //before we do any option we will clean out the buffer and read in the first option
         n = read(connfd, buffer, MAXLINE);        //we will then store the character answer in the option character array and use the atoi to convert to 
        int action_option;                         //string to integer
        char firstName[MAXLINE];
        char option[MAXLINE];
        sscanf(buffer, "%[^\n]", option);        //Here I am using the sscanf function that will stop until we get to the end of a new line
        action_option = atoi(option);
        bzero(buffer,MAXLINE);
    if(action_option == 1){     //Finally COMPLETE works with mutiple clients :))))
        char firstName[MAXLINE];       //For option 1 I decided to create temporary character arrays to store the information we are getting back from the 
        char LASTName[MAXLINE];        //client and use the function sscanf() that will read from the buffer until a new line character is reached.
        char zip_code[MAXLINE];       //After all the information has been stored temporarily, I then assigned the file_object to fopen and in appending mode +
        char Department[MAXLINE];     //Once I had the file in this appending mode I used the fprintf to send the information to the records.csv file 
        char salary[MAXLINE];         //Once that is done I proceeded to change the mode to reading so that the additional information would be added to the 
        n = read(connfd, buffer, MAXLINE);   //employees array of struct so that we would be able to use that information in future operations in the server 
        sscanf(buffer, "%[^\n]", firstName);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", LASTName);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", zip_code);
        bzero(buffer,MAXLINE);                      
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", Department);
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", salary);
        bzero(buffer,MAXLINE);
        pthread_mutex_lock(&mutex); 
        file_object = fopen("records.csv", "a+");
        fprintf(file_object,"%s,%s,%s,%s,%s\n",firstName,LASTName,zip_code,Department,salary);
        pthread_mutex_unlock(&mutex);  
        n = write(connfd,successMessage,strlen(successMessage));
        count = 0;  
        fclose(file_object);
        file_object = fopen("records.csv", "r");
         while (fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        fclose(file_object); 
        bzero(buffer,MAXLINE);
    }
    else if(action_option == 2){ 
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
       char lastName[MAXLINE];
        n = read(connfd, buffer, MAXLINE);       //For option 2 I decided to modify lab 6 so that instead of breaking out once we found one person we would continue 
        sscanf(buffer, "%[^\n]", firstName);   //through since we will have to Jack Sparrows
        bzero(buffer, MAXLINE);
        n = read(connfd, buffer, MAXLINE);    //Reading in the data from the client
        sscanf(buffer, "%[^\n]", lastName);
        bzero(buffer, MAXLINE);
        int index_holder = -1;
        //For loop to iterate through the array of employees 
        for(int index = 0; index < count; index++){
            //Comparing if the names match 
            if((strcmp(employees[index].firstName,firstName)==0) && (strcmp(employees[index].lastName,lastName)==0)){
                index_holder = index;
                snprintf(line,MAXLINE,"%s,%s,%s,%s,%d\n",employees[index_holder].firstName,employees[index_holder].lastName,employees[index_holder].zipCode,employees[index_holder].department,employees[index_holder].salary);
        //Using the sprintf function to store the line of data all together in the character array of line
            n = write(connfd,line,strlen(line));  //Writing to the client 
             bzero(line, MAXLINE);          
             bzero(buffer,MAXLINE);    //Clearing out the character arrays 
            }
        }
        if(index_holder == -1){ //If index holder didn't change the send back No Record found
            char n_line[MAXLINE];
             bzero(n_line,MAXLINE);    
            strcpy(n_line,"No record found!!\n");
            n = write(connfd,n_line,strlen(n_line));
        }
    }
    else if(action_option == 3){  //For option three I decided to iterate through the zip code structure array and if the zip code is there then 
        bzero(line, MAXLINE);    //string cat the information together else then write to the client No record found
        char zip_Code[MAXLINE];
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]",zip_Code);
        pthread_mutex_lock(&mutex);
        int index_holder = -1;
            for(int index = 0; index < count; index++){
                if((strcmp(employees[index].zipCode,zip_Code)==0)){
                    index_holder = index;
                     bzero(line, MAXLINE);
                    strcat(line,employees[index_holder].firstName);
                    strcat(line,",");
                    strcat(line,employees[index_holder].lastName);
                    strcat(line,",");
                    strcat(line,employees[index_holder].zipCode);
                    strcat(line,",");
                    strcat(line,employees[index_holder].department);
                    strcat(line,",");
                    char salary[MAX_LENGTH];
                    snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
                    strcat(line, salary);
                    strcat(line, "\n");
                    n = write(connfd,line,strlen(line));
                }
                
            }
        pthread_mutex_unlock(&mutex);
        if(index_holder == -1){ 
            char n_line[MAXLINE];
            bzero(n_line,MAXLINE);
            strcpy(n_line,"No record found!!\n");
            n = write(connfd,n_line,strlen(n_line));
        }
        else{
            bzero(line, MAXLINE);
            bzero(buffer,MAXLINE);
        }
    }
    else if(action_option == 4){  //Option 4, we are going to searching for the salary and doing a comparison 
        char SAlary[MAXLINE];     //I decided to do a string comparison to match up with the comaprsions then do a for loop to run through and check
        int new_counter = 0;
        file_object = fopen("records.csv", "r");
        while(fgets(line, sizeof(line), file_object)){
            new_counter++;
        }
        fclose(file_object); 
        file_object = fopen("records.csv", "r");
        if(new_counter != count){
        count=0;
         while(fgets(line, sizeof(line), file_object)) {
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%d",employees[count].firstName, employees[count].lastName,employees[count].zipCode, employees[count].department,&employees[count].salary);
            count++;
            }
        }
       fclose(file_object); 
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, "%[^\n]", SAlary);
        char comparison[MAXLINE];               //CORRECT
        bzero(buffer,MAXLINE);
        n = read(connfd, buffer, MAXLINE);
        sscanf(buffer, " %[^\n]", comparison);
        int salary = atoi(SAlary);
        int index_holder = -1;
        if((strcmp(comparison,">=")==0)){
        for(int index = 0; index < count; index++){
        if(employees[index].salary >= salary){
            index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
        }
        }
    }
        else if((strcmp(comparison,"<=")==0)){
         for(int index = 0; index < count; index++){
        if(employees[index].salary <= salary){
            index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
            }
         }
        }
        else if((strcmp(comparison,"<")==0)){
         for(int index = 0; index < count; index++){
       if(employees[index].salary < salary){
            index_holder = index;
            bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
            n = write(connfd,line,strlen(line));
        }
         }
        }
        else if((strcmp(comparison,">")==0)){
         for(int index = 0; index < count; index++){
       if(employees[index].salary > salary){
            index_holder = index;
            bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
        }
    }
    }
    else if((strcmp(comparison,"==")==0)){
         for(int index = 0; index < count; index++){
        if(employees[index].salary == salary){
           index_holder = index;
             bzero(line, MAXLINE);
            strcat(line,employees[index_holder].firstName);
            strcat(line,",");
            strcat(line,employees[index_holder].lastName);
            strcat(line,",");
            strcat(line,employees[index_holder].zipCode);
            strcat(line,",");
            strcat(line,employees[index_holder].department);
            strcat(line,",");
            char salary[MAX_LENGTH];
            snprintf(salary, sizeof(salary), "%d", employees[index_holder].salary);
            strcat(line, salary);
            strcat(line, "\n");
             n = write(connfd,line,strlen(line));
            
        }
    }
    }
    if(index_holder == -1){ //If index holder is still -1 then return back no record found 
        char n_line[MAXLINE];
        bzero(n_line,MAXLINE);
        strcpy(n_line,"No record found!!\n");
        n = write(connfd,n_line,strlen(n_line));
    }
    else{
        bzero(line,MAXLINE);
        bzero(buffer,MAXLINE);
    }
    if(n<0){
        perror("Error!!");
    }
    }
     else if(action_option==5){ 
         break;
     }
    }
}
void *thread(void *vargp){
    struct Arguments *arguments = (struct Arguments *)vargp;
    int connfd = (*arguments).connfd;
    char *client_hostname = (*arguments).client_hostname;
    char *client_port = (*arguments).client_port;
    pthread_detach(pthread_self());
    free(vargp);
    serverFunction(connfd);
    Close(connfd);
    printf("(%s,%s)disconnected\n", client_hostname, client_port);
    return NULL;
}


int main(int argc, char *argv[])
{
   int listenfd;
   int *connfd; //file descriptor to communicate with the client
   socklen_t clientlen;
   struct sockaddr_storage clientaddr;  //Enough space for any address 
   char client_hostname[MAXLINE], client_port[MAXLINE];
   pthread_t tid;
    
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    //Server runs in the infinite loop. 
    //To stop the server process, it needs to be killed using the Ctrl+C key. 
    while (1) {               
    	clientlen = sizeof(struct sockaddr_storage);
        // wait for the connection from the client.
        connfd = malloc(sizeof(int));
    	*connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, 
                                   MAXLINE,client_port, MAXLINE, 0);

        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        struct Arguments *arguments = malloc(sizeof(struct Arguments));
        (*arguments).connfd = *connfd;
        strcpy(arguments->client_hostname, client_hostname);
        strcpy(arguments->client_port, client_port);
        pthread_create(&tid, NULL, thread, arguments);
        //function to interact with the client's information
        //calling the server function to do the operations 
    }
        
    exit(0);
}
