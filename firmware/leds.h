/* 
 * num:
 * * 0..9 -- set number 0..9 dot is off
 * * -9..-0 -- set number 0..9 dot is off
 * * other -- reserverd (meaybe '-' example or else)
 *
 */
int leds_put(unsigned char num, unsigned char dot);
int leds_strobe();
