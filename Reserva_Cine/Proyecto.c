//-------------------------------------------------------------------//
/*                         CINEMA YAKU                              */
/*                                                                  */
/*            Created by Douglas Hernández, Hugo Andrés Gómez       */
/*                          & Abdenago López                        */
/*                                                                  */
/*                        Copyright © 2010                          */
//-------------------------------------------------------------------//

#include<stdio.h>
#include<stdlib.h>
#include<allegro.h>
#include<string.h>


#define FIL 11
#define COL 16
#define COR 10
#define DEPTH 32
#define ANCHO 320
#define ALTO  220

    typedef struct{
           char nombre[50];
           int cedula;
           int telefono;
           char pelicula[50];
           char silla [20];
    }CLIENTE;
    
    typedef struct{
              int sala;
              char pelicula[50];
              char formato[20];
              char room[FIL][COL];
    }SALAS;
    
    void Veregistro();
    void recibo(int coor[COR]);
    void crear();
    void creartmp();
    void auditorio(char sala[FIL][COL]);
    SALAS buscarsala(int buscar,char sala[FIL][COL]);
    void guardar(SALAS room,char sala[][]);
    
    void Ini(char sala[][]);
    void imprimir (SALAS );
    void cargar(char sala[][]);
    void Buffer(char sala[][],BITMAP *,BITMAP *,BITMAP *,BITMAP *);
    void  Imprimir2(BITMAP *buffer);
    void  allegro (SALAS,int coor[COR]);
    void mover(char sala[FIL][COL],int coor[COR]);
///////////////////////////////////////////////////////////////////////////////    
    /*funcion principal main 
      contiene los llamados a las funciones
      variables:
           tipo int:
              opc:  opcion menu principal.
              opc2: opcion menu secundario.
              buscar: guarda el numero de la sala que desea ver.
           tipo char:
               sala[][]:matriz que contiene el mapa de la sala
    */      
    
    main(){
        int opc=0,opc2=0,buscar=0;
        int coor[COR];
        char sala[FIL][COL];
        SALAS room;
            
        Ini(sala);
        cargar(sala); 
               
        while(opc!=5){
             system("cls");
             printf("\n>>>>CINE YAKU<<<<\n");       
             printf("\n1.Cliente\n2.Salas\n5.Salir\n");
             scanf("%i", &opc);
             switch(opc){
                 case 1:
                        opc2=0;
                      while(opc2!=5){       
                            system("cls");
                            printf("\n>>>>CINE YAKU<<<<\n");         
                            printf("\n1.Registrar cliente VIP\n2.Ver cliente registrado\n\n3.Reservar puesto\n4.Imprimir recibo\n5.Salir\n");
                            scanf("%i",&opc2);
                            switch(opc2){
                                   case 1:
                                        allegro_init();
                                        allegro_exit();
                                        crear();
                                        break;
                                   case 2:
                                        Veregistro();
                                        getch();
                                        break;  
                                   case 3:
                                        buscar=0;
                                        room=buscarsala(buscar,sala);
                                        if(room.sala!=0){
                                            allegro_init();
                                            install_keyboard();
                                            allegro(room,coor);                                                                                                              
                                            allegro_exit();
                                            creartmp();
                                        }else{
                                           printf("NO SE ENCUENTRA REGISTRADA LA PELICULA");
                                           getch();
                                        }
                                        break;
                                   case 4:
                                        recibo(coor);
                                        getch();
                                        break;    
                            }                        
                      }
                      break;
                 case 2:
                      opc2=0;
                      while(opc2!=5){
                            system("cls");         
                            printf("\n>>>>CINE YAKU<<<<\n");         
                            printf("\n1.Asignar peliculas\n2.Visualizar\n5.Salir\n");
                            scanf("%i",&opc2);
                            switch (opc2){
                                   case 1:
                                        auditorio(sala);
                                        break;
                                   case 2:
                                        printf("\nQue sala desea: \n");
                                        scanf("%i",&buscar);fflush (stdin);
                                        room=buscarsala(buscar,sala);
                                        if(room.sala!=0){
                                           imprimir(room);
                                           allegro_init();
                                           install_keyboard();
                                           allegro(room,coor);                                                                                                              
                                           allegro_exit();
                                        }else{
                                           printf("CINE YAKU SOLO CUENTA CON 4 SALAS DE CIENE INGRESE UNA OPC VALIDA");
                                           getch();
                                        }
                                        break;
                                   
                            }
                      }    
             }         
              
        }
    }END_OF_MAIN();
    
    void guardar(SALAS room,char sala[FIL][COL]){
       FILE *arch1;
    
       int i=0,j,k;
       if(room.sala==1){
                        arch1 = (fopen("sala1", "wb+"));
                        }
          if(room.sala==2){
                        arch1 = (fopen("sala2", "wb+"));
                        }
          if(room.sala==3){
                        arch1 = (fopen("sala3", "wb+"));
                       }
          if(room.sala==4){
                        arch1 = (fopen("sala4", "wb+"));
                        }
       
    
             for(k=0; k<FIL; k++){
                  for(j=0; j<COL; j++){
                           room.room[k][j]=sala[k][j];
                           }
                  } 
             fseek(arch1,0,SEEK_SET);       
             fwrite(&room,sizeof(room),1,arch1);
    
    fclose(arch1);
    }     
  
  ///////////////////////////////////////////////////////////////////////////  
    /*funcion imprimir
      recibe el dato, tipo estructura, llamado sala y la imprime.
      variables:
           tipo int:
              i, j: contadores.
    */      
              
    void imprimir(SALAS room){
     int i=0,j=0;
      
      system("cls");
      printf("\nSala:%i\nPelicula que se proyecta:%s\nFormato:%s",room.sala,room.pelicula,room.formato);
         
    }
  ///////////////////////////////////////////////////////////////////////////////  
    /*funcion Ini 
         recibe de la funcion main los parametros:
                tipo char:
                     sala[][]:que en este momento no contienen nada
         inicializa las matrices con espacios en blanco para evitar la basura que contienen
         variables:
              tipo int:
                  i,j:contadores.
     */     
    
    void Ini(char sala[FIL][COL]){
       int i,j;          
        for(i=0; i<FIL; i++){
             for(j=0; j<COL; j++){
               sala[i][j]=' ';                  
                }
         }            
    }
 ///////////////////////////////////////////////////////////////////////////////   
    /*funcion cargar
         recibe de la funcion main los parametros:
                tipo char:
                     sala[][]:que en este momento contiene espacios en blanco
        llena la matriz con el archivo de las salas
         variables:
              tipo int:
                  i,j: contadores
                  ancho:es el ancho del nivel
                  cont:es el limete que tiene para que cargue los datos del archivo      
              tipo char:
                   car: lee y guarda los caracteres del archivo uno a uno.
     */     
    
    void cargar(char sala[FIL][COL]){
          int i=0,j=0;
          FILE *arch;
          char car;
          
          arch=fopen("room2.txt","r");
          while(!feof(arch)){
                 car=fgetc(arch);
                 if(car!='\n'){
                    sala[i][j]=car;
                    j++;
                 }else{            
                    i++;
                    j=0;
                 }             
                              
          }
    fclose(arch);       
    }
  //////////////////////////////////////////////////////////////////////////  
    /*funcion buscarsala
         recibe de la funcion main los parametros:
                tipo int:
                     buscar: contiene el dato de la sala a buscar.
                tipo char:
                     sala[][] :contiene la sala cargada del archivo
                variables:
         tipo int: 
                     i, j:contadores.
         tipo char:
                  pelicula:nombre de la pelicula a buscar
         
     */ 
    
    SALAS buscarsala(int buscar,char sala[FIL][COL]){
          FILE *arch1;
          SALAS room;
          int cont=0,i,j;
          char pelicula[20];
          strcpy(room.pelicula,"hola");
          
          if(buscar==0){
              printf("\n nombre pelicula:");fflush(stdin);
              gets(pelicula);fflush(stdin); 
             while(strcasecmp(pelicula,room.pelicula)!=0){
                   buscar++;                                       
                   if(buscar==1){
                        arch1 = (fopen("sala1", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
                   if(buscar==2){
                        arch1 = (fopen("sala2", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
                   if(buscar==3){
                        arch1 = (fopen("sala3", "r"));
                        fread(&room,sizeof(room),1,arch1);
                       }
                   if(buscar==4){
                        arch1 = (fopen("sala4", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
                   if(buscar==5){
                        room.sala=0;
                         return room;               
                    }
                   }
                   
             fclose(arch1);
             return room;
             }
             
           if(buscar>4){
                 room.sala=0;
                 return room;
           }  
          if(buscar==1){
                        arch1 = (fopen("sala1", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
          if(buscar==2){
                        arch1 = (fopen("sala2", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
          if(buscar==3){
                        arch1 = (fopen("sala3", "r"));
                        fread(&room,sizeof(room),1,arch1);
                       }
          if(buscar==4){
                        arch1 = (fopen("sala4", "r"));
                        fread(&room,sizeof(room),1,arch1);
                        }
    
          if (arch1 == NULL){
                 printf("\nPrimero digite los datos para poder visualizarlos\n");
                  room.sala=0;
                  return room;
                  }
    
    fclose(arch1);
      return room;    
    }
 //////////////////////////////////////////////////////////////////////////////   
    /*funcion auditorio
         recibe de la funcion main el parametro:
                tipo char:
                     sala[][] :contiene la sala cargada del archivo
                variables:
         tipo int: 
                     i, j, k:contadores.
         tipo file:
                  arch:archivo que se crea guardando informacion de cada sala
         
     */ 
    
    void auditorio(char sala[FIL][COL]){
       FILE *arch1;
       FILE *arch2;
       FILE *arch3;
       FILE *arch4;
       SALAS room;
       int i=0,j,k;
       arch1=fopen("sala1","ab");
       arch2=fopen("sala2","ab");
       arch3=fopen("sala3","ab");
       arch4=fopen("sala4","ab");
       for(i=0;i<4;i++){
             printf("\nSALA %i\n",i+1);          
             room.sala=i+1;         
             printf("\nNombre Pelicula: ");fflush (stdin);
             gets(room.pelicula);fflush(stdin);
             printf("\nFormato: ");fflush(stdin);
             gets(room.formato);fflush(stdin);
             for(k=0; k<FIL; k++){
                  for(j=0; j<COL; j++){
                           room.room[k][j]=sala[k][j];
                           }
                  }        
             if(i==0){
                  fwrite(&room,sizeof(room),1,arch1);
               }
             if(i==1){
                 fwrite(&room,sizeof(room),1,arch2);
               }
             if(i==2){
                 fwrite(&room,sizeof(room),1,arch3);                     
               }
             if(i==3){
                   fwrite(&room,sizeof(room),1,arch4);                     
               } 
       }
             
             fclose(arch1);
             fclose(arch2);
             fclose(arch3);
             fclose(arch4);
    }
             
////////////////////////////////////////////////////////////////////////////////
    /*funcion veregistro --> Visualizar los clientes VIP
               variables:
         tipo int: 
                     i:contador.
         tipo FILE:
              arch: guarda el archivo creado con los VIP.
         
     */ 
    
    void Veregistro(){
        FILE *arch;
        CLIENTE client;
        int i=1;
        
          if ((arch= fopen("registrados", "r")) == NULL){
                  printf("\nPrimero digite los datos para poder visualizarlos.\n");
                  return;
                  }
        
        fread(&client,sizeof(client),1,arch);
        while(!feof(arch)){
              printf("\nCLIENTE %i\n",i);
              printf("\nNombre: %s\n",client.nombre);
              printf("\nCedula: %i\n",client.cedula);
              printf("\nTelefono: %i\n",client.telefono);
              printf("\nPelicula: %s\n",client.pelicula);
              printf("\nPuestos: %s\n",client.silla);
              i++;
              fread(&client,sizeof(client),1,arch);    
        }
    fclose(arch);
    }
 //////////////////////////////////////////////////////////////////////   
    /*funcion recibo --> Para imprimir recibo
         
                variables:
         tipo int: 
                     i:contador.
         tipo FILE:
                  arch:visualizar los clientes temporales.
         
     */ 
    
    void recibo(int coor[COR]){
        FILE *arch;
        CLIENTE client;
        int i=1,fil,col;
        fil=coor[0];
        col=coor[1];
          if ((arch= fopen("clientestmp", "r")) == NULL){
                  printf("\nPrimero digite los datos para poder visualizarlos.\n");
                  return;
                  }
        
        fread(&client,sizeof(client),1,arch);
        while(!feof(arch)){
              printf("\nCLIENTE %i\n",i);
              printf("\nNombre: %s\n",client.nombre);
              printf("\nCedula: %i\n",client.cedula);
              printf("\nTelefono: %i\n",client.telefono);
              printf("\nPelicula: %s\n",client.pelicula);
              printf("\nCatidad de Puestos: %s\n",client.silla);
              printf("\nLugares: (%c,%i)\n",fil,col);
              i++;
              fread(&client,sizeof(client),1,arch);    
        }
    fclose(arch);
    
    }
///////////////////////////////////////////////////////////////////////////    
    /*funcion crear --> Crear archivo con clientes VIP
         
                variables:
         tipo int: 
                     i:contador.
         tipo FILE:
                  arch:archivo con los VIP
         
     */ 
    
    void crear(){
       FILE *arch;
       CLIENTE client;
       int i=0;
       arch=fopen("registrados","ab");
       for(i=0;i<1;i++){
             printf("\nNombre Cliente: ");fflush (stdin);
             gets(client.nombre);fflush(stdin);
             printf("\nCedula:");fflush(stdin);
             scanf("%i",&client.cedula);fflush(stdin);
             printf("\nTelefono:");fflush(stdin);
             scanf("%i",&client.telefono);fflush(stdin);
             printf("\nPelicula:");fflush(stdin);
             gets(client.pelicula);fflush(stdin);
             printf("\nCantidad de Puestos:");fflush(stdin);
             scanf("%s",client.silla);fflush(stdin);
             printf("\n ");
             fseek(arch,0,SEEK_SET); 
             fwrite(&client, sizeof(client),1,arch);
       }
       fclose(arch);
    }
 ////////////////////////////////////////////////////////////////////////////   
    /*funcion creartmp
                 variables:
         tipo int: 
                     i:contador.
         tipo FILE:
                  arch:archivo con clientes temporales
         
     */ 
    
    void creartmp(){
       FILE *arch;
       CLIENTE client;
       int i=0;
       arch=fopen("clientestmp","wb+");
       for(i=0;i<1;i++){
             printf("\nNombre Cliente: ");fflush (stdin);
             gets(client.nombre);fflush(stdin);
             printf("\nCedula: ");fflush(stdin);
             scanf("%i",&client.cedula);fflush(stdin);
             printf("\nTelefono: ");fflush(stdin);
             scanf("%i",&client.telefono);fflush(stdin);
             printf("\nPelicula: ");fflush(stdin);
             gets(client.pelicula);fflush(stdin); 
             printf("\nCantidad de Puestos: ");fflush(stdin);
             scanf("%s",client.silla);fflush(stdin);
             printf("\n ");
             fseek(arch,0,SEEK_SET);         
             fwrite(&client, sizeof(client),1,arch);
       }
       fclose(arch);
    }
   //////////////////////////////////////////////////////////////////////////// 
    /*funcion allegro
         recibe de la funcion main los parametros:
                tipo estructura:
                     room: variable con las
                
                variables:
                tipo bitmap:
                     sprite: imagen del manejo de la sala
                     buffer: imagen temporal antes de imprimir la sala
                     numeros: imagen que contiene la numeracion de las sillas.
                     letras: imagen que contiene letras de las sillas
                
             
     */ 
    
    void allegro(SALAS room,int coor[COR]){
        BITMAP *sprite;
        BITMAP *buffer;
        BITMAP *numeros;
        BITMAP *letras;
        PALETTE palette; 
        
        set_color_depth( DEPTH );
        set_gfx_mode(GFX_AUTODETECT_WINDOWED,ANCHO,ALTO, 0, 0);
        set_window_title ("RESERVA >>>>CINE YAKU<<<<");
        
        letras=load_bitmap("letras.bmp",palette);
        numeros=load_bitmap("numeros.bmp",palette);
        sprite=load_bitmap("sala2.bmp",palette);
        buffer=create_bitmap(ANCHO,ALTO);                           
        clear (buffer);
        
        Buffer(room.room,sprite,letras,numeros,buffer);
        Imprimir2(buffer);
        
        while(!key[KEY_ESC])  {
             if(keypressed()){
                    mover(room.room,coor);
                    Buffer(room.room,sprite,letras,numeros,buffer);
                    Imprimir2(buffer);
                    clear_keybuf ();
              }
        }
         guardar(room,room.room);
        
        destroy_bitmap(letras);
        destroy_bitmap(numeros);
        destroy_bitmap(sprite);
        destroy_bitmap(buffer);
    }
  //////////////////////////////////////////////////////////////////////////  
    /*funcion mover
         recibe de la funcion allegro los parametros:
                tipo char:
                     sala[][]:que en este momento es la sala cargada del archivo
                
              variables:
              tipo int:
                  i, j, cont: contadores
                  col: coordenada de la columna en la sala
                  fil: coordenada de la fila en la sala
                               
      */   
    
    void mover(char sala[FIL][COL],int coor[COR]){
         int i, j,k;
         int col=0, fil=0;
         int cont=0;
         for(i=0; i<FIL; i++){
             for(j=0; j<COL; j++){
                 if(sala[i][j] == 'B'){
                    i = i+10;
                    break;
                    }
                 cont++;
                 }
             }     
             col = cont%COL;
             fil = cont/COL;
             
                      if(key[KEY_RIGHT]){
                                 if(sala[fil][col+1]=='A'){
                                    sala[fil][col+1]='B';
                                    sala[fil][col]='A';
                                    }
                                 if(sala[fil][col+1]=='D'&&sala[fil][col+2]!='C'){
                                       sala[fil][col+2]='B';
                                       sala[fil][col]='A';                                                     
                                    }
                     }
                      if(key[KEY_DOWN]){
                                 if(sala[fil+1][col]=='A'){
                                    sala[fil+1][col]='B';
                                    sala[fil][col]='A';
                                 }                               
                        }
                      if(key[KEY_LEFT]){
                                 if(sala[fil][col-1]=='A'){
                                    sala[fil][col-1]='B';
                                    sala[fil][col]='A';
                                 }
                                 if(sala[fil][col-1]=='D'&& sala[fil][col-2]!='C'){
                                       sala[fil][col-2]='B';
                                       sala[fil][col]='A';                                                     
                                    }
                         }
                     if(key[KEY_UP]){
                                 if(sala[fil-1][col]=='A'){
                                    sala[fil-1][col]='B';
                                    sala[fil][col]='A';
                                   }
                     }
                     if(key[KEY_ENTER]){
                          if(sala[fil][col]=='B'){
                             sala[fil][col]='C';
                          for(k=0;k<2;k++){
                              if(k==0){
                                  coor[k]=fil+65;
                              }else{
                                if(col<=7){    
                                 coor[k]=col+1;
                                 }else{
                                   coor[k]=col;
                                 }
                              }
                          }
                             /*printf("(%c, %i)", fil+65, col+1);
                             system("pause");*/
                             if(sala[fil][col+1]=='A'){
                               sala[fil][col+1]='B';
                             }else{
                                  for(i=0; i<FIL; i++){
                                      for(j=0; j<COL; j++){
                                           if(sala[i][j]=='A'){
                                               sala[i][j]='B';
                                               i=i+20;
                                           }
                                      }
                                  }
                             }
                           }                                   
                     }
           
    }
  ////////////////////////////////////////////////////////////////////  
    /*funcion Buffer
         recibe de la funcion allegro los parametros:
                tipo char:
                     sala[][] :que en este momento el nivel cargado del archivo
                tipo bitmap:
                     room: imagen del manejo de la sala
                     buffer: imagen temporal antes de imprimir la sala
                     numeros: imagen que contiene la numeracion de las sillas.
                     letras: imagen que contiene letras de las sillas
                                                                
         variables:
              tipo int:
                  i, j, k, x, z, car:contadores
                   
                  
                  */     
    
    void Buffer(char sala[FIL][COL],BITMAP *room,BITMAP *letras,BITMAP *numeros,BITMAP *buffer){
          int j,i,z=0,k=0,car=0,x=0;    
       
             for(i=0;i<FIL;i++){
                    for(j=0;j<COL;j++){
                        car=(int)sala[i][j];
                        if(car>=65&&car<=90){
                        x=((car-65)*20);
                        blit(room,buffer,x,0,k,z,20,20);
                        k=k+20;
                        }
                        if(car>=48&&car<=62){
                        x=((car-48)*20);
                        blit(numeros,buffer,x,0,k,z,20,20);
                        k=k+20;
                        }
                        if(car>=97&&car<=122){
                        x=((car-97)*20);
                        blit(letras,buffer,x,0,k,z,20,20);
                        k=k+20;
                        }
                    }  
                z=z+20;
                k=0;        
             }
    
    }
    ////////////////////////////////////////////////////
    /*funcion imprimir2
         recibe de la funcion allegro los parametros:
                tipo bitmap:
                     buffer: imagen temporal antes de imprimir la sala
                  
                  */  
      void  Imprimir2(BITMAP *buffer){
          
         blit(buffer,screen,0,0, 0,0,ANCHO,ALTO);
    }
    
