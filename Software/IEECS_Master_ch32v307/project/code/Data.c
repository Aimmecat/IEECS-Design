/*
 * Data.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//用于接收soar传输的指令
uint8 sip_receive_info_One[RECEIVE_MAXLEN];
//uint8 sip_receive_info_Two[RECEIVE_MAXLEN];

uint8 voltage;


//标注*表示soar缺省值 后续观察若无必要可在soar中对应删除
uint8 standard_sip_info[] = {
      FIRST_HEAD,                               //Head_first                0
      SECOND_HEAD,                              //Head_second               1
      46,                                       //Len                       2
      STOP_TYPE,                                //motors status             3
      0,                                        //xPos 低八位                                                   4
      0,                                        //xPos 高八位                                                   5
      0,                                        //yPos 低八位                                                   6
      0,                                        //yPos 高八位                                                   7
      0,                                        //thPos ---> angle 低八位               8
      0,                                        //thPos ---> angle 高八位               9
      0,                                        //*l_vel 低八位                                             10
      0,                                        //*l_vel 高八位                                             11
      0,                                        //*r_vel 低八位                                             12
      0,                                        //*r_vel 高八位                                             13
      80,                                       //*Battery 80 ---> 8.0V     14
      0x00,                                     //stall and bumpers 低八位            15
      0x00,                                     //stall and bumpers 高八位            16
      0,                                        //*setPointdegree diff 低八位   17
      0,                                        //*setPointdegree diff 高八位   18
      0x00,                                     //*flags 低八位                                             19
      0x00,                                     //*flags 高八位                                             20
      0,                                        //*Electronic compass       21
      8,                                        //new sonar reading         22

      0,                                        //sonar_0 标志号                                          23
      1,                                        //sonar_0 低八位                                          24
      0,                                        //sonar_0 高八位                                          25

      1,                                        //sonar_1 标志号                                          26
      1,                                        //sonar_1 低八位                                          27
      0,                                        //sonar_1 高八位                                          28

      2,                                        //sonar_2 标志号                                          29
      1,                                        //sonar_2 低八位                                          30
      0,                                        //sonar_2 高八位                                          31

      3,                                        //sonar_3 标志号                                          32
      1,                                        //sonar_3 低八位                                          33
      0,                                        //sonar_3 高八位                                          34

      4,                                        //sonar_4 标志号                                          35
      1,                                        //sonar_4 低八位                                          36
      0,                                        //sonar_4 高八位                                          37

      5,                                        //sonar_5 标志号                                          38
      1,                                        //sonar_5 低八位                                          39
      0,                                        //sonar_5 高八位                                          40

      6,                                        //sonar_6 标志号                                          41
      1,                                        //sonar_6 低八位                                          42
      0,                                        //sonar_6 高八位                                          43

      7,                                        //sonar_7 标志号                                          44
      1,                                        //sonar_7 低八位                                          45
      0,                                        //sonar_7 高八位                                          46

      //后续标准sip协议中全部缺省 故不再列出

      0,                                        //crc校验                                                             47
      0,                                        //crc校验                                                             48
};

//soar中只使用了analogInputs 5 6 7 8
uint8 standard_io_info[] = {
      FIRST_HEAD,                               //Head_first                0
      SECOND_HEAD,                              //Head_second               1
      28,                                       //Len                       2
      IO_TYPE,                                  //IO_flag                   3

      0,                                        //意义不明的缺省占位                                          4
      0,                                        //若后续要删除在上位机要同步更改
      0,
      0,
      0,
      0,
      0,
      0,
      0,                                        //以上均为缺省占位                                              12

      0,                                        //analogInputs_0 低八位                     13
      0,                                        //analogInputs_0 高八位                     14

      0,                                        //analogInputs_1 低八位                     15
      0,                                        //analogInputs_1 高八位                     16

      0,                                        //analogInputs_2 低八位                     17
      0,                                        //analogInputs_2 高八位                     18

      0,                                        //analogInputs_3 低八位                     19
      0,                                        //analogInputs_3 高八位                     20

      0,                                        //analogInputs_4 低八位                     21
      0,                                        //analogInputs_4 高八位                     22

      0,                                        //analogInputs_5 低八位                     23
      0,                                        //analogInputs_5 高八位                     24

      0,                                        //analogInputs_6 低八位                     25
      0,                                        //analogInputs_6 高八位                     26

      0,                                        //analogInputs_7 低八位                     27
      0,                                        //analogInputs_7 高八位                     28

      0,                                        //crc校验                                                             29
      0,                                        //crc校验                                                             30
};
