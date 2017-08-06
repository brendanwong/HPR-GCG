
#include <iostream>

static const std::string FR_EXTRUDE = "200";
static const std::string FR_MOVE_XY = "6000";
static const std::string DWELL = "1000";
static const std::string Z_FEEDRATE = "400";

static const std::string Z_START_CACL2 = "2.5";
static const std::string Z_MOVE = "5";

static const std::string EXTRUDE = "1";

static const std::string Z_START_ALGINATE = "10";
static const double ALG_EXT = 2.4;
static const double ALG_EXT_REV = 0.8;
static const int ALG_DWELL = 3000;

static const std::string Z_START_ABTS = "10";
static const double ABTS_EXT = 1.7;
static const double ABTS_EXT_REV = 0.4;
static const int FR_ABTS_EXT = 50;

static const std::string DISH_HEIGHT = "25";

static const std::string COORD_1 = "30";
static const std::string COORD_2 = "130";

static const int X_BORDER = 40;
static const int Y_BORDER = 40;
static const int DISH_DIAMETER = 100;

int main(int argc, const char * argv[]) {
    std::string output = "";
    
    std::string nameInput = "Brendan Wong";
    int yearInput = 2017;
    int monthInput = 8;
    int dayInput = 5;
    int heightInput = 5; //arrayHeight
    int widthInput = 6; //arrayWidth
    int positionInput = 1; //position
    int materialInput = 1; //material
    int X_MOVE;
    int Y_MOVE;
    int calc;
    
    X_MOVE = DISH_DIAMETER - X_BORDER;
    X_MOVE = X_MOVE / widthInput;
    
    Y_MOVE = DISH_DIAMETER - Y_BORDER;
    Y_MOVE = Y_MOVE / heightInput;
    
    output += "G90\n";
    output += "G1 Z" + DISH_HEIGHT + " F1000\n";
    
    switch(positionInput)
    {
        case 1:
            output += "G1 X" + COORD_1 + " Y" + COORD_1 + " F" + FR_MOVE_XY + "\n";
            break;
        case 2:
            output += "G1 X" + COORD_2 + " Y" + COORD_1 + " F" + FR_MOVE_XY + "\n";
            break;
        case 3:
            output += "G1 X" + COORD_1 + " Y" + COORD_2 + " F" + FR_MOVE_XY + "\n";
            break;
        case 4:
            output += "G1 X" + COORD_2 + " Y" + COORD_2 + " F" + FR_MOVE_XY + "\n";
    }
    
    switch(materialInput)
    {
        case 1:
            output += "G1 Z" + Z_START_CACL2 + " F1000\n";
            break;
        case 2:
            output += "G1 Z" + Z_START_ALGINATE + " F1000\n";
            break;
        case 3:
            output += "G1 Z" + Z_START_ABTS + " F1000\n";
            break;
            
    }
    
    
    output += "\nG91\n\n";
    
    switch(materialInput)
    {
            //cacl2
        case 1:
            for (int row = 0; row < heightInput; row++)
            {
                for (int col = 0; col < (widthInput - 1); col++)
                {
                    output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
                    output += "G4 P" + DWELL + "\n";
                    output += "G1 Z" + Z_MOVE + " F" + Z_FEEDRATE + "\n";
                    calc = row % 2 ? -1 : 1;
                    calc *= X_MOVE;
                    std::string temp  = std::to_string(calc);
                    output += "G1 X" + temp + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
                }
                output += "G1 E" + EXTRUDE + " F" + FR_EXTRUDE + "\n";
                output += "G4 P" + DWELL + "\n";
                output += "G1 Z" + Z_MOVE + " F" + Z_FEEDRATE + "\n";
                
                if (row < heightInput - 1)
                {
                    output += "G1 Y" + std::to_string(Y_MOVE) + " F" + FR_MOVE_XY + "\n";
                    output += "G1 Z-" + Z_MOVE + " F" + Z_FEEDRATE + "\n\n";
                }
                else
                    output += "\n\n";
            }
            output += "G90\n";
            output += "G1 Z" + DISH_HEIGHT + " F1000\n";
            output += "G1 E-.5 F50\n"; //reverse extrude to prevent dribbling
            output += "G1 X100 Y10 F6000\n";
            output += "M84\n";
            break;
            
            
            //hpr
        case 2:
            for (int row = 0; row < heightInput; row++)
            {
                for (int col = 0; col < (widthInput - 1); col++)
                {
                    output +=
                }
            }
            
            
            
            
            
            
            break;
            
            //abts
        case 3:
            break;
    }
    
    
    
    
    
    
    
    
    
    std::cout << output;
    
    
    
    
    
    
    
    
}




















































































