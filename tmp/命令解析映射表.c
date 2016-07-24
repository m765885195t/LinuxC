int main(int argc,char *argv[])      //该怎麽实现

{
	int i,j,flag=1,k[20]={0};
	char ml[50]; 
	
	getcwd(ml,50);  //获取当前目录路径
	
	//命令解析表
	char a[][5]={"-a","-l","-R","-al","-la","-aR",
			     "-Ra","-lR","-Rl","-alR","-aRl",
			     "-lRa","-laR","-Ral","-Rla"};
	
	for(i=1;i<argc;i++)
	{
		flag=0;
		for(j=0;j<15;j++)
			if(!strcmp(a[j],argv[i]))
				k[i-1]=j+1;	
	}
	if(flag)
		k[0]=0;	
	switch(k)                   // 命令映射表
	{
		case 0:mls(ml,0,0,0);break;
		case 1:mls(ml,1,0,0);break;    //   a    l    R
		case 2:mls(ml,0,1,0);break;
		case 3:mls(ml,0,0,1);break;
		case 4:
		case 5:mls(ml,1,1,0);break;
		case 6:
		case 7:mls(ml,1,0,1);break;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:mls(ml,1,1,1);break;
		
		default:printf("你输入的参数有误");break;
	}
}

