#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * \mainpage Smart Parking documentation
 * \section intro Introduction
 * This project was created for the NF05A course <br/>
 * Original instructions : <a href="../Project_Smart_Parking.pdf">Project_Smart_Parking.pdf</a>
 * \section install Installation
 * \subsection run To run the project
 * the binaries are available for Windows (project.exe) and for Linux (project.o)
 * \subsection compile To compile the project
 * you just have to compile project.c (with gcc, preferably)
 * 
*/
/**
  *  \file project.c
   * \brief This is the main file of the project
   * \author THARAUD Valentin & SAUVAGE Eli
   * \version 1.0
   * \date 25/04/2021
*/


/**
 *\fn void create_parking()
 *\brief Prodedure that creates the file of the parking <br/>
 *
 * by default, the file is filled with 0, which mean that every slot is available
 * */
void create_parking ()
{
    FILE *parking = NULL;
    parking=fopen("parking_slots.txt","w");
    for (int i=1;i<=100;i++)
    {
        fprintf(parking,"%d:0\n",i);
    }
    fclose(parking);
}

/**
 * \fn int check_slot(int slot_number)
 * \brief This function checks if a specific slot is taken or not
 * \param slot_number the number of the slot for which the availability is checked
 * \return 0 if available, 1 if taken
 * \note the file has to exist for this function to work
 * */
int check_slot(int slot_number)
{
    int i,availability ;
    //this variable is going to stock the line
    char line[5];
    //we open the file
    FILE *parking = NULL;
    parking=fopen("parking_slots.txt","r");

    //we are getting to the slot asked by the user reading each line but storing only the last one
    for(i=0;i<slot_number;i++)
    {
        fscanf(parking,"%s",line);
    }
    i=0;
    //until we find the character ':'
    while(line[i]!=':')
    {
        i++;//we increase the position in the line
    }
    //line[j+1] is basically the character that follows : 0 or 1
    if(line[i+1]=='0')//if '0' : available
    {
       availability=0;
        return availability;
    }
    else//if '1' : Not available
    {
        availability=1;
        return availability;
    }

    //we close the file
    fclose(parking);

}
/**
 * \fn void all_slots()
 * \brief This procedure displays every slot that is available
 *
 * \note the file has to exist for this function to work
 * */
void all_slots()
{
    int i, j;
    char line[6];
    FILE* parking = NULL;
    parking = fopen("parking_slots.txt","r");//we open the file
    //we are checking each slot to see if it s available
    for(i=1;i<=100;i++)
    {
        //we get the line
        fscanf(parking,"%s",line);
        j=0;
        while (line[j]!=':')//until we find the character ':'
        {
            j++;//we increase the position in the line
        }
        //line[j+1] is basically the character that follows : 0 or 1
        if(line[j+1]=='0')//if '0' : available
            printf("%d\n",i);//we print the number of the parking slot
    }
    //we close the file
    fclose(parking);
}
/**
 * \fn void all_slots_graphic()
 * \brief This procedure displays every slot in a graphic way <br/>
 * the "graphic" table is created thanks to the extended ascii character, which are supported by the c language and the printf function
 * 
 * \note the file has to exist for this function to work
 * */
void all_slots_graphic(){
    //first line
    printf("%c%c%c%c", 218, 196, 196, 196);//┌───
    for(int i=0; i<8; i++)printf("%c%c%c%c", 194, 196, 196, 196);//┬───
    printf("%c%c%c%c%c\n",194, 196,196,196, 191);//┬───┐
    for(int j=0; j<100; j+=10){
        for(int i=1; i<=10; i++){
            printf("%c", 179);//│
            int slotNb = i+j;
            if(slotNb<10)
                printf("  %d", slotNb);
            else if(slotNb==100)
                printf("%d", slotNb);
            else printf(" %d", slotNb);
        }
        printf("%c\n", 179);//│
        for(int i=1; i<=10; i++){
            printf("%c", 179);//│
            if(check_slot(i+j)==1)
                printf("%c%c%c", 177, 177, 177);//▒
            else
                printf("   ");
        }
        printf("%c\n", 179);//│
        if(j==90)break;//in order to close the table
        printf("%c%c%c%c", 195, 196, 196, 196);//├───
        for(int i=0; i<8; i++)printf("%c%c%c%c", 197, 196, 196, 196);//┼───
        printf("%c%c%c%c%c\n",197, 196,196,196, 180);//┼───┤
        //printf("%c\n", 179);//│ 
    }
    printf("%c%c%c%c", 192, 196, 196, 196);//└───
    for(int i=0; i<8; i++)printf("%c%c%c%c", 193, 196, 196, 196);//┴───
    printf("%c%c%c%c%c\n",193, 196,196,196, 217);//┴───┘
}
/**
 * \fn void numberOfAvailable()
 * \brief This procedure displays the number of available slots
 * 
 * \note the file has to exist for this function to work
 * */
void numberOfAvailable(){
    int i;
    int available = 0;
    char line[5];
    FILE* parking = NULL;
    parking=fopen("parking_slots.txt","r");//we open the file
    for(i=0;i<100;i++){//for every slot
        fscanf(parking,"%s",line);//we get the entire line in the variable line
        int j=0;
        while (line[j]!=':')//until we find the character ':'
        {
            j++;//we increase the position in the line
        }
        //line[j+1] is basically the character that follows : 0 or 1
        if(line[j+1]=='0')//if '0' : available
            available++; //we increase the number of available slots
    }
    printf("there are %d available slots\n", available);//we display the result
    fclose(parking);//we close the file
}
/**
 * \fn void change_slot(int slot, char state)
 * \brief The goal of this procedure is to change the value of a specific slot
 * \param slot this is the slot to change
 * \param state this is the new state. Its value should be either '0' or '1'
 *
 * \note the file has to exist for this function to work
*/

void change_slot(int slot, char state){
    FILE *parking = NULL;
    parking = fopen("parking_slots.txt","r+");//we open the file
    int lineNb = 1;
    //the slot number is the line, so we just need to go through the right number of lines
    while(lineNb < slot){
        if(fgetc(parking)=='\n')lineNb++;//if we meet a '\n', it means we reached the end of a line
    }
    // fseek(parking, 0, SEEK_CUR);
    fseek(parking, (slot<10?2:3), SEEK_CUR);
    if(slot==100)fseek(parking, 1, SEEK_CUR);//one more character
    fputc(state, parking);
    fclose(parking);
}
/**
 * \fn void makeReservation()
 * \brief This procedure allows the user to book a specific slot if it is not already taken
 * 
 * */
void makeReservation(){
    int slot_number;
    printf("Which slot do you want to reserve?\n");
    scanf("%d",&slot_number);
    while(slot_number<1 || slot_number>100)//while the slot is invalid
    {
        printf("Error the slot is out of range, please try again \n");
        scanf("%d",&slot_number);//we ask the user again to enter the slot
    }
    if(check_slot(slot_number)){//slot not available
        printf("sorry, the slot is already taken\n");
        makeReservation();//we ask again
    }
    change_slot(slot_number, '1');
}

/**
 * \fn void free_slot()
 * \brief This procedure allows the user to free a specific slot if it is not already available
 * 
*/
void free_slot(){
    int slot_number;
    printf("Which slot do you want to free?\n");
    scanf("%d",&slot_number);
    while(slot_number<1 || slot_number>100)//while the slot is invalid
    {
        printf("Error the slot is out of range, please try again \n");
        scanf("%d",&slot_number);//we ask the user again to enter the slot
    }
    if(!check_slot(slot_number)){//slot not available
        printf("sorry, the slot is already empty\n");
        makeReservation();//we ask again
    }
    change_slot(slot_number, '0');
}



/**
 * \fn int main()
 * \brief this is where the program starts
 * \return 0 for "no error" code
 * \p p a list of every possible option is printed to the user
 * */
int main()
{
    int features, slot_number;
    int continue_loop = 1;
    while(continue_loop==1){
        // we initialize the parking
        if(access("parking_slots.txt", F_OK) != 0){//if file doesn't exist
            create_parking();
        }
        // this is the interface for the user
        printf("Hello and welcome to the smart parking reservation system !\n\nChoose one of the following options by entering 1, 2, 3 or 4 : \n\n1-Check the availability of a specific car slot\n\n2-Display all available car slots\n\n3-Display the parking in a graphic way\n\n4-Display the number of available car slots \n\n5-Make a reservation \n\n6-Free a slot\n\n");
        //the user choose an option
        printf(">>>");
        scanf("%d",&features);
        while(features<1 || features>6)
        {
            int c;while((c = getchar()) != '\n' && c != EOF){}//this line allows to empty the input, that way we can't get stuck in this while loop
            printf("Error during the selections of the option please try again \n");
            printf(">>>");
            scanf("%d",&features);
        }
        switch (features)
        {
            case 1://asking for the user
                printf("Which slot do you want to check the availability ?\n");
                scanf("%d",&slot_number);
                //checking if his response is acceptable
                while(slot_number<1 || slot_number>100)
                {
                    printf("Error the slot is out of range, please try again \n");
                    scanf("%d",&slot_number);
                }
                if (check_slot(slot_number)==0)
                    printf("Available\n");
                else
                    printf("Not Available\n");
                break;
            case 2:all_slots();
                break;
            case 3:all_slots_graphic();
                break;
            case 4:numberOfAvailable();
                break;
            case 5:makeReservation();
                break;
            case 6:free_slot();
                break;
        }
        printf("\nDo you want to do anything else? 1-yes 2-no\n");
        printf(">>>");
        while(continue_loop<1 || continue_loop>2)
        {
            printf("Error during the selections of the option please try again \n");
            printf(">>>");
            scanf("%d",&continue_loop);
        }
        scanf("%d", &continue_loop);
    }
}
