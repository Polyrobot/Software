#ifndef MOTEURS_H_
#define MOTEURS_H_


// Definition MOTEUR E0
#define PMOTE0   PORTA
#define E0EN     2
#define E0STEP   4
#define E0DIR    6

// Definition MOTEUR E1
#define PMOTE1   PORTC
#define E1EN     7
#define E1STEP   1
#define E1DIR    2

void MOTEURS_Init(void);

#endif /* MOTEURS_H_ */
