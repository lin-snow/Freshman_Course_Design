#ifndef HEAD_score_management
#define HEAD_score_management

/* ---- Import Essential header files ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_definition.h"
#include "base.h"
/* ----------------------------------------*/

/* --------------------------------------- 计算成绩开始 ------------------------------------- */
void compute_grade()
{
    system("cls"); // clear the screen
    /* 选择如何改卷 */
    printf("|--------------------------------------------------------------------|\n");
    printf("|                Welcome to the Grade Compute System!                |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|       1. Compute the grade of a student                            |\n");
    printf("|       2. Compute the grade of all students                         |\n");
    printf("|       3. Return to the previous menu                               |\n");
    printf("|       4. Exit                                                      |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("Please input your choice[1-4]: "); // 提示用户输入
    /* 获取用户的选择 */
    int compute_choice;
    scanf("%d", &compute_choice);
    getchar(); // 吸收上一次输入的回车符
    switch (compute_choice) {
        case 1:
            compute_grade_of_a_student(); // 计算某一位学生的成绩
            break;
        case 2:
            compute_grade_of_all_students(); // 计算所有学生的成绩
            break;
        case 3:
                login_menu_teacher(); // 返回上一级菜单
            break;
        case 4:
            exit(0); // 退出程序
        default:
            printf("Error! Please input again!\n"); // 输入错误，重新输入
            compute_grade(); // 调用计算成绩菜单
    }
}
void compute_grade_of_a_student()
{
    system("cls"); // clear the screen
    /* 显示提示信息 */
    printf("|--------------------------------------------------------------------|\n");
    printf("|                Welcome to the Grade Compute System!                |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("Please input the student that you want to compute his/her grade: ");
    /* 调用查询菜单,获取需要改卷的学生 */
    struct student * student_need_to_compute_pointer ;
    student_need_to_compute_pointer = query_grade();

    /* 计算成绩 */
    /* 显示学生的答案及其对应的分数 */
    system("cls");
    printf("|-------------------------------------------------------------------------------------------------------------|\n");
    printf("|                             The student's answers and scores are as follows:                                |\n");
    printf("|-------------------------------------------------------------------------------------------------------------|\n");
    printf("| Major: %-17s    | Class: %-12s    |  Name: %-12s           |\n", student_need_to_compute_pointer->major, student_need_to_compute_pointer->class, student_need_to_compute_pointer->name);
    printf("|-------------------------------------------------------------------------------------------------------------|\n");

    /* 显示学生做的题目的序列及其对应的答案 */
    for (int i =0;student_need_to_compute_pointer->sn[i] != 0;i++)
    {
        /* 显示学生作答的题目 */
        struct question * question_need_to_compute_pointer = question_list->head;
        for (int j = 1;j < student_need_to_compute_pointer->sn[i];j++)
        {
            question_need_to_compute_pointer = question_need_to_compute_pointer->next;
        }
        printf("| SN: %-3d | Question: %-35s | Answer: %-21s | Score: %-3s |\n", student_need_to_compute_pointer->sn[i],question_need_to_compute_pointer->question,student_need_to_compute_pointer->answers[i],question_need_to_compute_pointer->score);
    }
    printf("|-------------------------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...\n");
    getchar();
    student_need_to_compute_pointer->grade[0] = '0';
    student_need_to_compute_pointer->grade[1] = '\0';
    printf("Please Now please give your grade for this paper: ");
    fgets(student_need_to_compute_pointer->grade,sizeof(student_need_to_compute_pointer->grade),stdin); // 获取分数
    student_need_to_compute_pointer->grade[strcspn(student_need_to_compute_pointer->grade, "\n")] = '\0'; // 将末尾的换行符替换为\0
    save_students_to_file(); // 保存学生信息到文件
    /* 输出改卷成功的提示 */
    printf("Compute successfully!\n");
    /* 返回上一级菜单 */
    compute_grade();
}
void compute_grade_of_all_students()
{
    system("cls"); // clear the screen
    /* 判断是否没有学生 */
    if (student_list->total_student == 0)
    {
        printf("There is no student!\n");
        printf("Press Enter to continue...\n");
        getchar();
        compute_grade();
    }
    // 用于遍历学生链表
    struct student * student_need_to_compute_pointer = student_list->head;
    while (1)
    {
        system("cls"); // clear the screen
        if (student_need_to_compute_pointer == NULL)
        {
            break;
        }
        /* 显示提示信息 */
        printf("|--------------------------------------------------------------------------------------|\n");
        printf("|                 The student's answers and scores are as follows:                     |\n");
        printf("|--------------------------------------------------------------------------------------|\n");
        printf("| Major: %-17s    | Class: %-12s    |  Name: %-12s           |\n", student_need_to_compute_pointer->major, student_need_to_compute_pointer->class, student_need_to_compute_pointer->name);
        printf("|--------------------------------------------------------------------------------------|\n");
        /* 显示学生做的题目的序列及其对应的答案 */
        for (int i =0;student_need_to_compute_pointer->sn[i] != 0;i++)
        {
            /* 显示学生作答的题目 */
            struct question * question_need_to_compute_pointer = question_list->head;
            for (int j = 1;j < student_need_to_compute_pointer->sn[i];j++)
            {
                question_need_to_compute_pointer = question_need_to_compute_pointer->next;
            }
            printf("| SN: %-3d | Question: %-25s | Answer: %-15s | Score: %-3s |\n", student_need_to_compute_pointer->sn[i],question_need_to_compute_pointer->question,student_need_to_compute_pointer->answers[i],question_need_to_compute_pointer->score);
        }
        printf("|--------------------------------------------------------------------------------------|\n");
        printf("Press Enter to continue...\n");
        getchar();
        student_need_to_compute_pointer->grade[0] = '0';
        student_need_to_compute_pointer->grade[1] = '\0';
        printf("Please Now please give your grade for this paper: ");
        fgets(student_need_to_compute_pointer->grade,sizeof(student_need_to_compute_pointer->grade),stdin); // 获取分数
        student_need_to_compute_pointer->grade[strcspn(student_need_to_compute_pointer->grade, "\n")] = '\0'; // 将末尾的换行符替换为\0
        /* 输出改卷成功的提示 */
        printf("Compute successfully!\n");
        /* 更新指向学生的指针 */
        student_need_to_compute_pointer = student_need_to_compute_pointer->next;
    }
    /* 提示所有学生改卷完毕 */
    printf("All students have been graded!\n");
    printf("Press Enter to continue...\n");
    getchar();
    save_students_to_file(); // 保存学生信息到文件
    /* 返回上一级菜单 */
    compute_grade();
}
/* --------------------------------------- 计算成绩结束 ------------------------------------- */

/* --------------------------------------- 查询学生成绩开始 ------------------------------------- */
struct student * query_grade()
{
    system("cls"); // clear the screen
    /* 显示查询菜单 */
    printf("|--------------------------------------------------------------------|\n");
    printf("|                      Welcome to the Query Menu!                    |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|       1. Single field query                                        |\n");
    printf("|       2. Multiple field query                                      |\n");
    printf("|       3. Return to the previous menu                               |\n");
    printf("|       4. Exit                                                      |\n");
    printf("|--------------------------------------------------------------------|\n");
    query_info = (struct student *) malloc(sizeof(struct student));
    /* 判断是否开辟成功 */
    if (query_info == NULL)
    {
        printf("Error! Please try again!\n");
        multiple_field_query();
    }
    /* 初始化查询信息 */
    strcpy(query_info->major,"");
    strcpy(query_info->class,"");
    strcpy(query_info->name,"");
    strcpy(query_info->grade,"");
    /* 获取用户的选择 */
    int query_choice;
    printf("Please input your choice[1-4]: "); // 提示用户输入
    scanf("%d", &query_choice); // 获取用户的选择
    switch (query_choice) {
        case 1:
            getchar(); // 吸收上一次输入的回车符
            return single_field_query(); // 单字段查询
        case 2:
            getchar(); // 吸收上一次输入的回车符
            return multiple_field_query(); // 多字段查询
        case 3:
            /* 判断之前是否为学生登录 */
            if (strcmp(user_checker, "student") == 0)
                login_menu_student(); // 返回上一级菜单
            else if (strcmp(user_checker, "teacher") == 0)
                login_menu_teacher(); // 返回上一级菜单
            break;
        case 4:
            exit(0); // 退出程序
        default:
            printf("Error! Please input again!\n"); // 输入错误，重新输入
            query_grade(); // 调用查询菜单
    }
}
/* --------------------------------------- 单字段查询开始 ------------------------------------- */
struct student * single_field_query()
{
    system("cls"); // clear the screen
    /* 输出提示信息 */
    printf("|--------------------------------------------------------------------|\n");
    printf("|                  Welcome to the Single Field Query !               |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("|       1. Query by major                                            |\n");
    printf("|       2. Query by class                                            |\n");
    printf("|       3. Query by name                                             |\n");
    printf("|       4. Query by grade                                            |\n");
    printf("|       5. Return to the previous menu                               |\n");
    printf("|       6. Exit                                                      |\n");
    printf("|--------------------------------------------------------------------|\n");
    printf("Please input your choice[1-6]: "); // 提示用户输入
    /* 获取用户的选择 */
    int single_query_choice;
    scanf("%d", &single_query_choice);
    getchar(); // 吸收上一次输入的回车符

    struct student * query_student_pointer = student_list->head; // 定义一个指针指向学生链表的头部，用于遍历学生链表
    char * query_rule = NULL;char *query_student_info_pointer = NULL;
    /* 匹配选项 */
    switch(single_query_choice)
    {
        case 1:
            query_rule = query_info->major;
            break;
        case 2:
            query_rule = query_info->class;
            break;
        case 3:
            query_rule = query_info->name;
            break;
        case 4:
            query_rule = query_info->grade;
            break;
        case 5:
            /* 判断之前是否为学生登录 */
            if (strcmp(user_checker, "student") == 0)
                login_menu_student(); // 返回上一级菜单
            else if (strcmp(user_checker, "teacher") == 0)
                login_menu_teacher(); // 返回上一级菜单
            break;
        case 6:
            exit(0);
        default:
            printf("Input error,please input again...\n");
            single_field_query();
    }
    /* 进行查找 */
    printf("Input the your information to query: ");
    fgets(query_rule, 100, stdin);
    query_rule[strcspn(query_rule, "\n")] = '\0'; // 去除末尾的换行符
    /* 进行查询 */
    while(query_student_pointer != NULL)
    {
        switch (single_query_choice) {
            case 1:
                query_student_info_pointer = query_student_pointer->major;
                break;
            case 2:
                query_student_info_pointer = query_student_pointer->class;
                break;
            case 3:
                query_student_info_pointer = query_student_pointer->name;
                break;
            case 4:
                query_student_info_pointer = query_student_pointer->grade;
                break;
        }
        if (strcmp(query_rule,query_student_info_pointer) == 0)
        {
            printf("|--------------------------------------------------------------------|\n");
            printf("|       The information you want to query is as follows:             |\n");
            printf("|--------------------------------------------------------------------|\n");
            printf("| Major: %-40s                    |\n", query_student_pointer->major);
            printf("| Class: %-40s                    |\n", query_student_pointer->class);
            printf("| Name: %-40s                     |\n", query_student_pointer->name);
            printf("| Grade: %-40s                    |\n", query_student_pointer->grade);
            printf("|--------------------------------------------------------------------|\n");
            printf("Press Enter to continue...\n");
            getchar();
            return query_student_pointer;
        }
        /* 更新指向学生的指针 */
        query_student_pointer = query_student_pointer->next;
    }
    /* 判断是否找不到 */
    if(query_student_pointer == NULL)
    {
        printf("Can't find the information you want to query!\n");
        printf("Press Enter to continue...\n");
        getchar();
    }

    /* 返回上一级菜单 */
    single_field_query();
}

/* --------------------------------------- 单字段查询结束 ------------------------------------- */

/* --------------------------------------- 多字段查询开始 ------------------------------------- */
struct student * multiple_field_query()
{
    system("cls"); // clear the screen
    /* 输出提示信息 */
    printf("|------------------------------------------------------------------|\n");
    printf("|                  Welcome to the Multiple Field Query !           |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("|       1. Query by major and class                                |\n");
    printf("|       2. Query by major and name                                 |\n");
    printf("|       3. Query by major and grade                                |\n");
    printf("|       4. Query by class and name                                 |\n");
    printf("|       5. Query by class and grade                                |\n");
    printf("|       6. Query by name and grade                                 |\n");
    printf("|       7. Return to the previous menu                             |\n");
    printf("|       8. Exit                                                    |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("Please input your choice[1-8]: "); // 提示用户输入
    /* 获取用户的选择 */
    int multiple_query_choice;
    scanf("%d", &multiple_query_choice);
    getchar(); // 吸收上一次输入的回车符

    struct student * query_student_pointer = student_list->head; // 定义一个指针指向学生链表的头部，用于遍历学生链表
    char * query_rule_one = NULL;char * query_rule_two = NULL;
    char * query_student_info_pointer_one = NULL;char * query_student_info_pointer_two = NULL;
    /* 匹配选项 */
    switch (multiple_query_choice) {
        case 1:
            query_rule_one = query_info->major;
            query_rule_two = query_info->class;
            break;
        case 2:
            query_rule_one = query_info->major;
            query_rule_two = query_info->name;
            break;
        case 3:
            query_rule_one = query_info->major;
            query_rule_two = query_info->grade;
            break;
        case 4:
            query_rule_one = query_info->class;
            query_rule_two = query_info->name;
            break;
        case 5:
            query_rule_one = query_info->class;
            query_rule_two = query_info->grade;
            break;
        case 6:
            query_rule_one = query_info->name;
            query_rule_two = query_info->grade;
            break;
        case 7:
            /* 判断之前是否为学生登录 */
            if (strcmp(user_checker, "student") == 0)
                login_menu_student(); // 返回上一级菜单
            else if (strcmp(user_checker, "teacher") == 0)
                login_menu_teacher(); // 返回上一级菜单
            break;
        default:
            printf("Input error,please input again...\n");
            single_field_query();
    }
    /* 输入查询信息 */
    printf("Input the your first information to query: ");
    fgets(query_rule_one, 100, stdin);
    query_rule_one[strcspn(query_rule_one, "\n")] = '\0'; // 去除末尾的换行符
    printf("Input the your second information to query: ");
    fgets(query_rule_two, 100, stdin);
    query_rule_two[strcspn(query_rule_two, "\n")] = '\0'; // 去除末尾的换行符
    /* 进行查询 */
    while(query_student_pointer != NULL)
    {
        switch(multiple_query_choice)
        {
            case 1:
                query_student_info_pointer_one = query_student_pointer->major;
                query_student_info_pointer_two = query_student_pointer->class;
                break;
            case 2:
                query_student_info_pointer_one = query_student_pointer->major;
                query_student_info_pointer_two = query_student_pointer->name;
                break;
            case 3:
                query_student_info_pointer_one = query_student_pointer->major;
                query_student_info_pointer_two = query_student_pointer->grade;
                break;
            case 4:
                query_student_info_pointer_one = query_student_pointer->class;
                query_student_info_pointer_two = query_student_pointer->name;
                break;
            case 5:
                query_student_info_pointer_one = query_student_pointer->class;
                query_student_info_pointer_two = query_student_pointer->grade;
                break;
            case 6:
                query_student_info_pointer_one = query_student_pointer->name;
                query_student_info_pointer_two = query_student_pointer->grade;
                break;
        }
        if (strcmp(query_rule_one,query_student_info_pointer_one) == 0 && strcmp(query_rule_two,query_student_info_pointer_two) == 0)
        {
            printf("|--------------------------------------------------------------------|\n");
            printf("|       The information you want to query is as follows:             |\n");
            printf("|--------------------------------------------------------------------|\n");
            printf("| Major: %-40s                    |\n", query_student_pointer->major);
            printf("| Class: %-40s                    |\n", query_student_pointer->class);
            printf("| Name: %-40s                     |\n", query_student_pointer->name);
            printf("| Grade: %-40s                    |\n", query_student_pointer->grade);
            printf("|--------------------------------------------------------------------|\n");
            printf("Press Enter to continue...\n");
            getchar();
            return query_student_pointer;
        }
        /* 更新指向学生的指针 */
        query_student_pointer = query_student_pointer->next;
    }
    /* 检查是否未查找到 */
    if (query_student_pointer == NULL)
    {
        printf("Can't find the information you want to query!\n");
        printf("Press Enter to continue...\n");
        getchar();
        /* 释放内存 */
        free(query_info);
        return NULL;
    }

    /* 返回上一级菜单 */
    multiple_field_query();
}
/* --------------------------------------- 多字段查询结束 ------------------------------------- */

/* --------------------------------------- 查询学生成绩结束 ------------------------------------- */

/* --------------------------------------- 统计学生成绩开始 ------------------------------------- */
void statistics_grade_menu()
{
    system("cls"); // clear the screen
    /* 输出提示信息 */
    printf("|------------------------------------------------------------------|\n");
    printf("|                  Welcome to the Statistics Menu!                 |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("|       1. Statistics all students' grade                         |\n");
    printf("|       2. Statistics the students within the score range          |\n");
    printf("|       3. Return to the previous menu                             |\n");
    printf("|       4. Exit                                                    |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("Please input your choice[1-4]: "); // 提示用户输入
    int statistics_choice; // 存储选项
    scanf("%d", &statistics_choice); // 输入选项
    getchar(); // 吸收回车
    switch (statistics_choice) {
        case 1:
            statistics_grade(); // 统计所有学生的成绩
            break;
        case 2:
            statistics_grade_in_range(); // 统计分数在某一范围内的学生
    }
}
void statistics_grade_in_range()
{
    system("cls");
    int upper_limit,lower_limit; // 上限、下限
    printf("Please input the upper limit of the score range: ");
    scanf("%d",&upper_limit);
    getchar();
    printf("\nPlease input the lower limit of the score range: ");
    scanf("%d",&lower_limit);
    getchar();

    /* 检查输入是否合法 */
    if (upper_limit < lower_limit)
    {
        printf("Input error! Please input again...\n");
        statistics_grade_in_range();
    }

    /* 调用排序函数，将学生按照分数升序排序   */
    sort_grade(1,0,0);
    /* 定义一个结构体指针，用于遍历学生 */
    struct student * each_student = student_list->head;
    /* 定义各项数据变量，用于统计分数 */
    double students_total_grade = 0.0; // 统计总分
    double students_average_grade ; // 统计平均分
    double students_max_grade ; // 统计最高分
    double students_min_grade ; // 统计最低分

    /* 学生列表行数   */
    int student_list_sn = 1;
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|                                           The Student List and Grade                        |\n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    while (each_student != NULL)
    {
        if (atof(each_student->grade) >= lower_limit && atof(each_student->grade) <= upper_limit)
        {
            /* 输出学生基本信息及其对应的成绩 */
            printf("|Student SN: %-3d |Major: %-12s|Class: %-10s  |Name: %-10s  |Grade: %-5s     |\n", student_list_sn,each_student->major,each_student->class,each_student->name,each_student->grade);
            printf("|---------------------------------------------------------------------------------------------|\n");
            /* 统计分数 */
            students_total_grade += atof(each_student->grade);
            /* 统计最低分 */
            if (student_list_sn == 1) students_min_grade = atof(each_student->grade);
            /* 统计最高分 */
            students_max_grade = atof(each_student->grade);
            /* 更新学生列表行数 */
            student_list_sn++;
        }

        /* 更新指针 */
        each_student = each_student->next;
    }
    /* 计算各项成绩数据 */
    students_average_grade = students_total_grade / (student_list_sn - 1); // 计算平均分
    /* 输出统计信息 */
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|Total score: %5.3lf | Average score: %5.3lf | The Max score: %5.3lf | The Min score: %5.3lf     |\n", students_total_grade,students_average_grade,students_max_grade,students_min_grade);
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...");
    getchar();

}
void statistics_grade()
{
    system("cls"); // clear the screen
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|                                      The Student List and Grade                             |\n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    /* 输出学生基本信息及其对应的成绩 */
    /* 定义一个结构体指针，用于遍历学生 */
    struct student * each_student = student_list->head;
    /* 定义各项数据变量，用于统计分数 */
    double students_total_grade = 0.0; // 统计总分
    double students_average_grade = 0.0; // 统计平均分
    double students_max_grade = atof(each_student->grade); // 统计最高分
    double students_min_grade = atof(each_student->grade); // 统计最低分
    /* 学生列表行数   */
    int student_list_sn = 1;
    while (each_student != NULL)
    {
        /* 输出学生基本信息及其对应的成绩 */
        printf("|Student SN: %-3d |Major: %-12s|Class: %-10s  |Name: %-10s  |Grade: %-5s     |\n", student_list_sn,each_student->major,each_student->class,each_student->name,each_student->grade);
        printf("|---------------------------------------------------------------------------------------------|\n");
        /* 统计分数 */
        students_total_grade += atof(each_student->grade);
        if (students_max_grade < atof(each_student->grade)) students_max_grade = atof(each_student->grade); // 更新最高分
        if (students_min_grade > atof(each_student->grade)) students_min_grade = atof(each_student->grade); // 更新最低分
        /* 更新指针 */
        each_student = each_student->next;
        /* 更新学生列表行数 */
        student_list_sn++;
    }
    /* 计算各项成绩数据 */
    students_average_grade = students_total_grade / (student_list->total_student - 1); // 计算平均分
    /* 输出统计信息 */
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|Total score: %5.3lf | Average score: %5.3lf | The Max score: %5.3lf | The Min score: %5.3lf     |\n", students_total_grade,students_average_grade,students_max_grade,students_min_grade);
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...");
    getchar();
}
/* --------------------------------------- 统计学生成绩结束 ------------------------------------- */

/* --------------------------------------- 学生成绩排序开始 ------------------------------------- */
void sort_menu()
{

    system("cls"); // clear the screen
    /* 输出提示信息 */
    printf("|------------------------------------------------------------------|\n");
    printf("|                  Welcome to the Score Sort Mode Menu   !         |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("|       1. Sort by ascending order(升序)                            |\n");
    printf("|       2. Sort by descending order(降序)                           |\n");
    printf("|       3. Return to the previous menu                             |\n");
    printf("|       4. Exit                                                    |\n");
    printf("|------------------------------------------------------------------|\n");
    printf("Please input your choice[1-4]: "); // 提示用户输入
    int sort_mode; // 存储选项
    scanf("%d", &sort_mode); // 输入选项
    getchar(); // 吸收回车
    int descend_order,ascend_order; // 降序、升序
    switch (sort_mode) {
        case 1:
            descend_order = 0;
            ascend_order = 1;
            sort_grade(ascend_order,descend_order,1);
            break;
        case 2:
            ascend_order = 0;
            descend_order = 1;
            sort_grade(ascend_order,descend_order,1);
            break;
        case 3:
            login_menu_teacher(); // 返回上一级菜单
        case 4:
            exit(0); // 退出程序
        default:
            printf("Input error,please input again...\n");
            sort_menu();
    }
}
void sort_grade(int ascend_order,int descend_order, int output_all)
{

    system("cls"); // clear the screen
    /* 检查是否没有学生 */
    if (student_list->total_student == 0)
    {
        printf("There is no student!\n");
        printf("Press Enter to continue...\n");
        getchar();
        sort_menu();
    }

    /* 创建一个用于存放链表上各个节点的地址的数组 */
    struct student * student_to_sort_array[student_list->total_student];
    /* 创建一个用于遍历链表的指针 */
    struct student * temp_student_pointer = student_list->head;
    /* 将链表上各个节点的地址存放到数组中 */
    for (int i =0;i < student_list->total_student;i++)
    {
        student_to_sort_array[i] = temp_student_pointer;
        temp_student_pointer = temp_student_pointer->next;
    }

    /* 开始对这个数组进行冒泡排序 */
    for (int i = 1;i <student_list->total_student;i++)
        for (int j = 0;j < student_list->total_student - i;j++)
        {
            if (atof(student_to_sort_array[j]->grade) > atof(student_to_sort_array[j+1]->grade))
            {
                struct student * temp = student_to_sort_array[j];
                student_to_sort_array[j] = student_to_sort_array[j+1];
                student_to_sort_array[j+1] = temp;
            }
        }

    if (descend_order == 1)
    {
        /* 将数组倒序 */
        for (int i = 0;i < student_list->total_student / 2;i++)
        {
            struct student * temp = student_to_sort_array[i];
            student_to_sort_array[i] = student_to_sort_array[student_list->total_student - i - 1];
            student_to_sort_array[student_list->total_student - i - 1] = temp;
        }
    }

    /* 将数组整合到链表中 */
    student_list->head = student_to_sort_array[0];
    for (int i = 0;i <student_list->total_student - 1;i++)
    {
        student_to_sort_array[i]->next = student_to_sort_array[i+1];
    }
    student_to_sort_array[student_list->total_student - 1]->next = NULL;
    student_list->tail = student_to_sort_array[student_list->total_student - 1];

    /* 输出排序后的学生信息 */
    /* 判断是否全部输出 */
    if (output_all) {
        printf("|-------------------------------------------------------------------------------------------|\n");
        printf("|                          The information after sort is as follows:                        |\n");
        printf("|-------------------------------------------------------------------------------------------|\n");
        /* 输出学生基本信息及其对应的成绩 */
        /* 定义一个结构体指针，用于遍历学生 */
        struct student * each_student = student_list->head;
        while (each_student != NULL)
        {
            /* 输出学生基本信息及其对应的成绩 */
            printf("|Major: %-15s    |Class: %-10s     |Name: %-10s       |Grade: %-5s     |\n", each_student->major,each_student->class,each_student->name,each_student->grade);
            printf("|-------------------------------------------------------------------------------------------|\n");
            /* 更新指针 */
            each_student = each_student->next;
        }
    }

    printf("Press Enter to continue...\n");
    getchar();
}

/* --------------------------------------- 学生成绩排序结束 ------------------------------------- */

/* --------------------------------------- 学生成绩修改开始 ------------------------------------- */
void modify_grade()
{
    system("cls"); // clear the screen
    /* 检查是否有学生 */
    if (student_list->total_student == 0)
    {
        printf("There is no student!\n");
        printf("Press Enter to continue...\n");
        getchar();
        login_menu_teacher();
    }
    /* 输出提示信息 */
    printf("|------------------------------------------------------------------|\n");
    printf("|                    Welcome to the Score Modify System !          |\n");
    printf("|------------------------------------------------------------------|\n");
    /* 获取需要修改成绩的学生 */
    struct student * student_need_to_modify_pointer = query_grade();
    /* 修改成绩 */
    printf("Please input the new grade: ");
    fgets(student_need_to_modify_pointer->grade,sizeof(student_need_to_modify_pointer->grade),stdin); // 获取分数
    student_need_to_modify_pointer->grade[strcspn(student_need_to_modify_pointer->grade, "\n")] = '\0'; // 将末尾的换行符替换为\0
    save_students_to_file(); // 保存学生信息到文件
    /* 输出修改成功的提示 */
    printf("Modify successfully!\n");
    printf("Press Enter to continue...\n");
    getchar();
}
/* --------------------------------------- 学生成绩修改结束 ------------------------------------- */

#endif