#include"PackedTaskTest.h"

void PackedTaskTest::Run()
{
	packaged_task<int(int, int, char)> operateTask([](int a, int b, char o)
		{
			this_thread::sleep_for(chrono::seconds(5));
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
	std::cout << "start task\n";
	RunTaskInOtherThread(move(operateTask));
	std::cout << "result from task print:-\n";
	std::cout << "task result" << taskRes.get() << '\n';
	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}
void PackedTaskTest::RunTaskImmidiate(packaged_task<int(int, int, char)> task)
{
	task(1, 2, '+');
}
void PackedTaskTest::RunTaskInOtherThread(packaged_task<int(int, int, char)> task)
{
	thread taskThread(move(task),1,2,'+');
	m_threadsInAction.push_back(move(taskThread));
}