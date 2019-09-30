#include<iostream>
#include<conio.h>

#define topeConjuntos 20

using namespace std;

struct conjunto{
	string nombre;
	string elementos[topeConjuntos];
	int numElementos;
	conjunto *sig;
}*Principal = NULL, *p, *q, *r, *s;

struct elemento{
	string elem;
	elemento * sig;
}*ListadoElementos=NULL, *k, *a,*b;

int menu();
int buscarElemento(string elem, string v[], int tam);
int menuOperaciones();
conjunto* crearConjunto(conjunto *&ptr, string name, int tam, string vec[]);
conjunto* buscarConjunto(conjunto *& ptr, string llave);
elemento* unionConjuntos(conjunto *&conjunto1,conjunto *&conjunto2, elemento *&listaAux);
elemento* interseccionConjuntos(conjunto *&conjunto1,conjunto *&conjunto2, elemento *&listaAux);
elemento* diferenciaConjuntos(conjunto *&conjunto1, conjunto *&conjunto2, elemento *&listaAux);
elemento* diferenciaSimetricaConjuntos(conjunto *&conjunto1, conjunto *&conjunto2, elemento *&listaAux);
elemento* complementoConjuntos(conjunto *&conjunto1, elemento *&universo, elemento *&listaAux);
elemento* insertarElemento(elemento *&ptr,string n);
bool buscarListaElemento(elemento *&ptr, string info);
void mostrarResultado(elemento *&ptr);
void mostrarConjunto(conjunto *& ptr, int opc=1);


//definir universo y terminar complemento
int main(){
	int sw = 1;
	int intAux;
	string strAux,strAux2;
	string vecAux[topeConjuntos] = {"\0"};
	elemento *Universo=NULL;
	do{
		system("cls");
		system("color 2f");
		switch(menu()){
			case 1:
				system("cls");
				cout<<"\n\t\t Nombre Conjunto: ";
				cin>>strAux2;
				cout<<"\n\t\t Cantidad de elementos (max "<<topeConjuntos<<"): ";
				cin>>intAux;
				while(intAux<0 or intAux>topeConjuntos){
					cout<<"\n\t\tError, numero fuera de rango: ";
					cin>>intAux;
				}
				for(int i=0; i<intAux; i++){
					cout<<"\n\t\t Elemento # "<<(i+1)<<": ";
					cin>>strAux;
					if(buscarListaElemento(Universo,strAux)){
						if(buscarElemento(strAux,vecAux,(i+1)) ==  -1){
							vecAux[i] = strAux;
						}
					}else{
						cout<<"\t"<<strAux<<" no pertenece al Universo ";
						while(!buscarListaElemento(Universo,strAux)){
							cout<<"\n\t\t Elemento # "<<(i+1)<<": ";
							cin>>strAux;
						}
						if(buscarElemento(strAux,vecAux,(i+1)) ==  -1){
							vecAux[i] = strAux;
						}
					}
				}
				Principal = crearConjunto(*&Principal, strAux2, intAux,vecAux);
			break;
			case 2:
				system("cls");
				cout<<"\n\t\t\t------------- CONJUNTOS EN MEMORIA----------";
				//aqui paso por parametro a dos para que muestre tambien los elementos de los conjuntos
				mostrarConjunto(Principal,2);
			break;
			case 3:
				system("cls");
				cout<<"\n\t\t\t------------- CONJUNTOS EN MEMORIA----------";
				//el 1 como segundo parametro indica que solo se muestre los nombres de los conjuntos
				mostrarConjunto(Principal,1);
				cout<<"\n\n\n\n\n\t\tPreseione cualquier tecla para continuar";
				getch();
				system("cls");
				
				intAux = menuOperaciones();
				
				if(intAux==5){
					cout<<"\n\t\\tConjunto(nombre): ";
					cin>>strAux;
					q = buscarConjunto(Principal, strAux);
					if(q==NULL){
						cout<<"\n\t\t Ese conjunto no esta registrado :( ";
						cout<<"\n\t\t Presione 1 para reintentar, otra tecla para salir:  ";
						if(getch()==49){
							while(q==NULL){
								cout<<"\n\t\tPrimer Conjunto(nombre): ";
								cin>>strAux;
								q = buscarConjunto(Principal,strAux);
							}
						}else{
							intAux = 0;
						}
						
					}
				}else if(intAux!=0){
					cout<<"\n\t\tPrimer Conjunto(nombre): ";
					cin>>strAux;
					q = buscarConjunto(Principal,strAux);
					if(q==NULL){
						cout<<"\n\t\t Ese conjunto no esta registrado :( ";
						cout<<"\n\t\t Presione 1 para reintentar, otra tecla para salir:  ";
						if(getch()==49){
							while(q==NULL){
								cout<<"\n\t\tPrimer Conjunto(nombre): ";
								cin>>strAux;
								q = buscarConjunto(Principal,strAux);
							}
						}else{
							intAux = 0;
						}
						
					}
					//validando si desea salir (opc otra tecla para salir)
					if(intAux!=0){
						cout<<"\n\t\tSegundo Conjunto(nombre): ";
						cin>>strAux2;
						s = buscarConjunto(Principal,strAux2);
						if(s==NULL){
							cout<<"\n\t\t Ese conjunto no esta registrado :( ";
							cout<<"\n\t\t Presione 1 para reintentar, otra tecla para salir:  ";
							if(getch()==49){
								while(s==NULL){
									cout<<"\n\t\tSegundo Conjunto(nombre): ";
									cin>>strAux2;
									s = buscarConjunto(Principal,strAux2);
								}
							}else{
								intAux = 0;
							}
							
						}
					}
				}
				switch(intAux){
					case 1:
						ListadoElementos = unionConjuntos(q,s,ListadoElementos);
						mostrarResultado(ListadoElementos);
					break;
					
					case 2:
						ListadoElementos = interseccionConjuntos(q,s,ListadoElementos);
						mostrarResultado(ListadoElementos);
					break;
					
					case 3:
						ListadoElementos = diferenciaConjuntos(q,s,ListadoElementos);
						mostrarResultado(ListadoElementos);
					break;
					case 4:
						ListadoElementos = diferenciaSimetricaConjuntos(q,s,ListadoElementos);
						mostrarResultado(ListadoElementos);
					break;
					case 5:
						ListadoElementos = complementoConjuntos(q,Universo,ListadoElementos);
						mostrarResultado(ListadoElementos);
					break;
					default:
						cout<<"Atras";
					break;
				}
				
			break;
			
			case 4:
				cout<<"\n\t\t Cuantos Elementos tiene el Universo: ";
				cin>>intAux;
				for(int t=0;t<intAux; t++){
					cout<<"\n\t\t Elemento #"<<(t+1)<<" : ";
					cin>>strAux;
					Universo = insertarElemento(Universo,strAux);
				}
				cout<<"\n\n\n\n Se ha finalizado la definicion de U";
			break;
			default:
				cout<<"\n\n\n\t\t\t TE ESPERAMOS PRONTO :-)";
				sw=0;
			break;
		}
		getch();
	}while(sw);
	
	
	return 0;
}

void mostrarResultado(elemento *&ptr){
	if(ptr==NULL){
		cout<<"\n\n\t Resultado = /0 'vacio' ";
	}else{
		cout<<"\n\n\t Resultado = {";
		b = ptr;
		while(b!=NULL){
			cout<<b->elem<<",";
			b = b->sig;
		}
		cout<<"} ";
	}
}

void mostrarConjunto(conjunto *& ptr, int opc){
	p = ptr;
	if(opc==1){
		while(p!=NULL){
			cout<<"\n\t\t "<<p->nombre;
			p=p->sig;
		}
	}else{
		while(p!=NULL){
			cout<<"\n\t\t "<<p->nombre<<" = {";
			for(int t=0; t<p->numElementos;t++){
				cout<<p->elementos[t]<<",";
			}
			cout<<"}";
			p=p->sig;
		}
	}
}

elemento* unionConjuntos(conjunto *&conjunto1,conjunto *&conjunto2, elemento *&listaAux){
	if(listaAux==NULL){
		for(int i=0; i<conjunto1->numElementos; i++){
			listaAux = insertarElemento(listaAux, conjunto1->elementos[i]);
		}
		for(int i=0; i<conjunto2->numElementos; i++){
			if(!buscarListaElemento(listaAux,conjunto2->elementos[i])){
				listaAux = insertarElemento(listaAux, conjunto2->elementos[i]);
			}
		}
		return listaAux;
	}else{
		while(listaAux!=NULL){
			a=listaAux;
			listaAux = listaAux->sig;
			delete(a);
		}
		return unionConjuntos(conjunto1, conjunto2, listaAux);
	}
}

elemento* interseccionConjuntos(conjunto *&conjunto1, conjunto *&conjunto2, elemento *&listaAux){
	int pos=-1;
	if(listaAux==NULL){
		for(int i=0; i<conjunto1->numElementos; i++){
			pos = buscarElemento(conjunto1->elementos[i],conjunto2->elementos,conjunto2->numElementos);
			if(pos > -1){
				listaAux = insertarElemento(listaAux,conjunto1->elementos[i]);
			}
		}
		return listaAux;
	}else{
		while(listaAux!=NULL){
			a=listaAux;
			listaAux = listaAux->sig;
			delete(a);
		}
		return interseccionConjuntos(conjunto1, conjunto2, listaAux);
	}
}

elemento* diferenciaConjuntos(conjunto *&conjunto1, conjunto *&conjunto2, elemento *&listaAux){
	int pos=-1;
	if(listaAux==NULL){
		for(int i=0; i<conjunto1->numElementos; i++){
			pos = buscarElemento(conjunto1->elementos[i],conjunto2->elementos,conjunto2->numElementos);
			if(pos == -1){
				listaAux = insertarElemento(listaAux,conjunto1->elementos[i]);
			}
		}
		return listaAux;
	}else{
		while(listaAux!=NULL){
			a=listaAux;
			listaAux = listaAux->sig;
			delete(a);
		}
		return diferenciaConjuntos(conjunto1, conjunto2, listaAux);
	}
}

elemento* diferenciaSimetricaConjuntos(conjunto *&conjunto1, conjunto *&conjunto2, elemento *&listaAux){
	int pos=-1;
	if(listaAux==NULL){
		for(int i=0; i<conjunto1->numElementos; i++){
			pos = buscarElemento(conjunto1->elementos[i],conjunto2->elementos,conjunto2->numElementos);
			if(pos == -1){
				listaAux = insertarElemento(listaAux,conjunto1->elementos[i]);
			}
		}
		for(int i=0; i<conjunto2->numElementos; i++){
			pos = buscarElemento(conjunto2->elementos[i],conjunto1->elementos,conjunto1->numElementos);
			if(pos == -1){
				listaAux = insertarElemento(listaAux,conjunto2->elementos[i]);
			}
		}
		return listaAux;
	}else{
		while(listaAux!=NULL){
			a=listaAux;
			listaAux = listaAux->sig;
			delete(a);
		}
		return diferenciaSimetricaConjuntos(conjunto1, conjunto2, listaAux);
	}
}

elemento* complementoConjuntos(conjunto *&conjunto1, elemento *&universo, elemento *&listaAux){
	if(listaAux==NULL){
		b=universo;
		while(b!=NULL){
			if(buscarElemento(b->elem,conjunto1->elementos,conjunto1->numElementos)==-1){
				listaAux = insertarElemento(listaAux,b->elem);
			}
			b=b->sig;
		}
		return listaAux;
	}else{
		while(listaAux!=NULL){
			a=listaAux;
			listaAux = listaAux->sig;
			delete(a);
		}
		return complementoConjuntos(conjunto1, universo, listaAux);
	}
}

int buscarElemento(string elem, string v[], int tam){
	for(int j=0; j<tam; j++){
		if(elem==v[j]){
			return j;
		}
	}
	return -1;
}

conjunto* buscarConjunto(conjunto *& ptr, string llave){
	r = ptr;
	while(r!=NULL){
		if(r->nombre==llave){
			return r;
		}
		r=r->sig;
	}
	return NULL;
}

bool buscarListaElemento(elemento *&ptr, string info){
	k = ptr;
	while(k!=NULL){
		if(k->elem==info){
			return true;
		}
		k=k->sig;
	}
	return false;
}

int menu(){
	int opcion;
	
	cout<<"\n\n\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t## Software para Operaciones entre conjuntos##\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t#########         OPCIONES          ##########\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t## 1 -> Crear Conjunto                      ##\n";
	cout<<"\t\t\t## 2 -> Consultar Listado de conjuntos      ##\n";
	cout<<"\t\t\t## 3 -> Realizar Operaciones Entre Conjuntos##\n";
	cout<<"\t\t\t## 4 -> Agregar Elementos al Universo       ##\n";
	cout<<"\t\t\t## 0 -> Salir                               ##\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t?: ";
	opcion = getch();
	
	while(opcion<48 or opcion>52){
		cout<<"\n\t\tOpcion invalida, ?:";
		opcion = getch();
	}
	opcion-=48;
	return opcion;
	
}

int menuOperaciones(){
	int opcion;
	
	cout<<"\n\n\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t##       OPERACIONES ENTRE CONJUNTOS        ##\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t#########         OPCIONES          ##########\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t## 1 -> Union                               ##\n";
	cout<<"\t\t\t## 2 -> Interseccion                        ##\n";
	cout<<"\t\t\t## 3 -> Diferencia                          ##\n";
	cout<<"\t\t\t## 4 -> Diferencia Simetrica                ##\n";
	cout<<"\t\t\t## 5 -> Complemento                         ##\n";
	cout<<"\t\t\t## 0 -> Menu Anterior                       ##\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t\t##############################################\n";
	cout<<"\t\t?: ";
	opcion = getch();
	
	while(opcion<48 or opcion>53){
		cout<<"\n\t\tOpcion invalida, ?:";
		opcion = getch();
	}
	opcion-=48;
	return opcion;
}

conjunto* crearConjunto(conjunto *&ptr, string name, int tam, string vec[]){
	
	p = new conjunto;
	p->nombre = name;
	p->numElementos = tam;
	p->sig = NULL;
	
	for(int i=0; i<tam; i++){
		p->elementos[i] = vec[i];
	}
	
	if(ptr==NULL){
		ptr = p;
	}else{
		r= ptr;
		while(r->sig!=NULL){
			r=r->sig;
		}
		r->sig = p;
	}
	return ptr;
}

elemento* insertarElemento(elemento *&ptr, string n){
	k = new elemento;
	k->elem = n;
	if(ptr==NULL){
		ptr = k;
		k->sig = NULL;
	}else{
		k->sig = ptr;
		ptr = k;
	}
	return ptr;
}
