

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

/**
 * Propósito: Devuelve un sistema nuevo.
 * Complejidad: O(1)
 * @return PapaNoel nuevo
 */
PapaNoel iniciarPN() {
    PapaNoel p = new PapaNoelRepr;
    p->pedidosFuturos = nuevaCP();
    p->fechaDeHoy = 0;
    p->cantPedidosDeHoy = 0;
    p->pedidosDeHoy = NULL;

    return p;
}

/**
 * Propósito: Devuelve la fecha actual (la “fecha de hoy”) del sistema.
 * Complejidad: O(1)
 * @param p
 * @return Fecha fechaDeHoy
 */
Fecha fechaActualPN(PapaNoel p) {
    return p->fechaDeHoy;
}

/**
 * Propósito: Registra la solicitud de entregarle un regalo a la persona x cuando llegue la fecha f indicada.
 * (Agrega un nuevo pedido a la cola de pedidos futuros).
 * Precondicion: La fecha debe ser posterior a la fecha de hoy, es decir, f > fechaActualPN(p).
 * Además, la persona x no puede pedir más de un regalo para la misma fecha.
 * Complejidad: O(log P), donde P es la cantidad total de pedidos cargados en el sistema.
 */
void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
    Pedido *pedido = new Pedido;
    pedido->persona = x;
    pedido->fechaEntrega = f;
    pedido->estado = Pendiente;

    encolarCP(p->pedidosFuturos, *pedido);
}

/**
 * Propósito: Realiza busqueda binaria sobre el array de pedidos y retorna un puntero al pedido (o NULL si no se lo encuentra).
 * Complejidad: O(log P), donde P es la cantidad de pedidos.
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
 * Propósito: Busca un pedido con Id id en los pedidos del dia de hoy.
 * Complejidad: O(log cantidadDePedidosDeHoy)
 */
Pedido *buscarPedido(PapaNoel p, Id id) {
    return busquedaBinariaPedido(p->pedidosDeHoy, 0, p->cantPedidosDeHoy - 1, id);
}

/**
 * Propósito: Devuelve el estado del pedido de la persona x en la fecha de hoy.
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 * @param PapaNoel p
 * @param Id x
 */
Estado estadoPedidoPN(PapaNoel p, Id x) {
    Pedido *pedido = buscarPedido(p, x);
    return pedido == NULL ? Inexistente : pedido->estado;
}

/**
 * Propósito: Entrega un regalo a la persona x, con motivo de su buen comportamiento, cambiando su estado a Entregado.
 * Precondición: La persona tiene que tener un regalo pendiente para la fecha de hoy, es decir se debe cumplir
 * que estadoPedidoPN(p, x) == Pendiente
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 * @param PapaNoel p
 * @param Id x
 */
void entregarPedidoPN(PapaNoel p, Id x) {
    buscarPedido(p, x)->estado = Entregado;
}

/**
 * Propósito: Registra el mal comportamiento de la persona x, cambiando su estado a MalComportamiento.
 * Precondición: La persona tiene que tener un regalo pendiente para la fecha de hoy, es decir se debe cumplir
 * que estadoPedidoPN(p, x) == Pendiente.
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 */
void registrarMalComportamientoPN(PapaNoel p, Id x) {
    buscarPedido(p, x)->estado = MalComportamiento;
}

/**
 * Propósito: Limpia los datos del array de pedidos de hoy.
 * No es necesario liberar ese array porque se va a reutilizar.
 * Complejidad: O(H), donde H es la cantidad total de pedidos para la fecha de hoy.
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
 * Propósito: Duplica el tamanio del array de pedidos de hoy.
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
 * Propósito: Popula el array de pedidosDeHoy con los pedidos del dia siguiente.
 * Complejidad: O(log P) donde P es la cantidad total de pedidos en la cola.
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

/**
 * Propósito: Finaliza el día actual, incrementando la fecha de hoy en 1.
 * Precondición: No debe haber ninguna persona en estado Pendiente.
 * Complejidad: O(H + M · log P), donde P es la cantidad total de pedidos cargados en el sistema,
 * H es la cantidad de pedidos para la fecha de hoy (antes de avanzar el día) y
 * M es la cantidad de pedidos registrados para la fecha de mañana
 * @param p
 */
void avanzarDiaPN(PapaNoel p) {
    limpiarPedidos(p);
    rellenarPedidosParaManiana(p);
    p->fechaDeHoy++;
}

/**
 * Propósito: Libera toda la memoria reservada para el sistema (sin restricciones de complejidad).
 * Complejidad: O(P), donde P es la cantidad total de pedidos cargados en el sistema.
 * @param p
 */
void finalizarPN(PapaNoel p) {
    destruirCP(p->pedidosFuturos);
    delete p->pedidosDeHoy;
}



