# Air_Pollution

This program helps users calculate the downwind air concentration (g/m3) from an elevated point source.

**Required Variables**

Q     = emissions strength at source [GRAMS/SECOND]

x     = distance in the x direction of the wind between the point of interest and the source [METERS]

y     = distance in the y direction perpendicular to the wind between the point of interest and the source [METERS]

z     = distance in the z vertical direction between the ground and the point of interest [METERS]

u1    = wind speed through the plume / at stack height [METERS/SECOND]

H     = effective stack height [METERS] 

        OR There is an option to calculate H with stack height & plume rise [METERS]
        
σy/σz = dispersion parameter [METERS]

        If known, σy/σz can be entered.
        
        OR If unknown, they will be calculated using:
        
        x = distance in the x direction between the point of interest and the source [METERS]
        
        s = Pasquill Gifford Stability Class [A, B, C, D, E, or F]
        
            OR If the stability class is unknown, it will be calculated using:
            
            u2 = wind speed at ground level [METERS/SECOND]
            
            + & time of day (nighttime or daytime), and solar radiation or cloud cover, respectively
            
**Sources of equations and constants and purpose**

 (1) The User's Guide for the Industrial Souce Complex (ISC3) Dispersion Models, Volume II - Description of Model Algorithsm, September 1995
 
https://www3.epa.gov/scram001/userg/regmod/isc3v2.pdf
     
- used to calculate concentration with reflection function
     
- used to get variables for / calculate sigma y/z functions
     
 (2) NOAA's Air Resources Laboratory: READY Tools: Pasquill Stability Classes
 
 https://www.ready.noaa.gov/READYpgclass.php
     
- used to find stability class function
    


