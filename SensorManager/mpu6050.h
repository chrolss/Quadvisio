#ifndef MPU6050_H_
#define MPU6050_H_

#include "I2Cdev.h"

//#include <avr/pgmspace.h>

#define pgm_read_byte(p) (*(uint8_t *)(p))

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F
#define MPU6050_RA_MOT_DUR          0x20
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_I2C_MST_CTRL     0x24
#define MPU6050_RA_I2C_SLV0_ADDR    0x25
#define MPU6050_RA_I2C_SLV0_REG     0x26
#define MPU6050_RA_I2C_SLV0_CTRL    0x27
#define MPU6050_RA_I2C_SLV1_ADDR    0x28
#define MPU6050_RA_I2C_SLV1_REG     0x29
#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
#define MPU6050_RA_I2C_SLV2_REG     0x2C
#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
#define MPU6050_RA_I2C_SLV3_REG     0x2F
#define MPU6050_RA_I2C_SLV3_CTRL    0x30
#define MPU6050_RA_I2C_SLV4_ADDR    0x31
#define MPU6050_RA_I2C_SLV4_REG     0x32
#define MPU6050_RA_I2C_SLV4_DO      0x33
#define MPU6050_RA_I2C_SLV4_CTRL    0x34
#define MPU6050_RA_I2C_SLV4_DI      0x35
#define MPU6050_RA_I2C_MST_STATUS   0x36
#define MPU6050_RA_INT_PIN_CFG      0x37
#define MPU6050_RA_INT_ENABLE       0x38
#define MPU6050_RA_DMP_INT_STATUS   0x39
#define MPU6050_RA_INT_STATUS       0x3A
#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS    0x61
#define MPU6050_RA_I2C_SLV0_DO      0x63
#define MPU6050_RA_I2C_SLV1_DO      0x64
#define MPU6050_RA_I2C_SLV2_DO      0x65
#define MPU6050_RA_I2C_SLV3_DO      0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
#define MPU6050_RA_MOT_DETECT_CTRL      0x69
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C
#define MPU6050_RA_BANK_SEL         0x6D
#define MPU6050_RA_MEM_START_ADDR   0x6E
#define MPU6050_RA_MEM_R_W          0x6F
#define MPU6050_RA_DMP_CFG_1        0x70
#define MPU6050_RA_DMP_CFG_2        0x71
#define MPU6050_RA_FIFO_COUNTH      0x72
#define MPU6050_RA_FIFO_COUNTL      0x73
#define MPU6050_RA_FIFO_R_W         0x74
#define MPU6050_RA_WHO_AM_I         0x75

#define MPU6050_TC_PWR_MODE_BIT     7
#define MPU6050_TC_OFFSET_BIT       6
#define MPU6050_TC_OFFSET_LENGTH    6
#define MPU6050_TC_OTP_BNK_VLD_BIT  0

#define MPU6050_VDDIO_LEVEL_VLOGIC  0
#define MPU6050_VDDIO_LEVEL_VDD     1

#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU6050_CFG_DLPF_CFG_BIT    2
#define MPU6050_CFG_DLPF_CFG_LENGTH 3

#define MPU6050_EXT_SYNC_DISABLED       0x0
#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACONFIG_XA_ST_BIT           7
#define MPU6050_ACONFIG_YA_ST_BIT           6
#define MPU6050_ACONFIG_ZA_ST_BIT           5
#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_DHPF_RESET          0x00
#define MPU6050_DHPF_5              0x01
#define MPU6050_DHPF_2P5            0x02
#define MPU6050_DHPF_1P25           0x03
#define MPU6050_DHPF_0P63           0x04
#define MPU6050_DHPF_HOLD           0x07

#define MPU6050_TEMP_FIFO_EN_BIT    7
#define MPU6050_XG_FIFO_EN_BIT      6
#define MPU6050_YG_FIFO_EN_BIT      5
#define MPU6050_ZG_FIFO_EN_BIT      4
#define MPU6050_ACCEL_FIFO_EN_BIT   3
#define MPU6050_SLV2_FIFO_EN_BIT    2
#define MPU6050_SLV1_FIFO_EN_BIT    1
#define MPU6050_SLV0_FIFO_EN_BIT    0

#define MPU6050_MULT_MST_EN_BIT     7
#define MPU6050_WAIT_FOR_ES_BIT     6
#define MPU6050_SLV_3_FIFO_EN_BIT   5
#define MPU6050_I2C_MST_P_NSR_BIT   4
#define MPU6050_I2C_MST_CLK_BIT     3
#define MPU6050_I2C_MST_CLK_LENGTH  4

#define MPU6050_CLOCK_DIV_348       0x0
#define MPU6050_CLOCK_DIV_333       0x1
#define MPU6050_CLOCK_DIV_320       0x2
#define MPU6050_CLOCK_DIV_308       0x3
#define MPU6050_CLOCK_DIV_296       0x4
#define MPU6050_CLOCK_DIV_286       0x5
#define MPU6050_CLOCK_DIV_276       0x6
#define MPU6050_CLOCK_DIV_267       0x7
#define MPU6050_CLOCK_DIV_258       0x8
#define MPU6050_CLOCK_DIV_500       0x9
#define MPU6050_CLOCK_DIV_471       0xA
#define MPU6050_CLOCK_DIV_444       0xB
#define MPU6050_CLOCK_DIV_421       0xC
#define MPU6050_CLOCK_DIV_400       0xD
#define MPU6050_CLOCK_DIV_381       0xE
#define MPU6050_CLOCK_DIV_364       0xF

#define MPU6050_I2C_SLV_RW_BIT      7
#define MPU6050_I2C_SLV_ADDR_BIT    6
#define MPU6050_I2C_SLV_ADDR_LENGTH 7
#define MPU6050_I2C_SLV_EN_BIT      7
#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
#define MPU6050_I2C_SLV_REG_DIS_BIT 5
#define MPU6050_I2C_SLV_GRP_BIT     4
#define MPU6050_I2C_SLV_LEN_BIT     3
#define MPU6050_I2C_SLV_LEN_LENGTH  4

#define MPU6050_I2C_SLV4_RW_BIT         7
#define MPU6050_I2C_SLV4_ADDR_BIT       6
#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
#define MPU6050_I2C_SLV4_EN_BIT         7
#define MPU6050_I2C_SLV4_INT_EN_BIT     6
#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU6050_MST_PASS_THROUGH_BIT    7
#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
#define MPU6050_MST_I2C_LOST_ARB_BIT    5
#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
#define MPU6050_MST_I2C_SLV0_NACK_BIT   0

#define MPU6050_INTCFG_INT_LEVEL_BIT        7
#define MPU6050_INTCFG_INT_OPEN_BIT         6
#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU6050_INTCFG_CLKOUT_EN_BIT        0

#define MPU6050_INTMODE_ACTIVEHIGH  0x00
#define MPU6050_INTMODE_ACTIVELOW   0x01

#define MPU6050_INTDRV_PUSHPULL     0x00
#define MPU6050_INTDRV_OPENDRAIN    0x01

#define MPU6050_INTLATCH_50USPULSE  0x00
#define MPU6050_INTLATCH_WAITCLEAR  0x01

#define MPU6050_INTCLEAR_STATUSREAD 0x00
#define MPU6050_INTCLEAR_ANYREAD    0x01

#define MPU6050_INTERRUPT_FF_BIT            7
#define MPU6050_INTERRUPT_MOT_BIT           6
#define MPU6050_INTERRUPT_ZMOT_BIT          5
#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU6050_INTERRUPT_DMP_INT_BIT       1
#define MPU6050_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU6050_DMPINT_5_BIT            5
#define MPU6050_DMPINT_4_BIT            4
#define MPU6050_DMPINT_3_BIT            3
#define MPU6050_DMPINT_2_BIT            2
#define MPU6050_DMPINT_1_BIT            1
#define MPU6050_DMPINT_0_BIT            0

#define MPU6050_MOTION_MOT_XNEG_BIT     7
#define MPU6050_MOTION_MOT_XPOS_BIT     6
#define MPU6050_MOTION_MOT_YNEG_BIT     5
#define MPU6050_MOTION_MOT_YPOS_BIT     4
#define MPU6050_MOTION_MOT_ZNEG_BIT     3
#define MPU6050_MOTION_MOT_ZPOS_BIT     2
#define MPU6050_MOTION_MOT_ZRMOT_BIT    0

#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU6050_PATHRESET_GYRO_RESET_BIT        2
#define MPU6050_PATHRESET_ACCEL_RESET_BIT       1
#define MPU6050_PATHRESET_TEMP_RESET_BIT        0

#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU6050_DETECT_FF_COUNT_BIT             3
#define MPU6050_DETECT_FF_COUNT_LENGTH          2
#define MPU6050_DETECT_MOT_COUNT_BIT            1
#define MPU6050_DETECT_MOT_COUNT_LENGTH         2

#define MPU6050_DETECT_DECREMENT_RESET  0x0
#define MPU6050_DETECT_DECREMENT_1      0x1
#define MPU6050_DETECT_DECREMENT_2      0x2
#define MPU6050_DETECT_DECREMENT_4      0x3

#define MPU6050_USERCTRL_DMP_EN_BIT             7
#define MPU6050_USERCTRL_FIFO_EN_BIT            6
#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU6050_USERCTRL_DMP_RESET_BIT          3
#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU6050_PWR1_DEVICE_RESET_BIT       7
#define MPU6050_PWR1_SLEEP_BIT              6
#define MPU6050_PWR1_CYCLE_BIT              5
#define MPU6050_PWR1_TEMP_DIS_BIT           3
#define MPU6050_PWR1_CLKSEL_BIT             2
#define MPU6050_PWR1_CLKSEL_LENGTH          3

#define MPU6050_CLOCK_INTERNAL              0x00
#define MPU6050_CLOCK_PLL_XGYRO             0x01
#define MPU6050_CLOCK_PLL_YGYRO             0x02
#define MPU6050_CLOCK_PLL_ZGYRO             0x03
#define MPU6050_CLOCK_PLL_EXT32K            0x04
#define MPU6050_CLOCK_PLL_EXT19M            0x05
#define MPU6050_CLOCK_KEEP_RESET            0x07

#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU6050_PWR2_STBY_XA_BIT            5
#define MPU6050_PWR2_STBY_YA_BIT            4
#define MPU6050_PWR2_STBY_ZA_BIT            3
#define MPU6050_PWR2_STBY_XG_BIT            2
#define MPU6050_PWR2_STBY_YG_BIT            1
#define MPU6050_PWR2_STBY_ZG_BIT            0

#define MPU6050_WAKE_FREQ_1P25              0x0
#define MPU6050_WAKE_FREQ_2P5               0x1
#define MPU6050_WAKE_FREQ_5                 0x2
#define MPU6050_WAKE_FREQ_10                0x3

#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU6050_BANKSEL_MEM_SEL_BIT         4
#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5

#define MPU6050_WHO_AM_I_BIT                6
#define MPU6050_WHO_AM_I_LENGTH             6

#define MPU6050_DMP_MEMORY_BANKS            8
#define MPU6050_DMP_MEMORY_BANK_SIZE        256
#define MPU6050_DMP_MEMORY_CHUNK_SIZE       16

class mpu6050 {

private:
    void setSleep(bool enabled);
    void setFullScaleGyroRange(uint8_t range);
    void setFullScaleAccelRange(uint8_t range);
    uint8_t getDeviceID();
    
    int I2CBus;
    uint8_t I2CAdress;
    
	uint8_t buf[14];
	int fd;
	char *fileName;
    
	int16_t accX, accY, accZ;
	int16_t ax,ay,az,gx,gy,gz;
    double pitch, roll, yaw;
    
    
    
public:
	mpu6050(int bus, uint8_t adress);
    void initialize();
    bool testConnection();
    
    // DMP stuff
    void setDMPEnable(bool enabled);
    uint8_t getIntStatus();
    uint16_t getFIFOCount();
    void getFIFOBytes(uint8_t *data, uint8_t length);
    
    // USER_CTRL register
    bool getFIFOEnabled();
    void setFIFOEnabled(bool enabled);
    bool getI2CMasterModeEnabled();
    void setI2CMasterModeEnabled(bool enabled);
    void switchSPIEnabled(bool enabled);
    void resetFIFO();
    void resetI2CMaster();
    void resetSensors();
    
    // USER_CTRL register (DMP functions)
    bool getDMPEnabled();
    void setDMPEnabled(bool enabled);
    void resetDMP();
    
    // DMP_CFG_1 register
    uint8_t getDMPConfig1();
    void setDMPConfig1(uint8_t config);
    
    // DMP_CFG_2 register
    uint8_t getDMPConfig2();
    void setDMPConfig2(uint8_t config);
    
    // FIFO_EN register
    bool getTempFIFOEnabled();
    void setTempFIFOEnabled(bool enabled);
    bool getXGyroFIFOEnabled();
    void setXGyroFIFOEnabled(bool enabled);
    bool getYGyroFIFOEnabled();
    void setYGyroFIFOEnabled(bool enabled);
    bool getZGyroFIFOEnabled();
    void setZGyroFIFOEnabled(bool enabled);
    bool getAccelFIFOEnabled();
    void setAccelFIFOEnabled(bool enabled);
    bool getSlave2FIFOEnabled();
    void setSlave2FIFOEnabled(bool enabled);
    bool getSlave1FIFOEnabled();
    void setSlave1FIFOEnabled(bool enabled);
    bool getSlave0FIFOEnabled();
    void setSlave0FIFOEnabled(bool enabled);
    
    
    // XG_OFFS_TC register
    uint8_t getOTPBankValid();
    void setOTPBankValid(bool enabled);
    int8_t getXGyroOffset();
    void setXGyroOffset(int8_t offset);
    
    // YG_OFFS_TC register
    int8_t getYGyroOffset();
    void setYGyroOffset(int8_t offset);
    
    // ZG_OFFS_TC register
    int8_t getZGyroOffset();
    void setZGyroOffset(int8_t offset);
    
    // X_FINE_GAIN register
    int8_t getXFineGain();
    void setXFineGain(int8_t gain);
    
    // Y_FINE_GAIN register
    int8_t getYFineGain();
    void setYFineGain(int8_t gain);
    
    // Z_FINE_GAIN register
    int8_t getZFineGain();
    void setZFineGain(int8_t gain);
    
    // XA_OFFS_* registers
    int16_t getXAccelOffset();
    void setXAccelOffset(int16_t offset);
    
    // YA_OFFS_* register
    int16_t getYAccelOffset();
    void setYAccelOffset(int16_t offset);
    
    // ZA_OFFS_* register
    int16_t getZAccelOffset();
    void setZAccelOffset(int16_t offset);
    
    // XG_OFFS_USR* registers
    int16_t getXGyroOffsetUser();
    void setXGyroOffsetUser(int16_t offset);
    
    // YG_OFFS_USR* register
    int16_t getYGyroOffsetUser();
    void setYGyroOffsetUser(int16_t offset);
    
    // ZG_OFFS_USR* register
    int16_t getZGyroOffsetUser();
    void setZGyroOffsetUser(int16_t offset);
    
    // INT_ENABLE register (DMP functions)
    bool getIntPLLReadyEnabled();
    void setIntPLLReadyEnabled(bool enabled);
    bool getIntDMPEnabled();
    void setIntDMPEnabled(bool enabled);
    
    // PWR_MGMT_1 register
    void reset();
    bool getSleepEnabled();
    void setSleepEnabled(bool enabled);
    bool getWakeCycleEnabled();
    void setWakeCycleEnabled(bool enabled);
    bool getTempSensorEnabled();
    void setTempSensorEnabled(bool enabled);
    uint8_t getClockSource();
    void setClockSource(uint8_t source);
    
    // BANK_SEL register
    void setMemoryBank(uint8_t bank, bool prefetchEnabled=false, bool userBank=false);
    
    // MEM_START_ADDR register
    void setMemoryStartAddress(uint8_t address);
    
    // MEM_R_W register
    uint8_t readMemoryByte();
    void writeMemoryByte(uint8_t data);
    void readMemoryBlock(uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0);
    bool writeMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true, bool useProgMem=false);
    bool writeProgMemoryBlock(const uint8_t *data, uint16_t dataSize, uint8_t bank=0, uint8_t address=0, bool verify=true);
    
    bool writeDMPConfigurationSet(const uint8_t *data, uint16_t dataSize, bool useProgMem=false);
    bool writeProgDMPConfigurationSet(const uint8_t *data, uint16_t dataSize);
    
    #ifdef MPU6050_INCLUDE_DMP_MOTIONAPPS20
        uint16_t dmpGetFIFOPacketSize();
        
        uint8_t *dmpPacketBuffer;
        uint16_t dmpPacketSize;
        
        uint8_t dmpInitialize();
        bool dmpPacketAvailable();
        
        uint8_t dmpSetFIFORate(uint8_t fifoRate);
        uint8_t dmpGetFIFORate();
        uint8_t dmpGetSampleStepSizeMS();
        uint8_t dmpGetSampleFrequency();
        int32_t dmpDecodeTemperature(int8_t tempReg);
        
        // Register callbacks after a packet of FIFO data is processed
        //uint8_t dmpRegisterFIFORateProcess(inv_obj_func func, int16_t priority);
        //uint8_t dmpUnregisterFIFORateProcess(inv_obj_func func);
        uint8_t dmpRunFIFORateProcesses();
        
        // Setup FIFO for various output
        uint8_t dmpSendQuaternion(uint_fast16_t accuracy);
        uint8_t dmpSendGyro(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendAccel(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendLinearAccel(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendLinearAccelInWorld(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendControlData(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendExternalSensorData(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendGravity(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendPacketNumber(uint_fast16_t accuracy);
        uint8_t dmpSendQuantizedAccel(uint_fast16_t elements, uint_fast16_t accuracy);
        uint8_t dmpSendEIS(uint_fast16_t elements, uint_fast16_t accuracy);
        
        // Get Fixed Point data from FIFO
        uint8_t dmpGetAccel(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetAccel(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetAccel(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetQuaternion(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetQuaternion(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetQuaternion(Quaternion *q, const uint8_t* packet=0);
        uint8_t dmpGet6AxisQuaternion(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGet6AxisQuaternion(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGet6AxisQuaternion(Quaternion *q, const uint8_t* packet=0);
        uint8_t dmpGetRelativeQuaternion(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetRelativeQuaternion(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetRelativeQuaternion(Quaternion *data, const uint8_t* packet=0);
        uint8_t dmpGetGyro(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyro(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyro(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpSetLinearAccelFilterCoefficient(float coef);
        uint8_t dmpGetLinearAccel(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccel(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccel(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccel(VectorInt16 *v, VectorInt16 *vRaw, VectorFloat *gravity);
        uint8_t dmpGetLinearAccelInWorld(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccelInWorld(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetLinearAccelInWorld(VectorInt16 *v, VectorInt16 *vReal, Quaternion *q);
        uint8_t dmpGetGyroAndAccelSensor(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyroAndAccelSensor(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyroAndAccelSensor(VectorInt16 *g, VectorInt16 *a, const uint8_t* packet=0);
        uint8_t dmpGetGyroSensor(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyroSensor(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGyroSensor(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetControlData(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetTemperature(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGravity(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGravity(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetGravity(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetGravity(VectorFloat *v, Quaternion *q);
        uint8_t dmpGetUnquantizedAccel(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetUnquantizedAccel(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetUnquantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetQuantizedAccel(int32_t *data, const uint8_t* packet=0);
        uint8_t dmpGetQuantizedAccel(int16_t *data, const uint8_t* packet=0);
        uint8_t dmpGetQuantizedAccel(VectorInt16 *v, const uint8_t* packet=0);
        uint8_t dmpGetExternalSensorData(int32_t *data, uint16_t size, const uint8_t* packet=0);
        uint8_t dmpGetEIS(int32_t *data, const uint8_t* packet=0);
        
        uint8_t dmpGetEuler(float *data, Quaternion *q);
        uint8_t dmpGetYawPitchRoll(float *data, Quaternion *q, VectorFloat *gravity);
    
        // Get Floating Point data from FIFO
        uint8_t dmpGetAccelFloat(float *data, const uint8_t* packet=0);
        uint8_t dmpGetQuaternionFloat(float *data, const uint8_t* packet=0);
        
        uint8_t dmpProcessFIFOPacket(const unsigned char *dmpData);
        uint8_t dmpReadAndProcessFIFOPacket(uint8_t numPackets, uint8_t *processed=NULL);
        
        uint8_t dmpSetFIFOProcessedCallback(void (*func) (void));
        
        uint8_t dmpInitFIFOParam();
        uint8_t dmpCloseFIFO();
        uint8_t dmpSetGyroDataSource(uint8_t source);
        uint8_t dmpDecodeQuantizedAccel();
        uint32_t dmpGetGyroSumOfSquare();
        uint32_t dmpGetAccelSumOfSquare();
        void dmpOverrideQuaternion(long *q);
    #endif

    
	double getAccX() {return accX;}
	double getAccY() {return accY;}
	double getAccZ() {return accZ;}
    void getMotion(double* ax, double* ay, double* az, double* gx, double* gy, double* gz);
	virtual ~mpu6050();
};

#endif /* MPU6050_H_ */
