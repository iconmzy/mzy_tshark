/*
 * librdkafka - Apache Kafka C library
 *
 * Copyright (c) 2019, Magnus Edenhill
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * Simple high-level balanced Apache Kafka consumer using the Kafka driver from librdkafka
 * (https://github.com/edenhill/librdkafka)
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#include "kafka_aurora.h"

static volatile sig_atomic_t run = 1;
/**
 * @brief Signal termination of program
 */
static void stop(int sig) {
	run = 0;
}

/**
 * 写pcap头
 * @param fp
 * @return
 */
void zhr_pcap_head(FILE * fp){
    unsigned char header[24] = {0xd4,0xc3,0xb2,0xa1, 0x02,0,0x04,0, 0,0,0,0, 0,0,0,0, 0xff,0xff,0,0, 1,0,0,0};
    fwrite(header, 1, 24, fp);
}

void zhr_atoi(const char *in, int len_in, unsigned char *out) {
    int i, j=0;
    char code[256];
    for(i=0;i<256;i++)code[i]=0;
    for(i='0';i<='9';i++)code[i]= i-'0';
    for(i='a';i<='f';i++)code[i]= i-'a'+10;

    for(i=0;i<len_in;i+=2) {
		out[j++] = (code[in[i]]<<4) + code[in[i+1]];
    }
}


rd_kafka_t * init_consumer(kafka_params *kap){
	rd_kafka_t *rk;          /* Consumer instance handle */
	rd_kafka_conf_t *conf;   /* Temporary configuration object */
	rd_kafka_resp_err_t err; /* librdkafka API error code */
	char errstr[512];        /* librdkafka API error reporting buffer */
	const char *brokers;     /* Argument: broker list */
	const char *groupid;     /* Argument: Consumer group id */
	char *topic;
	int topic_cnt;           /* Number of topics to subscribe to */
	rd_kafka_topic_partition_list_t *subscription; /* Subscribed topics */
	int i;

	brokers   = kap->brokers;
	groupid   = kap->groupid;
	topic = kap->topic;
	topic_cnt = kap->topic_cnt;

	/* Create Kafka client configuration place-holder */
	conf = rd_kafka_conf_new();

	/* Set bootstrap broker(s) as a comma-separated list of host or host:port (default port 9092).
	 * librdkafka will use the bootstrap brokers to acquire the full set of brokers from the cluster. */
	if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers, errstr,
						  sizeof(errstr)) != RD_KAFKA_CONF_OK) {
		fprintf(stderr, "%s\n", errstr);
		rd_kafka_conf_destroy(conf);
		return NULL;
	}

	/* Set the consumer group id.
	 * All consumers sharing the same group id will join the same
	 * group, and the subscribed topic' partitions will be assigned
	 * according to the partition.assignment.strategy
	 * (consumer config property) to the consumers in the group. */
	if (rd_kafka_conf_set(conf, "group.id", groupid, errstr,
						  sizeof(errstr)) != RD_KAFKA_CONF_OK) {
		fprintf(stderr, "%s\n", errstr);
		rd_kafka_conf_destroy(conf);
		return NULL;
	}

	/* If there is no previously committed offset for a partition
	 * the auto.offset.reset strategy will be used to decide where
	 * in the partition to start fetching messages.
	 * By setting this to earliest the consumer will read all messages
	 * in the partition if there was no previously committed offset. */
	if (rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", errstr,
						  sizeof(errstr)) != RD_KAFKA_CONF_OK) {
		fprintf(stderr, "%s\n", errstr);
		rd_kafka_conf_destroy(conf);
		return NULL;
	}

	/*
	 * Create consumer instance.
	 *
	 * NOTE: rd_kafka_new() takes ownership of the conf object
	 *       and the application must not reference it again after
	 *       this call.
	 */
	rk = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
	if (!rk) {
		fprintf(stderr, "%% Failed to create new consumer: %s\n", errstr);
		return NULL;
	}

	conf = NULL; /* Configuration object is now owned, and freed, by the rd_kafka_t instance. */

	/* Redirect all messages from per-partition queues to the main queue so that messages can be consumed with one
	 * call from all assigned partitions.
	 *
	 * The alternative is to poll the main queue (for events) and each partition queue separately,
	 * which requires setting up a rebalance callback and keeping track of the assignment:
	 * but that is more complex and typically not recommended. */
	rd_kafka_poll_set_consumer(rk);

	/* Convert the list of topics to a format suitable for librdkafka */
	subscription = rd_kafka_topic_partition_list_new(topic_cnt);
	for (i = 0; i < topic_cnt; i++)
		rd_kafka_topic_partition_list_add(subscription, topic,
				/* the partition is ignored  by subscribe() */ RD_KAFKA_PARTITION_UA);

	/* Subscribe to the list of topics */
	err = rd_kafka_subscribe(rk, subscription);
	if (err) {
		fprintf(stderr, "%% Failed to subscribe to %d topics: %s\n",
				subscription->cnt, rd_kafka_err2str(err));
		rd_kafka_topic_partition_list_destroy(subscription);
		rd_kafka_destroy(rk);
		return NULL;
	}

	rd_kafka_topic_partition_list_destroy(subscription);
	return rk;
}

int au_kafka_consumer(rd_kafka_t *rk, kafka_params *kap) {

    /* Signal handler for clean shutdown */
    signal(SIGINT, stop);

    /* Subscribing to topics will trigger a group rebalance
     * which may take some time to finish, but there is no need
     * for the application to handle this idle period in a special way
     * since a rebalance may happen at any time.
     * Start polling for messages. */

//    int packetNum = 1000;
//    FILE* pFile = fopen("/home/ymq/code/kafka_demo/Kafka_0000.pcap", "wb");
//    zhr_pcap_head(pFile);
    //int num=0;
    while (run) {
        rd_kafka_message_t *rkm;
        rkm = rd_kafka_consumer_poll(rk, 100);
        if (!rkm)
            continue; /* Timeout: no message within 100ms,
                                   *  try again. This short timeout allows
                                   *  checking for `run` at frequent intervals.
                                   */

        /* consumer_poll() will return either a proper message
         * or a consumer error (rkm->err is set). */
        if (rkm->err) {
            /* Consumer errors are generally to be considered
             * informational as the consumer will automatically try to recover from all types of errors. */
            fprintf(stderr, "%% Consumer error: %s\n", rd_kafka_message_errstr(rkm));
            rd_kafka_message_destroy(rkm);
            continue;
        }

        /* Proper message. */
//        printf("Message on %s [%" PRId32 "] at offset %" PRId64 ":\n",
//               rd_kafka_topic_name(rkm->rkt), rkm->partition,
//               rkm->offset);

        /* Print the message key & value/payload. */
        if (rkm->key && rkm->payload)
            printf("Key: %.*s\tValue(%d bytes): %.*s\n", (int)rkm->key_len, (const char *)rkm->key,
				   (int)rkm->len, (int)rkm->len, (const char *)rkm->payload);



        // 处理接收数据

//		int len_in = (int)rkm->len;
//		int out_len = len_in%2==0  ? len_in/2 : (len_in/2)+1;
//		unsigned char out[out_len];
//        zhr_atoi((char *)rkm->payload, len_in, out);

//        fwrite(out, out_len, 1, pFile);
        rd_kafka_message_destroy(rkm);

    }
//    fclose(pFile);


    return 0;
}

void destroy_consumer(rd_kafka_t* rk){
	/* Close the consumer: commit final offsets and leave the group. */
//	fprintf(stderr, "%% Closing consumer\n");
	rd_kafka_consumer_close(rk);

	/* Destroy the consumer */
	rd_kafka_destroy(rk);

}
