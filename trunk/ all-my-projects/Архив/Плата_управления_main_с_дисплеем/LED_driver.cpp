void led_1_on(void);
void led_1_off(void);



void led_1_on(void)
{
  DDRG|=(1<<PG2);
  PORTG&=~(1<<PG2);
}


void led_1_off(void)
{
  PORTG|=(1<<PG2);
  DDRG&=~(1<<PG2);
}

void led_2_on(void)
{
  DDRG|=(1<<PG4);
  PORTG&=~(1<<PG4);
}


void led_2_off(void)
{
  PORTG|=(1<<PG4);
  DDRG&=~(1<<PG4);
}

void led_3_on(void)
{
  DDRG|=(1<<PG3);
  PORTG&=~(1<<PG3);
}


void led_3_off(void)
{
  PORTG|=(1<<PG3);
  DDRG&=~(1<<PG3);
}