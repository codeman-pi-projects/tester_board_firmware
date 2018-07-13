/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC18F25K50
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>

//Need to put these to the right values!
#define BOARD_PWR_I2C_ADDR 10
#define BATT_PWR_I2C_ADDR 12

void Flush_EUSART(void);
void LED_Control(void);
void Relay_Control(void);
void Power_Monitoring(uint8_t addr);

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        unsigned char selection = 0;
    
        while(selection != 'x' && selection != 'X')
        {
            printf("\n\nThis is the main menu.  Make a selection: \n");
            printf("1: LED Control\n");
            printf("2: Relay Control\n");
            printf("3: Board Power IC\n");
            printf("4: Battery Power IC\n");

            printf("Selection:  ");

            selection = EUSART1_Read();
            EUSART1_Write(selection);   //echo it back just to show it's working

            switch(selection)
            {
                case '1':
                {
                    LED_Control();
                    break;
                }
                case '2':
                {
                    Relay_Control();
                    break;
                }
                case '3':
                {
                    Power_Monitoring(BOARD_PWR_I2C_ADDR);
                    break;
                }
                case '4':
                {
                    Power_Monitoring(BATT_PWR_I2C_ADDR);
                    break;
                }
                case 'x':
                case 'X':
                {
                    printf("\n\nQuitting Application...");
                    break;
                }

                default:
                {
                    printf("\n\nInvalid selection...");
                    break;
                }
            }


        }   
      
        
    }
}


void Flush_EUSART(void)
{
    while(EUSART1_is_rx_ready())
    {
        EUSART1_Read();
    }
}      


void LED_Control(void)
{
    printf("\n\nIt would be really nice if there was an LED on the board...\n\n");
    printf("Press any key to return");
    
    EUSART1_Read();
    Flush_EUSART();
    
}

void Relay_Control(void)
{
    unsigned char relay_selection = 0;
    
    while(relay_selection != 'x' && relay_selection != 'X')
    {
        printf("\n\nChoose the relay function\n");
        printf("1 = Board Power Relay Off\n");
        printf("2 = Board Power Relay On\n");
        printf("3 = Battery Relay Off\n");
        printf("4 = Battery Relay On\n");
        printf("X = Return to main menu\n");
        printf("\n\nSelection: ");
        
        relay_selection = EUSART1_Read();
        Flush_EUSART();

        switch(relay_selection)
                {
                    case '1':
                    {
                        BRD_PWR_RELAY_SetLow();
                        break;
                    }
                    case '2':
                    {
                        BRD_PWR_RELAY_SetHigh();    
                        break;
                    }
                    case '3':
                    {
                        BAT_PWR_RELAY_SetLow();
                        break;
                    }
                    case '4':
                    {
                        BAT_PWR_RELAY_SetHigh();
                        break;
                    }
                    case 'x':
                    case 'X':
                    {
                        printf("\n\nReturning to main menu...\n");
                        break;
                    }

                    default:
                    {
                        printf("\n\nInvalid selection...");
                        break;
                    }
                }
    }
}
    
    

void Power_Monitoring(uint8_t addr)
{
    unsigned char power_selection = 0;
    unsigned char input[16];
    uint8_t address = 0;
    uint8_t data = 0;
    
    while(power_selection != 'x' && power_selection != 'X')
    {
        printf("\n\nChoose the relay function\n");
        printf("1 = Write\n");
        printf("2 = Read\n");
        printf("X = Return to main menu\n");
        printf("\n\nSelection: ");
        
        power_selection = EUSART1_Read();
        Flush_EUSART();

        switch(power_selection)
                {
                    case '1':
                    {
                        printf("\n\nAddress (hex): ");
                        read_input(input);
                        address = xtoi(input);
                        printf("\nData (hex): ");
                        read_input(input);
                        data = xtoi(input);
                        printf("\n\nWriting 0x%x 0x%x",address, data);                        
                        break;
                    }
                    case '2':
                    {
                            
                        break;
                    }
                    case '3':
                    {
                        
                        break;
                    }
                    case '4':
                    {
                        
                        break;
                    }
                    case 'x':
                    case 'X':
                    {
                        printf("\n\nReturning to main menu...\n");
                        break;
                    }

                    default:
                    {
                        printf("\n\nInvalid selection...");
                        break;
                    }
                }
    }
   
}

void read_input(unsigned char *buf)
{
    //read the input string, end at the enter key
}

/**
 End of File
*/