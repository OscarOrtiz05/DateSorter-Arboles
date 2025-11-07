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
    };

};

/* un heap implementado sobre un arreglo de cualquier tipo de dato */
class Heap
{	public:
    //	un arreglo de tipo T, tamano maximo y actual del heap
    Restaurante *data;
    int maxSize;
    int currentSize;

    Heap (int n)
    {	maxSize = n;
        currentSize = 0;
        data = new Restaurante[maxSize];
    }

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
    Restaurante pop();
    void heapifyNombre(int);
    void swap(int, int);
    void show();

    int search(string);

    void heapifyOrden(int);
    void reacomodarPorOrdenes();
    Restaurante popOrden();

    void heapifyIngreso(int);
    void reacomodarPorIngresos();
    Restaurante popIngreso();


};

bool Heap::isEmpty()
{	return currentSize == 0; }

bool Heap::isFull()
{	return currentSize == maxSize; }

//	Regresa la raiz
Restaurante Heap::getTop()
{	return data[0]; }

int Heap::parent( int j)
{	int p = (j - 1) / 2;
    return p;  	}

int Heap::left( int j)
{	int l = 2*j + 1;
    return l;	}

int Heap::right( int j)
{	int r = 2*j + 2;
    return r; 	}

void Heap::push( string value, int n )
{   if (!this->isFull())
    {   int j =  currentSize;
        int p = parent(j);

        while (j > 0 && value < data[p].nombre)
        {
            data[j] = data[p];

            j = p;
            p = parent(j);
        }

        data[j] = Restaurante(value, n);
        currentSize++;

    }else {
        cout << "Heap lleno" << endl;
    }

}

//	intercanbia los valores de dos posiciones a y b
void Heap::swap( int a, int b )
{	Restaurante aux = data[a];
    data[a] = data[b];
    data[b] = aux;
}

void Heap::heapifyNombre( int index )
{
    int L = left(index), R = right(index), i = index;

    if (L < currentSize && data[L].nombre > data[i].nombre) i=L;

    if (R < currentSize && data[R].nombre > data[i].nombre) i=R;

    if (i != index) {
        swap(index, i);
        heapifyNombre(i);
    }

}

Restaurante Heap::pop( )
{
    if (!isEmpty()) {
        //Remplaza el primer valor por el ultimo y decrementa el tamaño
        Restaurante aux = data[0];
        data[0] = data[currentSize-1];
        currentSize--;

        //Reacomoda la pila
        heapifyNombre(0);

        //Regresa el valor eliminado
        return aux;
    }

    //Advierte que el heap está vacio
    cout << "Heap vacio" << endl;
    return Restaurante();

}

void Heap::show( )
{	int i;
    int level = 0;
    cout << "Size: " << currentSize << endl ;

    i = pow(2, level);
    while( i-1 < currentSize)
    {	cout << "\t" << data[i-1].nombre << "(Ordenes: " << data[i-1].totalOrdenes << ", Ingresos: " << data[i-1].totalIngreso << ")\n";
        i++;
        if ( (i) == pow(2, level+1) )
        {
            level++;
        }
    }
    cout << endl ;
}

int Heap::search( string value ) {
    for (int i = 0; i < currentSize; i++) {
        if (data[i].nombre == value) return i;
    }
    return -1;

}

void Heap::heapifyOrden( int index ) {
    int L = left(index), R = right(index), i = index;

    if (L < currentSize && data[L].totalOrdenes > data[i].totalOrdenes) i=L;

    if (R < currentSize && data[R].totalOrdenes > data[i].totalOrdenes) i=R;

    if (i != index) {
        swap(index, i);
        heapifyOrden(i);
    }
}

void Heap::reacomodarPorOrdenes() {
    for (int i = currentSize / 2 - 1; i >= 0; i--) {
        heapifyOrden(i);
    }
}

Restaurante Heap::popOrden() {
    if (!isEmpty()) {
        //Remplaza el primer valor por el ultimo y decrementa el tamaño
        Restaurante aux = data[0];
        data[0] = data[currentSize-1];
        currentSize--;

        //Reacomoda la pila
        heapifyOrden(0);

        //Regresa el valor eliminado
        return aux;
    }

    //Advierte que el heap está vacio
    cout << "Heap vacio" << endl;
    return Restaurante();
}

void Heap::heapifyIngreso(int index) {
    int L = left(index), R = right(index), i = index;

    if (L < currentSize && data[L].totalIngreso > data[i].totalIngreso) i=L;

    if (R < currentSize && data[R].totalIngreso > data[i].totalIngreso) i=R;

    if (i != index) {
        swap(index, i);
        heapifyIngreso(i);
    }
}

void Heap::reacomodarPorIngresos() {
    for (int i = currentSize / 2 - 1; i >= 0; i--) {
        heapifyIngreso(i);
    }
}

Restaurante Heap::popIngreso() {
    if (!isEmpty()) {
        //Remplaza el primer valor por el ultimo y decrementa el tamaño
        Restaurante aux = data[0];
        data[0] = data[currentSize-1];
        currentSize--;

        //Reacomoda la pila
        heapifyIngreso(0);

        //Regresa el valor eliminado
        return aux;
    }

    //Advierte que el heap está vacio
    cout << "Heap vacio" << endl;
    return Restaurante();
}

#endif //DATSORTERCPP_ARBOLES_HEAP_H