#define M_BEGIN do {
#define M_END } while(0)

#define BIT_SET(P, B) M_BEGIN \
  *(volatile unsigned char *)(P) |= (1u << (B)); \
  M_END
#define BIT_CLR(P, B) M_BEGIN \
  *(volatile unsigned char *)(P) &=~ (1u << (B)); \
  M_END

/*
These are SRAM addresses, recall SRAM address = IO address + 0x20.
*/
#define PORTB (0x38)
#define DDRB (0x37)

void
delay(unsigned int i) {
  do {
    unsigned int n = 2000;
    __asm__ __volatile__ (
      "1: sbiw %0,1" "\n\t" // 2 cycles
      "brne 1b" : "=w" (n) : "0" (n) // 2 cycles
    );
    --i;
  } while(i);
}

int
main(void) {
  unsigned char i;

  BIT_SET(DDRB, 1);

  while(1) {
    BIT_SET(PORTB, 1);
    delay(200);
    BIT_CLR(PORTB, 1);
    delay(200);
    for(i=0; i<8; ++i) {
      BIT_SET(PORTB, 1);
      delay(25);
      BIT_CLR(PORTB, 1);
      delay(25);
    }
    delay(200);
  }
}

