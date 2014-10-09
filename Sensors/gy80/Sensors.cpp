#include "Sensors.h"
bool Sensors::selectDevice(int i2c, int addr, char * name)
{
   if (ioctl(i2c, I2C_SLAVE, addr) < 0)
   {
      fprintf(stderr, "%s not present\n", name);
      return false;
   }

   return true;
}
const std::vector<short> Sensors::getxyz()
{
   std::vector<short> xyz;
   xyz.push_back(x);
   xyz.push_back(y);
   xyz.push_back(z);
   return xyz;
}
bool Sensors::writeToDevice(int i2c, char * buf, int len)
{
   if (write(i2c, buf, len) != len)
   {
      fprintf(stderr, "Can't write to device\n");
      return false;
   }
  return true;
}