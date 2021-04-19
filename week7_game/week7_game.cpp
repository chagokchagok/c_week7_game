#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
SceneID scene_Start, scene_Cave, scene_Upgrade, scene_Armor, scene_Avengers_Facility, scene_Avengers_Recruit, scene_Villain;
ObjectID icon_Start, icon_Support, icon_Upgrade, icon_Back, icon_Avengers_Facility, icon_Recruit, icon_Test, icon_Boss_Stage, icon_Attack;
ObjectID icon_Upgrade_Suit[8], icon_Anvil[8], ironman_Suit, avengers[16], icon_Avengers[16], icon_Avengers_Block[16], tip[10];

int scene_Upgrade_Y[8] = { 450, 350, 250, 150 };
int anvil_Y[8] = { 460, 360, 260, 160, 460, 360, 260, 160 };
int avengers_X[16] = {62, 180, 290, 420, 560, 720, 860, 980, 1100, 56, 197, 346, 454, 591, 823, 1131};
int icon_Avengers_X[4] = {275,575,875,1175};
int icon_Avengers_Y[4] = { 405, 315, 225, 135 };
int icon_Avengers_Block_X[4] = {53, 353,653, 953};
int icon_Avengers_Block_Y[4] = {396, 306, 216, 126};
int upgrade_Member[8] = { 0, 0, 1, 3, 7, 10, 13, 16 };
bool avengers_Status[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
bool avengers_Possible[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
bool upgrade_Possible[8] = { 1,1,0,0,0,0,0,0 };
double damage_Multiple[9] = {1.0, 1.0, 1.1, 1.2, 1.3, 1.5, 1.7, 2, 3 };

int avengers_Damage[16] = { 20, 20, 50, 50, 50, 100, 100, 1000, 1000, 10000, 5000, 5000, 20000, 2000, 30000, 40000 };
int villain_Damage[12] = { 5, 10, 40, 100, 150, 400, 500, 2500, 4500, 10000, 50000, 150000 };

int upgrade_Status = 0;
int support_Status = 0;
int damage_Status = 10;
int boss_Status = 0;
int attack_Count = 0;
int tip_Count = 0;
int boss_Hp = 0;
int avengers_Member = 0;
int damage_Maximum = 0;
int damage_Minimum = 0;

char icon_Upgrade_Image[20];
char tip_Image[24];
char ironman_Suit_Image[345];
char avengers_Image[81];
char icon_Boss[103];
char scene_Boss_Battle[34];

void avengersPossible(int i) {
    if(!avengers_Status[i])
        if (i == 0 || i == 1) {
            avengers_Possible[i] = 1;
        }
        else if (i == 2) {
            if (boss_Status >= 5) { avengers_Possible[i] = 1; }
        }
        else if (i == 3) {
            if (boss_Status >= 3) { avengers_Possible[i] = 1; }
        }
        else if (i == 4) {
            if (boss_Status >= 5) { avengers_Possible[i] = 1; }
        }
        else if (i == 5) {
            if (upgrade_Status >= 3) { avengers_Possible[i] = 1; }
        }
        else if (i == 6) {
            if (avengers_Status[2]) { avengers_Possible[i] = 1; }
        }
        else if (i == 7) {
            if (boss_Status >= 7) { avengers_Possible[i] = 1; }
        }
        else if (i == 8) {
            if (avengers_Status[4] && upgrade_Status >= 6) { avengers_Possible[i] = 1; }
        }
        else if (i == 9) {
            if (boss_Status >= 10) { avengers_Possible[i] = 1; }
        }
        else if (i == 10) {
            if (boss_Status >= 9) { avengers_Possible[i] = 1; }
        }
        else if (i == 11) {
            if (avengers_Status[9]) { avengers_Possible[i] = 1; }
        }
        else if (i == 12) {
            if (boss_Status >= 10) { avengers_Possible[i] = 1; }
        }
        else if (i == 13) {
            if (boss_Status >= 8) { avengers_Possible[i] = 1; }
        }
        else if (i == 14 || i == 15) {
            if (boss_Status >= 11) { avengers_Possible[i] = 1; }
        }
}


int damage_Calculate() {
    damage_Maximum = floor(damage_Status * damage_Multiple[upgrade_Status]);
    damage_Minimum = ceil(damage_Status * 9 / 10);
    return damage_Minimum + (rand() % (damage_Maximum - damage_Minimum + 1));
}

void recruitScene() {
    for (int i = 0; i < 16; i++) {
        hideObject(icon_Avengers_Block[i]);
        hideObject(icon_Avengers[i]);
    }
    enterScene(scene_Avengers_Recruit);

    for (int i = 0; i < 16; i++) {
        avengersPossible(i);
        if (avengers_Possible[i]) {
            icon_Avengers[i] = createObject("Images\\icon_Avengers.png");
        }
        else {
            icon_Avengers[i] = createObject("Images\\icon_Avengers_2.png");
        }
        if (avengers_Status[i]) {
            icon_Avengers_Block[i] = createObject("Images\\icon_Avengers_Block.png");
            locateObject(icon_Avengers_Block[i], scene_Avengers_Recruit, icon_Avengers_Block_X[i % 4], icon_Avengers_Block_Y[i / 4]);
            showObject(icon_Avengers_Block[i]);
        }
        locateObject(icon_Avengers[i], scene_Avengers_Recruit, icon_Avengers_X[i % 4], icon_Avengers_Y[i / 4]);
        showObject(icon_Avengers[i]);
    }

    if (tip_Count == 7) {
        locateObject(tip[7], scene_Avengers_Recruit, 100, 500);
        showObject(tip[7]);

    }
    else if (tip_Count == 8) {
        locateObject(tip[8], scene_Avengers_Recruit, 500, 500);
        showObject(tip[8]);

    }

    icon_Back = createObject("Images\\icon_Back.png");
    locateObject(icon_Back, scene_Avengers_Recruit, 0, 0);
    showObject(icon_Back);
}

void avengersFacilityScene() {
    enterScene(scene_Avengers_Facility);

    for (int i = 0; i < 16; i++) {
        sprintf(avengers_Image, "Images\\avengers\\avengers_%d.png", i);
        avengers[i] = createObject(avengers_Image);
        if (i < 9) {
            locateObject(avengers[i], scene_Avengers_Facility, avengers_X[i], 400);
        }
        else {
            locateObject(avengers[i], scene_Avengers_Facility, avengers_X[i], 170);
        }  
        if (avengers_Status[i]) {
            showObject(avengers[i]);
        }
    }

    icon_Back = createObject("Images\\icon_Back.png");
    locateObject(icon_Back, scene_Avengers_Facility, 0, 0);
    showObject(icon_Back);
}

void upgradeScene() {
    enterScene(scene_Upgrade);
    hideObject(icon_Upgrade_Suit[0]);
    hideObject(icon_Anvil[0]);

    for (int i = 0; i < 8; i++) {
        sprintf(icon_Upgrade_Image, "Images\\icon_Upgrade\\icon_Upgrade_%d.png", i);
        icon_Upgrade_Suit[i] = createObject(icon_Upgrade_Image);
        if (i < upgrade_Status + 1 && avengers_Member >= upgrade_Member[i]) {
            icon_Anvil[i] = createObject("Images\\icon_Anvil.png");
        }
        else {
            icon_Anvil[i] = createObject("Images\\icon_Anvil_2.png");
        }
        if (i < 4) {
            locateObject(icon_Upgrade_Suit[i], scene_Upgrade, 100, scene_Upgrade_Y[i]);
            locateObject(icon_Anvil[i], scene_Upgrade, 520, anvil_Y[i]);
        } else {    
            locateObject(icon_Upgrade_Suit[i], scene_Upgrade, 680, scene_Upgrade_Y[i - 4]);
            locateObject(icon_Anvil[i], scene_Upgrade, 1100, anvil_Y[i]);
        }
        showObject(icon_Upgrade_Suit[i]);
        showObject(icon_Anvil[i]);
    }

    if (tip_Count == 1) {
        locateObject(tip[1], scene_Upgrade, 100, 500);
        showObject(tip[1]);

    } else if (tip_Count == 2) {

        locateObject(tip[2], scene_Upgrade, 100, 500);
        showObject(tip[2]);
    }

    icon_Back = createObject("Images\\icon_Back.png");
    locateObject(icon_Back, scene_Upgrade, 0, 0);
    showObject(icon_Back);
}

void battleScene() {
    hideObject(ironman_Suit);
    boss_Hp = villain_Damage[boss_Status] * 3;
    sprintf(scene_Boss_Battle, "Images\\villain_Background\\scene_Villain_%d.png", boss_Status);
    scene_Villain = createScene("r", scene_Boss_Battle);
    enterScene(scene_Villain);

    locateObject(ironman_Suit, scene_Villain, 100, 30);
    showObject(ironman_Suit);

    icon_Attack = createObject("Images\\icon_Attack.png");
    locateObject(icon_Attack, scene_Villain, 480, 0);
    showObject(icon_Attack);

    if (tip_Count == 4) {
        locateObject(tip[4], scene_Villain, 300, 100);
        showObject(tip[4]);

    } else if (tip_Count == 5) {

        locateObject(tip[5], scene_Villain, 300, 100);
        showObject(tip[5]);
    }


}

void mainScene() {
    hideObject(ironman_Suit);
    hideObject(icon_Boss_Stage);

    if (upgrade_Status < 2) {
        enterScene(scene_Cave);
    } else if (upgrade_Status < 9) {
        enterScene(scene_Armor);
    }


    sprintf(ironman_Suit_Image, "Images\\ironman_Suit\\ironman_Suit_%d.png", upgrade_Status);
    ironman_Suit = createObject(ironman_Suit_Image);
    if (upgrade_Status < 2) {
        locateObject(ironman_Suit, scene_Cave, 500, 100);
    } else if (upgrade_Status < 9) {
        locateObject(ironman_Suit, scene_Armor, 500, 100);
    }
    showObject(ironman_Suit);

    sprintf(icon_Boss, "Images\\villain\\icon_Villain_%d.png", boss_Status);
    icon_Boss_Stage = createObject(icon_Boss);
    if (upgrade_Status < 2) {
        locateObject(icon_Boss_Stage, scene_Cave, 900, 300);
    }
    else if (upgrade_Status < 9) {
        locateObject(icon_Boss_Stage, scene_Armor, 900, 300);
    }
    showObject(icon_Boss_Stage);

    icon_Upgrade = createObject("Images\\icon_Upgrade.png");
    icon_Recruit = createObject("Images\\icon_Recruit.png");
    icon_Avengers_Facility = createObject("Images\\icon_Avengers_Facility.png");
    if (upgrade_Status < 2) {
        locateObject(icon_Upgrade, scene_Cave, 800, 10);
    }
    else if (upgrade_Status < 9) {
        locateObject(icon_Upgrade, scene_Armor, 800, 10);
        locateObject(icon_Recruit, scene_Armor, 100, 10);
        locateObject(icon_Avengers_Facility, scene_Armor, 10, 400);
    }
    showObject(icon_Upgrade);
    showObject(icon_Recruit);
    showObject(icon_Avengers_Facility);

    if (tip_Count == 0) {
        locateObject(tip[0], scene_Cave, 700, 50);
        showObject(tip[0]);

    } else if (tip_Count == 3) {
        locateObject(tip[3], scene_Cave, 600, 400);
        showObject(tip[3]);

    } else if (tip_Count == 6 && upgrade_Status >= 2) {
        locateObject(tip[6], scene_Armor, 100, 50);
        showObject(tip[6]);

    }
    else if (tip_Count == 9) {
        locateObject(tip[9], scene_Armor, 100, 500);
        showObject(tip[9]);

    }
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == icon_Start) {
        mainScene();
	}
    if (object == icon_Upgrade && tip_Count >= 1) {
        printf("%d", tip_Count);
        upgradeScene();
    }
    if (object == icon_Back) {
        mainScene();
    }
    if (object == icon_Avengers_Facility && tip_Count >= 10) {
        avengersFacilityScene();
    }
    if (object == icon_Recruit && tip_Count >= 7) {
        recruitScene();
    }
    if (object == icon_Boss_Stage && tip_Count >= 4) {
        battleScene();
    }
    for (int i = 0; i < 8; i++) {
        if (object == icon_Anvil[i] && i == upgrade_Status && tip_Count >= 3) {
            upgrade_Status = i + 1;
            upgradeScene();
            printf("%d", upgrade_Status);
        }
    }
    for (int i = 0; i < 16; i++) {
        if (object == icon_Avengers[i] && tip_Count >= 9) {
            avengersPossible(i);
            if (avengers_Possible[i]) {
                avengers_Status[i] = 1;
                avengers_Possible[i] = 0;
                avengers_Member++;
                damage_Status = damage_Status + avengers_Damage[i];
                printf("dmg status %d avengers mem %d", damage_Status, avengers_Member);
                recruitScene();
            }
        }
    }
    if (object == icon_Attack && tip_Count >= 6) { 
        boss_Hp = boss_Hp - damage_Calculate();
        attack_Count++;
        printf("%d %d %d \n", boss_Hp, attack_Count, boss_Status);  
        if (boss_Hp < 1) {
            boss_Status++;
            mainScene();
            attack_Count = 0;
        } else if (attack_Count == 3) {
            mainScene();
            attack_Count = 0;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (object == tip[i]) {
            tip_Count++;
            hideObject(tip[i]);
            if (i == 1) {
                upgradeScene();
            } else if (i == 4) {
                battleScene();
            }
            else if (i == 7) {
                recruitScene();
            }
        } 
    }
}

int main()
{
    setMouseCallback(mouseCallback);

    srand(time(NULL));

    scene_Start = createScene("Room1", "Images\\scene_Start.png");  
    scene_Cave = createScene("Room1", "Images\\scene_Cave.png");
    scene_Armor = createScene("r", "Images\\scene_Armor.png");
    scene_Upgrade = createScene("r", "Images\\scene_Upgrade.png");
    scene_Avengers_Recruit = createScene("s", "Images\\scene_Avengers_Recruit.png");
    scene_Avengers_Facility = createScene("a", "Images\\scene_Avengers_Facility.png");

    for (int i = 0; i < 10; i++) {
        sprintf(tip_Image, "Images\\tip\\tip_%d.png", i);
        tip[i] = createObject(tip_Image);
    }

    icon_Start = createObject("Images\\icon_Start.png");
    locateObject(icon_Start, scene_Start, 480, 0);
    showObject(icon_Start);
    icon_Test = createObject("Images\\icon_Avengers_2.png");
    locateObject(icon_Test, scene_Start, 0, 0);
    showObject(icon_Test);


    startGame(scene_Start);
}
   