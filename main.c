#include <stdlib.h>
#include "global_definition.h"
#include "base.h"

#include "data_utility.c"
#include "menu.c"
/* -------------- 声明全局变量开始 ---------------------*/
struct question_list *question_list; // 存储题目列表
struct store_table *store_table; // 存储表格格式的开头一行的"Questions"、"Answer"、“Score”
struct student *student; // 存储学生的信息
struct student_list *student_list; // 存储学生列表
struct store_student_table *store_student_table; //存储表格格式开头一行的"Major"、"Class"、"Name"、"Grade"、"SN of answered question"、"Answers"
char user_checker[10] = {}; // 存储用户的类型
int student_login_status = 1; // 存储登录状态
struct student * query_info; // 存储查询的学生信息

/* -------------- 声明全局变量结束 ---------------------*/

int main() {
    system("cls"); //clear the screen


    /* -------------------- 数据加载开始 ------------------------ */
    load_question_from_file(); // 从文件中加载题目
    load_student_list_from_file(); // 从文件中加载学生信息
    /* -------------------- 数据加载结束 ------------------------ */

    /* -------------------- 调用管理系统菜单开始 ------------------------ */
    login_menu();  //call the login menu
    /* -------------------- 调用管理系统菜单结束 ------------------------ */

    system("pause"); //pause the screen
    return 0;
}


