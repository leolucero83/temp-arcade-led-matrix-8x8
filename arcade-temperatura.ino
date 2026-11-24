#include <OneWire.h>
#include <DallasTemperature.h>
#include <LedControl.h>
#include <SPI.h>

// Definir el pin del sensor DS18B20
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Definir pines para la matriz 8x8 con MAX7219
#define MATRIX 0
#define DIN 4
#define CS  6
#define CLK 5
#define FRAME_DELAY 200

// Definir variables para la temperatura
int tens;
int units;
float tempc;


byte zero[] = {B00111000,B01000100,B01000100,B00111000,B00111000,B01000100,B01000100,B00111000};
byte one[] = {B00000000,B01000100,B01111100,B01000000,B00000000,B01000100,B01111100,B01000000};
byte two[] = {B01100100,B01010100,B01001100,B00000000,B00000000,B01100100,B01010100,B01001100};
byte three[] = {B01000100,B01010100,B01101100,B00000000,B00000000,B01000100,B01010100,B01101100};
byte four[] = {B00110000,B00101000,B01111100,B00000000,B00000000,B00110000,B00101000,B01111100};
byte five[] = {B01011100,B01010100,B01110100,B00000000,B00000000,B01011100,B01010100,B01110100};
byte six[] = {B01111100,B01010100,B01110100,B00000000,B00000000,B01111100,B01010100,B01110100};
byte seven[] = {B01100100,B00010100,B00001100,B00000000,B00000000,B01100100,B00010100,B00001100};
byte eight[] = {B01111100,B01010100,B01111100,B00000000,B00000000,B01101100,B01010100,B01111100};
byte nine[] = {B01011100,B01010100,B01111100,B00000000,B00000000,B01011100,B01010100,B01111100};


// ---------- SPACE INVADERS ----------
const uint64_t spaceInvaders[] = {
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0x24a5ffffdb7e2424,
  0x42247effdbffa524,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
  0xa55a24ffdb7e3c18,
  0x425a24ffdb7e3c18,
};


// ---------- PACMAN ----------
const uint64_t pacman[] = {
  0x0101010101010000,
  0x0203030302020100,
  0x0507060705040301,
  0x0a0f0c0f0b090703,
  0x151f181f16120f07,
  0x2a3f303f2d241f0e,
  0x557f617f5b493e1c,
  0xaafec2feb6927c38,
  0x54fc84fc6c24f870,
  0xa8f808f8d848f0e0,
  0x50f010f0b090e0c0,
  0xa0e020e06020c080,
  0x40c040c0c0408000,
  0x8080808080800000,
  0x0001000000000100,
  0x0103010000010301,
  0x0307070007070703,
  0x070f070103070f07,
  0x0f1f1f031f1e1f0f,
  0x1e3f1f070f1d3f1e,
  0x3c7e7f0f7f7b7e3c,
  0x78fc7e1e3e76fc78,
  0xf0f8fc3cfcecf8f0,
  0xe0f0f878f8d8f0e0,
  0xc0e0f0f0f0b0e0c0,
  0x80c0e0e0e060c080,
  0x0080c0c0c0c08000,
  0x0000808080800000,
  0x0000000000000000
};

// ---------- TETRIS ----------
const uint64_t tetris[] = {
  0x000000000000000f,
  0x0000000000000f0f,
  0x00000000000f0f03,
  0x000000000f0f0303,
  0x0000000f0f030303,
  0x00000f0f03030300,
  0x000f0f0303030000,
  0x0f0f030303000000,
  0x0f0f03030300000c,
  0x0f0f030303000c0c,
  0x0f0f0303030c0c0c,
  0x0f0f03031b181818,
  0x0f0f033333303030,
  0x0f0f636363606000,
  0x0fcfc3c3c3c00000,
  0xcfcfc3c3c3000000,
  0xcfcfc3c3c3000030,
  0xcfcfc3c3c3003030,
  0xcfcfc3c3c330303c,
  0xcfcfc3c3f3303c3c,
  0xcfcfc3f3f33c3c0c,
  0xcfcff3f3ff3c0c0c,
  0xcffff3ffff0c0c00,
  0xffffffffcf0c0000,
  0xaa55ffffcf0c0000,
  0x0000ffffcf0c0000,
  0x00ffffcf0c000000,
  0xffffcf0c00000000,
  0xaa55cf0c00000000,
  0x0000cf0c00000000,
  0x00cf0c0000000000,
  0xcf0c000000000000
};



// ---------- SNAKE ----------
const uint64_t snake[] = {
  0x0000002000000001,
  0x0000002000000003,
  0x0000002000000007,
  0x000000200000000f,
  0x000000200000001e,
  0x000000200000003c,
  0x0000002000002038,
  0x0000002000202030,
  0x0000002020202020,
  0x0004202020202000,
  0x0024202020200000,
  0x0034202020000000,
  0x003c202000000000,
  0x003c240008000000,
  0x003c040408000000,
  0x001c04040c004000,
  0x000c04041c004000,
  0x000404043c004000,
  0x000004047c004000,
  0x000000047c404100,
  0x000000007c406100,
  0x0000000078407100,
  0x0000000070407900,
  0x0000000060407d00,
  0x0000000040407f00
};

// ---------- CUADRADO ----------
const uint64_t cuadrado[] = {
  0x0000001818000000,
  0x00003c24243c0000,
  0x007e424242427e00,
  0xff818181818181ff,
  0x0000000000000000,
  0x0000001818000000,
  0x00003c24243c0000,
  0x007e424242427e00,
  0xff818181818181ff,
  0x0000000000000000
};



// ---------- PIN PONG  ----------
const uint64_t pinpong[] = {
  0x0101030180808080,
  0x0001010581808080,
  0x0001018189808000,
  0x0001018181908000,
  0x000101018180a080,
  0x00010101818080c0,
  0x000101018180c080,
  0x0001018181a08000,
  0x0000008191818100,
  0x0000008981818100,
  0x0000058181818000,
  0x0003018181808000,
  0x0103018180808000,
  0x0501018180808000,
  0x0009818181800000,
  0x0081918181000000,
  0x808181a101000000,
  0x8081818141000000,
  0x00818181c1000000,
  0x00018181c1800000,
  0x0001818181a00000,
  0x0001018181809000,
  0x0000018181818008,
  0x0000008181818500,
  0x0000008081838101
};

// ---------- TNT  ----------
const uint64_t tnt[] = {
  0x3c66603860663c00,
  0x3c66603860663c00,
  0x3c66603860663c00,
  0x7e060c3060663c00,
  0x7e060c3060663c00,
  0x7e060c3060663c00,
  0x7e1818181c181800,
  0x7e1818181c181800,
  0x7e1818181c181800,
  0x0000000000000000,
  0x993c66dbdb623c99,
  0x66c399242499c366,
  0x4299244242249942,
  0x9924428181422499,
  0x2442810000814224,
  0x4281000000008142,
  0x8100000000000081,
  0x0000000000000000,
  0x0000000000000000,
  0x0000000000000000
};

const uint64_t zigzag[] = {
  0x0804020102040810,
  0x0402010204081020,
  0x0201020408102040,
  0x0102040810204080,
  0x0204081020408040,
  0x0408102040804020,
  0x0810204080402010,
  0x1020408040201008,
  0x2040804020100804,
  0x4080402010080402,
  0x8040201008040201,
  0x4020100804020102,
  0x2010080402010204,
  0x1008040201020408,
  0x0804020102040810,
  0x0402010204081020,
  0x0201020408102040,
  0x0102040810204080,
  0x0204081020408040,
  0x0408102040804020,
  0x0810204080402010,
  0x1020408040201008,
  0x2040804020100804,
  0x4080402010080402,
  0x8040201008040201,
  0x4020100804020102,
  0x2010080402010204,
  0x1008040201020408
};




const uint64_t* animations[] = {
  spaceInvaders,
  pacman,
  tetris,
  snake,
  cuadrado,
  pinpong,
  tnt,
  zigzag
};

const uint16_t animationLengths[] = {
  sizeof(spaceInvaders) / 8,
  sizeof(pacman) / 8,
  sizeof(tetris) / 8,
  sizeof(snake) / 8,
  sizeof(cuadrado) / 8,
  sizeof(pinpong) / 8,
  sizeof(tnt) / 8,
  sizeof(zigzag) / 8
};

const byte ANIM_COUNT = sizeof(animations) / sizeof(animations[0]);

// Inicialización de la matriz de LED
LedControl lc = LedControl(DIN, CLK, CS, 1);

  


void setup() {  

  lc.shutdown(0, false);    // Desactivar modo de ahorro de energía
  lc.setIntensity(0, 1);     // Establecer el brillo de la matriz
  lc.clearDisplay(0);        // Limpiar la matriz

  sensors.begin();           // Inicializar el sensor DS18B20
}



void shuffleIndexes(byte* array, byte length) {
  for (byte i = length - 1; i > 0; i--) {
    byte j = random(0, i + 1);
    byte tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
  }
}

void drawFrame(uint64_t frame) {
  for (int y = 0; y < 8; y++) {
    byte row = (frame >> (y * 8)) & 0xFF;

    for (int x = 0; x < 8; x++) {
      // rotación 90° CW: (x, y) → (y, 7 - x)
      lc.setLed(0, x, 7 - y, bitRead(row, x));
    }
  }
}


void playAnimation(byte index) {
  for (uint16_t i = 0; i < animationLengths[index]; i++) {
    drawFrame(animations[index][i]);
    delay(FRAME_DELAY);
  }
}

byte animOrder[] = { 0, 1, 2, 3, 4, 5, 6, 7 };

void loop() {
  // Desordenar el orden de reproducción
  shuffleIndexes(animOrder, ANIM_COUNT);

  // Solicitar lectura de la temperatura
  sensors.requestTemperatures();  
  tempc = sensors.getTempCByIndex(0);  // Obtener la temperatura en grados Celsius

  // Extraer decenas y unidades de la temperatura
  int tempInt = (int)tempc;  // Parte entera de la temperatura
  int tempDecimal = (int)((tempc - tempInt) * 10 + 0.5);  // Primer decimal

  tens = tempInt / 10;  // Decenas
  units = tempInt % 10;  // Unidades

  // Reproducir todas las animaciones UNA sola vez
  for (byte i = 0; i < ANIM_COUNT; i++) {
    playAnimation(animOrder[i]);

    // Mostrar los dígitos en la matriz LED
    displayTemperature(tens, units);

    // Mostrar los decimales en la primera fila de la matriz
    displayDecimals(tempDecimal);

    delay(5000);  // Esperar 5 segundos antes de la siguiente animacion
  }
}


void displayTemperature(int tens, int units) {
  // Mostrar el primer dígito (decenas)
  for (int f = 0; f < 7; f++) {
    if (tens == 0) {
      lc.setRow(0, f, zero[f]);
    } else if (tens == 1) {
      lc.setRow(0, f, one[f]);
    } else if (tens == 2) {
      lc.setRow(0, f, two[f]);
    } else if (tens == 3) {
      lc.setRow(0, f, three[f]);
    } else if (tens == 4) {
      lc.setRow(0, f, four[f]);
    } else if (tens == 5) {
      lc.setRow(0, f, five[f]);
    } else if (tens == 6) {
      lc.setRow(0, f, six[f]);
    } else if (tens == 7) {
      lc.setRow(0, f, seven[f]);
    } else if (tens == 8) {
      lc.setRow(0, f, eight[f]);
    } else if (tens == 9) {
      lc.setRow(0, f, nine[f]);
    }
  }

  // Mostrar el segundo dígito (unidades)
  for (int f = 0; f < 7; f++) {
    if (units == 0) {
      lc.setRow(0, f + 4, zero[f]);
    } else if (units == 1) {
      lc.setRow(0, f + 4, one[f]);
    } else if (units == 2) {
      lc.setRow(0, f + 4, two[f]);
    } else if (units == 3) {
      lc.setRow(0, f + 4, three[f]);
    } else if (units == 4) {
      lc.setRow(0, f + 4, four[f]);
    } else if (units == 5) {
      lc.setRow(0, f + 4, five[f]);
    } else if (units == 6) {
      lc.setRow(0, f + 4, six[f]);
    } else if (units == 7) {
      lc.setRow(0, f + 4, seven[f]);
    } else if (units == 8) {
      lc.setRow(0, f + 4, eight[f]);
    } else if (units == 9) {
      lc.setRow(0, f + 4, nine[f]);
    }
  }
}

// Función para mostrar el primer decimal en la primera fila (Row 0)
void displayDecimals(int decimals) {
    if(decimals == 0){ // apago todos
      for (int fila = 0; fila < 8; fila++) {
        lc.setLed(0, fila, 7, false);
      }
    }

    if(decimals == 9){ // prendo los 8 leds para indicar 9
      for (int fila = 0; fila < 8; fila++) {
        lc.setLed(0, fila, 7, true);
      }
    }

    // Establecer el patrón de LEDs en la fila 0
    lc.setLed(0, decimals-1, 7, 1); 
}
