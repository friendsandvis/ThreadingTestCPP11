#include"DownloadConditionVariableTest.h"

string DownloadConditionVariableTest::downloadedData;
mutex DownloadConditionVariableTest::downloadingDataMtx;
mutex DownloadConditionVariableTest::downloadingCompleteMtx;
mutex DownloadConditionVariableTest::printMtx;
condition_variable DownloadConditionVariableTest::downloadCompleteConditionVar;
condition_variable DownloadConditionVariableTest::downloadDataUpdatedConditionVar;
bool DownloadConditionVariableTest::downloadDataUpdated;
bool DownloadConditionVariableTest::downloadCompleted;
void DownloadConditionVariableTest::Run()
{
	//init
	downloadedData = "";
	downloadCompleted = false;
	downloadDataUpdated = false;
	thread downloadThread(DownloadWork);
	m_threadsInAction.push_back(move(downloadThread));
	thread progressBarThread(ProgressBarWork);
	m_threadsInAction.push_back(move(progressBarThread));
	thread processDataThread(ProcessDownloaddedWork);
	m_threadsInAction.push_back(move(processDataThread));
	for (thread& t : m_threadsInAction)
	{
		t.join();
	}
}
void DownloadConditionVariableTest::DownloadWork()
{
	const int maxDownloadCycles = 200;
	for (int i = 0; i < maxDownloadCycles; i++)
	{
		lock_guard<mutex> downloadDataLock(downloadingDataMtx);
		downloadedData += "data chunk " + to_string(i);
		//nortify download progress
		downloadDataUpdated = true;
		downloadDataUpdatedConditionVar.notify_all();
		this_thread::sleep_for(chrono::milliseconds(1));
	}
	//nortify download complete condition
	downloadCompleted = true;
	downloadCompleteConditionVar.notify_all();
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "downloading end\n";
	}
}
void DownloadConditionVariableTest::ProgressBarWork()
{
	const bool progressBarRunning = true;
	int downloadedSize = 0;
	//start progressbar loop
	while (progressBarRunning)
	{
		//wait for download to be updated
		unique_lock<mutex> downloadDataLock(downloadingDataMtx);
		downloadDataUpdatedConditionVar.wait(downloadDataLock, []() {return downloadDataUpdated; });
		//download updated so update progress as well
		downloadedSize = downloadedData.size();
		{
			unique_lock<mutex> downloadcompleteLock(downloadingCompleteMtx);
			//wait on a condition variable to check if download completed or not and break out of progress bar loop accordingly
			if (downloadCompleteConditionVar.wait_for(downloadcompleteLock,chrono::milliseconds(10), []() {return downloadCompleted; }))
			{
				//download completed so break out of progress loop.
				break;
			}
		}
		
		//print progress
		{
			lock_guard<mutex> printLock(printMtx);
			cout << "progress update:::Downloaded size:- " << downloadedSize << " bytes\n";
		}
		downloadDataUpdated = false;
	}
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "progress bar end\n";
	}
}
void DownloadConditionVariableTest::ProcessDownloaddedWork()
{
	string downloadedDataCopy;
	unique_lock<mutex> downloadCompleteLock(downloadingCompleteMtx);
	//wait safly for download complete
	downloadCompleteConditionVar.wait(downloadCompleteLock, []() {return downloadCompleted; });
	//download complete process
	{
		lock_guard<mutex> dataLock(downloadingDataMtx);
		downloadedDataCopy = downloadedData;
	}
	{
		lock_guard<mutex> printLock(printMtx);
		cout << "Process Downloaded data :::content:-\n" << downloadedDataCopy;
	}

}