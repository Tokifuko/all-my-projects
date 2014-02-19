/* 
 * File:   ms5803-14ba.c
 * Author: Markus Backes
 *
 * Created on 8. August 2012
 * 
 */

#include "ms5803-14ba.h"


void calculateTemperature(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values) {
    long long i,a,b;
    values->dT = MM_DATA.D2 - CB_DATA.C5 * pow(2, 8);
    //values->TEMP = 2000 + ((values->dT * CB_DATA.C6) / pow(2, 23));
    a=  values->dT ;
    b= CB_DATA.C6;
    i= a*b;
   // i= values->dT * CB_DATA.C6;
    i=i >>23;
    values->TEMP = 2000+i;
}

void doSecondOrderTemperatureCompensation(CalculatedValues *values) {
    int32_t T2;
    int64_t OFF2;
    int64_t SENS2;
    if (values->TEMP < 2000) {
        //LOW TEMP
        T2 = 3 * pow(values->dT, 2) / pow(2, 33);
        OFF2 = 3 * pow((values->TEMP - 2000), 2) / pow(2, 1);
        SENS2 = 5 * pow((values->TEMP - 2000), 2) / pow(2, 3);

        if (values->TEMP < -1500) {
            //VERY LOW TEMP
            OFF2 = OFF2 + (7 * pow((values->TEMP + 1500), 2));
            SENS2 = SENS2 + (4 * pow((values->TEMP + 1500), 2));
        }
    } else {
        //HIGH TEMP
        T2 = 7 * pow(values->dT, 2) / pow(2, 37);
        OFF2 = 1 * pow((values->TEMP - 2000), 2) / pow(2, 4);
        SENS2 = 0;
    }

    values->TEMP = values->TEMP - T2;
    values->OFF = values->OFF - OFF2;
    values->SENS = values->SENS - SENS2;
}

void calculateTemperatureCompensatedPressure(CalibrationData CB_DATA, MeasurementData MM_DATA, CalculatedValues *values) {
        long long a,b,c,i,dT,c1,c2,c3,c4,d1,off,sens,p;
        c1=CB_DATA.C1 ;
        c2=CB_DATA.C2 ;
        c3=CB_DATA.C3 ;
        c4=CB_DATA.C4 ;
        d1=MM_DATA.D1;
        dT=values->dT;
        off=(c2 * pow(2, 18)) + ((c4 * dT) / pow(2, 5));
         off=(c2 <<18) + ((c4 * dT) >>5);
         a= c2 <<18;
         b=  c4 * dT;
         c=b>>5;
         off=a+c;
    values->OFF = off;
    a= c1<<17;
    b=c3 * dT;
    c=b>>7;
    sens=a+c;
        //sens= (c1 * pow(2, 17)) + ((c3 * dT) / pow(2, 7));
    values->SENS = sens;
        p=((d1 * sens / pow(2, 21)) - off) / pow(2, 15);
    values->P =p;
}
