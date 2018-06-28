
#include "ColaPedidos.h"

struct Nodo {
    int tam;
    Pedido pedido;
    Nodo *izq;
    Nodo *der;
};

struct ColaPedidosRepr {
    Nodo *raiz;
};

ColaPedidos nuevaCP() {
    // COMPLETAR
}

int tamCP(ColaPedidos cp) {
    // COMPLETAR
}

void encolarCP(ColaPedidos cp, Pedido p) {
    // COMPLETAR
}

Pedido proximoCP(ColaPedidos cp) {
    // COMPLETAR
}

void desencolarCP(ColaPedidos cp) {
    // COMPLETAR
}

void destruirCP(ColaPedidos cp) {
    // COMPLETAR
}

