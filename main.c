#include <stdio.h>
#include <stdlib.h>


typedef struct lista {
    int num;
    struct lista *sig;
} nodo;



void crear (nodo *);
void mostrar(nodo *);
nodo* insertar1(nodo*);
nodo* eliminar1(nodo*,float  );
void insertar2 (nodo* );
void eliminar2(nodo*,float  );
void insertMayorProm(nodo*,nodo*,float);
//---------------------------------------------------------------------------------------------------
void insertMayorProm(nodo*vieja,nodo*nueva,float promedio){
   while (vieja->sig!=NULL) {
        if(vieja->num > promedio) {//CONDICION DE GENERACION!!!!
            //COPIO LA INFORMACION DEL NODO VIEJO AL NODO NUEVO
            nueva->num=vieja->num;
            //PIDO EL PROX. NUEVO NODO PARA LA LISTA NUEVA
            nueva->sig=(nodo*)malloc(sizeof(nodo));
            //PASO A LA DIRECCION DEL NUEVO NODO
            nueva=nueva->sig;
        }
        //SIGO RECORRIENDO LA LISTA VIEJA
        vieja=vieja->sig;
    }
    nueva->sig=NULL;

}


//----------------------------------------------------------------------------------------------
void crear (nodo *registro) {
    scanf("%d",&registro->num);
    if (registro->num==-2)
        registro->sig=NULL;
    else {
        registro->sig=(nodo*)malloc(sizeof(nodo));
        crear (registro->sig);
    }
    return;
}
//----------------------------------------------------------------------------------------------
void mostrar (nodo *registro) {
    if (registro->sig !=NULL) {
        printf ("%d\n",registro->num);
        mostrar (registro->sig);
    }
    return;
}
//----------------------------------------------------------------------------------------------
nodo* insertar1(nodo *p) {
    nodo *aux;
    if(1) { //condicion de insercion
        aux=(nodo *)malloc(sizeof(nodo));
        aux->num=0;//valor a insertar
        aux->sig=p;
        p=aux;
    }
    return p;
}
//----------------------------------------------------------------------------------------------
void insertar2 (nodo *p) {
    nodo *aux;
    while(p->sig!=NULL) {
        if(1) { //condicion de insercion
            aux=(nodo *)malloc(sizeof(nodo));
            aux->num=0;//valor a insertar
            aux->sig=p->sig;
            p->sig=aux;
        }
        p=p->sig;
    }
}
//----------------------------------------------------------------------------------------------
nodo* eliminar1(nodo* p,float promedio) {
    nodo *aux;
    while(aux->num < promedio) { //condicion de eliminacion
        aux=p->sig;
        free(p);
        p=aux;
    }
    return p;
}
//----------------------------------------------------------------------------------------------
void eliminar2(nodo* p,float promedio) {//NUNCA SE TRABAJA SOBRE EL PRIMER NODO
    nodo *aux;
    while(p->sig!=NULL&& p->sig->sig!=NULL) {
        if(p->sig->num < promedio) { //condicion de eliminacion  p->sig->num
            aux=p->sig->sig;
            free(p->sig);
            p->sig=aux;
        } else {
            p=p->sig;
        }
    }
}

void generarListaNueva(nodo*vieja,nodo*nueva) {
    while (vieja->sig!=NULL) {
        if(vieja->num%2 !=0) {//CONDICION DE GENERACION!!!!
            //COPIO LA INFORMACION DEL NODO VIEJO AL NODO NUEVO
            nueva->num=vieja->num;
            //PIDO EL PROX. NUEVO NODO PARA LA LISTA NUEVA
            nueva->sig=(nodo*)malloc(sizeof(nodo));
            //PASO A LA DIRECCION DEL NUEVO NODO
            nueva=nueva->sig;
        }
        //SIGO RECORRIENDO LA LISTA VIEJA
        vieja=vieja->sig;
    }
    nueva->sig=NULL;
}

float calcularPromedio(nodo*lista) {
    nodo* aux;
    int suma = 0;
    int contador = 0;

    for(aux=lista; aux->sig!=NULL; aux=aux->sig) {
        suma += aux->num;
        contador ++;
    }

    return (float) suma/contador;
}


void ordenar(nodo* actual) {
    //DATOS QUE CONTIENE LA LISTA (UN AUXILIAR PARA CADA DATO DE LA LISTA)
    int aux;
    nodo *siguiente;

    while(actual->sig != NULL) {
        siguiente = actual->sig;
        while(siguiente->sig !=NULL) {
            if(actual->num > siguiente->num) {//ORDENO DE MENOR A MAYOR CON >
                aux=siguiente->num;
                siguiente->num=actual->num;
                actual->num=aux;
            }
            siguiente = siguiente->sig;
        }
        actual = actual->sig;
    }
}

/**
a)	Crear y mostrar la lista con números enteros. Termina con num=-2.
b)	Insertar en otra lista los números impares. Mostrarla.
b1)	Insertar en otra lista los números MAYORES AL PROMEDIO Mostrarla.
c)	Eliminar todos los valores menores al promedio de la lista original en la lista de números impares. Mostrarla
**/

//----------------------------------------------------------------------------------------------
int main() {
    nodo *prin=(nodo*)malloc(sizeof(nodo));
    printf("\nCREANDO LA LISTA DESDE TECLADO\n");
    crear(prin);
    printf("\nMOSTRANDO LA LISTA CREADA DESDE TECLADO\n");
    mostrar (prin);

    nodo*otropri = (nodo*)malloc(sizeof(nodo));
    generarListaNueva(prin,otropri);
    printf("\nMOSTRANDO LA LISTA GENERADA DESDE LA OTRA LISTA\n");
    mostrar (otropri);

    float promedio = calcularPromedio(prin);
    printf("\nPROMEDIO: %f",promedio);
    otropri=eliminar1(otropri,promedio);
    printf("\nELIMINAR1 OK");
    eliminar2(otropri,promedio);
    printf("\nMOSTRANDO LA LISTA GENERADA DESDE LA OTRA LISTA DESPUES DE ELIMINAR\n");
    mostrar (otropri);
    ordenar(prin);
    printf("\nMOSTRANDO LA LISTA GENERADA DESDE TECLADO ORDENADA\n ");
    mostrar (prin);
    nodo *mayores=(nodo*)malloc(sizeof(nodo));
    insertMayorProm(prin,mayores,promedio);
    printf("\nMOSTRANDO LA LISTA GENERADA CON MAYORES AL PROMEDIO DE LA LSTA CREADA DESDE TECLADO\n ");
    mostrar (mayores);

    /*
     prin=insertar1(prin);
     insertar2(prin);
     prin=eliminar1(prin);
     eliminar2(prin);
     mostrar(prin);
     */
    return 0;
}

