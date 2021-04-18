#define _CRT_SECURE_NO_WARNINGS
#include <bangtal.h>
#include <stdio.h>
SceneID scene_Start, scene_Cave, scene_Upgrade, scene_Armor, scene_Avengers_Facility, scene_Avengers_Recruit, scene_Villain;
ObjectID icon_Start, icon_Support, icon_Upgrade, icon_Back, icon_Avengers_Facility, icon_Recruit, icon_Test, icon_Boss_Stage, icon_Attack;
ObjectID icon_Upgrade_Suit[8], icon_Anvil[8], ironman_Suit, avengers[16], icon_Avengers[16], icon_Avengers_Block[16];

int scene_Upgrade_Y[8] = { 450, 350, 250, 150 };
int anvil_Y[8] = { 450, 350, 250, 150, 450, 350, 250, 150 };
int avengers_X[16] = {62, 180, 290, 420, 560, 720, 860, 980, 1100, 56, 197, 346, 454, 591, 823, 1131};
int icon_Avengers_X[4] = {275,575,875,1175};
int icon_Avengers_Y[4] = { 405, 315, 225, 135 };
int icon_Avengers_Block_X[4] = {53, 353,653, 953};
int icon_Avengers_Block_Y[4] = {396, 306, 216, 126};
bool avengers_Status[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
bool avengers_Possible[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int avengers_Damage[16] = { 20, 20, 50, 50, 50, 100, 100, 1000, 1000, 10000, 5000, 5000, 20000, 2000, 30000, 40000 };
int villain_Damage[12] = { 5, 10, 40, 100, 150, 400, 500, 2500, 4500, 10000, 50000, 150000 };

int upgrade_Status = 0;
int support_Status = 0;
int damage_Status = 150000;
int boss_Status = 0;
int attack_Count = 0;
int boss_Hp = 0;

char icon_Upgrade_Image[20];
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

    for (int i = 0; i < 8; i++) {
        sprintf(icon_Upgrade_Image, "Images\\icon_Upgrade_%d.png", i + 1);
        icon_Upgrade_Suit[i] = createObject(icon_Upgrade_Image);
        if (i < upgrade_Status + 1) {
            icon_Anvil[i] = createObject("Images\\icon_Anvil.png");
        }
        else {
            icon_Anvil[i] = createObject("Images\\icon_Anvil_2.png");
        }
        if (i < 4) {
            locateObject(icon_Upgrade_Suit[i], scene_Upgrade, 100, scene_Upgrade_Y[i]);
            locateObject(icon_Anvil[i], scene_Upgrade, 530, anvil_Y[i]);
        } else {
            locateObject(icon_Upgrade_Suit[i], scene_Upgrade, 680, scene_Upgrade_Y[i - 4]);
            locateObject(icon_Anvil[i], scene_Upgrade, 1110, anvil_Y[i]);
        }
        showObject(icon_Upgrade_Suit[i]);
        showObject(icon_Anvil[i]);
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

    icon_Attack = createObject("Images\\icon_Attack.png");
    locateObject(icon_Attack, scene_Villain, 480, 0);
    showObject(icon_Attack);

    locateObject(ironman_Suit, scene_Villain, 100, 100);
    showObject(ironman_Suit);

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
    ////////////////////////////////////////sceneCave/scene_Armor 구분 함수 만들면 깔끔
    sprintf(icon_Boss, "Images\\villain\\icon_Villain_%d.png", boss_Status);
    icon_Boss_Stage = createObject(icon_Boss);
    if (upgrade_Status < 2) {
        locateObject(icon_Boss_Stage, scene_Cave, 900, 300);
    }
    else if (upgrade_Status < 9) {
        locateObject(icon_Boss_Stage, scene_Armor, 900, 300);
    }
    showObject(icon_Boss_Stage);


    icon_Support = createObject("Images\\icon_Support.png");
    icon_Upgrade = createObject("Images\\icon_Upgrade.png");
    icon_Recruit = createObject("Images\\icon_Recruit.png");
    icon_Avengers_Facility = createObject("Images\\icon_Avengers_Facility.png");
    if (upgrade_Status < 2) {
        locateObject(icon_Support, scene_Cave, 0, 0);
        locateObject(icon_Upgrade, scene_Cave, 700, 0);
    }
    else if (upgrade_Status < 9) {
        locateObject(icon_Support, scene_Armor, 0, 0);
        locateObject(icon_Upgrade, scene_Armor, 1000, 0);
        locateObject(icon_Recruit, scene_Armor, 500, 0);
        locateObject(icon_Avengers_Facility, scene_Armor, 0, 400);
    }
    showObject(icon_Support);
    showObject(icon_Upgrade);
    showObject(icon_Recruit);
    showObject(icon_Avengers_Facility);
}

void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	if (object == icon_Start) {
        mainScene();
	}
    if (object == icon_Upgrade) {
        upgradeScene();
    }
    if (object == icon_Back) {
        mainScene();
    }
    if (object == icon_Avengers_Facility) {
        avengersFacilityScene();
    }
    if (object == icon_Recruit) {
        recruitScene();
    }
    if (object == icon_Boss_Stage) {
        battleScene();
    }
    for (int i = 0; i < 8; i++) {
        if (object == icon_Anvil[i] && i == upgrade_Status ) {
            upgrade_Status = i + 1;
            upgradeScene();
            printf("%d", upgrade_Status);
        }
    }
    for (int i = 0; i < 16; i++) {
        if (object == icon_Avengers[i]) {
            avengersPossible(i);
            if (avengers_Possible[i]) {
                avengers_Status[i] = 1;
                avengers_Possible[i] = 0;
                damage_Status = damage_Status + avengers_Damage[i];
                printf("%d", damage_Status);
                recruitScene();
            }
        }
    }
    if (object == icon_Attack) {
        boss_Hp = boss_Hp - damage_Status;
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

}

int main()
{
    setMouseCallback(mouseCallback);

    scene_Start = createScene("Room1", "Images\\scene_Start.png");
    scene_Cave = createScene("Room1", "Images\\scene_Cave.png");
    scene_Armor = createScene("r", "Images\\scene_Armor.png");
    scene_Upgrade = createScene("r", "Images\\scene_Upgrade.png");
    scene_Avengers_Recruit = createScene("s", "Images\\scene_Avengers_Recruit.png");
    scene_Avengers_Facility = createScene("a", "Images\\scene_Avengers_Facility.png");

    icon_Start = createObject("Images\\icon_Start.png");
    locateObject(icon_Start, scene_Start, 480, 0);
    showObject(icon_Start);
    icon_Test = createObject("Images\\icon_Avengers_2.png");
    locateObject(icon_Test, scene_Start, 0, 0);
    showObject(icon_Test);


    startGame(scene_Start);
}
   