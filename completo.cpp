#include <iostream>
#include <fstream>

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

//Función que lee un archivo de texto y crea un heap con eso
//Complejidad O(n^2)
void loadOrderData(const string& filename, Heap& out, int capacity) {
    int i = 0;
    string rest,sline,m,r,nm,n,d,h,min,s;
    int index;
    ifstream inFile2(filename);
    if (inFile2.is_open()) {
        // Extraer mes, d a, hora, minuto, segundo, restaurante, platillo y precio
        while (getline(inFile2, sline) && i < capacity) {
            string line = sline;
            index = line.find(" ");
            m = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" ");
            d = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(":");
            h = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(":");
            min = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" ");
            s = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(" O:");
            r = line.substr(2, index - 2);
            line = line.substr(index + 3);
            index = line.find("(");
            nm = line.substr(0, index);
            line = line.substr(index + 1);
            index = line.find(")");
            n = line.substr(0, index);

            //Busca el valor en el Heap
            if (int indexHeap = out.search(r); indexHeap != -1) {//Si lo encuentra
                //Suma uno al total de órdenes
                out.data[indexHeap].totalOrdenes++;
                //Suma al total de ingresos
                out.data[indexHeap].totalIngreso += stoi(n);
            }else {
                //Agrega el valor al heap si no lo encuentra
                out.push(r,stoi(n));
            }

            i++;
        }
    }

    inFile2.close();

}

int main() {
    //Declara el heap y el tamaño de este
    int capacity = 10000;
    Heap restaurantes = Heap(capacity);

    //Lee los datos del archivo y construye el heap
    loadOrderData("orders.txt", restaurantes, capacity);

    //Crea nuevo Heap con los valores de restaurante
    Heap heapOrdenes = Heap(restaurantes.currentSize);
    for (int i = 0; i < restaurantes.currentSize; i++) {
        heapOrdenes.data[i] = restaurantes.data[i];
        heapOrdenes.currentSize++;
    }

    //Abre un nuevo archivo
    ofstream FileOrdenes("restaurantes_top_ordenes.txt");
    //Reacomoda el nuevo heap para convertirlo en un Max-Heap de órdenes
    heapOrdenes.reacomodarPorOrdenes();
    //Hace pop 10 veces, por lo tanto,
    //muestra los 10 restaurantes con la mayor cantidad de órdenes
    cout << "10 restaurantes con la mayor cantidad de ordenes\n";
    FileOrdenes << "10 restaurantes con la mayor cantidad de ordenes\n";
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapOrdenes.popOrden();
        //Despliega la información
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
        //Guarda la información al archivo de texto
        FileOrdenes << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }
    //Cierra el archivo
    FileOrdenes.close();

    cout << "\n";

    //Crea nuevo Heap con los valores de restaurante
    Heap heapIngresos = Heap(restaurantes.currentSize);
    for (int i = 0; i < restaurantes.currentSize; i++) {
        heapIngresos.data[i] = restaurantes.data[i];
        heapIngresos.currentSize++;
    }

    //Abre un nuevo archivo
    ofstream FileIngresos("restaurantes_top_ingresos.txt");
    //Reacomoda el nuevo heap para convertirlo en un Max-Heap de ingresos
    heapIngresos.reacomodarPorIngresos();
    //Hace pop 10 veces, por lo tanto,
    //muestra los 10 restaurantes con la mayor cantidad de ingresos
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapIngresos.popIngreso();
        //Despliega la información
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
        //Guarda la información en el archivo de texto
        FileIngresos << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }
    //Cierra el archivo
    FileIngresos.close();

    return 0;
}