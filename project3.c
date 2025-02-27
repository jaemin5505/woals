#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#define CLEAR_SCREEN "clear"

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
    int stock;
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
time_t startTime;

void clearBuffer()
{
	 while(getchar() != '\n');

}


void showStock() 
{
    printf("\n===== 재고 상태 =====\n");
    for (int i = 0; i < productCount; i++)
    {
        printf("%d. %s", i + 1, products[i].name);
		for(int j = 0; j < products[i].stock; j++)
		{
			printf("*");
		}
		printf(" (%d개)\n", products[i].stock);
    }
}

void restockProduct() 
{
    int choice;
	int quantity;
    showStock();
    printf("\n입고할 제품 번호를 입력하세요 (취소: 0): ");
    scanf("%d", &choice);
    if (choice < 1 || choice > productCount) 
      return;
    printf("입고할 수량을 입력하세요: ");
    scanf("%d", &quantity);
    products[choice - 1].stock += quantity;
    printf("\n%s의 재고가 %d개로 증가했습니다!\n", products[choice - 1].name, products[choice - 1].stock);
}

int isAdult() 
{
    int birthYear;
    printf("\n태어난 연도를 입력하세요: ");
    scanf("%d", &birthYear);
    return birthYear <= 2006;
}

void purchaseProduct(struct Product * product) 
{
  if (product->stock <= 0) 
  {
        printf("\n해당 제품은 품절되었습니다!\n");
        return;
   }
    if (product->adultOnly && !isAdult()) 
    {
            printf("\n미성년자는 구매할 수 없습니다!\n");
            return;
    }

    
   int paymentMethod;
    printf("\n1. 카드 결제\n2. 현금 결제\n선택: ");
    if (scanf("%d", &paymentMethod) != 1)
		{
			printf("\n숫자를 입력하세요\n");
			clearBuffer();
			return;
		}

    if (paymentMethod == 1) 
	{
        store_money += product->price; //매출증가
    } 
	else if (paymentMethod == 2)
		{
        int cashGiven;
        printf("\n현금을 투입하세요: ");
        if (scanf("%d", &cashGiven) != 1 || cashGiven < product -> price)
		{
			printf("\n금액이 부족하거나 잘못된 입력입니다\n");
			return;
		}
 
	
            int change = cashGiven - product->price;
            store_money += product -> price;
            printf("\n거스름돈: %d원\n", change);
        } 
	else 
		{
            printf("\n잘못된 입력입니다\n");
            return;
        }
    
    product->stock--;//실제 재고 감소
    printf("\n구매 완료! 남은 재고: %d개\n", product -> stock);
}

void showProductList() {
  printf("\n===== 제품 목록 =====\n");
    for (int i = 0; i < productCount; i++) 
	{
        printf("%d. %s (%d개)\n", i + 1, products[i].name, products[i].stock);
    }

    char search[30];
	while (1)
	{	
		 printf("\n검색할 제품명을 입력하세요 (종료: 종료): ");
		 scanf("%s", search);
		 if(strcmp(search,"종료") == 0)
			 break;

        int found = 0;
        for (int i = 0; i < productCount; i++) 
		{
            if (strcasecmp(products[i].name, search) == 0) 
			{
				found = 1;
                printf("\n===== 제품 정보 =====\n");
                printf("제조회사: %s\n", products[i].company);
                printf("제품명: %s\n", products[i].name);
                printf("유통기한: %s\n", products[i].expiration);
                printf("가격: %d원\n", products[i].price);
                printf("19금 여부: %s\n", products[i].adultOnly ? "o 성인용" : "x 일반");
                
                
                char choice[10];
                printf("\n구매 또는 종료 입력: ");
                scanf("%s", choice);
                if (strcasecmp(choice, "구매") == 0) 
                {
                    purchaseProduct(&products[i]);
                }
                break;
            }
        }
        if (!found) 
		{
            printf("\n해당 제품을 찾을 수 없습니다.\n");
        }
        
    }
}

void mainMenu() {
    int choice;
    while (1) {
        printf("\n===== 메인 메뉴 =====\n");
         printf("1. 제품 목록\n2. 제품 입고\n3. 재고 상태\n4. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                showProductList();
                break;
            case 2:
                restockProduct();
                break;
            case 3:
                showStock();
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
	startTime = time(NULL);

    printf("아이디를 입력하세요: ");
    scanf("%s", id);
    printf("비밀번호를 입력하세요: ");
    scanf("%s", password);

  if (strcmp(id, user.id) == 0 && strcmp(password, user.password) == 0) 
  {
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
        printf("------ 개인정보 ------\n");
        printf("이름: %s\n", user.name);
        printf("나이: %d\n", user.age);
        printf("전화번호: %s\n", user.phoneNum);
        printf("\n------ 시스템 정보 ------\n");
        printf("현재 시간: %s\n", timestr);
        printf("분당 시급: %d원\n", wage_per_min);
        printf("현재 가게 잔고: %d원\n", store_money);
        printf("\n3초 후 메인 메뉴로 이동합니다...\n");
        sleep(3);
        system(CLEAR_SCREEN);
        mainMenu();
    } else {
        printf("\n로그인 실패!\n");
    }
  time_t endTime = time(NULL);
  int elp = (endTime - startTime) / 60;
  int ean = elp * 9200;

  printf("총 급여: %d원\n", ean);

    return 0;
}
