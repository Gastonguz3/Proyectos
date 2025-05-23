/* ** por compatibilidad se omiten tildes **
================================================================================
 TALLER System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

  Rutinas del controlador de interrupciones.
*/
#include "pic.h"

#define PIC1_PORT 0x20
#define PIC2_PORT 0xA0
#define CLK_PORT  0x40

static __inline __attribute__((always_inline)) void outb(uint32_t port,
                                                         uint8_t data) {
  __asm __volatile("outb %0,%w1" : : "a"(data), "d"(port));
}
void pic_finish1(void) { outb(PIC1_PORT, 0x20); }
void pic_finish2(void) {
  outb(PIC1_PORT, 0x20);
  outb(PIC2_PORT, 0x20);
}

void pic_reset() {
  outb(PIC1_PORT, 0x11);
  outb(PIC1_PORT + 1, 0x20);
  outb(PIC1_PORT + 1, 0x04);
  outb(PIC1_PORT + 1, 0x01);
  outb(PIC1_PORT + 1, 0xFF);

  outb(PIC2_PORT, 0x11);
  outb(PIC2_PORT + 1, 0x28);
  outb(PIC2_PORT + 1, 0x02);
  outb(PIC2_PORT + 1, 0x01);
  outb(PIC2_PORT + 1, 0xFF);
}

void pic_enable() {
  outb(PIC1_PORT + 1, 0x00);
  outb(PIC2_PORT + 1, 0x00);
}

void pic_disable() {
  outb(PIC1_PORT + 1, 0xFF);
  outb(PIC2_PORT + 1, 0xFF);
}

void pic_speedClock(){
  outb(CLK_PORT, 0x0);
  outb(CLK_PORT, 0x80);
}

void pic_lowSpeedClock(){
  outb(CLK_PORT, 0x54);
  outb(CLK_PORT, 0x37);
  outb(CLK_PORT, 0x12);
}
