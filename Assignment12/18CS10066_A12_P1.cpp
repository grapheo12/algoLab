/* Name: Shubham Mishra
 * Roll No: 18CS10066
 */

#include "bits/stdc++.h"
using namespace std;

class Job{
	public:
		int id;
		int start;	//Arrival Time
		int priority;
		int time;	//Remaining time
		int burst;	//Total time
		int end;
		int startTime;
		Job(){
			id = -1;
			start = -1;
			priority = -1;
			time = -1;
			burst = -1;
			end = -1;
			startTime = -1;
		}
};

int compare(Job j1, Job j2){
	if (j1.time < j2.time)
		return -1;
	else if (j1.time > j2.time)
		return 1;
	else{
		if (j1.id < j2.id)
			return -1;
		else if (j1.id > j2.id)
			return 1;
		else
			return 0;
	}
}

class JobQ{
	public:
		Job* arr;
		int last;
		int size;

		JobQ(int maxSize){
			size = maxSize;
			arr = new Job[size];
			last = 0;
		}

		void heapify(int i){
			while (i > 0 && compare(arr[i], arr[(i + 1) / 2 - 1]) == -1){
				Job temp = arr[i];
				arr[i] = arr[(i + 1) / 2 - 1];
				arr[(i + 1) / 2 - 1] = temp;

				i = (i + 1) / 2 - 1;
			}
		}

		void reheap(){
			int i = 0;
			while (2 * (i + 1) <= last - 1 && (compare(arr[2 * (i + 1) - 1], arr[i]) == -1 || compare(arr[2 * (i + 1)], arr[i]) == -1)){
				if (compare(arr[2 * (i + 1) - 1], arr[2 * (i + 1)]) == -1){
					Job temp = arr[i];
					arr[i] = arr[2 * (i + 1) - 1];
					arr[2 * (i + 1) - 1] = temp;

					i = 2 * (i + 1) - 1;
				}else{
					Job temp = arr[i];
					arr[i] = arr[2 * (i + 1)];
					arr[2 * (i + 1)] = temp;

					i = 2 * (i + 1) - 1;
				}
			}

			if (2 * (i + 1) - 1 == last - 1 && compare(arr[2 * (i + 1) - 1], arr[i]) == -1){
				Job temp = arr[i];
				arr[i] = arr[2 * (i + 1) - 1];
				arr[2 * (i + 1) - 1] = temp;

				i = 2 * (i + 1) - 1;
			}
		}

		void insert(Job j){
			arr[last].id = j.id;
			arr[last].start = j.start;
			arr[last].priority = j.priority;
			arr[last].time = j.burst;
			arr[last].burst = j.burst;

			heapify(last);
			last++;
		}

		Job getMin(){
			return arr[0];
		}

		Job extractMin(){
			last--;
			Job temp = arr[0];
			arr[0] = arr[last];
			arr[last] = temp;

			reheap();
			return arr[last];
		}
};


int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin >> n;

	JobQ **q = new JobQ*[6];
	for (int i = 0; i < 6; i++)
		q[i] = new JobQ(n);
	
	Job *jobs = new Job[n];
	int k = 0;

	Job buff;
	int id, start, burst, priority;
	for (int i = 0; i < n; i++){
		cin >> id >> start >> burst >> priority;
		buff.id = id;
		buff.start = start;
		buff.burst = burst;
		buff.priority = priority;
		int l = 0;
		while (l < k){
			if (jobs[l].start < start)
				l++;
			else
				break;
		}
		k++;
		int j = k;
		while (j > l){
			jobs[j] = jobs[j - 1];
			j--;
		}
		jobs[l].id = buff.id;
		jobs[l].start = buff.start;
		jobs[l].burst = buff.burst;
		jobs[l].priority = buff.priority;
	}

	int sys_clock = 0;
	k = 0;
	Job *order = new Job[n];
	int l = 0;

	while (k < n || q[1] -> last || q[2] -> last || q[3] -> last || q[4] -> last || q[5] -> last){
		//Insert new jobs
		int i = k;
		while (i < n && jobs[i].start == sys_clock){
			q[jobs[i].priority] -> insert(jobs[i]);
			i++;
		}
		k = i;

		//Find the highest priority job
		i = 1;
		while (i <= 5){
			if (q[i] -> last == 0)
				i++;
			else
				break;
		}

		//If all jobs are done
		if (i == 6)
			break;
		
		if (q[i] -> arr[0].time == q[i] -> arr[0].burst)
			q[i] -> arr[0].startTime = sys_clock;

		q[i] -> arr[0].time--;
		if (q[i] -> arr[0].time == 0){
			q[i] -> arr[0].end = sys_clock;
			buff = q[i] -> extractMin();
			//Process done
			int x = 0;
			while (x < l){
				if (order[x].id < buff.id)
					x++;
				else
					break;
			}
			l++;
			int y = l;
			while (y > x){
				order[y] = order[y - 1];
				y--;
			}
			order[x].id = buff.id;
			order[x].startTime = buff.startTime;
			order[x].end = buff.end;

		}else
			q[i] -> reheap();
		
		sys_clock++;
	}

	for (int i = 0; i < n; i++)
		cout << order[i].id << " " << order[i].startTime << " " << order[i].end + 1<< endl;

	return 0;
}