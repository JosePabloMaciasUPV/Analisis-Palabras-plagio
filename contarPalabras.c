#include <stdio.h>
#include <stdlib.h>



//Descripición de funciones:

//strlen obtiene la longitud de la cadena
//strcpy es para guardar una cadena en un array
//strcmp es para comparar cadenas
//rewind es para ir al inicio del archivo 
//fopen es para abrir un archivo
//system("cls") es para limpiar la pantalla
//feof sirve para comprobar si llego al final del archivo
//fscanf sirve para leer partes del archivo 
//fclose sirve para cerrar el archivo
//toupper sirve para convertir un carácter en mayuscula



// El simbolo de apostrofo original es este: '''''''''''''''


void analisis();
void analizarLasPalabrasMasUtilizadas(char cad[]);
void analisisPlagio();
void analizar();
int main(int argc, char** argv)
{
	
	char stopWords[200] ;
	char dirArchivoAnalizar[200];
	int opcion=0;
	printf("****Bienvenido este programa sirve para contar las palabras claves\n");
	printf("en un documento de texto****");
	printf("Introduce una opcion:\n");
	printf("1)Archivos en carpeta predeterminada stopw.txt y analisis.txt \n");
	printf("2)Analizar Plagio \n");
	printf("3)Salir  \n");
	printf("Tu Opcion: ");
	scanf("%i", &opcion);
	system("cls");
	
	
	
	switch(opcion){
		case 1:
			analisis();
			break;
		case 2:
			analizar();
			break;	
		case 3:
			return 0;
			
		default:
			printf("Opcion Invalida");		
	}
	return 0;
}


void analisis(){//Abrir archivo Stop Words	
	//Variables locales de la funcion
	char palabra[120];
	int contador=0;
	int contadorDiferentes=0;
	int i=0,j=0,k=0;
	int longitudMaxima=0;
	int cantPalabrasInvalidas=0;
	int cantPalabrasValidas=0;
	
	
	
	FILE *fpSW;
	fpSW = fopen ( "stopwords.txt", "r" );  
	//Comprobar existencia del archivo    
	if (fpSW==NULL) {fputs ("File error",stderr); exit (1);}
	
	
	//Analizar el archivo stop Words
	rewind(fpSW);//Vuelve al inicio del archivo de texto
	for( i=1;i<1000;i++){
		if(feof(fpSW)){
            break;
        }
        fscanf(fpSW, "%s ", palabra);
        contador++;
        if(strlen(palabra)>longitudMaxima){
        	longitudMaxima=strlen(palabra);
		}
    }
	//printf("La cantidad de palabras stop es: %i , la longitud maxima es : %i \n",contador,longitudMaxima);
	
	
	
	
	
	//Guarda las palabras Stop en un arreglo
	char arregloDeCadena[contador][longitudMaxima+2]; //Aquí se guardan las stop words
	int contadorStopWords[contador];//Aqui se guardarán las veces que se repite stop words
	int ordenarMenoraMayor[contador];//Aqui se guardanán ordenadamente el indice de las stop words que mas se repitan de mayor a menor 
	rewind(fpSW); //Vuelve al inicio del archivo de texto
	
	
	
	
	
	
	
	
	
	
	for(i=0;i<contador;i++){
		fscanf(fpSW, "%s", palabra);	
		strcpy(arregloDeCadena[i], palabra);//Guarda la palabra en la matriz de char
		
		
		
		for(k=0;k<strlen(arregloDeCadena[i]);k++){//Ciclo para convertir cada char del array en mayuscula
			arregloDeCadena[i][k]=toupper(arregloDeCadena[i][k]);
		}
		
	}
	

	
	
	//Cierra el archivo Stop Words
	fclose ( fpSW );
	
	
	//Se limpia el arreglo de contadorStopWords
	for(i=0;i<contador;i++){
		contadorStopWords[i]=0;
		ordenarMenoraMayor[i]=i;
	}
	
	
	
	//Abrir archivo a Analizar
	FILE *fpA;  //Crea una direccion de memoria para leer el archivo
	fpA = fopen ( "aAnalizar.txt", "r" );        
	if (fpA==NULL) {fputs ("File error",stderr); exit (1);}
	rewind(fpA); //Vuelve al inicio del archivo de texto
	for( i=1;i<100000;i++){
		if(feof(fpSW)){//comprueba si ya llego al final del archivo
			break;
        }
        fscanf(fpA, "%s ", palabra); //Lee la siguiente palabra
        
        
        for(k=0;k<strlen(palabra);k++){ //Ciclo para convertir la palabra a mayusculas
        	palabra[k]=toupper(palabra[k]);
		}
		
        for(j=0;j<contador;j++){ //Compara las stop words con la palabra leída del archivo analisis
			if(strcmp(palabra,arregloDeCadena[j])== 0){
				contadorStopWords[j]++;
			}
		}
		
    }
    
	fclose ( fpA ); //cierra el archivo de analisis
	
	
	
	
	//Genera las 10 palabras mas utilizadas
	char aAnalizar []={"aAnalizar.txt"};
	printf("\nSe analizo el archivo : %s",aAnalizar);
	analizarLasPalabrasMasUtilizadas(aAnalizar);
	
	
	
	
	int comparaciones=0,intercambios=0,aux=0;
	int strAux;
	
	//Ordenamos descendentemente la cantidad de repeticiones de las palabras
	for(i = 1; i < contador; ++i) {
      for( j = 0; j < (contador - i);++j) {
         comparaciones++;
         if(contadorStopWords[j] > contadorStopWords[j+1]){
            aux = contadorStopWords[j];
            strAux=ordenarMenoraMayor[j];
            contadorStopWords[j] = contadorStopWords[j + 1];
            ordenarMenoraMayor[j]=ordenarMenoraMayor[j+1];
            contadorStopWords[j + 1] = aux;
            ordenarMenoraMayor[j+1]=strAux;
            intercambios++;
         }
      }
    }
    
    printf("\nStop Words: ");
    //Mostrar los resultados
     //Opciones para mostrar resultados
    int count=0;
    int opcion=0;
    printf("\nComo deseas mostrar los resultados:");
    printf("\n1)Mostrar todas las stop words");
    printf("\n2)Mostrar solo n cantidad de stop words que mas se repitieron");
    printf("\nTu Opcion:");
    scanf("%i",&opcion);
    
    
    
    
    printf("\nStop Words: ");
    //Si la opcion que eligio fue la 1
    if(opcion==1){
    	for(i=contador-1;i>=0;i--){
    		printf("\nLa palabra: %s se repitio %i ",arregloDeCadena[ordenarMenoraMayor[i]],contadorStopWords[i]);
    		for(j=0;j<contadorStopWords[i];j++){
    			printf("/");
			}
		}
	}
	
	if(opcion==2){
		
		printf("Introduce el numero de stop words a mostrar(solo se mostraran aquellas que se repiten mas de una vez)");
		scanf("%i",&opcion);
		
		
		
		for(i=contador-1;i>=0;i--){
		if(count==opcion){
			break;
		}
    	if(contadorStopWords[i]>0){
    		printf("\nLa palabra: %s se repitio %i ",arregloDeCadena[ordenarMenoraMayor[i]],contadorStopWords[i]);
    		for(j=0;j<contadorStopWords[i];j++){
    			printf("/");
			}
		}
		count++;
	}
		
		
	}
    
	}
 
 void analizarLasPalabrasMasUtilizadas(char cad[]){
 	char original[]={"original.txt"};//Esta cadena sirve para compararla después
 	int longitudMaxima=0,contador=0,contadorTemp=0;
 	char palabra[120],palabraTemp[120];
 	int i=0,k=0,j=0;
 	int comprobacion=0;
 	FILE *fpOriginal;
	fpOriginal = fopen ( cad, "r" );  
	//Comprobar existencia del archivo    
	if (fpOriginal==NULL) {fputs ("File error",stderr); exit (1);}
	
	
	//Analizar el archivo original
	rewind(fpOriginal);//Vuelve al inicio del archivo de texto
	for( i=1;i<1000;i++){
		if(feof(fpOriginal)){
            break;
        }
        fscanf(fpOriginal, "%s ", palabra);
        contador++;
        if(strlen(palabra)>longitudMaxima){
        	longitudMaxima=strlen(palabra);
		}
    }

    //Guarda las palabras Stop en un arreglo
	char arregloDeCadena[contador][longitudMaxima+2]; //Aquí se guardan las palabras del archivo original
 	
	 
	
	rewind(fpOriginal);//Vuelve al inicio del archivo de texto
 	printf("\nPalabras totales en el archivo  %i",contador);

	for(i=0;i<contador;i++){
		fscanf(fpOriginal, "%s", palabra);//Lee palabra por palabra
		//Guarda la palabra en la matriz de char
		for(k=0;k<strlen(palabra);k++){//Ciclo para convertir cada char del array en mayuscula
			palabra[k]=toupper(palabra[k]);
		}
		
		for(j=0;j<=i;j++){//Ciclo comprueba si la palabra leída se encuentra en el arreglo
			if(strcmp(palabra,arregloDeCadena[j])== 0 ){//Verifica la existencia de la palabra en el arreglo
				comprobacion=1;//Si existe 
			}
		}
		if(comprobacion==0){// Si no existe en el arreglo se agrega
				strcpy(arregloDeCadena[contadorTemp], palabra);
				contadorTemp++;
		}
		comprobacion=0;//Vuelve a restablecerse la variable para volverla a utirlizar en la siguiente iteraccion
		
	}
	printf("\nCantidad de tipos de palabras %i ",contadorTemp);
	
	int comparaciones=0;
	int strAux;
	int contadorStopWords[contadorTemp];
	int aux;
	int ordenarMenoraMayor[contadorTemp];
	int intercambios=0;
	
	
	
	
	for(i=0;i<contadorTemp;i++){
		contadorStopWords[i]=0;
		ordenarMenoraMayor[i]=i;
	
	}
	
	
	
	rewind(fpOriginal); //Vuelve al inicio del archivo de texto
	for( i=0;i<contador;i++){
		if(feof(fpOriginal)){//comprueba si ya llego al final del archivo
            break;
        }
        fscanf(fpOriginal, "%s ", palabra); //Lee la siguiente palabra
        for(k=0;k<strlen(palabra);k++){//Ciclo para convertir cada char del array en mayuscula
			palabra[k]=toupper(palabra[k]);
		}
        for(j=0;j<contadorTemp;j++){ //Compara las stop words con la palabra leída del archivo analisis
			if(strcmp(palabra,arregloDeCadena[j])== 0){
				contadorStopWords[j]++;
			}
		}
		
    }
    
	fclose ( fpOriginal ); //cierra el archivo de analisis
	
	
	
	
	
	for(i = 1; i < contadorTemp; ++i) {
      for( j = 0; j < (contadorTemp - i);++j) {
         comparaciones++;
         if(contadorStopWords[j] > contadorStopWords[j+1]){
            aux = contadorStopWords[j];
            strAux=ordenarMenoraMayor[j];
            contadorStopWords[j] = contadorStopWords[j + 1];
            ordenarMenoraMayor[j]=ordenarMenoraMayor[j+1];
            contadorStopWords[j + 1] = aux;
            ordenarMenoraMayor[j+1]=strAux;
            intercambios++;
         }
      }
    }
    
    
   
    
    
    

	
	FILE *fp;
	
	if(strcmp(cad,original)==0){
		fp=fopen ("resultadosOriginal.txt","w");
	}
	else{
		fp=fopen ("resultados.txt","w");
	}
    
    contador=0;
    
    for(i=contadorTemp-1;contador<10;i--){
    	if(contadorTemp==contador){
    	break;	
		}
    	fprintf(fp,"%s ",arregloDeCadena[ordenarMenoraMayor[i]]);
    	printf("\nLa palabra %s se repitio %i ",arregloDeCadena[ordenarMenoraMayor[i]],contadorStopWords[i]);
    	for(k=0;k<contadorStopWords[i];k++){
    		printf("/");
		}
    	contador++;
	}
    
	
 	
 	fclose(fp);
 	
 	
 	
 	
 	
 }
 
 void analisisPlagio(){
 	//Variables locales de la funcion
	char palabra[120];
	int contador=0;
	int contadorOriginal=0;
	int i=0,j=0;
	int longitudMaxima=0;
	int concuerdanAmbasPalabras=0;
	float porcentajePlagio=0;
	
	FILE *fpSW;
	fpSW = fopen ( "resultados.txt", "r" );  
	//Comprobar existencia del archivo    
	if (fpSW==NULL) {fputs ("File error",stderr); exit (1);}
	
	//Analizar el archivo stop Words
	rewind(fpSW);//Vuelve al inicio del archivo de texto
	for( i=1;i<1000;i++){
		if(feof(fpSW)){
            break;
        }
        fscanf(fpSW, "%s ", palabra);
        contador++;
        if(strlen(palabra)>longitudMaxima){
        	longitudMaxima=strlen(palabra);
		}
    }
	//Guarda las palabras Stop en un arreglo
	char arregloDeCadena[contador][longitudMaxima+2]; //Aquí se guardan las stop words
    rewind(fpSW); //Vuelve al inicio del archivo de texto
	for(i=0;i<contador;i++){
		fscanf(fpSW, "%s", palabra);	
		strcpy(arregloDeCadena[i], palabra);//Guarda la palabra en la matriz de char
	}
    fclose(fpSW);
    
    
    
    
    
	longitudMaxima=0;
    FILE *fpO = fopen ( "resultadosOriginal.txt", "r" );  
    rewind(fpO);
    for( i=1;i<1000;i++){
		if(feof(fpO)){
            break;
        }
        fscanf(fpO, "%s ", palabra);
        contadorOriginal++;
        if(strlen(palabra)>longitudMaxima){
        	longitudMaxima=strlen(palabra);
		}
    }
    
    char arregloDeCadenaOriginal[contadorOriginal][longitudMaxima+2];
    rewind(fpO);
    for(i=0;i<contadorOriginal;i++){
		fscanf(fpO, "%s", palabra);	
		strcpy(arregloDeCadenaOriginal[i], palabra);//Guarda la palabra en la matriz de char
	}
    fclose(fpO);
    
    
    
    
    
    for(i=0;i<10;i++){
    	if(i>=contadorOriginal || i>=contador){
    		break;
		}
    	
	}
	
	for(i=0;i<contadorOriginal;i++){
		for(j=0;j<contador;j++){
			if(strcmp(arregloDeCadenaOriginal[i],arregloDeCadena[j])== 0){
				printf("\nArchivo Original: %s en pos:%i Archivo Plagio:%s en pos %i ",arregloDeCadenaOriginal[i],i,arregloDeCadena[j],j);
				concuerdanAmbasPalabras++;
			}
		}
		
	}
    
    
    float convertirAFloat=contadorOriginal;
    porcentajePlagio=(concuerdanAmbasPalabras/convertirAFloat)*100;
    printf("\nLas Palabras principales de ambos archivos se repitieron: %i\nEl porcentaje de plagio es %.2f",concuerdanAmbasPalabras,porcentajePlagio);
 }
 
 void analizar(){
 	char original[]={"original.txt"};
 	char posiblePlagio1[]={"plagio1.txt"};
 	char posiblePlagio2[]={"plagio2.txt"};
 	char posiblePlagio3[]={"plagio3.txt"};
 	printf("\n\t*****Se analizara el archivo Original:");
 	analizarLasPalabrasMasUtilizadas(original);
 	printf("\n\t*****Se analizara el Posible plagio 1:");
 	analizarLasPalabrasMasUtilizadas(posiblePlagio1);
 	printf("\n\t*****Resultados del analisis plagio 1");
 	analisisPlagio();
 	printf("\n\t*****Se analizara el Posible plagio 2:");
 	analizarLasPalabrasMasUtilizadas(posiblePlagio2);
 	printf("\n\t*****Resultados del analisis plagio 2");
 	analisisPlagio();
 	printf("\n\t*****Se analizara el Posible plagio 3:");
 	analizarLasPalabrasMasUtilizadas(posiblePlagio3);
 	printf("\n\t*****Resultados del analisis plagio 3");
 	analisisPlagio();
 }
