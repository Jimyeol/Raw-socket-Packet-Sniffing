
#pragma once

#include "PacketListCtrl.h"

#define TITLE TEXT("Raw Packet Capture")

#define PACKET_SIZE 6096

extern CPacketListCtrl g_ctrlLstPacket;
extern u_char *g_pPacket[PACKET_SIZE];
extern INT g_nPacketLen[PACKET_SIZE];
extern INT g_nPacket;

