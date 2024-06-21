/*
2)항해 (O)
3)스탯추가 (O)
4)보물상자 발견 이벤트 (O)
5)아이템 발견 이벤트 (O)
6)전투 이벤트 (O)
7)전투 결과 정산 (O)
8)게임종료 (O)
9)기타(O) - 이벤트 종류 추가(HP얻을 수 있음 - 추가공격력과 같이 일회성)
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

#define WIDTH 21
#define HEIGHT 3
#define FIX_INDEX 10
#define TARGET_CHAR 'M'
#define MOVING_CHAR '?'
#define REPLACEMENT_CHAR '!' 

char str[HEIGHT][WIDTH + 1];
int movingCharIndex = WIDTH - 1;
int isReplaced = 0;
int gold = 1000;
int addpower = 0;
int addHP = 0;
int addHP2 = 0;

void intro();
int battle(void);
void updateString();
void printString();
void initializeString();
int event(void);

int main() {
    srand((unsigned int)time(NULL));
    intro();
    initializeString();
    while (1) {
        printf("소지금 : %d골드\n", gold);
        printf("추가 공격력 : %d\n", addpower);
        printf("추가 HP : %d\n", addHP);
        printString();
        updateString();
        Sleep(200);
        system("cls");
    }

    return 0;
}

int event(void) {
    int gold2 = 0;
    int event = rand() % 4;
    switch (event) {
    case 0:
        gold2 = rand() % 500 + 1;
        gold = gold + gold2;
        printf("보물상자에서 %d골드를 발견했다!\n", gold2);
        break;
    case 1:
        addpower = 0;
        addpower = rand() % 6 + 5;
        printf("아이템을 발견했다!\n루피의 추가 공격력이 %d가 되었다.", addpower);
        break;
    case 2:
        addHP = rand() % 11 + 5;
        printf("고기를 발견했다!!\n배부른 루피는 기운이 넘쳤다!(HP가 %d늘었다!!).\n", addHP);
        break;

    case 3:
        printf("아니 저자는! 칠무해 크로커다일!\n\n");
        battle();
        break;
    }
    if (gold >= 2000) {
        printf("루피는 %d골드를 모아 동료들과 맛있는 식사를 했다!", gold);
        printf(" \033[34;47;1m\n--HAPPY ENDING--\033[0m\n");
        exit(0);
    }
    else { Sleep(3000); }
}

void updateString() {
    int i;
    if (isReplaced == 1 && movingCharIndex < FIX_INDEX) {
        str[1][movingCharIndex] = ' ';
        isReplaced = 0;
        str[1][FIX_INDEX] = TARGET_CHAR;
        str[1][movingCharIndex - 1] = MOVING_CHAR;
        movingCharIndex--;
    }
    else if (movingCharIndex == FIX_INDEX) {
        str[1][movingCharIndex] = REPLACEMENT_CHAR;
        movingCharIndex--;
        isReplaced = 1;
        str[1][movingCharIndex + 1] = '!';
        system("cls");
        printf("소지금 : %d골드\n", gold);
        printf("추가 공격력 : %d\n", addpower);
        printf("추가 HP : %d\n", addHP);
        printString();
        event();

    }
    else if (movingCharIndex == 0) {
        str[1][movingCharIndex] = ' ';
        movingCharIndex = WIDTH - 1;
        str[1][movingCharIndex] = MOVING_CHAR;
    }
    else {
        str[1][movingCharIndex] = ' ';
        str[1][movingCharIndex - 1] = MOVING_CHAR;
        movingCharIndex--;
    }
}

void printString() {
    int i;
    for (i = 0; i < HEIGHT; i++) {
        printf("%s\n", str[i]);
    }
}

void initializeString() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (i == 1 && j == FIX_INDEX)
                str[i][j] = TARGET_CHAR;
            else if (i == 1 && j == movingCharIndex)
                str[i][j] = MOVING_CHAR;
            else if (i == 0 || i == 2)
                str[i][j] = '*';
            else
                str[i][j] = ' ';
        }
        str[i][WIDTH] = '\0';
    }
}

void intro() {
    char enter;
    printf("===한피스 시작===\n");
    printf("해적왕이 될 사나이 루피는\n");
    printf("고잉 메리호를 타고 길을 떠난다.\n\n");
    printf("바다를 떠돌던 중\n");
    printf("칠무해 크로커다일을 만나 전투가 벌어지는데...\n");
    printf("강적을 만난 루피!\n");
    printf("과연 이길 수 있을 것인가?\n");
    printf("나는 너를 꺾고 더 강해지겠어!\n");
    printf("두둥탁!\n\n");
    printf("Press <Enter> to continue...\n");
    scanf_s("%[^\n]", &enter);
}
int battle(void) {
    int enter, 루피action;
    int sand = 0, gather = 1, pmd = 0, pmd2;
    srand((unsigned int)time(NULL));
    int 루피HP = addHP + rand() % 21 + 20;
    int 크로커다일HP = rand() % 31 + 20;
    int 루피power = addpower + rand() % 6 + 10;
    int 크로커다일power = rand() % 11 + 10;
    int gold3 = 0;

    printf("루피        HP: %d(+ %d 포함), 공격력:  %d (+ %d 포함)\n", 루피HP, addHP, 루피power, addpower);
    printf("크로커다일  HP: %d, 공격력:  %d\n", 크로커다일HP, 크로커다일power);

    while (1) {
        if (루피HP > 0) {
            printf("\n======= 루피 차례 =======\n");
            printf("1. 고무고무 총난타!\n");
            printf("2. 기 모으기\n");
            printf("=========================\n\n");

            printf("루피가 할 행동을 선택하세요(1/2) : ");
            scanf_s("%d", &루피action);
            switch (루피action) {
            case 1:
                if (루피power >= 크로커다일HP) {
                    printf("\n루피의 공격 : 고무고무 총!\n\n");
                    printf("크로커다일 : %d - %d = 0\n\n", 크로커다일HP, 루피power);
                    크로커다일HP = 0;
                    printf("루피        HP: %d\n", 루피HP);       //(4)행동 후 상태 표시
                    printf("크로커다일  HP: %d\n", 크로커다일HP);
                    break;
                }
                else if (sand == 1 && 루피power <= 크로커다일HP) {
                    if (gather >= 2 && sand == 1) {
                        printf("\n루피의 공격 : 고무고무 총! X %d\n\n", gather);
                        pmd2 = 크로커다일HP;
                        크로커다일HP -= (루피power * gather) / 2;
                        if (크로커다일HP <= 0) {
                            printf("크로커다일 : %d - %d = 0\n\n", pmd2, (루피power * gather) / 2);
                            크로커다일HP = 0;
                            printf("루피        HP: %d\n", 루피HP);
                            printf("크로커다일  HP: %d\n", 크로커다일HP);
                            break;
                        }
                        else
                        {
                            printf("크로커다일의 방어로 데미지가 반감됩니다.\n");
                            printf("크로커다일 : %d - %d = %d\n\n", pmd2, (루피power * gather) / 2, pmd2 - (루피power * gather) / 2);
                            gather = 1;
                            printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                            printf("크로커다일  HP: %d\n", 크로커다일HP);
                            sand = 0;
                            break;
                        }
                    }
                    else {
                        printf("\n루피의 공격 : 고무고무 총!\n\n");
                        printf("크로커다일의 방어로 데미지가 반감됩니다.\n");
                        printf("크로커다일 : %d - %d = %d\n\n", 크로커다일HP, 루피power / 2, 크로커다일HP - 루피power / 2);
                        크로커다일HP -= 루피power / 2;
                        printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                        printf("크로커다일  HP: %d, 모래로변신\n", 크로커다일HP);
                        sand = 0;
                        break;
                    }
                }
                else if (gather >= 2) {
                    printf("루피의 공격 : '고무고무 총!' X %d\n", gather);
                    pmd = 크로커다일HP;
                    크로커다일HP -= 루피power * gather;
                    if (크로커다일HP <= 0) {
                        printf("크로커다일 : %d - %d = 0\n\n", pmd, 루피power * gather);
                        크로커다일HP = 0;
                        printf("루피        HP: %d\n", 루피HP);
                        printf("크로커다일  HP: %d\n", 크로커다일HP);
                        break;
                    }
                    else {
                        printf("크로커다일 : %d - %d = %d\n\n", pmd, 루피power * gather, pmd - (루피power * gather));
                        printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                        printf("크로커다일  HP: %d\n", 크로커다일HP);
                        gather = 1;
                        break;
                    }
                    break;
                }
                else {
                    printf("\n루피의 공격 : 고무고무 총!\n\n");
                    printf("크로커다일 : %d - %d = %d\n\n", 크로커다일HP, 루피power, 크로커다일HP - 루피power);
                    크로커다일HP -= 루피power;
                    sand = 0;
                }
                printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                printf("크로커다일  HP: %d\n", 크로커다일HP);
                break;
            case 2:
                printf("\n루피가 기를 모으고 있습니다...\n");
                gather *= 2;
                printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                printf("크로커다일  HP: %d\n", 크로커다일HP);
                break;
            }

        }
        else {
            printf("\n크로커다일 용서하지 않겠어!!!!!!!!!!! 루피가 패배했다...\n");
            printf("크로커다일에게 가진 돈을 모두 잃은 루피는 나미에게 혼나게 된다..");
            printf("\033[31;47;1m\n--BAD ENDING--\033[0m\n");
            exit(0);
        }
        if (크로커다일HP > 0) {
            printf("\n=======크로커다일의 차례=======\n");
            int 크로커다일action = rand() % 3;
            switch (크로커다일action) {
            case 0:
                printf("크로커다일의 공격: '사막의 폭풍!\n\n");
                if (크로커다일power >= 루피HP) {
                    printf("루피 : %d - %d = 0\n\n", 루피HP, 크로커다일power);
                    루피HP = 0;
                    printf("루피        HP: %d\n", 루피HP);
                    printf("크로커다일  HP: %d\n", 크로커다일HP);
                    break;
                }
                else if (gather >= 2) {
                    printf("데미지를 받아서 루피가 모아둔 기가 흩어집니다.\n");
                    printf("루피 : %d - %d = %d\n\n", 루피HP, 크로커다일power, 루피HP - 크로커다일power);
                    루피HP -= 크로커다일power;
                    gather = 1;
                    printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                    printf("크로커다일  HP: %d\n", 크로커다일HP);
                    break;
                }
                else {
                    printf("루피 : %d - %d = %d\n\n", 루피HP, 크로커다일power, 루피HP - 크로커다일power);
                    루피HP -= 크로커다일power;
                }
                printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                printf("크로커다일  HP: %d\n", 크로커다일HP);
                break;
            case 1:
                printf("크로커다일이 물을 모래로 바꿉니다.\n\n");
                printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                printf("크로커다일  HP: %d, 모래로 변신\n", 크로커다일HP);
                sand = 1;
                break;
            case 2:
                printf("크로커다일은 여유를 부립니다: '니가 칠무해가 뭔지 알어?\n\n");
                printf("루피        HP: %d, 기 : %d배\n", 루피HP, gather);
                printf("크로커다일  HP: %d\n", 크로커다일HP);
                continue;
            }
        }
        else {
            gold3 = +rand() % 501 + 500;
            printf("\n루피가 크로커다일을 쓰러트려 %d원을 갈취했다!\n", gold3);
            gold = gold + gold3;
            break;
        }
    }
}