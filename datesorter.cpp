#include "Heap.h"
#include <fstream>

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

            if (int index = out.search(r); index != -1) {
                out.data[index].totalOrdenes++;
                out.data[index].totalIngreso += stoi(n);
            }else {
                out.push(r);
            }

            i++;
        }
    }

    inFile2.close();

}

int main() {
    int capacity = 10000;
    Heap restaurantes = Heap(capacity);

    loadOrderData("orders.txt", restaurantes, capacity);

    //Crea nuevo Heap con los valores de restaurante
    Heap heapOrdenes = Heap(restaurantes.currentSize);
    for (int i = 0; i < restaurantes.currentSize; i++) {
        heapOrdenes.data[i] = restaurantes.data[i];
        heapOrdenes.currentSize++;
    }

    heapOrdenes.reacomodarPorOrdenes();
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapOrdenes.popOrden();
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }
    cout << "\n";

    //Crea nuevo Heap con los valores de restaurante
    Heap heapIngresos = Heap(restaurantes.currentSize);
    for (int i = 0; i < restaurantes.currentSize; i++) {
        heapIngresos.data[i] = restaurantes.data[i];
        heapIngresos.currentSize++;
    }

    heapIngresos.reacomodarPorIngresos();
    for (int i = 0; i < 10; i++) {
        Restaurante aux = heapIngresos.popIngreso();
        cout << aux.nombre << " (Ordenes: " << aux.totalOrdenes << ", Ingresos: " << aux.totalIngreso <<")\n";
    }


    return 0;
}