#ifndef GLOBALCONST_H
#define GLOBALCONST_H

// 指示格子状态
enum enum_latticeStatus
{
    CLOSED,
    OPENED,
    FLAG,
    QUESTION,
    MINE_GAMEOVER
};

// 指示主题
enum enum_theme
{
    CLASSIC,
    DOG,
    PVZ
};

// 指示emoji的状态（笑脸或哭脸）
enum enum_emojiStatus
{
    SMILE,
    CRY
};

// 指示游戏结束状态（胜利或失败）
enum
{
    LOSE,
    WIN
};

const int SIDE_LENTH = 40; // 一个格子的边长/像素

#endif // GLOBALCONST_H
