#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
using namespace std;

    double emissions_strength; //emission strength of source GRAMS/SECOND
    double pi = 3.1415;
    double height_effective_stack, height_stack, height_plume_rise;  //effective height of emissions stack = stack height + plume rise
    string direction[3] = {"downwind (x)", "perpendicular to the wind (y)", "vertical (z)"};// coordinate directions x = downwind, y = perpindicular to wind, z = vertical
    double x_m, y_m, z_m, x_km;
    double between[3] = {x_m, y_m, z_m};
    double plume_wind_speed; 
    double surface_wind_speed;
    string more_info;
    string d_or_n;
    string in_solar_rad;
    string night_cloud_cover;
    string stack_height_calc_option;
    string calc_stability_class, input_stability_class;
    string input_sigmas;
    string input_info;
    double stability_classes_daytime_strong[5] = {0,0,1,2,2};// A, A, B, C, C
    double stability_classes_daytime_moderate[5] = {0,1,1,2,3}; // A, B, B, C, D
    double stability_classes_daytime_slight[5] = {1,2,2,3,3}; // B, C, C, D, D
    double stability_classes_nightime_less_clouds[5] = {4,4,3,3,3}; // E, E, D, D, D
    double stability_classes_nightime_more_clouds[5] = {5,5,4,3,3}; // F, F, E, D, D
    string Numeric_to_Alphabet[6] = {"A", "B", "C", "D", "E", "F"}; //0=A 1=B 2=C 3=C 4=D 5=E 
    int wind_array_index;
    int num_pasquill_stability_class;
    double sigma_y;
    double sigma_z;
    double var_a, var_b, var_c, var_d;
    double sigma_z_class_a_parameters[9][3] = {
        {0.10, 122.800, 0.94470},
        {0.15, 158.080, 1.05420},
        {0.20, 170.220, 1.09320},
        {0.25, 179.520, 1.12620},
        {0.30, 217.410, 1.26440},
        {0.40, 258.890, 1.40940},
        {0.50, 346.750, 1.72830},
        {3.11, 453.850, 2.11660},
        {5.00, 0, 0},
    };
    double sigma_z_class_b_parameters[3][3] = {
        {0.20, 90.673, 0.93198},
        {0.40, 98.483, 0.98332},
        {5.00, 109.300, 1.09710},
    };
    double sigma_z_class_d_parameters[6][3] = {
        {0.30, 34.459, 0.86974},
        {1.00, 32.093, 0.81066},
        {3.00, 32.093, 0.64403},
        {10.00, 33.504, 0.60486},
        {30.00, 36.650, 0.56589},
        {10000, 44.053, 0.51179},
    };
    double sigma_z_class_e_parameters[9][3] = {
        {0.10, 24.260, 0.83660},
        {0.30, 23.331, 0.81956},
        {1.00, 21.628, 0.75660},
        {2.00, 21.628, 0.63077},
        {4.00, 22.534, 0.57154},
        {10.00, 24.703, 0.50527},
        {20.00, 26.970, 0.46714},
        {40.00, 35.420, 0.37615},
        {10000, 47.618, 0.29592}
    };
    double sigma_z_class_f_parameters[10][3] = {
        {0.20, 15.209, 0.81558},
        {0.70, 14.457, 0.78407},
        {1.00, 13.953, 0.68465},
        {2.00, 13.953, 0.63227},
        {3.00, 14.823, 0.54503},
        {7.00, 16.187, 0.46490},
        {15.00, 17.836, 0.41507},
        {30.00, 22.651, 0.32681},
        {60.00, 27.074, 0.27436},
        {10000, 34.219, 0.21716}
    };
    double theta;
    int row_num;
    double x_dist_limit;
    double conc, conc_ug;
    string emissions_strength_input, check_num_output;
    double back_2_double;
    string between_input[3];
    string plume_wind_speed_input;
    string height_effective_stack_input, height_stack_input, height_plume_rise_input;
    string surface_wind_speed_input;
    string sigma_y_input, sigma_z_input;
    double end_program; // hit any key to end the program (for users without their IDE set up to keep window up after running)

    
double find_stability_class(int wind)
{
    while (d_or_n != "n" && d_or_n != "d")
    {
        cout << "Is this observation at [d]aytime or [n]ighttime]?" << endl;
        cin >> d_or_n; 
    }
    if (d_or_n == "d")
    {
        while (in_solar_rad != "s" && in_solar_rad != "m" && in_solar_rad != "sl")
        {
            cout <<  "What is the Daytime incoming solar radiation? [s]trong (>700 W/m2), [m]oderate (350-700 W/m2), or [sl]ight (<350 W/m2)" << endl;
            cin >> in_solar_rad;
        }
        if (in_solar_rad == "s")  
        {
            num_pasquill_stability_class = stability_classes_daytime_strong[wind];
        }  
        else if (in_solar_rad == "m")
        {
            num_pasquill_stability_class = stability_classes_daytime_moderate[wind];
        }
        else if (in_solar_rad == "sl")
        {
            num_pasquill_stability_class = stability_classes_daytime_slight[wind];
        }
    }
    else if (d_or_n == "n")
    {
        while (night_cloud_cover != "l" && night_cloud_cover != "m")
        {
            cout <<  "What is the nighttime cloud cover? [l]ess than 50% or [m]ore than 50%" << endl;
            cin >> night_cloud_cover;
        }
        if (night_cloud_cover == "l")  
        {
            num_pasquill_stability_class = stability_classes_nightime_less_clouds[wind];
        }  
        else if (night_cloud_cover == "m")
        {
            num_pasquill_stability_class = stability_classes_nightime_more_clouds[wind];
        }
    }
    return num_pasquill_stability_class;
}

double calc_conc_w_reflection(double x_m, double y_m, double z_m, double emissions_strength, double height_effective_stack, double plume_wind_speed, double sigma_y, double sigma_z)
{
    double first_term = emissions_strength / (2 * pi * plume_wind_speed * sigma_y * sigma_z);
    double second_term = exp((-1 * (pow(y_m, 2))) / (2 * pow(sigma_y, 2)));
    double third_term = exp((-1 * (pow((z_m - height_effective_stack), 2))) / (2 * pow(sigma_z, 2))) + exp((-1 * (pow((z_m + height_effective_stack), 2))) / (2 * pow(sigma_z, 2)));
    conc = first_term * second_term * third_term; 
    //check
    //cout << "first is " << first_term << endl;
    //cout << "q is " << emissions_strength << " pi is " << pi << " plume_wind_speed is " << plume_wind_speed << " sigma y is " << sigma_y << " sigma z is " << sigma_z << endl;
    //cout << "second is " << second_term << endl;
    //cout << "y_m is " << y_m << ". pow1 is " << pow(y_m, 2) << ". pow2 is " << pow(sigma_y, 2) << endl;
    //cout << "third is " << third_term << endl;
    //cout << "H is " << height_effective_stack << endl;
    return conc;

} 

double get_sigma_y_vars(int class_num)
{
    switch(class_num)
    { // all constants come from Table 1-1: PARAMETERS USED TO CALCULATE PASQUILL GIFFORD FY from the EPAB (source 1)
        case 0: // A
            var_c = 24.1670;
            var_d = 2.5334;
            break;
        case 1: // B
            var_c = 18.3330;
            var_d = 1.8096;
            break;
        case 2: // C
            var_c = 12.5000;
            var_d = 1.0857;
            break;
        case 3: // D
            var_c = 8.3330;
            var_d = 0.72382;
            break;
        case 4: // E
            var_c = 6.2500;
            var_d = 0.54287;
            break;
        case 5: // F
            var_c = 4.1667;
            var_d = 0.36191;
            break;
        default:
            cout << "Unknown Error with Pasquill Stability Class Calculations" << endl;
    }
    return 0;
}

double calc_sigma_y(double var_c, double var_d, double x_dist)
{
    theta = 0.017453292 * (var_c - (var_d * (log(x_dist))));
    sigma_y = 465.11628 * x_dist * tan(theta);
    return sigma_y;
}

double get_sigma_z_vars(double x_dist, int class_num) //test
{
    switch(class_num)
    {
        case 0: // A
            // check cout << "x_dist" << x_dist << endl;
            for(int i = 0; i <= 9; i++)  // run through the rows, first column
            { 
                x_dist_limit = sigma_z_class_a_parameters[i][0];
                // check cout << "x limit =" << x_dist_limit << endl;
                while(x_dist <= x_dist_limit)
                {
                    row_num = i; 
                    var_a = sigma_z_class_a_parameters[row_num][1];
                    //cout << "var a check = " << var_a << endl;
                    var_b = sigma_z_class_a_parameters[row_num][2];
                    //cout << "var b check = " << var_b << endl; 
                    return 0;

                }
            }
            break;
        case 1: // B
            for(int i = 0; i <= 3; i++)  // run through the rows, first column
                { 
                    x_dist_limit = sigma_z_class_b_parameters[i][0];
                    while(x_dist <= x_dist_limit)
                    {
                        row_num = i; 
                        var_a = sigma_z_class_b_parameters[row_num][1];
                        var_b = sigma_z_class_b_parameters[row_num][2];
                        return 0;
                    }
                }
        case 2: // C
            var_a = 61.141;
            var_b = 0.91465;
        case 3: // D
            for(int i = 0; i <= 6; i++)  // run through the rows, first column
                { 
                    x_dist_limit = sigma_z_class_d_parameters[i][0];
                    while(x_dist <= x_dist_limit)
                    {
                        row_num = i; 
                        var_a = sigma_z_class_d_parameters[row_num][1];
                        var_b = sigma_z_class_d_parameters[row_num][2];
                        return 0;
                    }
                }
        case 4: // E
            for(int i = 0; i <= 9; i++)  // run through the rows, first column
                { 
                    x_dist_limit = sigma_z_class_e_parameters[i][0];
                    while(x_dist <= x_dist_limit)
                    {
                        row_num = i; 
                        var_a = sigma_z_class_e_parameters[row_num][1];
                        var_b = sigma_z_class_e_parameters[row_num][2];
                        return 0;
                    }
                }
        case 5: // F
            for(int i = 0; i <= 10; i++)  // run through the rows, first column
                { 
                    x_dist_limit = sigma_z_class_f_parameters[i][0];
                    while(x_dist <= x_dist_limit)
                    {
                        row_num = i; 
                        var_a = sigma_z_class_f_parameters[row_num][1];
                        var_b = sigma_z_class_f_parameters[row_num][2];
                        return 0;
                    }
                }
        default:
            cout << "Unknown Error with Pasquill Stability Class Calculations" << endl;
            return 0;
    }
 return class_num;// cout << "var a is " << var_a << " var b is " << var_b <<" sigma z is " << sigma_z << endl;
}

double calc_sigma_z(double var_a, double var_b, double x_dist)
{
    sigma_z = var_a * pow(x_dist, var_b);
    return sigma_z;
}

string check_num(string name) // Checks if a user input is a number or numericallly related
{
    for (int i = 0; i < name.size(); i++)
    {
        if ((int)(name[i]) < 40 || (int)(name[i]) > 57 ) //only true when ASCII Code is numeric or numerically related i.e. ()*,-+/0123456789
            {
                cout << "Please enter a positive number." << endl;
                check_num_output = "false";
                return check_num_output;
            }
    //cout << name[i]; check
    check_num_output = "true";
    }
    return check_num_output; 
}

int main() 
{
    cout << "This program will calculate the concentration of an airborne pollutant for a location downwind from a point source at elevation (i.e. a plume leaving a smoke stack)" << endl;
//MORE INFORMATION LOOP
    while (more_info != "y" && more_info != "n") // while loop is used to make sure the user inputs responsive outcome (i.e. "y" or "n")
    {
        cout << "Would you like to know more about this program? [y]es or [n]o" << endl;
        cin >> more_info;
    }
    if (more_info == "y")
    {
        while (input_info != "a" && input_info != "s" && input_info != "v")
        {    
            cout << "Do you want to know more about the [s]ources of equations & functions, or [v]ariables needed to run this model?" << endl;
            cin >> input_info;
        }
        if (input_info == "s") //sources
        {
            cout << "(1) The User's Guide for the Industrial Souce Complex (ISC3) Dispersion Models, Volume II - Description of Model Algorithsm, September 1995" << endl; //https://www3.epa.gov/scram001/userg/regmod/isc3v2.pdf
            cout << "- calculate concentration with reflection function" << endl;
            cout << "- get variables for / calculate sigma y/z functions" << endl;
            cout << "(2) NOAA's Air Resources Laboratory: READY Tools: Pasquill Stability Classes" << endl; //https://www.ready.noaa.gov/READYpgclass.php
            cout << "- find stability class function" << endl;
            cout << endl;
        }
        if (input_info == "v") //variables required
        {
            cout << "C     = concentration of air pollutant at point of interest [GRAMS/METERS^3]" << endl;
            cout << "Q     = emissions strength at source [GRAMS/SECOND]" << endl;
            cout << "x     = distance in the x direction of the wind between the point of interest and the source [METERS]" << endl;
            cout << "y     = distance in the y direction perpendicular to the wind between the point of interest and the source [METERS]" << endl;
            cout << "z     = distance in the z vertical direction between the ground and the point of interest [METERS]" << endl;
            cout << "H     = effective stack height [METERS]" << endl; 
            cout << "        + There is an option to calculate H with stack height & plume rise [METERS]" << endl;
            cout << "u1    = wind speed through the plume / at stack height [METERS/SECOND]" << endl;
            cout << "σy/σz = dispersion parameter [METERS]" << endl;
            cout << "        + If known, σy/σz can be entered." << endl;
            cout << "        + If unknown, they will be calculated using:" << endl;
            cout << "        x = distance in the x direction between the point of interest and the source [METERS]" << endl;
            cout << "        s = Pasquill Gifford Stability Class [A, B, C, D, E, or F]" << endl;
            cout << "            + If the stability class is unknown, it will be calculated using:" << endl;
            cout << "            u2 = wind speed at ground level [METERS/SECOND]" << endl;
            cout << "            + & time of day (nighttime or daytime), and solar radiation or cloud cover, respectively." << endl;
            cout << endl;
        }
    }
    if (more_info == "n") //continue
    {} 

//EMISSION STRENGTH CALCULATIONS
    while (emissions_strength == false) //User inputs only numerical operators
    {
        cout << "Enter the emissions strength at the source in GRAMS/SECOND" << endl ;
        cin >> emissions_strength_input;
        check_num(emissions_strength_input);
        if (check_num_output == "false")
        {
            emissions_strength == false;
        }
        if (check_num_output == "true")
        {
            emissions_strength = stod(emissions_strength_input);
            break;
        }
    }

//LOCATION (X, Y, Z) INPUT LOOP
    for (int j = 0; j < 3; j++) 
    {
        while(between[j] == false) //User inputs only numerical operators
        {
            cout << "Enter the distance between your point of interest and the ground location of the source in the " << direction[j]; 
            cout << " direction [METERS]" << endl;
            cin >> between_input[j];
        
            check_num(between_input[j]);
            if (check_num_output == "false")
            {
                between[j] == false;
            }
            if (check_num_output == "true")
            {
                between[j] = stod(between_input[j]);
                break;
            }
        }
    }

// EFFECTIVE STACK HEIGHT INPUT / CALCULATIONS
    while (stack_height_calc_option != "e" && stack_height_calc_option != "s")
    {
        cout << "Would you like to enter in the [e]ffective stack height or the [s]tack height & plume rise?" << endl;
        cin >> stack_height_calc_option;
    }
    if (stack_height_calc_option == "e")
    {
        while (height_effective_stack == false) //User inputs only numerical operators
        {
            cout << "Enter the effective stack height in METERS." << endl;
            cin >> height_effective_stack_input;
            check_num(height_effective_stack_input);
            if (check_num_output == "false")
            {
                height_effective_stack == false;
            }
            if (check_num_output == "true")
            {
                height_effective_stack = stod(height_effective_stack_input);
                break;
            }
        }
    }
    if (stack_height_calc_option == "s")
    {
        while (height_stack == false) //User inputs only numerical operators
        {
            cout << "Enter the stack height in METERS" << endl;
            cin >> height_stack_input;
            check_num(height_stack_input);
            if (check_num_output == "false")
            {
                height_stack == false;
            }
            if (check_num_output == "true")
            {
                height_stack = stod(height_stack_input);
                break;
            }
        }
        while (height_plume_rise == false) //User inputs only numerical operators
        {
            cout << "Enter the vertical plume rise above the stack in METERS" << endl;
            cin >> height_plume_rise_input;
            check_num(height_plume_rise_input);
            if (check_num_output == "false")
            {
                height_plume_rise == false;
            }
            if (check_num_output == "true")
            {
                height_plume_rise = stod(height_plume_rise_input);
                break;
            }
        }
        height_effective_stack = height_stack + height_plume_rise; 
        cout << "The effective stack height for your source is " << height_effective_stack << " meters." << endl;
    } 

//WIND SPEED INPUT
    while (plume_wind_speed == false) //User inputs only numerical operators
    {
        cout << "Enter the wind speed through the plume in METERS/SECOND." << endl;
        cin >> plume_wind_speed_input;
        check_num(plume_wind_speed_input);
        if (check_num_output == "false")
        {
            plume_wind_speed == false;
        }
        if (check_num_output == "true")
        {
            plume_wind_speed = stod(plume_wind_speed_input);
            break;
        }
    }
//STABILITY CLASS VARIABLES AND CALCULATIONS
    x_m = between[0];
    y_m = between[1];
    z_m = between[2];
    x_km = x_m/1000; // convert to kilometers

    /*get_sigma_z_vars(x_km, num_pasquill_stability_class);
    sigma_z = calc_sigma_z(var_a, var_b, x_km);

    get_sigma_y_vars(num_pasquill_stability_class);
    sigma_y = calc_sigma_y(var_c, var_d, x_km);*/


// DISPERSION COEFFICIENT INPUTS / STABILITY CLASS CALCULATIONS
    while (input_sigmas != "n" && input_sigmas != "y") //Does the user know dispersion coefficients? if no --> proceed to next while loop - stability class
    {
        cout << "Do you know the dispersion coefficients sigma y and sigma z? [y]es or [n]o?" << endl; 
        cin >> input_sigmas;
    }
    if (input_sigmas == "n") // User does not have dispersion coefficient --> proceed to calculate with stability class
    {
        while (calc_stability_class != "n" && calc_stability_class != "y") //Does the user know the Pasquil Gifford Stability class? if no --> proceed to next while loop - surface wind speed
        {
        cout << "Do you know the Pasquill Gifford Stability class? [y]es or [n]o?" << endl; 
        cin >> calc_stability_class;
        }
        if (calc_stability_class == "y") //no dispersion coef., yes stability class
        { 
            while (input_stability_class != "A" && input_stability_class != "B" && input_stability_class != "C" && input_stability_class != "D" && input_stability_class != "E" && input_stability_class != "F")
            {
                cout << "Enter the Pasquill Giffod Stability class. [A], [B], [C], [D], [E], or [F]" << endl;
                cin >> input_stability_class;
            }
            if (input_stability_class == "A")
            {
                cout << "A" << endl;
                num_pasquill_stability_class = 0;
            }  
            if (input_stability_class == "B")
            {
                cout << "B" << endl;
                num_pasquill_stability_class = 1;
            }  
            if (input_stability_class == "C")
            {
                cout << "C" << endl;
                num_pasquill_stability_class = 2;
            }
            if (input_stability_class == "D")
            {
                cout << "D" << endl;
                num_pasquill_stability_class = 3;
            }
            if (input_stability_class == "E")
            {
                cout << "E" << endl;
                num_pasquill_stability_class = 4;
            }
            if (input_stability_class == "F")
            {
                cout << "F" << endl;
                num_pasquill_stability_class = 5;
            }   
        }
        else if (calc_stability_class == "n") //no dispersion coef,. no stability class --> stability class will be calculated from more user information
        { 
            while (surface_wind_speed == false)
            {
                cout << "Enter the surface wind speed in METERS/SECOND." << endl;
                cin >> surface_wind_speed_input;
                check_num(surface_wind_speed_input);
                if (check_num_output == "false")
                {
                    surface_wind_speed == false;
                }
                if (check_num_output == "true")
                {
                    surface_wind_speed = stod(surface_wind_speed_input);
                    break;
                }
            }
            if (surface_wind_speed < 2)
            {
                wind_array_index = 0;
            }
            else if (surface_wind_speed >= 2 && surface_wind_speed < 3 )
            {
                wind_array_index = 1;
            }
            else if (surface_wind_speed >= 3 && surface_wind_speed < 5 )
            {
                wind_array_index = 2;
            }
            else if (surface_wind_speed >= 5 && surface_wind_speed < 6 )
            {
                wind_array_index = 3;
            }
            else if (surface_wind_speed >= 6 )
            {
                wind_array_index = 4;
            }

            num_pasquill_stability_class = find_stability_class(wind_array_index);  
        } 
        get_sigma_z_vars(x_km, num_pasquill_stability_class);
        sigma_z = calc_sigma_z(var_a, var_b, x_km);

        get_sigma_y_vars(num_pasquill_stability_class);
        sigma_y = calc_sigma_y(var_c, var_d, x_km);

        cout << "The Pasquill Stability Class is " << Numeric_to_Alphabet[num_pasquill_stability_class] << ". This classification is used to approximate the dispersion coefficients of the plume. " << endl;
    } 
    if (input_sigmas == "y") //User input dispersion coefficients, stability class/surface wind not needed
    {
        while (sigma_y == false) //User inputs only numerical operators
        {
            cout << "Enter in sigma y (the direction " << direction[1] << ") in METERS." << endl;
            cin >> sigma_y_input;
            check_num(sigma_y_input);
            if (check_num_output == "false")
            {
                sigma_y == false;
            }
            if (check_num_output == "true")
            {
                sigma_y = stod(sigma_y_input);
                break;
            }
        }
        while (sigma_z == false) //User inputs only numerical operators
        {
            cout << "Enter in sigma z (the direction " << direction[2] << ") in METERS." << endl;
            cin >> sigma_z_input;
            check_num(sigma_z_input);
            if (check_num_output == "false")
            {
                sigma_z == false;
            }
            if (check_num_output == "true")
            {
                sigma_z = stod(sigma_z_input);
                break;
            }
        }
    }
//check
    cout << "sigma_y = " << sigma_y << " var c is " << var_c << " var_d is " << var_d << endl;
    // cout << "theta is = " << theta << endl;
    cout << "sigma_z = " << sigma_z << " var a is " << var_a << " var_b is " << var_b << endl;
    conc = calc_conc_w_reflection(x_m, y_m, z_m, emissions_strength, height_effective_stack, plume_wind_speed, sigma_y, sigma_z);
    conc_ug = conc*1000000;
    cout << "The concentration at " << x_m << "m, " << y_m << "m, " << z_m << "m from the source is " << conc << " grams/meters^3 or ";
    cout << conc_ug << " micrograms/meters^3. " << endl;
    cin >> end_program;

}
