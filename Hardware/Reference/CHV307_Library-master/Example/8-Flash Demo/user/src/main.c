/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file             main
* @company          成都逐飞科技有限公司
 * @author          逐飞科技(QQ790875685)
* @version          查看doc内version文件 版本说明
* @Software         MounRiver Studio V1.51
* @Target core      CH32V307VCT6
* @Taobao           https://seekfree.taobao.com/
* @date             2021-11-25
********************************************************************************************************************/


// *************************** 例程硬件连接说明 ***************************
// 使用逐飞科技 WCH-LINK 调试下载器连接
//      直接将下载器正确连接在核心板的调试下载接口即可
// 使用 USB-TTL 模块连接
//      模块管脚            单片机管脚
//      USB-TTL-RX          查看 zf_common_debug.h 文件中 DEBUG_UART_TX_PIN 宏定义的引脚 默认 B10
//      USB-TTL-TX          查看 zf_common_debug.h 文件中 DEBUG_UART_RX_PIN 宏定义的引脚 默认 B11
//      USB-TTL-GND         核心板电源地 GND
//      USB-TTL-3V3         核心板 3V3 电源

// *************************** 例程测试说明 ***************************
// 1.核心板烧录完成本例程，单独使用核心板与调试下载器或者 USB-TTL 模块，在断电情况下完成连接
// 2.将调试下载器或者 USB-TTL 模块连接电脑，完成上电
// 3.电脑上使用串口助手打开对应的串口，串口波特率为 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义 默认 115200，核心板按下复位按键
// 4.可以在串口助手上看到如下串口信息：
//      FLASH_SECTION_INDEX: 62, FLASH_PAGE_INDEX: 3, origin data is :
//      ...
// 如果发现现象与说明严重不符 请参照本文件最下方 例程常见问题说明 进行排查



#include "zf_common_headfile.h"


// **************************** 代码区域 ****************************

// 这段宏定义是为了演示如何向 FLASH 使用缓冲区写入和读取数据而定义
#define FLASH_SECTION_INDEX       FLASH_SECTION_62                          // 存储数据用的扇区 倒数第二个扇区
#define FLASH_PAGE_INDEX          FLASH_PAGE_3                              // 存储数据用的页码 倒数第一个页码





int main(void)
{
    interrupt_global_disable();            // 关闭总中断
    clock_init(SYSTEM_CLOCK_144M);      // 务必保留，设置系统时钟。
    debug_init();                       // 务必保留，本函数用于初始化MPU 时钟 调试串口

    // 此处编写用户代码 例如外设初始化代码等
     if(flash_check(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX))                      // 判断是否有数据
         flash_erase_page(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);                // 擦除这一页

     flash_read_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);      // 将数据从 flash 读取到缓冲区
     printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, origin data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // 将缓冲区第 1 个位置的数据以 uint32 格式输出
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // 将缓冲区第 2 个位置的数据以 int32  格式输出
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // 将缓冲区第 3 个位置的数据以 uint16 格式输出
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // 将缓冲区第 4 个位置的数据以 int16  格式输出
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // 将缓冲区第 5 个位置的数据以 uint8  格式输出
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // 将缓冲区第 6 个位置的数据以 int8   格式输出

     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

     // 例如 flash_data_union_buffer[0] 写入 int8_type 那么只能以 int8_type 读取
     // 同样 flash_data_union_buffer[0] 写入 float_type 那么只能以 float_type 读取
     printf("\r\n Data property display :");
     printf("\r\n flash_data_union_buffer[0] write int8 data type:");
     flash_data_union_buffer[0].int8_type   = -128;                              // 向缓冲区第 0 个位置写入     int8   数据
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出 数据将不正确
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // 将缓冲区第 0 个位置的数据以 int8   格式输出 得到正确写入数据

     printf("\r\n flash_data_union_buffer[0] write int8 data type:");
     flash_data_union_buffer[0].int8_type  -= 1;                                 // 向缓冲区第 0 个位置写入     int8   数据
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出 数据将不正确
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // 将缓冲区第 0 个位置的数据以 int8   格式输出 得到正确写入数据

     printf("\r\n flash_data_union_buffer[0] write float data type:");
     flash_data_union_buffer[0].float_type  = 16.625;                            // 向缓冲区第 0 个位置写入     float  数据
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出 得到正确写入数据
     printf("\r\n int8_type  : %d", flash_data_union_buffer[0].int8_type);       // 将缓冲区第 0 个位置的数据以 int8   格式输出 数据将不正确

     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据
     // 请注意 数据缓冲区的每个位置只能存储一种类型的数据

     flash_data_buffer_clear();                                                  // 清空缓冲区
     flash_data_union_buffer[0].float_type  = 3.1415926;                         // 向缓冲区第 0 个位置写入 float  数据
     flash_data_union_buffer[1].uint32_type = 4294967295;                        // 向缓冲区第 1 个位置写入 uint32 数据
     flash_data_union_buffer[2].int32_type  = -2147483648;                       // 向缓冲区第 2 个位置写入 int32  数据
     flash_data_union_buffer[3].uint16_type = 65535;                             // 向缓冲区第 3 个位置写入 uint16 数据
     flash_data_union_buffer[4].int16_type  = -32768;                            // 向缓冲区第 4 个位置写入 int16  数据
     flash_data_union_buffer[5].uint8_type  = 255;                               // 向缓冲区第 5 个位置写入 uint8  数据
     flash_data_union_buffer[6].int8_type   = -127;                              // 向缓冲区第 6 个位置写入 int8   数据
     flash_write_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);     // 向指定 Flash 扇区的页码写入缓冲区数据


     flash_data_buffer_clear();                                                  // 清空缓冲区
     printf("\r\n Flash data buffer default data is :");
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // 将缓冲区第 1 个位置的数据以 uint32 格式输出
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // 将缓冲区第 2 个位置的数据以 int32  格式输出
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // 将缓冲区第 3 个位置的数据以 uint16 格式输出
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // 将缓冲区第 4 个位置的数据以 int16  格式输出
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // 将缓冲区第 5 个位置的数据以 uint8  格式输出
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // 将缓冲区第 6 个位置的数据以 int8   格式输出


     flash_read_page_to_data_buffer(FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);      // 将数据从 flash 读取到缓冲区
     printf("\r\n FLASH_SECTION_INDEX: %d, FLASH_PAGE_INDEX: %d, new data is :", FLASH_SECTION_INDEX, FLASH_PAGE_INDEX);
     printf("\r\n float_type : %f", flash_data_union_buffer[0].float_type);      // 将缓冲区第 0 个位置的数据以 float  格式输出
     printf("\r\n uint32_type: %u", flash_data_union_buffer[1].uint32_type);     // 将缓冲区第 1 个位置的数据以 uint32 格式输出
     printf("\r\n int32_type : %d", flash_data_union_buffer[2].int32_type);      // 将缓冲区第 2 个位置的数据以 int32  格式输出
     printf("\r\n uint16_type: %u", flash_data_union_buffer[3].uint16_type);     // 将缓冲区第 3 个位置的数据以 uint16 格式输出
     printf("\r\n int16_type : %d", flash_data_union_buffer[4].int16_type);      // 将缓冲区第 4 个位置的数据以 int16  格式输出
     printf("\r\n uint8_type : %u", flash_data_union_buffer[5].uint8_type);      // 将缓冲区第 5 个位置的数据以 uint8  格式输出
     printf("\r\n int8_type  : %d", flash_data_union_buffer[6].int8_type);       // 将缓冲区第 6 个位置的数据以 int8   格式输出
     printf("\r\n");
     // 此处编写用户代码 例如外设初始化代码等
    interrupt_global_enable();            // 总中断最后开启
    while(1)
    {

    }
}
// **************************** 代码区域 ****************************

// *************************** 例程常见问题说明 ***************************
// 遇到问题时请按照以下问题检查列表检查
// 问题1：串口没有数据
//      查看串口助手打开的是否是正确的串口，检查打开的 COM 口是否对应的是调试下载器或者 USB-TTL 模块的 COM 口
//      如果是使用逐飞科技 WCH-LINK 调试下载器连接，那么检查下载器线是否松动，检查核心板串口跳线是否已经焊接，串口跳线查看核心板原理图即可找到
//      如果是使用 USB-TTL 模块连接，那么检查连线是否正常是否松动，模块 TX 是否连接的核心板的 RX，模块 RX 是否连接的核心板的 TX
//      如果上述检查都正常，但依旧没有输出数据，就进入调试看看是否进入断言，如果进入断言就更换扇区和页码尝试，如果依旧不行，那么联系技术支持
// 问题2：串口数据乱码
//      查看串口助手设置的波特率是否与程序设置一致，程序中 zf_common_debug.h 文件中 DEBUG_UART_BAUDRATE 宏定义为 debug uart 使用的串口波特率
// 问题3：数据不对
//      更换扇区和页码尝试，如果数据依旧读出不正确，联系技术支持



