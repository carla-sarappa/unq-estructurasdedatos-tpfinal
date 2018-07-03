#ifndef PAPA_NOEL_H
#define PAPA_NOEL_H

#include "Tipos.h"

struct PapaNoelRepr;
typedef PapaNoelRepr *PapaNoel;

/**
 * Propósito: Devuelve un sistema nuevo.
 * Complejidad: O(1)
 * @return PapaNoel nuevo
 */
PapaNoel iniciarPN();

/**
 * Propósito: Devuelve la fecha actual (la “fecha de hoy”) del sistema.
 * Complejidad: O(1)
 * @param p
 * @return Fecha fechaDeHoy
 */
Fecha fechaActualPN(PapaNoel p);

/**
 * Propósito: Registra la solicitud de entregarle un regalo a la persona x cuando llegue la fecha f indicada.
 * (Agrega un nuevo pedido a la cola de pedidos futuros).
 * Precondicion: La fecha debe ser posterior a la fecha de hoy, es decir, f > fechaActualPN(p).
 * Además, la persona x no puede pedir más de un regalo para la misma fecha.
 * Complejidad: O(log P), donde P es la cantidad total de pedidos cargados en el sistema.
 */
void registrarPedidoPN(PapaNoel p, Fecha f, Id x);

/**
 * Propósito: Devuelve el estado del pedido de la persona x en la fecha de hoy.
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 * @param PapaNoel p
 * @param Id x
 */
Estado estadoPedidoPN(PapaNoel p, Id x);

/**
 * Propósito: Entrega un regalo a la persona x, con motivo de su buen comportamiento, cambiando su estado a Entregado.
 * Precondición: La persona tiene que tener un regalo pendiente para la fecha de hoy, es decir se debe cumplir
 * que estadoPedidoPN(p, x) == Pendiente
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 * @param PapaNoel p
 * @param Id x
 */
void entregarPedidoPN(PapaNoel p, Id x);

/**
 * Propósito: Registra el mal comportamiento de la persona x, cambiando su estado a MalComportamiento.
 * Precondición: La persona tiene que tener un regalo pendiente para la fecha de hoy, es decir se debe cumplir
 * que estadoPedidoPN(p, x) == Pendiente.
 * Complejidad: O(log H), donde H es la cantidad total de pedidos para la fecha de hoy.
 */
void registrarMalComportamientoPN(PapaNoel p, Id x);

/**
 * Propósito: Finaliza el día actual, incrementando la fecha de hoy en 1.
 * Precondición: No debe haber ninguna persona en estado Pendiente.
 * Complejidad: O(H + M · log P), donde P es la cantidad total de pedidos cargados en el sistema,
 * H es la cantidad de pedidos para la fecha de hoy (antes de avanzar el día) y
 * M es la cantidad de pedidos registrados para la fecha de mañana
 * @param p
 */
void avanzarDiaPN(PapaNoel p);

/**
 * Propósito: Libera toda la memoria reservada para el sistema (sin restricciones de complejidad).
 * @param p
 */
void finalizarPN(PapaNoel p);

#endif
