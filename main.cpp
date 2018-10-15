/* Scheduling Processes and Avoiding Deadlocks
 * Jake Allport
 * Jeremy Gouveia
 *
 * Started: 5/12/2018
 * Last Modified: 5/24/2018 
 */
#include <iostream>
#include<vector>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>
#include "List.h"


using namespace std;

//************* TOTAL TIME ********************//
int duration;
//************* TOTAL TIME ********************//


//**************************** FUNCTION DECLERATIONS ***************
void SystemConfig(string);
void jobArrival(string);
void requestDevice(string);
void run(Jobs,string,string);
void releaseDevice(string);
void Display(string);
void wait(int);
//**************************** FUNCTION DECLERATIONS ****************



//****************************  SYS CFG VARIABLES *******************

//system to be simulated starts at
string timeStart;
//total mainMemory
string mainMemory;
int mainMemory_int;
int totalMemory;
//time quantum or time slice
string timeQuantum;
// Num serial devices;
string serialDevice;
//variables
ofstream outputfile;
// ****************************  SYS CFG VARIABLES ******************



//JOB ARRIVAL VARIABLES
//  **************************** Job Number *************************
string jobNum_Arrival;
// **************************** Job Number **************************


//  **************************** priority of arrived Number  ********
string priority;
//  **************************** priority of arrived Number  ********

//**************************** amount of memory required*************
string requiredMemory;
// ****************************   max number of devices   ***********
string maxDemand;
// ****************************  runTime ****************************
string runTime;
// ****************************  runTime ****************************


// **************************** JOB ARRIVAL VARIABLES  **************
string arrivalTime;
// **************************** JOB ARRIVAL VARIABLES  **************



// **************************** CREATE JOB Object *******************

//***TOTAL JOBS
int jobCount=0;

//***TOTAL JOBS

Jobs aJob;
//std::vector<Jobs> jobsVector;


// **************************** CREATE JOB Object ******************


// **************************** CREATE LINKED LIST QUEUES **********

List Released;

List Hold1;

List Hold2;

List waitQueue;

List readyQueue;
// **************************** CREATE LINKED LIST QUEUES **********


// **************************** START CLOCK ***********************

// start;

clock_t start = std::clock();

// **************************** START CLOCK **********************

int main() {




    ifstream inFile;

    inFile.open("OS.txt");

    if(!inFile){
        outputfile<<"Unable to open file";
        exit(1);
    }
    
    //WRITING TO FILE
    
    outputfile.open("output.txt");


    string str;

    while(std::getline(inFile, str)){

        //******************SYSCFG***********************//
        if (str[0]=='C'){
            SystemConfig(str);
            int n = std::stoi(timeStart);
            //function to wait the specified time in SysConf
            wait(n);


        }
        //******************JOBARRIVAL***********************//
        if(str[0]=='A'){
            jobArrival(str);
            //jobsVector.push_back(aJob);
            jobCount++;
            // jobsVector.resize(jobCount);

        }
        //******************DEVICEREQUEST***********************//

        if(str[0]=='Q')
            requestDevice(str);

        //******************DEVICERELEASE***********************//

        if(str[0]=='L')
            releaseDevice(str);
        //******************DISPLAY***********************//

        if(str[0]=='D')
            Display(str);

    }


    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile <<"End Time is: " << duration <<'\n';

    outputfile.close();
    return 0;
}


//************WAIT TILL START TIME *****************//
void wait (int seconds ){
    //outputfile<<"Time Ran"<<'\n';
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait) {}
}
//************WAIT TILL START TIME *****************//





//*********************** SystemConfig START *******************//
void SystemConfig(string str){

    /*


 //SYS CFG VARIABLES

     //system to be simulated starts at
     string timeStart;
     //total mainMemory
     string mainMemory;
     //time quantum or time slice
     string timeQuantum;
     // Num serial devices;
     string serialDevice;
     //variables

 //SYS CFG VARIABLES
 */



    //***************** Get timeStart value *******************//
    int i=2;
    while(str[i]!=' '){

        timeStart += str[i];
        i++;
    }
    //***************** Get timeStart value *******************//


    //********** Get mainMemory value *********************//
    i=0;
    while(str[i]!='M'){
        i++;
    }

    i+=2;
    while(str[i]!=' '){
        mainMemory+=str[i];
        i++;
    }
    //copy to int
    mainMemory_int=std::stoi(mainMemory);

    totalMemory=std::stoi(mainMemory);



    //********** Get Serial value *********************//
    i=0;
    while(str[i]!='S'){
        i++;
    }

    i+=2;
    while(str[i]!=' '){
        serialDevice+=str[i];
        i++;
    }

    //********** Get timeQuantum value *********************//

    i=0;
    while(str[i]!='Q'){
        i++;
    }
    i+=2;

    while(str[i]!='\0'){
        timeQuantum+=str[i];
        i++;
    }

    outputfile<<"//*********************** SYSCONFIG START *******************//"<<'\n';

    outputfile<<"Time Start "<<timeStart<<'\n';
    outputfile<<"Main Memory "<<mainMemory<<'\n';
    outputfile<<"Serial Devices "<<serialDevice<<'\n';
    outputfile<<"Time Quantum "<<timeQuantum<<'\n';

}


//*********************** SystemConfig END *******************//


//*********************** JOB Arrival START ***************************//

void jobArrival(string str){

//JOB ARRIVAL VARIABLES
//Job Number
    /*string*/ jobNum_Arrival=" " ;
//priority of arrived Number
    /*string*/ priority=" ";

//amount of memory required
    /*string*/ requiredMemory=" ";
//max number of devices
    /*string*/  maxDemand=" ";
//runTime
    /*string*/  runTime=" ";

//time arrives
    /*string*/  arrivalTime=" ";
//JOB ARRIVAL VARIABLES



    //********** arrivalTime *********************//

    int i=2;
    while(str[i]!=' '){
        arrivalTime+=str[i];
        i++;
    }
    //add arrival time to the object
    aJob.Job_Arrivaltime=arrivalTime;

    //********** arrivalTime *********************//



    //**************** REQUIRED MEMORY *****************//
    i=0;
    while(str[i]!='M'){
        i++;
    }
    i+=2;
    while(str[i]!=' '){
        requiredMemory+=str[i];
        i++;
    }
    aJob.Job_Memory=requiredMemory;

    //**************** REQUIRED MEMORY *****************//


    //**************** MAX DEVICES *****************//
    i=0;
    while(str[i]!='S'){
        i++;
    }
    i+=2;
    while(str[i]!=' '){
        maxDemand+=str[i];
        i++;
    }

    aJob.Job_Devices=stoi(maxDemand);

    //**************** MAX DEVICES *****************//

    //**************** RUN TIME *****************//
    i=0;
    while(str[i]!='R'){
        i++;
    }
    i+=2;
    while(str[i]!=' '){
        runTime+=str[i];
        i++;
    }
    aJob.Job_Runtime=stoi(runTime);
    
    //**************** RUN TIME*****************//

    //********** JOB NUMBER *********************//
    i=0;
    while(str[i]!='J'){
        i++;
    }

    i+=2;
    while(str[i]!=' '){
        jobNum_Arrival+=str[i];
        i++;
    }
    aJob.Job_Number=jobNum_Arrival;

    //********** JOB NUMBER *********************//


    //********** PRIORITY *********************//

    i=0;
    while(str[i]!='P'){
        i++;
    }
    i+=2;
    while(str[i]!='\0'){
        priority+=str[i];
        i++;
    }
    aJob.Job_Priority=priority;

    //********** PRIORITY *********************//

    outputfile<<"//*********************** JOB ARRIVAL START *******************//"<<'\n';

    outputfile<<"Arrival Time "<<aJob.Job_Arrivaltime<<'\n';

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile<<"Current Time "<<duration<<'\n';

    if(duration!=stoi(aJob.Job_Arrivaltime)){
        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

        outputfile<<"Waiting for: "<<stoi(aJob.Job_Arrivaltime)-duration<<" Seconds\n";
        wait(stoi(aJob.Job_Arrivaltime)-duration);
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    outputfile<<"Current Time "<<duration<<'\n';



    outputfile<<"Job Number "<<jobNum_Arrival<<'\n';
    outputfile<<"Required Memory "<<requiredMemory<<'\n';
    outputfile<<"Priority "<<priority<<'\n';


    /*
    outputfile<<"Arival Time "<<arrivalTime<<'\n';
    outputfile<<"Run Time "<<runTime<<'\n';
    outputfile<<"Max Memory"<<maxDemand<<'\n';
    outputfile<<"Priority "<<priority<<'\n';
    */
    outputfile<<"Possible?";

    if(totalMemory>=stoi(requiredMemory) && stoi(serialDevice)>=stoi(maxDemand)){
        outputfile<<" Yes"<<'\n';
        if(mainMemory_int>=std::stoi(requiredMemory)){
            outputfile<<"Run"<<'\n';

            aJob.Job_Running=true;
            readyQueue.AddNode(aJob);
            outputfile<<"In Ready Queue\n";
            mainMemory_int=mainMemory_int-std::stoi(requiredMemory);
            outputfile<<"Memory Left "<<mainMemory_int<<'\n';
            readyQueue.PrintList();
        }
        else {
            outputfile << "HOLD" << '\n';
            //  outputfile<<aJob.Job_Priority<<'\n';
            if (stoi(aJob.Job_Priority) == 1) {
                aJob.Job_onHold1 = true;

                //******************ADDTO QUEUE***********************//

                Hold1.AddNode(aJob);
                Hold1.sort();
                outputfile<<"In Hold 1\n";

                Hold1.PrintList();
                //******************ADDTO QUEUE***********************//

            }
                //******************ADDTO QUEUE***********************//


            else if(stoi(aJob.Job_Priority)==2){
                aJob.Job_onHold2=true;
                //******************ADDTO QUEUE***********************//
                Hold2.AddNode(aJob);
                outputfile<<"In Hold 2\n";
                Hold2.PrintList();
                //******************ADDTO QUEUE***********************//

            }
        }
    }
    else if(totalMemory<std::stoi(requiredMemory) || (aJob.Job_Devices)>std::stoi(serialDevice)){
        outputfile<<" NO; too much memory/too many devices\n";
    }



}

//*********************** jobArrival END *******************//


//*********************** Request Device START *******************//
void requestDevice(string str) {

    int i = 0;
    string timeRequest;
    string jobRequest;
    string numDevices;

    //********** at Time x *********************//

    i = 2;
    while (str[i] != ' ') {
        timeRequest += str[i];
        i++;
    }
    //********** at Time x *********************//


    //********** Job requested *********************//

    i = 0;
    while (str[i] != 'J') {
        i++;
    }

    i += 2;
    while (str[i] != ' ') {
        jobRequest += str[i];
        i++;
    }

    //********** Job requested *********************//


    //********** Number of Devices *********************//


    i = 0;
    while (str[i] != 'D') {
        i++;
    }

    i += 2;
    while (str[i] != '\0') {
        numDevices += str[i];
        i++;
    }

    //********** Number of Devices *********************//


    outputfile << "//*********************** REQUEST DEVICE START *******************//" << '\n';
    outputfile << "Time Requested " << timeRequest << '\n';
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile<<"\nCurrent Time "<<duration<<'\n';

    outputfile << "Job Requested " << jobRequest << '\n';
    outputfile << "Device Number Requested " << numDevices << '\n';
    //find node in readyQueue


    //Paste around line 506

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;


    if(stoi(timeRequest)!=duration){

        duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
        outputfile<<"\nWait until Ready\n";
        wait(stoi(timeRequest)-duration);
    }
    


    run(readyQueue.FindNode(stoi(jobRequest)),timeRequest,numDevices);



}

//*********************** Request Device END *******************//


//*********************** RUN START **********************************//

void run(Jobs aJob,string timeRequest,string numDevices){
    outputfile<<'\n'<<"//*********************** RUN **********************************//\n";

    aJob.Job_devicesRunning=stoi(numDevices);

    outputfile<<"Serial Devices "<<aJob.Job_Devices<<" \nDevices Requested "<<numDevices<<'\n';
    aJob.Job_Devices=aJob.Job_Devices-stoi(numDevices);
    outputfile<< aJob.Job_devicesRunning<<" Devices are now running\n";

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile<<"Current Time "<< duration<<'\n'<<"Run for "<<aJob.Job_Runtime<<" Seconds"<<'\n';
    wait((aJob.Job_Runtime));

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile<<"Current Time "<<duration<<'\n';

}

//*********************** RUN END **********************************//



//*********************** Release Device START *******************//

void releaseDevice(string str){

    int i=0;
    string time_Release;
    string jobNum_Release;
    string numDevice_Release;


    //********** timeRelease *********************//

    i=2;
    while(str[i]!=' '){
        time_Release+=str[i];
        i++;
    }

    //********** timeRelease *********************//


    //********** jobNum *********************//

    i=0;
    while(str[i]!='J'){
        i++;
    }
    i+=2;

    while(str[i]!=' '){
        jobNum_Release+=str[i];
        i++;
    }
    //********** jobNum *********************//

    //********** Device Num *********************//

    i=0;
    while(str[i]!='D'){
        i++;
    }
    i+=2;

    while(str[i]!='\0'){
        numDevice_Release+=str[i];
        i++;
    }

    //********** Device Num *********************//


    outputfile<<"//*********************** RELEASE DEVICE START *******************//"<<'\n';

    outputfile<<"Device Number "<<numDevice_Release<<'\n';
    outputfile<<"Release Time "<< time_Release<<'\n';
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    outputfile<<"Current Time "<<duration<<'\n';
    outputfile<<"\n Current Memory "<<mainMemory_int<<'\n';

    outputfile<<"Job Number to Release "<<jobNum_Release<<'\n';

    mainMemory_int+=stoi(aJob.Job_Memory);
    outputfile<<"\nMain Memory is now "<<mainMemory_int<<'\n';


    readyQueue.DeleteNode(stoi(numDevice_Release));
    
    while(Hold1.head != NULL) {
        readyQueue.AddNode(Hold1.pop());
        Hold1.DeleteNode(stoi(Hold1.pop().Job_Number));
    }
    
    Released.AddNode(aJob);
    readyQueue.PrintList();
    


}

//*********************** Release Device END *******************//


//*********************** DISPLAY START *******************//

void Display(string str){

    string timeDisplay;
    int i=2;
    //********** Time *********************//


    while(str[i]!='\0'){
        timeDisplay+=str[i];
        i++;
    }
    outputfile<<"//*********************** DISPLAY START *******************//"<<'\n';

    outputfile<<"Time Display "<<timeDisplay<<'\n';


    outputfile<<"In readyQueue\n";
    readyQueue.PrintList();
    outputfile<<"In waitQueue\n";
    waitQueue.PrintList();
    outputfile<<"In Hold 1\n";
    Hold1.PrintList();
    outputfile<<"In Hold 2\n";
    Hold2.PrintList();
    outputfile<<"In Released\n";
    Released.PrintList();



}


//*********************** DISPLAY  END *******************//

