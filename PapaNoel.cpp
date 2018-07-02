

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
    p->pedidosDeHoy = NULL;

    return p;
}

Fecha fechaActualPN(PapaNoel p) {
    return p->fechaDeHoy;
}

void registrarPedidoPN(PapaNoel p, Fecha f, Id x) {
    Pedido *pedido = new Pedido;
    pedido->persona = x;
    pedido->fechaEntrega = f;
    pedido->estado = Pendiente;
    encolarCP(p->pedidosFuturos, *pedido);
}

Estado estadoPedidoPN(PapaNoel p, Id x) {

}

void entregarPedidoPN(PapaNoel p, Id x) {
    // COMPLETAR
}

void registrarMalComportamientoPN(PapaNoel p, Id x) {
    // COMPLETAR
}

void limpiarPedidos(PapaNoel p) {
//    for (int i = 0; i < p->cantPedidosDeHoy; ++i) {
//        p->pedidosDeHoy[i] = NULL;
//    }
    delete[] p->pedidosDeHoy;
}

void duplicarTamanio(PapaNoel p, int &t) {
    Pedido *nuevo = new Pedido[2 * t];
    for (int i = 0; i < t; ++i) {
        nuevo[i] = p->pedidosDeHoy[i];
    }
    delete[] p->pedidosDeHoy;
    p->pedidosDeHoy = nuevo;
    t = 2 * t;
}

void rellenarPedidosParaManiana(PapaNoel p) {
    int i;
    int tamanio = 100;

    if (p->pedidosDeHoy == NULL) {
        p->pedidosDeHoy = new Pedido[tamanio];
    }

    while (proximoCP(p->pedidosFuturos).fechaEntrega == p->fechaDeHoy + 1) {
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
}

void finalizarPN(PapaNoel p) {
    // COMPLETAR
}

