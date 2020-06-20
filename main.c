#include "main.h"

//Hauptprogramm
int main(void)
{
    /*
    // 70cm ZF
    // Reference=25MHz
    // RX 307.000MHz -> 739.550MHz-307.000MHz = 432.550MHz
    uint32_t registers_rx[6] =  {0x310030
                              , 0x80080C9
                              , 0x4E42
                              , 0x4B3
                              , 0xBC803C
                              , 0x580005};
     */
    
    
    // 2m ZF
    // Reference=25MHz
    // RX 595.500MHz -> 739.550MHz-595.500MHz = 144.050MHz
    uint32_t registers_rx[6] =  {0x2F8038
                              , 0x80080C9
                              , 0x4E42
                              , 0x4B3
                              , 0xAC803C
                              , 0x580005};
    
    /*
    // Test
    // 144.530 MHz
    uint32_t registers_rx[6] =  {0x2e09c0
                              , 0x8009389
                              , 0x4E42
                              , 0x4B3
                              , 0xcc803c
                              , 0x580005};
  
     // Test
    // 144.530 MHz
     uint32_t registers_rx[6] =  {0x330010
                               , 0x8008029
                               , 0x4E42
                               , 0x4B3
                               , 0xec803c
                               , 0x580005};

      // Test
     // 3496.52 -> 3. 10489.560 MHz
      uint32_t registers_rx[6] =  {0x4590D0
                                , 0x8009389
                                , 0x4E42
                                , 0x4B3
                                , 0x8c8034
                                , 0x580005};*/
    
    
    //1 Sekunde Pause
    _delay_ms(200);
    _delay_ms(200);
    _delay_ms(200);
    _delay_ms(200);
    _delay_ms(200);
    
    //Port initialisieren
    //ADF_DDR |= (1<<ADF_CE) | (1<<ADF_LE) | (1<<ADF_DATA) | (1<<ADF_CLK); //Alle Pins Ausgang
    //ADF_PORT = (1<<ADF_CE); //Alle Pins LOW, CE High
    //Neues Layout benötigt kein CE - daher nur LE, Data und CLK
    ADF_DDR |= ((1<<ADF_LE) | (1<<ADF_DATA) | (1<<ADF_CLK)); //Alle Pins Ausgang
    
    //Alle 5 Register je 32 Bit senden
    for (int i = 5; i >= 0; i--)
        writePLL(registers_rx[i]);
    
    while(1)
    {
        //Kurze Pause
        _delay_ms(200);
        //mC in den Sleep Modus, um QRM zu vermeiden
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_mode();
    }
    return 0;
}

void writePLL(uint32_t pll_word) {
  
  for (uint8_t count=0; count<32; count++)
  {
 
    if (pll_word & 0x80000000)
        ADF_PORT |= (1<<ADF_DATA);      //Bit 1 -> Data High
      else
        ADF_PORT &= ~(1<<ADF_DATA);     //Bit 0 -> Data Low
                                                                             
    ADF_PORT |= (1<<ADF_CLK);           //Clock High
    nop();                              //Pause
    ADF_PORT &= ~(1<<ADF_CLK);          //Clock Low
            
    pll_word <<= 1;                     //Rotate left for next bit
  }

    ADF_PORT |= (1<<ADF_LE);            //LE High
    nop();                              //Pause
    ADF_PORT &= ~(1<<ADF_LE);           //LE low

    ADF_PORT &= ~(1<<ADF_DATA);         //Clear Data
}


