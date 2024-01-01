#ifndef HEAD_question_operation
#define HEAD_question_operation

/* ---- Import Essential header files ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_definition.h"
#include "base.h"
/* ----------------------------------------*/


/* --------------------------------------- 添加题目开始 ------------------------------------- */
void add_questions() {
    system("cls"); // 清屏
    /* 添加题目 */
    /* 开辟一块存储新问题的内存 */
    struct question *new_question = (struct question *) malloc(sizeof(struct question));
    /* 检查是否分配成功 */
    if (new_question == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    /* 从键盘获取新问题的信息 */
    printf("Input the question: ");
    fgets(new_question->question, sizeof(new_question->question), stdin);
    /* 将末尾的换行符替换为字符串结束符 */
    new_question->question[strcspn(new_question->question, "\n")] = '\0'; // 去除末尾的换行符
    /* 从键盘获取新问题的答案 */
    printf("Input the answer: ");
    fgets(new_question->answer, sizeof(new_question->answer), stdin);
    /* 将末尾的换行符替换为字符串结束符 */
    new_question->answer[strcspn(new_question->answer, "\n")] = '\0'; // 去除末尾的换行符
    /* 从键盘获取新问题的分数 */
    printf("Input the score: ");
    scanf("%s", new_question->score);
    /* 将末尾的换行符替换为字符串结束符 */
    new_question->score[strcspn(new_question->score, "\n")] = '\0'; // 去除末尾的换行符
    getchar(); // 吸收回车
    /* 将新问题添加到链表中 */
    new_question->next = NULL;
    if (question_list->head == NULL) {
        question_list->head = new_question;
        question_list->tail = new_question;
    } else {
        question_list->tail->next = new_question;
        question_list->tail = new_question;
    }
    /* 更新链表的长度 */
    question_list->length++;
    /* 保存数据到文件 */
    save_questions_to_file();
    /* 显示添加成功的信息 */
    printf("Add successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}
/* --------------------------------------- 添加题目结束 ------------------------------------- */

/* --------------------------------------- 删除题目开始 ------------------------------------- */
void delete_question()
{
    system("cls"); // clear the screen
    /* 显示题库中的所有题目 */
    show_questions();
    /* 输入需要删除的题目前面对应的题号 */
    int serial_number_to_delete;
    printf("Input the serial number of the question you want to delete: ");
    scanf("%d", &serial_number_to_delete);
    getchar(); // 吸收回车
    /* 检查输入的题号是否合法 */
    if (serial_number_to_delete < 1 || serial_number_to_delete > question_list->length) {
        printf("The serial number you input is illegal!\n");
        return;
    }
    /* 从链表中删除该题目 */
    struct question *question_to_delete_pointer = question_list->head;
    if (serial_number_to_delete == 1 && question_list->length == 1) {
        question_list->head = NULL;
        question_list->tail = NULL;
    } else {
        struct question *question_to_delete_pointer_previous = question_list->head;
        for (int i = 1; i < serial_number_to_delete - 1; i++) {
            question_to_delete_pointer_previous = question_to_delete_pointer_previous->next;
        }
        question_to_delete_pointer = question_to_delete_pointer_previous->next;
        question_to_delete_pointer_previous->next = question_to_delete_pointer->next;
    }
    /* 释放内存 */
    free(question_to_delete_pointer);
    /* 更新链表的长度 */
    question_list->length--;
    /* 保存数据到文件 */
    save_questions_to_file();
    /* 显示删除成功的信息 */
    printf("Delete successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}
/* --------------------------------------- 删除题目结束 ------------------------------------- */

/* --------------------------------------- 修改题目开始 ------------------------------------- */
void modify_question()
{
    system("cls"); // clear the screen
    /* 显示题库中的所有题目 */
    show_questions();
    /* 从键盘获取想要修改的题目 */
    char question_to_modify[101];
    printf("Input the question's Serial number you want to modify: ");
    fgets(question_to_modify, sizeof(question_to_modify), stdin);
    /* 将末尾的换行符替换为字符串结束符 */
    question_to_modify[strcspn(question_to_modify, "\n")] = '\0'; // 去除末尾的换行符
    /* 将输入的 Serial Number 转换为 int 类型 */
    int serial_number_to_modify = atoi(question_to_modify);
    /* 检查输入的题号是否合法 */
    if (serial_number_to_modify < 1 || serial_number_to_modify > question_list->length) {
        printf("The serial number you input is illegal!\n");
        return;
    }
    /* 从链表中找到该题目 */
    struct question *question_to_modify_pointer = question_list->head;
    for (int i = 1; i < serial_number_to_modify; i++) {
        question_to_modify_pointer = question_to_modify_pointer->next;
    }
    /* 显示该题目的信息 */
    printf("The question you want to modify is: \n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|Serial number|                        Questions                   |      Answer     |  Score |\n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|%-13d|%-52s|%-17s|%-8s|\n", serial_number_to_modify, question_to_modify_pointer->question, question_to_modify_pointer->answer, question_to_modify_pointer->score);
    printf("|---------------------------------------------------------------------------------------------|\n");
    /* 从键盘获取修改后的题目 */
    char question_modified[101];
    printf("Input the modified question(Press Enter to keep it originally.): ");
    fgets(question_modified, sizeof(question_modified), stdin);
    /* 将末尾的换行符替换为字符串结束符 */
    question_modified[strcspn(question_modified, "\n")] = '\0'; // 去除末尾的换行符
    /* 从键盘获取修改后的答案 */
    char answer_modified[101];
    printf("Input the modified answer(Press Enter to keep it originally.): ");
    fgets(answer_modified, sizeof(answer_modified), stdin);
    /* 将末尾的换行符替换为字符串结束符 */
    answer_modified[strcspn(answer_modified, "\n")] = '\0'; // 去除末尾的换行符
    /* 从键盘获取修改后的分数 */
    char score_modified[101];
    printf("Input the modified score(Press Enter to keep it originally.): ");
    scanf("%s", score_modified);
    getchar(); // 吸收回车
    /* 将末尾的换行符替换为字符串结束符 */
    score_modified[strcspn(score_modified, "\n")] = '\0'; // 去除末尾的换行符
    /* 修改题目 */
    if(strlen(question_modified) != 0) strcpy(question_to_modify_pointer->question, question_modified);
    if(strlen(answer_modified) != 0) strcpy(question_to_modify_pointer->answer, answer_modified);
    if (strlen(score_modified) != 0) strcpy(question_to_modify_pointer->score, score_modified);
    /* 显示修改成功的信息 */
    printf("Modify successfully!\n");
    /* 显示修改之后的题目 */
    printf("The question after modified is: \n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|Serial number|                        Questions                   |      Answer     |  Score |\n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|%-13d|%-52s|%-17s|%-8s|\n", serial_number_to_modify, question_to_modify_pointer->question, question_to_modify_pointer->answer, question_to_modify_pointer->score);
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...\n");
    getchar();
    /* 保存数据到文件 */
    save_questions_to_file();
}
/* --------------------------------------- 修改题目结束 ------------------------------------- */

/* --------------------------------------- 查看题目开始 ------------------------------------- */
void show_questions()
{
    system("cls"); // clear the screen
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|Serial number|                        Questions                   |      Answer     |  Score |\n");
    printf("|---------------------------------------------------------------------------------------------|\n");
    /* 从链表中读取数据并显示 */
    struct question *question_to_show = question_list->head;
    int serial_number = 1;
    while (question_to_show != NULL) {
        if (strcmp(user_checker, "student") == 0) {
            printf("|%-13d|%-52s|%-17s|%-8s|\n", serial_number, question_to_show->question, " ***************", question_to_show->score);
        } else {
            printf("|%-13d|%-52s|%-17s|%-8s|\n", serial_number, question_to_show->question, question_to_show->answer, question_to_show->score);
        }
        question_to_show = question_to_show->next;
        serial_number++;
    }
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("|                                     Total %-3d questions!                                    |\n", question_list->length);
    printf("|---------------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...");
    getchar(); // 暂停显示题目
}

/* --------------------------------------- 查看题目结束 ------------------------------------- */

#endif