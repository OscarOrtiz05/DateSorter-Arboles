#include "Heap.h"
#include <fstream>

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