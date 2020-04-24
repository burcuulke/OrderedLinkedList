#include <stdio.h>
#include <stdlib.h>

struct nodeFB
{
int id;
int age;
struct nodeFB *next;
};

struct nodeGS
{
int id;
struct nodeGS *next;
};

struct nodeFBnew
{
int id;
int age;
struct nodeGSnew *next;
};

struct nodeGSnew
{
int id;
struct nodeFBnew *next;
};

void insertFB(struct nodeFB **ns, int i, int a)
{
	struct nodeFB *temp, *tmp, *t;
	
	temp=*ns;
	
	if(*ns==NULL)
	{
		*ns=malloc(sizeof(struct nodeFB));
		(*ns)->id=i;
		(*ns)->age=a;
		(*ns)->next=NULL;
	}
	else
	{
		if((*ns)->id>i)
		{
			t=malloc(sizeof(struct nodeFB));
			t->id=i;
			t->age=a;
			t->next=(*ns);
			*ns=t;
		}
		else
		{
			while(temp!=NULL && temp->id<=i)
			{
				tmp=temp;
				temp=temp->next;
			}
			t=malloc(sizeof(struct nodeFB));
			t->id=i;
			t->age=a;
			t->next=temp;
			tmp->next=t;
		}			
	}
}

void insertGS(struct nodeGS **ns, int i)
{
	struct nodeGS *temp, *tmp, *t;
	
	temp=*ns;
	
	if(*ns==NULL)
	{
		*ns=malloc(sizeof(struct nodeGS));
		(*ns)->id=i;
		(*ns)->next=NULL;
	}
	else
	{
		if((*ns)->id<i)
		{
			t=malloc(sizeof(struct nodeGS));
			t->id=i;
			t->next=(*ns);
			*ns=t;
		}
		else
		{
			while(temp!=NULL && temp->id>=i)
			{
				tmp=temp;
				temp=temp->next;
			}
			t=malloc(sizeof(struct nodeGS));
			t->id=i;
			t->next=temp;
			tmp->next=t;
		}			
	}
}

void merge(struct nodeFBnew **n, struct nodeFB *fb, struct nodeGS *gs)
{
	struct nodeFBnew *tempfb;
	struct nodeGSnew *tempgs;
	struct nodeFBnew *temphead;

	if(fb==NULL)
		return;
	
	*n=malloc(sizeof(struct nodeFBnew));
	(*n)->id=fb->id;
	(*n)->age=fb->age;
	
	(*n)->next=malloc(sizeof(struct nodeGSnew));
	(*n)->next->id=gs->id;

	fb=fb->next;
	gs=gs->next;
	
	temphead=*n;
	
	while(fb!=NULL)
	{
		temphead->next->next=malloc(sizeof(struct nodeFBnew));
		temphead->next->next->id=fb->id;
		temphead->next->next->age=fb->age;
		
		temphead->next->next->next=malloc(sizeof(struct nodeGSnew));
		temphead->next->next->next->id=gs->id;
			
		temphead=temphead->next->next;
		
		fb=fb->next;
		gs=gs->next;
	}
	temphead->next->next=NULL;
}
		
void printFB(struct nodeFB *temp)
{
	while(temp!=NULL)
	{
		printf("Id:%d\tAge:%d\n",temp->id, temp->age);
		temp=temp->next;
	}
	printf("\n");
}

void printGS(struct nodeGS *temp)
{
	while(temp!=NULL)
	{
		printf("Id:%d\n",temp->id);
		temp=temp->next;
	}
	printf("\n");
}

void printAll(struct nodeFBnew *tempfb)
{
	int c=0;
	struct nodeGSnew *tempgs;
	
	if(tempfb==NULL)
			return;
		
	while(tempfb!=NULL)
	{
		if(c==0)
		{
			printf("Id:%d\tAge:%d\n",tempfb->id, tempfb->age);
			c++;
			tempgs=tempfb->next;
		}
		else
		{
			printf("Id:%d\n",tempgs->id);
			c--;
			tempfb=tempgs->next;
		}
	}
}
int main()
{
	struct nodeFB *fbPtr=NULL, *fbtemp=NULL;
	struct nodeGS *gsPtr=NULL, *gstemp=NULL;
	struct nodeFBnew *nAll;
	
	int id, age;
	
	scanf("%d%d",&id,&age);
	
	while(id!=-1)
	{
		insertFB(&fbPtr,id,age);
		scanf("%d%d",&id,&age);
	}
	
	scanf("%d",&id);
	
	while(id!=-1)
	{
		insertGS(&gsPtr,id);
		scanf("%d",&id);
	}
	
	printFB(fbPtr);
	printGS(gsPtr);
	
	merge(&nAll,fbPtr, gsPtr);
	printAll(nAll);
	return 0;
}