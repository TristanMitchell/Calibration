//
//  Program to read a .csv file.
//
// Import library that defines the ifstream object.
#include <fstream>
// Import library that defines cout object.
#include <iostream>
// Import library that provides the getline() function.
#include <string>
// Import library that defines the stringstream object.
#include <sstream>
//Need for quoted functionality
#include <iomanip>
// Need for access to pow() function
#include <cmath>
// Specify default namespace.
using namespace std;
//variables
double k = 0.23637841; // spring constant
double WorkingSlope = 0; // used to store the appropriate Working EQ slope for calculations 
double WorkingIntercept = 0; // used to store the appropriate Working EQ intercept for calculations
double WorkingSlope4745 = 707.618973576853; // calibration done with 0.4785 pin, difference in gauge pin weight taken into account in uncertainty. Input the slope of the working equation from the 0.4745 pin in minor marks/lbf
double WorkingSlope4785 = 707.618973576853; // input the slope of the working equation from the 0.4785 pin in minor marks/lbf
double WorkingIntercept4745 = -132.785964676194; // (based on .4785, taken into account in uncertainty) input the slope of the working equation from the 0.4785 pin in minor marks
double WorkingIntercept4785 = -132.785964676194; //  input the slope of the working equation from the 0.4785 pin in minor marks
double setupheightstock = 3.178; //distance from top edge of hole to baseplate
double setupheight = 0; // stores the height of the top edge of the measured hole from the baseplate
int response1 = 0; // gets a response for the diameter of the gauge pin
int response2 = 0; // gets the number of stopper bolt shims
double maxforce = 0; // gets the prefered maximum force
double diameter = 0; // stores diameter of gauge pin that is being used
double HeadHeight = 0; // stores the height of the top of the stopper bolt head
double weight = 0; // stores the weight of the sliding assembly
double weight1 = 0.1661875; // GUESSED!!! assigns a wieght in lbs to the sliding assembly of 0.4745" diameter gauge pin
double weight2 = 0.1561875; // assigns a wieght in lbs to the sliding assembly of 0.4785" diameter gauge pin
double minormarkseq = 0; // calculation value for equivelnt number of marks needed for specified max force
double majormarks = 0; // calculation value for number of major marks needed for specified max force
double minormarks = 0; // calculation value for number of minor marks needed for specified max force
double revolutions = 0; // calculation value for number of revolutions needed for specified max force
float raiseinches = 0; // stores height to raise device if needed
float lowerinches = 0; // stores height to lower device if needed
float uncertainty = 0.00742; // uncertianty in lbf
char char1 = 'y';
int main () 
{
    while (char1 == 'y')
    {

    // Getting the diameter of the gauge pin
    cout << "Are you using a gauge pin within the diameters of 0.4745 in to 0.4785 in?" << endl;
    cout << "1:     Yes" << endl;
    cout << "2:     No" << endl;
    cin >> response1;
    if (response1==1)   
    {
        diameter=0.4785;
    }
    else
    {
        
        cout << endl << endl;
        cout << "Please recalibrate the device for your gauge pin selection and update the program variables, then restart the program!" << endl;
        cout << endl << endl;
        while (1==1);
        {
            
        }
    }
    

    // Assigning a weight of the sliding assembly based on diameter of gauge pin
    if (response1 == 1)
    {
        weight = weight1;
        WorkingSlope = WorkingSlope4785;
        WorkingIntercept = WorkingIntercept4785;
    }
   


    // Getting the number of stopper bolt shims
    cout << "How many shims are you using underneath the stopper bolt?" << endl;
    cout << "1:     1" << endl;
    cout << "2:     2" << endl;
    cout << "3:     3" << endl;
    cout << "4:     4" << endl;
    cout << "5:     5" << endl;
    cin >> response2;
    if (response2==1 or response2==2 or response2==3 or response2==4 or response2==5)   
    {
        HeadHeight=5+(0.0625*response2);
    }
    else
    {
        cout << "Please restart and type the 1 through 5 corresponding to your choice." << endl << endl;
    }
    //cout << "The head height is " << HeadHeight << "inches" << endl;
    

    // Gets the height between the baseplate and the top edge of the hole
    cout << "What is the distance between the face bracket and the top edge of the hole to be measured? Answer in inches and type only the numerical value in decimal form. Do not enter the unit." << endl;
    cin >> setupheight;
    setupheight = setupheight + ((response2-1)*-0.0625);
    // Gets the preferred max force
    cout << "What would you like to set the maximum force to (in lbf)? Type only the number" << endl;
    cout << "* Note  - this must be higher than 0.157 lbf *" << endl;
    cin >> maxforce;
    cout << endl;


    // Tells the user which settings to use
    minormarkseq =  (-1*(setupheight-setupheightstock)*(10*25.4/1.5))+(WorkingSlope*maxforce) + WorkingIntercept;
    
    //cout << "# of equivalent minor marks: " << minormarkseq << endl;
    revolutions = int(minormarkseq/10);
    minormarks = ((int(minormarkseq))-double((10*revolutions)))/1;
    majormarks = int(revolutions/5);
    revolutions = revolutions - (majormarks*5);
    raiseinches = ((maxforce-0.3)*(1/k))+(setupheightstock-setupheight);
    lowerinches = ((0.3-maxforce)*(1/k))+(setupheight-setupheightstock);
    if (majormarks>2 or (majormarks==2 & revolutions>1 & minormarks>0))
    {
        cout << "------------------------------------------------------------------------------------------------"<< endl;
        cout << "The measured object must be raised. Please raise the object " << setprecision(3) << raiseinches << " inches and restart the program!" << endl;
        cout << "------------------------------------------------------------------------------------------------"<< endl << endl << endl;

    }
    else if ((majormarks<0 or (majormarks==0 & revolutions<1)))
    {
        cout << "------------------------------------------------------------------------------------------------"<< endl;
        cout << "The measured object must be lowered. Please lower the object " << setprecision(3) << lowerinches << " inches and restart the program!" << endl;
        cout << "------------------------------------------------------------------------------------------------"<< endl << endl << endl;

    }
    else
    {
        cout << "------------------------------------------------------------------------------------------------"<< endl;
        cout << "Set the device to " << majormarks << " major marks " << revolutions << " revolutions and "<< minormarks << " minor marks." << endl;
        cout << "------------------------------------------------------------------------------------------------"<< endl << endl << endl;
    }
    
    
    

    }
}