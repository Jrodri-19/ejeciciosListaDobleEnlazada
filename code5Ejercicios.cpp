/*
AUTOR:
CALLO HUAYNA, JUAN RODRIGO
*/
#include <iostream>
//-------------------------------------------------------------
//Definición de la clase Node----------------------------------
//-------------------------------------------------------------
template<typename T>
class Node {
public:
	//--------Constructor
	Node(T data) : data(data), next(nullptr), prev(nullptr) {}
	//--------Destructor
	~Node() {
		// No hay memoria dinamica, no necesita un destructor
	}
	//--------Getter y Setter
	//----Data
	T getData() const { return data; }
	void setData(T newData) { data = newData; }
	//----Next
	Node<T>* getNext() const { return next; }
	void setNext(Node<T>* newNext) { next = newNext; }
	//----Prev
	Node<T>* getPrev() const { return prev; }
	void setPrev(Node<T>* newPrev) { prev = newPrev; }
	
private:
		T data;
		Node<T>* next;
		Node<T>* prev;
};
//-------------------------------------------------------------
//Definición de la clase LinkedList----------------------------
//-------------------------------------------------------------
template<typename T>
class DoubleLinkedList {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	//--------Constructor
	DoubleLinkedList() : head(nullptr), tail(nullptr) {}
	//--------Destructor
	~DoubleLinkedList() {
		Node<T>* current = head; 	//puntero a mover
		Node<T>* nextNode;			//puntero temporal
		while (current != nullptr) {
			nextNode = current->getNext();	
			delete current;
			current = nextNode;
		}
	}
	// Método para obtener el puntero al head (método público)
	Node<T>* getHeadPtr() const {
		return head;
	}
	
	// Método para establecer el puntero al head (método público)
	void setHeadPtr(Node<T>* newHead) {
		head = newHead;
	}
	
	// Método para obtener el puntero al tail (método público)
	Node<T>* getTailPtr() const {
		return tail;
	}
	
	// Método para establecer el puntero al tail (método público)
	void setTailPtr(Node<T>* newTail) {
		tail = newTail;
	}
	//--------Métodos
	//---------------------------------------------------------
	//IMPRIMIR-------------------------------------------------
	//---------------------------------------------------------
	//----Método para imprimir la lista
	void print_list() const {
		Node<T>* temp = head;					//puntero temporal
		std::cout << "nullptr" << " <-> "; 		//Es el previus del primer nodo
		while (temp != nullptr) {
			std::cout << temp->getData() << " <-> ";
			temp = temp->getNext();				//recorre temp por la doble lista
		}
		std::cout << "nullptr\n" << std::endl; 	//Es el next del ultimo nodo
	}
	//----Método para imprimir la lista en reversa
	void print_reverse() const{
		Node<T>* temp = tail;					//puntero temporal
		std::cout<<"nullptr"<< " <-> ";  		//Es el next del ultimo nodo
		while (temp != nullptr) {
			std::cout << temp->getData() << " <-> ";
			temp = temp->getPrev();				//recorre temp por la doble lista
		}
		std::cout << "nullptr\n" << std::endl; 	//Es el previus del primer nodo
		return;
	}
	//---------------------------------------------------------
	//INSERTAR-------------------------------------------------
	//---------------------------------------------------------
	// Método para insertar al frente
	void push_front(T data) {
		Node<T>* newNode = new Node<T>(data); 	//Creo un nuevo nodo con el dato
		if(head == nullptr){					//Si no hay ningun nodo
			head = newNode;						//Tanto head como tail apuntan
			tail = newNode;						//al mismo nodo
			return;
		}
		//Si hay más de un nodo
		head -> setPrev(newNode);				//Asigno el previo de head a newNode
		newNode->setNext(head);					//Asigno el next de newNode a head
		head = newNode;							//Asignamos head al nuevo nodo
		return;
	}
	// Método para insertar por atras
	void push_back(T data) {
		Node<T>* newNode = new Node<T>(data);	//Creo un nuevo nodo con el dato
		if(head == nullptr){					//Si no hay ningun dato
			head = newNode;						//Tanto head como tail apuntan
			tail = newNode;						//al mismo nodo
			return;
		}
		//Si hay más de un nodo
		tail -> setNext(newNode);				//Asigno el next de tail a newNode
		newNode->setPrev(tail);					//Asigno el previo de newNode a tail
		tail = newNode;							//Asignamos tail al nuevo nodo
		return;
	}
	//---------------------------------------------------------
	//ELIMINAR-------------------------------------------------
	//---------------------------------------------------------
	// Método para eliminar por frente
	void pop_front() {
		if(head == nullptr ){					//Si no hay ningun nodo
			return;								//Retornar ya que no hay nodo por eliminar
		}
		if(head == tail ){						//Si hay un solo nodo
			Node<T>* temp = head;				//Asigno un puntero que apunte al unico nodo  
			head = nullptr;						//El head apuntando a nulo ya que no habria ningun nodo
			tail = nullptr;						//El tail apuntando a nulo ya que no habria ningun nodo
			delete temp;						//Elimino el unico nodo
			return;
		}
		//Si hay más de un nodo
		Node<T>* temp = head;					//Asigno un temporal para el head(primer nodo)
		head=head->getNext();					//Cambios el head al segundo nodo
		head->setPrev(nullptr);					//Este nuevo head asignamos su previo a nulo
		delete temp;							//Eliminamos el temporal apuntado a al primer nodo
		return;
	}
	// Método para eliminar por atras
	void pop_back() {
		if(head == nullptr ){					//Si no hay ningun nodo
			return;								//Retornar ya que no hay nodo por eliminar
		}
		if(head == tail ){						//Si hay un solo nodo
			Node<T>* temp = tail;				//Asigno un puntero que apunte al unico nodo 
			head = nullptr;						//El head apuntando a nulo ya que no habria ningun nodo
			tail = nullptr;						//El tail apuntando a nulo ya que no habria ningun nodo
			delete temp;						//Elimino el unico nodo
			return;
		}
		//Si hay más de un nodo
		Node<T>* temp = tail;					//Asigno un temporal para el tail(ultimo nodo)
		tail=tail->getPrev();					//Cambios el tail al penultimo nodo
		tail->setNext(nullptr);					//Este nuevo tail asignamos su next a nulo
		delete temp;							//Eliminamos el temporal apuntado a al ultimo nodo
		return;
	}
	//---------------------------------------------------------
	//GETTER---------------------------------------------------
	//---------------------------------------------------------
	// Método para get en front
	T getfront() const {
		try{
			if(head == nullptr){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			return head -> getData();
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en getData(): "<<e.what()<<std::endl;
			return T();
		}
	}
	// Método para get en back
	T getback() const {
		try{
			if(head == nullptr ){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			return tail -> getData();
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en getData(): "<<e.what()<<std::endl;
			return T();
		}
	}
	//---------------------------------------------------------
	//SETTER---------------------------------------------------
	//---------------------------------------------------------
	// Método para set en front
	void setfront(T data) {
		try{
			if(head == nullptr){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			head -> setData(data);
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en setData(): "<<e.what()<<std::endl;
			return;
		}
	}
	// Método para set en back
	void setback(T data) {
		try{
			if(head == nullptr ){
				throw std::runtime_error("Intento de acceso a un nodo nulo");
			}
			tail -> setData(data);
			return ;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción en setData(): "<<e.what()<<std::endl;
			return ;
		}
	}
	//---------------------------------------------------------
	//COMPROBACION DE LISTA VACIA------------------------------
	//---------------------------------------------------------
	bool empty() {
		if(head == tail && head== nullptr){
			return true;
		}
		return false; 
	}
	//---------------------------------------------------------
	//ELIMINAR TODOS LOS ELEMENTOS-----------------------------
	//---------------------------------------------------------
	void clear(){
		while(!empty()){						//Si no esta vacio, eliminar
			pop_front();
			pop_back();
		}
	}
		//---------------------------------------------------------
		//TAMAÑO-----------------------------
		//---------------------------------------------------------
	int sizeDoubleList(){
		Node<T>* temp = head;
		int contador = 0;
		while(temp != nullptr){
			contador++;
			temp = temp->getNext();	
		}
		return contador;
	}
	//---------------------------------------------------------
	//INSERTAR ELEMENTO----------------------------------------
	//---------------------------------------------------------
	void insert(int index, const T valor) {	//index de 0 a dato
		if (index == 0) {
			push_front(valor);
			return;
		}
		int sizeDL=sizeDoubleList();
		try{
			if(sizeDL<index || index<0){
				throw std::runtime_error("Intento de acceso a fuera de rango");
			}
			Node<T>* newNode = new Node<T>(valor);
			Node<T>* temp = head;
			int contador=0;
			while(contador<index-1){
				temp = temp->getNext();	
				contador++;
			}
			newNode->setNext(temp->getNext());
			newNode->setPrev(temp);
			if (temp->getNext() != nullptr) {
				temp->getNext()->setPrev(newNode);
			}
			temp->setNext(newNode);
			if (newNode->getNext() == nullptr) {
				tail = newNode;
			}
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de insercion: "<<e.what()<<std::endl;
			return;
		}
	}
	//---------------------------------------------------------
	//REMOVER ELEMENTO----------------------------------------
	//---------------------------------------------------------
	void remove(int index) {	//index de 0 a dato
		if (index == 0) {
			pop_front();
			return;
		}
		int sizeDL=sizeDoubleList();
		try{
			if(sizeDL<index || index<0){
				throw std::runtime_error("Intento de acceso a fuera de rango");
			}
			Node<T>* temp = head;
			int contador=0;
			while(contador<index-1){
				temp = temp->getNext();	
				contador++;
			}
			if (temp->getNext() == tail) {
				pop_back();
			}
			else {
				Node<T>* nodeToDelete = temp->getNext();
				temp->setNext(nodeToDelete->getNext());
				nodeToDelete->getNext()->setPrev(temp);
				delete nodeToDelete;
			}
			
			return;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de eliminacion: "<<e.what()<<std::endl;
			return;
		}
	}
	//---------------------------------------------------------
	//BUSQUEDA ------------------------------------
	//---------------------------------------------------------
	Node<T>* busquedaNodoPorDato(const T value) const {
		Node<T>* temp = head;
		while (temp != nullptr) {
			if (temp->getData() == value) {
				return temp; 
			}
			temp = temp->getNext();
		}
		return nullptr;  
	}
	int busquedaIndicePorDato( const T valor) {
		Node<T>* datoEncontrado=busquedaNodoPorDato(valor);
		try{
			if(datoEncontrado==nullptr){
				throw std::runtime_error("Dato no encontrado");
			}
			Node<T>* temp = head;
			int contador = 0;
			while (temp != datoEncontrado) {
				temp = temp->getNext();
				contador++;
			}
			return contador;
		} catch(const std::exception& e){
			//Manejo de la excepción
			std::cerr <<"Excepción de insercion: "<<e.what()<<std::endl;
			return -1;
		}
	}
//EJERCICIO 1--Concatenar Dos Listas--------------------------------------------
	void concatenate( DoubleLinkedList<T>* other){
		if(other->head == nullptr){//CASO 1 --- Si la otra lista esta vacia
			return;
		}
		if(this->head == nullptr){//CASO 2 --- Si la lista principal esta vacia
			this->head=other->head;
			this->tail=other->tail;
		}
		else//CASO 3 --- Si no es ni el caso 1 ni el caso 2
		{	
			this->tail->setNext(other->head);
			other->head->setPrev(this->tail);
			this->tail=other->tail;
		}
		other->head=nullptr;
		other->tail=nullptr;
	}
//EJERCICIO 2--Intercalar Dos Listas--------------------------------------------
	void combine( DoubleLinkedList<T>* other){
		if(other->head == nullptr){//CASO 1 --- Si la otra lista esta vacia
			return;
		}
		if(this->head == nullptr){//CASO 2 --- Si la lista principal esta vacia
			this->head=other->head;
			this->tail=other->tail;
		}
		else//CASO 3 --- Si no es ni el caso 1 ni el caso 2
		{	
			Node<T>* temp1 = this->head;
			Node<T>* temp2 = other->head;
			while (temp1 != nullptr && temp2 != nullptr){
				Node<T>* aux1 = temp1->getNext();
				Node<T>* aux2 = temp2->getNext();
				temp1->setNext(temp2);
				temp2->setPrev(temp1);
				if(aux1!= nullptr){
					temp2->setNext(aux1);
					aux1->setPrev(temp2);
				}
				else{
					this->tail=temp2;
					temp2->setNext(nullptr);
				}
				temp1=aux1;
				temp2=aux2;
			}
			if (temp2 != nullptr) {
				// Si la lista `other` es más larga, ajustar el tail
				this->tail->setNext(temp2);
				temp2->setPrev(this->tail);
				this->tail = other->tail;
			}
		}
		
		other->head=nullptr;
		other->tail=nullptr;
	}
//EJERCICIO 3--Dividir una Lista en Dos-----------------------------------------
	DoubleLinkedList<T> split(int position) {
		DoubleLinkedList<T> otherList;
		try {
			if (position <= 0 || position >= sizeDoubleList()) {
				throw std::out_of_range("Posición fuera de rango");
			}
			
			Node<T>* temp = head;
			int count = 0;
			
			// Avanzar hasta la posición deseada
			while (count < position - 1) {
				temp = temp->getNext();
				count++;
			}
			
			// Actualizar punteros para la división
			otherList.head = temp->getNext();
			otherList.tail = tail;
			tail = temp;
			tail->setNext(nullptr) ;
			return otherList;
		}catch (const std::exception& e) {
			std::cerr << "Excepción en split(): " << e.what() << std::endl<<std::endl;
			// Retornar una lista vacía en caso de error
			return otherList;
		}
		
	}
//EJERCICIO 4--Reverir una Lista ----------------------------------------------
	void reverse(){
		if (head == nullptr || head == tail) {
			return;
		}
		Node<T>* temporal = head;
		Node<T>* auxiliar = nullptr;
		while (temporal != nullptr) {
			auxiliar = temporal->getPrev();
			temporal->setPrev(temporal->getNext());
			temporal->setNext(auxiliar);
			temporal = temporal->getPrev(); 
		}
		temporal=head;
		head=tail;
		tail=temporal;
	}
//EJERCICIO 5--Eliminar Duplicados en una Lista Ordenada------------------------
	void remove_duplicates(){
		if (head == nullptr || head == tail) {
			return; 
		}
		Node<T>* current = head; //puntero a recorrer
		while (current != nullptr) {
			T currentData = current->getData(); //dato temporal a comparar
			Node<T>* nextNode = current->getNext();
			while (nextNode != nullptr) {
				if (nextNode->getData() == currentData) {
					Node<T>* temp = nextNode;
					nextNode = nextNode->getNext();
					
					if (temp == tail) {
						tail = temp->getPrev();
					}
					
					if (temp->getPrev() != nullptr) {
						temp->getPrev()->setNext(temp->getNext());
					}
					
					if (temp->getNext() != nullptr) {
						temp->getNext()->setPrev(temp->getPrev());
					}
					
					delete temp;
				} else {
					nextNode = nextNode->getNext();
				}
			}
			
			current = current->getNext();
		}
	}
};

int main() {
//1 - Concatenar
	std::cout<<"\t1 Concatenar\n\n";
	DoubleLinkedList<int>* A = new DoubleLinkedList<int>;
	DoubleLinkedList<int>* B = new DoubleLinkedList<int>;
	//CASO 1	
	A->push_back(1);A->push_back(2);
	A->concatenate(B);
	A->print_list();
	//CASO 2
	A->clear();B->clear();
	B->push_back(3);
	A->concatenate(B);
	A->print_list();
	//CASO 3
	A->clear();B->clear();
	B->push_back(4);
	A->push_back(1);A->push_back(2);A->push_back(3);
	A->concatenate(B);
	A->print_list();
	//Limpiando todo
	A->clear();B->clear();
//2 - Intercalado
	std::cout<<"\t2 Intercalado\n\n";
	//CASO 1	
	A->push_back(1);A->push_back(2);
	A->combine(B);
	A->print_list();
	//CASO 2
	A->clear();B->clear();
	B->push_back(3);
	A->combine(B);
	A->print_list();
	//CASO 3
	A->clear();B->clear();
	B->push_back(4);
	A->push_back(1);A->push_back(2);A->push_back(3);
	A->combine(B);
	A->print_list();
	//CASO 4
	A->clear();B->clear();
	A->push_back(1);A->push_back(2);
	B->push_back(4);B->push_back(5);B->push_back(6);
	A->combine(B);
	A->print_list();
	//Limpiando todo
	A->clear();B->clear();
//3 - Dividir una lista en 2
	std::cout<<"\t3 Dividir una lista en 2\n\n";
	A->push_back(15);
	A->push_back(12);
	A->push_back(2);
	A->push_back(4);
	A->print_list();
	DoubleLinkedList<int> C = A->split(1);
	A->print_list();
	C.print_list();
	//Limpiando todo
	A->clear();B->clear(),C.clear();
//4 - Reveritr una Lista
	std::cout<<"\t4 Reveritr una Lista\n\n";
	A->push_back(1);
	A->push_back(2);
	A->push_back(3);
	A->push_back(4);
	A->print_list();
	A->reverse();
	A->print_list();
	//Limpiando todo
	A->clear();B->clear(),C.clear();
//5 - Eliminar duplicados
	std::cout<<"\t5 Eliminar duplicados\n\n";
	A->push_back(1);
	A->push_back(2);
	A->push_back(2);
	A->push_back(3);
	A->push_back(3);
	A->push_back(3);
	A->push_back(4);
	A->print_list();
	A->remove_duplicates();
	A->print_list();
	delete A,B;
}
