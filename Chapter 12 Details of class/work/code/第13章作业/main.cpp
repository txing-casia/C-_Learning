#include <iostream>
#include <ctime>
#include <algorithm>
#include <unistd.h>
#include "roles.h"
#include "rooms.h"
using namespace std;

void fight_monster(Role_Player* player, Role_Monster_with_arm* monster_A);
void fight_monster(Role_Player* player, Role_Monster_King* monster_A);
void fight_monster(Role_Player* player, Role_Monster* monster_A);
void fight_monster(Role_Player* player, Role_Monster* monster_A, Role_Monster* monster_B);
void fight_monster(Role_Player* player, Role_Monster* monster_A,
                   Role_Monster* monster_B, Role_Monster* monster_C);

void player_use_arm(Role_Player* player, Role_Monster* monster_A);
void player_use_arm(Role_Player* player, Role_Monster_King* monster_A);
void player_use_arm(Role_Player* player, Role_Monster_with_arm* monster_A);
void monster_use_arm(Role_Monster_with_arm* player, Role_Player* monster_A);

int num_base_room = 0;
int num_normal_room = 0;
int num_trap_room = 0;
int num_king_room = 0;
int num_arm_room = 0;

// 进入事件 → 死亡判定 → 战斗事件 → 死亡判定 → 结算
int main()
{
    srand((int)time(0)); // set random seed
    // rand()%(b-a)+a ==> [a,b) rand()%(bound[1]-bound[0]+1)+bound[0];
    // rand()%(b-a+1)+a ==> [a,b]

    int i = 0;  // 遇到房间的个数
    int bound[2] = {0, 100}; // 生成随机数边界[a,b]

    Role_Player player;
    Role_Monster monster(0.);
    Role_Monster_King monster_king;

    Room_base room_base;
    Room_normal room_normal;
    Room_trap room_trap;
    Room_kingroom room_kingroom;
    Room_arm room_arm(0);

    player.player_arm(0);  // 初始化武器状态

    double room_type_curr;
    try
    {
        while (true)
        {
            cout << "--- Round: " << ++i << " ---" << endl;
            cout << "Player State: HP: " << player.HP << ", Arm: " << player.player_arm_index << endl;
            room_type_curr = (rand()%(bound[1]-bound[0]+1)+bound[0])/double(bound[1]);  // [0,1]
            int flag_monster_num = 0;
            //---进入事件---
            if (room_type_curr <= room_base.rate_show)
            {
                // 进入营地
                num_base_room ++;

                // 房间持续性buff结算
                if(player.buff_room_normal_time != 0){
                    player.HP += room_normal.buff_HP;
                    player.buff_room_normal_time -= 1;
                    if(player.HP > player.HP_max){
                        player.HP = player.HP_max;
                    }
                }
                if(player.buff_room_trap_time != 0){
                    player.HP += room_trap.buff_HP;
                    player.buff_room_trap_time -= 1;
                    if(player.HP <= 0.){
                        cout << "You died in Base room!" << endl;
                        break;
                    }
                }
                player.HP = player.HP_max;

                cout << "Base Room: Player HP up to MAX!" << endl;
                sleep(1);
            }
            else if(room_type_curr <= room_normal.rate_show
                                     + room_base.rate_show)
            {
                // 进入普通房间
                num_normal_room ++;

                // 房间持续性buff结算
                if(player.buff_room_normal_time != 0){
                    player.HP += room_normal.buff_HP;
                    player.buff_room_normal_time -= 1;
                    if(player.HP > player.HP_max){
                        player.HP = player.HP_max;
                    }
                }
                if(player.buff_room_trap_time != 0){
                    player.HP += room_trap.buff_HP;
                    player.buff_room_trap_time -= 1;
                    if(player.HP <= 0.)
                    {
                        cout << "You died in Normal room!" << endl;
                        break;
                    }
                }

                // 当前房间效果
                player.buff_room_normal_time = room_normal.buff_last_time;
                if((rand()%(bound[1]-bound[0]+1)+bound[0])/double(bound[1]) < room_normal.change_HP_showrate)
                {
                    player.HP += room_normal.change_HP;  // 0.1概率HP+10
                    player.buff_room_normal_time = 2;
                    if(player.HP > player.HP_max){
                        player.HP = player.HP_max;
                    }
                }

                flag_monster_num = rand() % (room_normal.master_num_max) + 1;
                if(flag_monster_num == 1)
                {
                    // [-room_normal.master_buff_max, room_normal.master_buff_max]
                    double flag_room_buff_A = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                                    / double(100)) - room_normal.master_buff_max;
                    Role_Monster monster_A(flag_room_buff_A);
                    cout << "Monster ATK: " << monster_A.ATK << endl;
                    fight_monster(&player, &monster_A);
                }
                else if(flag_monster_num == 2)
                {
                    double flag_room_buff[2] = {0., 0.};
                    flag_room_buff[0] = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                              / double(100)) - room_normal.master_buff_max;
                    flag_room_buff[1] = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                              / double(100)) - room_normal.master_buff_max;
                    sort(flag_room_buff, flag_room_buff + 2);

                    Role_Monster monster_A(flag_room_buff[1]);
                    Role_Monster monster_B(flag_room_buff[0]);
                    cout << "Monster ATK: " << monster_A.ATK << ", " << monster_B.ATK << endl;
                    fight_monster(&player, &monster_A, &monster_B);

                }
                else if(flag_monster_num == 3)
                {
                    double flag_room_buff[3] = {0., 0., 0.};
                    flag_room_buff[0] = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                        / double(100)) - room_normal.master_buff_max;
                    flag_room_buff[1] = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                        / double(100)) - room_normal.master_buff_max;
                    flag_room_buff[2] = ((rand() % int(room_normal.master_buff_max * 20 + 1))
                                        / double(100)) - room_normal.master_buff_max;
                    sort(flag_room_buff, flag_room_buff+3);

                    Role_Monster monster_A(flag_room_buff[2]),
                                 monster_B(flag_room_buff[1]),
                                 monster_C(flag_room_buff[0]);
                    cout << "Monster ATK: " << monster_A.ATK << ", " << monster_B.ATK << ", " << monster_C.ATK << endl;
                    fight_monster(&player, &monster_A, &monster_B, &monster_C);
                }

                if (player.HP <= 0.){
                    cout << "You died!!!"<< endl;
                    break;
                }

                // exp结算
                if(player.HP != 0. && (player.EXP_max - player.EXP) > 1. * flag_monster_num)
                {
                    player.EXP += 1. * flag_monster_num;
                }
                else if(player.HP != 0. && (player.EXP_max - player.EXP) <= 1. * flag_monster_num)
                {
                    player.HP = player.HP_max;  // 升级，满血
                    player.EXP += 1. * flag_monster_num;
                    player.EXP -= player.EXP_max;
                    cout << "Your LV. Up!!" << endl;
                }

                cout << "Normal Room: Player VS " << flag_monster_num << " x Monster" << endl;
                sleep(1);

            }
            else if(room_type_curr <= room_normal.rate_show
                                     + room_base.rate_show
                                     + room_trap.rate_show)
            {
                // 进入陷阱房间
                num_trap_room ++;

                // 房间持续性buff结算
                if(player.buff_room_normal_time != 0){
                    player.HP += room_normal.buff_HP;
                    player.buff_room_normal_time -= 1;
                    if(player.HP > player.HP_max){
                        player.HP = player.HP_max;
                    }
                }
                if(player.buff_room_trap_time != 0){
                    player.HP += room_trap.buff_HP;
                    player.buff_room_trap_time -= 1;
                    if(player.HP <= 0.){
                        cout << "You died in Trap room!" << endl;
                        break;
                    }
                }

                // 当前房间效果
                player.HP *= (1 + room_trap.change_HP_rate);
                player.buff_room_trap_time = room_trap.buff_last_time;

                flag_monster_num = 1;
                double flag_room_buff_A = 1.0;
                Role_Monster monster_A(flag_room_buff_A);
                cout << "Monster ATK: " << monster_A.ATK << endl;
                fight_monster(&player, &monster_A);

                if (player.HP <= 0.){
                    cout << "You died!!!"<< endl;
                    break;
                }

                // exp结算
                if(player.HP != 0. && (player.EXP_max - player.EXP) > 1. * flag_monster_num)
                {
                    player.EXP += 1. * flag_monster_num;
                }
                else if(player.HP != 0. && (player.EXP_max - player.EXP) <= 1. * flag_monster_num)
                {
                    player.HP = player.HP_max;  // 升级，满血
                    player.EXP += 1. * flag_monster_num;
                    player.EXP -= player.EXP_max;
                    cout << "Your LV. Up!!" << endl;
                }

                cout << "Trap Room: Player VS Monster" << endl;
                sleep(1);

            }else if(room_type_curr <= room_normal.rate_show
                                     + room_base.rate_show
                                     + room_trap.rate_show
                                     + room_kingroom.rate_show)
            {
                // 进入BOSS房间
                num_king_room ++;

                // 房间持续性buff结算
                player.buff_room_trap_time = 0;
                player.HP += 20.;
                if(player.buff_room_normal_time != 0){
                    player.HP += room_normal.buff_HP;
                    player.buff_room_normal_time -= 1;
                    if(player.HP > player.HP_max){
                        player.HP = player.HP_max;
                    }
                }

                flag_monster_num = 1;
                Role_Monster_King monster_king_A;
                cout << "Monster King ATK: " << monster_king_A.ATK << endl;
                fight_monster(&player, &monster_king_A);

                if (player.HP <= 0.){
                    cout << "You are killed by Monster King!"<< endl;
                    break;
                }

                // exp结算
                if(player.HP != 0. && (player.EXP_max - player.EXP) > 5. * flag_monster_num)
                {
                    player.EXP += 5. * flag_monster_num;
                }
                else if(player.HP != 0. && (player.EXP_max - player.EXP) <= 5. * flag_monster_num)
                {
                    player.HP = player.HP_max;  // 升级，满血
                    player.EXP += 5. * flag_monster_num;
                    player.EXP -= player.EXP_max;
                    cout << "Your LV. Up!!" << endl;
                }

                cout << "Boss Room: Player VS Monster(king)" << endl;
                sleep(1);

            }else
            {
                // 进入武器房间
                num_arm_room ++;

                // 记录当前生命值
                room_arm.flag_curr_HP = player.HP;

                int arm_index = rand() % 3 + 1;  // 1,2,3

                Role_Monster_with_arm monster_A(player.HP, player.HP_max, player.ATK);
                monster_A.monster_arm(arm_index);
                cout << "Monster with arm ATK: " << monster_A.ATK << ", Arm index: " << monster_A.monster_arm_index << endl;
                fight_monster(&player, &monster_A);

                if (player.HP <= 0.){
                    cout << "You are killed by Monster with arm!"<< endl;
                    break;
                }

                // exp结算
                if(player.HP != 0. && (player.EXP_max - player.EXP) > 2. * flag_monster_num)
                {
                    player.EXP += 2. * flag_monster_num;
                }
                else if(player.HP != 0. && (player.EXP_max - player.EXP) <= 2. * flag_monster_num)
                {
                    player.HP = player.HP_max;  // 升级，满血
                    player.EXP += 2. * flag_monster_num;
                    player.EXP -= player.EXP_max;
                    cout << "Your LV. Up!!" << endl;
                }

                // HP结算
                player.HP = room_arm.flag_curr_HP;

                // 武器结算
                player.player_arm(arm_index);

                cout << "Player VS Monster(arm), Obtain: Arm_" << arm_index << endl;
                sleep(1);
            }

            if (i > 500)
            {
                // throw;
                break;
            }
        }

        cout << "-------------------------------" << endl;
        cout << "You have entered " << num_base_room + num_normal_room +
                num_trap_room + num_king_room + num_arm_room << " rooms!!" << endl;
        cout << "Base room: " << num_base_room << endl;
        cout << "Normal room: " << num_normal_room << endl;
        cout << "Trap room: " << num_trap_room << endl;
        cout << "Boss room: " << num_king_room << endl;
        cout << "Arm room: " << num_arm_room << endl;
    }
    catch(...)
    {
        cout << "----Error!!!----";
    }

    return 0;
}


////////////////////////////////////////////
// 1个monster with arm
void fight_monster(Role_Player* player, Role_Monster_with_arm* monster_A)
{
    while (monster_A->HP > 0. && player->HP > 0.)
    {
        player_use_arm(player,monster_A);
        if(monster_A->HP == 0.)
        {
            cout << "Monster with arm is killed!" << endl;
            break;
        }
        // cout << "player HP: " << player->HP << endl;
        // cout << "arm time: " << monster_A->arm_time << "arm ex_ATK: " << monster_A->ex_ATK<<  endl;

        monster_use_arm(monster_A, player);
        if(player->HP == 0.)
        {
            // cout << "You are killed by Monster with arm (ATK: " << monster_A->ATK << ", Arm ATK: " << monster_A->ex_ATK << ")! " << endl;
            break;
        }
    }
}

// 1个monster king
void fight_monster(Role_Player* player, Role_Monster_King* monster_A)
{
    int flag_boss_giveup_atk = 0;
    while (monster_A->HP > 0. && player->HP > 0.)
    {
        player_use_arm(player, monster_A);

        if(monster_A->HP == 0.)
        {
            cout << "Monster King is killed!" << endl;
            break;
        }
        // boss特殊攻击模式
        monster_A->ATK += 1.;
        if(monster_A->HP <= 10. and flag_boss_giveup_atk == 0)
        {
            monster_A->HP += 20.;
            flag_boss_giveup_atk = 1;
        }else
        {
            player->HP = max(0., player->HP - monster_A->ATK);
        }

        if(player->HP == 0.)
        {
            // cout << "You are killed by Monster King (ATK: " << monster_A->ATK << ")! " << endl;
            break;
        }
    }
}

// 1个monster
void fight_monster(Role_Player* player, Role_Monster* monster_A)
{
    while (monster_A->HP > 0. && player->HP > 0.)
    {
        // if(player->player_arm_index == 0){
        //     monster_A->HP = max(0., monster_A->HP - player->ATK);
        // }else if(player->player_arm_index == 1){
        //     monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        //     player->arm_time -= 1;
        // }else if(player->player_arm_index == 2){
        //     monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        //     player->arm_time -= 1;
        //     player->ex_ATK = double(player->arm_time);
        // }else if(player->player_arm_index == 3){
        //     if((rand()%(100+1)+0)/double(100) > player->rate_forever_ATK_double){  // [0,1]
        //         player->ex_ATK *= 2;
        //     }
        //     monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        //     player->arm_time -= 1;
        // }
        // if(player->arm_time <= 0){
        //     player->player_arm(0);  // 武器报废
        // }
        player_use_arm(player, monster_A);

        if(monster_A->HP == 0.)
        {
            cout << "Monster is killed!" << endl;
            break;
        }
        player->HP = max(0., player->HP - monster_A->ATK);
        if(player->HP == 0.)
        {
            break;
        }
    }
}

// 2个monster
void fight_monster(Role_Player* player, Role_Monster* monster_A, Role_Monster* monster_B)
{
    while ((monster_A->HP > 0. || monster_B->HP > 0.) && player->HP > 0.)
    {
        if(monster_A->HP != 0.){
            // monster_A->HP = max(0., monster_A->HP - player->ATK);
            player_use_arm(player, monster_A);
            if(monster_A->HP <= 0.){
                cout << "Monster_A is killed!" << endl;
            }
        }else if(monster_B->HP != 0.){
            // monster_B->HP = max(0., monster_B->HP - player->ATK);
            player_use_arm(player, monster_B);
            if(monster_B->HP <= 0.){
                cout << "Monster_B is killed!" << endl;
            }
        }

        if(monster_A->HP == 0. && monster_B->HP == 0.){
            break;
        }

        if(monster_A->HP != 0.){
            player->HP = max(0., player->HP - monster_A->ATK);
            player->HP = max(0., player->HP - monster_B->ATK);
        }else{
            player->HP = max(0., player->HP - monster_B->ATK);
        }

        if(player->HP == 0.){
            break;
        }
    }
}

// 3个monster
void fight_monster(Role_Player* player, Role_Monster* monster_A,
                   Role_Monster* monster_B, Role_Monster* monster_C)
{
    while ((monster_A->HP > 0. || monster_B->HP > 0. || monster_C->HP > 0.) && player->HP > 0.)
    {
        if(monster_A->HP != 0.){
            player_use_arm(player, monster_A);
            if(monster_A->HP <= 0.){
                cout << "Monster_A is killed!" << endl;
            }
        }else if(monster_B->HP != 0.){
            player_use_arm(player, monster_B);
            if(monster_B->HP <= 0.){
                cout << "Monster_B is killed!" << endl;
            }
        }else if(monster_C->HP != 0.){
            player_use_arm(player, monster_C);
            if(monster_C->HP <= 0.){
                cout << "Monster_C is killed!" << endl;
            }
        }

        if(monster_A->HP == 0. && monster_B->HP == 0. && monster_C->HP == 0.){
            break;
        }

        if(monster_A->HP != 0.){
            player->HP = max(0., player->HP - monster_A->ATK);
            player->HP = max(0., player->HP - monster_B->ATK);
            player->HP = max(0., player->HP - monster_C->ATK);
        }else if(monster_B->HP != 0.)
        {
            player->HP = max(0., player->HP - monster_B->ATK);
            player->HP = max(0., player->HP - monster_C->ATK);
        }else{
            player->HP = max(0., player->HP - monster_C->ATK);
        }

        if(player->HP == 0.){
            break;
        }
    }
}


void player_use_arm(Role_Player* player, Role_Monster* monster_A)
{
    if(player->player_arm_index == 0){
        monster_A->HP = max(0., monster_A->HP - player->ATK);
    }else if(player->player_arm_index == 1){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }else if(player->player_arm_index == 2){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
        player->ex_ATK = double(player->arm_time);
    }else if(player->player_arm_index == 3){
        if((rand()%(100+1)+0)/double(100) > player->rate_forever_ATK_double){  // [0,1]
            player->ex_ATK *= 2;
        }
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }
    if(player->arm_time <= 0){
        player->player_arm(0);  // 武器报废
    }
}

void monster_use_arm(Role_Monster_with_arm* player, Role_Player* monster_A)
{
    if(player->monster_arm_index == 0){
        monster_A->HP = max(0., monster_A->HP - player->ATK);
    }else if(player->monster_arm_index == 1){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }else if(player->monster_arm_index == 2){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
        player->ex_ATK = double(player->arm_time);
    }else if(player->monster_arm_index == 3){
        if((rand()%(100+1)+0)/double(100) > player->rate_forever_ATK_double){  // [0,1]
            player->ex_ATK *= 2;
        }
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }
    if(player->arm_time <= 0){
        player->monster_arm(0);  // 武器报废
    }
}

// monster king
void player_use_arm(Role_Player* player, Role_Monster_King* monster_A)
{
    if(player->player_arm_index == 0){
        monster_A->HP = max(0., monster_A->HP - player->ATK);
    }else if(player->player_arm_index == 1){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }else if(player->player_arm_index == 2){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
        player->ex_ATK = double(player->arm_time);
    }else if(player->player_arm_index == 3){
        if((rand()%(100+1)+0)/double(100) > player->rate_forever_ATK_double){  // [0,1]
            player->ex_ATK *= 2;
        }
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }
    if(player->arm_time <= 0){
        player->player_arm(0);  // 武器报废
    }
}

// monster with arm
void player_use_arm(Role_Player* player, Role_Monster_with_arm* monster_A)
{
    if(player->player_arm_index == 0){
        monster_A->HP = max(0., monster_A->HP - player->ATK);
    }else if(player->player_arm_index == 1){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }else if(player->player_arm_index == 2){
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
        player->ex_ATK = double(player->arm_time);
    }else if(player->player_arm_index == 3){
        if((rand()%(100+1)+0)/double(100) > player->rate_forever_ATK_double){  // [0,1]
            player->ex_ATK *= 2;
        }
        monster_A->HP = max(0., monster_A->HP - player->ATK - player->ex_ATK);
        player->arm_time -= 1;
    }
    if(player->arm_time <= 0){
        player->player_arm(0);  // 武器报废
    }
}
