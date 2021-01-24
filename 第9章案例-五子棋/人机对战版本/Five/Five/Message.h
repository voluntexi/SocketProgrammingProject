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

// 落子消息
#define MSG_DROPDOWN     0x00000001