//
// Created by ymq on 12/23/21.
//

#ifndef WIRESHARK_KAFKA_AURORA_H
#define WIRESHARK_KAFKA_AURORA_H

#include <librdkafka/rdkafka.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct producer_pa{
	char brokers[512];
	char topic[512];
};

typedef struct kafka_pa{
	char brokers[512];
	char topic[512];
}kafka_params;


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //WIRESHARK_KAFKA_AURORA_H
