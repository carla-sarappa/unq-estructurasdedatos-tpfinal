
#include "ColaPedidos.h"
#include <iostream>

using namespace std;


struct Nodo {
    int tam;
    Pedido pedido;
    Nodo *izq;
    Nodo *der;
};

struct ColaPedidosRepr {
    Nodo *raiz;
};

/**
 * Propósito: Crea una nueva cola.
 * Complejidad: O(1)
 * @return ColaPedidos nueva
 */
ColaPedidos nuevaCP() {
    ColaPedidos c = new ColaPedidosRepr;
    c->raiz = NULL;

    return c;
}

/**
 * Propósito: Devuelve la cantidad de pedidos en la cola.
 * Complejidad: O(1)
 * @param ColaPedidos cp
 */
int tamCP(ColaPedidos cp) {
    return cp->raiz == NULL ? 0 : cp->raiz->tam;
}

/**
 * Propósito: Crea un nuevo pedido
 * Complejidad: O(1)
 * @param Pedido pedido
 */
Nodo *nuevoNodo(Pedido pedido) {
    Nodo *n = new Nodo;
    n->pedido = pedido;
    n->izq = NULL;
    n->der = NULL;
}

// Devuelve true si p1 tiene mayor prioridad que p2.
bool masPrioritario(Pedido p1, Pedido p2) {
    return p1.fechaEntrega < p2.fechaEntrega ||
           (p1.fechaEntrega == p2.fechaEntrega && p1.persona < p2.persona);
}

/**
 * Propósito: Inserta en un árbol de Braun
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param Nodo *nodo
 * @param Pedido pedido
 */
Nodo *insertarEnBraunHeap(Nodo *nodo, Pedido pedido) {
    if (nodo == NULL) {
        //Si el árbol A está vacío, el árbol pasa a tener un único nodo con el elemento x en la raíz.
        Nodo *nuevo = nuevoNodo(pedido);
        nuevo->tam = 1;
        return nuevo;

    } else {
        // Si el árbol A no está vacío, tiene tamaño n, una raíz y, un hijo izquierdo I y un hijo derecho D.

        if (masPrioritario(pedido, nodo->pedido)) {
            // 1. Si el elemento que se desea insertar (x) tiene más prioridad que la raíz del árbol (y), intercambiar
            // los valores de x e y.
            Pedido tmp = pedido;
            pedido = nodo->pedido;
            nodo->pedido = tmp;
        }

        // 2. Insertar recursivamente x en el árbol derecho D.
        nodo->der = insertarEnBraunHeap(nodo->der, pedido);

        // 3. Si el tamaño original del árbol (n) era impar, intercambiar el hijo izquierdo I con el hijo derecho D.
        if (nodo->tam % 2 == 1) {
            Nodo *tmp = nodo->izq;
            nodo->izq = nodo->der;
            nodo->der = tmp;
        }

        // 4. Incrementar el campo tam
        nodo->tam++;
        return nodo;
    }
}

/**
 * Propósito: Encola un pedido.
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param ColaPedidos cp
 * @param Pedido p
 */
void encolarCP(ColaPedidos cp, Pedido p) {
    cp->raiz = insertarEnBraunHeap(cp->raiz, p);
}

/**
 * Propósito: Devuelve el pedido de la cola que tiene mayor prioridad. Nota: No modifica la cola de prioridad.
 * Precondición: La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * Complejidad: O(1).
 * @param ColaPedidos cp
 */
Pedido proximoCP(ColaPedidos cp) {
    return cp->raiz->pedido;
}

/**
 * Propósito: Elimina el elemento más prioritario del Braun heap
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param Nodo *n
 * @param Pedido &p
 */
Nodo *eliminarDeBraunHeap(Nodo *n, Pedido &p) {
    if (n->tam == 1) {
        // 1. Si el árbol tiene exactamente un nodo, eliminar ese nodo. El árbol queda vacío.
        p = n->pedido;
        delete n;
        return NULL;

    } else {
        // 2. Si el árbol tiene al menos dos nodos, eliminar recursivamente un nodo del hijo izquierdo I.
        n->izq = eliminarDeBraunHeap(n->izq, p);

        // 3. Si el tamaño original del árbol (n) era impar, intercambiar el hijo izquierdo con el derecho.
        if (n->tam % 2 == 1) {
            Nodo *tmp = n->izq;
            n->izq = n->der;
            n->der = tmp;
        }

        // 4. Decrementar el campo tam.
        n->tam--;
    }
}

/**
 * Propósito: Devuelve true si el nodo tiene un hijo con más prioridad que él, false en caso contrario.
 * Complejidad: O(1).
 * @param Nodo *nodo
 * @return bool
 */
bool tieneHijoMayor(Nodo *nodo) {
    return (nodo->izq != NULL && masPrioritario(nodo->izq->pedido, nodo->pedido))
           || (nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->pedido));
}

/**
 * Propósito: Dado un nodo retorna un puntero a su hijo más prioritario
 * Complejidad: O(1).
 * @param Nodo *nodo
 * @return Nodo*
 */
Nodo *hijoMayor(Nodo *nodo) {
    if (nodo->der != NULL && masPrioritario(nodo->der->pedido, nodo->izq->pedido)) {
        return nodo->der;
    } else {
        return nodo->izq;
    }
}

/**
 * Propósito: Mueve el nodo hacia abajo en el arbol hasta ubicarlo en una posición acorde a su prioridad
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param nodo
 */
void bajar(Nodo *nodo) {
    Nodo *p = nodo;
    while (tieneHijoMayor(p)) {
        Nodo *mayor = hijoMayor(p);
        Pedido tmp = mayor->pedido;
        mayor->pedido = p->pedido;
        p->pedido = tmp;
        p = mayor;
    }
}

/**
 * Propósito: Desencola el pedido de mayor prioridad.
 * Precondición: La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param ColaPedidos cp
 */
void desencolarCP(ColaPedidos cp) {
    Pedido tmp;
    cp->raiz = eliminarDeBraunHeap(cp->raiz, tmp);

    // Supongamos que el nodo que se eliminó tiene valor x y que la raíz del árbol tiene valor y.
    // El algoritmo procede del siguiente modo:
    // 5. Sobreescribir el valor y de la raíz con el valor x que tenía el nodo que se acaba de eliminar.
    if (cp->raiz != NULL) {
        cp->raiz->pedido = tmp;

        //  6. Aplicar el procedimiento de “bajar la raíz” como es usual en un heap, es decir: mientras la raíz tenga
        //  menor prioridad que alguno de sus hijos:
        //  Intercambiar la raíz con su hijo más prioritario.
        //  Continuar aplicando el mismo procedimiento en dicho hijo
        bajar(cp->raiz);
    }
}

void destruirNodo(Nodo *nodo) {
    if (nodo != NULL) {
        destruirNodo(nodo->izq);
        destruirNodo(nodo->der);
        delete (nodo);
    }
}

/**
 * Propósito: Libera toda la memoria reservada para la cola de prioridad (sin restricciones de eficiencia).
 * Complejidad: O(P), donde P es la cantidad total de pedidos cargados en la cola.
 * @param ColaPedidos cp
 */
void destruirCP(ColaPedidos cp) {
    destruirNodo(cp->raiz);
}

