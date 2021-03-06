//
// Created by musta on 11.04.2016.
//

#ifndef HMM_THE_GAME_H
#define HMM_THE_GAME_H

//#include "map.h"

class the_game // ��������� �� 2-� ������� ������ ����� ����������.
    // ����� �� ����� ���������� ������,
    // ���������, ������ ��� ������� ���� ������� ������
    // �� ��� ��� ���� ���� �� ������ �� ���������� �� ���������� �����
{
private:
    vector<creature *> game_creature_Mas; // ������ ������� �� ���� ���
    int game_creature_Mas_Count;

    SDL_Texture * bg = NULL; // �������� ���������
    SDL_Texture * net = NULL; // �������� ���������
    SDL_Texture * console = NULL; // �������� �������
    SDL_Texture * step = NULL; // �������� �������
    SDL_Texture * hp = NULL; // �������� ���������
    SDL_Texture * bgframe = NULL; // �������� ���������
    SDL_Texture * player_bg = NULL; // �������� ���������

    string logs_memory = " "; // �������� ������ �����

    void make_game_mass(player &gamer1, player &gamer2) // ���������� ������� ����������
    {
        int i;
        for (i = 0; i < min(gamer1.count_of_creatures(), gamer2.count_of_creatures()); ++i) {
            game_creature_Mas.push_back(gamer1.creatureMass[i]);
            game_creature_Mas.push_back(gamer2.creatureMass[i]);
        }
//        cout << "i = " << i << endl;
        for (int j = i; j < max(gamer1.count_of_creatures(), gamer2.count_of_creatures()); ++j) {
            if (gamer1.count_of_creatures() > gamer2.count_of_creatures()) {
                game_creature_Mas.push_back(gamer1.creatureMass[j]);
            } else {
                game_creature_Mas.push_back(gamer2.creatureMass[j]);
            }
        }
    }

    bool is_this_creature_of_this_game(unsigned int creature_id) { // ��������� ���������� �� �������� � ����� id � ����
        for (int i = 0; i < game_creature_Mas_Count; ++i) {
            if (game_creature_Mas[i]->get_id() == creature_id) {
                return true;
            }
        }
        return false;
    }

    creature *return_creature_by_id(unsigned int creature_id) {
        for (int i = 0; i < game_creature_Mas_Count; ++i) {
            if (game_creature_Mas[i]->get_id() == creature_id) {
                return game_creature_Mas[i];
            }
        }
        return NULL;
    }

public:

    void print_steps(SDL_Texture * step, creature* active_creature) // ��������� ��������� �����
    {
        for (int i = 0; i < width; i++)
           {
               for (int j = 0; j < height; j++)
               {
                    if(active_creature->can_creature_move_to_point(j,i) && map::is_this_point_empty(j,i) != 0)
                    {
                        ApplySurface(i*85,j*95+116,step,renderer);
                    }
               };
           };
    }

    void print_map(SDL_Texture * bg, SDL_Texture * net, SDL_Texture * player_bg, SDL_Texture * step) {
        // cout << setfill(' ') << setw(3)  << "x/y ";
        // for (int k = 0; k < width; ++k) {
        //     cout << setfill(' ') << setw(2) << k << " ";
        // }
        // cout << endl;
        // cout << endl;
        // for (int i = 0; i < height; ++i) {
        //     cout << setfill(' ') << setw(1) << i << "   ";
        //     for (int j = 0; j < width; ++j) {
        //         cout << setfill(' ') << setw(2) << map_of_id[i][j] << " ";
        //     }
        //     cout << endl;
        // }
SDL_RenderClear(renderer);
//cout << player_bg << endl;
ApplySurface(0,0,bg,renderer); // ��������� ����
ApplySurface(0,116,net,renderer); // ��������� �����
ApplySurface(0,591,console,renderer); // ��������� �������
Print_Font(gFont, textColor, logs ,70,591+10, 15); // ����
ApplySurface(10,10,player_bg,renderer,1); // ���� ������� ������
ApplySurface(SCREEN_WIDTH-85-10,10,player_bg,renderer,2); // ���� ������� ������




for (int i = 0;i < game_creature_Mas_Count ;i++ )
{
    if (game_creature_Mas[i]->alive)
    {
        //int a = game_creature_Mas[i]->count_hp;
        //char *intStr = itoa(a);
        //string count_hp_str = string(intStr);

        //cout << i << " = "<< game_creature_Mas[i]->count_hp << endl;



        if(game_creature_Mas[i]->is_it_active)
            {
                ApplySurface(game_creature_Mas[i]->y0*85,game_creature_Mas[i]->x0*95+116,bgframe,renderer);      // ������� ��������� ���������
                print_steps(step, game_creature_Mas[i]);
            }
        ApplySurface(game_creature_Mas[i]->y0*85 ,game_creature_Mas[i]->x0*95+116,game_creature_Mas[i]->skin,renderer, game_creature_Mas[i]->belong_to); // ��������� ���������
        Print_Font(gFont, textColor, intToStr(game_creature_Mas[i]->ID),game_creature_Mas[i]->y0*85+5, game_creature_Mas[i]->x0*95+116+5, 15 ); // ID
        ApplySurface(game_creature_Mas[i]->y0*85+41 ,game_creature_Mas[i]->x0*95+116+76,hp,renderer); // hp bg
        Print_Font(gFont, textColor, intToStr(game_creature_Mas[i]->health),game_creature_Mas[i]->y0*85+41+15, game_creature_Mas[i]->x0*95+116+76+2, 10 ); // ���������� hp
    }
}

/*show_damage(int x, int y, creature another)
{
    for (int i = 0;i < game_creature_Mas_Count ;i++ )
    {
        if (game_creature_Mas[i]->alive && (game_creature_Mas[i]->belong_to != another->belong_to))
        {
            Print_Font(gFont, textColor, health_str ,game_creature_Mas[i]->y0*85+41+15, game_creature_Mas[i]->x0*95+116+76+2, 10 );
        }
    }
}*/

//ApplySurface(rand() % 300,rand() % 300,game_creature_Mas[0]->skin,renderer);
SDL_RenderPresent(renderer); // ������ ������������ ������
SDL_Delay(100);


    }

    the_game(player &gamer1, player &gamer2) //
    {
        make_game_mass(gamer1, gamer2);
        game_creature_Mas_Count = game_creature_Mas.size();
        bg = LoadImage("field2.png");
        if (bg == NULL)
            cout << "bg not found " << endl;
        bgframe = LoadImage("frame.png");
        if (bgframe == NULL)
            cout << "bgframe not found " << endl;
        hp = LoadImage("hp1.png");
        if (hp == NULL)
            cout << "hp not found " << endl;
        net = LoadImage("net.png");
        if (net == NULL)
            cout << "net not found " << endl;
        console = LoadImage("console.png");
        if (console == NULL)
            cout << "console not found " << endl;
        step = LoadImage("step.png");
        if (step == NULL)
            cout << "step not found " << endl;
        player_bg = LoadImage("player_bg.png");
        cout << "player_bg" <<  player_bg << endl;
        if (player_bg == NULL)
            cout << "player_bg not found " << endl;
        //Initialize PNG loading

        int imgFlags = IMG_INIT_PNG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            cout <<  "SDL_image could not initialize! SDL_image Error: %s\n" <<  IMG_GetError() << endl;
            //success = false;
        }

         //Initialize SDL_ttf
        if( TTF_Init() == -1 )
        {
            cout <<  "SDL_ttf could not initialize! SDL_ttf Error: %s\n" <<  TTF_GetError() << endl;
           // success = false;
        }
    }

    bool start(player &gamer1, player &gamer2, SDL_Renderer *GAMErenderer) {

        cout << "POSHUMIM BLEAT!!!" << endl;
        cout << "GAME START" << endl;
        int i = 0;
        int inp_x;
        int inp_y;
        bool is_it_enemy; // true: ����� �������. false: ������ �������

        int tmp_x; // �������, � ������� ����� ������� ���������
        int tmp_y;

        int check; // ��������
        bool ext = true;

        SDL_Event ev;
        logs = " ";

        const Uint8* keyState;

//        bool is_point_empty; // true: ������ ������. false: �� ������

        creature *tmp_creature; // ����� ��������� ���������

        while (gamer1.count_of_creatures() > 0 &&
               gamer2.count_of_creatures() > 0 &&  // ���� ���� �� ��� ��� ���� � ����� ���������� ���� ����� ������
                ext)
        {
            if (game_creature_Mas[i]->alive) // ��� ������ ������ ����� ����������
            {
                logs_memory = logs;
                game_creature_Mas[i]->is_it_active = true; // ������ ��������� ��������
                cout << endl;
                cout << "RACE:" << game_creature_Mas[i]->race << ";  ID:" << game_creature_Mas[i]->ID << endl;
                cout << "path length of creature:" << game_creature_Mas[i]->path_length << endl;

                string text = "";
                SDL_StartTextInput();
                do {
                    repeat_input:;
                    check = 1;


                    while (SDL_PollEvent(&ev) != 0) // ����� ���������� ��������� ����� �� ����������
                    {
                        if (ev.type == SDL_QUIT) // �������� ����
                        {
                            ext = false;
                            return 0;
                        }else if(ev.type == SDL_TEXTINPUT || ev.type == SDL_KEYDOWN) // ���� ������ ��� ������ ������� �������
                        {
                            system("cls");
                            if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_BACKSPACE && text.length() > 0)
                                text = text.substr(0, text.length() - 1);
                            else if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN)
                                {
                                    text = "";
                                    check = -1;
                                    goto try_to_do_step;
                                }
                            else if(ev.type == SDL_TEXTINPUT)
                                text += ev.text.text;


                            cout << text << endl;
                        }
                        if (ev.type == SDL_MOUSEBUTTONDOWN) // ������� ������ ����
                        {
                            if(ev.button.button == SDL_BUTTON_LEFT) // ��������� ������ �����
                            {
                                if(ev.button.y >= 116 && ev.button.y <= 591) // ������� �� ���� ���
                                {
                                   inp_y = ev.button.x / 85;
                                    inp_x = (ev.button.y - 116) / 95;
                                    cout << "LEFT BUTTON PRESSED! at x: " << ev.button.x  << " y: " << ev.button.y << endl;
                                    cout << "inp_x: " << inp_x  << " inp_y: " << inp_y << endl;
                                    goto try_to_do_step;
                                }else if (ev.button.y >= 591 && ev.button.y <= 591 + 40) // ������ ������
                                    {
                                        if(ev.button.x >= 781 && ev.button.x <= 850) // ������� ����
                                        {
                                            check = -1;
                                            goto try_to_do_step;
                                        }
                                    };
                            }
                        }else if(ev.type == SDL_MOUSEMOTION)
                        {
                            if(ev.motion.y >= 116 && ev.motion.y <= 591) // ��������� �� ���� ��� �� ���� ���
                            {
                               inp_y = ev.button.x / 85;
                                inp_x = (ev.button.y - 116) / 95;
                                unsigned int tmp_id;
                                //cout << "id of it creature = " << map::get_creature_ID(inp_x,inp_y) << endl;
                                tmp_id = map::get_creature_ID(inp_x,inp_y);
                                tmp_creature = return_creature_by_id(tmp_id);

                                if(tmp_creature != NULL)
                                {
                                    logs = tmp_creature->race + ". ";
                                    if(tmp_creature->damage != 0)
                                    {
                                        logs += "DAMAGE: " + intToStr(tmp_creature->damage) + " - " + intToStr(tmp_creature->damage_max) + ". "; // ����� ���� �����
                                    }
                                    if(tmp_creature->count_hp != 0)
                                    {
                                        logs += "ADD HP: " + intToStr(tmp_creature->count_hp) + " - " + intToStr(tmp_creature->count_hp_max) + ". ";
                                    }
                                    if(tmp_creature-> arrow_damage != 0)
                                    {
                                        logs += "ARROW DAMAGE: " + intToStr(tmp_creature->arrow_damage) + " - " + intToStr(tmp_creature->arrow_damage_max) + ". ";
                                    }
                                    logs += "DEFENSE: " + intToStr(tmp_creature->defense) + ". ";

                                }else logs = logs_memory;
                                //goto try_to_do_step;
                            }
                        }
                    }

                    keyState = SDL_GetKeyboardState(NULL);



                    print_map(bg, net, player_bg, step);
                    goto repeat_input;

                    try_to_do_step:;

                    if (check == 0) // ���� ���������� ������� �����������
                    {
                        cout << "ERROR: this position is't on the map" << endl;
                        goto repeat_input;
                    }
                    if (check == -1) // ���� ����� ����� ���������� ���
                    {
                        cout << "You missed your turn" << endl;
                        logs = game_creature_Mas[i]->race + " missed it's turn.";
                        break;
                    }



                    if (!(map::is_this_point_empty(inp_x, inp_y))) // ���� ������ ��������
                    {
//                        is_point_empty = false; // ������ ��������
                        tmp_creature = return_creature_by_id(
                                map::get_id_of_point(inp_x, inp_y)); // ������� ����� ��������� �� ��������� ������
                        if (game_creature_Mas[i]->belong_to ==
                            tmp_creature->belong_to)          // ���� ��� ����
                        {
                            if (game_creature_Mas[i]->add_hp(
                                    tmp_creature)) // ���� ���� �������� ����� ��������������� ��������
                            {
                                cout << "ATTACK: I add hp to " << tmp_creature->ID << endl;
                            } else {
                                cout << "ERROR: this creature is your friend" << endl;
                                goto repeat_input;
                            }
                        } else {
                            if (game_creature_Mas[i]->arrow_attack(tmp_creature)) // ���� ���� �������� ����� ��������
                            {
                                cout << "ATTACK: I shot a " << tmp_creature->ID << endl;
                            } else // ���������� ������� � ����
                            {
                                if (!(game_creature_Mas[i]->can_creature_move_to_point(inp_x,
                                                                                       inp_y)))// ��������� � ���� ������������ �� ��������� ����������
                                {
                                    cout << "ERROR: this creature can't move so far" << endl;
                                    goto repeat_input;
                                } else // ���� �������� � ���� ������������
                                {
                                    if ((abs(game_creature_Mas[i]->x0 - inp_x) <= 1) &&
                                        (abs(game_creature_Mas[i]->y0 - inp_y)) <=
                                        1) // ��������� ��������� �� ��������� �������� ��� � ������� ����� ������
                                    {
                                        if (game_creature_Mas[i]->attack(
                                                tmp_creature)) // ����� �� ��� �������� ���������
                                        {
                                            cout << "attackHere = " << tmp_creature->get_id() <<
                                            endl; // ������� ������� ���������� ��������� � ������
                                        } else {
                                            cout << "ERROR: this creature can't attack" << endl;
                                            goto repeat_input;
                                        }
                                    } else {
                                        if (search_empty_point(game_creature_Mas[i], tmp_creature, tmp_x,
                                                               tmp_y)) // ��������� ����� �� ������� � �������� ��������
                                        {
                                            if (game_creature_Mas[i]->attack(
                                                    tmp_creature)) // ����� �� ��� �������� ���������
                                            {
                                                cout << "attackThere = " << tmp_creature->get_id() <<
                                                endl; // ������� ������� ���������� ��������� � ������
                                                game_creature_Mas[i]->move(tmp_x, tmp_y);
                                            } else {
                                                cout << "ERROR: this creature can't attack" << endl;
                                                goto repeat_input;
                                            }
                                        } else {
                                            cout << "ERROR: you can't attack this creature" << endl;
                                            goto repeat_input;
                                        }
                                    }
                                }
                            }
                        }

                    } else // ����� � ��� ����� ��������
                    {
                        if (
                                !(game_creature_Mas[i]->can_creature_move_to_point(inp_x,
                                                                                   inp_y)))// ��������� � ���� ������������ �� ��������� ����������
                        {
                            cout << "ERROR: this creature can't move so far" << endl;
                            goto repeat_input;
                        } else {
                            game_creature_Mas[i]->move(inp_x, inp_y);
                            logs = game_creature_Mas[i]->race + " went to: (" + intToStr(inp_x) + "," + intToStr(inp_y) + ")";
                        }
//                        is_point_empty = true; // ������ ������
                    }

                } while (false);
                SDL_StopTextInput();
                game_creature_Mas[i]->is_it_active = false; // ������ ��������� �� ��������
                i = (i + 1) % game_creature_Mas_Count;
            } else
            {
                game_creature_Mas[i]->is_it_active = false; // ������ ��������� �� ��������
                i = (i + 1) % game_creature_Mas_Count;
            }
            print_map(bg,net, player_bg, step);
        }
        int winnerNum; // number of winner player
        if(gamer1.count_of_creatures() > gamer2.count_of_creatures())
        {
            winnerNum = 1;
        }else
        {
            winnerNum = 2;
        }



        repeat_thank:;

        while (SDL_PollEvent(&ev) != 0)
        {
            if (ev.type == SDL_QUIT) // �������� ����
            {
                logs = " ";
            }
        }

        //SDL_RenderClear(renderer);
        logs = "The " + intToStr(winnerNum) + " player won the game. " + "Thank you for playing.";
        print_map(bg,net, player_bg,step);
        //Print_Font(gFont, textColor, "The " + winnerNum_str + " player won the game", 30 , 250, 40 );
        //Print_Font(gFont, textColor, "Thank you for playing", 30 , 350, 40 );

        SDL_RenderPresent(renderer); // ������ ������������ ������
        SDL_Delay(100);

        goto repeat_thank;
    }

    bool search_empty_point(creature *creature1, creature *creature2, int &x,
                            int &y) // ����� ��������� �����, ���� ����� ������ creature1, ����� ������� creature2. False: creature2 ������ �������
    {
        double distance = sqrt(width * width + height * height) + 10; // ���������� �� ���������
        bool found = false;                                   // �������� ������� �� ���� �� ���� ���������� ������
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if ((map_of_id[i][j] == 0) &&
                    // ������� ����� ������ ���� ������
                    (abs(creature1->x0 - i) < creature1->path_length) &&
                    // ������� ����� ������ ���� � ���� ����� creature1
                    (abs(creature1->y0 - j) < creature1->path_length) &&
                    (abs(creature2->x0 - i) <= 1) &&
                    // ������� ����� ������ ���� �������� � creature2
                    (abs(creature2->y0 - j) <= 1) &&
                    (creature1->distance_to_point(i, j) <
                     distance))               // ������� ����� ���������� �� ������ ���� ������ ��� � ���������� ������
                {
                    x = i;                                          // ��������� ����������
                    y = j;
                    cout << "new x = " << x << " new y = " << y << endl;
                    distance = creature1->distance_to_point(i, j);    // ��������� ����������
                    found = true;
                }
            }
        }
        return found;
    }


};

#endif //HMM_THE_GAME_H
