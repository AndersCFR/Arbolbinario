#include <iostream>
#include <stdlib.h>

using namespace std;


//Estructura del nodo
struct Nodo{
	int dato;
	Nodo *derecha;
	Nodo *izquierda;
	Nodo *padre;
};


//Inicialización de funciones
Nodo *crearNodo(int, Nodo *);
void esVacio(Nodo *&);
void insertarNodo(Nodo *&, int, Nodo *);
void mostrarArbol(Nodo *,int);
bool busqueda(Nodo *,int);
void preOrden(Nodo *);
void inOrden(Nodo *);
void postOrden(Nodo *);
void eliminardato(Nodo *,int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar(Nodo *,Nodo *);
void destruirNodo(Nodo *);

//Inicialización del árbol 
Nodo *arbol = NULL;


int main(){
	int dato, opcion;
	int contador=0;
	while(opcion!=9){
		cout<<"\t Arbol binario"<<endl;
		cout<<"Escoge una opcion:"<<endl;
		cout<<"1. Es vacio?"<<endl;
		cout<<"2. Insertar nodo"<<endl;
		cout<<"3. Mostrar arbol"<<endl;
		cout<<"4. Buscar elemento"<<endl;
		cout<<"5. Recorrer arbol en PreOrden"<<endl;
		cout<<"6. Recorrer arbol en InOrden"<<endl;
		cout<<"7. Recorrer arbol en PostOrden"<<endl;
		cout<<"8. Eliminar nodo del arbol"<<endl;
		cout<<"9. Salir"<<endl;
		cin>>opcion;
		switch(opcion){
			
			case 1:
				esVacio(arbol);
				break;

			case 2: 
				cout <<"Valor a ingresar:\n";
				cin>>dato;
				insertarNodo(arbol, dato, NULL);
				cout<<"\n";
				break;
				
			case 3:
				cout<<"\n \n";
				mostrarArbol(arbol, contador);
				cout<<"\n";
				break;
				
			case 4:
				int valor;
				cout<<"Ingrese valor a buscar"<<endl;
				cin>>valor;
				if(busqueda(arbol, valor)==true){
					cout<<"El valor "<<valor<<" se encuentra en el arbol"<<endl;
				}else{
					cout<<"El valor "<<valor<<" NO se encuentra en el arbol"<<endl;
				}
				cout<<"\n";
				break;
				
			case 5:
				cout<<"\n PreOrden"<<endl;
				preOrden(arbol);
				cout<<"\n";
				break;
				
			case 6:
				cout<<"\n InOrden"<<endl;
				inOrden(arbol);
				cout<<"\n";
				break;
			
			case 7:
				cout<<"\n PostOrden"<<endl;
				postOrden(arbol);
				cout<<"\n";
				break;	
			
			case 8:
				int valoreliminar;
				cout<<"\n Ingresa valor a eliminar"<<endl;
				cin>>valoreliminar;
				eliminardato(arbol, valoreliminar);
				cout<<"\n";
				break;			
			
			case 9:
				exit;
				break;
				
		}			
	}
	
	return 0;
}

//Función para ver si el árbol está vacío
void esVacio(Nodo *&arbol){
	if(arbol==NULL){
		cout<<"El arbol esta vacio"<<endl;
	}else{
		cout<<"El arbol tiene nodos"<<endl;
	}
}

//Función para crear un Nodo
Nodo *crearNodo(int n, Nodo *padre){
	Nodo *nuevo_nodo = new Nodo(); //asignando memoria
	nuevo_nodo->dato = n;
	nuevo_nodo->derecha = NULL;
	nuevo_nodo->izquierda = NULL;
	nuevo_nodo->padre = padre;
}


//Función insertar elementos  en el arbol
void insertarNodo(Nodo *&arbol, int n, Nodo *padre){
	if(arbol == NULL){
		//Si el árbol no se ha creado
		Nodo *nuevo_nodo = crearNodo(n, padre);
		arbol= nuevo_nodo;
	}else{
		//Si el árbol ya tiene raíz
		int valorRaiz = arbol->dato; //obtenemos valor de raiz
		if(n < valorRaiz){//si es menor a la raiz insertamos a la izquierda
			insertarNodo(arbol->izquierda,n,arbol);
		}
		else{//si es mayor a la raiz insertamos a la derecha
			insertarNodo(arbol->derecha,n,arbol);
		}
	}
}


//Función para buscar un elemento
bool busqueda(Nodo *arbol, int valorbusqueda){
	if(arbol==NULL){
		return false;
	}else if(arbol->dato == valorbusqueda){
		return true;
	}else if(valorbusqueda < arbol->dato){
		return busqueda(arbol->izquierda, valorbusqueda);
	}else{
		return busqueda(arbol->derecha, valorbusqueda);
	}
}

//Función mostrar en pantalla el árbol binario
void mostrarArbol(Nodo *arbol, int auxiliar){
	if(arbol==NULL){
		return;
	}else{
		mostrarArbol(arbol->derecha, auxiliar+1);
		for(int i=0; i<auxiliar; i++){
			cout<<"   ";
		}
		cout<<arbol->dato<<endl;
		mostrarArbol(arbol->izquierda,auxiliar+1);
	}
}

//Función recorrido en PreOrden
void preOrden(Nodo *arbol){
	if(arbol==NULL){
		return ;
	}
	else{
		cout<<arbol->dato<<" - "; //valor raiz
		preOrden(arbol->izquierda); //valores izquierda
		preOrden(arbol->derecha); //valores derecha
	}
}

//Función recorrido en InOrden
void inOrden(Nodo *arbol){
	if(arbol==NULL){
		return ;
	}
	else{
		inOrden(arbol->izquierda); //valores izquierda
		cout<<arbol->dato<<" - ";  //valor raiz
		inOrden(arbol->derecha); //valores derecha
	}
}

//Función recorrido en PostOrden
void postOrden(Nodo *arbol){
	if(arbol==NULL){
		return ;
	}
	else{
		postOrden(arbol->izquierda); //valores izquierda
		postOrden(arbol->derecha); //valores derecha
		cout<<arbol->dato<<" - "; //valor raiz
	}
}

//Función para eliminar un valor del arbol
void eliminardato(Nodo *arbol, int n){
	if(arbol==NULL){
		return; 
	}else if(n < arbol->dato){//busqueda del valor a eliminar por la izquierda
		eliminardato(arbol->izquierda,n);
	}else if(n > arbol->dato){
		eliminardato(arbol->derecha,n);//busqueda del valor a eliminar por la derecha
	}else{
		eliminarNodo(arbol); //eliminación del nodo
	}
}

//Función para eliminar el nodo
void eliminarNodo(Nodo *nodoEliminar){
	if(nodoEliminar->izquierda and nodoEliminar->derecha){ //caso eliminacion si el nodo tiene dos hijos
		Nodo *menor = minimo(nodoEliminar->derecha);
		nodoEliminar->dato=menor->dato; //reemplazando los punteros
		eliminarNodo(menor);
	}else if(nodoEliminar->izquierda){//caso eliminacion si el nodo tiene hijos a la izquierda
		reemplazar(nodoEliminar, nodoEliminar->izquierda);
		destruirNodo(nodoEliminar);
	}else if(nodoEliminar->derecha){ //caso eliminacion si el nodo tiene hijos a la izquierda
		reemplazar(nodoEliminar, nodoEliminar->derecha);
		destruirNodo(nodoEliminar);
	}else{  //caso eliminacion si el nodo no tiene hijos, ocea es una hoja
		reemplazar(nodoEliminar, NULL);
		destruirNodo(nodoEliminar);
	}
}

//Función destruir nodo
void destruirNodo(Nodo *nodo){
	//elimina dirección memoria del nodo a borrar
	nodo->izquierda=NULL;
	nodo->derecha=NULL;
	delete nodo; 
}

//Función reemplazar nodo para poder eliminar
void reemplazar(Nodo *arbol, Nodo *nuevoNodo){
	if(arbol->padre){
		//reemplazar si el nodo tiene hijos en el lado izquierdo
		if(arbol->dato == arbol->padre->izquierda->dato){
			arbol->padre->izquierda = nuevoNodo;
		}
		//reemplazar si el nodo tiene hijos en el lado derecho
		else if(arbol->dato == arbol->padre->derecha->dato){
			arbol->padre->derecha = nuevoNodo;
		}
	}
	if(nuevoNodo){
		nuevoNodo->padre = arbol->padre; //asignando puntero del nuevo padre 
	}
}

//Función para valor mínimo para poder eliminar nodo
Nodo *minimo(Nodo *arbol){
	if(arbol ==NULL){
		return NULL; //retorna nulo
	}
	if(arbol->izquierda){
		return minimo(arbol->izquierda); //seguir a la izquierda
	}
	else{
		return arbol;
	}
}



