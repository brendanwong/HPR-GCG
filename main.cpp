#include <iostream>

using namespace std;

static const int FR_EXTRUDE = 200;
static const int FR_MOVE_XY = 6000;
static const int DWELL = 1000;
static const int Z_FEEDRATE = 400;

static const double Z_START_CACL2 = 2.5;
static const int Z_MOVE = 5;

static const int EXTRUDE = 1;

static const int Z_START_ALGINATE = 10;
static const int ALG_EXT = 2.4;
static const int ALG_EXT_REV = 0.8;
static const int ALG_DWELL = 3000;

static const int Z_START_ABTS = 10;
static const int ABTS_EXT = 1.7;
static const int ABTS_EXT_REV = 0.4;
static const int FR_ABTS_EXT = 50;

static const int DISH_HEIGHT = 25;
static const int PRINT_AREA = 60;
static const int DIST_3x3 = 20;
static const int DIST_4x4 = 14;
static const int COORD_1 = 30;
static const int COORD_2 = 130;

static const int NUM_TRYS = 3;


static const int X_BORDER = 40;
static const int Y_BORDER = 40;
static const int DISH_DIAMETER = 100;



void arrayPrint(int material, int arrayWidth, int arrayLength, int X_MOVE, int Y_MOVE);

int main()
{
    //initial file info
    
    string name;
    int position, material, arrayWidth, arrayHeight, X_MOVE, Y_MOVE;
    
    cout << "Enter name: ";
    cin >> name;
    
    cout << "Enter material (1 for CaCl2, 2 for HPR, 3 for ABTS): ";
    cin >> material;
    
    if (material > 3 || material < 1)
    {
        cout << "please enter a valid material\n";
    }
    
    cout << "Enter position: ";
    cin >> position;
    
    if (position > 4 || position < 1)
    {
        cout << "please enter a valid position\n";
    }
    
    cout << "Enter a width for the array (up to 8): ";
    cin >> arrayWidth;
    
    if (arrayWidth > 8 || arrayWidth < 1)
    {
        cout << "please enter a valid width\n";
    }
    
    cout << "Enter a height for the array (up to 8): ";
    cin >> arrayHeight;
    
    if (arrayHeight > 8 || arrayHeight < 1)
    {
        cout << "please enter a valid width\n";
    }
    
    
    
    //display entered info for verification
    
    cout << endl;
    cout << "name: " << name << endl;
    
    cout << "material: ";
    switch(material)
    {
        case 1:
            cout << "CaCl2\n";
            break;
        case 2:
            cout << "HPR\n";
            break;
        case 3:
            cout << "ABTS\n";
            break;
    }
    cout << "postition: " << position << endl;
    
    cout << "size: " << arrayWidth << "x" << arrayHeight << endl;
    
    cout << endl;
    
    
    
    //dynamic array move calculations
    
    //assuming set dish diameter of 100mm
    
    
    
    X_MOVE = DISH_DIAMETER - X_BORDER;
    X_MOVE = X_MOVE / arrayWidth;
    
    Y_MOVE = DISH_DIAMETER - Y_BORDER;
    Y_MOVE = Y_MOVE / arrayHeight;
    
    
    
    
    
    //begin building gcode
    
    cout << "G90\n";
    cout << "G1 Z" << DISH_HEIGHT << " F1000\n";
    
    switch(position)
    {
        case 1:
            cout << "G1 X" << COORD_1 << " Y" << COORD_1 << " F" << FR_MOVE_XY << endl;
            break;
        case 2:
            cout << "G1 X" << COORD_2 << " Y" << COORD_1 << " F" << FR_MOVE_XY << endl;
            break;
        case 3:
            cout << "G1 X" << COORD_1 << " Y" << COORD_2 << " F" << FR_MOVE_XY << endl;
            break;
        case 4:
            cout << "G1 X" << COORD_2 << " Y" << COORD_2 << " F" << FR_MOVE_XY << endl;
            break;
    }
    
    //detects material type, sets variables for each
    switch(material)
    {
        case 1:
            cout << "G1 Z" << Z_START_CACL2 << " F1000\n";
            break;
        case 2:
            cout << "G1 Z" << Z_START_ALGINATE << " F1000\n";
            break;
        case 3:
            cout << "G1 Z" << Z_START_ABTS << " F1000\n";
            break;
    }
    
    cout << "\nG91\n";
    
    
    arrayPrint(material, arrayWidth, arrayHeight, X_MOVE, Y_MOVE);
    
    
}


void arrayPrint(int material, int arrayWidth, int arrayHeight, int X_MOVE, int Y_MOVE)
{
    
    switch(material)
    {
        case 1:
            for (int row = 0; row < arrayHeight; row++)
            {
                for (int col = 0; col < (arrayWidth - 1); col++)
                {
                    cout << "G1 E" << EXTRUDE << " F" << FR_EXTRUDE << endl;
                    cout << "G4 P" << DWELL << endl;
                    cout << "G1 Z" << Z_MOVE << " F" << Z_FEEDRATE << endl;
                    cout << "G1 X" << (row % 2 ? -1 : 1)*X_MOVE << " F" << FR_MOVE_XY << endl;
                    cout << "G1 Z-" << Z_MOVE << " F" << Z_FEEDRATE << endl << endl;
                }
                cout << "G1 E" << EXTRUDE << " F" << FR_EXTRUDE << endl;
                cout << "G4 P" << DWELL << endl;
                cout << "G1 Z" << Z_MOVE << " F" << Z_FEEDRATE << endl;
                
                if (row < arrayHeight)
                {
                    cout << "G1 Y" << Y_MOVE << " F" << FR_MOVE_XY << endl;
                    cout << "G1 Z-" << Z_MOVE << " F" << Z_FEEDRATE << endl;
                }
                else
                    cout << endl;
            }
            cout << "G90\n";
            cout << "G1 Z" << DISH_HEIGHT << " F1000\n";
            cout << "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
            cout << "G1 X100 Y10 F6000\n";
            cout << "M84\n";
            break;
        case 2:
            for (int row = 0; row < arrayHeight; row++)
            {
                for (int col = 0; col < (arrayWidth - 1); col++)
                {
                    cout << "G1 E" << ALG_EXT << " F" << FR_EXTRUDE << endl;
                    cout << "G1 E-" << ALG_EXT_REV << " F" << FR_EXTRUDE << endl;
                    
                }
            }
            
    }
    
}


/*
 
 Enter name: brendan
 Enter material (1 for CaCl2, 2 for HPR, 3 for ABTS): 1
 Enter position: 1
 Enter a width for the array (up to 8): 3
 Enter a length for the array (up to 8): 3
 
 brendan
 CaCl2
 1
 3x3
 
 G90
 G1 Z25 F1000
 G1 X30 Y30 F6000
 G1 Z2.5 F1000
 
 G91
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 Y20 F6000
 G1 Z-5 F400
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X-20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X-20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 Y20 F6000
 G1 Z-5 F400
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 G1 X20 F6000
 G1 Z-5 F400
 
 G1 E1 F200
 G4 P1000
 G1 Z5 F400
 
 G90
 G1 Z25 F1000
 Program ended with exit code: 0
 
 */










