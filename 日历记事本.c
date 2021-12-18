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
struct Reminders //���屸��¼�ṹ��
{
     int flag;
     char txt[100];
} t[31];
void showlist(int Year, int Month, int Day) //������µ�������������
{
     int i;
     for (i = 0; i < days_of_month(Year, Month); i++)
     {
          if (t[i - 1].flag == 1)
               printf("��%d��:%s\n", i, t[i - 1].txt);
     }
     system("pause");
}
void scantxt(int Day) //�жϵ����Ƿ�����ʾ��Ϣ
{
     if (t[Day - 1].flag == 0)
     {
          printf("������ڸ����������ı�,������:");
          scanf("%s", t[Day - 1].txt);
          t[Day - 1].flag = 1;
     }
     else
     {
          printf("��������ӵ���ı�\n������������%s\n", t[Day - 1].txt);
     }
}
int isLeapYear(int Year) //�ж�ĳ���Ƿ�Ϊ����ĺ���,���귵��1,ƽ�귵��0.
{
     if (Year % 4 == 0 && Year % 100 != 0 || Year % 400 == 0)
          return 1;
     return 0;
}
int days_of_month(int Year, int Month) //�ж�ĳ������
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
int getWeekDay(int Year, int Month, int Day) //�ж�ĳ��ĳ��ĳ�����ܼ��ĺ���
{
     int i, temp, weekday, Days = 0;
     for (i = 1; i <= Month - 1; i++)
          Days += days_of_month(Year, i);
     Days += Day;
     temp = (Year - 1) + (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400 + Days;
     weekday = temp % 7;
     /*
         һ�갴��365�����,
         Ҫ��������������ٵ�����,
         ����Ҫ���㱻4��400����,�Ҳ��ܱ�100����.
         (Year-1)/400���ܱ�400��������ݸ���,
         ���������ܱ�100��4���������,
         Ҫ��Ӧ�ļ�ȥ�ܱ�100���������,
         �����ܱ�4���������,
         ��365%7=1
         ��temp = (Year - 1) + (Year - 1) / 4 - (Year - 1) / 100 + (Year - 1) / 400 + Days;
         �ȼ���
         temp = (Year - 1)*365 + (Year - 1) / 4*1 - (Year - 1) / 100*1 + (Year - 1) / 400*1+ Days;
     */
     return weekday;
}
void printMonthDays(int Year, int Month) //���ĳ��ĳ�������ĺ���
{
     int i, j, weekday;
     print_time();
     printf("%d��%d�µ�����\n", Year, Month);
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
void print_time() //��̬��ʾʱ��
{
     SYSTEMTIME time;
     printf("��ǰʱ��:\n");
     GetLocalTime(&time);
     printf(
         "%4d/%02d/%02d %02d:%02d:%02d ����%1d\n",
         time.wYear,
         time.wMonth,
         time.wDay,
         time.wHour,
         time.wMinute,
         time.wSecond,
         time.wDayOfWeek);
}
void Shutdown(int Year, int Month, int Day) //���ص��ܽ���
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
     } //�����б��ȫΪ0
     print_time();
     printf("\n�밴�� ��/�� �ĸ�ʽ������Ҫ��ѯ������\n");
     scanf("%d/%d", &Year, &Month);
begin:
     system("cls");
     printMonthDays(Year, Month);
     printf("\n��������Ӧ������\n����0:���鿴����\n����:�鿴������������\n404�˳��������������\n��������:�鿴����������������\n");
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
               printf("�밴�� ��/�� �ĸ�ʽ������Ҫ��ѯ������\n");
               scanf("%d/%d", &Year, &Month);
               printMonthDays(Year, Month);
               system("pause");
          }
     case 1:
          system("cls");
          print_time();
          if (t[Day - 1].flag == 0)
          {
               printf("��������������\n");
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
