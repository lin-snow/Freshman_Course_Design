#ifndef PROJECT_GLOBAL_DEFINITION_H
#define PROJECT_GLOBAL_DEFINITION_H
// Global definition

/* ----------------------------------- About questions ------------------------------*/
/* 定义问题的结构体 */
struct question {
    char question[101];
    char answer[101];
    char score[101];
    struct question *next;
};
/* 定义表头的结构体 */
struct store_table {
    char question[101];
    char answer[101];
    char score[101];
};
/* 定义问题的链表 */
struct question_list {
    struct question *head;
    struct question *tail;
    int length;
};

extern struct question_list *question_list;
extern struct store_table *store_table;
/* ----------------------------------- About questions ------------------------------*/

/* ----------------------------------- About students ------------------------------*/
/* 定义学生的结构体 */
struct student {
    char major[101];
    char class[101];
    char name[101];
    char grade[100];
    int sn[101];
    char answers[101][101];
    struct student *next;
};
/* 定义学生的链表 */
struct student_list {
    struct student *head;
    struct student *tail;
    int total_student;
};
/* 定义存储学生表顶部信息栏的结构体 */
struct store_student_table {
    char major[101];
    char class[101];
    char name[101];
    char grade[101];
    char sn[101];
    char answers[101];
};

extern struct student * student;
extern struct store_student_table* store_student_table;
extern struct student_list * student_list;
/* ----------------------------------- About students ------------------------------*/

/* ----------------------------------- About others -------------------------------*/
extern char user_checker[10];
extern int student_login_status;
extern struct student * query_info;

/* ----------------------------------- About others -------------------------------*/



#endif //PROJECT_GLOBAL_DEFINITION_H