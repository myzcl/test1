/*
日期：2018.0729
名称：link1.c
描述：头指针链表
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node
{
	int value;
	struct node *next;
}node;

node *head = NULL;

//创建节点
node *mk_node(int value)
{
	node *p = (node *)malloc(sizeof(node));
	if (p == NULL)
	{
		printf("malloc failed!\n");
		exit(1);
	}
	
	p->value = value;
	p->next = NULL;
	
	return p;
}

//释放节点
void free_node(node *p)
{
	free(p);
}

//插入节点
void insert_node(node *p)
{
	p->next = head;
	head = p;
}

//遍历节点
void traverse()
{
	node *p = head;
	
	while (p != NULL)
	{
		printf("%d ", p->value);
		p = p->next;		
	}
	printf("\n");
}

//销毁链表
void destroy_link()
{
	node *p = head;
	
	while (head != NULL)
	{
		p = head;
		head = head->next;
		free_node(p);
	}
}

//查找节点
node *search_node(int value)
{
	node *p = head;
	
	while (p != NULL)
	{
		if (p->value == value)
		{
			return p;
		}

		p = p->next;
	}
	
	return NULL;
}

//删除节点(rm意思是移除，不需要释放，单独释放)
void rm_node(node *p)
{
	node *pre = head;
	
	if (p == head)
	{
		head = head->next;
		p->next = NULL;
		//free_node(p);
		return;
	}
	
	while (pre->next != NULL)
	{
		if (pre->next == p)
		{
			pre->next = p->next;
			p->next = NULL;
			//free_node(p);
			return;
		}
		
		pre = pre->next;
	}
}

//链表逆序
void reverse_list()
{
	node *p = head;
	node *nhead = NULL;
	
	if (p == NULL || p->next == NULL)//注意次序，短路
	{
		return;
	}
	
	while (head != NULL)
	{
		p = head;
		head = head->next;
		
		p->next = nhead;
		nhead = p;
	}
	
	head = nhead;
}

//删除value = x的节点(需要释放)
void dele_x_node1(int x)
{
	node *p;

	while ((p = search_node(x)) != NULL)
	{
		rm_node(p);
		free_node(p);
	}
}

//删除value = x的节点(需要释放)
void dele_x_node2(int x)
{
	node *pre = head;
	node *p;
	
	if (head == NULL)
	{
		return;
	}
	
	while (pre->next != NULL)
	{
		p = pre->next;
		if (p->value == x)
		{
			pre->next = p->next;
			free_node(p);
			continue;
		}
		
		pre = pre->next;
	}
	
	if (head->value == x)
	{
		p = head;
		head = head->next;
		free_node(p);
	}
}


//顺序插入
void insert_node_sort(node *p)
{
	//node *p;
	node *pre = head;
	
	if (head == NULL || p->value < head->value)
	{
		p->next = head;
		head = p;
		return;
	}
	
	while (pre->next != NULL)
	{
		if (p->value < pre->next->value)
		{
			break;
		}
			
		pre = pre->next;
	}
	
	p->next = pre->next;
	pre->next = p;
}

//无序变有序
void insert_sort()
{
	node nhead = {0, NULL};
	node *pre = head;
	node *p = head;
	
	while (head != NULL)
	{
		p = head;
		head = head->next;
		
		pre = &nhead;
		while (pre->next != NULL)
		{
			if (p->value < pre->next->value)
			{
				break;
			}
			
			pre = pre->next;
		}
		p->next = pre->next;
		pre->next = p;
	}
	
	head = nhead.next;
}

int main()
{
	int i = 0;
	int value = 0;
	node *p;
	
	srand(time(NULL));
	for (i = 0; i < 10; i++)
	{
		value = rand() % 100 + 1;
		if (i < 5)
		{
			value = 20;
		}
		else
		{
			value = i + 1;			
		}

		p = mk_node(value);
		insert_node(p);
		//insert_node_sort(p);
	}
	traverse(head);
	
	insert_sort(head);
	traverse(head);
	
	p = search_node(9);
	if (p == NULL)
	{
		printf("can't find!\n");
	}
	else
	{
		rm_node(p);	
		free_node(p);
	}
	traverse();
	
	reverse_list();
	traverse();
	
	dele_x_node2(20);
	traverse();
	
	
	destroy_link();
	traverse();
	
	return 0;
}
