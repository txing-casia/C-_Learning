class Role_Player
{
public:
    double HP = 100.0;
    double HP_max = 100.0;
    double ATK = 10.0;
    double EXP = 0.0;
    double EXP_max = 10.0;

    int buff_room_normal_time = 0;
    int buff_room_trap_time = 0;

    int player_arm_index = 0;  // [0,1,2,3]
    double ex_ATK = 0.;
    int arm_time = 0;
    double rate_forever_ATK_double = 2.;

    void player_arm(int index)
    {
        player_arm_index = index;
        if(index == 1){
            ex_ATK = 4.0;
            arm_time = 6;
        }else if(index == 2){
            ex_ATK = 6.;
            arm_time = 6;
        }else if(index == 3){
            ex_ATK = 1.;
            arm_time = 6;
            rate_forever_ATK_double = 0.5;
        }else{
            player_arm_index = 0;
            ex_ATK = 0.;
            arm_time = 0;
            rate_forever_ATK_double = 2.;
        }
    }

};

class Role_Monster
{
public:
    Role_Monster(double room_buff)
    {
        HP = 10.0 * (1 + room_buff);
        HP_max = 10.0 * (1 + room_buff);
        ATK = 5.0 * (1 + room_buff);
    }

    double HP = 10.0;
    double HP_max = 10.0;
    double ATK = 5.0;
};

class Role_Monster_King
{
public:
    // Role_Monster_King(double room_buff)
    // {
    //     HP = 10.0 * (1 + room_buff);
    //     HP_max = 10.0 * (1 + room_buff);
    //     ATK = 5.0 * (1 + room_buff);
    // }
    double HP = 40.0;
    double HP_max = 40.0;
    double ATK = 15.0;
};

class Role_Monster_with_arm
{
public:
    Role_Monster_with_arm(double player_HP, double player_HP_max, double player_ATK)
    {
        HP = player_HP * (0 + 0.4);
        HP_max = player_HP_max * (0 + 0.4);
        ATK = player_ATK * (0 + 0.4);
    }
    double HP;
    double HP_max;
    double ATK;

    int monster_arm_index = 0;  // [0,1,2,3]
    double ex_ATK = 0.;
    int arm_time = 0;
    double rate_forever_ATK_double = 2.;

    void monster_arm(int index)
    {
        monster_arm_index = index;
        if(index == 1){
            ex_ATK = 4.0;
            arm_time = 6;
        }else if(index == 2){
            ex_ATK = 6.;
            arm_time = 6;
        }else if(index == 3){
            ex_ATK = 1.;
            arm_time = 6;
            rate_forever_ATK_double = 0.5;
        }else{
            monster_arm_index = 0;
            ex_ATK = 0.;
            arm_time = 0;
            rate_forever_ATK_double = 2.;
        }
    }
};
