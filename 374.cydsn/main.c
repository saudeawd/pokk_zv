#include "project.h"
#include <stdbool.h>

#define T_US 10

#define SET_D(v) do { \
    D0_Write((v >> 0) & 1); \
    D1_Write((v >> 1) & 1); \
    D2_Write((v >> 2) & 1); \
    D3_Write((v >> 3) & 1); \
    D4_Write((v >> 4) & 1); \
    D5_Write((v >> 5) & 1); \
    D6_Write((v >> 6) & 1); \
    D7_Write((v >> 7) & 1); \
} while (0)

#define READ_Q() ( \
    (Q0_Read() << 0) | \
    (Q1_Read() << 1) | \
    (Q2_Read() << 2) | \
    (Q3_Read() << 3) | \
    (Q4_Read() << 4) | \
    (Q5_Read() << 5) | \
    (Q6_Read() << 6) | \
    (Q7_Read() << 7) )

void clock_rising_edge(void)
{
    CK_Write(0);
    CyDelayUs(T_US);
    CK_Write(1);
    CyDelayUs(T_US);
    CK_Write(0);
    CyDelayUs(T_US);
}

bool test_74374(void)
{
    for (uint16_t v = 0; v < 256; v++)
    {
        SET_D(v);
        CyDelayUs(T_US);

        clock_rising_edge();
        
        if (READ_Q() != v)
            return false;

        for (uint8_t i = 0; i < 20; i++)
        {
            SET_D((i * 73) & 0xFF);
            CyDelayUs(T_US);

            if (READ_Q() != v)
                return false;
        }
    }

    for (uint8_t b = 0; b < 8; b++)
    {
        uint8_t m = 1 << b;
        SET_D(m);
        CyDelayUs(T_US);
        clock_rising_edge();

        if (READ_Q() != m)
            return false;
    }

    return true;
}

int main(void)
{
    CyGlobalIntEnable;

    OE_Write(0);
    CK_Write(0);
    SET_D(0);

    LED_OK_Write(0);
    LED_FAIL_Write(0);

    CyDelay(100);

    if (test_74374())
    {
        LED_OK_Write(1);
        LED_FAIL_Write(0);
    }
    else
    {
        LED_OK_Write(0);
        LED_FAIL_Write(1);
    }

    for (;;)
        CyDelay(1000);
}
