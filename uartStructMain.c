/*
 * File:   uartStructMain.c
 * Author: anoop
 *
 * Created on 24 November, 2023, 3:06 PM
 */

// Configuration settings
#define _XTAL_FREQ 20000000UL // Define your oscillator frequency
#include <pic18.h>
#include <xc.h>

// Define the UART configuration structure (as previously defined)
typedef struct {
    unsigned int baud_rate;
    unsigned char data_bits;
    unsigned char stop_bits;
  
} UART_Config;



// Initialize UART based on configuration structure
void UART_Init(UART_Config config) {
    // Set the baud rate
    SPBRG = (_XTAL_FREQ/(16UL * config.baud_rate)-1);
}
    
typedef struct {
    unsigned int txEnable : 1; // Bit 0: Transmit Enable
    unsigned int syncMode : 1; // Bit 4: Sync/Async mode
    unsigned int highSpeed : 1;
} TXSTA_Config;

// Function to configure TXSTA using the structure
void UART_Config_TXSTA(TXSTA_Config config) {
    TXSTAbits.TXEN = config.txEnable; // Set Transmit Enable bit
    TXSTAbits.SYNC = config.syncMode; // Set Sync/Async mode bit
    TXSTAbits.BRGH = config.highSpeed; //Set high speed
    // Configure other TXSTA bits similarly
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
void main() {
     TRISC=0X00;
    TXSTA_Config txConfig; 
    txConfig.txEnable = 1; // Enable transmit
    txConfig.syncMode = 0; // Async mode
    txConfig.highSpeed = 1;


    UART_Config_TXSTA(txConfig);
    RCSTA=0X90;
    UART_Config uartConfig;
    uartConfig.baud_rate = 9600; // Set baud rate to 9600
    uartConfig.data_bits = 8; // Set data bits to 8
    uartConfig.stop_bits = 1; // Set stop bits to 1

    // Initialize UART with the configured parameters
    UART_Init(uartConfig);

    // Your main code here
    while (1) {
        // Wait for TXIF flag before transmitting data
        UART_WaitForTxComplete();

        // Transmit data
        TXREG = 'W'; // Transmit character 'A'
        UART_TransmitString("Hi all");

        // Your additional logic here
        __delay_ms(1000); // Delay for 1 second
    }
}
