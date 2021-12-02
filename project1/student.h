void register_student(int,char *,float,char);
void search_student(int);
void display_all();
void display_particular(int);
void delete_entry(int);

struct student{
		int idno;
		char name[20];
		float marks;
		char gender;
		struct student *link;
		};
struct student *head;
