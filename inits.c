#include "main.h"

void init_CPU(){
	MDR_RST_CLK->HS_CONTROL=RST_CLK_HSE_ON; //���. HSE
	while((MDR_RST_CLK->CLOCK_STATUS&RST_CLK_CLOCK_STATUS_HSE_RDY )!=RST_CLK_CLOCK_STATUS_HSE_RDY );		//��� HSE
	MDR_RST_CLK->CPU_CLOCK=0x00000102; //�������������� ������ ������������� c2 �� CPU_C1
	MDR_RST_CLK->PLL_CONTROL = ((1 << 2) | (9 << 8));//���. PLL  | ����. ��������� = 9+1
	while ((MDR_RST_CLK->CLOCK_STATUS & RST_CLK_CLOCK_STATUS_PLL_CPU_RDY) != RST_CLK_CLOCK_STATUS_PLL_CPU_RDY);// ��� PLL_CPU
	MDR_RST_CLK->CPU_CLOCK=0x00000106; // ������ ������������� �2 �� PLLCPU
}


void init_TIMER1(){
	/*������ ��� �������� ��������� �������*/
	/*������������ ��������*/
	MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_TIMER1;
	MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM1_CLK_EN;
	
	/*���������*/
	MDR_TIMER1->CH1_CNTRL = 0x00000000;
	MDR_TIMER1->CH2_CNTRL = 0x00000000;
	MDR_TIMER1->CH3_CNTRL = 0x00000000;
	MDR_TIMER1->CH4_CNTRL = 0x00000000;
	MDR_TIMER1->CH1_CNTRL1 = 0x00000000;
	MDR_TIMER1->CH2_CNTRL1 = 0x00000000;
	MDR_TIMER1->CH3_CNTRL1 = 0x00000000;
	MDR_TIMER1->CH4_CNTRL1 = 0x00000000;	
	MDR_TIMER1->CH1_CNTRL2 = 0x00000000;
	MDR_TIMER1->CH2_CNTRL2 = 0x00000000;
	MDR_TIMER1->CH3_CNTRL2 = 0x00000000;
	MDR_TIMER1->CH4_CNTRL2 = 0x00000000;	
	MDR_TIMER1->STATUS = 0x00000000;
	MDR_TIMER1->CNTRL = 0x00000000; // ����� ������������� �������
	MDR_TIMER1->CNT = 0x00000000; // ��������� �������� ��������	

	/*��������� �������*/
	MDR_TIMER1->PSG = 1599; // ������������ �������
	MDR_TIMER1->ARR = 49999; // ��������� ����� (16 ���)
	// ������� 1 ��. ������ ������� ������� �� 50000 ��������
	MDR_TIMER1->CNTRL = TIMER_CNTRL_ARRB_EN | (0 << TIMER_CNTRL_CNT_MODE_Pos); //�����, ����������� ��������
	
	/*���������� ������*/
	MDR_TIMER1->IE = TIMER_IE_CNT_ARR_EVENT_IE;		//���������� �� cnt=arr
	NVIC_EnableIRQ(Timer1_IRQn); //��������� ���������� �������	
	MDR_TIMER1->CNTRL |= TIMER_CNTRL_CNT_EN; //�������� ������.	
}

void init_TIMER2(){
	/*������ ��� ����������*/
	/*������������ ��������*/
	MDR_RST_CLK->PER_CLOCK |= RST_CLK_PCLK_TIMER2;
	MDR_RST_CLK->TIM_CLOCK |= RST_CLK_TIM_CLOCK_TIM2_CLK_EN;
	
	/*���������*/
	MDR_TIMER2->CH1_CNTRL = 0x00000000;
	MDR_TIMER2->CH2_CNTRL = 0x00000000;
	MDR_TIMER2->CH3_CNTRL = 0x00000000;
	MDR_TIMER2->CH4_CNTRL = 0x00000000;
	MDR_TIMER2->CH1_CNTRL1 = 0x00000000;
	MDR_TIMER2->CH2_CNTRL1 = 0x00000000;
	MDR_TIMER2->CH3_CNTRL1 = 0x00000000;
	MDR_TIMER2->CH4_CNTRL1 = 0x00000000;	
	MDR_TIMER2->CH1_CNTRL2 = 0x00000000;
	MDR_TIMER2->CH2_CNTRL2 = 0x00000000;
	MDR_TIMER2->CH3_CNTRL2 = 0x00000000;
	MDR_TIMER2->CH4_CNTRL2 = 0x00000000;	
	MDR_TIMER2->STATUS = 0x00000000;
	MDR_TIMER2->CNTRL = 0x00000000; // ����� ������������� �������
	MDR_TIMER2->CNT = 0x00000000; // ��������� �������� ��������	

	/*��������� �������*/
	MDR_TIMER2->PSG = 79; // ������������ �������
	MDR_TIMER2->ARR = 33332; // ��������� ����� (16 ���)
	// �������������� 30 ��
	MDR_TIMER2->CNTRL = TIMER_CNTRL_ARRB_EN | (0 << TIMER_CNTRL_CNT_MODE_Pos); //�����, ����������� ��������
	
	/*���������� ������*/
	MDR_TIMER2->IE = TIMER_IE_CNT_ARR_EVENT_IE;		//���������� �� cnt=arr
	NVIC_EnableIRQ(Timer2_IRQn); //��������� ���������� �������	
	MDR_TIMER2->CNTRL |= TIMER_CNTRL_CNT_EN; //�������� ������.	
}

void init_SPI(){
	SSP_InitTypeDef SSI_init_struct;
	PORT_InitTypeDef GPIOInitStruct;
	
	// ��������� ������������
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP2, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTD, ENABLE);
	
	//������������� ����� 
	GPIOInitStruct.PORT_PULL_UP   = PORT_PULL_UP_OFF;
	GPIOInitStruct.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
	GPIOInitStruct.PORT_PD_SHM    = PORT_PD_SHM_OFF;
	GPIOInitStruct.PORT_PD        = PORT_PD_DRIVER;
	GPIOInitStruct.PORT_GFEN      = PORT_GFEN_OFF;
	GPIOInitStruct.PORT_SPEED     = PORT_SPEED_MAXFAST;
	GPIOInitStruct.PORT_MODE      = PORT_MODE_DIGITAL;	
	GPIOInitStruct.PORT_FUNC  = PORT_FUNC_ALTER;
  GPIOInitStruct.PORT_Pin   = (SPI2_CLK | SPI2_TXD);
  PORT_Init (SPI2_PORT, &GPIOInitStruct);
	 
	//������������� SSI
	SSP_DeInit(MDR_SSP2);
	SSP_BRGInit(MDR_SSP2,SSP_HCLKdiv2); //40���
	SSP_StructInit (&SSI_init_struct);
	
	SSI_init_struct.SSP_SCR = 2; //������ �������� F_SSPCLK / ( CPSDVR * (1 + SCR) )
	SSI_init_struct.SSP_CPSDVSR = 2; // ������ �������� (������ �����)
	SSI_init_struct.SSP_Mode = SSP_ModeMaster;
	SSI_init_struct.SSP_WordLength = SSP_WordLength8b;
	SSI_init_struct.SSP_FRF = SSP_FRF_SPI_Motorola; //����� ssi ��� spi
	SSI_init_struct.SSP_HardwareFlowControl = SSP_HardwareFlowControl_None;
	SSP_Init(MDR_SSP2, &SSI_init_struct);
	
	SSP_Cmd(MDR_SSP2, ENABLE);
}
	
