#include"fun.h"

//文件输入
void in(process *p,int process_num)
{
	const char* filename = "process.txt";
	ifstream ism;
	ism.open(filename);
	if (!ism.is_open())
	{
		cout << "hhhhhhhhh"<<endl;
	}
	int i = 0;
	for (i; i < process_num; i++)
	{
		ism >> p[i].name;
	}
	for (int i = 0; i < process_num; i++)
	{
		ism >> p[i].come_time;
	}
	for (int i = 0; i < process_num; i++)
	{
		ism >> p[i].server_time;
	}
}

//输出相关结果
void out(process* p,int process_num)
{
	sort_come(p, process_num);
	cout << "进程名字:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].name << "\t";
	}
	cout << endl;
	cout << "到达时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].come_time << "\t";
	}
	cout << endl;
	cout << "服务时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].server_time << "\t";
	}
	cout << endl;
	cout << "完成时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].fin_time << "\t";
	}
	cout << endl;
	cout << "周转时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].turn_time << "\t";
	}
	cout << endl;
	cout << "带权周转时间:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << r2(p[i].weight_turn_time) << "\t";
	}
	cout << endl<<endl;
	cout << "平均周转时间:" << "\t";
	float total_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_turntime += p[i].turn_time;
	}
	cout << r2(total_turntime/process_num)<<endl<<endl;

	cout << "平均带权周转时间:" << "\t";
	float total_weight_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_weight_turntime += p[i].weight_turn_time;
	}
	cout << r2(total_weight_turntime / process_num) << endl;
}

//按照到达时间进行升序排序
void sort_come(process* p, int process_num)
{
	for (int i = 0; i < process_num; i++)
	{
		for (int j = process_num-1; j > i; j--)
		{
			if (p[j - 1].come_time > p[j].come_time)
			{
				process temp = p[0];
				temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
}

//按照服务时间进行升序排序
void sort_server(process* p, int process_num)
{
	for (int i = 0; i < process_num; i++)
	{
		for (int j = process_num - 1; j > i; j--)
		{
			if (p[j - 1].server_time > p[j].server_time)
			{
				process temp = p[0];
				temp = p[j - 1];
				p[j - 1] = p[j];
				p[j] = temp;
			}
		}
	}
}

//先来先服务FCFS
void FCFS(process* p, int process_num)
{
	sort_come(p, process_num);		//先按进程照到达时间进行升序排序
	int i = 0;		//记录次数
	float time = 0;		//当前时间，用来判断当前时间是否已有进程到达
	for (i; i < process_num; i++)
	{
		if (time < p[i].come_time)		//当前时间没有到达的进程，时间增加，重新判断最前的进程是否到达
		{
			time++;
			i--;
		}
		else
		{
			p[i].fin_time = time + p[i].server_time;		//计算结束时间
			p[i].turn_time = p[i].fin_time - p[i].come_time;		//计算周转时间
			p[i].weight_turn_time = p[i].turn_time / p[i].server_time;		//计算带权周转时间
			time = p[i].fin_time;	//每服务完一个进程，更新当前时间
		}
		
	}
}

void SJF(process* p, int process_num)
{
	sort_server(p, process_num);	//按照服务时间进行升序排序
	int i = 0;		
	float time = 0;		//记录当前时间
	int count = 0;		//用来记录已经服务完的进程的数量
	for (i; i < process_num; i++)
	{
		if (p[i].come_time == 0) { break; }		//找到到达时间为0的进程并记录
	}
	int first = i;
	//对第一个进程进行处理
	p[first].fin_time = time + p[first].server_time;
	p[first].turn_time = p[first].fin_time - p[first].come_time;
	p[first].weight_turn_time = p[first].turn_time / p[first].server_time;
	time = p[first].fin_time;
	p[first].flag = 1;		//更新标记
	count++;				//总数+1

	//该循环用来按服务时间顺序查找当前时间，服务时间最短的进程是否到达。
	//每找到一个可服务的进程，都会重新遍历整个进程列表，找到下一个服务时间最短且已到达且未被服务的进程
	for (int i = 0; i < process_num; i++)
	{
		if (p[i].flag == 1)		//若当前进程已被服务，判断 1.若是最后一个进程，则退出，2.还有未服务的进程，i++，继续循环。
		{
			if (count == process_num)
			{
				break;
			}
			else
			{
				continue;
			}
		}
		else	//当前找到的进程还未被服务过
		{
			if (p[i].come_time < time)	//当前时间，该进程已到达
			{
				p[i].fin_time = time + p[i].server_time;
				p[i].turn_time = p[i].fin_time - p[i].come_time;
				p[i].weight_turn_time = p[i].turn_time / p[i].server_time;
				time = p[i].fin_time;

				p[i].flag = 1;	//更新标记
				i = 0;
				i--;		//从头开始找未被服务且服务时间最短的进程，以免在循环刚开始进行时，遗漏服务时间很短但到达时间很晚的进程
				count++;
			}
			else
			{
				time = time + 1;	
				//i = i - 1;
			}
		}
	}
}

//仅仅用来输出结果保留两位小数、看起来简洁
float r2(float a)
{
	return(round(a * 100) / 100.0);
}

int main()
{
	
	int process_num = 4;
	process *p = new process[process_num];
	in(p, process_num);
	int a = 0;
	while (1)
	{
		cout << endl;
		cout << "pls input a number to select a function" << endl;
		cout << "1.FCFS" << endl;
		cout << "2.SJF" << endl;
		cout << "3.quit"<<endl;

		cin >> a;
		if (a == 1)
		{
			cout << "-----FCFS-----" << endl;
			FCFS(p, process_num);
			out(p, process_num);
		}
		else if (a == 2)
	    {
			cout << "-----SJF-----" << endl;
			SJF(p, process_num);
			out(p, process_num);
		}
		else if (a == 3)
		{
			break;
		}
		else
		{
			cout << "pls intput a ture number" << endl;
		}
	}



	return 0;
}