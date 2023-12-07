// Додекаэдр
// Лента 720 светодиодов плотностью 144/м
// 30 граней по 24 светодиода
//
//  case 40: Sparkle(0xff, 0xff, 0xff, thisdelay); break;                           случайные вспышки белого цвета
// https://github.com/AlexGyver/WS2812_FX/blob/master/прошивки/WS2812_FX_buttonChange/WS2812_FX_buttonChange.ino

// CRT таблица
const uint8_t CRTgammaPGM[256] PROGMEM = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    1,
    2,
    2,
    2,
    2,
    2,
    2,
    3,
    3,
    3,
    3,
    3,
    3,
    4,
    4,
    4,
    4,
    5,
    5,
    5,
    5,
    6,
    6,
    6,
    6,
    7,
    7,
    7,
    8,
    8,
    8,
    9,
    9,
    9,
    10,
    10,
    10,
    11,
    11,
    12,
    12,
    12,
    13,
    13,
    14,
    14,
    15,
    15,
    16,
    16,
    17,
    17,
    18,
    18,
    19,
    19,
    20,
    20,
    21,
    21,
    22,
    23,
    23,
    24,
    24,
    25,
    26,
    26,
    27,
    28,
    28,
    29,
    30,
    30,
    31,
    32,
    32,
    33,
    34,
    35,
    35,
    36,
    37,
    38,
    39,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    66,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    76,
    77,
    78,
    79,
    81,
    82,
    83,
    84,
    86,
    87,
    88,
    90,
    91,
    92,
    94,
    95,
    96,
    98,
    99,
    101,
    102,
    103,
    105,
    106,
    108,
    109,
    111,
    112,
    114,
    115,
    117,
    118,
    120,
    122,
    123,
    125,
    126,
    128,
    130,
    131,
    133,
    135,
    136,
    138,
    140,
    142,
    143,
    145,
    147,
    149,
    150,
    152,
    154,
    156,
    158,
    160,
    161,
    163,
    165,
    167,
    169,
    171,
    173,
    175,
    177,
    179,
    181,
    183,
    185,
    187,
    189,
    191,
    193,
    195,
    197,
    200,
    202,
    204,
    206,
    208,
    210,
    213,
    215,
    217,
    219,
    221,
    224,
    226,
    228,
    231,
    233,
    235,
    238,
    240,
    242,
    245,
    247,
    250,
    252,
    255,
};

#include <FastLED.h>
#include <TimerMs.h>
#include <Random16.h>
#include <CRT.h>
#include <Star.h>

#define FASTLED_ESP8266_D1_PIN_ORDER
#define NUM_LEDS 10 // 720
#define LED_PIN D3
#define BRIGHTNESS 64
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define VOLTS 5       // ограничение по напряжению
#define MILLIAMPS 1000 // ограничение по току

#define MIN_T 1 // Минимальный период в секундах
#define MAX_T 5 // Максимальынй период в секундах

Random16 rnd;
CRGB leds[NUM_LEDS];



unsigned int minT = 1000 * MIN_T; // мин время таймера
unsigned int maxT = 1000 * MAX_T; // мах время таймера

TimerMs tmrStar(random(minT, maxT), 1, 1);
TimerMs tmrFlash(random(minT, maxT), 1, 1);

int star_1 = 0;
int rndled1;
int rndled2;
boolean blink1 = 1; // должна ли мигнуть первая звезда
boolean blink2 = 1; // должна ли мигнуть вторая звезда

void setup()
{
  delay(1000); // защита при включении
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILLIAMPS);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  rnd.setSeed(12345);

}
void loop()
{
  // test(255, 255, 255, 500);

  if (tmrStar.tick())
  { 
    rndled1 = rnd.get(9);
    blink1 = 1;
    Serial.println(blink1);
  }

  if (blink1)
  {
   brightness_1(rndled1);
  }

    //  brightness_2();
    

  // Serial.print(tmrStar.tick());
  // Serial.println(tmrFlash.tick());
}

void blink(int star)
{
  static int val = 1;
  static bool dir = 1; // направление свечения
  // val = getBrightCRT(val); // берем значение из приятной глазу таиблицы

  val += dir;
  leds[star].setRGB(val, val, val);

  if (val == 255)
    dir = !dir; // разворачиваем
  if (val == 0)
    star_1 = 0;
}

// функция возвращает скорректированное по CRT значение
byte getBrightCRT(byte val)
{
  return pgm_read_byte(&(CRTgammaPGM[val]));
}

void test(int red, int green, int blue, int delayDuration)
{
  int pixel = random(NUM_LEDS);
  leds[pixel].setRGB(red, green, blue);
  // leds[pixel].setRGB(0, 0, 0);
}

void brightness_1(int star)
{
  // Яркоть звезды
  const byte brt1 = 1;
  const int dir = 1;
  if (tmrFlash.tick())
  {
    brt1 += dir;
    Serial.println(brt1);
  }
  if (brt1 == 255)
    dir = -1;

    if (brt1 == 0)
    {
      blink1 = 0;
      tmrStar.setTime(random(minT, maxT));
      tmrStar.start();
    }
  }
  leds[star].setRGB(brt1, brt1, brt1);
  FastLED.show(); // выводим изменения на ленту
}
