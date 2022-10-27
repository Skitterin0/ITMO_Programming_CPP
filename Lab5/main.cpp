#pragma once
#include "allocator.h"

int main() {

    allocator one(100000);
    one.init();
    one.allocate(100);
    one.allocate(25);
    one.allocate(200);

    one.free(25);



    return 0;
}
