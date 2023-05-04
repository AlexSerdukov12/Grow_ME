#ifndef FANCONTROL_H
#define FANCONTROL_H

class FanControl {
  private:
    const int INA1, INB1, INA2, INB2;

  public:
    FanControl(int ina1, int inb1, int ina2, int inb2);
    void begin();
    void update(float temperature);
};

#endif