#include <Arduino.h>

class Max7219 {
  public:
    int pinCLK;
    int pinCS;
    int pinDIN;
 
    void write_byte(unsigned char data) 
    {  
      unsigned char i;
      digitalWrite(pinCS, LOW);
      for(i=8; i>=1; i--)
      {
        digitalWrite(pinCLK, LOW);
        digitalWrite(pinDIN, data&0x80);// Extracting a bit data
        data = data<<1;
        digitalWrite(pinCLK, HIGH);
      }
    }

    void Write(unsigned char address,unsigned char dat)
    {
      digitalWrite(pinCS, LOW);
      write_byte(address);           //address，code of LED
      write_byte(dat);               //data，figure on LED 
      digitalWrite(pinCS,HIGH);
    }

    Max7219(int clk, int cs, int din) {
      pinCLK = clk;
      pinCS = cs;
      pinDIN = din;
    }
    
    void setup() {
      pinMode(pinCLK,OUTPUT);
      pinMode(pinCS,OUTPUT);
      pinMode(pinDIN,OUTPUT);
      delay(50);
      Write(0x09, 0x00);       //decoding ：BCD
      Write(0x0a, 0x01);       //brightness 
      Write(0x0b, 0x07);       //scanlimit；8 LEDs
      Write(0x0c, 0x01);       //power-down mode：0，normal mode：1
      Write(0x0f, 0x00);       //test display：1；EOT，display：0
    }
};

class DisplayFace {
  public:
    Max7219 display_hw;

  /** 
2 bars + face?
*/
  void with_bars(unsigned char bits[], char left, char right) {
    //Draw a bit display with left and right bars
    /* 
    none lit = 0
    all lit > 8
    */
    for (int i=0; i<8; i++) {
      char bitset = bits[i];
      if(i < left) {
        bitset |= 0x01;
      }
      if(i < right) {
        bitset |= 0x80;
      }
      display_hw.Write(i+1, bitset);
    }
  }

  void smile(char left, char right) {
    unsigned char bits[8] = { 
      0x00, // 0000 0000
      0x42, // 0100 0010
      0xa5, // 1010 0101
      0x42, // 0100 0010    
      0x00, // 0000 0000
      0x00, // 0000 0000
      0x42, // 0100 0010
      0x3c, // 0011 1100
    };
    with_bars(bits, left, right);
  }
  
  void close_eyes(char left, char right) {
    unsigned char bits[8] = { 
      0x00, // 0000 0000
      0x00, // 0000 0000
      0xe7, // 1110 0111
      0x00, // 0000 0000    
      0x00, // 0000 0000
      0x3c, // 0011 1100
      0x42, // 0100 0010
      0x3c, // 0011 1100
    };
    with_bars(bits, left, right);
  }
};
