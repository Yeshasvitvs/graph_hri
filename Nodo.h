#include <iostream>
using std::cout;
using std::endl;

//definizione della classe Nodo:
template <class T>
class Nodo
{
	private:
		Nodo<T>* next; // This is the node data type with in the node class
	public:
		T dato; //is the type name with the data

		Nodo( const T& , Nodo<T>* );
		Nodo<T>* getNext() const { return next; };
		void inserisciDopo( Nodo<T>* );				// inserisce un nodo dopo quello corrente
		Nodo<T>* cancellaDopo();					// elimina il nodo dopo quello corrente
};

//implementazione del costruttore della classe Nodo:
template <class T>
Nodo<T>::Nodo( const T& valore , Nodo<T>* prossimo = NULL )
{
	dato = valore;
	next = prossimo;
}

//implementazione della funzione "inserisciDopo" della classe Nodo:
template <class T>
void Nodo<T>::inserisciDopo( Nodo<T>* successivo )
{
	successivo->next = next; //How exactly does this assignment work??
	next = successivo;
}

//implementazione della funzione "cancellaDopo" della classe Nodo:
template <class T>
Nodo<T>* Nodo<T>::cancellaDopo()
{
	Nodo<T>* temp;
	temp = next;

	if ( next == NULL )
		return NULL;

	next = temp->next;

	return temp;
}
