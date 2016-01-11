#include <iostream>
using std::cout;
using std::endl;

#include "Nodo.h"

//definizione della classe Lista Linkata:
template <class T>
class ListaLinkata
{
	private:
		Nodo<T>* Testa; //Head
		Nodo<T>* Coda; //Tail
		Nodo<T>* Corrente; //Current
		Nodo<T>* Prev; //Previous
		int Size;
		int Position;

		Nodo<T>* creaNodo( const T& , Nodo<T>* );
		void cancellaNodo( Nodo<T>* punt ) { delete punt; };
		void copiaLista( const ListaLinkata<T>& );
	public:
		ListaLinkata() { Testa = Coda = Corrente = Prev = NULL ; Size = 0 ; Position = -1; };  //Default constructor
		ListaLinkata( const ListaLinkata<T>& lista ) { Testa = Coda = Corrente = Prev = NULL ; Size = 0 ; Position = -1; copiaLista( lista ); };
		~ListaLinkata() { clearLista(); };
		ListaLinkata<T>& operator= ( const ListaLinkata<T>& );
		int getSize() const { return Size; };
		int ListaVuota() const { return Size == 0; }
		void reset ( int );								// aggiorna i puntatori Corrente e Prev // Updates pointers to current and previous nodes
		void next();									// passa al nodo successivo
		int fineLista() const { return Corrente == NULL; };
		int getPosition() const { return Position; };
		void inserisciTesta ( const T& );
		void inserisciCoda( const T& );
		void inserisci( const T& );
		void insertAfter( const T& );
		T eliminaTesta();
		void cancellaQui();
		T& getDato();
		void clearLista();
};

// implementazione del metodo privato "creaNodo" della Lista Linkata:
template <class T>
Nodo<T>* ListaLinkata<T>::creaNodo( const T& item , Nodo <T>* ptrnext = NULL ) //Here item is the cost in AND-OR graph
{
	Nodo<T>* nuovo;
	nuovo = new Nodo<T>( item , ptrnext ); //Node class constructor

	// verifica dell'avvenuta allocazione:
	if ( nuovo == NULL )
	{
		cout<<"Allocazione di memoria fallita." <<endl;
		exit(1);
	}

	return nuovo;
};

// implementazione del metodo privato "copiaLista" della Lista Linkata:
template <class T>
void ListaLinkata<T>::copiaLista( const ListaLinkata<T>& list )
{
	Nodo<T>* ptr = list.Testa;
	int pos;

	while ( ptr != NULL )
	{
		inserisciCoda( ptr->Dato );
		ptr = ptr->getNext();
	}

	// se la lista � vuota la funzione termina:
	if ( Position == -1 )
		return;

	// aggiornamento dei campi nella lista corrente:
	Prev = NULL;
	Corrente = Testa;

	for ( pos = 0 ; pos != position ; pos++ )
	{
		Prev = Corrente;
		Corrente = Corrente->getNext();
	}
};

// ridefinizione dell'operatore di assegnazione per la Lista Linkata:
template <class T>
ListaLinkata<T>& ListaLinkata<T>::operator= ( const ListaLinkata<T>& lista )
{
	// verifica che la lista passata come parametro NON � quella chiamante:
	if ( this == &lista )
		return *this;

	clearLista();
	copiaLista ( lista );

	return *this;
};

// implementazione della funzione "reset" della Lista Linkata:
template <class T>
void ListaLinkata<T>::reset( int pos = 0 )
{
	int startPos;

	// se la lista � vuota la funzione termina:
	if ( Testa == NULL )
		return;
	// se la posizione non � valida, il programma termina:
	if ( pos < 0 || pos >= Size )
		return;

	if ( pos == 0 )
	{
		Prev = NULL;
		Corrente = Testa;
		Position = 0;
	}
	else
	{
		Corrente = Testa->getNext();
		Prev = Testa;
		startPos = -1;

		for ( Position = startPos ; Position < Pos ; Position++ )
		{
			Prev = Corrente;
			Corrente = Corrente->getNext();
		}
	}
};

// implementazione della funzione "next" della Lista Linkata:
template <class T>
void ListaLinkata<T>::next()
{
	if ( Corrente != NULL )
	{
		Prev = Corrente;
		Corrente = Corrente->getNext();
		Position++;
	}
};

// implementazione della funzione "inserisciTesta" della Lista Linkata:
template <class T>
void ListaLinkata<T>::inserisciTesta( const T& item )
{
	// posizionamento alla testa della lista se questa non � vuota:
	if ( Testa != NULL )
		reset();

	inserisci( item );
};

// implementazione della funzione "inserisciCoda" della Lista Linkata:
template <class T>
void ListaLinkata<T>::inserisciCoda( const T& item )
{
	Nodo<T>* nuovo = creaNodo( item );
	Prev = Coda;

	// se la lista � vuota, inserimento in testa:
	if ( Coda == NULL )
		Testa = Coda = nuovo;
	else
	{
		Coda->insertAfter( nuovo );
		Coda = nuovo;
	}

	// aggiornamento dei puntatori:
	Corrente = Coda;
	Position = Size;
	Size++;
};

// implementazione della funzione "inserisci" della Lista Linkata:
template <class T>
void ListaLinkata<T>::inserisci( const T& item )
{
	Nodo<T>* nuovo;

	// inserimento in testa alla lista:
	if ( Prev == NULL )
	{
		nuovo = creaNodo( item , Testa );
		Testa = nuovo;
	}
	// inserimento all'interno della lista:
	else
	{
		nuovo = creaNodo( item );
		Prev->insertAfter( nuovo );
	}

	// inserimento in coda alla lista:
	if ( Prev == Coda )
	{
		Coda = nuovo;
		Position = Size;
	}

	// aggiornamento dei puntatori:
	Corrente = nuovo;
	Size++;
};

// implementazione della funzione "insertAfter" della Lista Linkata (RICORSIVA):
template <class T>
void ListaLinkata<T>::insertAfter( const T& item )
{
	Nodo<T>* punt;
	punt = creaNodo( item );

	// inserimento in una lista vuota:
	if ( Testa = NULL )
	{
		Testa = Corrente = Coda = punt;
		Position = 0;
	}
	else
	{
		if ( Corrente == NULL )
			Corrente = Prev;

		Corrente->insertAfter( punt );

		if ( Corrente == Coda )
		{
			Coda = punt;
			Position = Size;
		}
		else
			Position++;

		Prev = Corrente;
		Corrente = punt;
	}
	Size++;
};

// implementazione della funzione "eliminaTesta" della Lista Linkata:
template <class T>
T ListaLinkata<T>::eliminaTesta()
{
	T item;
	reset();
	if ( Testa == NULL )
	{
		cout<<"Impossibile cancellare da una lista vuota" <<endl;
		exit(1);
	}
	item = Testa->Dato;
	cancellaQui();
	return item;
};

// implementazione della funzione "cancellaQui" della Lista Linkata:
template <class T>
void ListaLinkata<T>::cancellaQui()
{
	Nodo<T>* punt;

	if ( Corrente == NULL )
	{
		cout<<"Impossibile cancellare da una lista vuota" <<endl;
		exit(1);
	}

	if ( Prev == NULL )
	{
		punt = Testa;
		Testa = Testa->getNext();
	}

	punt = Prev->deleteAfter();

	if ( punt == Coda )
	{
		Coda = Prev;
		Position--;
	}

	Corrente = punt->getNext();
	cancellaNodo( punt );
	Size--;
};

// implementazione della funzione "getDato" della Lista Linkata:
template <class T>
T& ListaLinkata<T>::getDato()
{
	if ( Size == 0 || Corrente == NULL )
	{
		cout<<"Impossibile leggere il dato indicato. Riferimento inesistente" <<endl;
		exit(1);
	}
	return (Corrente->Dato);
};

// implementazione della funzione "clearLista" della Lista Linkata:
template <class T>
void ListaLinkata<T>::clearLista()
{
	Nodo<T>* currPos = Testa;
	Nodo<T>* nextPos;

	while ( currPos != NULL )
	{
		nextPos = currPos->getNext();
		cancellaNodo( currPos );
		currPos = nextPos;
	}
	Testa = Coda = Corrente = Prev = NULL;
	Size = 0;
	Position = -1;
};
