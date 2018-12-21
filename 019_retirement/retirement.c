#include <stdio.h>
#include <stdlib.h>

struct retire_info_tag {
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct retire_info_tag retire_info_t;

double BalanceOutput(int startAge, double initial, retire_info_t infoStruct) {
  double currentBlance = initial;
  for (int i = startAge; i < (startAge + infoStruct.months); i++) {
    printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, currentBlance);
    currentBlance = currentBlance * (1 + infoStruct.rate_of_return) + infoStruct.contribution;
  }
  //printf("Age %3d month %2d you have $%.2lf\n", endYear, endMonth, currentBlance);
  return currentBlance;
}

void retirement(int startAge, double initial, retire_info_t working, retire_info_t retired) {
  double CurrentSaving = BalanceOutput(startAge, initial, working);
  int retiredAge = startAge + working.months;
  BalanceOutput(retiredAge, CurrentSaving, retired);
}
int main(void) {
  int start_age = 345;
  double saving = 8116.20;
  retire_info_t working;
  retire_info_t retired;
  working.months = 410;
  working.contribution = 2517;
  working.rate_of_return = 0.0056;
  retired.months = 398;
  retired.contribution = -6534;
  retired.rate_of_return = 0.00473;
  retirement(start_age, saving, working, retired);
  return 0;
}
