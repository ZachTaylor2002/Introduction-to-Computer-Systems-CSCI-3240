//Zach Taylor
//CSCI 3240
//Project 1 
//Hexadecimal dump
#include <stdio.h>
#include <string.h>                               //Pre-Processor directives 
#include <ctype.h>
#include <stdbool.h>
void print_less_than_normal_amt();
void print_normal_characters(char,char*,int);
int main(int argc, char **argv) {   
    FILE *file_object;                           //Variable declarations of the object file and the text_info_array that we will be reading from to store the 
    const int MAXIMUM_SIZE = 16;                 //characters from the file 
    char text_info_array[MAXIMUM_SIZE];
    char *file_name = argv[1];                    //Since we took in data from the user from the command line you must index from argv[1] to get the name of the text file
    file_object = fopen(file_name, "r");          //Opening the file in r mode so that we can read from the file
    int hex_counter = 0;                      //More varaiable declarations of hex_counter and single_char  
    char single_char;
    while (feof(file_object)!=true) {      //Using the C function of feof (which is a end of file flag) that will continue on until we have reached the end of the file 
        printf("%08x: ", hex_counter);      //Printing of the hexadecimal row counter 
        int text_counter = 0;                                         //Variable declaration of text_counter that will keep up with the number of characters read 
        //Using a for loop to iterate through the file to get characters.
        //Since we want to print every two letters together (in Hexadecimal) and we know that each line will have 16 of them I decided to readin two numbers together and the increment by 2 (in the for loop) everytime we did that so we will be able to eight sub-sections together 
        for (int index = 0; index < MAXIMUM_SIZE; index += 2) {
            single_char = fgetc(file_object);
            text_info_array[index] = single_char;
            single_char = fgetc(file_object);
            text_info_array[index+1] = single_char;
        
             if (single_char == EOF) {      //if the single_character variable is equal to the end of file then you can break out of the for loop
                break;
            }
            printf("%02x%02x ", text_info_array[index],text_info_array[index+1]);    
            text_counter += 2;                                //incrementing the text_counter by two since we have successfully read and printined out two hexadecimal characters 
        }
        //In the case that we have less than 16 characters that we are trying to read we must print out spaces for the text to be aligned 
        if(text_counter<16){
        //calling the print less than normal amount function 
         print_less_than_normal_amt();
        }
        //printing the characters from the file normally  
        print_normal_characters(single_char,text_info_array,text_counter);
        hex_counter += 16;
    }

    fclose(file_object); //closing the file 
    return 0; 
}
void print_less_than_normal_amt(){ //About 15 total spaces between the last printing of the hexadecimal number and the ".h/isprint"
    for (int index = 0; index < 15; index++) { 
            printf(" ");  //Printing out the single character space 
        }
}
void print_normal_characters(char single_char,char* text_info_array ,int text_counter){
    printf(" ");//Printing out the space before 
    for (int index = 0; index < text_counter; index++) { //Printing out the characters 
              single_char = text_info_array[index];
            if (isprint(single_char)) { //if the isprint function returns anything postive which is true then print out the characters
                putchar(single_char);
            } 
            else {  //not printinable character print the period.
                putchar('.');
            }
        }

        putchar('\n');

}
