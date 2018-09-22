#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <functional>

using namespace std;

class Job
{
public:
	int job_id;
	int p_j;// processing time of job j
	int s_j;// start time of job j on specific machine
	int c_j;// completion time of job j on specific machine
	Job(int _job_id, int _p_j) { job_id = _job_id; p_j = _p_j; s_j = c_j = -1; }
};

bool operator> (Job j1, Job j2)
{
	if (j1.p_j < j2.p_j)
		return true;
	else
		return false;
}

class Machine
{
public:
	deque<Job> m_job_list;// jobs which are assigned on Machine
	int makespan;
	Machine() { makespan = 0; }
};

typedef priority_queue < Job, deque<Job>, greater<Job>> P_Q;

int main()
{
	ifstream myfile("input.csv");
	P_Q p_q;
	vector <Machine> m_list;

	int m_num;

	if (myfile.is_open())
	{
		string line;
		int job_id;
		int p_time;
		getline(myfile, line, ',');
		getline(myfile, line);
		m_num = stoi(line);
		Machine temp;
		for (int i = 0; i < m_num; i++)
			m_list.push_back(temp);
		getline(myfile, line);
		while (!(myfile.eof()))
		{
			getline(myfile, line, ',');
			if (line == "" || line == "\n")
				break;
			job_id = stoi(line);
			getline(myfile, line);
			p_time = stoi(line);

			Job temp(job_id, p_time);
			p_q.push(temp);
		}
	}
	else
		cout << "파일이 제대로 열리지 않았습니다.";

	while (!p_q.empty())
	{
		int add = 0;
		for (int i = 0; i < m_list.size(); i++)
		{
			if (m_list[i].makespan < m_list[add].makespan)
				add = i;
		}
		m_list[add].m_job_list.push_back(p_q.top());
		m_list[add].makespan += p_q.top().p_j;
		p_q.pop();
	}

	cout << "Enter input file name : input.csv" << endl;

	for (int i = 0; i < m_list.size(); i++)
	{
		cout << endl << "M/C " << i+1 << ": ";
		for (int j = 0; j < m_list[i].m_job_list.size(); j++)
		{
			for (int k = 0; k < m_list[i].m_job_list[j].p_j; k++)
				cout << m_list[i].m_job_list[j].job_id;
		}
	}

	cout << endl << endl << "Makespan of schedule = ";
	int max = m_list[0].makespan;
	for (int i = 1; i < m_list.size(); i++)
	{
		if (m_list[i].makespan > max)
			max = m_list[i].makespan;
	}
	cout <<max << endl;
}