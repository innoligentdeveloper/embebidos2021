//=====[Libraries]=============================================================

#include "main_core.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    systemInit();
    while (true) {
        systemUpdate();
    }
}