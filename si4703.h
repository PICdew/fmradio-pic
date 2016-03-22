/* 
 * File:   si4703.h
 * Author: dinusha
 *
 * Created on December 12, 2015, 6:55 PM
 */

#ifndef SI4703_H
#define	SI4703_H

#include <stdint.h>

//#ifdef	__cplusplus
//extern "C" {
//#endif

void si4703_setup_2wire();
void si4703_init();
void si4703_read_regs(uint16_t *r);
//void si4703_print_regs(uint16_t *r);
void si4703_write_regs(uint16_t *r);
void si4703_tune(uint16_t freq);
void si4703_set_volume(uint8_t val);
uint16_t si4703_getrssi();
uint16_t si4703_getchannel();
void si4703_get_rds(uint8_t *buff);
void si4703_mute();
void si4703_powerdown();
void si4703_volume_up();
void si4703_volume_down();
void si4703_seek(uint8_t seekdown);



//#ifdef	__cplusplus
//}
//#endif

#endif	/* SI4703_H */

