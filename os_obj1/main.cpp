#include"fun.h"

//�ļ�����
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

//�����ؽ��
void out(process* p,int process_num)
{
	sort_come(p, process_num);
	cout << "��������:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].name << "\t";
	}
	cout << endl;
	cout << "����ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].come_time << "\t";
	}
	cout << endl;
	cout << "����ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].server_time << "\t";
	}
	cout << endl;
	cout << "���ʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].fin_time << "\t";
	}
	cout << endl;
	cout << "��תʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << p[i].turn_time << "\t";
	}
	cout << endl;
	cout << "��Ȩ��תʱ��:" << "\t";
	for (int i = 0; i < process_num; i++)
	{
		cout << r2(p[i].weight_turn_time) << "\t";
	}
	cout << endl<<endl;
	cout << "ƽ����תʱ��:" << "\t";
	float total_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_turntime += p[i].turn_time;
	}
	cout << r2(total_turntime/process_num)<<endl<<endl;

	cout << "ƽ����Ȩ��תʱ��:" << "\t";
	float total_weight_turntime = 0;
	for (int i = 0; i < process_num; i++)
	{
		total_weight_turntime += p[i].weight_turn_time;
	}
	cout << r2(total_weight_turntime / process_num) << endl;
}

//���յ���ʱ�������������
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

//���շ���ʱ�������������
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

//�����ȷ���FCFS
void FCFS(process* p, int process_num)
{
	sort_come(p, process_num);		//�Ȱ������յ���ʱ�������������
	int i = 0;		//��¼����
	float time = 0;		//��ǰʱ�䣬�����жϵ�ǰʱ���Ƿ����н��̵���
	for (i; i < process_num; i++)
	{
		if (time < p[i].come_time)		//��ǰʱ��û�е���Ľ��̣�ʱ�����ӣ������ж���ǰ�Ľ����Ƿ񵽴�
		{
			time++;
			i--;
		}
		else
		{
			p[i].fin_time = time + p[i].server_time;		//�������ʱ��
			p[i].turn_time = p[i].fin_time - p[i].come_time;		//������תʱ��
			p[i].weight_turn_time = p[i].turn_time / p[i].server_time;		//�����Ȩ��תʱ��
			time = p[i].fin_time;	//ÿ������һ�����̣����µ�ǰʱ��
		}
		
	}
}

void SJF(process* p, int process_num)
{
	sort_server(p, process_num);	//���շ���ʱ�������������
	int i = 0;		
	float time = 0;		//��¼��ǰʱ��
	int count = 0;		//������¼�Ѿ�������Ľ��̵�����
	for (i; i < process_num; i++)
	{
		if (p[i].come_time == 0) { break; }		//�ҵ�����ʱ��Ϊ0�Ľ��̲���¼
	}
	int first = i;
	//�Ե�һ�����̽��д���
	p[first].fin_time = time + p[first].server_time;
	p[first].turn_time = p[first].fin_time - p[first].come_time;
	p[first].weight_turn_time = p[first].turn_time / p[first].server_time;
	time = p[first].fin_time;
	p[first].flag = 1;		//���±��
	count++;				//����+1

	//��ѭ������������ʱ��˳����ҵ�ǰʱ�䣬����ʱ����̵Ľ����Ƿ񵽴
	//ÿ�ҵ�һ���ɷ���Ľ��̣��������±������������б��ҵ���һ������ʱ��������ѵ�����δ������Ľ���
	for (int i = 0; i < process_num; i++)
	{
		if (p[i].flag == 1)		//����ǰ�����ѱ������ж� 1.�������һ�����̣����˳���2.����δ����Ľ��̣�i++������ѭ����
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
		else	//��ǰ�ҵ��Ľ��̻�δ�������
		{
			if (p[i].come_time < time)	//��ǰʱ�䣬�ý����ѵ���
			{
				p[i].fin_time = time + p[i].server_time;
				p[i].turn_time = p[i].fin_time - p[i].come_time;
				p[i].weight_turn_time = p[i].turn_time / p[i].server_time;
				time = p[i].fin_time;

				p[i].flag = 1;	//���±��
				i = 0;
				i--;		//��ͷ��ʼ��δ�������ҷ���ʱ����̵Ľ��̣�������ѭ���տ�ʼ����ʱ����©����ʱ��̵ܶ�����ʱ�����Ľ���
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

//��������������������λС�������������
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