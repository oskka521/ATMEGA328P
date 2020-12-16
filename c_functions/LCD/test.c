#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_bin(unsigned char temp);
void LCD_Char(unsigned char data);

int main(void){
    int x = 0x26;
    printf("nBinary is %d \n",x);

    //bitmasks
    /*
    unsigned char our_char1 = 'H';  
    unsigned char our_char2 = 'A'; 
    unsigned char our_char3 = 'o';
    print_bin('H');
    print_bin('e');
    print_bin('l');
    print_bin(0x7c);
    print_bin(0x20);
    */
    LCD_Char('H');
    LCD_Char('e');
    LCD_Char('l');
    LCD_Char('l');
    LCD_Char('o');
    LCD_Char('1');


    return 0;
}

void upload_data_lcd(unsigned char data, int upper){

    if (upper){
        unsigned char filtered_data = (data & 0xF0);
        print_bin(data);
        //print_bin(filtered_data);
        if (filtered_data & 0b00010000){
            printf("good1\n");
        }
        if (filtered_data & 0b00100000){
            printf("good2\n");
        }
        if (filtered_data & 0b01000000){
            printf("good3\n");
        }
        if (filtered_data & 0b10000000){
            printf("good4\n");
        }
    }
    else{
        unsigned char filtered_data = (data & 0x0F);
        print_bin(data);
        //print_bin(filtered_data);
        if (filtered_data & 0b00000001){
            printf("good1_low\n");
        }
        if (filtered_data & 0b00000010){
            printf("good2_low\n");
        }
        if (filtered_data & 0b00000100){
            printf("good3_low\n");
        }
        if (filtered_data & 0b00001000){
            printf("good4_low\n");
        }
    } 
}

void LCD_Char(unsigned char data)
{
    int upper = 1;
    upload_data_lcd(data, upper);
    upper = 0;
    upload_data_lcd(data, upper);
}

void print_bin(unsigned char temp){
    char buffer[10];
    itoa(temp,buffer,2);
    printf("%c = %08s \n",temp,buffer);
    //printf("%X = %08s \n",temp,buffer);
}
