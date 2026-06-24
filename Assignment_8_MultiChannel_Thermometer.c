#include <reg51.h>

// LCD pinleri
sbit rs = P1^2;
sbit rw = P1^1;
sbit en = P1^0;

// 4051 MUX pinleri
sbit selA = P1^3; // MUX A0
sbit selB = P1^4; // MUX A1

// ADC0804 pinleri
sbit rd_adc = P1^7;
sbit wr_adc = P1^6;
sbit intr_adc = P1^5;

#define LCD_DATA P0

void delay(unsigned int);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);
void display_temp(unsigned char channel, signed char temp);
unsigned char read_adc(void);
unsigned char readTemp(unsigned char channel);
signed char adc_to_temp(unsigned char val);
void sortTemps(signed char temps[], unsigned char chs[], unsigned char n);

void main(void)
{
    unsigned char i;
    unsigned char adc_vals[4];
    signed char temps[4];
    unsigned char chs[4] = {1, 2, 3, 4}; // CH1–CH4

    // LCD baslat
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x06);

    while(1)
    {
        // Okuma
        for(i = 0; i < 4; i++)
        {
            adc_vals[i] = readTemp(i);         // CH0–CH3
            temps[i] = adc_to_temp(adc_vals[i]);
        }

        // Siralama
        sortTemps(temps, chs, 4);

        // Ekrana yazdir (sirali sekilde)
        for(i = 0; i < 4; i++)
        {
            if(i < 2)
                lcd_cmd(0x80 + i * 8);  // 1. satir
            else
                lcd_cmd(0xC0 + (i - 2) * 8); // 2. satir

            display_temp(chs[i], temps[i]);
        }

        delay(100);
        lcd_cmd(0x01); // Temizle
    }
}

// MUX üzerinden ADC degeri okuma
unsigned char readTemp(unsigned char channel)
{
    switch(channel)
    {
        case 0:
            selA = 0; selB = 0;
            break;
        case 1:
            selA = 1; selB = 0;
            break;
        case 2:
            selA = 0; selB = 1;
            break;
        case 3:
            selA = 1; selB = 1;
            break;
    }

    delay(20); // MUX sabitlenmesi için
    return read_adc();
}

// ADC0804'ten okuma
unsigned char read_adc()
{
    unsigned char val;
    wr_adc = 0;
    delay(1);
    wr_adc = 1;
    while(intr_adc == 1); // Bitene kadar bekle
    rd_adc = 0;
    delay(1);
    val = P2;
    rd_adc = 1;
    return val;
}

// ADC degeri sicakliga çevirme
signed char adc_to_temp(unsigned char adc_val)
{
    return (adc_val -50);  // yaklasik deger
}

// LCD'ye sicaklik yazdirma
void display_temp(unsigned char channel, signed char temp)
{
    char buf[5];
    unsigned char i = 0;
    lcd_data('C');
    lcd_data('H');
    lcd_data(channel + '0');  // CH1, CH2...
    lcd_data('=');
    if(temp < 0)
    {
        lcd_data('-');
        temp = -temp;
    }

    if(temp >= 100)
    {
        buf[i++] = (temp / 100) + '0';
        temp %= 100;
    }
    if(temp >= 10 || i > 0)
    {
        buf[i++] = (temp / 10) + '0';
        temp %= 10;
    }

    buf[i++] = temp + '0';
    buf[i] = '\0';

    lcd_str((unsigned char *)buf);
    lcd_data(0xDF); // Derece sembolü
}

// LCD komut gönderme
void lcd_cmd(unsigned char cmd)
{
    LCD_DATA = cmd;
    rs = 0;
    rw = 0;
    en = 1;
    delay(2);
    en = 0;
}

// LCD veri gönderme
void lcd_data(unsigned char dat)
{
    LCD_DATA = dat;
    rs = 1;
    rw = 0;
    en = 1;
    delay(2);
    en = 0;
}

// LCD string gönderme
void lcd_str(unsigned char *s)
{
    while(*s)
    {
        lcd_data(*s++);
    }
}

// Gecikme fonksiyonu
void delay(unsigned int time)
{
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 1275; j++);
}

void sortTemps(signed char temps[], unsigned char chs[], unsigned char n)
{
    unsigned char i, j, temp_ch;
    signed char temp_val;

    for(i = 0; i < n - 1; i++)
    {
        for(j = 0; j < n - i - 1; j++)
        {
            if(temps[j] > temps[j + 1])
            {
                // Sicakliklari yer degistir
                temp_val = temps[j];
                temps[j] = temps[j + 1];
                temps[j + 1] = temp_val;

                // Kanal numaralarini da degistir
                temp_ch = chs[j];
                chs[j] = chs[j + 1];
                chs[j + 1] = temp_ch;
            }
        }
    }
}
