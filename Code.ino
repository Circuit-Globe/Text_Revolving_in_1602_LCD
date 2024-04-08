#define       command_en_high             1       // rs = 0, en = 1
#define       command_en_low              0       // rs = 0, en = 0
#define       data_en_high                3       // rs = 1, en = 1
#define       data_en_low                 2       // rs = 1, en = 0
#define       clear_display               0x01
#define       display_on_cursor_off       0x0C
#define       two_line_n_5_7_matrix       0x38
#define       row1_1st_position           0x80
#define       row1_last_position          0x9b
#define       row2_last_position          0xda
#define       left_shift_cursor           0x04



volatile char *dirf, *outf, *dirk, *outk;


void lcd_data(volatile char *ptr){
while(*ptr){
    *outf = *ptr;
    *outk = data_en_low;      delay1(1); 
    *outk = data_en_high;     delay1(1);
    *outk = data_en_low;      delay1(1);
    ptr++;
  }
}


void init_lcd(){
  lcd_cmd(two_line_n_5_7_matrix);
  lcd_cmd(display_on_cursor_off);
  lcd_cmd(clear_display);
}


void lcd_cmd(volatile char cmd){
  *outf = cmd;   
  *outk = command_en_low;    delay1(1); 
  *outk = command_en_high;   delay1(1);    
  *outk = command_en_low;    delay1(1);
}


void init_port(){
  dirf=0x30;     *dirf=0xff;    outf=0x31;   // PORTF sets as output
  dirk=0x107;    *dirk=0x03;    outk=0x108;  // PORTK sets as output
}


void delay1(volatile int time){
  while(time--)
  for(volatile long i=0; i<100; i++);
}



int main(){
  volatile short row1_pos, row2_pos;
  init_port();
  init_lcd();

while(1){
  
  for(row1_pos = row1_1st_position, row2_pos = row2_last_position; row1_pos <= row1_last_position; row1_pos++, row2_pos--){
    lcd_cmd(clear_display);
    lcd_cmd(left_shift_cursor);  // for left shift the cursor;
    lcd_cmd(row1_pos);
    lcd_data("oT emocleW");

    lcd_cmd(row2_pos);
    lcd_data("ymedacA NECE");
    delay1 (1000);
  }
 }
}

