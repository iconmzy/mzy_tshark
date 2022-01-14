//
// Created by ymq on 12/23/21.
//

#ifndef WIRESHARK_KAFKA_AURORA_H
#define WIRESHARK_KAFKA_AURORA_H

#include <librdkafka/rdkafka.h>
#include "ws_symbol_export.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef enum {
    KAFKA_NO_RUN,
    KAFKA_PRODUCER,
    KAFKA_CONSUMER,
    KAFKA_PRODUCER_CONSUMER,
} kafka_status_t;

typedef struct kafka_pa{
    char brokers[512];
    char topic[512];
    char groupid[256];
    int topic_cnt;
    kafka_status_t status;
}kafka_params;


WS_DLL_PUBLIC rd_kafka_t* init_producer(kafka_params *kap);
WS_DLL_PUBLIC int au_kafka_producer(rd_kafka_t* rk, kafka_params *kap, const char *key, const char *value);
WS_DLL_PUBLIC void destroy_producer(rd_kafka_t* rk);

WS_DLL_PUBLIC rd_kafka_t* init_consumer(kafka_params *kap);
WS_DLL_PUBLIC int au_kafka_consumer(rd_kafka_t *rk, kafka_params *kap);
WS_DLL_PUBLIC void destroy_consumer(rd_kafka_t* rk);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //WIRESHARK_KAFKA_AURORA_H
