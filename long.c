#include <stdio.h>
#define DEL() while (getchar() != '\n')
typedef struct cauThu_{
  char ten[50];
  int tuoi;
  int chieuCao;
  int canNang;
  char tenDoiBong[50];
  int namKinhNghiem;
} cauThu;

cauThu list[5];

void nhap();
void xuatall();
void xuatone();
void printone(int);

int main() {
  int choose = 0;

  do {
    printf("############################################\n");
    printf("                  MENU\n\n");
    printf("\t1. Nhap thong tin cho 5 cau thu\n");
    printf("\t2. Xuat tat ca thong tin cau thu\n");
    printf("\t3. Nhap vi tri cau thu muon xem\n");
    printf("\t4. Thoat\n");
    do {
      printf("Ban chon: ");
      scanf("%d", &choose); DEL();
      if (choose < 1 || choose > 4) {
	printf("Ban chon sai.\n");
      }
    } while (choose < 1 || choose > 4);

    switch (choose) {
    case 1:
      nhap();
      break;
    case 2:
      xuatall();
      break;
    case 3:
      xuatone();
      break;
    case 4:
      printf("Ket thuc chuong trinh\n\n");
    }
  } while (choose != 4);
}

void nhap() {
  printf("Nhap thong tin cua 5 cau thu\n");
  int i;
  for (i = 0; i < 5; i++) {
    printf("\n#%d\n", i + 1);
    printf("\tTen: ");
    scanf("%[^\n]", list[i].ten); DEL();
    printf("\tTuoi: ");
    scanf("%d", &list[i].tuoi); DEL();
    printf("\tChieu cao: ");
    scanf("%d", &list[i].chieuCao); DEL();
    printf("\tCan nang: ");
    scanf("%d", &list[i].canNang); DEL();
    printf("\tTen doi bong dang hoat dong: ");
    scanf("%[^\n]", list[i].tenDoiBong); DEL();
    printf("\tNam kinh nghiem: ");
    scanf("%d", &list[i].namKinhNghiem); DEL();
  }

  printf("Nhap thong tin xong\n");
}

void printone(int i) {
  printf("\tTen: %s\n", list[i].ten);
  printf("\tTuoi: %d\n", list[i].tuoi);
  printf("\tChieu cao: %d\n", list[i].chieuCao);
  printf("\tCan nang: %d\n", list[i].canNang);
  printf("\tTen doi bong dang hoat dong: %s\n", list[i].tenDoiBong);
  printf("\tNam kinh nghiem: %d\n", list[i].namKinhNghiem);
}

void xuatall() {
  int i;
  for (i = 0; i < 5; i++) {
    printf("Cau thu thu %d\n", i + 1);
    printone(i);
    printf("\n");
  }
}

void xuatone() {
  int i;
  do {
    printf("Nhap vi tri cau thu ban muon xem: ");
    scanf("%d", &i);
    if (i < 1 || i > 5) {
      printf("Ban chon sai. Vi tri thuoc [1, 5]\n");
    }
  } while (i < 1 || i > 5);
    printf("Thong tin cau thu thu %d\n", i);
    printone(i - 1);
}