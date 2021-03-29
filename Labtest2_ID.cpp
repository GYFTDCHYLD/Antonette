#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char Description[20];
    int Quantity;
	float Price;	
}Item;
Item List[20];// array to store 20 items											

void Menu();
void Select(int choice); // select function accept one va
void addItem();
void updatePrice();
void printBill();
int index, i;

int main(){
	index = 0;
	for(i = 0; i < 20; i++){
		List[i].Quantity = 0;
	}
	Menu();	
	return 0;
}


void Menu(){ // this function return an int for the option selected to be utilized by the select function  
	
	int option;

    printf("________________________\n");
    printf("|         Menu         |\n");
    printf("|  1. Add Item         |\n");
    printf("|  2. Update Price     |\n");
    printf("|  3. Print Bill       |\n");
    printf("|  4. Exit             |\n");
    printf("|______________________|\n");
    printf(" Choice: ");
	
	scanf("%d", &option);
    
    Select(option);
}



void Select(int choice){// this function use the value returned by the main function 

	switch (choice) {
    case 1: addItem();
			break;
			
    case 2: updatePrice();
			break;
			
    case 3: printBill();
			break;
	case 4: system("exit");
			break;
			
	default:
	    	printf("\n  Invalid Option*");
	}
} 
	

void addItem(){
	if(index == 19){// handle the error if user tries to enter item when list has reach the limit
		printf("The list is full");
	}else{	
		printf("\n Please enter number of item:");
		scanf("%d", &List[index].Quantity);//sstore the data in the correct index of the list
		
		printf("\n Please enter item description:");
		scanf("%s", &List[index].Description);	
	}
	index ++;
	fflush(stdin);
	Menu();
}

void updatePrice(){
	int index = 0;
	while(List[index].Quantity > 0){ 
		printf("\n Please enter price for each %s $: ", List[index].Description);
		scanf("%f", &List[index].Price);
		index ++;
	}
	fflush(stdin);
	Menu();
}

void printBill(){
	int index = 0;
	float total = 0;
	printf(" Quantity \t Description \t Total Cost");
	while(List[index].Quantity > 0){
		printf("%d \t",List[index].Quantity);
		printf("%s \t",List[index].Description);
		printf("%f",List[index].Price * List[index].Quantity);
	}
	fflush(stdin);
	Menu();		
}
