#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

struct User {
    char id[20];
    char password[20];
    char name[30];
    int age;
    char phoneNum[50];
};

struct Product {
    char company[50];
    char name[30];
    char expiration[20];
    int price;
    int adultOnly;
};

struct Product products[] = {
    {"파리바게트", "빵", "2025-12-01", 2000, 0},
    {"말보루", "담배", "2026-05-15", 4500, 1},
    {"코카콜라", "음료수", "2025-07-30", 1500, 0},
    {"던킨도넛", "도넛", "2025-08-21", 2500, 0},
    {"테라", "술", "2030-01-01", 2700, 1},
    {"다이소", "가위", "2035-12-31", 5000, 0},
    {"다이소", "풀", "2032-06-15", 1000, 0},
    {"다이소", "공책", "2030-11-20", 3000, 0},
    {"다이소", "볼펜", "2033-09-05", 1200, 0},
    {"지에스", "물티슈", "2026-02-14", 2500, 0}
};

const int productCount = sizeof(products) / sizeof(products[0]);
int store_money = 1234000;

void pur(struct Product product) {
    int paymentMethod;
    printf("\n1. 카드 결제\n2. 현금 결제\n선택: ");
    scanf("%d", &paymentMethod);

    if (paymentMethod == 1) { // 카드 결제
        store_money -= product.price;
        printf("\n결제 성공! 가게 잔고: %d원\n", store_money);
    } else if (paymentMethod == 2) { // 현금 결제
        int cashGiven;
        printf("\n현금을 투입하세요: ");
        scanf("%d", &cashGiven);
        if (cashGiven >= product.price) {
            int change = cashGiven - product.price;
            store_money += product.price;
            printf("\n결제 완료! 거스름돈: %d원, 가게 잔고: %d원\n", change, store_money);
        } else {
            printf("\n금액이 부족합니다!\n");
        }
    } else {
        printf("\n잘못된 입력입니다.\n");
    }
}

void showProtList() {
    printf("\n===== 제품 목록 =====\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d. %s\n", i + 1, products[i].name);
    }

    char search[30];
    printf("\n검색할 제품명을 입력하세요 (종료: exit): ");
    scanf("%s", search);

    while (strcmp(search, "exit") != 0) {
        int found = 0;
        for (int i = 0; i < productCount; i++) {
            if (strcasecmp(products[i].name, search) == 0) {
                printf("\n===== 제품 정보 =====\n");
                printf("제조회사: %s\n", products[i].company);
                printf("제품명: %s\n", products[i].name);
                printf("유통기한: %s\n", products[i].expiration);
                printf("가격: %d원\n", products[i].price);
                printf("19금 여부: %s\n", products[i].adultOnly ? "✅ 성인용" : "❌ 일반");
                found = 1;
                
                char choice[10];
                printf("\n구매 또는 exit 입력: ");
                scanf("%s", choice);
                if (strcasecmp(choice, "구매") == 0) {
                    pur(products[i]);
                }
                break;
            }
        }
        if (!found) {
            printf("\n해당 제품을 찾을 수 없습니다.\n");
        }
        printf("\n검색할 제품명을 입력하세요 (종료: exit): ");
        scanf("%s", search);
    }
}

void mainMenu() {
    int choice;
    while (1) {
          printf("\n===== 메인 메뉴 =====\n");
        printf("1. 제품 목록\n");
        printf("2. 제품 입고\n");
        printf("3. 재고 상태\n");
        printf("4. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
                case 1:
                showProductList();
                break;
            case 2:
                printf("\n[제품 입고] 기능은 아직 구현되지 않았습니다.\n");
                break;
            case 3:
                printf("\n[재고 상태] 기능은 아직 구현되지 않았습니다.\n");
                break;
            case 4:
                printf("\n프로그램을 종료합니다.\n");
                return;
            default:
                printf("\n잘못된 입력입니다. 다시 선택하세요.\n");

        }
    }
}

int main() {
    struct User user = {"woals", "4482", "이재민", 26, "010-5505-3045"};
    char id[20];
    char password[20];

    printf("아이디를 입력하세요: ");
    scanf("%19s", id);
    printf("비밀번호를 입력하세요: ");
    scanf("%19s", password);

    if (strcmp(id, user.id) == 0 && strcmp(password, user.password) == 0) {
        // 현재 시간 가져오기
        time_t t;
        struct tm *tm;
        char timestr[30];

        time(&t);
        tm = localtime(&t);
        strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", tm);

        // 시급 계산
        int wage_per_min = 9200;
        int balance = 1234000;

        printf("\n로그인 성공! 환영합니다, %s님!\n", user.name);
        printf("===== 개인정보 =====\n");
        printf("이름: %s\n", user.name);
        printf("나이: %d\n", user.age);
        printf("전화번호: %s\n", user.phoneNum);
        printf("\n===== 시스템 정보 =====\n");
        printf("현재 시간: %s\n", timestr);
        printf("분당 시급: %d원\n", wage_per_min);
        printf("현재 잔고: %d원\n", balance);

        // 5초 대기
        printf("\n5초 후 메인 메뉴로 이동합니다...\n");
        sleep(5);

        // 화면 클리어
        #ifdef _WIN32
            system("clear"); // 리눅스/맥 환경
        #endif

        // 메인 메뉴 실행
        mainMenu();

    } else {
        printf("\n로그인 실패! 아이디 또는 비밀번호가 잘못되었습니다.\n");
    }

    return 0;
}
