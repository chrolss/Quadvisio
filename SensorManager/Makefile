# You need to "sudo apt-get install libgtkmm-3.0-dev" to build the demo_3d binary

all: demo_raw demo_dmp demo_3d

HDRS = I2Cdev.h MPU6050.h
CMN_OBJS = I2Cdev.o MPU6050.o
RAW_OBJS = demo_raw.o

# Set DMP FIFO rate to 20Hz to avoid overflows on 3d demo.  See comments in
# MPU6050_6Axis_MotionApps20.h for details.

CXXFLAGS = -Wall -g -O2 

$(CMN_OBJS) $(DMP_OBJS) $(RAW_OBJS) : $(HDRS)

demo_raw: $(CMN_OBJS) $(RAW_OBJS)
	$(CXX) -o $@ $^ -lm

clean:
	rm -f $(CMN_OBJS) $(RAW_OBJS) demo_raw

