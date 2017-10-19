BOARD_TAG    = cm904
ARDUINO_LIBS =

#MONITOR_PORT = /dev/ttyACM0
CURRENT_DIR = ${PWD}
OPENCMIDE_DIR = ${CURRENT_DIR}/ROBOTIS_OpenCM-v1.0.2
LOCAL_INO_SRCS = ${CURRENT_DIR}/sketchbook/igmr_dynamixel_control/igmr_dynamixel_control.ino
TARGET = ${CURRENT_DIR}/sketchbook/igmr_dynamixel_control/igmr_dynamixel_control

include ${CURRENT_DIR}/makefiles/OpenCM.mk
