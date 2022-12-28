#ifndef TC72_TEMPR_H_
#define TC72_TEMPR_H_

#define CONTROL_REG   0x80
#define START_CONV    0x10
#define TEMPR_REG     0x02
#define FRAC_FLAG     0x00C0


void TC72_Init(void);
int TC72_ReadTempr(void);
float GetData(signed int tempr);
signed int Continous_reading(void);
#endif /* TC72_TEMPR_H_ */
