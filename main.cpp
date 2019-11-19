#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
using namespace std;


struct infoJuegos{
    char titulo[20];
    char genero[20];
    char precio[10];
} juegos;

FILE *archivo;

void menuOpciones();

void guardarJuego();
void mostrarJuegos();
void buscarUnJuego();
void modificarJuego ();
void eliminarJuego();

void hora();
void conversionAMinusculas(char valorAConvertir []);




int main(){
    int opcion;
    char opcionSeguir;

    menuOpciones();
    do{
        cout <<"\nSeleccione una opcion del menu > ";
        cin >>opcion;

        switch(opcion){
            case 0:
                system("cls");
                cout<<"Gracias por usar el programa! c:";
                exit(1);
                break;
            case 1:
                system("cls");
                guardarJuego();
                cout<<"Juegos registrados correctamente. ";
                break;
            case 2:
                system("cls");
                mostrarJuegos();
                break;
            case 3:
                system("cls");
                buscarUnJuego();
                break;
            case 4:
                system("cls");
                modificarJuego ();

                break;
            case 5:
                system("cls");
                eliminarJuego ();

                break;
            case 6:
                fclose(archivo);
                if( remove( "ListaJuegos.txt" ) != 0 )
                    perror( "No se pudo eliminar" );
                else
                    puts( "Archivo eliminado" );
                    fclose(archivo);
                if( remove( "Temporal.txt" ) != 0 )
                    perror( "No se pudo eliminar" );
                else
                    puts( "Archivo eliminado" );
                break;

            default:
                cout<<"La opcion no existe. "<<endl;
                break;
            }
        cout<<"\n\nDesea realizar otra operacion? <s/n>: ";
        cin>>opcionSeguir;
        system("cls");

        menuOpciones();
    }while((opcionSeguir == 's') || (opcionSeguir == 'S') );
    system("cls");
    cout<<"Cerrando programa, presione cualquier tecla";
}




//Opcion 1.
void guardarJuego(){
    system("cls");

    archivo = fopen("ListaJuegos.txt", "r");
    int cantidadDeJuegos = 0;

    //Cuento la cantidad de juegos que tengo
    while (fread(&juegos, sizeof(juegos), 1, archivo)){
        cantidadDeJuegos++;
    }
    fclose(archivo);

    fflush(stdin);
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"-                    MENU REGISTRO DE JUEGOS                         -"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<" \tJuego > "<< cantidadDeJuegos+1<<endl;
    cout<<"\tTitulo: ";
    cin>>juegos.titulo;
    fflush(stdin);
    cout<<"\tGenero: ";
    cin>>juegos.genero;
    fflush(stdin);
    cout<<"\tPrecio  ";
    cin>>juegos.precio;
    cout<<endl;
    system("cls");


    archivo=fopen("ListaJuegos.txt","a+");
    fwrite(&juegos,sizeof(infoJuegos),1,archivo);
    fclose(archivo);
}


//opcion 2
void mostrarJuegos(){
    system("cls");
    archivo = fopen("ListaJuegos.txt", "r");
    if (archivo == NULL){
		cout<<"No se puede abrir el archivo, o no existe el mismo.\n"<<endl;

    } else {
        fread(&juegos, sizeof(infoJuegos), 1, archivo);
        while (!feof(archivo)){
            cout<<"----------------------------------------------------"<<endl;
            cout<<"Titulo -> "<<juegos.titulo<<endl;
            cout<<"Genero -> "<<juegos.genero<<endl;
            cout<<"Precio -> "<<juegos.precio<<endl;
            cout<<endl;
            fread(&juegos, sizeof(infoJuegos), 1, archivo); //vuelve a leer el archivo para ver si quedan datos en el para cargar otra estructura
        }
        fclose(archivo);
    }

}


//opcion 3
void buscarUnJuego(){
    system("cls");
	char auxTituloJuego[20];

	int cantidadDeJuegos = 0;

	archivo = fopen("ListaJuegos.txt","r");
    if ( archivo == NULL ){
		cout<<"No se puede abrir el archivo o el mismo no existe\n"<<endl;

	} else {
        cout<<"Ingrese el nombre del juego que desea buscar en el almacen > ";
        cin>>auxTituloJuego;

        conversionAMinusculas(auxTituloJuego);

        fread(&juegos,sizeof(infoJuegos),1,archivo);  // lee el archivo para ver si hay estructuras para cargar a mi struct
        while(!feof(archivo))
        {
            conversionAMinusculas(juegos.titulo);
            if(strcmp(juegos.titulo, auxTituloJuego) == 0){
                cout<< "\nEl juego fue encontrado y el mismo fue ingresado en el orden: "<< cantidadDeJuegos+1;
                cout<< "\nMostrando datos del juego\n\n";
                cout<<"Titulo -> "<<juegos.titulo<<endl;
                cout<<"Genero -> "<<juegos.genero<<endl;
                cout<<"Precio -> "<<juegos.precio<<endl;
            }
            fread(&juegos,sizeof(infoJuegos),1,archivo); //vuelve a leer el archivo para ver si quedan datos en el para cargar otra estructura
            cantidadDeJuegos++;
        }

        fclose(archivo);
	}
}



//opcion 4
void modificarJuego (){

    system("cls");

    int cantidadDeJuegos = 0;
	FILE *archivoTemporal; //Luego se utilizara para reemplazar el original
	bool juegoEncontrado = false;
    char auxTituloJuego[20];



	archivo = fopen("ListaJuegos.txt","r");
    if (archivo == NULL){
    	cout<<"No se puede abrir el archivo o no existe el mismo\n "<<endl;
	} else {

        archivoTemporal = fopen("Temporal.txt","a+");

        if (archivoTemporal == NULL){
            cout<<"No se puede abrir el Archivo\n";
        } else {
            cout<< "Actualmente estan estos juegos registrados: " << endl;
            fread(&juegos,sizeof(infoJuegos),1,archivo);
            while(!feof(archivo)){
                cout<< cantidadDeJuegos+1<<" - "<<juegos.titulo<<"."<<endl;
                cantidadDeJuegos++;
                fread(&juegos,sizeof(infoJuegos),1,archivo);
            }
            fclose(archivo);

            cout<<"\nIngrese el nombre del juego que desee modificar. ";
            cin>>auxTituloJuego;

            conversionAMinusculas(auxTituloJuego);

            archivo = fopen("ListaJuegos.txt","r");

            fread(&juegos,sizeof(infoJuegos),1,archivo);
            while(!feof(archivo)){
                conversionAMinusculas(juegos.titulo);
                if(strcmp(juegos.titulo, auxTituloJuego) == 0){ //Modifica si se encontro el juego
                    fflush(stdin);
                    cout<<"Nuevo Genero ---> ";
                    ZeroMemory(juegos.genero, sizeof(juegos.genero));
                    cin>>juegos.genero;
                    cout<<"Nuevo Precio ---> ";
                    ZeroMemory(juegos.precio, sizeof(juegos.precio));
                    cin>>juegos.precio;

                    fwrite(&juegos, sizeof(infoJuegos), 1, archivoTemporal); // agrego los datos al archivo temporal (nuevo)
                    juegoEncontrado = true;
                } else { //si no se encontro el juego, no hay nada q modificar y los voy agregando al temporal

                    fwrite(&juegos,sizeof(infoJuegos),1,archivoTemporal);
                }

                fread(&juegos,sizeof(infoJuegos),1,archivo); //vuelve a leer el archivo para ver si quedan datos en el para cargar otra estructura

            }
            // cerrando archivos;
            fclose(archivo);
            fclose(archivoTemporal);


            remove("ListaJuegos.txt"); //Eliminamos el archivo antiguo
            rename("Temporal.txt" , "ListaJuegos.txt"); //renombramos el nuevo archivo temporal a listaJuegos.txt


            if ( juegoEncontrado == false)
                cout<<"No existe este juego \n\n";
            else
                cout<<"Registro Actualizado"<<endl;
            }
        }
}


//opcion 4
void eliminarJuego(){

    system("cls");

    int cantidadDeJuegos = 0;
	FILE *archivoTemporal; // se utilizara para reemplazar el original
	bool juegoEncontrado = false;
    char auxTituloJuego[20];


	archivo = fopen("ListaJuegos.txt","r");

    if (archivo == NULL){
    	cout<<"No se puede abrir el archivo o no existe el mismo\n "<<endl;
	} else {

        archivoTemporal = fopen("Temporal.txt","a+");

        if (archivoTemporal == NULL){
            cout<<"No se puede abrir el Archivo\n";
        } else {
            cout<< "Actualmente estan estos juegos registrados: " << endl;
            fread(&juegos,sizeof(infoJuegos),1,archivo);
            while(!feof(archivo)){
                cout<< cantidadDeJuegos+1<<" - "<<juegos.titulo<<"."<<endl;
                cantidadDeJuegos++;
                fread(&juegos,sizeof(infoJuegos),1,archivo);
            }
            fclose(archivo);

            cout<<"\nIngrese el nombre del juego que desee eliminar. ";
            cin>>auxTituloJuego;

            conversionAMinusculas(auxTituloJuego);

            archivo = fopen("ListaJuegos.txt","r");

            fread(&juegos,sizeof(infoJuegos),1,archivo);
            while(!feof(archivo)){
                conversionAMinusculas(juegos.titulo);
                if(strcmp(juegos.titulo, auxTituloJuego) == 0){ //Modifica si se encontro el juego
                    juegoEncontrado = true;
                } else { //si no se encontro el juego, no hay nada q modificar y los voy agregando al temporal
                    fwrite(&juegos, sizeof(infoJuegos), 1, archivoTemporal); // agrego los datos al archivo temporal (nuevo)
                }

                fread(&juegos,sizeof(infoJuegos),1,archivo); //vuelve a leer el archivo para ver si quedan datos en el para cargar otra estructura

            }
            fclose(archivo);
            fclose(archivoTemporal);


            remove("ListaJuegos.txt");
            rename("Temporal.txt" , "ListaJuegos.txt");


            if ( juegoEncontrado == true){
                cout<<"El juego fue eliminado \n\n";
            } else {
                cout<<"El juego ingresado no existe"<<endl;
            }
        }
    }
}
void conversionAMinusculas(char valorAConvertir[] ){
    for (int i=0; i<strlen(valorAConvertir); i++){
        valorAConvertir[i] = tolower(valorAConvertir[i]);
    }
}

//Menus
void menuOpciones()
{
    //cout<<ultimoj;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"\tBIENVENIDO SELECCIONE UNA OPCION DEL MENU PARA PROCEDER.     |"<<endl;
    cout<<"----------------------------------------------------------------------"<<endl;
    cout<<"[1] --> \tREGISTRAR JUEGO                                           "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[2] --> \tMOSTRAR JUEGOS REGISTRADOS                                "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[3] --> \tBUSCAR JUEGO REGISTRADOS                                  "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[4] --> \tMODIFICAR JUEGO.                                          "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[5] --> \tELIMINAR JUEGO.                                           "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[6] --> \tELIMINAR ARCHIVO (test)                                  "<<endl;
    cout<<"                                                                     |"<<endl;
    cout<<"[0] --> \tSalir.                                                    "<<endl;
    cout<<"--------------------------------------------------------------------- "<<endl;
}

/*
Modos de apertura de archivos
r � abre el archivo en modo de solo lectura.
w � abre el archivo para escritura (si no existe lo crea, si existe lo destruye).
a � abre el archivo para agregar informaci�n (si no existe lo crea).
r+ � abre el archivo para lectura/escritura (comienza al principio del archivo).
w+ � abre el archivo para lectura/escritura, sobre-escribe el archivo si este ya existe o lo crea si no).
a+ � abre el archivo para lectura/escritura (se sit�a al final del archivo).
*/
