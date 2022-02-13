#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <math.h>

#define MAXCHAR 1000

// Customer Struct
struct Registrasi{
    char customerName[50];
    char dateOfBirth[11];
    char placeOfBirth[30];   
    char email[100];
    char phoneNumber[20];
    char nationality[20];
    int saldo;
    char password[50];
};

struct DataTxt{
    char userName[255];
    char password[255];
};

// Variable GLOBAL
int jlhuser = 0;
int indexLoginSekarang = -1;
int saldo = 0;
int valid = 0;
int flagEmail = 0;
int cekEmail = 0;

// Struct GLOBAL
Registrasi customer[100];
DataTxt customer2[100];

// Method tampilan e-Money
int asciiArt();
void menuPage();
void loginPage();
void registerPage();
void interfacePage(int indexLoginSekarang);
void topUpPage(int indexLoginSekarang);
void transferPage(int indexLoginSekarang);
void transferMoney();

// Method tambahan untuk e-Money
void clrscr();
void displayAllEmail();
char email[50];
void checkEmail(char email[]);
void checkEmail(char str[]);
void scanEmail();

// fungsi int main dimulai dari sini

int main(){
	
//	ini untuk load data2 nya supaya engga harus daftar berulang2
    scanEmail();
    menuPage();

    return 0;
}

// semua fungsi ada dibawah sini
// fungsi untuk memanggil ASCII ART
// ini sudah aman

int asciiArt(){
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "ascii_art.txt";

    fp = fopen(filename,"r");
    if(fp == NULL){
        printf("Could not open the file %s" , filename);
        return 1;
    }
    while(fgets(str,MAXCHAR,fp)!=NULL){
        printf("%s",str);
    }
    fclose(fp);
}

// fungsi dari registerPage

void registerPage(){
    // panggil ascii art
    asciiArt();
    char name[50],dateOfBirth[50],nationality[50];
    char placeOfBirth[50],phoneNumber[50];
    printf("Please register here! \n");
        printf("Name                        : ");
        scanf(" %[^\n]s",&name);
        while(1){
            printf("e-Mail                      : ");
            scanf(" %[^\n]s",&email);
            checkEmail(email);
            if(flagEmail == 1){
            	break;
			}
        }
        printf("Date of Birth (dd-mm-yyyy)  : ");
        scanf(" %[^\n]s",&dateOfBirth);
        printf("Nationality                 : ");
        scanf(" %[^\n]s",&nationality);
        printf("Place of Birth              : ");
        scanf(" %[^\n]s",&placeOfBirth);
        printf("Phone Number                : ");
        scanf(" %[^\n]s",&phoneNumber);
        printf("Password                    : ");
        const int maxPasswordLength = 50;
        char password[maxPasswordLength+1];
        char ch;
        int characterPosition = 0;
            while(1){
                ch = getch();
                if(ch == 13){ // ketika user ketika ENTER button kita keluar loop
            break;
        } else if(ch == 8){ // when the user hit backspace key
            if(characterPosition > 0){
                characterPosition--;
                password[characterPosition] = '\0';
                printf("\b \b");
            }
        } else if(ch == 32 || ch == 9){ // when the user hits backspace or tab key
            continue;
        } else{
            if (characterPosition < maxPasswordLength){
                password[characterPosition] = ch;
                characterPosition++;
                printf("*");
            } else{
                printf("\n Your input exceeds maximum password length of %d , so only first %d of the character will be considered",maxPasswordLength,characterPosition);
                break;
            }
        }
    }

    password[characterPosition]='\0';
    if(strlen(password) == 0){
        printf("No password entered\n");
    }
        strcpy(customer[jlhuser].customerName,name);
        strcpy(customer[jlhuser].email,email);
        strcpy(customer[jlhuser].dateOfBirth,dateOfBirth);
        strcpy(customer[jlhuser].nationality,nationality);
        strcpy(customer[jlhuser].placeOfBirth,placeOfBirth);
        strcpy(customer[jlhuser].phoneNumber,phoneNumber);
        strcpy(customer[jlhuser].password,password);
        customer[jlhuser].saldo=0;
        jlhuser++;
        FILE *fp = fopen("data.txt","a");
//        FILE *fp2 = fopen("data pengguna.txt","a");
			fputs("{",fp);
//			fputs("{",fp2);
		    fprintf(fp,"%s;",name);
		    fprintf(fp,"%s;",email);
//		    fprintf(fp2,"%s;",email);
		    fprintf(fp,"%s;",dateOfBirth);
		    fprintf(fp,"%s;",nationality);
		    fprintf(fp,"%s;",placeOfBirth);
		    fprintf(fp,"%s;",phoneNumber);
		    fprintf(fp,"%s;",password);
//		    fprintf(fp2,"%s;",password);
//		    fprintf(fp2,"%d;}",customer[jlhuser].saldo);
//		    fputs("}\n",fp2);
		    fputs("}\n",fp);
        fclose(fp);
//        fclose(fp2);
        getchar();
        printf("\nYour data was recorded!\n");
        getchar();
        system("cls");
        menuPage(); 
}

// bagian menuPage dimana ini merupakan perkenalan awal dari USER INTERFACE

void menuPage(){
    asciiArt();
    printf("|             Kelompok 1 - e-Money              |\n");
    printf("|                                               |\n");
    printf("| 1. Register                                   |\n");
    printf("| 2. Login                                      |\n");
    printf("| 0. Exit                                       |\n");
    printf("=================================================\n");
    printf(" Please enter which option do you want : ");
    int menuInput;
    scanf("%d",&menuInput);
    if(menuInput == 1){         // jika input == 1 , maka akan membuka registerPage
        system("cls");
        registerPage();
    }
    else if(menuInput == 2){    // jika input == 2 , maka akan membuka loginPage
        system("cls");
        loginPage();
    }
    else if(menuInput == 0){    // jika input == 0 , maka akan closeProgram
    	 printf("%d",jlhuser);
        // for(int i=0;i<jlhuser;i++){
        // printf("%s\n",customer[i].customerName);
        // }
        exit(0);
    }
    else{                       // diluar dari itu akan diminta input ulang dimana akan dibawa kembali ke Menupage
        printf("Sorry your input was unavailable\n");
        getchar();
        getchar();
        system("cls");
        menuPage();
    }
}

void loginPage(){
    char email[100];
    asciiArt();
    printf("Input '0' (without quoted) to out from this operation\n");
    int index;
    while(1){
        printf("e-Mail      : ");
        scanf(" %[^\n]s",&email);
        // kalau user berikan input 0 maka akan clearscreen dan balik ke menuPage
        if(strcmp(email,"0") == 0){
        	system("cls");
            menuPage();
            break;
        }
        int flag = 0;
        for(int i=0;i<jlhuser;i++){
            if(strcasecmp(email,customer[i].email)==0){
                index = i;
                flag = 1;
                break;
            }
        }
        if(flag){
            break;
        }
        printf("eMail unregistered!\n");
    }

    while(1){
        printf("Password    : ");
        int maxPasswordLength = 50;
        char password[maxPasswordLength+1];
        char ch;
        int characterPosition = 0;
            while(1){
                ch = getch();
                if(ch == 13){ // ketika user ketika ENTER button kita keluar loop
                break;
            } else if(ch == 8){ // when the user hit backspace key
                if(characterPosition > 0){
                    characterPosition--;
                    password[characterPosition] = '\0';
                    printf("\b \b");
                }
            } else if(ch == 32 || ch == 9){ // when the user hits backspace or tab key
                continue;
            } else{
                if (characterPosition < maxPasswordLength){
                    password[characterPosition] = ch;
                    characterPosition++;
                    printf("*");
                }
            }
        }
        password[characterPosition]='\0';
        if(strcmp(password,customer[index].password) == 0){
            break;
        }
        printf("\nWrong Password!\n");
    }
    indexLoginSekarang = index;
    printf("\nSuccessfully Logged In\n");
    getchar();
    system("cls");
    interfacePage(indexLoginSekarang);
}

void interfacePage(int indexLoginSekarang){
    // panggil ascii art
    asciiArt();
    int flag = 1;
    // deklarasi variable dengan namaCustomer sebagai char array
    char namaCustomer[255];

    strcpy(namaCustomer,customer[indexLoginSekarang].customerName);

    printf("Welcome back Mr/Mrs. %s \n",namaCustomer);
    printf("Your balance : Rp. %d \n",saldo);
    printf("=================================================\n");
    printf("|1. Top Up                                      |\n");
    printf("|2. Transfer                                    |\n");
    printf("|0. Abort all operation and exit the program    |\n");
    printf("=================================================\n");
    int interfaceInput;
    printf("Please enter which option do you want : ");
    scanf("%d",&interfaceInput);
    if(interfaceInput==1){
        system("cls");
        topUpPage(indexLoginSekarang);
    }
    else if(interfaceInput==2){
        system("cls");
        transferPage(indexLoginSekarang);
    }
    else if(interfaceInput==0){
        exit(0);
    }
    else{
        printf("Input was not available!\n");
        getchar();
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
}

void topUpPage(int indexLoginSekarang){
    asciiArt();
    printf("Welcome to the top up station!");
    printf("\nHow much do you want to top up?");
    printf("\n=================================================");
    printf("\n[1] Rp. 10.000");
    printf("\n[2] Rp. 20.000");
    printf("\n[3] Rp. 50.000");
    printf("\n[4] Rp. 100.000");
    printf("\n[5] Rp. 250.000");
    printf("\n[6] Rp. 1.000.000");
    printf("\n[7] Return to Home");
    printf("\n[0] EXIT PROGRAM");
    printf("\n=================================================");
    printf("\nPlease enter which option do you want : ");
    int topUpInput;
    scanf("%d",&topUpInput);
    if(topUpInput==1){
        saldo += 10000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 10.000\n");
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==2){
        saldo += 20000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 20.000\n");
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==3){
        saldo += 50000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 50.000\n");
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==4){
        saldo += 100000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 100.000\n");
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==5){
        saldo += 250000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 250.000\n");
        getchar();
        system("cls");
       	topUpPage(indexLoginSekarang);
    }
    else if(topUpInput==6){
        saldo += 1000000;
        customer[indexLoginSekarang].saldo = saldo;
        printf("Your balance have been successfully added Rp. 1.000.000\n");
        getchar();
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==7){
        system("cls");
        interfacePage(indexLoginSekarang);
    }
    else if(topUpInput==0){
        exit(0);
    }
    else{
        printf("\nYour input was invalid!");
        getchar();
        getchar();
        system("cls");
        topUpPage(indexLoginSekarang);
    }
}

void transferPage(int indexLoginSekarang){
	asciiArt();
    char namaCustomer[255];
    strcpy(namaCustomer,customer[indexLoginSekarang].customerName);
	printf("              M-Banking Transfer");
    printf("\n=================================================");
    printf("\nDear Mr/Mrs. %s\n",namaCustomer);
    printf("Your current balance is : %d\n",saldo);
    printf("[1] Transfer Money to another user (must input email!)\n");
    printf("[2] Display all the email\n");
    printf("[3] Return to Home\n");
    printf("[0] Abort all operation and exit program\n");
    printf("=================================================\n");
    printf("\nPlease enter which option do you want : ");
    int transferPageInput;
    scanf("%d",&transferPageInput);
    if(transferPageInput==1){
        system("cls");
        transferMoney();
    }
    else if(transferPageInput==2){
    	system("cls");
    	displayAllEmail();
	}
	else if(transferPageInput==3){
		system("cls");
		interfacePage(indexLoginSekarang);
	}
	else if(transferPageInput==0){
		system("cls");
		exit(0);
	}
	else{
		printf("Your input was invalid!");
		getchar();
		getchar();
		system("cls");
		transferPage(indexLoginSekarang);
	}
}

void transferMoney(){
    asciiArt();
    char email[255];
    int money;
    printf("              M-Banking Transfer");
    printf("\n=================================================");
    while(1){
    	printf("\nEnter the user email destination : ");
    	scanf(" %[^\n]s",&email);
    	for(int i=0;i<jlhuser;i++){
    		if(strcmp(email,customer[i].email)==0){
    			valid = 1;
    			break;
			}
			else{
				valid = 0;
			}
		}
		if(valid==1){
			printf("Email valid!\n");
			break;
		}
		else{
			printf("Email tidak valid!\n");
		}
	}
    printf("\nEnter the nominal you want to transfer : ");
    scanf("%d",&money);
    if(saldo-money<=0){
        printf("Your balance is insufficient!\n");
        getchar();
        getchar();
        system("cls");
        transferMoney();
    }
    else{
        printf("Transferred Successfully!\n");
        saldo = saldo - money;
        system("cls");
        interfacePage(indexLoginSekarang);
    }
}

void displayAllEmail(){
	printf("List Email :");
	printf("\n=================================================");
	for(int i=0;i<jlhuser;i++){
		printf("\n%s with username %s\n",customer[i].email,customer[i].customerName);
	}
	printf("\n");
	printf("\n=================================================");
	printf("\n\nPress Enter and back to Transfer Menu!");
	getchar();
	getchar();
	system("cls");
	transferPage(indexLoginSekarang);
}

void checkEmail(char str[]){
	for(int i=0;i<=strlen(str)-1;i++){
		if(str[i]==64){
			flagEmail = 1;
            break;
		}	
		flagEmail = 0;
	}
    (flagEmail == 1)? printf("Email Valid\n") : printf("Email tidak valid!\n");
}
unsigned long CheckFile(){
    unsigned long size;
    FILE *file;;
    if(file = fopen("data.txt","r")){
        fseek(file,0L,SEEK_END);
        size = ftell(file);
        fclose(file);
    }
    return size;
}

 void scanEmail(){
	if(CheckFile()>0){
        FILE *fp = fopen("data.txt","r");
        
        if(fp==NULL){
            menuPage();
        }
            
        while(fscanf(fp,"{%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];}\n",&customer[jlhuser].customerName,&customer[jlhuser].email,&customer[jlhuser].dateOfBirth,&customer[jlhuser].nationality,&customer[jlhuser].placeOfBirth,&customer[jlhuser].phoneNumber,&customer[jlhuser].password)!=EOF){
            jlhuser++;
        }
        
        fclose(fp);
    }
}



