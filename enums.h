/**************************************************************************
文件名：enums.h
功能模块和目的：建立一些枚举型变量
开发者：程晔安
日期：7/26
版权信息：Copyright 2018 by Yean Cheng .All rights reserved.
更改记录：7/26最后更改
**************************************************************************/
#ifndef ENUMS_H
#define ENUMS_H
enum RoomType{CLOCK, BIGBED, TWOBED, EXPENSIVE, PRESIDENT
        };
//房间的种类：钟点房、大床房、双人房、奢华房、总统套房
enum QuestState{ BOOKED, PAIED, REFUND, INROOM, CHECKOUT, COMMENTED};
//订单的状态：已预定、已交款、退款、入住、退房、已评论

#endif // ENUMS_H
