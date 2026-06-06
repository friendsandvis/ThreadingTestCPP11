#include"PackedTaskTest.h"

void PackedTaskTest::Run()
{
	packaged_task<int(int, int, char)> operateTask([](int a,int b,char o)
	{
			this_thread::sleep_for(chrono::seconds(3));
		switch (o)
		{
		case '+':
			return a + b; break;
		case '-':
			return a - b; break;
		case '*':
			return a * b; break;
		case '/':
			return a / b; break;

		}
	});
	future<int> taskRes = operateTask.get_future();
	RunTaskImmidiate(move(operateTask));
	std::cout << "task result" << taskRes.get() << '\n';
}
void PackedTaskTest::RunTaskImmidiate(packaged_task<int(int, int, char)> task)
{
	task(1, 2, '+');
}