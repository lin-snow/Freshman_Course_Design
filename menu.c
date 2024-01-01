#ifndef HEAD_menu
#define HEAD_menu

/* ---- Import Essential header files ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_definition.h"
#include "base.h"

#include "question_operation.c"
#include "score_management.c"
#include "student_operation.c"
#include "linsnow.c"
/* ----------------------------------------*/

/* --------------------------------------- 登录菜单开始 ------------------------------------- */
void login_menu()
{
    system("cls"); //clear the screen
    printf("---------------------------------------------------------------------\n");
    printf("|       Welcome to the English Grade Management System!             |\n");
    printf("|-------------------------------------------------------------------|\n");
    printf("|       1. Student Login                                            |\n");
    printf("|       2. Teacher Login                                            |\n");
    printf("|       3. About                                                    |\n");
    printf("|       4. Exit                                                     |\n");
    printf("|-------------------------------------------------------------------|\n");

    //reaction
    int choice;
    printf("Please input your choice[1-3]: ");
    scanf("%d", &choice);
    getchar(); // 吸收回车
    switch (choice) {
        case 1:
            strcpy(user_checker, "student"); // 将用户类型设置为学生
            login_menu_student(); // 调用学生菜单
            break;
        case 2:
            strcpy(user_checker, "teacher"); // 将用户类型设置为教师
            login_menu_teacher(); // 调用教师菜单
            break;
        case 3:
            print_author(); // 调用打印作者信息函数
            login_menu(); // 调用登录菜单
            break;
        case 4:
            exit(0); // 退出程序
        default:
            printf("Error! Please input again!\n"); // 输入错误，重新输入
            login_menu(); // 调用登录菜单
    }
}
/* --------------------------------------- 登录菜单结束 ------------------------------------- */

/* --------------------------------------- 学生菜单开始 ------------------------------------- */
void login_menu_student()
{
    // 检查学生是否登录,当学生未登录时，调用学生登录界面（student_login_status=1时为未登录，调用登录界面）
    if (student_login_status)
    {
        student_login_interface(); // 调用学生登录界面，登录成功后，student_login_status=0
    }
    printf("Login successfully!\n");
    printf("Press Enter to continue...");
    getchar(); //暂停显示登录信息
    system("cls"); //clear the screen
    printf("---------------------------------------------------------------------\n");
    printf("|       Welcome to the Student English Grade Management System!     |\n");
    printf("|-------------------------------------------------------------------|\n");
    printf("|       1. Doing the English Test                                   |\n");
    printf("|       2. Query the English Grade                                  |\n");
    printf("|       3. Return to the Login Menu                                 |\n");
    printf("|       4. Exit                                                     |\n");
    printf("|-------------------------------------------------------------------|\n");

    //reaction
    int choice;
    printf("Please input your choice[1-4]: ");
    scanf("%d", &choice);
    getchar(); // 吸收回车
    switch (choice) {
        case 1:
            //answer_questions();
            answer_questions(); // 调用答题函数
            login_menu_student(); // 调用学生菜单
            break;
        case 2:
            //query_grade();
            query_grade(); // 调用查询成绩函数
            login_menu_student(); // 调用学生菜单
            break;
        case 3:
            login_menu(); // 调用登录菜单
            break;
        case 4:
            exit(0); // 退出程序
        default:
            printf("Error! Please input again!\n");
            login_menu_student(); // 调用学生菜单
    }
}
/* --------------------------------------- 学生菜单结束 ------------------------------------- */

/* --------------------------------------- 教师菜单开始 ------------------------------------- */
void login_menu_teacher()
{
    system("cls"); //clear the screen
    printf("---------------------------------------------------------------------\n");
    printf("|       Welcome to the Teacher English Grade Management System!     |\n");
    printf("|-------------------------------------------------------------------|\n");
    printf("|       1. Add the English Topic                                    |\n");
    printf("|       2. Delete the English Topic                                 |\n");
    printf("|       3. Modify the English Topic                                 |\n");
    printf("|       4. Show the English Topic                                   |\n");
    printf("|       5. Compute the English Grade                                |\n");
    printf("|       6. Query the English Grade                                  |\n");
    printf("|       7. Statistics the English Grade                             |\n");
    printf("|       8. Sort the English Grade                                   |\n");
    printf("|       9. Modify the English Grade                                 |\n");
    printf("|       10.Delete the Student's Answers                             |\n");
    printf("|       11.Backup current data                                      |\n");
    printf("|       12.Return to the Login Menu                                 |\n");
    printf("|       13.Exit                                                     |\n");
    printf("|-------------------------------------------------------------------|\n");

    //reaction
    int choice;
    printf("Please input your choice[1-12]: ");
    scanf("%d", &choice);
    getchar(); // 吸收回车
    switch (choice) {
        case 1:
            //add_questions();
            add_questions(); // 调用添加题目函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 2:
            //delete_question();
            delete_question(); // 调用删除题目函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 3:
            //modify_question();
            modify_question(); // 调用修改题目函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 4:
            //show_questions();
            show_questions(); // 调用显示题目函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 5:
            //compute_grade();
            compute_grade(); // 调用计算成绩函数
            break;
        case 6:
            //query_grade();
            query_grade(); // 调用查询成绩函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 7:
            //statistics_grade();
            statistics_grade_menu(); // 调用统计成绩函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 8:
            //sort_grade();
            sort_menu();
            printf("Press Enter to continue...");
            getchar();
            login_menu_teacher();
            break;
        case 9:
            //modify_grade();
            modify_grade(); // 调用修改题目函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 10:
            //delete_student();
            delete_student_answer(); // 调用删除学生答案函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 11:
            // backup_data();
            backup_data(); // 调用备份数据函数
            login_menu_teacher(); // 调用教师菜单
            break;
        case 12:
            login_menu(); // 调用登录菜单
            break;
        case 13:
            exit(0); // 退出程序
        default:
            printf("Error! Please input again!\n");
            login_menu_teacher(); // 调用教师菜单
    }
}
/* --------------------------------------- 教师菜单结束 ------------------------------------- */

#endif