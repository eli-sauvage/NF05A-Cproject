#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char fullName[100];
    int age;
    int year;
    char field[100];
    int interests[8];
}User;

typedef struct{
    User user;
    User *follows;
    int followNumber;
}userFollow;

void addFollow(User userToFollow, userFollow user){
    user.followNumber++;
    size_t UserSize = sizeof (*user.follows);
    if(user.follows == NULL){//if not following anyone
        user.follows = malloc(user.followNumber * UserSize);
    }else{
        User *tmp = realloc(user.follows, user.followNumber * UserSize);
        if(tmp != NULL) user.follows = tmp;
        else{
            printf("c'est la merde\n");
            return;
        }
    }
    user.follows[user.followNumber-1] = userToFollow;
}

void createFile(userFollow *userDatabase[],int userPerLetter[]){
    FILE *fichier = NULL;
    fichier = fopen("save2", "w+");
    for(int lettre=0;lettre<26;lettre++){
        fprintf(fichier, "%c\n\t", (char)(lettre+65));

    }
}

void addUserToDb(userFollow user, userFollow *userDatabase[], int userPerLetter[], int index){
    userPerLetter[index]++;
    if(userDatabase[index] == NULL){//if not following anyone
        userDatabase[index] = malloc(userPerLetter[index] * sizeof * userDatabase[index]);
    }else{
        userFollow *tmp = realloc(userDatabase[index], userPerLetter[index] * sizeof * userDatabase[index]);
        if(tmp != NULL) userDatabase[index] = tmp;
        else{
            printf("c'est la merde\n");
            return;
        }
    }
    userDatabase[index][userPerLetter[index]-1] = user;
}

int main(){
    userFollow user1;strcpy(user1.user.fullName,"adfgsd");
    userFollow user2;strcpy(user2.user.fullName,"bfgdfqsfd");
    userFollow user3;strcpy(user3.user.fullName,"zfgfd");
    //declaration database
    int userPerLetter[26];
    for(int i=0;i<26;i++)userPerLetter[i]=0;
    userFollow *userDatabase[26];
    addUserToDb(user1, userDatabase, userPerLetter, 0);
    // addUserToDb(user2, userDatabase, userPerLetter, 0);
    // addUserToDb(user3, userDatabase, userPerLetter, 25);

    createFile(userDatabase,userPerLetter);
    return 0;
}
