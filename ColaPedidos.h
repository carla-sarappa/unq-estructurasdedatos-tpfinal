#ifndef COLA_PEDIDOS_H
#define COLA_PEDIDOS_H

#include "Tipos.h"


struct ColaPedidosRepr;
typedef ColaPedidosRepr *ColaPedidos;

/**
 * Propósito: Crea una nueva cola.
 * Complejidad: O(1)
 * @return ColaPedidos nueva
 */
ColaPedidos nuevaCP();

/**
 * Propósito: Devuelve la cantidad de pedidos en la cola.
 * Complejidad: O(1)
 * @param ColaPedidos cp
 */
int tamCP(ColaPedidos cp);

/**
 * Propósito: Encola un pedido.
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param ColaPedidos cp
 * @param Pedido p
 */
void encolarCP(ColaPedidos cp, Pedido p);

/**
 * Propósito: Devuelve el pedido de la cola que tiene mayor prioridad. Nota: No modifica la cola de prioridad.
 * Precondición: La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * Complejidad: O(1).
 * @param ColaPedidos cp
 */
Pedido proximoCP(ColaPedidos cp);

/**
 * Propósito: Desencola el pedido de mayor prioridad.
 * Precondición: La cola no puede estar vacía (es decir, tamCP(cp) > 0).
 * Complejidad: O(log n), donde n es la cantidad de pedidos en la cola.
 * @param ColaPedidos cp
 */
void desencolarCP(ColaPedidos cp);

/**
 * Propósito: Libera toda la memoria reservada para la cola de prioridad (sin restricciones de complejidad).
 * @param ColaPedidos cp
 */
void destruirCP(ColaPedidos cp);


#endif
