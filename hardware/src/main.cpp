#include "wrap-hwlib.hpp"

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    namespace target = hwlib::target;

    auto serv_1 = target::pin_out(target::pins::d2);
    auto serv_2 = target::pin_out(target::pins::d3);
    auto serv_3 = target::pin_out(target::pins::d4);

    for (;;) {
        serv_1.set(0);
        serv_2.set(0);
        serv_3.set(0);
        hwlib::wait_us(1600);
        serv_1.set(1);
        serv_2.set(1);
        serv_3.set(1);
        hwlib::wait_us(1600);
    }

    return 0; // test
}
