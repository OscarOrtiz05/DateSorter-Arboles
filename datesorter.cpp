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

    ofstream FileOrdenes("restaurantes_top_ordenes.txt");
    heapOrdenes.reacomodarPorOrdenes();
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapOrdenes.popOrden();
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
        FileOrdenes << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }
    FileOrdenes.close();

    cout << "\n";

    //Crea nuevo Heap con los valores de restaurante
    Heap heapIngresos = Heap(restaurantes.currentSize);
    for (int i = 0; i < restaurantes.currentSize; i++) {
        heapIngresos.data[i] = restaurantes.data[i];
        heapIngresos.currentSize++;
    }

    ofstream FileIngresos("restaurantes_top_ingresos.txt");
    heapIngresos.reacomodarPorIngresos();
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapIngresos.popIngreso();
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
        FileIngresos << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }
    FileIngresos.close();

    return 0;
}