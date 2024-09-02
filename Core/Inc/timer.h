#ifndef INC_TIMER_H_
#define INC_TIMER_H_

typedef struct
{
	uint32_t millis;
	uint32_t ticks;
	void (*callback)(void);
} TIMER_HandleTypeDef;

void TIMER_Init(TIMER_HandleTypeDef* timer, void (*callback)(void), uint32_t millis)
{
	timer->millis = millis;
	timer->ticks = 0;
	timer->callback = callback;
}

void TIMER_Update(TIMER_HandleTypeDef* timer)
{
	uint32_t nowTicks = HAL_GetTick();

	if (nowTicks - timer->ticks > timer->millis)
	{
		timer->ticks = nowTicks;

		timer->callback();
	}
}

void TIMER_SetMillis(TIMER_HandleTypeDef* timer, uint32_t millis)
{
	timer->millis = millis;
}

#endif
