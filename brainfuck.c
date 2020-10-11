//*************************//
//********** PLC **********//
//***** Anthony Asilo *****//
//****** aka pillared *****//
//*************************//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 30000

/* GLOBAL VARIABLES */
char buffer[BUFFER_SIZE];           //buffer that holds brainfuck chars
char printbuff[BUFFER_SIZE];        //buffer that holds the translated chars to print
char loopContents[BUFFER_SIZE];     //buffer that holds brainfuck chars in a loop to later execute
int p = 0;                          //pointer to buffer
int looped = 0;                     //bool [1 | 0] that locks and unlocks inLoop bool
int inLoop = 0;                     //bool [1 | 0] that defines whether in a loop or not
int counter = 0;                    //counter to count characters within a loop, disregarding "[" , "]"
int a;                              //temp var to hold if interpretLoop() returns a success (1)
int printbuffCounter = 0;           //cunter that handles how many chars will be printed.

/* FUNCTION DECLARATIONS */
void execute(char filename[]);                  //execute the brainfuck interpreter from textfile
void interpretOptions(char c);                  //interprets brainfuck chars, decides next move
int interpretLoop(char array[], int x);         //interprets characters within a loop []
void printBuffer(char printbuff[]);             //prints contents of each element in secondary buffer
void reset();                                   //set a buffer to all null; ASCII 0

//main takes text file as argument with the contents of a brainfuck sequence.
int main(int argc, char *argv[]){
    //correct usage
    if(argc!=2){
        fprintf(stderr,"Usage: ./filename <brainfuck.txt>\n");
        return -1;
    }
    printf("Authenticating...\n\n");
    execute(argv[1]);
    printf("You made it to the end:)\n");
    return 0;
}

//starts reading the text file char by char, and interpreting each item
void execute(char arg[]){
    int t;
    FILE *fp;                       //file pointer
    char c;                         // buffer char
    fp = fopen(arg, "r");           //open text file
    do{
        c = getc(fp);               //get next char
        interpretOptions(c);        //interpret char
    }while(c!=EOF);                 //read till no chars left to read (hit an EOF symbol)
    fclose(fp);                     //close
    printBuffer(printbuff);         //print the brainfuck in Integers format and ASCII format.
    printf("\nFCLOSE TERMINATED SUCCESSFULLY\n\n");
}

//interpret recieved char and decide what to do next.
void interpretOptions(char c){
    
    printf("%c := ", c);
    
    //dowhile control conditions
    if(inLoop == 1 && c != ']'){                                    //if you are in loop and have not reached EOL
        loopContents[counter] = c;                                  //set char into a buffer to later execute
        printf("READING LOOP STATEMENT (%c) \n", c);
        counter++;                                                  //count how many chars in current loop
        return;                                                     //do not do other statements. grab new char.
    }if(c == '<'){                                                  //decrease pointer
        --p;
        printf("Decreased pointer. ");
        printf("Pointer = %d \n",p);
    }else if(c == '>'){                                             //increase pointer
        ++p;
        printf("Increased pointer. ");
        printf("Pointer = %d \n",p);
    }else if(c == '+'){                                             //increase contents of pointer
        ++buffer[p];
        printf("Increased pointer contents. ");
        printf("Pointer %d's contents = %d  \n", p, buffer[p]);
    }else if(c == '-'){                                             //decrease contents of pointer
        --buffer[p];
        printf("Decreased pointer contents. ");
        printf("Pointer %d's contents = %d  \n", p, buffer[p]);
    }else if(c == '.'){                                             //print contents of buffer
        printf("Printing pointer contents: ");
        printf("%d \n", buffer[p]);                                 //print Integer value in real-time (aka Debug)
        printf("%d \n", (char)buffer[p]);                           //print ASCII value in real-time (aka Debug)
        printbuff[printbuffCounter] = buffer[p];                    //store contents in buffer to print at end
        printbuffCounter++;                                         //increase pointer for printbuffer
    }else if(c == ','){                                             // set contents of pointer
        printf("Setting pointer contents from %d to ",buffer[p]);
        buffer[p] = c;
        printf("%d \n", buffer[p]);
    }else if(c == '['){                                             //loop start
        printf("INTERPRETING LOOP... \n");
        looped = 1;                                                 //set bool true as you enter loop for control
        counter = 0;                                                //set counter for values inside loop bounds.
    }else if(c == ']'){                                             //loop end
        looped = 0;                                                 //set bool false as loop has terminated
        printf("\nEXECUTING LOOP... \n");
        a = interpretLoop(loopContents, p);
        reset();
    }else{
        printf("FATAL ERROR: SYNTAX NOT  PREVIOUSLY DEFINED\n");      //if not a brainfuck char,
        return;                                                     //throw exception and continue.
    }
    if(looped == 1){                                                //if you are in loop,
        inLoop = 1;                                                 //set bool to 1 to grab next var, not [
    }else if(looped == 0){                                          //if you are not in loop
        inLoop = 0;                                                 //you are not in loop
    }
}

//takes a buffer with contents inside loop
// and pointer of brainfuck buffer
// and returns a success if completed
int interpretLoop(char array[], int x){
    int ptr = x;                                //create copy of current pointer in brainfuck
    inLoop = 0;                                 //make sure not stuck
    while(buffer[ptr] > 0){                     //while contents of current pointer are not 0
        for(x = 0; x < counter; x++){           //loop invariant = loop counter "counter"
            interpretOptions(array[x]);         //interpret all loop characters
        }
    }
    printf("\nLOOP HAS TERMINATED SUCCESSFULLY\n\n");
    return 1;
}

//set all elements of buffer to 0
void reset(){
    int i;
    for(i = 0; i < BUFFER_SIZE; i++){
        loopContents[i] = 0;
    }
}

//print Integer form and ASCII form of brainfuck program.
void printBuffer(char buffer[]){
    int z;                                      //just another counter
    printf("INTEGERS:\n");
    for(z = 0; z < BUFFER_SIZE; z++){
        if(buffer[z] != 0){                     //if an actual value in the buffer
            printf("[%d] ", buffer[z]);         //print the integer value
        }
    }printf("\nASCII VALUES:\n");
    for(z = 0; z < BUFFER_SIZE; z++){
        if(buffer[z] != 0){                     //if an actual value in the buffer
            printf("%c", (char)buffer[z]);      //print the ASCII value
        }
    }printf("\n");
    
}
