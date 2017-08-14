#!/usr/bin/env python3
# -*- coding: utf-8 -*-

###################################################
#
# Description: asr parser and mqtt clinet
#
# Author:      ninja
#
# Date:        created by 2017-08-14
#
###################################################

import socket
import jieba
import paho.mqtt.client as mqtt

def getToken(msg):
    seg_list = jieba.cut(msg, cut_all=False)
    count = 0
    token = []
    print(type(seg_list))
    for n in seg_list:
        print("token ", count, ": ", n)
        count += 1
        token.append(n)
    return token

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind(('localhost', 6666))
    sock.listen(5)
    print("start listening...")

    mqttc = mqtt.Client("python3_pub")
    mqttc.connect("192.168.3.121", 1883)
    mqttc.loop_start()

    while True:
        connection, address = sock.accept()
        buf = str(connection.recv(4096), encoding="utf8")
        print(buf)
        tokenList = getToken(buf)
        print("token len: %d" % (tokenList.__len__()))
        print(tokenList[0])
        mqttc.publish("switch", tokenList[0])
        mqttc.publish("switch", tokenList[1])

    connection.close()
