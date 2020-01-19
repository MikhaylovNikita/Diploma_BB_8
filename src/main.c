#include <ch.h>
#include <hal.h>
#include <chprintf.h>

int main(void)
{
    halInit();
    chSysInit();

    lldControlInit();

    while(true)
    {

    }
}
