#pragma once
typedef struct  tagStep { //����һ��������ݽṹ
    int x;
    int y;
    int color;
} STEP;

typedef struct tagMsgStruct {
    // ��ϢID
    UINT uMsg;
    // ������Ϣ
    int x;
    int y;
    int color;
    // ��Ϣ����
    TCHAR szMsg[128];
} MSGSTRUCT;

// ������Ϣ
#define MSG_DROPDOWN     0x00000001