#include<stdio.h>
#include<stdlib.h>
#include"linkedlist.h"
int main()
{
 int opt,num,n,n1,n2,c,val,position,i,arr[i];
 while(1)
 {
  printf("\nenter opt\n0.exit\n1.add at begining\n2.delete at begining\n3.add at last\n4.delete at last\n5.display all nodes\n6.count no. of nodes\n7.search a particular node\n8.delete all nodes\n9.delte a particular node\n10.create a list\n11.add node after a node\n12.add node before a node\n13.reverse list\n14.swap two nodes\n15.delete duplicate nodes\n16.selection sort by nodes\n17.selection sort by links\n18.bubble sort by data\n19.bubble sort by links\n");
  scanf("%d",&opt);
  switch(opt)
   {
    case 0: exit(0);

    case 1: printf("\nenter the value:");
            scanf("%d",&num);
            add_at_beg(num);
            break;

    case 2: delete_at_beg();
            break;

    case 3: printf("\nenter the input to add at last:");
            scanf("%d",&num);
            add_last(num);
            break;

    case 4: delete_at_last();
            break;

    case 5: display_all_nodes();
            break;

    case 6: c=count();
            printf("\nno.of nodes in list is :%d\n",c);
            break;
    case 7: printf("\nenter the input to be searched:\n");
            scanf("%d",&val);
            position=search(val);
            printf("\nposition of entered value:%d\n",position);
            break;
   
    case 8: delete_list();
            break;

    case 9: printf("enter the value you want to delte\n");
            scanf("%d",&val);
            delete_particularnode(val);
            break;

    case 10: printf("enter the no of elements\n");
             scanf("%d",&n); 
       for(i=0;i<n;i++)
             {
             printf("enter the element %d\n",i+1);
             scanf("%d",&arr[i]);
             }
             createlist(arr,n);
             break; 

    case 11: printf("enter the node value and enter node to be added after value\n");
             scanf("%d%d",&val,&num);
             add_after(val,num);
             break;

    case 12: printf("enter the node value and enter node to be added before value\n");
             scanf("%d%d",&val,&num);
             add_before(val,num);
             break;

    case 13: reverselist();
             break;

    case 14: printf("enter the node you want to swap:");
             scanf("%d%d",&n1,&n2);
             swapnodes(n1,n2);
             break;

    case 15: delete_duplicate();
             break;

    case 16: selectionsort_data();
             break;

    case 17: selectionsort_links();
             break;

    case 18: bubblesort_data();
             break;
    
    case 19: bubblesort_link();
             break;

    default:printf("\nchoose the vaid option\n");
  }
 }
}
