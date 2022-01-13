#include <stdio.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>
#define centinela '#'
#define finCadena '\0'


/*
	Regex asignada -->  [0-9]+F|[0-9]\.[01]? Centinela: #
	
	Matriz que representa al AFD mínimo -->        /  n° / 'F' / '.' /  0  /  1  /  (FUE COMPLETADA CON '5' COMO ESTADO DE RECHAZO)
	                                               -------------------------------
                                                0- /  1  /  5  /  5  /  5  /  5  /                          
                                                1  /  2  /  3  /  4  /  5  /  5  /
                                                2  /  2  /  3  /  5  /  5  /  5  /
                                                3+ /  5  /  5  /  5  /  5  /  5  /
                                                4+ /  5  /  5  /  5  /  3  /  3  /
                                                5  /  5  /  5  /  5  /  5  /  5  /
*/ 


void vaciar (char *cad);

int main(){
	setlocale(LC_ALL, ""); 
	int estado =0; int d=0;
	char cadena [100]; char *p; 
	
	while(d==0){
		vaciar(cadena);
		int cont = 0;
		printf("Ingresá la cadena a evaluar: ");
		scanf("%s", cadena);
		printf("\nLa cadena a evaluar es: %s\n", cadena);
		p=cadena;
		
		while(*p != finCadena){	
			while(*p != centinela && *p != finCadena){
				printf("%c", *p);
				switch(estado){
					case 0:
						if(isdigit(*p)){
							estado = 1;
							p++;
						} else {
							estado = 5;
							p++;
						}
						break;
					case 1:
						if(isdigit(*p)){
							estado = 2;
							p++;
						} else {
							if(*p=='F'){
								estado = 3;
								p++;
							} else {
								if(*p=='.'){
									estado = 4;
									p++;
								} else {
									estado = 5;
									p++;
								}
							}
						}
						break;
					case 2:
						if(isdigit(*p)){
							p++;
						} else {
							if(*p=='F'){
								estado = 3;
								p++;
							} else {
								estado = 5;
								p++;
							}
						}
						break;
					case 3:
						estado = 5;
						p++;
						break;
					case 4:
						if(*p=='0' || *p=='1'){
							estado = 3;
							p++;
						} else {
							estado = 5;
							p++;
						}
						break;
					case 5:
						p++;
						break;
				}
			}
			
			if(estado==3 || estado==4){
				cont++;
				printf("--> Es palabra del lenguaje (número %d)\n", cont);
			} else {
				printf("--> No es palabra del lenguaje\n");
			}
			p++; estado=0;
		}
		
		printf("\n\nDesea ingresar otra cadena? (0/1) ");
		scanf("%d", &d);
	}
}

void vaciar(char *cad){
	for(int i=0; i<100; i++){
		cad[i] = finCadena;	
	}
}

