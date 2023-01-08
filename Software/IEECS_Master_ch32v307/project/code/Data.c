/*
 * Data.c
 *
 *  Created on: Nov 10, 2022
 *      Author: Aimmecat
 */

#include "headfile.h"

//���ڽ���soar�����ָ��
uint8 sip_receive_info_One[RECEIVE_MAXLEN];
//uint8 sip_receive_info_Two[RECEIVE_MAXLEN];

uint8 voltage;


//��ע*��ʾsoarȱʡֵ �����۲����ޱ�Ҫ����soar�ж�Ӧɾ��
uint8 standard_sip_info[] = {
      FIRST_HEAD,                               //Head_first                0
      SECOND_HEAD,                              //Head_second               1
      46,                                       //Len                       2
      STOP_TYPE,                                //motors status             3
      0,                                        //xPos �Ͱ�λ                                                   4
      0,                                        //xPos �߰�λ                                                   5
      0,                                        //yPos �Ͱ�λ                                                   6
      0,                                        //yPos �߰�λ                                                   7
      0,                                        //thPos ---> angle �Ͱ�λ               8
      0,                                        //thPos ---> angle �߰�λ               9
      0,                                        //*l_vel �Ͱ�λ                                             10
      0,                                        //*l_vel �߰�λ                                             11
      0,                                        //*r_vel �Ͱ�λ                                             12
      0,                                        //*r_vel �߰�λ                                             13
      80,                                       //*Battery 80 ---> 8.0V     14
      0x00,                                     //stall and bumpers �Ͱ�λ            15
      0x00,                                     //stall and bumpers �߰�λ            16
      0,                                        //*setPointdegree diff �Ͱ�λ   17
      0,                                        //*setPointdegree diff �߰�λ   18
      0x00,                                     //*flags �Ͱ�λ                                             19
      0x00,                                     //*flags �߰�λ                                             20
      0,                                        //*Electronic compass       21
      8,                                        //new sonar reading         22

      0,                                        //sonar_0 ��־��                                          23
      1,                                        //sonar_0 �Ͱ�λ                                          24
      0,                                        //sonar_0 �߰�λ                                          25

      1,                                        //sonar_1 ��־��                                          26
      1,                                        //sonar_1 �Ͱ�λ                                          27
      0,                                        //sonar_1 �߰�λ                                          28

      2,                                        //sonar_2 ��־��                                          29
      1,                                        //sonar_2 �Ͱ�λ                                          30
      0,                                        //sonar_2 �߰�λ                                          31

      3,                                        //sonar_3 ��־��                                          32
      1,                                        //sonar_3 �Ͱ�λ                                          33
      0,                                        //sonar_3 �߰�λ                                          34

      4,                                        //sonar_4 ��־��                                          35
      1,                                        //sonar_4 �Ͱ�λ                                          36
      0,                                        //sonar_4 �߰�λ                                          37

      5,                                        //sonar_5 ��־��                                          38
      1,                                        //sonar_5 �Ͱ�λ                                          39
      0,                                        //sonar_5 �߰�λ                                          40

      6,                                        //sonar_6 ��־��                                          41
      1,                                        //sonar_6 �Ͱ�λ                                          42
      0,                                        //sonar_6 �߰�λ                                          43

      7,                                        //sonar_7 ��־��                                          44
      1,                                        //sonar_7 �Ͱ�λ                                          45
      0,                                        //sonar_7 �߰�λ                                          46

      //������׼sipЭ����ȫ��ȱʡ �ʲ����г�

      0,                                        //crcУ��                                                             47
      0,                                        //crcУ��                                                             48
};

//soar��ֻʹ����analogInputs 5 6 7 8
uint8 standard_io_info[] = {
      FIRST_HEAD,                               //Head_first                0
      SECOND_HEAD,                              //Head_second               1
      28,                                       //Len                       2
      IO_TYPE,                                  //IO_flag                   3

      0,                                        //���岻����ȱʡռλ                                          4
      0,                                        //������Ҫɾ������λ��Ҫͬ������
      0,
      0,
      0,
      0,
      0,
      0,
      0,                                        //���Ͼ�Ϊȱʡռλ                                              12

      0,                                        //analogInputs_0 �Ͱ�λ                     13
      0,                                        //analogInputs_0 �߰�λ                     14

      0,                                        //analogInputs_1 �Ͱ�λ                     15
      0,                                        //analogInputs_1 �߰�λ                     16

      0,                                        //analogInputs_2 �Ͱ�λ                     17
      0,                                        //analogInputs_2 �߰�λ                     18

      0,                                        //analogInputs_3 �Ͱ�λ                     19
      0,                                        //analogInputs_3 �߰�λ                     20

      0,                                        //analogInputs_4 �Ͱ�λ                     21
      0,                                        //analogInputs_4 �߰�λ                     22

      0,                                        //analogInputs_5 �Ͱ�λ                     23
      0,                                        //analogInputs_5 �߰�λ                     24

      0,                                        //analogInputs_6 �Ͱ�λ                     25
      0,                                        //analogInputs_6 �߰�λ                     26

      0,                                        //analogInputs_7 �Ͱ�λ                     27
      0,                                        //analogInputs_7 �߰�λ                     28

      0,                                        //crcУ��                                                             29
      0,                                        //crcУ��                                                             30
};
