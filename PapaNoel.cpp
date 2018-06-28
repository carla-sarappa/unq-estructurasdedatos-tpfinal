

#include "ColaPedidos.h"
#include "PapaNoel.h"

struct PapaNoelRepr {
    int fechaDeHoy;
    ColaPedidos pedidosFuturos;
    int cantPedidosDeHoy;
    Pedido *pedidosDeHoy;
};

PapaNoel iniciarPN() {
    // COMPLETAR
}

Fecha fechaActualPN(PapaNoel p) {
    // COMPLETAR
}

void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
    // COMPLETAR
}

Estado estadoPedidoPN(PapaNoel p, Id x) {
    // COMPLETAR
}

void entregarPedidoPN(PapaNoel p, Id x) {
    // COMPLETAR
}

void registrarMalComportamientoPN(PapaNoel p, Id x) {
    // COMPLETAR
}

void avanzarDiaPN(PapaNoel p) {
    // COMPLETAR
}

void finalizarPN(PapaNoel p) {
    // COMPLETAR
}

