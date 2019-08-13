#include <stdio.h>
#include <stdlib.h>
int i, user_input, randum = 0;
int x = 30;
int main(int argc, char **argv) {
	printf("\n\n Ingrese el numero de repeticiones : ");
	scanf("%d", &user_input);

	for (i = 1; i <= user_input ; i++){
		randum = rand() % 6 + 1;
		if (x + randum == 31){
			printf("\033[0;31m"); //Set the text to the color red
			printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i); //Display Hello in red
			printf("\033[0m");
		}else if (x + randum == 32){
				printf("\033[0;32m"); //Set the text to the color blue
                printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
                printf("\033[0m");
		}else if (x + randum == 33){
				printf("\033[0;33m"); //Set the text to the color blue
                printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
                printf("\033[0m");
		}else if (x + randum == 34){
				printf("\033[0;34m"); //Set the text to the color blue
                printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
                printf("\033[0m");
		}else if (x + randum == 35){
				printf("\033[0;35m"); //Set the text to the color blue
                printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
                printf("\033[0m");
		}else if (x + randum == 36){
				printf("\033[0;36m"); //Set the text to the color blue
                printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
                printf("\033[0m");
		}else{
				printf("\n\n #%d FSE2020-1 Caballero Ft De La Cruz", i);
		}
	}
	printf("\n");
	return 0;
}
