// Додекаэдр
// Лента 720 светодиодов плотностью 144/м
// 30 граней по 24 светодиода
//
//  case 40: Sparkle(0xff, 0xff, 0xff, thisdelay); break;                           случайные вспышки белого цвета
// https://github.com/AlexGyver/WS2812_FX/blob/master/прошивки/WS2812_FX_buttonChange/WS2812_FX_buttonChange.ino

#include <FastLED.h>
#include <TimerMs.h>
#include <Random16.h>
#include <CRT.h>

#define FASTLED_ESP8266_D1_PIN_ORDER
#define NUM_LEDS 720
#define LED_PIN 2
#define BRIGHTNESS 64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
#define VOLTS 5;       // ограничение по напряжению
#define MILLIAMPS 600; // ограничение по току

#define MIN_T 20 // Минимальный период в секундах
#define MAX_T 50 // Максимальынй период в секундах

Random16 rnd;
CRGB leds[NUM_LEDS];

// (период, мс), (0 не запущен / 1 запущен), (режим: 0 период / 1 таймер)
TimerMs tmrStar(700, 1, 0); // период выбора новой звезды
TimerMs tmrFlash(10, 1, 0); // скорость мерцания

int rndled;

unsigned int minT = 1000 * MIN_T; // мин время таймера
unsigned int maxT = 1000 * MAX_T; // мах время таймера

void setup()
{
    delay(3000); // защита при включении
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MILLIAMPS);
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    // tmr.setTimerMode();
    tmr.setPeriodMode();
    rnd.setSeed(12345);
}
void loop()
{

    if (tmrStar.tick())
    {
        rndled = rnd.get(0, NUMLEDS); // выбираем случайныую звезду
        blink(rndled);                // мерцаем ей
    }
    FastLED.show(); // выводим изменения на ленту
}

void blink(int star)
{
    static int val = 0;

    if (tmrFlash.tick())
    {
        static bool dir = 1; // направление свечения
        val += dir;
        val = CRT8_table(val); // берем значение из приятной глазу таиблицы

        if (val == 255 || val == 0)
            dir = !dir; // разворачиваем
    }

    leds[star].setRGB(val, val, val);
}