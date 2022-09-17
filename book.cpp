#include<bits/stdc++.h>
using namespace std;
int shenfen,n;
typedef struct Book//这个为借书还书所需要的书籍信息结构体 
{
	char name[1000];
	int numb;
	int rest;  //书的剩余量
}book,*books; 
typedef struct player//用户结构体 
{
	char id[10];
	char password[50];
	char name[10];
	int flag;
}users;
 void zhuce()//账号的注册功能 
 {
 	char password1[10];
	users a,b;
	FILE *f; //定义文件指针
	f=fopen("D:/yhh.txt","r");  //r 打开只读文件，该文件必须存在
	if(f==NULL)
	{
		printf("注册时打开文件失败");
		
	}
	else
	{
		printf("\t\t\t欢迎来到注册列表\n");
		printf("\t\t\t请输入账号:");
		scanf("%s",&a.id);
		fread(&b,sizeof(struct player),1,f);
		//从给定输入流stream读取最多count个对象到数组buffer中
		//size_t fread( void *restrict buffer, size_t size, size_t count, FILE *restrict stream );
		//buffer- 指向要读取的数组中首个对象的指针 size- 每个对象的大小（单位是字节）
		//count- 要读取的对象个数  stream- 输入流
	}
	while(1)
	{
		if(strcmp(a.id,b.id))
		{
			if(!feof(f)) //测试文件是否接受结束，结束返回非0值，未结束返回0
			{
				fread(&b,sizeof(struct player),1,f);
			}
			else
			{
				printf("\t\t\t此账号可注册\n");
				break;
			}
		}//通过一个死循环实现逐个暴力比对 
		else
        {   
            printf("\t\t\t此用户名已存在,请重新注册\n");
            fclose(f);
            return;      
        }
	}
	do{
		printf("\t\t\t请输入密码:");
		scanf("%s",&a.password);
		printf("\t\t\t请再次输入确认密码:");
		scanf("%s",&password1);
		if(strcmp(a.password,password1))
		{
			printf("\t\t\t两次密码输入不相同\n");
		}
		else
		{	
			printf("\t\t\t密码一致\n");
			break;
		}
	}while(1);
	a.flag=0;
	printf("\t\t\t请输入你的昵称:");
	scanf("%s",&a.name);
	f=fopen("D:/yhh.txt","a"); //a 以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留。
	fwrite(&a, sizeof(struct player), 1,f);
    printf("\t\t\t账号注册成功，请登录！\n"); 
    fclose(f);
}
 
bool denglu()//登陆函数 
{
	users a;
	FILE *f;
	char id1[10],password1[10];
	printf("\t\t\t请输入您的账号:");
	scanf("%s",&id1);
	printf("\t\t\t请输入密码:");
	scanf("%s",&password1);
	f=fopen("D:/yhh.txt","r");
	while(1)
	{
		if(strcmp(a.id,id1))
		{
			if(!feof(f))
			{
				fread(&a,sizeof(struct player),1,f);
			}
			else
			{
				printf("\t\t\t不存在此账号\n");
				fclose(f);
				return false;
			}
		}
		else
		{
			if(strcmp(a.password,password1))
			{
				printf("\t\t\t密码错误\n");
				return false;
			}
			else
			{
				shenfen=a.flag;
				printf("\t\t\t登录成功\n");
				return true;//flag为角色身份 我们提前录入了管理员所以以后在注册都是普通用户 
			}
		}
	}
}
void del_book(books*BOOK,char*point)//借书函数 
{
	int flag=0;//标记是否找到书籍 
	FILE*fp1=fopen("D:/b.txt","rb"); //加入b 字符用来告诉函数库打开的文件为二进制文件
	int i; 
	for(i=0;i<n;i++)
	{
		if(strcmp(point,(*BOOK)[i].name)==0)
		{
			flag=1;
			break;
		}
	}
	if(!flag)
	{
		printf("抱歉，目没有此书籍"); 
		goto flag1;
	}
	if((*BOOK)[i].rest==0)
	{
		printf("很抱歉，书已经全部借出\n");
		goto flag1;
	}
	(*BOOK)[i].rest--;
	printf("%s的剩余量为：%d\n",(*BOOK)[i].name,(*BOOK)[i].rest);
	system("pause");
	system("cls"); //清屏
	printf("------------------借书目录------------------\n"); 
		for(int i=0;i<n;i++)
	{
		printf("name:%s\n",(*BOOK)[i].name);
		printf("number:%d\n",(*BOOK)[i].numb);
		printf("rest:%d\n",(*BOOK)[i].rest);
	}
	printf("----------------------------------------\n");
	flag1:
	fclose(fp1);//清屏功能 
	FILE*fp2=fopen("D:/b.txt","wb");
	for(int i=0;i<n;i++)
	{
		fwrite(&(*BOOK)[i],sizeof((*BOOK)[i]),1,fp2);
	}
	fclose(fp2);//对修改后的书籍写入实现同步更新 
}

void add_book(books*BOOK,char*point){//还书函数 
	int flag=0;//和借书相似比较名称的标记符号 
	FILE*fp1=fopen("D:/b.txt","rb");
	int i=0;
	for(i=0;i<n;i++)
	{
		if(strcmp(point,(*BOOK)[i].name)==0)
		{
			flag=1;
			break;
		}
	}
	if(!flag)
	{
		printf("抱歉，目没有此书籍"); 
		goto flag1;
	}
	else
	{
		if((*BOOK)[i].rest==(*BOOK)[i].numb)
		{
			cout<<"此书并未借出！"<<endl;
			return ;
		}
		(*BOOK)[i].rest++;
		cout<<"还书成功，谢谢！"<<endl;
	}
	printf("%s的剩余量为：%d\n",(*BOOK)[i].name,(*BOOK)[i].rest);
	system("pause");
	system("cls"); //清屏幕功能 
	printf("------------------目录------------------\n"); 
		for(int i=0;i<n;i++)
	{
		printf("name:%s\n",(*BOOK)[i].name);
		printf("number:%d\n",(*BOOK)[i].numb);
		printf("rest:%d\n",(*BOOK)[i].rest);
	}
	printf("----------------------------------------\n");
	flag1:
	fclose(fp1);
	FILE*fp2=fopen("D:/b.txt","wb");
	for(int i=0;i<n;i++)
	{
		fwrite(&(*BOOK)[i],sizeof((*BOOK)[i]),1,fp2); 
	}
	fclose(fp2);
}
void add_del()//借书还书集合函数 用户输入借书还书先会跳入这个界面 然后进行下一步操作程序判断是借书还是还书 
{
	FILE*fp1=fopen("D:/b.txt","rb");
	books BOOK=(books)malloc(sizeof(book)*n);
	printf("----------------目录-------------------\n");
	for(int i=0;i<n;i++)
	{
 
		fread(&BOOK[i],sizeof(book),1,fp1);
		printf("name:%s\n",BOOK[i].name);
		printf("number:%d\n",BOOK[i].numb);
		printf("rest:%d\n",BOOK[i].rest);
	}
	printf("------------------------------------------\n");
	flag1:
	printf("借书请输入1，还书则输入2，退出输入3：\n");
	int flag;
	scanf("%d",&flag);
	if(flag!=1&&flag!=2&&flag!=3){
	fflush(stdin); //清空输入缓冲区
	while(flag!=1&&flag!=2&&flag!=3)
	{
		cout<<"错误操作请重新输入！"<<endl;
		scanf("%d",&flag);
		fflush(stdin);
	}
	}
	if(flag==1)
	{
	char ponit[1000];
	printf("请输入想要借出的书名：\n");
	scanf("%s",ponit);
	del_book(&BOOK,ponit);
	}
	else if(flag==2)
	{ 
	char ponit[1000];
	printf("请输入想要还的书名：\n");
	scanf("%s",ponit);
	add_book(&BOOK,ponit);
	}
	else{
		fclose(fp1);
		system("cls");
		return ;
	}
	fclose(fp1);
}

//把文件改成anis 
FILE *fp;
int xuan;
typedef struct ook
{
	char name[100];
	char author[100];
	char num[100];
	double price;
}libr;//浏览书籍的结构体 
void end()
{//录入这里使用追加功能 
	book B;
	struct ook boo;
	printf("输入书名吧（建议叫做马小飞）:");
	scanf("%s",boo.name);
	strcpy(B.name,boo.name);
	printf("输入我的专属号码吧 主人:");
	scanf("%s",boo.num); 
	printf("输入作者名字(建议叫做颜金城):");
	scanf("%s",boo.author);
	printf("输入我的价格吧(250金挺吉利的):");
	scanf("%lf",&boo.price);
	printf("输入数量:");
	scanf("%d",&B.numb);
	B.rest=B.numb;
	getchar();
	fseek(fp,0,2);//定位到文件最后 int fseek(FILE *stream, long offset, int fromwhere);
    // 函数设置文件指针stream的位置。如果执行成功，stream将指向以fromwhere为基准，偏移offset（指针偏移量）个字节的位置，函数返回0。
	fwrite(&boo,sizeof(libr),1,fp);
	FILE*fp2=fopen("D:/b.txt","ab");
	fwrite(&B,sizeof(B),1,fp2);
	fclose(fp2);
	n++;
	system("pause");
 } 
void print()//当进入浏览功能后会进行下面函数 
{
	struct ook bo;
	fread(&bo,sizeof(libr),1,fp);
	printf("%-10s%-10s%-10s%-10s\n","书名","编号","作者","价格");
	while(feof(fp)==0)
	{
		printf("%-10s%-10s%-10s%-10.2lf\n",bo.name,bo.num,bo.author,bo.price);//逐一读出数据库中的信息 
		fread(&bo,sizeof(libr),1,fp);
	}
	system("pause");
}
int dui(char* p,char* p1)//查询功能 
{
	int flag=0;
	int i;
	for(int i=0;i<(int)strlen(p1);i++)
	{
		if(p[0]==p1[i])
		{
			flag=i;
		}
	}
	if((int)strlen(p)>(int)strlen(p1)-flag+1)
		return 0;
	for(i=0;i<(int)strlen(p);i++)
	{
		if(p[i]!=p1[flag+i])
		{
			return 0;
		}
	}
	return 1;
}
void find()//总查询界面 输入查询后进入根据操作者的指令进行下一步操作 
{
	int flag=0;
	char temp[100]={0};
	printf("\t\t1-----书名查询\t\t\t");
	printf("2-----编码查询\n\n");
	printf("\n\t\t3-书名模糊查询                  4-编号模糊查询\n\n");
	scanf("%d",&xuan);
	struct ook boo;
	fread(&boo,sizeof(libr),1,fp);
	if(xuan==1)
	{
		printf("请输入书名:");
		scanf("%s",temp);
		while(feof(fp)==0)
		{
			if(strcmp(temp,boo.name)==0)
			{
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t%-10s%-10s%-10s%-10s\n","书名","编号","作者","价格");
				printf("\t\t\t\t%-10s%-10s%-10s%-10.2lf\n\n\n\n\n\n\n\n\n\n\n\n\n",boo.name,boo.num,boo.author,boo.price);
				flag=1; 
			}
			fread(&boo,sizeof(libr),1,fp);
		}
	}
	if(xuan==2)
	{
		printf("请输入编号:");
		scanf("%s",temp);
		while(feof(fp)==0)
		{
			if(strcmp(temp,boo.num)==0)
			{
				printf("%-10s%-10s%-10s%-10s\n","书名","编号","作者","价格");
				printf("%-10s%-10s%-10s%-10.2lf\n",boo.name,boo.num,boo.author,boo.price);
				flag=1; 
			}
			fread(&boo,sizeof(libr),1,fp);
		}
	}
	if(xuan==4)
	{
		printf("输入模糊编号:");
		scanf("%s",temp);
		int fan;
		while(!feof(fp))
		{
			fan=dui(temp,boo.num);
			if(fan==1)
			{
				printf("%-10s%-10s%-10s%-10s\n","书名","编号","作者","价格");
				printf("%-10s%-10s%-10s%-10.2lf\n",boo.name,boo.num,boo.author,boo.price);
				flag=1;
			}
			fread(&boo,sizeof(libr),1,fp);
		}
	}
	if(xuan==3)
	{
		printf("输入模糊名称:");
		scanf("%s",temp);
		int fan;
		while(!feof(fp))
		{
			fan=dui(temp,boo.name);
			if(fan==1)
			{
				printf("%-10s%-10s%-10s%-10s\n","书名","编号","作者","价格");
				printf("%-10s%-10s%-10s%-10.2lf\n",boo.name,boo.num,boo.author,boo.price);
				flag=1;
			}
			fread(&boo,sizeof(libr),1,fp);
		}
	}
	if(flag==0)
		printf("\n\n\n\n\n\n\n\t\t\t\t\t！查无此书！\n\n\n\n\n\n\n\n\n\n\n\n");
	system("pause");
} 
int mulu(void)//用户登陆后的界面操作选择 
{
	system("cls");
	if((fp=fopen("D:/c.txt","rb+"))==NULL)
	{
		fp=fopen("D:/c.txt","wb+");
	}
	printf("\n\n");
	int i; 
	for(i=0;i<80;i++)
		printf("#");
	printf("\n\n");	
	printf("\t\t1-----图书录入\t\t\t");
	printf("2-----图书浏览\n\n");
	printf("\t\t3-----图书查询\t\t\t");
	printf("4-----借阅或归还图书\n\n");
	printf("\n\t\t\t\t输入其他任意键退出\n");
	printf("\n\n");
	for(i=0;i<80;i++)
		printf("#");
	printf("\n\n");
	z:
	scanf("%d",&xuan);
	
	while(xuan==1||xuan==2||xuan==3||xuan==4)
	{
		if(xuan==1&&shenfen==0){
		printf("对不起无权限！\n");
		goto z;
		}
		system("cls");
		fp=fopen("D:/c.txt","rb+");
		switch(xuan)
		{
			case 0:break;
			case 1:end();break;
			case 2:print();break;
			case 3:find();break;
			case 4:add_del();break;
		}
		fclose(fp);
		printf("\n\n");
		int i; 
		for(i=0;i<80;i++)
			printf("#");
		printf("\n\n");	
		printf("\t\t1-----图书录入\t\t\t");
		printf("2-----图书浏览\n\n");
		printf("\t\t3-----图书查询\t\t\t");
		printf("4-----借阅或归还图书\n\n");
		printf("\n\t\t\t\t输入其他任意键退出\n");
		printf("\n\n");
		for(i=0;i<80;i++)
			printf("#");
		printf("\n\n");
		scanf("%d",&xuan);
	}
}
int main()//初始界面 
{
	ma:
	printf("\t\t\t\t ***********************\n");
	printf("\t\t\t\t ***欢迎光临324图书馆***\n");
	printf("\t\t\t\t ***********************\n");
	printf("\t\t注册账号...1\t\t登录账号...2\t\t退出...3\n");
	flag1:
	int temp;
	bool flag; 
	scanf("%d",&temp);
	if(temp==1)zhuce();
	if(temp==2)flag=denglu();
	if(temp==3){
		FILE*fp2=fopen("D:/d.txt","w");
		char cn[100];
		sprintf(cn,"%d",n);
		fputs(cn,fp2); // int fputs(const char *str, FILE *stream);
        //str：这是一个数组，包含了要写入的以空字符终止的字符序列。
         //stream：指向 FILE 对象的指针，该 FILE 对象标识了要被写入字符串的流
		fclose(fp2);
		printf("欢迎下次光临!!!\n"); 
		system("pause");
		return 0;
	} 
	if(!flag){
		fflush(stdin);
		goto flag1;
	}
	else
	{
		FILE*fp1=fopen("D:/d.txt","r");
		char cn[100];
		fgets(cn,100,fp1);
		sscanf(cn,"%d",&n);
		fclose(fp1);
		fp1=NULL;
		system("cls");
		printf("欢迎回来!\n");
		cout<<"请选择操作"<<endl;
		if(flag==1)mulu();
		system("cls"); 
		goto ma;
	}
}