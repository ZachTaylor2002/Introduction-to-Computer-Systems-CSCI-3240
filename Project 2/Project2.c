/* CSCI3240: Project 2
 * <Zach Taylor>
 * <M01524585>
 * CSCI 3240
 * Project2.c
 */

//Mystery Function 1
//This function is computing the answer of a raised to the power of b
long MysteryFunction1(long a, int b){
  //Declaring an accumlator to one so that when we do the multiplication we don't get zero everytime becuase zero times anything is going to be zero
  long accumulator = 1;
  //If the integer for b is odd then we can jump into the for loop 
  if (b % 2 == 1) {
      //This for loop iterates through until we get the number of times we need to multiply a
    for (int exponent_counter = 0; exponent_counter < b; exponent_counter++) {
      //Multipling the accumulator once by a since the number passed in for B is odd
      accumulator *= a;
    }
  } 
    //If the number is even the we can go into this else statement do to the multiplication 
  else {
      //Since the number for b is even we know that we need to mulitply the (a*a) once for each time we got an even number
        for (int exponet_counter = 0; exponet_counter < b; exponet_counter += 2) {     //Incrementing by 2
            //Multiplying the accumulator by two since b is an even number 
          (accumulator *= (a * a));
        }
      }
    //returning the accumulator that has the answer of a raised to the power of b.
    return accumulator;
}

//Mystery Function 2
//This function takes in the number and reverses the binary bits
unsigned int MysteryFunction2(unsigned int num){
  //Declaring an integer of Bit_counter to the sizeof num and times 2^3
   unsigned int Bit_counter = sizeof(num)<<3;
    //Declaring an int number_reversed to zero
   unsigned int number_reversed = 0;
  //This for loop itertates throught each bit of num and reverse its bits 
   for(unsigned int index=0; index < Bit_counter; index++){
       //if statement to check to see if index bit is set equal to one
       if((num & (1<<index))){
        number_reversed |= 1 << (Bit_counter-1-index);
       }
   }
    //returning the number_reversed 
    return number_reversed;
}

//MysteryFunction3
//This function takes in an array and the number you want to find and returns the index+1
long MysteryFunction3(long *a, int n){
    //Declaring a position of type long to zero
	long position = 0;
    //assigning the value to a[n-1] 
    position = a[n-1];
    //returning the position
    return position;
}

//MysteryFunction4
//This function counts the number of ones of the unsigned number in binary form
int MysteryFunction4(unsigned long n){
    //Declaring a ones_counter to zero
   int ones_counter = 0;
    //while loop to iterate through until the number is equal to zero
    while(n != 0){
        //Setting the remainder to (n%2) to see if the number is even or odd
        int remainder = (n % 2);
        //If the remainder is odd then you can increment the ones_counter 
        if(remainder == 1){
            ones_counter++;
        }
        //re-setting the number n to its new value
        n = n / 2;
    }
    //returning the ones_counter 
    return ones_counter;
}
//MysteryFunction5
//This function counts the number of one bits when you xor two numbers 
unsigned int MysteryFunction5(unsigned int A, unsigned int B){
    //Setting the int half_result to A ^ B which is the xor of the two numbers
    unsigned int half_result = A ^ B;
    //Setting the ones_counter equal to zero
    unsigned int ones_counter = 0;
    //While loop to iterate through until the hold_result (which is the result of xoring the A and B together) is zero
	while(half_result != 0){
        //If the half_result is odd then you can increment the ones_counter
		if(half_result % 2 ==1){
			ones_counter++;
		}
        //re-setting the half_result to its new value after dividing 
		half_result = half_result / 2;
	}
    //returning the ones_counter
    return ones_counter;
}
