#include "xmc_can.h"
#include "xmc_gpio.h"

// Enable CAN kernel
XMC_CAN_Init(CAN, XMC_CAN_CANCLKSRC_FPERIPH, 1);  // "1" = CAN is divided from fPERIPH

XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t can_bit_time = {
  .baudrate = 500000,     // 500 kbit/s
  .sample_point = 8000,   // 80%
  .sjw = 1                // Re-synchronization jump width
};

XMC_CAN_NODE_Init(CAN_NODE0, &can_bit_time);

XMC_GPIO_CONFIG_t can_tx_pin = {
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2
};
XMC_GPIO_CONFIG_t can_rx_pin = {
  .mode = XMC_GPIO_MODE_INPUT_TRISTATE
};

XMC_GPIO_Init(P1_12, &can_tx_pin);
XMC_GPIO_Init(P1_13, &can_rx_pin);

XMC_CAN_MO_t tx_mo, rx_mo;

void can_setup_message_objects(void)
{
  // TX message object
  tx_mo.can_mo_ptr = CAN_MO0;   // MO0 = transmit buffer
  XMC_CAN_MO_Config(&tx_mo);
  XMC_CAN_MO_SetIdentifier(&tx_mo, 0x100, XMC_CAN_FRAME_TYPE_STANDARD);
  XMC_CAN_MO_SetDataLengthCode(&tx_mo, 8);
  XMC_CAN_AllocateMOToNodeList(CAN_NODE0, 0, &tx_mo);

  // RX message object
  rx_mo.can_mo_ptr = CAN_MO1;   // MO1 = receive buffer
  XMC_CAN_MO_Config(&rx_mo);
  XMC_CAN_MO_SetIdentifier(&rx_mo, 0x200, XMC_CAN_FRAME_TYPE_STANDARD);
  XMC_CAN_MO_SetDataLengthCode(&rx_mo, 8);
  XMC_CAN_AllocateMOToNodeList(CAN_NODE0, 1, &rx_mo);
}

XMC_CAN_NODE_Enable(CAN_NODE0);

void can_send(void)
{
  uint8_t data[8] = {1,2,3,4,5,6,7,8};

  XMC_CAN_MO_UpdateData(&tx_mo, data);
  XMC_CAN_MO_Transmit(&tx_mo);
}

void can_receive(void)
{
  if (XMC_CAN_MO_GetStatus(&rx_mo) & XMC_CAN_MO_STATUS_RX_PENDING)
  {
    uint8_t rx_data[8];
    XMC_CAN_MO_Receive(&rx_mo, rx_data);
    // process rx_data
  }
}

int main(void)
{
  SystemCoreClockUpdate();

  // Init CAN + pins
  XMC_CAN_Init(CAN, XMC_CAN_CANCLKSRC_FPERIPH, 1);
  XMC_CAN_NODE_NOMINAL_BIT_TIME_CONFIG_t bit_time = {500000, 8000, 1};
  XMC_CAN_NODE_Init(CAN_NODE0, &bit_time);

  XMC_GPIO_Init(P1_12, &(XMC_GPIO_CONFIG_t){.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT2});
  XMC_GPIO_Init(P1_13, &(XMC_GPIO_CONFIG_t){.mode = XMC_GPIO_MODE_INPUT_TRISTATE});

  can_setup_message_objects();
  XMC_CAN_NODE_Enable(CAN_NODE0);

  while (1)
  {
    can_send();
    can_receive();
  }
}
