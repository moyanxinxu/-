#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void showlist(int year, int month, int day);
void scantxt(int day);
int days_of_month(int Year, int Month);
int isLeapYear(int Year);
int getWeekDay(int Year, int Month, int Day);
void printMonthDays(int Year, int Month);
void print_time();
void showlist(int year, int month, int day);
struct Reminders //定义备忘录结构体
{
     int flag;
     char txt[100];
} t[31];
void showlist(int Year, int Month, int Day) //输出该月的所有提醒事项
{
     int i;
     for (i = 0; i < days_of_month(Year, Month); i++)
     {
          if (t[i - 1].flag == 1)
               printf("第%d日:%s\n", i, t[i - 1].txt);
     }
     system("pause");
}
void scantxt(int Day) //判断当日是否有提示信息
{
     if (t[Day - 1].flag == 0)
     {
          printf("你可以在该日期输入文本,请输入:");
          scanf("%s", t[Day - 1].txt);
          t[Day - 1].flag = 1;
     }
     else
     {
          printf("该日期已拥有文本\n该提醒事项是%s\n", t[Day - 1].txt);
     }
}
int isLeapYear(int Year) //判断某年是否为闰年的函数,闰年返回1,平年返回0.
{
     if (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0)
          return 1;
     return 0;
}
int days_of_month(int Year, int Month) //判断某月天数
{
     if (
         Month == 1 ||
         Month == 3 ||
         Month == 5 ||
         Month == 7 ||
         Month == 8 ||
         Month == 10 ||
         Month == 12)
          return 31;
     else if (
         Month == 4 ||
         Month == 6 ||
         Month == 9 ||
         Month == 11)
          return 30;
     else if (isLeapYear(Year))
          return 29;
     return 28;
}
int getWeekDay(int Year, int Month, int Day) //判断某年某月某号是周几的函数
{
     int i, temp, weekday, Days = 0;
     for (i = 1; i <= Month - 1; i++)
          Days += days_of_month(Year, i);
     Days += Day;
     temp = (Year - 1) + (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400 + Days;
     weekday = temp % 7;
     /*
         一年按照365天计算,
         要加上因闰年而减少的天数,
         闰年要满足被4和400整除,且不能被100整除.
         (Year-1)/400是能被400整除的年份个数,
         但包含了能被100和4整除的年份,
         要相应的减去能被100整除的年份,
         加上能被4整除的年份,
         ∵365%7=1
         ∴temp = (Year - 1) + (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400 + Days;
         等价于
         temp = (Year - 1)*365 + (Year - 1) / 4*1 - (Year - 1) / 100*1 + (Year - 1) / 400*1+ Days;
     */
     return weekday;
}
void printMonthDays(int Year, int Month) //输出某年某月日历的函数
{
     int i, j, weekday;
     print_time();
     printf("%d年%d月的日历\n", Year, Month);
     printf("Sun\tMon\tTues\tWed\tThur\tFri\tSat\n");
     weekday = getWeekDay(Year, Month, 1);
     for (i = 0; i < weekday; i++)
          printf("\t");
     for (j = 1; j <= days_of_month(Year, Month); j++)
     {
          if (t[j - 1].flag == 1)
               printf("(%2d)\t", j);
          if (t[j - 1].flag != 1)
               printf("%2d\t", j);
          if ((j + weekday) % 7 == 0)
               printf("\n");
     }
     printf("\n");
}
void print_time() //静态显示时间
{
     SYSTEMTIME time;
     printf("当前时间:\n");
     GetLocalTime(&time);
     printf(
         "%4d/%02d/%02d %02d:%02d:%02d 星期%1d\n",
         time.wYear,
         time.wMonth,
         time.wDay,
         time.wHour,
         time.wMinute,
         time.wSecond,
         time.wDayOfWeek);
}
void Shutdown(int Year, int Month, int Day) //返回到总界面
{
     system("cls");
     printMonthDays(Year, Month);
}
int main()
{
     int Year, Month, Day, temp, i;
     for (i = 0; i < days_of_month(Year, Month); i++)
     {
          t[i].flag = 0;
     } //令所有标记全为0
     print_time();
     printf("\n请按照 年/月 的格式输入所要查询的月历\n");
     scanf("%d/%d", &Year, &Month);
begin:
     system("cls");
     printMonthDays(Year, Month);
     printf("\n请输入相应的数字\n数字0:仅查看日历\n日期:查看当天提醒事项\n404退出提醒事项的输入\n其他数字:查看该月所有提醒事项\n");
     scanf("%d", &Day);
     if (Day == 0)
          temp = 0;
     else if (Day >= 1 && Day <= days_of_month(Year, Month))
          temp = 1;
     else if (Day == 404)
          temp = 2;
     else
          temp = 3;

     switch (temp)
     {
     case 0:
          while (1)
          {
               system("cls");
               print_time();
               printf("请按照 年/月 的格式输入所要查询的月历\n");
               scanf("%d/%d", &Year, &Month);
               printMonthDays(Year, Month);
               system("pause");
          }
     case 1:
          system("cls");
          print_time();
          if (t[Day - 1].flag == 0)
          {
               printf("请输入提醒事项\n");
               scanf("%s", t[Day - 1].txt);
               t[Day - 1].flag = 1;
          }
          else
               scantxt(Day);
          system("pause");
          printMonthDays(Year, Month);
          goto begin;
          break;
     case 2:
          Shutdown(Year, Month, Day);
          break;
     default:
          system("cls");
          showlist(Year, Month, Day);
          goto begin;
     }
     system("pause");
     return 0;
}
