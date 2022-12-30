import serial#导入串口通信库
from time import sleep
from time import time

ser = serial.Serial()

def port_open_recv():#对串口的参数进行配置
    ser.port='com5'
    ser.baudrate=115200
    ser.bytesize=8
    ser.stopbits=1
    ser.parity="N"#奇偶校验位
    ser.open()
    if(ser.isOpen()):#isOpen()函数来查看串口的开闭状态
        print("串口打开成功！")
    else:
        print("串口打开失败！")

def port_close():
    ser.close()
    if(ser.isOpen()):
        print("串口关闭失败！")
    else:
        print("串口关闭成功！")

def send(send_data):
    if(ser.isOpen()):
        ser.write(send_data.encode('utf-8'))#编码
        print("发送成功",send_data)
    else:
        print("发送失败！")

def sendPacket(data):
    pkt = [0xFA,0xFB,len(data)+2]
    for d in data:
      pkt.append(d)
    pkt.append(0)
    pkt.append(0)
    chk = calcChecksum(pkt)
    pkt[len(pkt)-2] = (chk >> 8)
    pkt[len(pkt)-1] = (chk & 0xFF)
    s = Get_Bytes_Str(pkt)
    print(s)
    try:
      ser.write(s)
    except:
      sys.stderr.write("Could not write to serials port.  Is robot turned on and connected?\n")
    sleep(0.008)

def Get_Hex_To_Char(dec):
    hex_str = hex(dec)[2:]
    if len(hex_str) == 1:
      hex_str = '0' + hex_str
    return hex_str

def Get_Bytes_Str(pkt_list):
    trans_str = ""
    for index in range(len(pkt_list)):
      hex_str = Get_Hex_To_Char(pkt_list[index])
      trans_str += hex_str
      if index != len(pkt_list) - 1:
        trans_str += ' '
    return bytes.fromhex(trans_str)

def calcChecksum(data):
    c = 0
    i = 3
    n = data[2]-2
    while n > 1:
      c += (data[i]<<8) | (data[i+1])
      c = c & 0xFFFF
      n -= 2
      i += 2
    if n > 0:
      c = c ^ data[i]
    return c

def recvPacket():
    timeout = 5.0
    data = [0,0,0]
    while True:
      tstart = time()
      while (time()-tstart) < timeout:
        if ser.inWaiting() > 0:
          data[2] = ord(ser.read())
          break
      if (time()-tstart) > timeout:
        raise Exception("Read timeout")
      if data[0] == 0xFA and data[1] == 0xFB:
        break

      data[0] = data[1]
      data[1] = data[2]

    for d in range(data[2]):
      data.append(ord(ser.read()))

    crc = calcChecksum(data)
    if data[len(data)-1] != (crc & 0xFF) or data[len(data)-2] != (crc >> 8):
      ser.flushInput()
      raise Exception("Checksum failure")
    return data



if __name__ == '__main__':
    port_open_recv()
    while True:
        dat = input("inputs:")
        sendPacket([int(dat)])
        receive_dat = recvPacket()
        print(receive_dat)
