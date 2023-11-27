#include "uart.h"


// Initialize UART based on configuration structure
void UART_Init(UART_Config config) {
    // Set the baud rate
    SPBRG = (_XTAL_FREQ/(16* config.baud_rate)-1);
}

// Function to configure TXSTA using the structure
void UART_Config_TXSTA(TXSTA_Config config) {
    TXSTAbits.TXEN = config.txEnable; // Set Transmit Enable bit
    TXSTAbits.SYNC = config.syncMode; // Set Sync/Async mode bit
    TXSTAbits.BRGH = config.highSpeed; //Set high speed
    // Configure other TXSTA bits similarly
}

// Function to configure RCSTA using the structure
void UART_Config_RCSTA(RCSTA_Config config) {
    RCSTAbits.SPEN = config.SerialPortEnable; 
    RCSTAbits.CREN = config.continiousReciveEnable; // 
  
 
}
// Function to wait until TXIF flag is set
void UART_WaitForTxComplete() {
    while (!PIR1bits.TXIF) {
        continue; // Wait until TXIF flag is set
    }
}
// Function to transmit a string via UART
void UART_TransmitString(const char* data) {
    while (*data != '\0') {
        // Wait for TXIF flag indicating the transmit buffer is empty
        while (!TXSTAbits.TRMT) {
            continue;
        }
        TXREG = *data;
        data++; 
    }
}