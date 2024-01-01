#ifndef HEAD_data_utility
#define HEAD_data_utility

/* ---- Import Essential header files ---- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global_definition.h"
#include "base.h"

#include "score_management.c"
#include "question_operation.c"
/* ----------------------------------------*/

/* -------------------------------- 从加载题目开始 -------------------------------- */
void load_question_from_file()
{
    /* ----------------------- 检查数据文件开始 ------------------------ */
    /* 检查是否有questions.txt文件 */
    FILE *fp_check = fopen("questions.txt", "r");
    /* 如果没有questions.txt文件，则创建一个 */
    if (fp_check == NULL) {
        init_question_file();
    }
    /* 关闭文件 */
    fclose(fp_check);
    /* ----------------------- 检查数据文件结束 ------------------------ */

    /* ----------------------- 加载数据开始 --------------------------- */
    /* Load data from questions.txt,students.txt */
    /*  显示加载数据的信息 */
    printf("Loading data from questions.txt,please wait a moment! \n");
    /*  读取文件中的题目 */
    FILE *fp = fopen("questions.txt", "r");
    if (fp == NULL) {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    /* 给链表分配空间 */
    question_list = (struct question_list *) malloc(sizeof(struct question_list));
    /* 检查是否分配成功 */
    if (question_list == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    /* 初始化链表 */
    question_list->head = NULL;
    question_list->tail = NULL;
    question_list->length = 0;
    /* 将questions.txt中的表格中的开头一行的"Questions"、"Answer"、“Score” */
    store_table = (struct store_table *) malloc(sizeof(struct store_table));
    /* 检查是否分配成功 */
    if (store_table == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    /* 读取题目 */
    fscanf(fp,"|%100[^|]|", store_table->question);
    /* 读取答案 */
    fscanf(fp,"|%100[^|]|", store_table->answer);
    /* 读取分数 */
    fscanf(fp,"|%100[^|]|", store_table->score);
    /* 读取换行符，达到跳过换行符的作用 */
    fscanf(fp,"\n");

    /* 读取题目 */
    while (!feof(fp)) {
        struct question *question = (struct question *) malloc(sizeof(struct question));
        /* 检查是否分配成功 */
        if (question == NULL) {
            perror("Memory allocation failed!");
            exit(EXIT_FAILURE);
        }
        /* 读取题目 */
        fscanf(fp,"|%100[^|]|", question->question);
        /* 读取答案 */
        fscanf(fp,"|%100[^|]|", question->answer);
        /* 读取分数 */
        fscanf(fp,"|%100[^|]|", question->score);
        /* 读取换行符，达到跳过换行符的作用 */
        fscanf(fp,"\n");
        /* 将题目添加到链表中 */
        if (question_list->head == NULL) {
            question_list->head = question;
            question_list->tail = question;
        } else {
            question_list->tail->next = question;
            question_list->tail = question;
        }
        /* 更新链表的长度 */
        question_list->length++;
    }
    /* 给出提示信息 */
    printf("Total %d questions have been loaded successfully!\n", question_list->length);
    /* 关闭文件 */
    fclose(fp);
    /* ----------------------- 加载数据结束 --------------------------- */

}
/* -------------------------------- 加载题目结束 -------------------------------- */

/* ------------------------------- 初始化数据文件开始 -------------------------------*/
void init_question_file()
{
    /* 初始化一份题目文件--questions.txt */
    /* 1.创建文件 */
    FILE *fp = fopen("questions.txt", "w");
    /* 检查是否创建成功 */
    if (fp == NULL) {
        perror("Create file failed!");
        exit(EXIT_FAILURE);
    }
    /* 2.写入表格的开头一行的"Questions"、"Answer"、“Score” */
    fprintf(fp, "|%s||%s||%s|\n", "Questions", "Answer", "Score");
    /* 3.关闭文件 */
    fclose(fp);
}
/* ------------------------------- 初始化数据文件结束 -------------------------------*/

/* -------------------------------- 保存数据文件开始 --------------------------------*/
void save_questions_to_file()
{
    /* 1.创建一块内存用来临时保存每一个节点的数据 */
    struct question * data_saver = question_list->head;
    /* 检查是否分配成功 */
    if (data_saver == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    /* 2.打开文件 */
    FILE *fp = fopen("questions.txt", "w");
    /* 检查是否打开成功 */
    if (fp == NULL) {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    /* 3.将表格的开头一行的"Questions"、"Answer"、“Score”写入文件 */
    fprintf(fp, "|%s||%s||%s|\n", store_table->question, store_table->answer, store_table->score);
    /* 4.将链表中的数据写入文件 */
    while (data_saver != NULL) {
        fprintf(fp, "|%s||%s||%s|\n", data_saver->question, data_saver->answer, data_saver->score);
        data_saver = data_saver->next;
    }
    /* 5.关闭文件 */
    fclose(fp);
    /* 6.给出提示信息 */
    printf("Save all questions to questions.txt successfully!\n");
    /* 7.释放内存 */
    free(data_saver);
}
/* -------------------------------- 保存数据文件结束 --------------------------------*/

/* -------------------------------- 加载学生列表开始 --------------------------------*/
void load_student_list_from_file() {
    /* ----------------------- 检查数据文件开始 ------------------------ */
    /* 检查是否有students.txt文件 */
    FILE *fp_check = fopen("students.txt", "r");
    /* 如果没有students.txt文件，则创建一个 */
    if (fp_check == NULL) {
        init_student_file();
    }
    /* ----------------------- 检查数据文件结束 ------------------------ */

    /* ------------------------- 加载数据开始 ------------------------- */
    /* 打开数据文件--students.txt */
    FILE *fp = fopen("students.txt", "r");
    /* 检查是否打开成功 */
    if (fp == NULL) {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    /* 将文件指针指向文件的第一行开头 */
    fseek(fp, 0, SEEK_SET);
    /* 从students.txt中加载数据 */
    /*  显示加载数据的信息 */
    printf("Loading data from students.txt,please wait a moment! \n");
    /* 为学生链表分配内存空间 */
    student_list = (struct student_list *) malloc(sizeof(struct student_list));
    /* 检查是否分配成功 */
    if (student_list == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    /* 初始化学生链表 */
    student_list->head = NULL; // 初始化头指针
    student_list->tail = NULL; // 初始化尾指针
    student_list->total_student = 0; // 初始化学生总数
    /* 先将文件指针移动到第二行开头，跳过表格顶行信息 */
    store_student_table = (struct store_student_table *) malloc(sizeof(struct store_student_table));
//    /* 检查是否分配成功 */
    if (store_student_table == NULL) {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    fscanf(fp,"|%100[^|]|", store_student_table->major); // 跳过表格顶行信息
    fscanf(fp,"|%100[^|]|", store_student_table->class); // 跳过表格顶行信息
    fscanf(fp,"|%100[^|]|", store_student_table->name);  // 跳过表格顶行信息
    fscanf(fp,"|%100[^|]|", store_student_table->grade); // 跳过表格顶行信息
    fscanf(fp,"|%100[^|]|", store_student_table->sn);    // 跳过表格顶行信息
    fscanf(fp,"|%100[^|]|", store_student_table->answers); // 跳过表格顶行信息
    fscanf(fp,"\n"); // 跳过换行符
    /* 开始读取学生信息 */

    while(!feof(fp))
    {
        /* 分配内存空间，用于存储表中每个学生的信息 */
        struct student * co_student = (struct student *) malloc(sizeof(struct student));
        /* 检查是否分配成功 */
        if (co_student == NULL) {
            perror("Memory allocation failed!");
            exit(EXIT_FAILURE);
        }
        /* 初始化学生信息 */
        strcpy(co_student->major, "");
        strcpy(co_student->class, "");
        strcpy(co_student->name, "");
        strcpy(co_student->grade, "");
        /* 将student->answer置为空 */
        for (int i = 0;i < 101;i++)
            co_student->answers[i][0] = '\0';
        /* 将student->grade置为0 */
        co_student->grade[0] = '0'; // 初始化学生的成绩为0
        co_student->grade[1] = '\0'; // 初始化学生的成绩为0
        /* 将student->sn置为0 */
        for (int i = 0;i < 101;i++)
            co_student->sn[i] = 0;
        /* 将 next 置为 NULL */
        co_student->next = NULL;
        /* 读取学生的信息 */
        fscanf(fp,"|%100[^|]|", co_student->major);
        fscanf(fp,"|%100[^|]|", co_student->class);
        fscanf(fp,"|%100[^|]|", co_student->name);
        fscanf(fp,"|%100[^|]|", co_student->grade);
        /* 开始读取学生的答案序列 */
        /* 现将文件指针指到答题序列开头 */
        /* 读取答题序列 */
        int i = 0;
        int current_char = fgetc(fp); // 获取当前文件指针指向的字符,跳过SN of answered question的第一个分割线
        current_char = fgetc(fp); // 更新当前文件指针指向的字符
        fseek(fp, -1, SEEK_CUR); // 将文件指针指回当前位置
        while (current_char != '|') {
            char temp_sn_number[6]; // 临时存放题号的字符串
            fscanf(fp,"*%5[^*]*", temp_sn_number); // 读取题号
            /* 将读取到字符串题号转变为整形数字 */
            co_student->sn[i] = atoi(temp_sn_number);
            i++;
            current_char = fgetc(fp); // 更新当前文件指针指向的字符
            fseek(fp, -1, SEEK_CUR); // 将文件指针指回当前位置
        }
        current_char = fgetc(fp); // 获取当前文件指针指向的字符,跳过SN of answered question的第二个分割线
        /* 开始读取学生的答案 */
        /* 现将文件指针指到答案开头 */
        fgetc(fp); //跳过Answers的第一个分割线
        /* 读取答案 */
        i = 0;
        current_char = fgetc(fp); // 获取当前文件指针指向的字符
        fseek(fp, -1, SEEK_CUR); // 将文件指针指回当前位置
        while (current_char != '|') {
            fscanf(fp,"*%100[^*]*", co_student->answers[i]); // 读取答案
            i++;
            current_char = fgetc(fp); // 更新当前文件指针指向的字符
            fseek(fp, -1, SEEK_CUR); // 将文件指针指回当前位置
        }
        fgetc(fp); //跳过Answers的第二个分割线
        /* 将学生信息添加到链表中 */
        if (student_list->head == NULL) {
            student_list->head = co_student;
            student_list->tail = co_student;
        } else {
            student_list->tail->next = co_student;
            student_list->tail = co_student;
        }
        /* 更新链表的长度 */
        student_list->total_student++;
        /* 将文件指针指向下一行 */
        fscanf(fp,"\n");
    }
    /* 给出提示信息 */
    printf("Total %d students have been loaded successfully!\n", student_list->total_student);
    /* 关闭文件 */
    fclose(fp);
    /* ------------------------- 加载数据开始 ------------------------- */
}
/* -------------------------------- 加载学生列表结束 --------------------------------*/

/* ------------------------------- 初始化数据文件开始 -------------------------------*/
void init_student_file()
{
    /* 初始化一份学生文件--students.txt */
    /* 1.创建文件 */
    FILE *fp = fopen("students.txt", "w");
    /* 检查是否创建成功 */
    if (fp == NULL) {
        perror("Create file failed!");
        exit(EXIT_FAILURE);
    }
    /* 2.写入表格的开头一行的"Major"、"Class"、“Name”、“Answers”、"SN of answered question"、“Grade” */
    fprintf(fp, "|%s||%s||%s||%s||%s||%s|\n", "Major", "Class", "Name", "Grade", "SN of answered question(Each SN is divided by '*')","Answers (Each answer is divided by '*')");
    /* 3.关闭文件 */
    fclose(fp);
}
/* ------------------------------- 初始化数据文件结束 -------------------------------*/

/* -------------------------------- 保存数据文件开始 --------------------------------*/
void save_students_to_file()
{
    /* 创建一个用于指向学生的指针 */
    struct student * student_data_saver = student_list->head;
    /* 打开文件 */
    FILE *fp = fopen("students.txt", "w");
    /* 检查是否打开成功 */
    if (fp == NULL) {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    /* 将指针设置到文件开头 */
    fseek(fp, 0, SEEK_SET);
    /* 将表格的开头一行的"Major"、"Class"、“Name”、“Grade”、“Answers”、"SN of answered question"、写入文件 */
    fprintf(fp, "|%s||%s||%s||%s||%s||%s|\n", store_student_table->major, store_student_table->class, store_student_table->name, store_student_table->grade, store_student_table->sn, store_student_table->answers);
    /* 将链表中的数据写入文件 */
    while (student_data_saver != NULL) {
        fprintf(fp, "|%s||%s||%s||%s|", student_data_saver->major, student_data_saver->class, student_data_saver->name, student_data_saver->grade);
        /* 将答题序列写入文件 */
        fprintf(fp, "|"); // 写入SN of answered question的第一个分割线
        for (int i = 0;i <101;i++) {
            if (student_data_saver->sn[i] != 0) {
                fprintf(fp, "*%d*", student_data_saver->sn[i]);
            }
        }
        fprintf(fp, "|"); // 写入SN of answered question的第二个分割线
        /* 将答案写入文件 */
        fprintf(fp, "|"); // 写入Answers的第一个分割线
        for (int i = 0;i <101;i++) {
            /* 如果答案不为空，则写入答案 */
            if (strlen(student_data_saver->answers[i]) != 0) {
                fprintf(fp, "*%s*", student_data_saver->answers[i]); // 写入答案
            }
        }
        fprintf(fp, "|"); // 写入Answers的第二个分割线
        /* 将文件指针指向下一行 */
        fprintf(fp, "\n");
        /* 更新指针 */
        student_data_saver = student_data_saver->next;
    }
    /* 关闭文件 */
    fclose(fp);
}
/* -------------------------------- 保存数据文件结束 --------------------------------*/

/* -------------------------------- 删除学生答题信息开始 --------------------------------*/
void delete_student_answer()
{
    system("cls"); // clear the screen
    /* 显示进行删除操作的提示信息 */
    printf("Please choose the way to delete the student's answer!\n");
    printf("|---------------------------------------------------------------------|\n");
    printf("|       1. Delete by student's answer by query                        |\n");
    printf("|       2. Delete by student's answer by serial number                |\n");
    printf("|       3. Return to the teacher menu                                 |\n");
    printf("|       4. Exit                                                       |\n");
    printf("|---------------------------------------------------------------------|\n");
    /* 从键盘获取选择 */
    int delete_choice;
    printf("Please input your choice[1-4]: ");
    scanf("%d", &delete_choice);
    getchar(); // 吸收上一次输入的回车符
    /* 根据选择进行操作 */
    struct student * student_to_delete_pointer = NULL;
    switch (delete_choice) {
        case 1:
            student_to_delete_pointer = delete_student_answer_by_query();
            break;
        case 2:
            student_to_delete_pointer = delete_student_answer_by_sn();
            break;
        case 3:
            return;
        case 4:
            exit(0);
        default:
            printf("Error! Please input again!\n");
            delete_student_answer();

    }

    system("cls"); // clear the screen
    /* 检查是否找到该学生 */
    if (student_to_delete_pointer == NULL) {
        printf("Can't find the student!\n");
        printf("Press Enter to continue");
        getchar();
        return;
    }
    /* 如果找到该学生，显示该学生的信息及其答案 */
    /* 显示学生的答案及其对应的分数 */
    printf("|--------------------------------------------------------------------------------------|\n");
    printf("|                 The student's answers and scores are as follows:                     |\n");
    printf("|--------------------------------------------------------------------------------------|\n");
    printf("| Major: %-17s    | Class: %-12s    |  Name: %-12s           |\n", student_to_delete_pointer->major, student_to_delete_pointer->class, student_to_delete_pointer->name);
    printf("|--------------------------------------------------------------------------------------|\n");

    /* 显示学生做的题目的序列及其对应的答案 */
    for (int i =0;student_to_delete_pointer->sn[i] != 0;i++)
    {
        /* 显示学生作答的题目 */
        struct question * question_accord_to_sn_pointer = question_list->head;
        for (int j = 1;j < student_to_delete_pointer->sn[i];j++)
        {
            question_accord_to_sn_pointer = question_accord_to_sn_pointer->next;
        }
        printf("| SN: %-3d | Question: %-25s | Answer: %-15s | Score: %-3s |\n", student_to_delete_pointer->sn[i],question_accord_to_sn_pointer->question,student_to_delete_pointer->answers[i],question_accord_to_sn_pointer->score);
    }
    printf("|--------------------------------------------------------------------------------------|\n");
    printf("Press Enter to continue...\n");
    getchar();
    /* 输入想要删除学生的答案对应的题目的sn */
    /* 获取该学生的答题数 */
    int total_answered_question = 0;
    for (int i = 0;student_to_delete_pointer->sn[i] != 0;i++)
    {
        total_answered_question++;
    }
    /* 输入想要删除的题目的sn */
    int sn_to_delete[101] = {0};
    printf("Input the SN of the question you want to delete(Press Enter after each input): ");
    for (int i = 0;i < total_answered_question;i++)
    {
        char temp_sn[5] = "";
        fgets(temp_sn, sizeof(temp_sn), stdin);
        if(temp_sn[0] == '\n') break; // 如果输入的是回车，则跳出循环
        temp_sn[strcspn(temp_sn, "\n")] = '\0'; // 去除末尾的换行符
        /* 转换为整形 */
        int int_sn = atoi(temp_sn);
        /* 检查输入的sn是否合法 */
        int isSNExit = 0;
        int k; // 用于遍历学生的sn,记录当前遍历到的sn的下标
        for(k = 0;k < total_answered_question;k++)
        {
            if (student_to_delete_pointer->sn[k] == int_sn)
            {
                isSNExit = 1;
                break;
            }
        }
        if (isSNExit == 0) {
            printf("The SN you input is illegal!\n");
            printf("Press Enter to continue...");
            getchar();
            /* 返回当前函数 */
            delete_student_answer();
        }
        /* 输入合法，存入数组 */
        sn_to_delete[i] = int_sn;
    }
    /* 删除该学生的答案，并将其保存到stu1.txt中 */
    /* 检查是否有stu1.txt文件 */
    FILE *fp_check = fopen("stu1.txt", "r");
    /* 如果没有stu1.txt文件，则创建一个 */
    if (fp_check == NULL) {
        FILE *fp = fopen("stu1.txt", "w");
        fprintf(fp, "|%s||%s||%s||%s||%s|\n", store_student_table->major, store_student_table->class, store_student_table->name, store_student_table->sn, store_student_table->answers);
        fclose(fp);
    }
    fclose(fp_check);
    /* 打开stu1.txt文件 */
    FILE *fp = fopen("stu1.txt", "a");
    /* 检查是否打开成功 */
    if (fp == NULL) {
        perror("Open file failed!");
        exit(EXIT_FAILURE);
    }
    int total_sn_to_delete = 0;
    for (int i = 0;sn_to_delete[i] != 0;i++)
    {
        total_sn_to_delete++;
    }
    /* 将学生基本信息及其被删除的答案和被删除答案的对应的题目内容和题目的sn写入stu1.txt中 */
    fprintf(fp, "|%s||%s||%s|", student_to_delete_pointer->major, student_to_delete_pointer->class, student_to_delete_pointer->name);
    /* 将被删除的答案对应题目的序列和被删除的答案写入文件 */
    fprintf(fp, "|"); // 写入SN of answered question的第一个分割线
    for (int i = 0;i < total_sn_to_delete;i++) {
        fprintf(fp, "*%d*", sn_to_delete[i]);
    }
    fprintf(fp, "|"); // 写入SN of answered question的第二个分割线
    /* 将被删除的答案写入文件 */
    fprintf(fp, "|"); // 写入Answers的第一个分割线
    for (int i = 0;i < total_sn_to_delete;i++) {
        fprintf(fp, "*%s*", student_to_delete_pointer->answers[sn_to_delete[i] - 1]); // 写入答案
    }
    fprintf(fp, "|"); // 写入Answers的第二个分割线
    /* 将文件指针指向下一行 */
    fprintf(fp, "\n");
    /* 将students_list中对应的学生的答案删除 */
    for (int i = 0;i < total_sn_to_delete;i++)
    {
        for (int j = 0;j < total_answered_question;j++)
        {
            if (student_to_delete_pointer->sn[j] == sn_to_delete[i])
            {
                student_to_delete_pointer->sn[j] = 0;
                student_to_delete_pointer->answers[j][0] = '\0';
            }
        }
    }
    /* 将学生的答案重新保存到students.txt中 */
    save_students_to_file();
    /* 关闭文件 */
    fclose(fp);
    /* 给出提示信息 */
    printf("Delete successfully!\n");
    /* 暂停查看提示信息 */
    printf("Press Enter to continue...");
    getchar();
}

struct student * delete_student_answer_by_query()
{
     system("cls"); // clear the screen
    /* 显示提示信息 */
    struct student *student_to_delete_answer_pointer = NULL;
    student_to_delete_answer_pointer  = query_grade();
    /* 检查是否找到该学生 */
    if (student_to_delete_answer_pointer == NULL) {
        printf("Can't find the student!\n");
        return NULL;
    }
    /* 返回该学生的指针 */
    return student_to_delete_answer_pointer;
}

struct student * delete_student_answer_by_sn()
{
    system("cls"); // clear the screen
    /* 显示所有学生及其答案 */
    statistics_grade();
    /* 输入需要删除的学生的序号 */
    int serial_number_to_delete;
    printf("Input the Student SN you want to delete: ");
    scanf("%d", &serial_number_to_delete);
    getchar(); // 吸收回车
    /* 检查输入的序号是否合法 */
    if (serial_number_to_delete < 1 || serial_number_to_delete > student_list->total_student) {
        printf("The serial number you input is illegal!\n");
        printf("Press Enter to continue...");
        getchar();
        /* 返回当前函数 */
        return delete_student_answer_by_sn();
    }
    /* 找到该学生 */
    struct student *student_to_delete_pointer = student_list->head;
    for (int i = 1; i < serial_number_to_delete; i++) {
        student_to_delete_pointer = student_to_delete_pointer->next;
    }
    /* 返回该学生的指针 */
    return student_to_delete_pointer;
}
/* -------------------------------- 删除学生答题信息结束 --------------------------------*/

/* --------------------------------备份当前函数开始 --------------------------------*/
void backup_data()
{
    /* 清屏   */
    system("cls"); // clear the screen
    /* 显示备份菜单 */
    printf("----------------------------- Backup Data -----------------------------\n");
    printf("|                                                                     |\n");
    printf("|       1. Backup all data (include questions.txt students.txt)       |\n");
    printf("|       2. Backup questions.txt                                       |\n");
    printf("|       3. Backup students.txt                                        |\n");
    printf("|       4. Return to the teacher menu                                 |\n");
    printf("|       5. Exit                                                       |\n");
    printf("|                                                                     |\n");
    printf("-----------------------------------------------------------------------\n");
    /* 从键盘获取选择 */
    int backup_choice;
    printf("Please input your choice[1-4]: ");
    scanf("%d", &backup_choice);
    getchar(); // 吸收上一次输入的回车符

    switch (backup_choice) {
        case 1:
            /* backup all data */
            /* backup questions */
            backup_questions();
            /* backup students */
            backup_students();
            break;
        case 2:
            /* backup questions */
            backup_questions();
            break;
        case 3:
            /* backup students */
            backup_students();
            break;
        case 4:
            return;
        case 5:
            exit(0);
    }
}
/* backup_questions */
void backup_questions()
{
    /* 清屏   */
    system("cls"); // clear the screen
    /* 显示当前需要备份的数据 */
    printf("The data you want to backup is as follows: \n");
    show_questions();
    /* 然后将数据备份到backup_questions.txt中 */
    /* 将questions以questions_backup.txt文件备份到backup文件夹中 */
    /* 检查是否有backup文件夹 */
    FILE *fp_check = fopen("backup", "r");
    /* 如果没有backup文件夹，则创建一个 */
    if (fp_check == NULL) {
        system("mkdir backup");
    }
    fclose(fp_check);
    /* 将questions.txt文件备份到backup文件夹中 */
    save_questions_to_file();
    system("copy questions.txt backup\\questions_backup.txt");
    /* 给出提示信息 */
    printf("Backup successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}
/* backup_students */
void backup_students()
{
    /* 清屏   */
    system("cls"); // clear the screen
    /* 显示当前需要备份的数据 */
    printf("The data you want to backup is as follows: \n");
    statistics_grade();
    /* 然后将数据备份到backup_students.txt中 */
    /* 将students以students_backup.txt文件备份到backup文件夹中 */
    /* 检查是否有backup文件夹 */
    FILE *fp_check = fopen("backup", "r");
    /* 如果没有backup文件夹，则创建一个 */
    if (fp_check == NULL) {
        system("mkdir backup");
    }
    fclose(fp_check);
    /* 将students.txt文件备份到backup文件夹中 */
    save_students_to_file();
    system("pause");
    system("copy students.txt backup\\students_backup.txt");
    /* 给出提示信息 */
    printf("Backup successfully!\n");
    printf("Press Enter to continue...");
    getchar();
}
/* --------------------------------备份当前函数结束 --------------------------------*/


#endif