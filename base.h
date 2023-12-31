#ifndef PROJECT_BASE_H
#define PROJECT_BASE_H
/* All Function prototypes  */

// data_utility.c
void init_question_file();
void load_question_from_file();
void save_questions_to_file();
void init_student_file();
void load_student_list_from_file();
void save_students_to_file();
void delete_student_answer();
struct student * delete_student_answer_by_query();
struct student * delete_student_answer_by_sn();
void backup_data();
void backup_questions();
void backup_students();

// question_operation.c
void add_questions();
void delete_question();
void modify_question();
void show_questions();

// student_operation.c
void student_login_interface();
void answer_questions();

// score_management.c
void compute_grade();
void compute_grade_of_a_student();
void compute_grade_of_all_students();
struct student * query_grade();
struct student * single_field_query();
struct student * multiple_field_query();
void statistics_grade_menu();
void statistics_grade();
void statistics_grade_in_range();
void sort_menu();
void sort_grade(int ascend_order,int descend_order, int output_all);
void modify_grade();

// menu.c
void login_menu();
void login_menu_student();
void login_menu_teacher();

// linsnow.c
void print_author();

#endif //PROJECT_BASE_H
