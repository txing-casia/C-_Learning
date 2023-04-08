// 营地
class Room_base
{
public:
    double rate_show = 0.10;  // 10%概率出现
    double change_HP = 100.0;  // +100HP
    double change_HP_showrate = 1.0;  //回复HP的概率
    double buff_HP = 0.0; // 进一个房间+0生命值
    int buff_last_time = 0;  // buff持续时间
};

// 普通房间
class Room_normal
{
public:
    double rate_show = 0.55;  // 55%概率出现
    double change_HP = 10.0;  // +10HP
    double change_HP_showrate = 0.1;  //回复HP的概率
    double buff_HP = 5.0; // 进一个房间+5生命值
    int buff_last_time = 2;  // buff持续时间

    int master_num_max = 3;
    double master_buff_max = 0.4;

};

// 陷阱房间
class Room_trap
{
public:
    double rate_show = 0.15;  // 15%概率出现
    double change_HP_rate = -0.1;  // 掉血百分比模式
    double change_HP_showrate = 1.0;
    double buff_HP = -2.0; // 进一个房间+5生命值
    int buff_last_time = 5;
};

// BOSS房间
class Room_kingroom
{
public:
    double rate_show = 0.10;  // 10%概率出现
    double change_HP = 20.0;  // +20HP
    double change_HP_showrate = 1.0;
    double buff_HP = 0.0; // 进一个房间+5生命值
    int buff_last_time = 0;
    int flag_disable_dbuff = 1;  // 清除所有负面效果
};

class Room_arm
{
public:
    Room_arm(double HP)
    {
        // 记录当前生命值
        flag_curr_HP = HP;
    }
    double rate_show = 0.10;
    double flag_curr_HP;

};