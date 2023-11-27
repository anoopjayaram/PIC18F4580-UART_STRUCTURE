/*
 * File:   uartStructMain.c
 * Author: anoop
 *
 * Created on 24 November, 2023, 3:06 PM
 */

#include "uart.h"

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
void main() {
     TRISC=0X00;
    TXSTA_Config txConfig; 
    txConfig.txEnable = 1; // Enable transmit
    txConfig.syncMode = 0; // Async mode
    txConfig.highSpeed = 1;
    
    RCSTA_Config rxConfig; 
    rxConfig.SerialPortEnable = 1; // Enable transmit
    rxConfig.continiousReciveEnable = 1; // Async mode


    UART_Config_TXSTA(txConfig);
    UART_Config_RCSTA(rxConfig);
    
    
    UART_Config uartConfig;
    uartConfig.baud_rate = 9600UL; // Set baud rate to 9600
    uartConfig.data_bits = 8; // Set data bits to 8
    uartConfig.stop_bits = 1; // Set stop bits to 1

    // Initialize UART with the configured parameters
    UART_Init(uartConfig);
   
    // Your main code here
    while (1) {
        // Wait for TXIF flag before transmitting data
        UART_WaitForTxComplete();

        // Transmit data
        
        UART_TransmitString("Hello World\r\n ");

        __delay_ms(1000); // Delay for 1 second
    }
}
