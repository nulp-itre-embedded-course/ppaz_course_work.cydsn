#include "project.h"
#include "stdio.h"
#include "tty_utils.h"

#define TAB   '\t'
#define SPACE ' ' 
#define CR    '\r'
#define LF    '\n'

#define RX_BUF_LEN  128
#define STR_BUF_LEN  64

volatile char rx_buf[RX_BUF_LEN] ;
volatile int  rx_write_index = 0 ;
int           rx_read_index  = 0 ;
int           str_buf_index  = 0 ;
char          str[STR_BUF_LEN + 1] ;

static inline int is_delimiter(char c)
{
    return((c == TAB)||(c == SPACE)||(c == CR)||(c == LF)) ;
}

static inline int is_eol(char c)
{
    return((c == CR) || (c == LF)) ;
}

void print(char *str)
{
    UART_PutString(str) ; /* for PSoC 4 */
}

CY_ISR(tty_rx_isr)
{
    if (UART_GetRxBufferSize()) {
        rx_buf[rx_write_index] = UART_GetByte() ;
        rx_write_index = (rx_write_index + 1) % RX_BUF_LEN ;
    }
    tty_rx_int_ClearPending() ;
}

void splash(char *prog_name) 
{
    if (prog_name && *prog_name) {
        print(prog_name) ;
    } 
    print(" (") ;
    print(__DATE__) ;
    print(" ") ;
    print(__TIME__) ;
    print(")\n") ;
}

void prompt(void)
{
    print("> ") ;
}

void tty_init(void)
{
    tty_rx_int_ClearPending() ;
    tty_rx_int_StartEx(tty_rx_isr) ;
    UART_Start() ;
}

int get_string(void)
{
    int result = 0 ;
    
    if (rx_read_index != rx_write_index) {
        if (is_delimiter(rx_buf[rx_read_index])) {
            str[str_buf_index] = (char)NULL ;
            result = str_buf_index ;
            str_buf_index = 0 ;
        } else {
            str[str_buf_index++] = rx_buf[rx_read_index] ;
            if (str_buf_index >= STR_BUF_LEN) {
                str[STR_BUF_LEN] = (char)NULL ;
                str_buf_index = 0 ;
                result = -1 ; /* str buf overflow */
            }
        }
        rx_read_index = (rx_read_index + 1) % RX_BUF_LEN ;
    }
    return( result ) ;
}

int get_line(void)
{
    int result = 0 ;
    
    if (rx_read_index != rx_write_index) {
        if (is_eol(rx_buf[rx_read_index])) {
            str[str_buf_index] = (char)NULL ;
            result = str_buf_index ;
            str_buf_index = 0 ;
        } else {
            str[str_buf_index++] = rx_buf[rx_read_index] ;
            if (str_buf_index >= STR_BUF_LEN) {
                str[STR_BUF_LEN] = (char)NULL ;
                str_buf_index = 0 ;
                result = -1 ; /* str buf overflow */
            }
        }
        rx_read_index = (rx_read_index + 1) % RX_BUF_LEN ;
    }
    return( result ) ;
}


