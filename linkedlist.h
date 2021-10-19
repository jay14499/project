 struct node{
            int data;
            struct node *link;
           };

 void add_at_beg(int );
 void delete_at_beg();
 void add_last(int );
 void delete_at_last();
 void display_all_nodes();
 int count();
 int search(int );
 void delete_list();
 void delete_particularnode(int );
 void createlist(int *,int );
 void add_after(int ,int );
 void add_before(int ,int );
 void reverselist();
 void swapnodes(int ,int );
 void delete_duplicate();
 void selectionsort_data();
 void selectionsort_links();
 void bubblesort_data();
 void bubblesort_link();

struct node *head;
