#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define Length 200

typedef struct book
{
	char Isbn[Length]; 
	char authors[Length];
	char book_name[Length];
	int book_amount;
	int book_left;
	struct book *next;
}Book;

Book *head_book=NULL;




void print_list_book(void)
{
	Book *temp=head_book;
	int i=1;
	if(head_book==NULL)
	{
		printf("\t\t\t\tList is empty!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			printf("\t\t\t\t***%d***\n",i);
			printf("\t\t\t\t%s\n",temp->Isbn);
			printf("\t\t\t\t%s\n",temp->authors);
			printf("\t\t\t\t%s\n",temp->book_name);
			printf("\t\t\t\t%d\n",temp->book_amount);
			printf("\t\t\t\t%d\n",temp->book_left);
			i++;
			temp=temp->next;
		}
	}
}



void add_node_book(Book **newbook)
{
	(*newbook)->next=NULL;
	Book *temp=head_book;
	if(head_book==NULL)
	{
		head_book=*newbook;
	}
	else
	{
		while(temp->next!=NULL)
		{
			temp=temp->next;
		}
		temp->next=*newbook;
	}
}

int count_lines_book(void)
{
	FILE *f=fopen("books.csv","r");
	int count=0,size=0;
	char c;
	while(!feof(f))
	{
		c=getc(f);
		if(c==';')
		{
			count++;
		}
	}
	size=(count/5);
	fclose(f);
	return size;
}
void readfile_book(void)
{
	Book *newbook;
	int loop=0;
	int row=count_lines_book();
	char c;
	char Isbn[Length];
	char authors[Length];
	char book_name[Length];
	char book_amount_c[Length];
	char book_left_c[Length];
	FILE *f=fopen("books.csv","r");
	int k=0,i=0;
	if(f==NULL)
	{
		printf("Cannnot find the file\n");
		return;
	}
	for(i=0;i<row;i++)
	{
		fscanf(f,"%[^;];%[^;];%[^;];%[^;];%[^;];\n",Isbn,authors,book_name,book_amount_c,book_left_c);
		newbook=(Book*)malloc(sizeof(Book));
		strcpy(newbook->Isbn,Isbn);
		strcpy(newbook->authors,authors);
		strcpy(newbook->book_name,book_name);
		newbook->book_amount=0;
		for(loop=0;loop<strlen(book_amount_c);loop++)
		{
			newbook->book_amount=newbook->book_amount*10+(book_amount_c[loop]-'0');
		}
		newbook->book_left=0;
		for(loop=0;loop<strlen(book_left_c);loop++)
		{
			newbook->book_left=newbook->book_left*10+(book_left_c[loop]-'0');
		}
		add_node_book(&newbook);
	}
	fclose(f);
}


int search_book(char s[])
{
	Book *temp=head_book;
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,s)==0)
		{
			printf("Such book exists!\n");
			return -1;
		}
		else
		{
			temp=temp->next;
		}
	}
}

void add_book(void)
{
	char Isbn[Length];
	char authors[Length];
	char book_name[Length];
	int book_amount;
	int book_left;
	printf("Isbn:");
	scanf("%s",Isbn);
	getchar();
	if(search_book(Isbn)==-1)
	{
		return;
	}
	printf("Authors:");
	scanf("%[^\n]s",authors);
	getchar();
	printf("Book name:");
	scanf("%[^\n]s",book_name);
	printf("Amount of book:");
	scanf("%d",&book_amount);
	book_left=book_amount;
	Book *newbook=(Book*)malloc(sizeof(Book));
	strcpy(newbook->Isbn,Isbn);
	strcpy(newbook->authors,authors);
	strcpy(newbook->book_name,book_name);
	newbook->book_amount=book_amount;
	newbook->book_left=book_left;
	add_node_book(&newbook);
}




int Book_menu()
{
	int c;
	printf("\t\t\t\t\t\t*MENU*\n");
	printf("\t\t\t\t\t1->Add book\n");
	printf("\t\t\t\t\t2->Delete book\n");
	printf("\t\t\t\t\t3->Edit data of book\n");
	printf("\t\t\t\t\t4->Edit amount of book\n");
	printf("\t\t\t\t\t5->Print list\n");
	printf("\t\t\t\t\t6->Save and exit\n");
	printf("\t\t\t\t\tInput->");
	scanf("%d",&c);
	return c;
}


void delete_book(void)
{
	char str[Length];
	printf("Isbn of book:");
	scanf("%s",str);
	Book *prev=NULL,*temp=head_book;
	while(temp!=NULL)
	{
		if(strcmp(head_book->Isbn,str)==0)
		{
			temp=head_book->next;
			free(head_book);
			head_book=temp;
		}
		else
		{
			if(strcmp(temp->Isbn,str)==0)
			{
				prev->next=temp->next;
				free(temp);
				temp=prev->next;
			}
			else
			{
				prev=temp;
				temp=temp->next;
			}
		}
	}
}

int choose_f_book()
{
	int c;
	printf("1->YES;0->NO\n");
	scanf("%d",&c);
	return c;
}


void edit_book(void)
{
	Book *temp=head_book;
	printf("#Changing some data#\n");
	char str[Length];
	printf("ISBN of book:");
	scanf("%s",str);
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,str)==0)
		{
			printf("Want to change author name?\n");
			if(choose_f_book()==1)
			{
				char authors[Length];
				printf("Changing the author name:");
				scanf("%s",authors);
				strcpy(temp->authors,authors);		
			}
			printf("Want to change book name?\n");
			if(choose_f_book()==1)
			{
				char book_name[Length];
				printf("Changing the book name:");
				scanf("%s",book_name);
				strcpy(temp->book_name,book_name);
			}
			printf("Successfull changing!\n");
			return;
		}
		else
		{
			temp=temp->next;
		}
	}
	printf("Sorry,but such a book doesn't exist!\n");
}

void show_number_accessibe_book(void)
{
	int sum=0;
	Book *temp=head_book;
	while(temp!=NULL)
	{
		sum=sum+temp->book_left;
		temp=temp->next;
	}
	printf("The amount of all accessible books:%d\n",sum);
	return;
}

void edit_amount_book(void)
{
	show_number_accessibe_book();
	Book *temp=head_book;
	printf("#Changing some data#\n");
	char str[Length];
	printf("ISBN of book:");
	scanf("%s",str);
	while(temp!=NULL)
	{
		if(strcmp(temp->Isbn,str)==0)
		{
			printf("Want to change the amount of books?\n");
			if(choose_f_book()==1)
			{
				int book_amount;
				printf("Changing the amount of book:");
				scanf("%d",&book_amount);
				temp->book_amount=book_amount;
				temp->book_left=book_amount;		
			}
			printf("Successfull changing!\n");
			return;
		}
		else
		{
			temp=temp->next;
		}
	}
	printf("Sorry,but such a book doesn't exist!\n");
}


void save_and_exit(void)
{
	FILE *f=fopen("books.csv","w");
	Book *temp=head_book;
	if(head_book==NULL)
	{
		printf("Successfull saving!\n");
		return;
	}
	else
	{
		while(temp!=NULL)
		{
			fprintf(f,"%s;",temp->Isbn);
			fprintf(f,"%s;",temp->authors);
			fprintf(f,"%s;",temp->book_name);
			fprintf(f,"%d;",temp->book_amount);
			fprintf(f,"%d;\n",temp->book_left);
			temp=temp->next;
		}
	}
	printf("Successfull saving!\n");
	fclose(f);
}

int main()
{
	readfile_book();
	int choose;
	while(choose!=6)
	{
		choose=Book_menu();
		switch(choose)
		{
		case 1: add_book(); break;
		case 2:	delete_book(); break;
		case 3:	edit_book(); break;
		case 4:	edit_amount_book(); break;
		case 5: print_list_book(); break;
		case 6: save_and_exit(); break;
		default: printf("Choose another action\n");break;
		}
	}
}
