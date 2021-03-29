#include <stdio.h>
#include <stdlib.h>
//Antoinette Ranger

int MAXIMUM = 50;

typedef struct{
    int bookId;
    char bookName[30];
    char bookStatus;
    char bookLocation;	
}book;
book ListOfBooks[50];										

void mainMenu();
void menuOption(int key);
void addBook();
void loanBook();
void viewBooks();

int currentId = 1;

int main(){
	int i = 0;
	while(i < MAXIMUM){
		ListOfBooks[i].bookId = 0;
		i++;
	}
	mainMenu();	
	return 0;
}


void mainMenu()
{ 
	int choice;
    printf(" 1. Add Book    \n");
    printf(" 2. Loan Book   \n");
    printf(" 3. View Books  \n");
    printf(" 4. Exit        \n");
    printf("                \n");
    printf(" Select an Option: ");
	scanf("%d", &choice);
    menuOption(choice);
}



void menuOption(int key)
{
    if(key == 1)
    {
        addBook();
    }
    else if (key == 2)
    {
        loanBook();
    }
    else if(key == 3)
    {
        viewBooks();
    }
     else if(key == 4)
    {
       printf("\n  Exit!");  
    }
    else
    {
      printf("\n  Invalid Option!!!");  
    }
    fflush(stdin);
	mainMenu();
} 
	

void addBook()
{
	if(currentId == MAXIMUM)
	{
		printf("The shelf cannot hold anymore books");
	}
	else
	{	
		printf("\n Your Book ID is : %d",currentId);
	
		printf("\n Please enter name of book:");
		scanf("%s", ListOfBooks[currentId-1].bookName);
		printf("\n Please enter location to store book, Shelf:");
		scanf("%s", &ListOfBooks[currentId-1].bookLocation);
		ListOfBooks[currentId-1].bookId = currentId;
		ListOfBooks[currentId-1].bookStatus = 'A';
	}
	currentId ++;
}

void loanBook()
{
	int i = 0;
	int key;
	int found = 0;
	printf("\n Please Id# of book wish to loan: ");
	scanf("%d", &key);
	while(ListOfBooks[i].bookId > 0)
	{
	    if(ListOfBooks[i].bookId == key && ListOfBooks[i].bookStatus == 'A')
	    {
	        ListOfBooks[i].bookStatus = 'L';
	        found = 1;
	    }
		i++;
	}
	if(found == 1)
	{
	   printf("\n Book was Loaned successfully: "); 
	}
}

void viewBooks()
{
	int i = 0;
	printf(" Id   \t   Name \t Location \t  Status\n");
	do
	{
	    if(ListOfBooks[i].bookId != 0)
	    {
    		printf("  %d ",ListOfBooks[i].bookId);
    		printf("\t %s \t",ListOfBooks[i].bookName);
    		printf("\t %c \t\t",ListOfBooks[i].bookLocation);
    		printf("%c \n",ListOfBooks[i].bookStatus);
	    }
		i++;
	}while(i < MAXIMUM);	
}
