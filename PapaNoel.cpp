

#include "ColaPedidos.h"
#include "PapaNoel.h"
#include <iostream>

using namespace std;


struct PapaNoelRepr {
    int fechaDeHoy;
    ColaPedidos pedidosFuturos;
    int cantPedidosDeHoy;
    Pedido *pedidosDeHoy;
};

PapaNoel iniciarPN() {
    PapaNoel p = new PapaNoelRepr;
    p->pedidosFuturos = nuevaCP();
    p->fechaDeHoy = 0;
    p->cantPedidosDeHoy = 0;
    p->pedidosDeHoy = NULL;

    return p;
}

Fecha fechaActualPN(PapaNoel p) {
    return p->fechaDeHoy;
}

/**
 * Precondicion: la fecha es posterior a la de hoy.
 *
 * Agrega un nuevo pedido a la cola de pedidos futuros.
 */
void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
    Pedido *pedido = new Pedido;
    pedido->persona = x;
    pedido->fechaEntrega = f;
    pedido->estado = Pendiente;
    encolarCP(p->pedidosFuturos, *pedido);
}

/**
 * Realiza busqueda binaria sobre el array de pedidos y retorna un puntero al pedido (o NULL si no se lo encuentra).
 *
 * O(log pedidos)
 *
 * @param pedidos el array de Pedido sobre el que se va a buscar.
 * @param start posicion en donde se empieza a buscar.
 * @param end posicion tope para buscar.
 * @param id el id que se busca
 * @return un puntero al Pedido si se encuentra o NULL si no se encuentra.
 */
Pedido *busquedaBinariaPedido(Pedido *pedidos, int start, int end, Id id) {
    if (start > end) return NULL;

    int medio = start + (end - start) / 2;
    if (id == pedidos[medio].persona) {
        return &pedidos[medio];
    }

    if (pedidos[medio].persona > id) {
        return busquedaBinariaPedido(pedidos, start, medio - 1, id);
    }

    return busquedaBinariaPedido(pedidos, medio + 1, end, id);
}

/**
 * Busca un pedido con Id id en los pedidos del dia de hoy.
 *
 * O(log cantidadDePedidosDeHoy)
 */
Pedido *buscarPedido(PapaNoel p, Id id) {
    return busquedaBinariaPedido(p->pedidosDeHoy, 0, p->cantPedidosDeHoy - 1, id);
}

Estado estadoPedidoPN(PapaNoel p, Id x) {
    Pedido *pedido = buscarPedido(p, x);
    return pedido == NULL ? Inexistente : pedido->estado;
}

void entregarPedidoPN(PapaNoel p, Id x) {
    buscarPedido(p, x)->estado = Entregado;
}

/**
 * Precondicion: existe una persona con Id x y pedido el dia de hoy.
 *
 * O(log cantidadDePedidosDeHoy)
 */
void registrarMalComportamientoPN(PapaNoel p, Id x) {
    buscarPedido(p, x)->estado = MalComportamiento;
}

/**
 * Limpia los datos del array de pedidos de hoy.
 * No es necesario liberar ese array porque se va a reutilizar.
 *
 * O(cantPedidosDeHoy)
 */
void limpiarPedidos(PapaNoel p) {
    Pedido a;
    a.estado = Inexistente;
    a.persona = 0;
    a.fechaEntrega = 0;
    for (int i = 0; i < p->cantPedidosDeHoy; ++i) {
        p->pedidosDeHoy[i] = a;
    }
}

/**
 * Duplica el tamanio del array de pedidos de hoy.
 *
 * @param p papaNoel
 * @param t tamanio hasta el momento, es actualizado con el nuevo.
 */
void duplicarTamanio(PapaNoel p, int &t) {
    Pedido *nuevo = new Pedido[2 * t];
    for (int i = 0; i < t; ++i) {
        nuevo[i] = p->pedidosDeHoy[i];
    }
    delete[] p->pedidosDeHoy;
    p->pedidosDeHoy = nuevo;
    t = 2 * t;
}

/**
 * Popula el array de pedidosDeHoy con los pedidos del dia siguiente.
 *
 * O(log P) donde P es la cantidad total de pedidos en la cola.
 */
void rellenarPedidosParaManiana(PapaNoel p) {
    int i = 0;
    int tamanio = p->cantPedidosDeHoy == 0 ? 100 : p->cantPedidosDeHoy;

    if (p->pedidosDeHoy == NULL) {
        p->pedidosDeHoy = new Pedido[tamanio];
    }

    while (tamCP(p->pedidosFuturos) > 0 && proximoCP(p->pedidosFuturos).fechaEntrega == p->fechaDeHoy + 1) {
        p->pedidosDeHoy[i] = proximoCP(p->pedidosFuturos);
        desencolarCP(p->pedidosFuturos);
        i++;
        if (i >= tamanio) {
            duplicarTamanio(p, tamanio);
        }
    }

    p->cantPedidosDeHoy = i;
}

void avanzarDiaPN(PapaNoel p) {
    limpiarPedidos(p);
    rellenarPedidosParaManiana(p);
    p->fechaDeHoy++;
}

void finalizarPN(PapaNoel p) {
    destruirCP(p->pedidosFuturos);
    delete p->pedidosDeHoy;
}

void printPedidosDeHoy(PapaNoel p) {
    if (tamCP(p->pedidosFuturos) > 0) {
        printCP(p->pedidosFuturos);
    }

    cout << "(cant:" << p->cantPedidosDeHoy << ")" << "[ ";
    for (int i = 0; i < p->cantPedidosDeHoy && p->cantPedidosDeHoy > 0; ++i) {
        cout << "id:" << p->pedidosDeHoy[i].persona << " e:" << p->pedidosDeHoy[i].estado << ", ";
    }
    cout << " ]" << endl;
}

