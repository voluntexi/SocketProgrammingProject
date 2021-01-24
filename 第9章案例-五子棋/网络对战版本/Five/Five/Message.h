#pragma once
typedef struct  tagStep { //定义一手棋的数据结构
    int x;
    int y;
    int color;
} STEP;

typedef struct tagMsgStruct {
    // 消息ID
    UINT uMsg;
    // 落子信息
    int x;
    int y;
    int color;
    // 消息内容
    TCHAR szMsg[128];
} MSGSTRUCT;

//定义各种消息
#define MSG_DROPDOWN    0x01 //落子
#define MSG_ROLLBACK    0x02 //悔棋
#define MSG_AGREEBACK   0x03 //同意悔棋
#define MSG_REFUSEDBACK 0x04 //拒绝悔棋
#define MSG_DRAW		  0x05 //和棋
#define MSG_AGREEDRAW  0x06 //同意和棋
#define MSG_REFUSEDRAW 0x07 //拒绝和棋
#define MSG_GIVEUP     0x08 //认输
#define MSG_CHAT       0x09 //聊天
#define MSG_OPPOSITE   0x0a //对手信息
#define MSG_PLAYAGAIN   0x0b //再次开局
#define MSG_AGREEAGAIN  0x0c //同意再次开局