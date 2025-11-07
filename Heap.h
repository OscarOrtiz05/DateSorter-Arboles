//
// Created by oscal on 11/5/2025.
//

#ifndef DATSORTERCPP_ARBOLES_HEAP_H
#define DATSORTERCPP_ARBOLES_HEAP_H

#include<iostream>
#include<cmath>

using namespace std;

//Clase Restaurante para guardar los valores de los restaurantes
class Restaurante {
public:
    string nombre; //Nombre del restaurante
    int totalOrdenes; //Número total de órdenes
    int totalIngreso; //Ingreso total

    //Constructor default
    Restaurante() {
        nombre = "";
        totalOrdenes = 0;
        totalIngreso = 0;
    }

    //Constructor por nombre
    Restaurante(string _nombre, int ingreso) {
        nombre = _nombre;
        totalOrdenes = 1;//Se inicializa en 1 porque es la primer orden que se registra
        totalIngreso = ingreso;
    }

};

/* un heap implementado sobre un arreglo de tipo Restaurante */
class Heap
{	public:
    //	un arreglo de tipo Restaurante, tamaño máximo y actual del heap
    Restaurante *data;
    int maxSize;
    int currentSize;

    //Constructor del Heap de tamaño de n
    Heap (int n)
    {	maxSize = n;
        currentSize = 0;
        data = new Restaurante[maxSize];
    }

    //Destructor del Heap
    //se tiene que especificar porque usa memoria dinámica
    ~Heap()
    {
        delete[] data;
        maxSize = 0;
        currentSize = 0;
    }

    bool isEmpty();
    bool isFull();

    Restaurante getTop();
    int	parent(int);
    int left(int);
    int right(int);

    void push(string,int);
    void swap(int, int);
    int search(string);

    void heapifyOrden(int);
    void reacomodarPorOrdenes();
    Restaurante popOrden();

    void heapifyIngreso(int);
    void reacomodarPorIngresos();
    Restaurante popIngreso();


};

//Para saber si el Heap está vacío
//Complejidad O(1)
bool Heap::isEmpty()
{	return currentSize == 0; }

//Para saber si el Heap está lleno
//Complejidad O(1)
bool Heap::isFull()
{	return currentSize == maxSize; }

//	Regresa la raiz
//Complejidad O(1)
Restaurante Heap::getTop()
{	return data[0]; }

//Obtiene el padre del nodo
//Complejidad O(1)
int Heap::parent( int j)
{	int p = (j - 1) / 2;
    return p;  	}

//Obtiene el hijo izquierdo
//Complejidad O(1)
int Heap::left( int j)
{	int l = 2*j + 1;
    return l;	}

//Obtiene el hijo derecho
//Complejidad O(1)
int Heap::right( int j)
{	int r = 2*j + 2;
    return r; 	}

//Agrega un valor al heap
//Complejidad O(log n)
void Heap::push( string value, int n )
{
    //Revisa que no esté lleno
    if (!this->isFull())
    {
        //Inicializa los índices donde se
        //comenzará el proceso de inserción
        int j =  currentSize;
        int p = parent(j);

        //Reacomoda los nodos para después insertar manteniendo la propiedad del Heap
        while (j > 0 && value < data[p].nombre)
        {
            //Mueve el valor del índice p al índice j
            data[j] = data[p];

            //Avanza j y p
            j = p;
            p = parent(j);
        }

        //Inserta el nuevo valor
        data[j] = Restaurante(value, n);
        currentSize++;
    }else {
        //Avisa cunando el Heap está lleno
        cout << "Heap lleno" << endl;
    }
}

//intercambia los valores de dos posiciones a y b
//Complejidad O(1)
void Heap::swap( int a, int b )
{	Restaurante aux = data[a];
    data[a] = data[b];
    data[b] = aux;
}

//Busca un valor en el Heap por nombre del Restaurante
//Complejidad O(n)
int Heap::search( string value ) {
    //Itera sobre toda la lista hasta encontrar el valor
    for (int i = 0; i < currentSize; i++) {
        //Regresa el índice si encuentra el valor
        //Busca por nombre
        if (data[i].nombre == value) return i;
    }
    //Regresa -1 si no los encuentra
    return -1;
}

//Hace heapify al heap basandose en totalOrdenes
//Complejidad O(log n)
void Heap::heapifyOrden( int index ) {
    //Obtiene los índices de los hijos
    int L = left(index), R = right(index), i = index;

    //Encuentra el mayor de los tres valores
    if (L < currentSize && data[L].totalOrdenes > data[i].totalOrdenes) i=L;
    if (R < currentSize && data[R].totalOrdenes > data[i].totalOrdenes) i=R;

    //Verifica si el mayor es uno de los hijos
    if (i != index) {
        //Intercambia los valores y vuelva a llamar a la función
        swap(index, i);
        heapifyOrden(i);
    }
}

//Reacomoda el Heap a un Max-Heap por total de órdenes
//Complejidad O(n)
void Heap::reacomodarPorOrdenes() {
    //Llama al heapifyOrden empezando por el último nodo con hijos
    for (int i = currentSize / 2 - 1; i >= 0; i--) {
        heapifyOrden(i);
    }
}

//Libera los valores del Heap manteniendo un Max-Heap de órdenes
//Compleajidad O(log n)
Restaurante Heap::popOrden() {
    if (!isEmpty()) {
        //Remplaza el primer valor por el último y decrementa el tamaño
        Restaurante aux = data[0];
        data[0] = data[currentSize-1];
        currentSize--;

        //Reacomoda el heap manteniendo un Max-Heap de órdenes
        heapifyOrden(0);

        //Regresa el valor eliminado
        return aux;
    }

    //Advierte que el heap está vacio
    cout << "Heap vacio" << endl;
    return Restaurante();
}

//Hace heapify al heap basandose en totalOrdenes
//Complejidad O(log n)
void Heap::heapifyIngreso(int index) {
    //Obtiene los índices de los hijos
    int L = left(index), R = right(index), i = index;

    //Encuentra el mayor de los tres valores
    if (L < currentSize && data[L].totalIngreso > data[i].totalIngreso) i=L;
    if (R < currentSize && data[R].totalIngreso > data[i].totalIngreso) i=R;

    //Verifica si el mayor es uno de los hijos
    if (i != index) {
        //Intercambia los valores y vuelva a llamar a la función
        swap(index, i);
        heapifyIngreso(i);
    }
}

//Reacomoda el Heap a un Max-Heap por total de ingresos
//Complejidad O(n)
void Heap::reacomodarPorIngresos() {
    //Llama al heapifyIngreso empezando por el último nodo con hijos
    for (int i = currentSize / 2 - 1; i >= 0; i--) {
        heapifyIngreso(i);
    }
}
//Libera los valores del Heap manteniendo un Max-Heap de ingresos
//Complejidad O(log n)
Restaurante Heap::popIngreso() {
    if (!isEmpty()) {
        //Remplaza el primer valor por el último y decrementa el tamaño
        Restaurante aux = data[0];
        data[0] = data[currentSize-1];
        currentSize--;

        //Reacomoda el heap manteniendo un Max-Heap de ingresos
        heapifyIngreso(0);

        //Regresa el valor eliminado
        return aux;
    }

    //Advierte que el heap está vacio
    cout << "Heap vacio" << endl;
    return Restaurante();
}

#endif //DATSORTERCPP_ARBOLES_HEAP_H