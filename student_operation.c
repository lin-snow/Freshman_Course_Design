#ifndef HEAD_student_operation
#define HEAD_student_operation

/* ---- Import Essential header files ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_definition.h"
#include "base.h"

#include "data_utility.c"
#include "menu.c"
/* ----------------------------------------*/

/* --------------------------------------- 学生登录开始 ------------------------------------- */
void student_login_interface()
{
    system("cls"); // clear the screen
    student = (struct student *) malloc(sizeof(struct student)); // 开辟一块存储学生信息的内存
    /* 初始化学生信息 */
    strcpy(student->major, "");
    strcpy(student->class, "");
    strcpy(student->name, "");
    /* 将student->answer置为空 */
    for (int i = 0;i < 101;i++)
        student->answers[i][0] = '\0';
    /* 将student->grade置为0 */
    student->grade[0] = '0';
    student->grade[1] = '\0';
    /* 将student->sn置为0 */
    for (int i = 0;i < 101;i++)
        student->sn[i] = 0;
    /* 将next置为NULL */
    student->next = NULL;
    printf("|---------------------------------------------------------------------|\n");
    printf("|                                 Login                               |\n");
    printf("|---------------------------------------------------------------------|\n");
    printf("1. Enter your major: ");
    fgets(student->major, sizeof(student->major), stdin);
    student->major[strcspn(student->major, "\n")] = '\0'; // 去除末尾的换行符
    printf("2. Enter your class: ");
    fgets(student->class, sizeof(student->class), stdin);
    student->class[strcspn(student->class, "\n")] = '\0'; // 去除末尾的换行符
    printf("3. Enter your name: ");
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = '\0'; // 去除末尾的换行符
    /* 对登录信息进行有效性检查 */
    /* 检查专业是否为空 */
    while (strlen(student->major) == 0) {
        printf("Error! Please input again!\n");
        printf("1. Enter your major: ");
        fgets(student->major, sizeof(student->major), stdin);
        student->major[strcspn(student->major, "\n")] = '\0'; // 去除末尾的换行符
    }
    /* 检查班级是否为空 */
    while (strlen(student->class) == 0) {
        printf("Error! Please input again!\n");
        printf("2. Enter your class: ");
        fgets(student->class, sizeof(student->class), stdin);
        student->class[strcspn(student->class, "\n")] = '\0'; // 去除末尾的换行符
    }
    /* 检查姓名是否为空 */
    while (strlen(student->name) == 0) {
        printf("Error! Please input again!\n");
        printf("3. Enter your name: ");
        fgets(student->name, sizeof(student->name), stdin);
        student->name[strcspn(student->name, "\n")] = '\0'; // 去除末尾的换行符
    }
    /* 显示登录信息 */
    printf("|---------------------------------------------------------------------|\n");
    printf("|             Your login information is as follows:                   |\n");
    printf("|---------------------------------------------------------------------|\n");
    printf("| Major: %-40s                     |\n", student->major);
    printf("| Class: %-40s                     |\n", student->class);
    printf("| Name: %-40s                      |\n", student->name);
    printf("|---------------------------------------------------------------------|\n");
    /* 更新登录状态 */
    student_login_status = 0; // 将登录状态设置为已登录
    /* 判断链表是否为空 */
    if (student_list->head == NULL) {
        student_list->head = student; // 将student添加到student_list的头部
        student_list->tail = student; // 将student添加到student_list的尾部
        student_list->total_student++; // 更新student_list的总人数
        student->next = NULL; // 将student的next置为NULL
//        save_students_to_file();
        return;
    } else {
        student_list->tail->next = student; // 将student添加到student_list的尾部
        student_list->tail = student; // 更新student_list的尾部
        student_list->total_student++; // 更新student_list的总人数
        student->next = NULL; // 将student的next置为NULL
//        save_students_to_file();
        return;
    }
}
/* --------------------------------------- 学生登录结束 ------------------------------------- */

/* --------------------------------------- 学生答题开始 ------------------------------------- */
void answer_questions()
{
    system("cls"); //clear the screen
    /* 显示题库中的所有题目 */
    show_questions();
    /* 从键盘获取要答题的题目的序号 */
    int serial_number_to_answer[101] = {0}; // 存储要答题的题目的序号,从第一个格子开始写，依次存放要做的题目的序号，0表示空白
    int i = 0; // 记录输入的题号的个数
    char temp_receive_sn[5]; // 临时存储从键盘接收的题号
    printf("Input the serial number of the question you want to answer\n(Press Enter to answer all questions): ");
    while (1) {
        temp_receive_sn[0] = '\0'; // 清空temp_receive_sn
        fgets(temp_receive_sn, sizeof(temp_receive_sn) ,stdin); // 从键盘接收题号
        if (temp_receive_sn[0] == '\n') break;
        temp_receive_sn[strcspn(temp_receive_sn, "\n")] = '\0'; // 去除末尾的换行符
        serial_number_to_answer[i] = atoi(temp_receive_sn);
        i++;
    }
    /* 判断是否全做 */
    if (serial_number_to_answer[0] == 0) {
        /* 全做，将题库中的所有题目添加到试卷中 */
        for(i = 0;i < question_list->length;i++) {
            serial_number_to_answer[i] = i + 1;
        }
    }
    /* 检查输入的题号是否合法 */
    for (int j = 0;j < i;j++) {
        if (serial_number_to_answer[j] < 1 || serial_number_to_answer[j] > question_list->length) {
            printf("The serial number you input is illegal!\n");
            return;
        }
    }
    /* 生成答题册 */
    printf("Generating the question sheet...\n");
    printf("Press Enter to continue...");
    getchar(); //暂停查看提示信息
    system("cls"); //clear the screen
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("|                                                      Question Sheet                                               |\n");
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    struct question *question_to_answer_pointer = question_list->head;
    double total_paper_score = 0.0; // 记录答题册的总分
    for (int j = 0;j < i;j++) {
        /* 从链表中找到该题目 */
        for (int k = 1; k < serial_number_to_answer[j]; k++) {
            question_to_answer_pointer = question_to_answer_pointer->next;
        }
        /* 计入答题册总分 */
        total_paper_score += atof(question_to_answer_pointer->score);
        /* 显示该题目 */
        printf("| %-100s | %10s |\n", question_to_answer_pointer->question, question_to_answer_pointer->score);
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        /* 更新question_to_answer_pointer的位置 */
        question_to_answer_pointer = question_list->head;
    }
    printf("| Total questions: %-5d                                                            |            Total score : %-5.2lf|\n", i, total_paper_score);
    printf("|-------------------------------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to confirm the question sheet and start answering...");
    getchar(); //暂停查看提示信息
    /* 生成答题册结束 */
    /* 将答题册的信息存储到student->sn中 */
    for (int j = 0;j < i;j++) {
        student->sn[j] = serial_number_to_answer[j];
    }

    /* 正式开始答题 */
    system("cls"); //clear the screen
    for (int m = 0; m < i; m++) {
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("|                                                       Question %3d                                                |\n", student->sn[m]);
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        /* 从链表中找到该题目 */
        for (int k = 1; k < student->sn[m]; k++) {
            question_to_answer_pointer = question_to_answer_pointer->next;
        }
        /* 显示该题目 */
        printf("| %-100s | %10s |\n", question_to_answer_pointer->question, question_to_answer_pointer->score);
        printf("|-------------------------------------------------------------------------------------------------------------------|\n");
        printf("Input your answer: ");
        fgets(student->answers[m], sizeof(student->answers[m]), stdin);
        student->answers[m][strcspn(student->answers[m], "\n")] = '\0'; // 去除末尾的换行符
        /* 检查是否能够做出该题 */
        if (strlen(student->answers[m]) == 0) {
            strcpy(student->answers[m], "$No answer$"); // 将答案设置为"$No answer$"
        }
        /* 更新question_to_answer_pointer的位置 */
        question_to_answer_pointer = question_list->head;
    }
    /* 正式答题结束 */
    printf("Congratulations! You have finished the test!\n");
    printf("Press Enter to continue...");
    getchar(); //暂停查看提示信息
    /* 保存数据到文件 */
    save_students_to_file();
    return;
}
/* --------------------------------------- 学生答题结束 ------------------------------------- */

#endif



