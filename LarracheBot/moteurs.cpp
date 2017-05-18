#include <avr/io.h>
#include "moteurs.h"

void MOTEURS_Init(void)
{
  // Disable MOTEURS EO et E1
  PMOTE0 |= (1 << E0EN);
  PMOTE1 |= (1 << E1EN);

  // STEP MOTEURS E0 et E1
  PMOTE0 &= ~(1 << E0STEP);
  PMOTE1 &= ~(1 << E1STEP);
  
  // DIR MOTEURS E0 et E1
  PMOTE0 |= (1 << E0DIR);
  PMOTE1 &= ~(1 << E1DIR);
}


