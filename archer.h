//
// Created by anton on 09.04.16.
//

#ifndef HMM_ARCHER_H
#define HMM_ARCHER_H


class archer : public virtual creature {
private:
    int arrow_damage; // урон от стрел
public:

    friend class skeleton_archer;

    friend class elf;

    virtual bool arrow_attack(
            creature *attacked_creature) {  // возможность стрелять из лука. это существо может стрелять
        if (attacked_creature->alive) {
            //cout << "I arrow_attack " << attacked_creature->ID << endl;
            attacked_creature->get_damage(arrow_damage); // наносит врагу урон стрелой.
        }
        return true;
    }

};


#endif //HMM_ARCHER_H
