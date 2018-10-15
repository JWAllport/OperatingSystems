/* Scheduling Processes and Avoiding Deadlocks
 * Jake Allport
 * Jeremy Gouveia
 *
 * Started: 5/12/2018
 * Last Modified: 5/24/2018 
 */
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <ctime>


using namespace std;
class Jobs
{
  // Access specifier
public:

  // Data Members
  string Job_Number;
  string Job_Memory;
  string Job_Priority;
  int Job_Devices;
  int Job_Runtime;
  string Job_Arrivaltime;
  int Job_devicesRunning;
  bool Job_Running = false;

  bool Job_onHold1 = false;
  bool Job_onHold2 = false;
  bool Job_Requested = false;
  bool Job_Released = false;


};
