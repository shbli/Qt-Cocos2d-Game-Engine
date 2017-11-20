#include "layer.h"

Layer::Layer() {

}

Layer * Layer::node() {
    return new Layer();
}
