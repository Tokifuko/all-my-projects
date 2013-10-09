/*
 * MeasureCurrentClass.h
 *
 *  Created on: 30 сент. 2013 г.
 *      Author: Stefan
 */

#ifndef MEASURECURRENTCLASS_H_
#define MEASURECURRENTCLASS_H_


#define MEASURE_CUR_STOP	0
#define MEASURE_CUR_UP		1
#define MEASURE_CUR_DOWN	2
#define SWITCH_DELAY		1

void MesureCurInit(void);
void MesureCurStop(void);
void MesureCurUpward(void);
void MesureCurDownward(void);
void MesureCurToggle(void);



#endif /* MEASURECURRENTCLASS_H_ */
