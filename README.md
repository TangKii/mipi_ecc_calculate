# mipi_ecc_calculate
calculate mipi DSI packet header ecc value
algorithm refer to https://eevblog.com/forum/microcontrollers/calculate-ecc-byte-for-mipi-dsi-header/


#build
build with gcc: gcc ecc.c -o mipi_ecc_cal

#usage：
mipi_ecc_cal 0x9c21

user01:/mnt/d/worktmp/ecc$ ./mipi_ecc_cal 0x9c21
0x00009c21 ecc result = 0x1e009c21
user01:/mnt/d/worktmp/ecc
