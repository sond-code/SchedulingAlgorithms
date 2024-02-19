/*
Tareq Sarayji 20200130
Taya Jarrar   20200813
Sondos Ali    20200438
el "2ata3at"
*/
#include<iostream>
#include <queue>
using namespace std;

// const float Q1_CPU_PERCENT = 0.6;
// const float Q2_CPU_PERCENT = 0.25;
// const float Q3_CPU_PERCENT = 0.15;

class Process{
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int response_time;
    int turnaround_time;
    int remaining_time;
    // queue<int>* currQ;
public:
    Process(){
        // arrival_time=-1;
        // burst_time=-1;
        waiting_time=0;
        response_time=-1;
        turnaround_time=0;
    }
    void set_id(int id){
        this->id=id;
    }
    void set_arrival_time(int arrival_time){
        this-> arrival_time=arrival_time;
    }
    void set_burst_time(int burst_time){
        this-> burst_time=burst_time;
    }
    void set_waiting_time(int waiting_time){
        this-> waiting_time=waiting_time;
    }
    void set_response_time(int response_time){
        this-> response_time=response_time;
    }
    void set_turnaround_time(int turnaround_time){
        this-> turnaround_time=turnaround_time;
    }
    void set_remaning_time(int remaining_time){
        this-> remaining_time=remaining_time;
    }
    // void set_currQ(queue<int>* currQ){
    //     this-> currQ=currQ;
    // }
   
// --------setters--------getters--------
    int get_id(){
        return id;
    }
    int get_arrival_time(){
        return arrival_time;
    }
    int get_burst_time(){
        return burst_time;
    }
    int get_waiting_time(){
        return waiting_time;
    }
    int get_response_time(){
        return response_time;
    }
    int get_turnaround_time(){
        return turnaround_time;
    }
    int get_remaning_time(){
        return remaining_time;
    }
    // queue<int>* get_currQ(){
    //     return currQ;
    // }
};

// gantt chart is a queue that takes pID and the current starting time and ending time.
// queue containing all processes
class Gantt{
public:
    queue<Process> pG;
    queue<int> pID;
    queue<int> start_time;
    queue<int> end_time;
};

// gantt chart is a queue that takes pID and the current starting time and ending time.

// queue containing all processes
queue<Process> Qrr8;
queue<Process> Qrr16;
queue<Process> Qfcfs;

// total_time to calculate total burst time
int total_time;
// input the number of processes
void numberOfProcesses(int *numP){
    cout<<"Enter the number of processes: ";
    cin>>*numP;
}

// sort an array of objects based on arrival time
void sort_on_AT(Process *p, int numP){
  int min_index;
  for(int i=0;i<numP-1;i++){
    min_index=i;
    for(int j=i+1;j<numP;j++){
      if(p[j].get_arrival_time()<p[min_index].get_arrival_time()){
        min_index=j;
      }
      if(min_index!=i){
        Process temp=p[min_index];
        p[min_index]=p[i];
        p[i]=temp;
      }
    }
  }
return;
}

// input processes data
void input_process(Process *p,int numP){
    int time=0;
    for(int i=0;i<numP;i++){
        p[i].set_id(i);
        // cout<<"\nProcess P"<<i<<":\n";
        // cout<<"Enter the arrival time: ";
        cin>>time;
        p[i].set_arrival_time(time);
        // cout<<"Enter the burst time: ";
        cin>>time;
        total_time+=time;
        p[i].set_burst_time(time);
    }
    // sort based on arrival time
    sort_on_AT(p,numP);
    // enqueue all processes into Q
    for(int i=0;i<numP;i++){
        Qrr8.push(p[i]);
    }
    return;
}

Gantt info;
void RR(int *curr_time,int CPU_time){
    int Qtime=8;
    while(Qrr8.size()>0 && *curr_time<CPU_time){
        Process p=Qrr8.front();
        if(p.get_burst_time()+ *curr_time>CPU_time){//**check
            p.set_remaning_time(p.get_remaning_time()-(CPU_time-*curr_time));
            p.set_waiting_time((*curr_time-p.get_turnaround_time())+p.get_waiting_time());
            *curr_time+=CPU_time-*curr_time;
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            return;
        }
        if(p.get_burst_time()<=Qtime){
            p.set_waiting_time(*curr_time-p.get_arrival_time());
            *curr_time+=p.get_burst_time();
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            p.set_remaning_time(0);
            Qrr8.pop();
            info.pG.push(p);
        }
        else{
            p.set_waiting_time(*curr_time-p.get_arrival_time());
            *curr_time+=Qtime;
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            p.set_remaning_time(*curr_time-Qtime);
            Qrr16.push(p);
            if(p.get_remaning_time() == 0){
                info.pG.push(p);
            }
        }
    }
    return;
}
void RR16(int *curr_time,int CPU_time){
    int Qtime=16;
    while(Qrr16.size()>0 && *curr_time<CPU_time){
        Process p=Qrr16.front();
        if(p.get_remaning_time()+ *curr_time>CPU_time){//**check
            p.set_remaning_time(p.get_remaning_time()-(CPU_time-*curr_time));
            p.set_waiting_time((*curr_time-p.get_turnaround_time())+p.get_waiting_time());
            *curr_time+=CPU_time-*curr_time;
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            Qrr16.pop();
            Qfcfs.push(p);
            return;
        }
        if(p.get_remaning_time()<=Qtime){
            p.set_waiting_time(*curr_time-p.get_arrival_time());
            *curr_time+=p.get_burst_time();
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            p.set_remaning_time(0);
            Qrr16.pop();
            info.pG.push(p);
        }
        else{
            p.set_waiting_time(*curr_time-p.get_arrival_time());
            *curr_time+=Qtime;
            p.set_turnaround_time(*curr_time-p.get_arrival_time());
            p.set_remaning_time(*curr_time-Qtime);
            Qfcfs.push(p);
            Qrr16.pop();
            if(p.get_remaning_time() == 0){
                info.pG.push(p);
            }
        }
    }
    return;
}
void FCFS(int *curr_time){
    while(Qfcfs.size()>0){
        Process p = Qfcfs.front();
        Qfcfs.pop();
        p.set_waiting_time((*curr_time-p.get_turnaround_time())+p.get_waiting_time());
        p.set_turnaround_time(*curr_time-p.get_arrival_time());
        if(p.get_burst_time()==-1){
            p.set_burst_time(*curr_time-p.get_arrival_time());
        }
        *curr_time+=p.get_remaning_time();
        p.set_remaning_time(0);
        info.pG.push(p);
    }
    return;
}

void Execute(){
    int curr_time=0,curr_P_ID;
    float avgwt=0,avgtat=0;

    float Q1_CPU_time=0.6*total_time;
    float Q2_CPU_time=(0.6+0.25)*total_time;
    float Q3_CPU_time=(0.6+0.25+0.15)*total_time;
   
    while(curr_time<total_time){
        if(curr_time<Q1_CPU_time){
            RR(&curr_time,Q1_CPU_time);
        }
        else if(curr_time<Q2_CPU_time){
            RR16(&curr_time,Q2_CPU_time);
        }
        else {
            FCFS(&curr_time);
        }
    }
    return;
}

// void draw_chart() {
// }

void average_function(int numP) {
    float res_avg = 0;
    float wait_avg = 0;
    float turn_avg = 0;
    for (int i = 0; i < numP; i++) {
        res_avg += info.pG.front().get_response_time();

        wait_avg+= info.pG.front().get_waiting_time();
        turn_avg+= info.pG.front().get_turnaround_time();
        info.pG.pop();
    }
   
    res_avg = res_avg / numP;
    wait_avg = wait_avg / numP;
    turn_avg = turn_avg / numP;

    cout <<"the avarage response time is "<< res_avg<<endl;
    cout << "the avarage waiting time is " << wait_avg<<endl;
    cout << "the avarage turnAround time is " << turn_avg<<endl;
   
}

int main() {
    int numP;
    numberOfProcesses(&numP);
    Process p[numP];
    input_process(p, numP);
    Execute();
    average_function( numP);

    return 0;
}
