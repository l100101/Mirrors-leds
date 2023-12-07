//#include <FastLED.h>

class STAR {
  public:
    STAR(byte pos, uint16_t prd, int* leds, int num) {
      _pos = pos;
      _prd = prd;
	  _num = num;
	  _leds = &leds;
    }

    void setPrd(uint16_t prd) {
      _prd = prd;
    }
	
    void blink() {
      if (millis() - _tmr >= _prd) {
		if (_dir) _val++; // увеличиваем яркость
		else _val--;     // уменьшаем
		if (_val >= 255 || _val <= 0) _dir = !_dir; // разворачиваем
		//analogWrite(3, getBrightCRT(val));
		_val=getBrightCRT(_val);
		leds[_pos].setRGB(_val, _val, _val);
      }
	  
    }

  private:
    byte _pos;
    uint32_t _tmr;
    uint16_t _prd;
    uint16_t _num;
    uint16_t _leds[];

    bool _dir;
	byte _val = 0;
	
	byte getBrightCRT(byte val) {
		return ((long)val * val * val + 130305) >> 16;
	}
	
};