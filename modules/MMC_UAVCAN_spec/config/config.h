/*
 * config.h
 *
 *  Created on: Sep 28, 2018
 *      Author: jay
 */

#ifndef MMC_UAVCAN_CONFIG_CONFIG_H_
#define MMC_UAVCAN_CONFIG_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define MMC_CAN1_IFACE_MASK		(1)
#define MMC_CAN2_IFACE_MASK		(1<<1)

#define MMC_CANBUS_BITRATE		(1000000)

#define MMC_NODEID_FC			(6)
#define MMC_NODEID_FW_SERVER	(6)
#define MMC_NODEID_IMU			(11)
#define MMC_NODEID_GNSS			(15)
#define MMC_NODEID_RTK			(19)
#define MMC_NODEID_TX2			(20)
#define MMC_NODEID_PWR			(51)

#define MMC_FW_PATH_IMU			("")
#define MMC_FW_PATH_GNSS		("")
#define MMC_FW_PATH_RTK			("")
#define MMC_FW_PATH_PWR			("")

// 5 bits priority	= 0 ~ 31
#define MMC_MSG_PRIO_TIMESYNC	(2)
#define MMC_MSG_PRIO_NODESTATUS	(3)

// sensor bridge
#define SENSBR_NODE_ID_BIT_NUM  	(6)
#define SENSBR_NODE_ID_MASK  		((1 << SENSBR_NODE_ID_BIT_NUM) - 1)

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MMC_UAVCAN_CONFIG_CONFIG_H_ */
