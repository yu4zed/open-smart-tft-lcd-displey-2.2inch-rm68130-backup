CMO 2.0б▒ Initial Code
void RMM68130_CMO_20_Initial(void)
{
// VCI=2.8V, IOVCC=2.8V --- Gamma 2.4
//************* Start Initial Sequence **********//
RM68130_CMD_DATA(0x0028, 0x00CE); // Software Reset
RM68130_CMD_DATA(0x0001, 0x011C); // driver output control
RM68130_CMD_DATA(0x0003, 0x1030); // Entry mode
				// n=1,2,3 бн 262K бн80-system 16-bit
				// n=0 бн 65K бн80-system 16-bit
				// n=1,2 бн 262K бн80-system 8-bit
				// n=0,3 бн 65K бн80-system 8-bit
RM68130_CMD_DATA(0x0007, 0x0017); // Display control
RM68130_CMD_DATA(0x0011, 0x1000); // Power control
RM68130_CMD_DATA(0x0020, 0x0000); // RAM address set(Horizontal Address)
RM68130_CMD_DATA(0x0021, 0x0000); // RAM address set(Vertical Address)
RM68130_CMD_DATA(0x0036, 0x00AF); // Windows address position
RM68130_CMD_DATA(0x0037, 0x0000); // Windows address position
RM68130_CMD_DATA(0x0038, 0x00DB); // Windows address position
RM68130_CMD_DATA(0x0039, 0x0000); // Windows address position
RM68130_CMD_DATA(0x0002, 0x0000); // LCD driving wave control 0 : Column Inversion
RM68130_CMD_DATA(0x00B0, 0x1412); // Power control(0c12)
RM68130_CMD_DATA(0x000B, 0x0000); // Frame Rate Control 4-bit
//************* Start Gamma Setting **********//
RM68130_CMD_DATA(0x00E8, 0x0100); // Gamma Command 1 : Gamma Enable
RM68130_CMD_DATA(0x00B1, 0x0F0F); // +- Gamma Voltage Setting
RM68130_CMD_DATA(0x0050, 0x0003); // Below : Gamma Setting
RM68130_CMD_DATA(0x0051, 0x0807);
RM68130_CMD_DATA(0x0052, 0x0C08);
RM68130_CMD_DATA(0x0053, 0x0503);
RM68130_CMD_DATA(0x0054, 0x0003);
RM68130_CMD_DATA(0x0055, 0x0807);
RM68130_CMD_DATA(0x0056, 0x0003);
RM68130_CMD_DATA(0x0057, 0x0503);
RM68130_CMD_DATA(0x0058, 0x0000);
RM68130_CMD_DATA(0x0059, 0x0000);
RM68130_CMD_DATA(0x00E8, 0x0102);
RM68130_CMD_DATA(0x00FB, 0x002A);
RM68130_CMD_DATA(0x00E8, 0x0101);
RM68130_CMD_DATA(0x00F1, 0x0040);
}

void RM68130_Enter_Sleep(void)
{
RM68130_CMD_DATA(0x0010, 0x0002); // Enter Sleep
}
void RM68130_Sleep_Out(void)
{
RM68130_CMD_DATA(0x0010, 0x0000); // Exit Sleep
}
void LCD_BlockWrite_1N2011(kal_uint16 startx,kal_uint16 starty,kal_uint16 endx,kal_uint16 endy)
{
	kal_uint16 roi_width;
	kal_uint16 x,y;
	while (LCD_IS_RUNNING){};
	
	//   ASSERT(lcd_assert_fail==KAL_FALSE);
	lcd_assert_fail = KAL_TRUE;
	
	
	SET_LCD_CMD_PARAMETER(0,LCD_CMD,((0x37& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(1,LCD_CMD,(0x37 & 0xFF));
	SET_LCD_CMD_PARAMETER(2,LCD_DATA,((startx&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(3,LCD_DATA,(startx & 0xFF));

	SET_LCD_CMD_PARAMETER(4,LCD_CMD,((0x36& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(5,LCD_CMD,(0x36 & 0xFF));
	SET_LCD_CMD_PARAMETER(6,LCD_DATA,((endx&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(7,LCD_DATA,(endx & 0xFF));

	SET_LCD_CMD_PARAMETER(8,LCD_CMD,((0x39& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(9,LCD_CMD,(0x39 & 0xFF));
	SET_LCD_CMD_PARAMETER(10,LCD_DATA,((starty&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(11,LCD_DATA,(starty & 0xFF));

	SET_LCD_CMD_PARAMETER(12,LCD_CMD,((0x38& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(13,LCD_CMD,(0x38 & 0xFF));
	SET_LCD_CMD_PARAMETER(14,LCD_DATA,((endy&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(15,LCD_DATA,(endy & 0xFF));

	SET_LCD_CMD_PARAMETER(16,LCD_CMD,((0x20& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(17,LCD_CMD,(0x20 & 0xFF));
	SET_LCD_CMD_PARAMETER(18,LCD_DATA,((startx&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(19,LCD_DATA,(startx & 0xFF));

	SET_LCD_CMD_PARAMETER(20,LCD_CMD,((0x21& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(21,LCD_CMD,(0x21 & 0xFF));
	SET_LCD_CMD_PARAMETER(22,LCD_DATA,((starty&0xff00)>>8));
	SET_LCD_CMD_PARAMETER(23,LCD_DATA,(starty & 0xFF));

	SET_LCD_CMD_PARAMETER(24,LCD_CMD,((0x22& 0xFF00)>>8));
	SET_LCD_CMD_PARAMETER(25,LCD_CMD,(0x22 & 0xFF));
	
	SET_LCD_ROI_CTRL_NUMBER_OF_CMD(26);		
	
	ENABLE_LCD_TRANSFER_COMPLETE_INT;
	ENABLE_LCD_ROI_CTRL_CMD_FIRST;
	START_LCD_TRANSFER;

	
	lcd_assert_fail = KAL_FALSE;
}                     